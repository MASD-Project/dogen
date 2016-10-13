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
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/quilt.cpp/types/formattables/hydration_error.hpp"
#include "dogen/quilt.cpp/io/formattables/profile_group_io.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group_hydrator.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("quilt.cpp.formattables.profile_group_hydrator"));

const std::string profile_dir("profiles");
const std::string group_name_key("name");
const std::string parents_key("parents");
const std::string bind_to_stereotype_key("bind_to_stereotype");
const std::string decoration_profile_key("decoration_profile");
const std::string facet_name_key("facet_name");
const std::string formatter_name_key("formatter_name");
const std::string profile_type_key("profile_type");
const std::string default_facet_profile_key("default_facet_profile");
const std::string default_formatter_profile_key("default_formatter_profile");
const std::string facet_profiles_key("facet_profiles");
const std::string formatter_profiles_key("formatter_profiles");
const std::string licence_name_key("licence_name");
const std::string copyright_notices_key("copyright_notices");
const std::string modeline_group_name_key("modeline_group_name");
const std::string profile_type_global_value("global");
const std::string profile_type_local_value("local");
const std::string enabled_key("enabled");
const std::string overwrite_key("overwrite");

const std::string duplicate_profile_group_name(
    "Duplicate profile group name: ");
const std::string empty_profile_group_name(
    "Profile group name cannot be empty.");
const std::string empty_facet_profile_name(
    "Facet profile name cannot be empty.");
const std::string empty_formatter_profile_name(
    "Formatter profile name cannot be empty.");
const std::string duplicate_facet_profile_name(
    "Duplicate facet profile name: ");
const std::string duplicate_formatter_profile_name(
    "Duplicate formatter profile name: ");
const std::string invalid_json_file("Failed to parse JSON file: ");
const std::string empty_stereotype_name("Stereotype name cannot be empty.");
const std::string invalid_option_in_json_file(
    "Failed to read option in JSON file: ");
const std::string invalid_path("Failed to find path: ");
const std::string failed_to_open_file("Failed to open file: ");
const std::string invalid_profile_type("Invalid profile type: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::vector<boost::filesystem::path>
profile_group_hydrator::create_directory_list(
    const std::vector<boost::filesystem::path>& data_dirs) const {
    std::vector<boost::filesystem::path> r;
    r.reserve(data_dirs.size());
    for (const auto& d : data_dirs)
        r.push_back(d / profile_dir);
    return r;
}

profile_types
profile_group_hydrator::to_profile_type(const std::string v) const {
    if (v == profile_type_global_value)
        return profile_types::global;
    else if (v == profile_type_local_value)
        return profile_types::local;

    BOOST_LOG_SEV(lg, error) << invalid_profile_type << v;
    BOOST_THROW_EXCEPTION(hydration_error(invalid_profile_type + v));
}

decoration_profile profile_group_hydrator::
read_decoration_profile(const boost::property_tree::ptree& pt) const {
    decoration_profile r;

    const auto ln(pt.get_optional<std::string>(licence_name_key));
    if (ln)
        r.licence_name(*ln);

    const auto i = pt.find(copyright_notices_key);
    if (i != pt.not_found()) {
        for (auto j(i->second.begin()); j != i->second.end(); ++j) {
            const auto cn(j->second.get_value<std::string>());
            r.copyright_notices().push_back(cn);
        }
    }

    const auto mgn(pt.get_optional<std::string>(modeline_group_name_key));
    if (mgn)
        r.modeline_group_name(*mgn);

    return r;
}

std::pair<std::string, facet_profile> profile_group_hydrator::
read_facet_profile(const boost::property_tree::ptree& pt) const {
    std::pair<std::string, facet_profile> r;

    const auto name(pt.get_optional<std::string>(facet_name_key));
    if (name)
        r.first = *name;

    r.second.enabled(pt.get<bool>(enabled_key));

    const auto overwrite(pt.get_optional<bool>(overwrite_key));
    if (overwrite)
        r.second.overwrite(*overwrite);

    return r;
}

std::pair<std::string, formatter_profile> profile_group_hydrator::
read_formatter_profile(const boost::property_tree::ptree& pt) const {

    std::pair<std::string, formatter_profile> r;
    const auto name(pt.get_optional<bool>(formatter_name_key));
    if (name)
        r.first = *name;

    r.second.enabled(pt.get<bool>(enabled_key));

    const auto overwrite(pt.get_optional<bool>(overwrite_key));
    if (overwrite)
        r.second.overwrite(*overwrite);

    return r;
}

std::unordered_map<std::string, facet_profile> profile_group_hydrator::
read_facet_profiles(const boost::property_tree::ptree& pt) const {
    std::unordered_map<std::string, facet_profile> r;
    for (auto i(pt.begin()); i != pt.end(); ++i) {
        const auto pair(read_facet_profile(i->second));
        const auto fctn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing facet profile: " << fctn;
        if (fctn.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_facet_profile_name;
            BOOST_THROW_EXCEPTION(hydration_error(empty_facet_profile_name));
        }

        const auto& fct_prf(pair.second);
        const auto fct_prf_pair(std::make_pair(fctn, fct_prf));
        const auto inserted(r.insert(fct_prf_pair).second);
        if (inserted)
            continue;

        BOOST_LOG_SEV(lg, error) << duplicate_facet_profile_name << fctn;
        BOOST_THROW_EXCEPTION(
            hydration_error(duplicate_facet_profile_name + fctn));
    }
    return r;
}

std::unordered_map<std::string, formatter_profile> profile_group_hydrator::
read_formatter_profiles(const boost::property_tree::ptree& pt) const {
    std::unordered_map<std::string, formatter_profile> r;
    for (auto i(pt.begin()); i != pt.end(); ++i) {
        const auto pair(read_formatter_profile(i->second));
        const auto fmtn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing formatter profile: " << fmtn;
        if (fmtn.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_profile_name;
            BOOST_THROW_EXCEPTION(
                hydration_error(empty_formatter_profile_name));
        }

        const auto& fmt_prf(pair.second);
        const auto fmt_prf_pair(std::make_pair(fmtn, fmt_prf));
        const auto inserted(r.insert(fmt_prf_pair).second);
        if (inserted)
            continue;

        BOOST_LOG_SEV(lg, error) << duplicate_formatter_profile_name << fmtn;
        BOOST_THROW_EXCEPTION(
            hydration_error(duplicate_formatter_profile_name + fmtn));
    }
    return r;
}

profile_group profile_group_hydrator::read_stream(std::istream& s) const {
    using namespace boost::property_tree;
    ptree pt;
    read_json(s, pt);

    profile_group r;
    r.name(pt.get<std::string>(group_name_key));
    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_profile_group_name;
        BOOST_THROW_EXCEPTION(hydration_error(empty_profile_group_name));
    }
    BOOST_LOG_SEV(lg, debug) << "Procesing profile group: " << r.name();

    auto i = pt.find(parents_key);
    if (i != pt.not_found()) {
        const auto& parents(i->second);
        for (auto j(parents.begin()); j != parents.end(); ++j)
            r.parents().push_back(j->second.get_value<std::string>());
    }

    const auto bts(pt.get_optional<std::string>(bind_to_stereotype_key));
    if (bts) {
        r.bind_to_stereotype(*bts);
        if (r.bind_to_stereotype().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_stereotype_name;
            BOOST_THROW_EXCEPTION(hydration_error(empty_stereotype_name));
        }
    }

    i = pt.find(decoration_profile_key);
    if (i != pt.not_found())
        r.decoration_profile(read_decoration_profile(i->second));

    const auto prft(pt.get_optional<std::string>(profile_type_key));
    if (prft)
        r.profile_type(to_profile_type(*prft));

    i = pt.find(default_facet_profile_key);
    if (i != pt.not_found()) {
        const auto pair(read_facet_profile(i->second));
        const auto& fct_prf(pair.second);
        r.default_facet_profile(fct_prf);
    }

    i = pt.find(default_formatter_profile_key);
    if (i != pt.not_found()) {
        const auto pair(read_formatter_profile(i->second));
        const auto& fmt_prf(pair.second);
        r.default_formatter_profile(fmt_prf);
    }

    i = pt.find(facet_profiles_key);
    if (i != pt.not_found())
        r.facet_profiles(read_facet_profiles(i->second));

    i = pt.find(formatter_profiles_key);
    if (i != pt.not_found())
        r.formatter_profiles(read_formatter_profiles(i->second));

    return r;
}

profile_group profile_group_hydrator::hydrate(std::istream& s) const {
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

profile_group profile_group_hydrator::
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

std::unordered_map<std::string, profile_group> profile_group_hydrator::
hydrate(const std::vector<boost::filesystem::path>& data_dirs) const {
    BOOST_LOG_SEV(lg, debug) << "Hydrating profile groups.";

    const auto dl(create_directory_list(data_dirs));
    BOOST_LOG_SEV(lg, debug) << "Directory list: " << dl;

    std::unordered_map<std::string, formattables::profile_group> r;
    const auto files(dogen::utility::filesystem::find_files(dl));
    for (const auto& f : files) {
        BOOST_LOG_SEV(lg, debug) << "Hydrating file: " << f.generic_string();
        const auto pg(hydrate(f));
        const auto pgn(pg.name());
        const auto pair(std::make_pair(pgn, pg));
        const auto inserted(r.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_profile_group_name + pgn;
            BOOST_THROW_EXCEPTION(
                hydration_error(duplicate_profile_group_name + pgn));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Hydrated profile groups. Found: " << r.size();
    BOOST_LOG_SEV(lg, debug) << "Profile groups: " << r;
    return r;
}

} } } }
