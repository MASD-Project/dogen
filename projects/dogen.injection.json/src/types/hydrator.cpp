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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.injection.json/types/hydration_error.hpp"
#include "dogen.injection.json/types/hydrator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("injection.json.hydrator"));

const std::string empty;
const std::string object_element_type("masd::object");
const std::string fallback_element_type_key("fallback_element_type");
const std::string name_key("name");
const std::string parents_key("parents");
const std::string documentation_key("documentation");
const std::string tagged_values_key("tagged_values");
const std::string type_key("type");
const std::string value_key("value");
const std::string elements_key("elements");
const std::string attributes_key("attributes");
const std::string stereotypes_key("stereotypes");
const std::string in_global_module_key("in_global_module");
const std::string can_be_enumeration_underlier_key(
    "can_be_enumeration_underlier");
const std::string can_be_primitive_underlier_key(
    "can_be_primitive_underlier");
const std::string is_associative_container_key("is_associative_container");
const std::string is_floating_point_key("is_floating_point");
const std::string is_default_enumeration_type_key(
    "is_default_enumeration_type");

const std::string mssing_elements("Missing mandatory elements collection.");
const std::string invalid_json_file("Failed to parse JSON file: ");
const std::string invalid_value_in_json("Failed to value in JSON: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string failed_to_open_file("Failed to open file: ");

}

namespace dogen::injection::json {

std::string
hydrator::read_documentation(const boost::property_tree::ptree& pt) const {
    const auto opt(pt.get_optional<std::string>(documentation_key));
    if (!opt)
        return empty;

    const auto r(*opt);
    return r;
}

std::list<std::pair<std::string, std::string>>
hydrator::read_tagged_values(const boost::property_tree::ptree& pt) const {
    std::list<std::pair<std::string, std::string>> r;
    const auto i(pt.find(tagged_values_key));
    if (i == pt.not_found() || i->second.empty())
        return r;

    for (auto j(i->second.begin()); j != i->second.end(); ++j) {
        const auto key(j->first);
        const auto value(j->second.get_value<std::string>());
        r.push_back(std::make_pair(key, value));
    }
    return r;
}

std::list<std::string>
hydrator::read_stereotypes(const boost::property_tree::ptree& pt) const {
    std::list<std::string> r;
    const auto i(pt.find(stereotypes_key));
    if (i == pt.not_found() || i->second.empty())
        return r;

    for (auto j(i->second.begin()); j != i->second.end(); ++j)
        r.push_back(j->second.get_value<std::string>());

    return r;
}

std::list<std::string>
hydrator::read_parents(const boost::property_tree::ptree& pt) const {
    std::list<std::string> r;
    const auto i(pt.find(parents_key));
    if (i == pt.not_found() || i->second.empty())
        return r;

    for (auto j(i->second.begin()); j != i->second.end(); ++j)
        r.push_back(j->second.get_value<std::string>());

    return r;
}

injection::entities::attribute hydrator::
read_attribute(const boost::property_tree::ptree& pt) const {
    injection::entities::attribute r;
    r.name(pt.get<std::string>(name_key));
    r.type(pt.get<std::string>(type_key));
    r.value(pt.get<std::string>(value_key, empty));
    r.documentation(read_documentation(pt));
    r.tagged_values(read_tagged_values(pt));
    r.stereotypes(read_stereotypes(pt));

    return r;
}

injection::entities::element hydrator::read_element(
    const boost::property_tree::ptree& pt, const std::string& id) const {
    injection::entities::element r;
    r.name(pt.get<std::string>(name_key));
    r.documentation(read_documentation(pt));
    r.parents(read_parents(pt));
    r.tagged_values(read_tagged_values(pt));
    r.stereotypes(read_stereotypes(pt));

    const auto opt(pt.get_optional<std::string>(fallback_element_type_key));
    if (!opt)
        r.fallback_element_type(object_element_type);
    else
        r.fallback_element_type(*opt);

    const auto i(pt.find(attributes_key));
    if (i == pt.not_found() || i->second.empty())
        BOOST_LOG_SEV(lg, debug) << "Did not find any attributes in element.";
    else {
        for (auto j(i->second.begin()); j != i->second.end(); ++j)
            r.attributes().push_back(read_attribute(j->second));
    }

    const auto f(false);
    r.origin_element_id(id);
    r.in_global_module(pt.get(in_global_module_key, f));
    r.is_associative_container(pt.get(is_associative_container_key, f));
    r.can_be_primitive_underlier(pt.get(can_be_primitive_underlier_key, f));
    r.is_default_enumeration_type(pt.get(is_default_enumeration_type_key, f));
    r.is_floating_point(pt.get(is_floating_point_key, f));
    r.can_be_enumeration_underlier(pt.get(can_be_enumeration_underlier_key, f));

    return r;
}

injection::entities::model
hydrator::read_stream(std::istream& s) const {
    boost::property_tree::ptree pt;
    read_json(s, pt);

    injection::entities::model r;
    r.documentation(read_documentation(pt));
    r.tagged_values(read_tagged_values(pt));
    r.stereotypes(read_stereotypes(pt));

    const auto i(pt.find(elements_key));
    if (i == pt.not_found()) {
        BOOST_LOG_SEV(lg, error) << mssing_elements;
        BOOST_THROW_EXCEPTION(hydration_error(mssing_elements));
    } else if (i->second.empty())
        BOOST_LOG_SEV(lg, warn) << "Elements collection is empty.";
    else {
        /*
         * Compute an element ID based on the position of the object
         * in the diagram. This allows us to uniquely identify an
         * element in a diagram.
         */
        const std::string prefix("J");
        unsigned int j = 0;
        for (auto k = i->second.begin(); k != i->second.end(); ++k, ++j) {
            const auto id(prefix + std::to_string(j));
            r.elements().push_back(read_element(k->second, id));
        }
    }

    return r;
}

injection::entities::model hydrator::hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON stream.";
    using namespace boost::property_tree;
    try {
        auto r(read_stream(s));
        BOOST_LOG_SEV(lg, debug) << "Parsed JSON stream successfully.";
        return r;
    } catch (const json_parser_error& e) {
        BOOST_LOG_SEV(lg, error) << invalid_json_file << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_json_file + e.what()));
    } catch (const ptree_bad_data& e) {
        BOOST_LOG_SEV(lg, error) << invalid_value_in_json << e.what();
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_value_in_json + e.what()));
    } catch (const ptree_bad_path& e) {
        BOOST_LOG_SEV(lg, error) << invalid_path << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_path + e.what()));
    }
}

injection::entities::model
hydrator::hydrate(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << gs;
    boost::filesystem::ifstream s(p);

    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << gs;
        BOOST_THROW_EXCEPTION(hydration_error(failed_to_open_file + gs));
    }

    auto r(hydrate(s));
    r.name(p.stem().generic_string());

    BOOST_LOG_SEV(lg, debug) << "Parsed JSON file successfully.";
    return r;
}

}
