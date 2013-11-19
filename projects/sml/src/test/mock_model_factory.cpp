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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/meta_data_writer.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/test/building_error.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.mock_model_factory"));

const std::string model_name_prefix("some_model_");
const std::string simple_name_prefix("some_type_");
const std::string property_name_prefix("some_property_");
const std::string module_name_prefix("some_module_");
const std::string visitor_postfix("_visitor");
const std::string versioned_postfix("_versioned");
const std::string unversioned_postfix("_unversioned");

const std::string boolean("bool");
const std::string unsigned_int("unsigned int");

const std::string documentation("Some documentation");

const std::string licence_name("gpl_v2");
const std::string modeline_group_name("emacs");
const std::string marker("SAMPLE_MARKER");
const std::string copyright_holders(
    "Copyright (C) 2012 Person <name@company.co.uk>");

const std::string header_extension(".hpp");

const std::string invalid_property_type("Unknown property type.");
const std::string invalid_object_type("Invalid or unsupported object type.");

std::string simple_name(unsigned int i) {
    std::ostringstream stream;
    stream << simple_name_prefix << i;
    return stream.str();
}

std::string model_name(unsigned int i) {
    std::ostringstream stream;
    stream << model_name_prefix << i;
    return stream.str();
}

std::string property_name(unsigned int i) {
    std::ostringstream stream;
    stream << property_name_prefix << i;
    return stream.str();
}

std::string module_name(unsigned int i) {
    std::ostringstream stream;
    stream << module_name_prefix << i;
    return stream.str();
}

dogen::sml::nested_qname mock_nested_qname(const dogen::sml::qname& qn) {
    dogen::sml::qname pqn;
    pqn.simple_name(qn.simple_name());
    pqn.model_name(qn.model_name());

    dogen::sml::nested_qname r;
    r.type(pqn);
    return r;
}

dogen::sml::qname mock_model_qname(unsigned int i) {
    dogen::sml::qname r;
    r.model_name(model_name(i));
    return r;
}

dogen::sml::nested_qname
mock_nested_qname_shared_ptr(const dogen::sml::qname& qn) {
    dogen::sml::qname e;
    e.simple_name("shared_ptr");
    e.model_name("boost");

    dogen::sml::nested_qname r;
    r.type(e);

    dogen::sml::nested_qname c;
    c.type(qn);

    r.children(std::list<dogen::sml::nested_qname> { c });

    return r;
}

dogen::sml::nested_qname mock_nested_qname(
    dogen::sml::test::mock_model_factory::property_types pt) {
    using namespace dogen::sml;

    qname qn;
    nested_qname r;

    typedef test::mock_model_factory::property_types property_types;
    switch(pt) {
    case property_types::unsigned_int:
        qn.simple_name(unsigned_int);
        r.type(qn);
        break;
    case property_types::boolean:
        qn.simple_name(boolean);
        r.type(qn);
        break;
    case property_types::boost_variant: {
        qname e;
        e.simple_name("variant");
        e.model_name("boost");
        r.type(e);

        qname f;
        f.simple_name(boolean);
        nested_qname c;
        c.type(f);

        qname g;
        g.simple_name(unsigned_int);
        nested_qname d;
        d.type(g);
        r.children(std::list<nested_qname> { c, d });
        break;
    }
    case property_types::std_string:
        qn.simple_name("string");
        qn.model_name("std");
        r.type(qn);
        break;
    case property_types::std_pair: {
        qname e;
        e.simple_name("pair");
        e.model_name("std");
        r.type(e);

        qname f;
        f.simple_name(boolean);
        nested_qname c;
        c.type(f);

        qname g;
        g.simple_name(boolean);
        nested_qname d;
        d.type(g);
        r.children(std::list<nested_qname> { c, d });
        break;
    }
    default:
        BOOST_LOG_SEV(lg, error) << invalid_property_type;
        BOOST_THROW_EXCEPTION(test::building_error(invalid_property_type));
    }
    return r;
}

void populate_object(dogen::sml::abstract_object& o, const unsigned int i,
    const dogen::sml::qname& model_qname, const unsigned int module_n) {

    dogen::sml::qname qn;
    qn.model_name(model_qname.model_name());
    qn.simple_name(simple_name(i));

    for (unsigned int i(0); i < module_n; ++i)
        qn.module_path().push_back(module_name(i));

    o.name(qn);
    o.generation_type(dogen::sml::generation_types::full_generation);
    o.documentation(documentation);
    o.origin_type(dogen::sml::origin_types::user);
}

void populate_simple_model_properties(dogen::sml::model& m, const unsigned int n) {
    m.name(mock_model_qname(n));
    m.documentation(documentation);
    m.origin_type(dogen::sml::origin_types::user);
    m.generation_type(dogen::sml::generation_types::full_generation);
}

dogen::sml::property mock_property(const unsigned int n = 0,
    const dogen::sml::test::mock_model_factory::property_types pt =
    dogen::sml::test::mock_model_factory::property_types::unsigned_int,
    boost::optional<dogen::sml::qname> qn =
    boost::optional<dogen::sml::qname>()) {
    dogen::sml::property r;
    r.name(property_name(n));

    using property_types = dogen::sml::test::mock_model_factory::property_types;
    if (pt == property_types::value_object)
        r.type(mock_nested_qname(*qn));
    else if (pt == property_types::boost_shared_ptr)
        r.type(mock_nested_qname_shared_ptr(*qn));
    else
        r.type(mock_nested_qname(pt));

    return r;
}

template<typename Stateful>
void add_property(Stateful& s, const bool indexed, const unsigned int n = 0,
    const dogen::sml::test::mock_model_factory::property_types pt =
    dogen::sml::test::mock_model_factory::property_types::unsigned_int,
    boost::optional<dogen::sml::qname> qn =
    boost::optional<dogen::sml::qname>()) {

    auto p(mock_property(n, pt, qn));
    s.local_properties().push_back(p);

    if (indexed)
        s.all_properties().push_back(p);
}

template<typename Nameable>
void add_relationship(dogen::sml::abstract_object& target,
    const Nameable& relative,
    const dogen::sml::relationship_types rt) {
    using dogen::sml::relationship_types;
    target.relationships()[rt].push_back(relative.name());
}

const bool add_leaf(true);

void parent_to_child(dogen::sml::abstract_object& parent,
    dogen::sml::abstract_object& child,
    dogen::sml::abstract_object& original_parent,
    const bool add_leaf_relationship = true) {
    using dogen::sml::relationship_types;
    add_relationship(child, parent, relationship_types::parents);
    add_relationship(child, original_parent,
        relationship_types::original_parents);

    original_parent.is_inheritance_root(true);
    if (add_leaf_relationship)
        add_relationship(parent, child, relationship_types::leaves);

    parent.is_parent(true);
    child.is_child(true);
}

void parent_to_child(dogen::sml::abstract_object& parent,
    dogen::sml::abstract_object& child,
    const bool add_leaf_relationship = true) {
    parent_to_child(parent, child, parent, add_leaf_relationship);
}

template<typename Nameable>
void insert_nameable(std::unordered_map<dogen::sml::qname, Nameable>& map,
    const Nameable& n) {
    map.insert(std::make_pair(n.name(), n));
}

void insert_object(dogen::sml::model& m,
    boost::shared_ptr<dogen::sml::abstract_object> o) {
    m.objects().insert(std::make_pair(o->name(), o));
}

std::string filename_for_qname(const dogen::sml::qname& qn) {
    boost::filesystem::path r;
    for (const auto& p : qn.external_module_path())
        r /= p;

    r /= qn.model_name();

    if (qn.simple_name().empty())
        r /= qn.model_name();
    else
        r /= qn.simple_name();

    r.replace_extension(header_extension);
    return r.generic_string();
}

template<typename Taggable>
void add_test_tags(Taggable& t) {
    dogen::sml::meta_data_writer writer(t.meta_data());
    writer.add(dogen::sml::tags::cpp::types::header_file::file_name,
        filename_for_qname(t.name()));
    writer.add(dogen::sml::tags::licence_name, licence_name);
    writer.add(dogen::sml::tags::copyright_holder, copyright_holders);
    writer.add(dogen::sml::tags::modeline_group_name, modeline_group_name);
    writer.add(dogen::sml::tags::code_generation_marker, marker);
    writer.add(dogen::sml::tags::generate_preamble,
        dogen::sml::tags::bool_true);
}

}

namespace dogen {
namespace sml {
namespace test {

mock_model_factory::mock_model_factory(const bool tagged, const bool indexed)
    : tagged_(tagged), indexed_(indexed) { }

std::string mock_model_factory::model_name(const unsigned int n) const {
    return ::model_name(n);
}

std::string mock_model_factory::simple_name(const unsigned int n) const {
    return ::simple_name(n);
}

std::string mock_model_factory::module_name(const unsigned int n) const {
    return ::module_name(n);
}

std::string mock_model_factory::property_name(const unsigned int n) const {
    return ::property_name(n);
}

bool mock_model_factory::
is_model_n(const unsigned int n, const dogen::sml::qname& qn) const {
    return is_model_n(n, qn.model_name());
}

bool mock_model_factory::
is_model_n(const unsigned int n, const std::string& s) const {
    return model_name(n) == s;
}

bool mock_model_factory::
is_simple_name_n(const unsigned int n, const dogen::sml::qname& qn) const {
    return is_simple_name_n(n, qn.simple_name());
}

bool mock_model_factory::
is_simple_name_n(const unsigned int n, const std::string& s) const {
    return simple_name(n) == s;
}

bool mock_model_factory::
is_module_n(const unsigned int n, const std::string& s) const {
    return module_name(n) == s;
}

bool mock_model_factory::is_simple_name_n_unversioned(const unsigned int n,
    const dogen::sml::qname& qn) const {
    return
        boost::contains(qn.simple_name(), simple_name(n)) &&
        boost::contains(qn.simple_name(), unversioned_postfix);
}

bool mock_model_factory::is_simple_name_n_versioned(const unsigned int n,
    const dogen::sml::qname& qn) const {
    return
        boost::contains(qn.simple_name(), simple_name(n)) &&
        boost::contains(qn.simple_name(), versioned_postfix);
}

bool mock_model_factory::is_simple_name_n_visitor(const unsigned int n,
    const dogen::sml::qname& qn) const {
    return
        boost::contains(qn.simple_name(), simple_name(n)) &&
        boost::contains(qn.simple_name(), visitor_postfix);
}

bool mock_model_factory::is_file_for_qname(const boost::filesystem::path& p,
    const dogen::sml::qname& qn) const {
    std::string fn;

    if (qn.simple_name().empty())
        fn = qn.model_name();
    else
        fn = qn.simple_name();

    fn += header_extension;
    return boost::algorithm::ends_with(p.generic_string(), fn);
}

boost::shared_ptr<dogen::sml::abstract_object> mock_model_factory::
build_value_object(const unsigned int i, const dogen::sml::qname& model_qname,
    const unsigned int module_n) const {

    using dogen::sml::value_object;
    auto r(boost::make_shared<value_object>());
    populate_object(*r, i, model_qname, module_n);
    r->type(dogen::sml::value_object_types::plain);

    if (tagged_)
        add_test_tags(*r);

    return r;
}

boost::shared_ptr<dogen::sml::abstract_object> mock_model_factory::
build_value_object(unsigned int i, const unsigned int module_n) const {
    return build_value_object(i, mock_model_qname(i), module_n);
}

dogen::sml::concept mock_model_factory::build_concept(
    const unsigned int i, const dogen::sml::qname& model_qname) const {

    dogen::sml::concept r;

    dogen::sml::qname qn;
    qn.model_name(model_qname.model_name());
    qn.simple_name(simple_name(i));

    r.name(qn);
    r.documentation(documentation);
    r.origin_type(dogen::sml::origin_types::user);

    if (tagged_)
        add_test_tags(r);

    return r;
}

boost::shared_ptr<dogen::sml::abstract_object> mock_model_factory::
build_entity(const dogen::sml::property& prop, const bool keyed,
    const unsigned int i, const dogen::sml::qname& model_qname,
    const unsigned int module_n) const {

    using namespace dogen::sml;
    boost::shared_ptr<abstract_entity> r;
    if (keyed)
        r = boost::shared_ptr<abstract_entity>(new keyed_entity());
    else
        r = boost::shared_ptr<abstract_entity>(new entity());

    populate_object(*r, i, model_qname, module_n);
    r->identity().push_back(prop);

    if (tagged_)
        add_test_tags(*r);

    return r;
}

dogen::sml::enumeration mock_model_factory::
build_enumeration(const unsigned int i, const dogen::sml::qname& model_qname,
    const unsigned int module_n) const {
    dogen::sml::qname qn;
    qn.model_name(model_qname.model_name());
    qn.simple_name(simple_name(i));

    for (unsigned int i(0); i < module_n; ++i)
        qn.module_path().push_back(module_name(i));

    dogen::sml::enumeration r;
    r.name(qn);
    r.generation_type(dogen::sml::generation_types::full_generation);
    r.documentation(documentation);

    dogen::sml::qname uqn;
    uqn.simple_name(unsigned_int);
    r.underlying_type(uqn);

    const auto lambda([&](const unsigned int n) -> dogen::sml::enumerator {
            dogen::sml::enumerator r;
            r.name(simple_name(n));
            r.value(boost::lexical_cast<std::string>(n));
            return r;
        });

    r.enumerators().push_back(lambda(0));
    r.enumerators().push_back(lambda(1));

    if (tagged_)
        add_test_tags(r);

    return r;
}

boost::shared_ptr<dogen::sml::abstract_object> mock_model_factory::
build_exception(const unsigned int i, const dogen::sml::qname& model_qname,
    const unsigned int module_n) const {
    dogen::sml::qname qn;
    qn.model_name(model_qname.model_name());
    qn.simple_name(simple_name(i));

    for (unsigned int i(0); i < module_n; ++i)
        qn.module_path().push_back(module_name(i));

    using dogen::sml::value_object;
    boost::shared_ptr<value_object> r(new value_object());
    r->name(qn);
    r->generation_type(dogen::sml::generation_types::full_generation);
    r->documentation(documentation);
    r->type(dogen::sml::value_object_types::exception);

    if (tagged_)
        add_test_tags(*r);

    return r;
}

qname mock_model_factory::build_qname(const unsigned int model_n,
    const unsigned int simple_n) const {

    dogen::sml::qname r;
    r.model_name(model_name(model_n));
    r.simple_name(simple_name(simple_n));
    return r;
}

model mock_model_factory::build_empty_model(const unsigned int n) const {
    model r;
    populate_simple_model_properties(r, n);

    if (tagged_)
        add_test_tags(r);

    return r;
}

model mock_model_factory::
build_single_type_model(const unsigned int n, const object_types ot) const {
    return build_multi_type_model(n, 1, ot);
}

model mock_model_factory::
build_single_type_model_in_module(const unsigned int n, const object_types ot,
    const unsigned int mod_n) const {
    return build_multi_type_model(n, 1, ot, mod_n);
}

model mock_model_factory::
build_multi_type_model(const unsigned int n, const unsigned int type_n,
    const object_types ot, const unsigned int mod_n) const {

    model r(build_empty_model(n));

    std::list<std::string> pp;
    for (unsigned int i(0); i < mod_n; ++i) {
        qname qn;
        qn.model_name(r.name().model_name());
        qn.simple_name(module_name(i));
        qn.module_path(pp);

        module p;
        p.name(qn);
        p.documentation(documentation);
        insert_nameable(r.modules(), p);

        pp.push_back(module_name(i));
    }

    switch (ot) {
    case object_types::value_object:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto o(build_value_object(i, r.name(), mod_n));
            insert_object(r, o);
        }
        break;
    case object_types::enumeration:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(build_enumeration(i, r.name(), mod_n));
            insert_nameable(r.enumerations(), e);
        }
        break;
    case object_types::exception:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(build_exception(i, r.name(), mod_n));
            insert_object(r, e);
        }
        break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(building_error(invalid_object_type));
    }

    return r;
}

model mock_model_factory::
build_single_concept_model(const unsigned int n) const {
    model r(build_empty_model(n));
    concept c(build_concept(0, r.name()));
    add_property(c, indexed_);
    insert_nameable(r.concepts(), c);

    auto o(build_value_object(0, r.name()));
    add_property(*o, indexed_, 1);
    o->modeled_concepts().push_back(c.name());
    using dogen::sml::relationship_types;
    add_relationship(*o, c, relationship_types::modeled_concepts);
    insert_object(r, o);

    return r;
}

model mock_model_factory::
build_first_degree_concepts_model(const unsigned int n) const {
    model r(build_empty_model(n));
    concept c0(build_concept(0, r.name()));
    add_property(c0, indexed_);
    insert_nameable(r.concepts(), c0);

    concept c1(build_concept(1, r.name()));
    add_property(c1, indexed_, 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    using dogen::sml::relationship_types;
    const auto mc(relationship_types::modeled_concepts);

    auto o0(build_value_object(0, r.name()));
    o0->modeled_concepts().push_back(c0.name());
    add_relationship(*o0, c0, mc);
    insert_object(r, o0);

    auto o1(build_value_object(0, r.name()));
    add_property(*o1, indexed_, 2);
    o1->modeled_concepts().push_back(c1.name());
    add_relationship(*o1, c1, mc);
    insert_object(r, o1);

    return r;
}

model mock_model_factory::
build_second_degree_concepts_model(const unsigned int n) const {
    model r(build_empty_model(n));
    concept c0(build_concept(0, r.name()));
    add_property(c0, indexed_);
    insert_nameable(r.concepts(), c0);

    concept c1(build_concept(1, r.name()));
    add_property(c1, indexed_, 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    concept c2(build_concept(1, r.name()));
    add_property(c2, indexed_, 2);
    c2.refines().push_back(c1.name());
    insert_nameable(r.concepts(), c2);

    using dogen::sml::relationship_types;
    const auto mc(relationship_types::modeled_concepts);

    auto o0(build_value_object(0, r.name()));
    o0->modeled_concepts().push_back(c1.name());
    add_relationship(*o0, c1, mc);
    insert_object(r, o0);

    auto o1(build_value_object(1, r.name()));
    o1->modeled_concepts().push_back(c0.name());
    add_relationship(*o1, c0, mc);
    insert_object(r, o1);

    auto o2(build_value_object(2, r.name()));
    o2->modeled_concepts().push_back(c2.name());
    add_property(*o2, indexed_, 3);
    add_relationship(*o2, c2, mc);
    insert_object(r, o2);

    return r;
}

model mock_model_factory::build_multiple_inheritance_concepts_model(
    const unsigned int n) const {
    model r(build_empty_model(n));
    concept c0(build_concept(0, r.name()));
    add_property(c0, indexed_);
    add_property(c0, indexed_);
    insert_nameable(r.concepts(), c0);

    concept c1(build_concept(1, r.name()));
    add_property(c1, 1);
    insert_nameable(r.concepts(), c1);

    concept c2(build_concept(1, r.name()));
    add_property(c2, 2);
    c2.refines().push_back(c0.name());
    c2.refines().push_back(c1.name());
    insert_nameable(r.concepts(), c2);

    using dogen::sml::relationship_types;
    const auto mc(relationship_types::modeled_concepts);

    auto o0(build_value_object(0, r.name()));
    o0->modeled_concepts().push_back(c2.name());
    add_relationship(*o0, c2, mc);
    insert_object(r, o0);
    return r;
}

model mock_model_factory::
build_diamond_inheritance_concepts_model(const unsigned int n) const {
    model r(build_empty_model(n));
    concept c0(build_concept(0, r.name()));
    add_property(c0, indexed_);
    insert_nameable(r.concepts(), c0);

    concept c1(build_concept(1, r.name()));
    add_property(c1, 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    concept c2(build_concept(1, r.name()));
    add_property(c2, 2);
    c2.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c2);

    concept c3(build_concept(1, r.name()));
    add_property(c3, 3);
    c3.refines().push_back(c1.name());
    c3.refines().push_back(c2.name());
    insert_nameable(r.concepts(), c3);

    using dogen::sml::relationship_types;
    const auto mc(relationship_types::modeled_concepts);

    auto o0(build_value_object(0, r.name()));
    o0->modeled_concepts().push_back(c3.name());
    add_relationship(*o0, c3, mc);
    insert_object(r, o0);
    return r;
}

model mock_model_factory::
object_with_property(const object_types ot, const property_types pt) const {
    using namespace dogen::sml;

    const auto mn(mock_model_qname(0));
    auto o1(build_value_object(1, mn));

    property p(mock_property(0, pt, o1->name()));

    boost::shared_ptr<abstract_object> o0;
    if (ot == object_types::value_object)
        o0 = build_value_object(0, mn);
    else if (ot == object_types::keyed_entity || ot == object_types::entity)
        o0 = build_entity(p, ot == object_types::keyed_entity, 0, mn);
    else {
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(building_error(invalid_object_type));
    }

    o0->local_properties().push_back(p);
    if (indexed_)
        o0->all_properties().push_back(p);

    model r(build_empty_model(0));
    insert_object(r, o0);
    if (pt == property_types::value_object ||
        pt == property_types::boost_shared_ptr)
        insert_object(r, o1);

    if (pt == property_types::unsigned_int ||
        pt == property_types::boolean) {
        sml::primitive ui;
        ui.name(p.type().type());
        insert_nameable(r.primitives(), ui);
    } else if (pt == property_types::boost_shared_ptr) {
        dogen::sml::qname qn;
        qn.simple_name("shared_ptr");
        qn.model_name("boost");

        boost::shared_ptr<value_object> o2(new value_object());
        o2->name(qn);
        o2->type(dogen::sml::value_object_types::smart_pointer);
        insert_object(r, o2);
    } else if (pt == property_types::std_pair) {

        sml::primitive b;
        b.name().simple_name(boolean);
        r.primitives().insert(std::make_pair(b.name(), b));

        dogen::sml::qname qn;
        qn.simple_name("pair");
        qn.model_name("std");

        boost::shared_ptr<value_object> o2(new value_object());
        o2->name(qn);
        o2->type(sml::value_object_types::plain);
        insert_object(r, o2);
    } else if (pt == property_types::boost_variant) {
        sml::primitive b;
        b.name().simple_name(boolean);
        r.primitives().insert(std::make_pair(b.name(), b));

        sml::primitive ui;
        ui.name().simple_name(unsigned_int);
        r.primitives().insert(std::make_pair(ui.name(), ui));

        dogen::sml::qname qn;
        qn.simple_name("variant");
        qn.model_name("boost");

        boost::shared_ptr<value_object> o2(new value_object());
        o2->name(qn);
        o2->type(sml::value_object_types::plain);
        insert_object(r, o2);
    } else if (pt == property_types::std_string) {
        dogen::sml::qname qn;
        qn.simple_name("string");
        qn.model_name("std");

        boost::shared_ptr<value_object> o2(new value_object());
        o2->name(qn);
        o2->type(sml::value_object_types::plain);
        insert_object(r, o2);
    }

    return r;
}

std::array<model, 2>
mock_model_factory::object_with_property_type_in_different_model() const {
    auto o0(build_value_object(0));
    auto o1(build_value_object(1));

    using property_types = dogen::sml::test::mock_model_factory::property_types;
    add_property(*o0, indexed_, 0, property_types::value_object, o1->name());

    qname m0_qn;
    m0_qn.model_name(model_name(0));

    model m0;
    m0.name(m0_qn);
    insert_object(m0, o0);

    qname m1_qn;
    m1_qn.model_name(model_name(1));

    model m1;
    m1.name(m1_qn);
    insert_object(m1, o1);

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::object_with_missing_property_type() const {
    auto o0(build_value_object(0));
    auto o1(build_value_object(1));

    using property_types = dogen::sml::test::mock_model_factory::property_types;
    add_property(*o0, indexed_, 0, property_types::value_object, o1->name());

    qname mn_qn;
    mn_qn.model_name(model_name(0));

    model r(build_empty_model(0));
    insert_object(r, o0);

    return r;
}

model mock_model_factory::
object_with_parent_in_the_same_model(const bool has_property) const {
    const auto mn(mock_model_qname(0));

    model r(build_empty_model(0));
    auto o0(build_value_object(0, mn));
    using property_types = dogen::sml::test::mock_model_factory::property_types;
    if (has_property) {
        add_property(*o0, indexed_);
        sml::primitive ui;
        ui.name().simple_name(unsigned_int);
        r.primitives().insert(std::make_pair(ui.name(), ui));
    }

    auto o1(build_value_object(1, mn));
    if (has_property)
        add_property(*o1, 1);

    parent_to_child(*o1, *o0);
    insert_object(r, o0);
    insert_object(r, o1);

    o0->parent_name(o1->name());
    o0->original_parent_name(o1->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());
    return r;
}

model mock_model_factory::object_with_missing_child_in_the_same_model() const {
    const auto mn(mock_model_qname(0));
    auto o0(build_value_object(0, mn));
    auto o1(build_value_object(1, mn));
    o0->parent_name(o1->name());
    o0->original_parent_name(o1->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());
    parent_to_child(*o1, *o0);
    model r(build_empty_model(0));
    insert_object(r, o1);

    return r;
}

std::array<model, 2> mock_model_factory::
object_with_parent_in_different_models() const {
    auto o0(build_value_object(0));
    auto o1(build_value_object(1));
    parent_to_child(*o1, *o0);

    o0->original_parent_name(o1->name());
    o0->parent_name(o1->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    model m0(build_empty_model(0));
    insert_object(m0, o0);

    model m1(build_empty_model(1));
    insert_object(m1, o1);
    m1.name(mock_model_qname(1));
    m1.origin_type(origin_types::user);

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::object_with_three_children_in_same_model() const {
    const auto mn(mock_model_qname(0));
    auto o0(build_value_object(0, mn));
    auto o1(build_value_object(1, mn));
    auto o2(build_value_object(2, mn));
    auto o3(build_value_object(3, mn));

    parent_to_child(*o3, *o0);
    parent_to_child(*o3, *o1);
    parent_to_child(*o3, *o2);

    o0->parent_name(o3->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o3->name());
    o1->original_parent_name(o3->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());

    o3->is_parent(true);
    o3->leaves().push_back(o0->name());
    o3->leaves().push_back(o1->name());
    o3->leaves().push_back(o2->name());

    model r(build_empty_model(0));
    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    insert_object(r, o3);
    r.name(mn);
    return r;
}

model mock_model_factory::
object_with_third_degree_parent_in_same_model(const bool has_property) const {
    const auto mn(mock_model_qname(0));

    model r(build_empty_model(0));

    auto o0(build_value_object(0, mn));
    if (has_property) {
        add_property(*o0, indexed_);

        sml::primitive ui;
        ui.name().simple_name(unsigned_int);
        r.primitives().insert(std::make_pair(ui.name(), ui));
    }

    auto o1(build_value_object(1, mn));
    if (has_property)
        add_property(*o1, indexed_, 1);

    auto o2(build_value_object(2, mn));
    if (has_property)
        add_property(*o2, indexed_, 1);

    auto o3(build_value_object(3, mn));
    if (has_property)
        add_property(*o3, indexed_, 3);

    parent_to_child(*o1, *o0, *o3, !add_leaf);
    parent_to_child(*o2, *o1, *o3, !add_leaf);
    parent_to_child(*o3, *o2, *o3, !add_leaf);
    add_relationship(*o3, *o0, relationship_types::leaves);

    o0->parent_name(o1->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o2->name());
    o1->original_parent_name(o3->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());
    o2->is_parent(true);
    o2->leaves().push_back(o0->name());

    o3->leaves().push_back(o0->name());
    o3->is_parent(true);

    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    insert_object(r, o3);

    return r;
}

model mock_model_factory::object_with_third_degree_parent_missing() const {
    const auto mn(mock_model_qname(0));
    auto o0(build_value_object(0, mn));
    auto o1(build_value_object(1, mn));
    auto o2(build_value_object(2, mn));
    auto o3(build_value_object(3, mn));

    parent_to_child(*o1, *o0, *o3, !add_leaf);
    parent_to_child(*o2, *o1, *o3, !add_leaf);
    parent_to_child(*o3, *o2, *o3, !add_leaf);
    add_relationship(*o3, *o0, relationship_types::leaves);

    o0->parent_name(o1->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o2->name());
    o1->original_parent_name(o3->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());
    o2->is_parent(true);
    o2->leaves().push_back(o0->name());

    o3->is_parent(true);
    o3->leaves().push_back(o0->name());

    model r(build_empty_model(0));
    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    r.name(mn);
    return r;
}

std::array<model, 4> mock_model_factory::
object_with_third_degree_parent_in_different_models() const {
    auto o0(build_value_object(0));
    auto o1(build_value_object(1));
    auto o2(build_value_object(2));
    auto o3(build_value_object(3));

    parent_to_child(*o1, *o0, *o3, !add_leaf);
    parent_to_child(*o2, *o1, *o3, !add_leaf);
    parent_to_child(*o3, *o2, *o3, !add_leaf);
    add_relationship(*o3, *o0, relationship_types::leaves);

    o0->parent_name(o1->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o2->name());
    o1->original_parent_name(o3->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());
    o2->is_parent(true);
    o2->leaves().push_back(o0->name());

    o3->is_parent(true);
    o3->leaves().push_back(o0->name());

    model m0(build_empty_model(0));
    insert_object(m0, o0);

    model m1(build_empty_model(1));
    insert_object(m1, o1);

    model m2(build_empty_model(2));
    insert_object(m2, o2);

    model m3(build_empty_model(3));
    insert_object(m3, o3);

    return std::array<model, 4>{{ m0, m1, m2, m3 }};
}

std::array<model, 4> mock_model_factory::
object_with_missing_third_degree_parent_in_different_models() const {
    auto o0(build_value_object(0));
    auto o1(build_value_object(1));
    auto o2(build_value_object(2));
    auto o3(build_value_object(3));

    parent_to_child(*o1, *o0, *o3, !add_leaf);
    parent_to_child(*o2, *o1, *o3, !add_leaf);
    parent_to_child(*o3, *o2, *o3, !add_leaf);
    add_relationship(*o3, *o0, relationship_types::leaves);

    o0->parent_name(o1->name());
    o0->original_parent_name(o3->name());

    o1->parent_name(o2->name());
    o1->original_parent_name(o3->name());
    o1->is_parent(true);
    o1->leaves().push_back(o0->name());

    o2->parent_name(o3->name());
    o2->original_parent_name(o3->name());
    o2->is_parent(true);
    o2->leaves().push_back(o0->name());

    o3->is_parent(true);
    o3->leaves().push_back(o0->name());

    model m0(build_empty_model(0));
    insert_object(m0, o0);

    model m1(build_empty_model(1));
    insert_object(m1, o1);

    model m2(build_empty_model(2));
    insert_object(m2, o2);

    return std::array<model, 4>{{ m0, m1, m2 }};
}

} } }
