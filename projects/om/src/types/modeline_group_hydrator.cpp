/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/throw_exception.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/om/types/hydration_error.hpp"
#include "dogen/om/types/modeline_group_hydrator.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om.modeline_group_hydrator"));

const std::string empty;
const std::string duplicate_modeline_group("Duplicate modeline group found: ");
const std::string invalid_group_name("Invalid group name: ");
const std::string invalid_ini_file("Failed to parse INI file: ");
const std::string invalid_option_in_ini_file("Failed to read option in INI file: ");
const std::string invalid_path("Failed to find INI file: ");
const std::string invalid_directory("Not a directory: ");
const std::string directory_not_found("Could not find directory: ");
const std::string invalid_editor("Invalid or unsupported editor: ");
const std::string invalid_location(
    "Invalid or unsupported modeline location: ");

const std::string cpp_group_name("c++");
const std::string odb_group_name("odb");
const std::string cmake_group_name("cmake");

const std::string editor_field("editor");
const std::string editor_emacs_value("emacs");
const std::string editor_vi_value("vi");
const std::string editor_vim_value("vim");
const std::string editor_ex_value("ex");

const std::string location_field("location");
const std::string location_top_value("top");
const std::string location_bottom_value("bottom");

const std::string space_code("space");
const std::string space_value(" ");

}

namespace dogen {
namespace om {

editors modeline_group_hydrator::
translate_editor_enum(const std::string value) const {
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

modeline_locations modeline_group_hydrator::
translate_location_enum(const std::string value) const {
    if (value == location_top_value)
        return modeline_locations::top;
    else if (value == location_bottom_value)
        return modeline_locations::bottom;

    BOOST_LOG_SEV(lg, error) << invalid_location << value;
    BOOST_THROW_EXCEPTION(hydration_error(invalid_location + value));
}

std::string modeline_group_hydrator::
translate_special_values(const std::string value) const {
    if (value == space_value)
        return space_code;
    return value;
}

bool modeline_group_hydrator::
is_group_name_valid(const std::string& n) const {
    return
        n == cpp_group_name || n == odb_group_name ||
        n == cmake_group_name;
}

modeline_group modeline_group_hydrator::hydrate(std::istream& i) const {
    modeline_group r;
    using namespace boost::property_tree;
    try {
        ptree pt;
        read_ini(i, pt);
        for (ptree::const_iterator i(pt.begin()); i != pt.end(); ++i) {
            const auto& sn(i->first);
            if (!is_group_name_valid(sn)) {
                BOOST_LOG_SEV(lg, error) << invalid_group_name << sn;
                BOOST_THROW_EXCEPTION(
                    hydration_error(invalid_group_name + sn));
            }

            modeline p;
            for (ptree::const_iterator j(i->second.begin());
                 j != i->second.end();
                 ++j) {

                const auto field_name(j->first);
                const auto field_value(j->second.get_value<std::string>());

                if (field_name == editor_field)
                    p.editor(translate_editor_enum(field_value));
                else if (field_name == location_field)
                    p.location(translate_location_enum(field_value));
                else {
                    modeline_field f;
                    f.name(field_name);
                    f.value(translate_special_values(field_value));
                    p.fields().push_back(f);
                }
            }
            r.modelines().insert(std::make_pair(sn, p));
        }
    } catch (const ini_parser_error& e) {
        BOOST_LOG_SEV(lg, error) << invalid_ini_file << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_ini_file + e.what()));
    } catch (const ptree_bad_data& e) {
        BOOST_LOG_SEV(lg, error) << invalid_option_in_ini_file << ": "
                                 << e.what();
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_option_in_ini_file + e.what()));
    } catch (const ptree_bad_path& e) {
        BOOST_LOG_SEV(lg, error) << invalid_path << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_path + e.what()));
    }

    return r;
}

} }
