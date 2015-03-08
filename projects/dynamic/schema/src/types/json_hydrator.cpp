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
#include <istream>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/schema/types/hydration_error.hpp"
#include "dogen/dynamic/schema/types/json_hydrator.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("dynamic.schema.json_hydrator"));

const std::string invalid_json_file("Failed to parse JSON file");
const std::string invalid_option_in_json_file(
    "Failed to read option in JSON file: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string definition_has_no_name("Field definition has no 'name'.");
const std::string definition_has_no_hierarchy(
    "Field definition has no 'ownership_hierarchy'.");

const std::string name_key("name");
const std::string name_simple_key("simple");
const std::string name_qualified_key("qualified");
const std::string ownership_hierarchy_key("ownership_hierarchy");
const std::string ownership_hierarchy_model_name_key("model_name");
const std::string type_key("type");
const std::string scope_key("scope");

}

namespace dogen {
namespace dynamic {
namespace schema {

scope_types json_hydrator::to_scope_type(const std::string& /*s*/) const {
    scope_types r(scope_types::invalid);
    return r;
}

value_types json_hydrator::to_value_type(const std::string& /*s*/) const {
    value_types r(value_types::invalid);
    return r;
}

name json_hydrator::read_name(const boost::property_tree::ptree& /*pt*/) const {
    name r;
    return r;
}

ownership_hierarchy json_hydrator::
read_ownership_hierarchy(const boost::property_tree::ptree& /*pt*/) const {
    ownership_hierarchy r;
    return r;
}

std::forward_list<field_definition> json_hydrator::
read_stream(std::istream& s) const {
    using namespace boost::property_tree;
    ptree pt;
    read_json(s, pt);

    std::forward_list<field_definition> r;
    for (auto i(pt.begin()); i != pt.end(); ++i) {
        field_definition fd;

        auto j(pt.find(name_key));
        if (j == pt.not_found() || j->second.empty()) {
            BOOST_LOG_SEV(lg, error) << definition_has_no_name;
            BOOST_THROW_EXCEPTION(hydration_error(definition_has_no_name));
        }
        fd.name(read_name(i->second));

        j = pt.find(ownership_hierarchy_key);
        if (j == pt.not_found() || j->second.empty()) {
            BOOST_LOG_SEV(lg, error) << definition_has_no_hierarchy;
            BOOST_THROW_EXCEPTION(hydration_error(definition_has_no_hierarchy));
        }
        fd.ownership_hierarchy(read_ownership_hierarchy(i->second));

        fd.type(to_value_type(i->second.get_value<std::string>(type_key)));
        fd.scope(to_scope_type(i->second.get_value<std::string>(scope_key)));
        r.push_front(fd);
    }
    return r;
}

std::forward_list<field_definition> json_hydrator::
hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON stream.";
    using namespace boost::property_tree;
    try {
        auto r(read_stream(s));
        BOOST_LOG_SEV(lg, debug) << "Parsed JSON stream successfully.";
        return r;
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

std::forward_list<field_definition> json_hydrator::
hydrate(const boost::filesystem::path& p) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << p.generic_string();
    boost::filesystem::ifstream s(p);
    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Parsed JSON file successfully.";
    return r;
}

} } }
