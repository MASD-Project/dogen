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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/scribble_group.hpp"
#include "dogen/yarn/io/meta_model/name_io.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn.json/types/hydration_error.hpp"
#include "dogen/yarn.json/types/hydrator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.json.hydrator"));

const std::string empty;
const std::string is_default_enumeration_type_key(
    "is_default_enumeration_type");
const std::string is_floating_point_key("is_floating_point");
const std::string in_global_module_key("in_global_module");
const std::string name_key("name");
const std::string parents_key("parents");
const std::string refines_key("refines");
const std::string model_name_key("model_name");
const std::string bool_true("true");
const std::string bool_false("false");

const std::string documentation_key("documentation");
const std::string root_module_key("root_module");
const std::string elements_key("elements");
const std::string attributes_key("attributes");
const std::string enumerators_key("enumerators");
const std::string stereotypes_key("stereotypes");

const std::string meta_type_key("meta_type");
const std::string meta_type_object_value("object");
const std::string meta_type_builtin_value("builtin");
const std::string meta_type_module_value("module");
const std::string meta_type_enumeration_value("enumeration");
const std::string meta_type_primitive_value("primitive");
const std::string meta_type_exception_value("exception");
const std::string meta_type_concept_value("concept");

const std::string can_be_enumeration_underlier_key(
    "can_be_enumeration_underlier");
const std::string can_be_primitive_underlier_key(
    "can_be_primitive_underlier");

const std::string unparsed_type_key("unparsed_type");
const std::string simple_key("simple");
const std::string external_modules_key("external_modules");
const std::string internal_modules_key("internal_modules");
const std::string annotations_key("annotation");

const std::string object_type_key("object_type");
const std::string object_type_smart_pointer_value("smart_pointer");
const std::string object_type_associative_container_value(
    "associative_container");
const std::string object_type_sequence_container_value("sequence_container");

const std::string invalid_json_file("Failed to parse JSON file: ");
const std::string invalid_value_in_json("Failed to value in JSON: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string invalid_meta_type("Invalid value for meta type: ");
const std::string missing_module("Could not find module: ");
const std::string failed_to_open_file("Failed to open file: ");
const std::string invalid_object_type("Invalid or unsupported object type: ");
const std::string duplicate_element_id("Duplicate element id: ");
const std::string missing_name("JSON element name is mandatory.");
const std::string missing_root_module("Root module not found.");

}

namespace dogen {
namespace yarn {
namespace json {

meta_model::object_types hydrator::
to_object_type(const boost::optional<std::string>& s) const {
    if (!s)
        return meta_model::object_types::invalid;

    const auto ot(*s);
    if (ot == object_type_smart_pointer_value)
        return meta_model::object_types::smart_pointer;
    else if (ot == object_type_associative_container_value)
        return meta_model::object_types::associative_container;
    else if (ot == object_type_sequence_container_value)
        return meta_model::object_types::sequence_container;

    BOOST_LOG_SEV(lg, error) << invalid_object_type << ot;
    BOOST_THROW_EXCEPTION(hydration_error(invalid_object_type + ot));
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

annotations::scribble_group
hydrator::read_scribble_group(const boost::property_tree::ptree& pt,
    const annotations::scope_types st) const {

    annotations::scribble_group r;
    const auto kvps(read_kvps(pt));
    if (kvps.empty())
        return r;

    annotations::scribble sbl;
    sbl.entries(kvps);
    sbl.scope(st);
    r.parent(sbl);

    return r;
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::module>>
hydrator::read_root_module(const boost::property_tree::ptree& pt) const {
    auto rm(boost::make_shared<meta_model::module>());
    rm->documentation(read_documentation(pt));
    rm->is_root(true);

    const auto st(annotations::scope_types::root_module);
    const auto sg(read_scribble_group(pt, st));
    return std::make_pair(sg, rm);
}

void hydrator::read_and_insert_scribble(const meta_model::name& owner,
    const annotations::scope_types st, const boost::property_tree::ptree& pt,
    annotations::scribble_group& sg) const {

    const auto kvps(read_kvps(pt));
    if (kvps.empty())
        return;

    annotations::scribble sbl;
    sbl.entries(kvps);
    sbl.scope(st);

    const auto sn(owner.simple());
    const auto pair(std::make_pair(sn, sbl));
    const bool inserted(sg.children().insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element_id << sn;
        BOOST_THROW_EXCEPTION(hydration_error(duplicate_element_id + sn));
    }
}

std::vector<std::string> hydrator::
read_stereotypes(const boost::property_tree::ptree& pt) const {
    std::vector<std::string> r;
    const auto i(pt.find(stereotypes_key));
    if (i == pt.not_found() || i->second.empty())
        return r;

    for (auto j(i->second.begin()); j != i->second.end(); ++j)
        r.push_back(j->second.get_value<std::string>());

    return r;
}

meta_model::name
hydrator::read_name(const boost::property_tree::ptree& pt) const {
    yarn::helpers::name_builder b;
    const auto sn(pt.get<std::string>(simple_key));
    b.simple_name(sn);

    const auto im(pt.get<std::string>(internal_modules_key, empty));
    if (!im.empty())
        b.internal_modules(im);

    const auto r(b.build());
    return r;
}

std::list<meta_model::name>
hydrator::read_names(const boost::property_tree::ptree& pt) const {
    std::list<meta_model::name> r;
    for (auto i(pt.begin()); i != pt.end(); ++i) {
        const auto& apt(i->second);
        r.push_back(read_name(apt));
    }
    return r;
}

std::string
hydrator::read_documentation(const boost::property_tree::ptree& pt) const {
    const auto opt(pt.get_optional<std::string>(documentation_key));
    if (!opt)
        return empty;

    auto r(*opt);
    boost::trim(r);
    return r;
}

std::vector<meta_model::enumerator>
hydrator::read_enumerators(const boost::property_tree::ptree& pt,
    annotations::scribble_group& sg) const {

    std::vector<meta_model::enumerator> r;
    for (auto i(pt.begin()); i != pt.end(); ++i) {
        const auto& apt(i->second);
        meta_model::enumerator en;
        const auto j(apt.find(name_key));
        if (j == apt.not_found()) {
            BOOST_LOG_SEV(lg, error) << missing_name;
            BOOST_THROW_EXCEPTION(hydration_error(missing_name));
        }
        en.name(read_name(j->second));
        en.documentation(read_documentation(apt));

        const auto st(annotations::scope_types::property);
        read_and_insert_scribble(en.name(), st, apt, sg);
        r.push_back(en);
    }
    return r;
}

std::list<meta_model::attribute>
hydrator::read_attributes(const boost::property_tree::ptree& pt,
    annotations::scribble_group& sg) const {
    std::list<meta_model::attribute> r;

    for (auto i(pt.begin()); i != pt.end(); ++i) {
        const auto& apt(i->second);
        meta_model::attribute a;

        const auto j(apt.find(name_key));
        if (j == apt.not_found()) {
            BOOST_LOG_SEV(lg, error) << missing_name;
            BOOST_THROW_EXCEPTION(hydration_error(missing_name));
        }
        a.name(read_name(j->second));

        a.unparsed_type(apt.get<std::string>(unparsed_type_key));
        a.documentation(read_documentation(apt));

        const auto st(annotations::scope_types::property);
        read_and_insert_scribble(a.name(), st, apt, sg);
        r.push_back(a);
    }
    return r;
}

void hydrator::populate_element(const boost::property_tree::ptree& pt,
    meta_model::element& e) const {

    const auto in_global_module(pt.get(in_global_module_key, false));
    const auto i(pt.find(name_key));
    if (i == pt.not_found()) {
        BOOST_LOG_SEV(lg, error) << missing_name;
        BOOST_THROW_EXCEPTION(hydration_error(missing_name));
    }

    meta_model::name n(read_name(i->second));
    const auto id(n.id());

    BOOST_LOG_SEV(lg, debug) << "Processing element: " << n.id();
    e.name(n);
    e.in_global_module(in_global_module);
    e.documentation(read_documentation(pt));
    e.stereotypes(read_stereotypes(pt));
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::object>>
hydrator::read_object(const boost::property_tree::ptree& pt) const {

    auto o(boost::make_shared<meta_model::object>());
    populate_element(pt, *o);

    const auto ot(pt.get_optional<std::string>(object_type_key));
    o->object_type(to_object_type(ot));

    const auto cbpu(pt.get(can_be_primitive_underlier_key, false));
    o->can_be_primitive_underlier(cbpu);

    const auto st(annotations::scope_types::entity);
    auto sg(read_scribble_group(pt, st));

    auto i(pt.find(attributes_key));
    if (i != pt.not_found())
        o->local_attributes(read_attributes(i->second, sg));

    i = pt.find(parents_key);
    if (i != pt.not_found())
        o->parents(read_names(i->second));

    return std::make_pair(sg, o);
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::builtin>>
hydrator::read_builtin(const boost::property_tree::ptree& pt) const {

    auto b(boost::make_shared<meta_model::builtin>());
    populate_element(pt, *b);

    const auto dit(pt.get(is_default_enumeration_type_key, false));
    b->is_default_enumeration_type(dit);

    const auto ifp(pt.get(is_floating_point_key, false));
    b->is_floating_point(ifp);

    const auto cbeu(pt.get(can_be_enumeration_underlier_key, false));
    b->can_be_enumeration_underlier(cbeu);

    const auto cbpu(pt.get(can_be_primitive_underlier_key, false));
    b->can_be_primitive_underlier(cbpu);

    const auto st(annotations::scope_types::entity);
    auto sg(read_scribble_group(pt, st));
    return std::make_pair(sg, b);
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::module>>
hydrator::read_module(const boost::property_tree::ptree& pt) const {

    auto m(boost::make_shared<meta_model::module>());
    populate_element(pt, *m);

    const auto st(annotations::scope_types::entity);
    auto sg(read_scribble_group(pt, st));
    return std::make_pair(sg, m);
}

std::pair<annotations::scribble_group,
          boost::shared_ptr<meta_model::enumeration>>
hydrator::read_enumeration(const boost::property_tree::ptree& pt) const {

    auto e(boost::make_shared<meta_model::enumeration>());
    populate_element(pt, *e);

    const auto st(annotations::scope_types::entity);
    auto sg(read_scribble_group(pt, st));

    const auto i(pt.find(enumerators_key));
    if (i != pt.not_found())
        e->enumerators(read_enumerators(i->second, sg));

    return std::make_pair(sg, e);
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::primitive>>
hydrator::read_primitive(const boost::property_tree::ptree& pt) const {

    auto p(boost::make_shared<meta_model::primitive>());
    populate_element(pt, *p);

    const auto st(annotations::scope_types::entity);
    auto sg(read_scribble_group(pt, st));

    return std::make_pair(sg, p);
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::exception>>
hydrator::read_exception(const boost::property_tree::ptree& pt) const {

    auto e(boost::make_shared<meta_model::exception>());
    populate_element(pt, *e);

    const auto st(annotations::scope_types::entity);
    auto sg(read_scribble_group(pt, st));

    return std::make_pair(sg, e);
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::concept>>
hydrator::read_concept(const boost::property_tree::ptree& pt) const {

    auto c(boost::make_shared<meta_model::concept>());
    populate_element(pt, *c);

    const auto st(annotations::scope_types::entity);
    auto sg(read_scribble_group(pt, st));

    auto i(pt.find(attributes_key));
    if (i != pt.not_found())
        c->local_attributes(read_attributes(i->second, sg));

    i = pt.find(refines_key);
    if (i != pt.not_found()) {
        for (auto j(i->second.begin()); j != i->second.end(); ++j)
            c->refines().push_back(read_name(j->second));
    }

    return std::make_pair(sg, c);
}

void hydrator::read_element(const boost::property_tree::ptree& pt,
    meta_model::exogenous_model& em) const {

    const auto s(pt.get<std::string>(meta_type_key));
    if (s == meta_type_object_value)
        em.objects().push_back(read_object(pt));
    else if (s == meta_type_builtin_value)
        em.builtins().push_back(read_builtin(pt));
    else if (s == meta_type_module_value)
        em.modules().push_back(read_module(pt));
    else if (s == meta_type_enumeration_value)
        em.enumerations().push_back(read_enumeration(pt));
    else if (s == meta_type_primitive_value)
        em.primitives().push_back(read_primitive(pt));
    else if (s == meta_type_exception_value)
        em.exceptions().push_back(read_exception(pt));
    else if (s == meta_type_concept_value)
        em.concepts().push_back(read_concept(pt));
    else {
        BOOST_LOG_SEV(lg, error) << invalid_meta_type << s;
        BOOST_THROW_EXCEPTION(hydration_error(invalid_meta_type + s));
    }
}

meta_model::exogenous_model hydrator::read_stream(std::istream& s) const {
    boost::property_tree::ptree pt;
    read_json(s, pt);

    meta_model::exogenous_model r;
    auto i(pt.find(root_module_key));
    if (i == pt.not_found() || i->second.empty()) {
        BOOST_LOG_SEV(lg, error) << missing_root_module;
        BOOST_THROW_EXCEPTION(hydration_error(missing_root_module));
    }
    r.root_module(read_root_module(i->second));

    i = pt.find(elements_key);
    if (i == pt.not_found() || i->second.empty())
        BOOST_LOG_SEV(lg, warn) << "Did not find any elements in model.";
    else {
        for (auto j(i->second.begin()); j != i->second.end(); ++j)
            read_element(j->second, r);
    }

    return r;
}

meta_model::exogenous_model
hydrator::hydrate(std::istream& s) const {
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

meta_model::exogenous_model hydrator::
hydrate(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << gs;
    boost::filesystem::ifstream s(p);

    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << gs;
        BOOST_THROW_EXCEPTION(hydration_error(failed_to_open_file + gs));
    }

    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Parsed JSON file successfully.";
    return r;
}

} } }
