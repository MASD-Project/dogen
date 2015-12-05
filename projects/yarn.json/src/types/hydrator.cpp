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
#include <istream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn.json/types/hydration_error.hpp"
#include "dogen/yarn.json/types/hydrator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.json.hydrator"));

const std::string empty;
const std::string in_global_module_key("in_global_module");
const std::string model_name_key("model_name");
const std::string bool_true("true");
const std::string bool_false("false");

const std::string documentation_key("documentation");
const std::string origin_key("origin");
const std::string origin_system_value("system");
const std::string origin_user_value("user");
const std::string elements_key("elements");

const std::string meta_type_key("meta_type");
const std::string meta_type_object_value("object");
const std::string meta_type_primitive_value("primitive");

const std::string simple_name_key("simple_name");
const std::string internal_module_path_key("internal_module_path");
const std::string extensions_key("extensions");

const std::string object_type_key("object_type");
const std::string object_type_smart_pointer_value("smart_pointer");
const std::string object_type_ordered_container_value("ordered_container");
const std::string object_type_hash_container_value("hash_container");
const std::string object_type_sequence_container_value("sequence_container");

const std::string invalid_json_file("Failed to parse JSON file");
const std::string invalid_option_in_json_file(
    "Failed to read option in JSON file: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string invalid_origin("Invalid value for origin: ");
const std::string invalid_meta_type("Invalid value for meta type: ");
const std::string model_has_no_types("Did not find any elements in model");
const std::string missing_module("Could not find module: ");
const std::string failed_to_open_file("Failed to open file: ");
const std::string invalid_object_type("Invalid or unsupported object type: ");

}

namespace dogen {
namespace yarn {
namespace json {

hydrator::hydrator(const dynamic::workflow& w)
    : dynamic_workflow_(w) { }

yarn::generation_types hydrator::generation_type(const bool is_target) const {
    return is_target ?
        yarn::generation_types::full_generation :
        yarn::generation_types::no_generation;
}

dynamic::object hydrator::
create_dynamic_extensions(const boost::property_tree::ptree& pt,
    const dynamic::scope_types st) const {
    const auto i(pt.find(extensions_key));
    if (i == pt.not_found())
        return dynamic::object();

    dynamic::object r;
    std::list<std::pair<std::string, std::string> > kvps;
    for (auto j(i->second.begin()); j != i->second.end(); ++j) {
        const auto field_name(j->first);
        const auto field_value(j->second.get_value<std::string>());
        kvps.push_back(std::make_pair(field_name, field_value));
    }
    return dynamic_workflow_.execute(st, kvps);
}

void hydrator::read_element(const boost::property_tree::ptree& pt,
    yarn::intermediate_model& m) const {

    yarn::name_builder b;
    const auto in_global_module(pt.get(in_global_module_key, false));
    if (!in_global_module)
        b.model_name(m.name().location());

    const auto simple_name_value(pt.get<std::string>(simple_name_key));
    b.simple_name(simple_name_value);

    const auto i(pt.find(internal_module_path_key));
    if (i != pt.not_found()) {
        std::list<std::string> ipp;
        for (auto& item : pt.get_child(internal_module_path_key))
            ipp.push_back(item.second.get_value<std::string>());

        if (!ipp.empty())
            b.internal_module_path(ipp);
        else {
            BOOST_LOG_SEV(lg, debug) << "Ignoring empty internal module path. "
                                     << "Type: " << simple_name_value;
        }
    }

    yarn::name n(b.build());
    const auto documentation(pt.get_optional<std::string>(documentation_key));

    const auto lambda([&](yarn::element& e) {
            BOOST_LOG_SEV(lg, debug) << "Processing element: " << n.qualified();
            e.name(n);
            e.origin_type(m.origin_type());
            e.generation_type(m.generation_type());
            e.in_global_module(in_global_module);

            if (documentation)
                e.documentation(*documentation);

            const auto scope(dynamic::scope_types::entity);
            e.extensions(create_dynamic_extensions(pt, scope));
        });

    const auto meta_type_value(pt.get<std::string>(meta_type_key));
    if (meta_type_value == meta_type_object_value) {
        yarn::object o;
        lambda(o);

        const auto ot(pt.get_optional<std::string>(object_type_key));
        o.object_type(to_object_type(ot));
        m.objects().insert(std::make_pair(n.qualified(), o));
    } else if (meta_type_value == meta_type_primitive_value) {
        yarn::primitive p;
        lambda(p);
        m.primitives().insert(std::make_pair(n.qualified(), p));
    }
    else {
        BOOST_LOG_SEV(lg, error) << invalid_meta_type << meta_type_value;
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_meta_type + meta_type_value));
    }
}

yarn::intermediate_model hydrator::read_stream(
    std::istream& s, const bool is_target) const {
    yarn::intermediate_model r;
    r.generation_type(generation_type(is_target));

    boost::property_tree::ptree pt;
    read_json(s, pt);

    const auto model_name_value(pt.get<std::string>(model_name_key));
    r.original_model_name(model_name_value);

    yarn::name_factory nf;
    r.name(nf.build_model_name(model_name_value));
    BOOST_LOG_SEV(lg, debug) << "Processing model: " << r.name().qualified();

    const auto scope(dynamic::scope_types::root_module);
    r.extensions(create_dynamic_extensions(pt, scope));

    const auto documentation(pt.get_optional<std::string>(documentation_key));
    if (documentation)
        r.documentation(*documentation);

    const auto origin_value(pt.get<std::string>(origin_key));
    if (origin_value == origin_system_value)
        r.origin_type(yarn::origin_types::system);
    else if (origin_value == origin_user_value)
        r.origin_type(yarn::origin_types::system);
    else {
        BOOST_LOG_SEV(lg, error) << invalid_origin << origin_value;
        BOOST_THROW_EXCEPTION(hydration_error(invalid_origin + origin_value));
    }

    yarn::module m;
    m.name(r.name());
    m.origin_type(r.origin_type());
    m.generation_type(r.generation_type());
    r.modules().insert(std::make_pair(m.name().qualified(), m));

    const auto i(pt.find(elements_key));
    if (i == pt.not_found() || i->second.empty()) {
        BOOST_LOG_SEV(lg, error) << model_has_no_types;
        BOOST_THROW_EXCEPTION(hydration_error(model_has_no_types));
    }

    for (auto j(i->second.begin()); j != i->second.end(); ++j)
        read_element(j->second, r);

    return r;
}

yarn::object_types hydrator::
to_object_type(const boost::optional<std::string>& s) const {
    if (!s)
        return yarn::object_types::user_defined_value_object;

    const auto ot(*s);
    if (ot == object_type_smart_pointer_value)
        return yarn::object_types::smart_pointer;
    else if (ot == object_type_ordered_container_value)
        return yarn::object_types::ordered_container;
    else if (ot == object_type_hash_container_value)
        return yarn::object_types::hash_container;
    else if (ot == object_type_sequence_container_value)
        return yarn::object_types::sequence_container;

    BOOST_LOG_SEV(lg, error) << invalid_object_type << ot;
    BOOST_THROW_EXCEPTION(hydration_error(invalid_object_type + ot));
}

yarn::intermediate_model hydrator::hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON stream.";
    using namespace boost::property_tree;
    try {
        const bool is_target(false);
        auto r(read_stream(s, is_target));
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

yarn::intermediate_model hydrator::
hydrate(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << gs;
    boost::filesystem::ifstream s(p);

    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << ": " << gs;
        BOOST_THROW_EXCEPTION(hydration_error(failed_to_open_file + gs));
    }

    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Parsed JSON file successfully.";
    return r;
}

} } }
