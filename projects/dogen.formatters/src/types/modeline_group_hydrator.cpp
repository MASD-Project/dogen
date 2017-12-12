/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen.formatters/types/hydration_error.hpp"
#include "dogen.formatters/types/modeline_group_hydrator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("formatters.modeline_group_hydrator"));

const std::string invalid_json_file("Failed to parse JSON file: ");
const std::string invalid_option_in_json_file(
    "Failed to read option in JSON file: ");
const std::string invalid_path("Failed to find path: ");
const std::string invalid_editor("Invalid or unsupported editor: ");
const std::string invalid_location(
    "Invalid or unsupported modeline location: ");
const std::string no_fields("Modeline must have at least one field");
const std::string no_modelines(
    "Modeline group must have at least one modeline");
const std::string duplicate_modeline_name(
    "Modeline name must be unique. Duplicate: ");
const std::string empty_modeline_name("Modeline name cannot be empty.");
const std::string failed_to_open_file("Failed to open file: ");

const std::string group_name_key("group_name");
const std::string modelines_key("modelines");
const std::string modeline_name_key("modeline_name");
const std::string editor_key("editor");
const std::string location_key("location");
const std::string fields_key("fields");
const std::string field_name_key("name");
const std::string field_value_key("value");

const std::string editor_emacs_value("emacs");
const std::string editor_vi_value("vi");
const std::string editor_vim_value("vim");
const std::string editor_ex_value("ex");

const std::string location_top_value("top");
const std::string location_bottom_value("bottom");

}

namespace dogen {
namespace formatters {

editors modeline_group_hydrator::to_editor(const std::string value) const {
    if (value == editor_emacs_value)
        return editors::emacs;
    else if (value == editor_vi_value)
        return editors::vi;
    else if (value == editor_vim_value)
        return editors::vim;
    else if (value == editor_ex_value)
        return editors::ex;

    BOOST_LOG_SEV(lg, error) << invalid_editor << value;
    BOOST_THROW_EXCEPTION(hydration_error(invalid_editor + value));
}

modeline_locations
modeline_group_hydrator::to_modeline_location(const std::string value) const {
    if (value == location_top_value)
        return modeline_locations::top;
    else if (value == location_bottom_value)
        return modeline_locations::bottom;

    BOOST_LOG_SEV(lg, error) << invalid_location << value;
    BOOST_THROW_EXCEPTION(hydration_error(invalid_location + value));
}

modeline modeline_group_hydrator::
read_modeline(const boost::property_tree::ptree& pt) const {
    modeline r;
    r.editor(to_editor(pt.get<std::string>(editor_key)));

    const auto location(pt.get_optional<std::string>(location_key));
    if (location)
        r.location(to_modeline_location(*location));
    else
        r.location(modeline_locations::top);

    r.name(pt.get<std::string>(modeline_name_key));
    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_modeline_name;
        BOOST_THROW_EXCEPTION(hydration_error(empty_modeline_name));
    }

    const auto i(pt.find(fields_key));
    if (i == pt.not_found()) {
        BOOST_LOG_SEV(lg, error) << no_fields;
        BOOST_THROW_EXCEPTION(hydration_error(no_fields));
    }

    const auto& fields(i->second);
    for (auto j(fields.begin()); j != fields.end(); ++j) {
        modeline_field f;
        f.name(j->second.get<std::string>(field_name_key));
        f.value(j->second.get<std::string>(field_value_key));
        r.fields().push_back(f);
    }

    if (r.fields().empty()) {
        BOOST_LOG_SEV(lg, error) << no_fields;
        BOOST_THROW_EXCEPTION(hydration_error(no_fields));
    }
    return r;
}

modeline_group modeline_group_hydrator::read_stream(std::istream& s) const {
    modeline_group r;

    using namespace boost::property_tree;
    ptree pt;
    read_json(s, pt);

    r.name(pt.get<std::string>(group_name_key));
    const auto i(pt.find(modelines_key));
    if (i == pt.not_found()) {
        BOOST_LOG_SEV(lg, error) << no_modelines;
        BOOST_THROW_EXCEPTION(hydration_error(no_modelines));
    }

    const auto& modelines(i->second);
    for (auto j(modelines.begin()); j != modelines.end(); ++j) {
        const auto ml(read_modeline(j->second));
        const auto result(r.modelines().insert(std::make_pair(ml.name(), ml)));
        if (!result.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_modeline_name << ml.name();
            BOOST_THROW_EXCEPTION(
                hydration_error(duplicate_modeline_name + ml.name()));
        }
    }

    if (r.modelines().empty()) {
        BOOST_LOG_SEV(lg, error) << no_modelines;
        BOOST_THROW_EXCEPTION(hydration_error(no_modelines));
    }

    return r;
}

modeline_group modeline_group_hydrator::hydrate(std::istream& s) const {
    using namespace boost::property_tree;
    try {
        return read_stream(s);
    } catch (const json_parser_error& e) {
        BOOST_LOG_SEV(lg, error) << invalid_json_file << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_json_file + e.what()));
    } catch (const ptree_bad_data& e) {
        BOOST_LOG_SEV(lg, error) << invalid_option_in_json_file << ": "
                                 << e.what();
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_option_in_json_file + e.what()));
    } catch (const ptree_bad_path& e) {
        BOOST_LOG_SEV(lg, error) << invalid_path << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_path + e.what()));
    }
}

modeline_group modeline_group_hydrator::
hydrate(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Reading file: " << gs;

    boost::filesystem::ifstream s(p);
    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << ": " << gs;
        BOOST_THROW_EXCEPTION(hydration_error(failed_to_open_file + gs));
    }

    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Read file successfully.";
    return r;
}

} }
