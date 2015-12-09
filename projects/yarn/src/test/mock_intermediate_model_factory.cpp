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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/dynamic/types/value_factory.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/test/building_error.hpp"
#include "dogen/yarn/test/mock_intermediate_model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.mock_intermediate_model_factory"));

const std::string model_name_prefix("some_model_");
const std::string type_name_prefix("some_type_");
const std::string concept_name_prefix("some_concept_");
const std::string property_name_prefix("some_property_");
const std::string module_name_prefix("some_module_");
const std::string visitor_postfix("_visitor");
const std::string versioned_postfix("_versioned");
const std::string unversioned_postfix("_unversioned");

const std::string boolean("bool");
const std::string unsigned_int("unsigned int");

const std::string documentation("Some documentation");

const std::string types_main_header("types_");
const std::string types_forward_declaration("types_fwd_");
const std::string serialization_main_header("serialization_");
const std::string serialization_forward_declaration("serialization_fwd_");

const std::string licence_name_key("licence_name");
const std::string licence_name_value("gpl_v2");
const std::string modeline_group_name_key("modeline_group_name");
const std::string modeline_group_name_value("emacs");
const std::string generate_preamble_key("generate_preamble");
const std::string generate_preamble_value("true");
const std::string code_generation_marker_message_key(
    "code_generation_marker.message");
const std::string code_generation_marker_message_value("sample message");
const std::string copyright_notices_key("copyright_notices");
const std::string copyright_notices_value(
    "Copyright (C) 2012 Person <name@company.co.uk>");

const std::string header_extension(".hpp");

const std::string invalid_property_type("Unknown property type.");
const std::string invalid_object_type("Invalid or unsupported object type.");

std::string concept_name(const unsigned int i) {
    std::ostringstream stream;
    stream << concept_name_prefix << i;
    return stream.str();
}

std::string type_name(const unsigned int i) {
    std::ostringstream stream;
    stream << type_name_prefix << i;
    return stream.str();
}

std::string model_name(const unsigned int i) {
    std::ostringstream stream;
    stream << model_name_prefix << i;
    return stream.str();
}

std::string property_name(const unsigned int i) {
    std::ostringstream stream;
    stream << property_name_prefix << i;
    return stream.str();
}

std::string module_name(const unsigned int i) {
    std::ostringstream stream;
    stream << module_name_prefix << i;
    return stream.str();
}

dogen::yarn::name mock_model_name(unsigned int i) {
    dogen::yarn::name_factory nf;
    return nf.build_model_name(model_name(i));
}

dogen::yarn::nested_name mock_nested_name(const dogen::yarn::name& n) {
    dogen::yarn::nested_name r;
    r.type(n);
    return r;
}

dogen::yarn::nested_name
mock_nested_name_shared_ptr(const dogen::yarn::name& n) {
    dogen::yarn::nested_name r;
    dogen::yarn::name_factory nf;
    r.type(nf.build_element_name("boost", "shared_ptr"));

    dogen::yarn::nested_name c;
    c.type(n);
    r.children(std::list<dogen::yarn::nested_name> { c });

    return r;
}

dogen::yarn::nested_name mock_nested_name(
    dogen::yarn::test::mock_intermediate_model_factory::property_types pt) {
    using namespace dogen::yarn;

    nested_name r;
    dogen::yarn::name_factory nf;
    typedef test::mock_intermediate_model_factory::property_types property_types;
    switch(pt) {
    case property_types::unsigned_int:
        r.type(nf.build_element_name(unsigned_int));
        break;
    case property_types::boolean:
        r.type(nf.build_element_name(boolean));
        break;
    case property_types::boost_variant: {
        r.type(nf.build_element_name("boost", "variant"));
        r.children(std::list<nested_name> {
                mock_nested_name(nf.build_element_name(boolean)),
                mock_nested_name(nf.build_element_name(unsigned_int))
        });
        break;
    }
    case property_types::std_string:
        r.type(nf.build_element_name("std", "string"));
        break;
    case property_types::std_pair: {
        r.type(nf.build_element_name("std", "pair"));
        r.children(std::list<nested_name> {
                mock_nested_name(nf.build_element_name(boolean)),
                mock_nested_name(nf.build_element_name(boolean))
        });
        break;
    }
    default:
        BOOST_LOG_SEV(lg, error) << invalid_property_type;
        BOOST_THROW_EXCEPTION(test::building_error(invalid_property_type));
    }
    return r;
}

std::list<std::string> make_internal_module_path(const unsigned int module_n) {
    std::list<std::string> r;
    for (unsigned int i(0); i < module_n; ++i)
        r.push_back(module_name(i));
    return r;
}

dogen::yarn::primitive make_primitive(const std::string& simple_name) {
    dogen::yarn::name_builder b;
    b.simple_name(simple_name);

    dogen::yarn::primitive r;
    r.name(b.build());
    return r;
}

void populate_object(dogen::yarn::object& o, const unsigned int i,
    const dogen::yarn::name& model_name, const unsigned int module_n) {

    const auto sn(type_name(i));
    const auto ipp(make_internal_module_path(module_n));

    dogen::yarn::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, sn, ipp));

    o.name(n);
    o.generation_type(dogen::yarn::generation_types::full_generation);
    o.documentation(documentation);
    o.origin_type(dogen::yarn::origin_types::user);
}

void populate_simple_model_properties(dogen::yarn::intermediate_model& m,
    const unsigned int n) {
    m.name(mock_model_name(n));
    m.origin_type(dogen::yarn::origin_types::user);
    m.generation_type(dogen::yarn::generation_types::full_generation);
}

dogen::yarn::property mock_property(const unsigned int n = 0,
    const dogen::yarn::test::mock_intermediate_model_factory::
    property_types pt =
    dogen::yarn::test::mock_intermediate_model_factory::property_types::
    unsigned_int,
    boost::optional<dogen::yarn::name> name =
    boost::optional<dogen::yarn::name>()) {
    dogen::yarn::property r;
    r.name(property_name(n));

    using property_types = dogen::yarn::test::mock_intermediate_model_factory::
        property_types;
    if (pt == property_types::value_object)
        r.type(mock_nested_name(*name));
    else if (pt == property_types::boost_shared_ptr)
        r.type(mock_nested_name_shared_ptr(*name));
    else
        r.type(mock_nested_name(pt));

    return r;
}

template<typename Stateful>
void add_property(Stateful& s, const bool properties_indexed,
    const unsigned int n = 0,
    const dogen::yarn::test::mock_intermediate_model_factory::
    property_types pt =
    dogen::yarn::test::mock_intermediate_model_factory::property_types::
    unsigned_int,
    boost::optional<dogen::yarn::name> name =
    boost::optional<dogen::yarn::name>()) {

    auto p(mock_property(n, pt, name));
    s.local_properties().push_back(p);

    if (properties_indexed)
        s.all_properties().push_back(p);
}

const bool add_leaf(true);

void model_concept(const bool properties_indexed,
    dogen::yarn::object& o, const dogen::yarn::concept& c) {

    o.modeled_concepts().push_back(c.name());
    if (properties_indexed) {
        for (const auto& p : c.all_properties()) {
            o.local_properties().push_back(p);
            o.all_properties().push_back(p);
        }
    }
}

void parent_to_child(const bool properties_indexed,
    dogen::yarn::object& parent,
    dogen::yarn::object& child,
    dogen::yarn::object& root_parent,
    const bool add_leaf_relationship = true) {

    child.parents().push_back(parent.name());
    parent.root_parents().push_back(root_parent.name());

    if (add_leaf_relationship)
        parent.leaves().push_back(child.name());

    parent.is_parent(true);
    child.is_child(true);

    if (properties_indexed && !parent.all_properties().empty()) {
        child.inherited_properties().insert(std::make_pair(
                parent.name(), parent.all_properties()));

        child.all_properties().insert(child.all_properties().end(),
            parent.all_properties().begin(), parent.all_properties().end());
    }
}

void parent_to_child(const bool properties_indexed,
    dogen::yarn::object& parent, dogen::yarn::object& child,
    const bool add_leaf_relationship = true) {
    parent_to_child(properties_indexed, parent, child, parent,
        add_leaf_relationship);
}

template<typename Nameable>
void insert_nameable(std::unordered_map<std::string, Nameable>& map,
    const Nameable& n) {
    map.insert(std::make_pair(n.name().qualified(), n));
}

void insert_object(dogen::yarn::intermediate_model& m,
    const dogen::yarn::object& o) {
    m.objects().insert(std::make_pair(o.name().qualified(), o));
}

void add_test_dynamic_extensions(dogen::dynamic::object& o) {
    using namespace dogen::dynamic;

    value_factory f;
    o.fields().insert(std::make_pair(licence_name_key,
            field_instance(f.make_text(licence_name_value))));

    o.fields().insert(std::make_pair(copyright_notices_key,
            field_instance(f.make_text(copyright_notices_value))));

    o.fields().insert(std::make_pair(modeline_group_name_key,
            field_instance(f.make_text(modeline_group_name_value))));

    o.fields().insert(std::make_pair(code_generation_marker_message_key,
            field_instance(
                f.make_text(code_generation_marker_message_value))));

    o.fields().insert(std::make_pair(generate_preamble_key,
            field_instance(f.make_text(generate_preamble_value))));
}

}

namespace dogen {
namespace yarn {
namespace test {

mock_intermediate_model_factory::flags::flags(const bool tagged,
    const bool merged, const bool resolved,
    const bool concepts_indexed, const bool properties_indexed,
    const bool associations_indexed) :
    tagged_(tagged), merged_(merged), resolved_(resolved),
    concepts_indexed_(concepts_indexed),
    properties_indexed_(properties_indexed),
    associations_indexed_(associations_indexed) { }

bool mock_intermediate_model_factory::flags::tagged() const {
    return tagged_;
}

void mock_intermediate_model_factory::flags::tagged(const bool v) {
    tagged_ = v;
}

bool mock_intermediate_model_factory::flags::merged() const {
    return merged_;
}

void mock_intermediate_model_factory::flags::merged(const bool v) {
    merged_ = v;
}

bool mock_intermediate_model_factory::flags::resolved() const {
    return resolved_;
}

void mock_intermediate_model_factory::flags::resolved(const bool v) {
    resolved_ = v;
}

bool mock_intermediate_model_factory::flags::concepts_indexed() const {
    return concepts_indexed_;
}
void mock_intermediate_model_factory::flags::concepts_indexed(const bool v) {
    concepts_indexed_ = v;
}

bool mock_intermediate_model_factory::flags::properties_indexed() const {
    return properties_indexed_;
}
void mock_intermediate_model_factory::flags::properties_indexed(const bool v) {
    properties_indexed_ = v;
}

bool mock_intermediate_model_factory::flags::associations_indexed() const {
    return associations_indexed_;
}
void mock_intermediate_model_factory::flags::
associations_indexed(const bool v) {
    associations_indexed_ = v;
}

mock_intermediate_model_factory::
mock_intermediate_model_factory(const flags& f,
    dynamic_extension_function_type fn) : flags_(f),
      dynamic_extension_function_(fn ? fn : add_test_dynamic_extensions) { }

std::string mock_intermediate_model_factory::
simple_model_name(const unsigned int n) const {
    return ::model_name(n);
}

std::string mock_intermediate_model_factory::
simple_concept_name(const unsigned int n) const {
    return ::concept_name(n);
}

std::string mock_intermediate_model_factory::
simple_type_name(const unsigned int n) const {
    return ::type_name(n);
}

std::string mock_intermediate_model_factory::
simple_module_name(const unsigned int n) const {
    return ::module_name(n);
}

std::string mock_intermediate_model_factory::
simple_property_name(const unsigned int n) const {
    return ::property_name(n);
}

name mock_intermediate_model_factory::
model_name(const unsigned int n) const {
    return ::mock_model_name(n);
}

bool mock_intermediate_model_factory::
is_model_n(const unsigned int n, const name& name) const {
    const auto mmp(name.location().model_module_path());
    if (mmp.empty())
        return false;

    const auto mn(name.location().model_module_path().back());
    return is_model_n(n, mn);
}

bool mock_intermediate_model_factory::
is_model_n(const unsigned int n, const std::string& name) const {
    return simple_model_name(n) == name;
}

bool mock_intermediate_model_factory::
is_type_name_n(const unsigned int n, const name& name) const {
    return is_type_name_n(n, name.simple());
}

bool mock_intermediate_model_factory::
is_concept_name_n(const unsigned int n, const name& name) const {
    return concept_name(n) == name.simple();
}

bool mock_intermediate_model_factory::
is_type_name_n(const unsigned int n, const std::string& name) const {
    return type_name(n) == name;
}

bool mock_intermediate_model_factory::
is_module_n(const unsigned int n, const std::string& name) const {
    return module_name(n) == name;
}

bool mock_intermediate_model_factory::is_type_name_n_visitor(
    const unsigned int n, const name& name) const {
    return
        boost::contains(name.simple(), type_name(n)) &&
        boost::contains(name.simple(), visitor_postfix);
}

void mock_intermediate_model_factory::handle_model_module(
    const bool add_model_module, yarn::intermediate_model& m) const {
    if (!add_model_module)
        return;

    const auto module(make_module(m.name(), documentation));
    insert_nameable(m.modules(), module);
}

object mock_intermediate_model_factory::make_value_object(const unsigned int i,
    const name& model_name, const unsigned int module_n) const {

    object r;
    populate_object(r, i, model_name, module_n);
    r.object_type(dogen::yarn::object_types::user_defined_value_object);

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

object mock_intermediate_model_factory::make_value_object(unsigned int i,
    const unsigned int module_n) const {
    return make_value_object(i, mock_model_name(i), module_n);
}

concept mock_intermediate_model_factory::make_concept(const unsigned int i,
    const name& model_name) const {

    dogen::yarn::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, concept_name(i)));

    concept r;
    r.name(n);
    r.documentation(documentation);
    r.origin_type(origin_types::user);

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

enumeration mock_intermediate_model_factory::
make_enumeration(const unsigned int i, const name& model_name,
    const unsigned int module_n) const {

    const auto sn(type_name(i));
    const auto ipp(make_internal_module_path(module_n));

    dogen::yarn::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, sn, ipp));

    enumeration r;
    r.name(n);
    r.generation_type(generation_types::full_generation);
    r.documentation(documentation);

    name un;
    un.simple(unsigned_int);
    r.underlying_type(un);

    const auto lambda([&](const unsigned int n) -> enumerator {
            enumerator r;
            r.name(type_name(n));
            r.value(boost::lexical_cast<std::string>(n));
            return r;
        });

    r.enumerators().push_back(lambda(0));
    r.enumerators().push_back(lambda(1));

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

object mock_intermediate_model_factory::make_exception(const unsigned int i,
    const name& model_name, const unsigned int module_n) const {

    const auto sn(type_name(i));
    const auto ipp(make_internal_module_path(module_n));

    dogen::yarn::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, sn, ipp));

    object r;
    r.name(n);
    r.generation_type(generation_types::full_generation);
    r.documentation(documentation);
    r.object_type(dogen::yarn::object_types::exception);

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

module mock_intermediate_model_factory::make_module(const yarn::name& n,
    const std::string& documentation) const {
    module r;
    r.name(n);
    r.documentation(documentation);

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

module mock_intermediate_model_factory::make_module(const unsigned int module_n,
    const yarn::name& model_name,
    const std::list<std::string>& internal_module_path,
    const std::string& documentation) const {

    name_factory nf;
    const auto mn(module_name(module_n));
    const auto n(nf.build_module_name(model_name, mn, internal_module_path));
    return make_module(n, documentation);
}

name mock_intermediate_model_factory::make_name(const unsigned int model_n,
    const unsigned int simple_n) const {

    name_builder b;
    b.simple_name(simple_type_name(simple_n));
    b.model_name(simple_model_name(model_n));
    return b.build();
}

intermediate_model mock_intermediate_model_factory::make_empty_model(
    const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r;
    populate_simple_model_properties(r, n);
    handle_model_module(add_model_module, r);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_single_type_model(const unsigned int n, const object_types ot,
    const bool add_model_module) const {
    return make_multi_type_model(n, 1, ot, 0, add_model_module);
}

intermediate_model mock_intermediate_model_factory::
make_single_type_model_in_module(const unsigned int n, const object_types ot,
    const unsigned int mod_n, const bool add_model_module) const {
    return make_multi_type_model(n, 1, ot, mod_n, add_model_module);
}

intermediate_model mock_intermediate_model_factory::
make_multi_type_model(const unsigned int n, const unsigned int type_n,
    const object_types ot, const unsigned int mod_n,
    const bool add_model_module) const {

    intermediate_model r(make_empty_model(n, add_model_module));

    std::list<std::string> internal_module_path;
    for (unsigned int i(0); i < mod_n; ++i) {
        const auto m(make_module(i, r.name(), internal_module_path,
                documentation));
        insert_nameable(r.modules(), m);
        internal_module_path.push_back(module_name(i));
    }

    switch (ot) {
    case object_types::value_object:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto o(make_value_object(i, r.name(), mod_n));
            insert_object(r, o);
        }
        break;
    case object_types::enumeration:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(make_enumeration(i, r.name(), mod_n));
            insert_nameable(r.enumerations(), e);
        }
        break;
    case object_types::exception:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(make_exception(i, r.name(), mod_n));
            insert_object(r, e);
        }
        break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(building_error(invalid_object_type));
    }

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_single_concept_model(const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));

    const auto ui(make_primitive(unsigned_int));
    r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

    concept c(make_concept(0, r.name()));
    add_property(c, flags_.properties_indexed());
    insert_nameable(r.concepts(), c);

    auto o(make_value_object(0, r.name()));
    add_property(o, flags_.properties_indexed(), 1);
    model_concept(flags_.properties_indexed(), o, c);
    insert_object(r, o);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_first_degree_concepts_model(const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));

    const auto ui(make_primitive(unsigned_int));
    r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    auto o0(make_value_object(0, r.name()));
    model_concept(flags_.properties_indexed(), o0, c0);
    insert_object(r, o0);

    auto o1(make_value_object(1, r.name()));
    add_property(o1, flags_.properties_indexed(), 2);

    if (flags_.concepts_indexed())
        model_concept(flags_.properties_indexed(), o1, c0);

    model_concept(flags_.properties_indexed(), o1, c1);
    insert_object(r, o1);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_second_degree_concepts_model(const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));

    const auto ui(make_primitive(unsigned_int));
    r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    concept c2(make_concept(2, r.name()));
    add_property(c2, flags_.properties_indexed(), 2);

    if (flags_.concepts_indexed())
        c2.refines().push_back(c0.name());

    c2.refines().push_back(c1.name());
    insert_nameable(r.concepts(), c2);

    auto o0(make_value_object(0, r.name()));
    model_concept(flags_.properties_indexed(), o0, c0);
    insert_object(r, o0);

    auto o1(make_value_object(1, r.name()));
    if (flags_.concepts_indexed())
        model_concept(flags_.properties_indexed(), o1, c0);

    model_concept(flags_.properties_indexed(), o1, c1);
    insert_object(r, o1);

    auto o2(make_value_object(2, r.name()));
    add_property(o2, flags_.properties_indexed(), 3);
    if (flags_.concepts_indexed()) {
        model_concept(flags_.properties_indexed(), o2, c0);
        model_concept(flags_.properties_indexed(), o2, c1);
    }
    model_concept(flags_.properties_indexed(), o2, c2);
    insert_object(r, o2);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_multiple_inheritance_concepts_model(
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));

    const auto ui(make_primitive(unsigned_int));
    r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    insert_nameable(r.concepts(), c1);

    concept c2(make_concept(1, r.name()));
    add_property(c2, flags_.properties_indexed(), 2);
    c2.refines().push_back(c0.name());
    c2.refines().push_back(c1.name());
    insert_nameable(r.concepts(), c2);

    auto o0(make_value_object(0, r.name()));
    model_concept(flags_.properties_indexed(), o0, c2);
    insert_object(r, o0);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_diamond_inheritance_concepts_model(const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));

    const auto ui(make_primitive(unsigned_int));
    r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    concept c2(make_concept(2, r.name()));
    add_property(c2, flags_.properties_indexed(), 2);
    c2.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c2);

    concept c3(make_concept(3, r.name()));
    add_property(c3, flags_.properties_indexed(), 3);
    if (flags_.concepts_indexed())
        c3.refines().push_back(c0.name());

    c3.refines().push_back(c1.name());
    c3.refines().push_back(c2.name());
    insert_nameable(r.concepts(), c3);

    auto o0(make_value_object(0, r.name()));
    if (flags_.concepts_indexed()) {
        model_concept(flags_.properties_indexed(), o0, c0);
        model_concept(flags_.properties_indexed(), o0, c1);
        model_concept(flags_.properties_indexed(), o0, c2);
    }
    model_concept(flags_.properties_indexed(), o0, c3);
    insert_object(r, o0);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_object_with_parent_that_models_concept(
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));

    const auto ui(make_primitive(unsigned_int));
    r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    auto o0(make_value_object(0, r.name()));
    model_concept(flags_.properties_indexed(), o0, c0);

    insert_object(r, o0);

    auto o1(make_value_object(1, r.name()));
    parent_to_child(flags_.properties_indexed(), o0, o1);
    o0.is_parent(true);
    insert_object(r, o1);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_object_with_parent_that_models_a_refined_concept(
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));

    const auto ui(make_primitive(unsigned_int));
    r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    auto o0(make_value_object(0, r.name()));

    model_concept(flags_.properties_indexed(), o0, c1);
    if (flags_.concepts_indexed())
        model_concept(flags_.properties_indexed(), o0, c0);

    insert_object(r, o0);

    auto o1(make_value_object(1, r.name()));
    parent_to_child(flags_.properties_indexed(), o0, o1);
    o0.is_parent(true);
    insert_object(r, o1);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_concept_that_refines_missing_concept(const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));
    concept c0(make_concept(0, r.name()));
    concept c1(make_concept(1, r.name()));
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_object_that_models_missing_concept(const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));

    const auto ui(make_primitive(unsigned_int));
    r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());

    auto o0(make_value_object(0, r.name()));

    model_concept(flags_.properties_indexed(), o0, c0);
    insert_object(r, o0);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_object_that_models_concept_with_missing_parent(
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(n, add_model_module));

    const auto ui(make_primitive(unsigned_int));
    r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    auto o0(make_value_object(0, r.name()));
    auto o1(make_value_object(1, r.name()));
    parent_to_child(flags_.properties_indexed(), o0, o1);
    o0.is_parent(true);

    model_concept(flags_.properties_indexed(), o1, c0);
    insert_object(r, o1);

    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_both_regular_and_weak_associations(
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(0, add_model_module));
    const auto mn(mock_model_name(0));
    auto o1(make_value_object(1, mn));
    insert_object(r, o1);

    object o0(make_value_object(0, mn));
    property p0(mock_property(0, property_types::value_object, o1.name()));
    o0.local_properties().push_back(p0);
    if (flags_.properties_indexed())
        o0.all_properties().push_back(p0);

    if (flags_.associations_indexed())
        o0.regular_associations().push_back(o1.name());

    dogen::yarn::name_factory nf;
    object o2;
    o2.name(nf.build_element_name("boost", "shared_ptr"));
    o2.object_type(dogen::yarn::object_types::smart_pointer);
    insert_object(r, o2);

    property p1(mock_property(1, property_types::boost_shared_ptr, o1.name()));
    o0.local_properties().push_back(p1);
    if (flags_.properties_indexed())
        o0.all_properties().push_back(p1);

    if (flags_.associations_indexed())
        o0.weak_associations().push_back(o1.name());

    object o3(make_value_object(3, mn));
    insert_object(r, o3);

    property p2(mock_property(2, property_types::boost_shared_ptr, o3.name()));
    o0.local_properties().push_back(p2);
    if (flags_.properties_indexed())
        o0.all_properties().push_back(p2);

    if (flags_.associations_indexed())
        o0.weak_associations().push_back(o3.name());

    object o4;
    o4.name(nf.build_element_name("std", "string"));
    o4.object_type(dogen::yarn::object_types::user_defined_value_object);
    insert_object(r, o4);

    property p3(mock_property(3, property_types::value_object, o4.name()));
    o0.local_properties().push_back(p3);

    if (flags_.properties_indexed())
        o0.all_properties().push_back(p3);

    if (flags_.associations_indexed())
        o0.regular_associations().push_back(o4.name());

    insert_object(r, o0);
    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_property(const object_types ot, const property_types pt,
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o1(make_value_object(1, mn));

    property p(mock_property(0, pt, o1.name()));

    object o0;
    if (ot == object_types::value_object)
        o0 = make_value_object(0, mn);
    else {
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(building_error(invalid_object_type));
    }

    o0.local_properties().push_back(p);
    if (flags_.properties_indexed())
        o0.all_properties().push_back(p);

    dogen::yarn::name_factory nf;
    intermediate_model r(make_empty_model(0, add_model_module));
    if (pt == property_types::value_object ||
        pt == property_types::boost_shared_ptr) {
        insert_object(r, o1);

        if (flags_.associations_indexed())
            o0.regular_associations().push_back(o1.name());
    }

    if (pt == property_types::unsigned_int ||
        pt == property_types::boolean) {
        primitive ui;
        ui.name(p.type().type());
        insert_nameable(r.primitives(), ui);

        if (flags_.associations_indexed())
            o0.regular_associations().push_back(ui.name());

    } else if (pt == property_types::boost_shared_ptr) {
        object o2;
        o2.name(nf.build_element_name("boost", "shared_ptr"));
        o2.object_type(dogen::yarn::object_types::smart_pointer);
        insert_object(r, o2);

        if (flags_.associations_indexed())
            o0.weak_associations().push_back(o2.name());

    } else if (pt == property_types::std_pair) {
        const auto b(make_primitive(boolean));
        r.primitives().insert(std::make_pair(b.name().qualified(), b));

        if (flags_.associations_indexed())
            o0.regular_associations().push_back(b.name());

        object o2;
        o2.name(nf.build_element_name("std", "pair"));
        o2.object_type(dogen::yarn::object_types::user_defined_value_object);

        if (flags_.associations_indexed())
            o0.regular_associations().push_back(o2.name());

        insert_object(r, o2);
    } else if (pt == property_types::boost_variant) {
        const auto b(make_primitive(boolean));
        r.primitives().insert(std::make_pair(b.name().qualified(), b));

        if (flags_.associations_indexed())
            o0.regular_associations().push_back(b.name());

        const auto ui(make_primitive(unsigned_int));
        r.primitives().insert(std::make_pair(ui.name().qualified(), ui));

        if (flags_.associations_indexed())
            o0.regular_associations().push_back(ui.name());

        object o2;
        o2.name(nf.build_element_name("boost", "variant"));
        o2.object_type(dogen::yarn::object_types::user_defined_value_object);
        insert_object(r, o2);

        if (flags_.associations_indexed())
            o0.regular_associations().push_back(o2.name());

    } else if (pt == property_types::std_string) {
        object o2;
        o2.name(nf.build_element_name("std", "string"));
        o2.object_type(dogen::yarn::object_types::user_defined_value_object);
        insert_object(r, o2);

        if (flags_.associations_indexed())
            o0.regular_associations().push_back(o2.name());
    }
    insert_object(r, o0);
    return r;
}

std::array<intermediate_model, 2>
mock_intermediate_model_factory::object_with_property_type_in_different_model(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));

    add_property(o0, flags_.properties_indexed(),
        0, property_types::value_object, o1.name());

    intermediate_model m0;
    dogen::yarn::name_factory nf;
    m0.name(nf.build_model_name(simple_model_name(0)));
    insert_object(m0, o0);
    handle_model_module(add_model_module, m0);

    intermediate_model m1;
    m1.name(nf.build_model_name(simple_model_name(1)));
    insert_object(m1, o1);
    handle_model_module(add_model_module, m1);

    return std::array<intermediate_model, 2> {{ m0, m1 }};
}

intermediate_model mock_intermediate_model_factory::
object_with_missing_property_type(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));

    add_property(o0, flags_.properties_indexed(), 0,
        property_types::value_object, o1.name());

    if (flags_.associations_indexed())
        o0.regular_associations().push_back(o1.name());

    intermediate_model r(make_empty_model(0, add_model_module));
    insert_object(r, o0);

    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_parent_in_the_same_model(const bool has_property,
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));

    auto r(make_empty_model(0, add_model_module));
    if (has_property) {
        const auto ui(make_primitive(unsigned_int));
        r.primitives().insert(std::make_pair(ui.name().qualified(), ui));
    }

    auto o0(make_value_object(0, mn));
    if (has_property)
        add_property(o0, flags_.properties_indexed());

    auto o1(make_value_object(1, mn));
    if (has_property)
        add_property(o1, flags_.properties_indexed(), 1);

    parent_to_child(flags_.properties_indexed(), o1, o0);
    insert_object(r, o0);
    insert_object(r, o1);

    o1.is_parent(true);
    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_missing_parent_in_the_same_model(
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o0(make_value_object(0, mn));
    auto o1(make_value_object(1, mn));
    o1.is_parent(true);
    parent_to_child(flags_.properties_indexed(), o1, o0);
    auto r(make_empty_model(0, add_model_module));
    insert_object(r, o1);

    return r;
}

std::array<intermediate_model, 2> mock_intermediate_model_factory::
object_with_parent_in_different_models(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));
    parent_to_child(flags_.properties_indexed(), o1, o0);

    o1.is_parent(true);

    auto m0(make_empty_model(0, add_model_module));
    insert_object(m0, o0);

    auto m1(make_empty_model(1, add_model_module));
    insert_object(m1, o1);
    m1.name(mock_model_name(1));
    m1.origin_type(origin_types::user);

    return std::array<intermediate_model, 2> {{ m0, m1 }};
}

intermediate_model mock_intermediate_model_factory::
object_with_three_children_in_same_model(
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o0(make_value_object(0, mn));
    auto o1(make_value_object(1, mn));
    auto o2(make_value_object(2, mn));
    auto o3(make_value_object(3, mn));

    parent_to_child(flags_.properties_indexed(), o3, o0);
    parent_to_child(flags_.properties_indexed(), o3, o1);
    parent_to_child(flags_.properties_indexed(), o3, o2);

    o3.is_parent(true);

    auto r(make_empty_model(0, add_model_module));
    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    insert_object(r, o3);
    r.name(mn);
    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_third_degree_parent_in_same_model(const bool has_property,
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));

    auto r(make_empty_model(0, add_model_module));
    if (has_property) {
        const auto ui(make_primitive(unsigned_int));
        r.primitives().insert(std::make_pair(ui.name().qualified(), ui));
    }

    auto o3(make_value_object(3, mn));
    if (has_property)
        add_property(o3, flags_.properties_indexed(), 3);

    auto o2(make_value_object(2, mn));
    if (has_property)
        add_property(o2, flags_.properties_indexed(), 2);
    parent_to_child(flags_.properties_indexed(), o3, o2, o3, !add_leaf);

    auto o1(make_value_object(1, mn));
    if (has_property)
        add_property(o1, flags_.properties_indexed(), 1);
    parent_to_child(flags_.properties_indexed(), o2, o1, o3, !add_leaf);

    auto o0(make_value_object(0, mn));
    if (has_property)
        add_property(o0, flags_.properties_indexed());

    parent_to_child(flags_.properties_indexed(), o1, o0, o3, !add_leaf);

    o1.is_parent(true);
    o1.leaves().push_back(o0.name());

    o2.is_parent(true);
    o2.leaves().push_back(o0.name());

    o3.is_parent(true);
    o3.leaves().push_back(o0.name());

    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    insert_object(r, o3);

    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_third_degree_parent_missing(
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o0(make_value_object(0, mn));
    auto o1(make_value_object(1, mn));
    auto o2(make_value_object(2, mn));
    auto o3(make_value_object(3, mn));

    parent_to_child(flags_.properties_indexed(), o1, o0, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o2, o1, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o3, o2, o3, !add_leaf);

    o1.is_parent(true);
    o1.leaves().push_back(o0.name());

    o2.is_parent(true);
    o2.leaves().push_back(o0.name());

    o3.is_parent(true);
    o3.leaves().push_back(o0.name());

    auto r(make_empty_model(0, add_model_module));
    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    r.name(mn);
    return r;
}

std::array<intermediate_model, 4> mock_intermediate_model_factory::
object_with_third_degree_parent_in_different_models(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));
    auto o2(make_value_object(2));
    auto o3(make_value_object(3));

    parent_to_child(flags_.properties_indexed(), o1, o0, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o2, o1, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o3, o2, o3, !add_leaf);

    o1.is_parent(true);
    o1.leaves().push_back(o0.name());

    o2.is_parent(true);
    o2.leaves().push_back(o0.name());

    o3.is_parent(true);
    o3.leaves().push_back(o0.name());

    auto m0(make_empty_model(0, add_model_module));
    insert_object(m0, o0);

    auto m1(make_empty_model(1, add_model_module));
    insert_object(m1, o1);

    auto m2(make_empty_model(2, add_model_module));
    insert_object(m2, o2);

    auto m3(make_empty_model(3, add_model_module));
    insert_object(m3, o3);

    return std::array<intermediate_model, 4>{{ m0, m1, m2, m3 }};
}

std::array<intermediate_model, 4> mock_intermediate_model_factory::
object_with_missing_third_degree_parent_in_different_models(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));
    auto o2(make_value_object(2));
    auto o3(make_value_object(3));

    parent_to_child(flags_.properties_indexed(), o1, o0, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o2, o1, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o3, o2, o3, !add_leaf);

    o1.is_parent(true);
    o1.leaves().push_back(o0.name());

    o2.is_parent(true);
    o2.leaves().push_back(o0.name());

    o3.is_parent(true);
    o3.leaves().push_back(o0.name());

    auto m0(make_empty_model(0, add_model_module));
    insert_object(m0, o0);

    auto m1(make_empty_model(1, add_model_module));
    insert_object(m1, o1);

    auto m2(make_empty_model(2, add_model_module));
    insert_object(m2, o2);

    return std::array<intermediate_model, 4>{{ m0, m1, m2 }};
}

intermediate_model mock_intermediate_model_factory::
object_with_group_of_properties_of_different_types(
    const bool repeat_group, const bool add_model_module) const {
    auto r(make_empty_model(0, add_model_module));
    const auto mn(r.name());

    auto o0(make_value_object(0, mn));
    const auto lambda([&](const property& p) {
            o0.local_properties().push_back(p);
            if (flags_.properties_indexed())
                o0.all_properties().push_back(p);
        });

    auto o1(make_value_object(1, mn));
    auto p0(mock_property(0, property_types::value_object, o1.name()));
    lambda(p0);
    insert_object(r, o1);

    auto p1(mock_property(1));
    lambda(p1);
    primitive ui;
    ui.name(p1.type().type());
    insert_nameable(r.primitives(), ui);

    auto o3(make_value_object(3, mn));
    insert_object(r, o3);
    auto p2(mock_property(2, property_types::boost_shared_ptr, o3.name()));
    lambda(p2);

    object o2;
    dogen::yarn::name_factory nf;
    o2.name(nf.build_element_name("boost", "shared_ptr"));
    o2.object_type(dogen::yarn::object_types::smart_pointer);
    insert_object(r, o2);

    auto o4(make_value_object(4, mn));
    insert_object(r, o4);
    auto p3(mock_property(3, property_types::value_object, o4.name()));
    lambda(p3);

    if (repeat_group) {
        auto p4(mock_property(4, property_types::value_object, o1.name()));
        lambda(p4);

        auto p5(mock_property(5));
        lambda(p5);

        auto p6(mock_property(6, property_types::boost_shared_ptr, o3.name()));
        lambda(p6);

        auto p7(mock_property(7, property_types::value_object, o4.name()));
        lambda(p7);
    }
    insert_object(r, o0);
    return r;
}

} } }
