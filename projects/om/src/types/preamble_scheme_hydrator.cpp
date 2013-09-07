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
#include "dogen/om/types/preamble_scheme_hydrator.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om.preamble_scheme_hydrator"));

const std::string empty;
const std::string invalid_scheme_name("Invalid scheme name: ");
const std::string invalid_ini_file("Failed to parse INI file: ");
const std::string invalid_option_in_ini_file("Failed to read option in INI file: ");
const std::string invalid_path("Failed to find INI file: ");
const std::string invalid_directory("Not a directory: ");
const std::string directory_not_found("Could not find directory: ");

const std::string cpp_scheme_name("c++");
const std::string odb_scheme_name("odb");
const std::string cmake_scheme_name("cmake");

const std::string prefix_field("prefix");
const std::string kvp_separator_field("kvp_separator");
const std::string field_separator_field("field_separator");
const std::string postfix_field("postfix");
const std::string space_code("space");
const std::string space_value(" ");

}

namespace dogen {
namespace om {

preamble_scheme_hydrator::preamble_scheme_hydrator(
    const std::list<boost::filesystem::path>& directories)
    : directories_(directories) { }


std::list<boost::filesystem::path>
preamble_scheme_hydrator::
files_in_directory(const boost::filesystem::path& d) const {
    if (!boost::filesystem::is_directory(d))
        BOOST_THROW_EXCEPTION(hydration_error(invalid_directory + d.string()));

    if (!boost::filesystem::exists(d))
        BOOST_THROW_EXCEPTION(
            hydration_error(directory_not_found + d.string()));

    std::list<boost::filesystem::path> r;
    using boost::filesystem::recursive_directory_iterator;
    for (recursive_directory_iterator end, i(d); i != end; ++i) {
        const auto& p(*i);
        if (boost::filesystem::is_regular_file(p))
            r.push_back(p);
    }

    BOOST_LOG_SEV(lg, debug) << "Files found in directory " << d.string()
                             << ": " << r;

    return r;
}

std::string preamble_scheme_hydrator::
translate_special_values(const std::string value) const {
    if (value == space_value)
        return space_code;
    return value;
}

bool preamble_scheme_hydrator::
is_scheme_name_valid(const std::string& n) const {
    return
        n == cpp_scheme_name || n == odb_scheme_name ||
        n == cmake_scheme_name;
}

preamble_scheme preamble_scheme_hydrator::
hydrate_file(const boost::filesystem::path& f) const {
    const auto path(f.string());
    BOOST_LOG_SEV(lg, debug) << "hydrating file: " << path;

    preamble_scheme r;
    using namespace boost::property_tree;
    try {

        ptree pt;
        read_ini(path, pt);
        for (ptree::const_iterator i(pt.begin()); i != pt.end(); ++i) {
            const auto& sn(i->first);
            if (!is_scheme_name_valid(sn)) {
                BOOST_LOG_SEV(lg, error) << invalid_scheme_name << sn;
                BOOST_THROW_EXCEPTION(
                    hydration_error(invalid_scheme_name + sn));
            }

            preamble p;
            for (ptree::const_iterator j(i->second.begin());
                 j != i->second.end();
                 ++j) {

                const auto field_name(j->first);
                const auto field_value(j->second.get_value<std::string>());
                if (field_name == prefix_field)
                    p.prefix(translate_special_values(field_value));
                else if (field_name == kvp_separator_field)
                    p.kvp_separator(translate_special_values(field_value));
                else if (field_name == field_separator_field)
                    p.field_separator(translate_special_values(field_value));
                else if (field_name == postfix_field)
                    p.postfix(translate_special_values(field_value));
                else {
                    preamble_field f;
                    f.name(field_name);
                    f.value(translate_special_values(field_value));
                    p.fields().push_back(f);
                }
            }
            r.preambles().insert(std::make_pair(sn, p));
        }
    } catch (const ini_parser_error& e) {
        BOOST_LOG_SEV(lg, error) << invalid_ini_file << path
                                 << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_ini_file + path));
    } catch (const ptree_bad_data& e) {
        BOOST_LOG_SEV(lg, error) << invalid_option_in_ini_file << path
                                 << ": " << e.what();
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_option_in_ini_file + path));
    } catch (const ptree_bad_path& e) {
        BOOST_LOG_SEV(lg, error) << invalid_path << path
                                 << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_path + path));
    }

    return r;
}

std::unordered_map<std::string, preamble_scheme>
preamble_scheme_hydrator::hydrate() const {
    std::unordered_map<std::string, preamble_scheme> r;

    for (const auto& d : directories_) {
        for (const auto& f : files_in_directory(d))
            r.insert(std::make_pair(f.filename().string(), hydrate_file(f)));
    }

    return r;
}

} }
