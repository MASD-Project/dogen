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
#include "dogen/annotations/types/scribble_group.hpp"
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
const std::string is_default_enumeration_type_key(
    "is_default_enumeration_type");
const std::string in_global_module_key("in_global_module");
const std::string model_name_key("model_name");
const std::string bool_true("true");
const std::string bool_false("false");

const std::string documentation_key("documentation");
const std::string elements_key("elements");

const std::string meta_type_key("meta_type");
const std::string meta_type_object_value("object");
const std::string meta_type_primitive_value("primitive");

const std::string simple_name_key("simple_name");
const std::string internal_modules_key("internal_modules");
const std::string annotations_key("annotation");

const std::string object_type_key("object_type");
const std::string object_type_smart_pointer_value("smart_pointer");
const std::string object_type_associative_container_value(
    "associative_container");
const std::string object_type_sequence_container_value("sequence_container");

const std::string invalid_json_file("Failed to parse JSON file");
const std::string invalid_option_in_json_file(
    "Failed to read option in JSON file: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string invalid_meta_type("Invalid value for meta type: ");
const std::string model_has_no_types("Did not find any elements in model");
const std::string missing_module("Could not find module: ");
const std::string failed_to_open_file("Failed to open file: ");
const std::string invalid_object_type("Invalid or unsupported object type: ");
const std::string duplicate_element_id("Duplicate element id: ");

}

namespace dogen {
namespace yarn {
namespace json {

yarn::generation_types hydrator::generation_type(const bool is_target) const {
    return is_target ?
        yarn::generation_types::full_generation :
        yarn::generation_types::no_generation;
}

std::list<std::pair<std::string, std::string>>
hydrator::read_kvps(const boost::property_tree::ptree& pt) const {

    std::list<std::pair<std::string, std::string>> r;
    const auto i(pt.find(annotations_key));
    if (i == pt.not_found())
        return r;

    for (auto j(i->second.begin()); j != i->second.end(); ++j) {
        const auto field_name(j->first);
        const auto field_value(j->second.get_value<std::string>());
        r.push_back(std::make_pair(field_name, field_value));
    }
    return r;
}

void hydrator::insert_scribbles(const yarn::name& owner,
    const std::list<std::pair<std::string, std::string>>& kvps,
    intermediate_model& im) const {

    if (kvps.empty())
        return;

    annotations::scribble_group sgrp;
    sgrp.parent(annotations::scribble(kvps));
    const auto id(owner.id());
    const auto pair(std::make_pair(id, sgrp));
    const bool inserted(im.indices().scribble_groups().insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element_id << id;
        BOOST_THROW_EXCEPTION(hydration_error(duplicate_element_id + id));
    }
}

void hydrator::read_element(const boost::property_tree::ptree& pt,
    yarn::intermediate_model& im) const {

    yarn::name_builder b;
    const auto in_global_module(pt.get(in_global_module_key, false));
    if (!in_global_module)
        b.model_name(im.name().location());

    const auto simple_name_value(pt.get<std::string>(simple_name_key));
    b.simple_name(simple_name_value);

    const auto i(pt.find(internal_modules_key));
    if (i != pt.not_found()) {
        std::list<std::string> ipp;
        for (auto& item : pt.get_child(internal_modules_key))
            ipp.push_back(item.second.get_value<std::string>());

        if (!ipp.empty())
            b.internal_modules(ipp);
        else {
            BOOST_LOG_SEV(lg, debug) << "Ignoring empty internal module path. "
                                     << "Type: " << simple_name_value;
        }
    }

    yarn::name n(b.build());
    const auto documentation(pt.get_optional<std::string>(documentation_key));

    const auto lambda([&](yarn::element& e) {
            BOOST_LOG_SEV(lg, debug) << "Processing element: " << n.id();
            e.name(n);
            e.origin_type(origin_types::not_yet_determined);
            e.generation_type(im.generation_type());
            e.in_global_module(in_global_module);

            if (documentation)
                e.documentation(*documentation);

            const auto kvps(read_kvps(pt));
            insert_scribbles(e.name(), kvps, im);
        });

    const auto meta_type_value(pt.get<std::string>(meta_type_key));
    if (meta_type_value == meta_type_object_value) {
        yarn::object o;
        lambda(o);

        const auto ot(pt.get_optional<std::string>(object_type_key));
        o.object_type(to_object_type(ot));
        const auto pair(std::make_pair(n.id(), o));
        const bool inserted(im.objects().insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element_id << n.id();
            BOOST_THROW_EXCEPTION(
                hydration_error(duplicate_element_id + n.id()));
        }
    } else if (meta_type_value == meta_type_primitive_value) {
        yarn::primitive p;
        const auto dit(pt.get(is_default_enumeration_type_key, false));
        p.is_default_enumeration_type(dit);
        lambda(p);
        const auto pair(std::make_pair(n.id(), p));
        const bool inserted(im.primitives().insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element_id << n.id();
            BOOST_THROW_EXCEPTION(
                hydration_error(duplicate_element_id + n.id()));
        }
    }
    else {
        BOOST_LOG_SEV(lg, error) << invalid_meta_type << meta_type_value;
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_meta_type + meta_type_value));
    }
}

yarn::intermediate_model hydrator::
read_stream(std::istream& s, const bool is_target) const {
    yarn::intermediate_model r;
    r.generation_type(generation_type(is_target));

    boost::property_tree::ptree pt;
    read_json(s, pt);

    yarn::name_factory nf;
    const auto model_name_value(pt.get<std::string>(model_name_key));
    r.name(nf.build_model_name(model_name_value));
    BOOST_LOG_SEV(lg, debug) << "Processing model: " << r.name().id();

    const auto tg(origin_types::target);
    const auto nyd(origin_types::not_yet_determined);
    const auto ot(is_target ? tg : nyd);
    r.origin_type(ot);

    yarn::module m;
    const auto kvps(read_kvps(pt));
    insert_scribbles(r.name(), kvps, r);

    const auto documentation(pt.get_optional<std::string>(documentation_key));
    if (documentation)
        m.documentation(*documentation);

    m.name(r.name());
    m.origin_type(origin_types::not_yet_determined);
    m.generation_type(r.generation_type());
    r.modules().insert(std::make_pair(m.name().id(), m));

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
    else if (ot == object_type_associative_container_value)
        return yarn::object_types::associative_container;
    else if (ot == object_type_sequence_container_value)
        return yarn::object_types::sequence_container;

    BOOST_LOG_SEV(lg, error) << invalid_object_type << ot;
    BOOST_THROW_EXCEPTION(hydration_error(invalid_object_type + ot));
}

intermediate_model hydrator::
hydrate(std::istream& s, const bool is_target) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON stream.";
    using namespace boost::property_tree;
    try {
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

intermediate_model hydrator::
hydrate(const boost::filesystem::path& p, const bool is_target) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << gs;
    boost::filesystem::ifstream s(p);

    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << ": " << gs;
        BOOST_THROW_EXCEPTION(hydration_error(failed_to_open_file + gs));
    }

    const auto r(hydrate(s, is_target));
    BOOST_LOG_SEV(lg, debug) << "Parsed JSON file successfully.";
    return r;
}

} } }
