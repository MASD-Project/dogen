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
#include "dogen/annotations/types/value_factory.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/builtin.hpp"
#include "dogen/yarn/types/helpers/building_error.hpp"
#include "dogen/yarn/test/mock_intermediate_model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.mock_intermediate_model_factory"));

const std::string model_name_prefix("some_model_");
const std::string type_name_prefix("some_type_");
const std::string concept_name_prefix("some_concept_");
const std::string attribute_name_prefix("some_attribute_");
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

const std::string invalid_attribute_type("Unknown attribute type.");
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

std::string attribute_name(const unsigned int i) {
    std::ostringstream stream;
    stream << attribute_name_prefix << i;
    return stream.str();
}

std::string module_name(const unsigned int i) {
    std::ostringstream stream;
    stream << module_name_prefix << i;
    return stream.str();
}

dogen::yarn::name mock_model_name(unsigned int i) {
    dogen::yarn::helpers::name_factory nf;
    return nf.build_model_name(model_name(i));
}

dogen::yarn::name_tree mock_name_tree(const dogen::yarn::name& n) {
    dogen::yarn::name_tree r;
    r.current(n);
    return r;
}

dogen::yarn::name_tree
mock_name_tree_shared_ptr(const dogen::yarn::name& n) {
    dogen::yarn::name_tree r;
    dogen::yarn::helpers::name_factory nf;
    r.current(nf.build_element_name("boost", "shared_ptr"));
    r.are_children_opaque(true);

    dogen::yarn::name_tree c;
    c.current(n);
    r.children(std::list<dogen::yarn::name_tree> { c });

    return r;
}

std::string mock_unparsed_type(const dogen::yarn::name& n) {
    std::string r;
    for (const auto& mm : n.location().model_modules())
        r += mm + "::";

    for (const auto& mm : n.location().internal_modules())
        r += mm + "::";

    r += n.simple();
    return r;
}

std::string mock_unparsed_type_shared_ptr(const dogen::yarn::name& n) {
    std::string r("boost::shared_ptr<");
    r += mock_unparsed_type(n);
    r += ">";
    return r;
}

dogen::yarn::name_tree mock_name_tree(
    dogen::yarn::test::mock_intermediate_model_factory::attribute_types pt) {
    using namespace dogen::yarn;

    name_tree r;
    dogen::yarn::helpers::name_factory nf;
    using test::mock_intermediate_model_factory;
    using attribute_types = mock_intermediate_model_factory::attribute_types;

    switch(pt) {
    case attribute_types::unsigned_int:
        r.current(nf.build_element_name(unsigned_int));
        break;
    case attribute_types::boolean:
        r.current(nf.build_element_name(boolean));
        break;
    case attribute_types::boost_variant: {
        r.current(nf.build_element_name("boost", "variant"));
        r.children(std::list<name_tree> {
                mock_name_tree(nf.build_element_name(boolean)),
                mock_name_tree(nf.build_element_name(unsigned_int))
        });
        break;
    }
    case attribute_types::std_string:
        r.current(nf.build_element_name("std", "string"));
        break;
    case attribute_types::std_pair: {
        r.current(nf.build_element_name("std", "pair"));
        r.children(std::list<name_tree> {
                mock_name_tree(nf.build_element_name(boolean)),
                mock_name_tree(nf.build_element_name(boolean))
        });
        break;
    }
    default:
        BOOST_LOG_SEV(lg, error) << invalid_attribute_type;
        BOOST_THROW_EXCEPTION(helpers::building_error(invalid_attribute_type));
    }
    return r;
}

std::string mock_unparsed_type(
    dogen::yarn::test::mock_intermediate_model_factory::attribute_types pt) {
    using namespace dogen::yarn;
    using test::mock_intermediate_model_factory;
    using attribute_types = mock_intermediate_model_factory::attribute_types;

    switch(pt) {
    case attribute_types::unsigned_int:
        return unsigned_int;
        break;
    case attribute_types::boolean:
        return boolean;
        break;
    case attribute_types::boost_variant: {
        std::string r("boost::variant<");
        r += boolean;
        r += ", ";
        r += unsigned_int;
        r += ">";
        return r;
        break;
    }
    case attribute_types::std_string:
        return "std::string";
        break;
    case attribute_types::std_pair: {
        std::string r("std::pair<");
        r += boolean;
        r += ", ";
        r += unsigned_int;
        r += ">";
        break;
    }
    default:
        BOOST_LOG_SEV(lg, error) << invalid_attribute_type;
        BOOST_THROW_EXCEPTION(helpers::building_error(invalid_attribute_type));
    }
    return std::string();
}

std::list<std::string> make_internal_modules(const unsigned int module_n) {
    std::list<std::string> r;
    for (unsigned int i(0); i < module_n; ++i)
        r.push_back(module_name(i));
    return r;
}

dogen::yarn::builtin make_builtin(const std::string& simple_name) {
    dogen::yarn::helpers::name_builder b;
    b.simple_name(simple_name);

    dogen::yarn::builtin r;
    r.name(b.build());
    return r;
}

void populate_object(dogen::yarn::object& o, const unsigned int i,
    const dogen::yarn::name& model_name, const unsigned int module_n,
    const dogen::yarn::origin_types ot) {

    const auto sn(type_name(i));
    const auto ipp(make_internal_modules(module_n));

    dogen::yarn::helpers::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, sn, ipp));

    o.name(n);
    o.documentation(documentation);
    o.origin_type(ot);
}

void populate_simple_model_attributes(dogen::yarn::intermediate_model& m,
    const unsigned int n, const dogen::yarn::origin_types ot) {
    m.name(mock_model_name(n));
    m.origin_type(ot);
}

dogen::yarn::attribute mock_attribute(const dogen::yarn::name& owning_element,
    const bool types_parsed, const unsigned int n = 0,
    const dogen::yarn::test::mock_intermediate_model_factory::
    attribute_types pt =
    dogen::yarn::test::mock_intermediate_model_factory::attribute_types::
    unsigned_int,
    boost::optional<dogen::yarn::name> name =
    boost::optional<dogen::yarn::name>()) {

    dogen::yarn::helpers::name_factory f;
    const auto pn(f.build_attribute_name(owning_element, attribute_name(n)));

    dogen::yarn::attribute r;
    r.name(pn);
    r.documentation(documentation);

    using dogen::yarn::test::mock_intermediate_model_factory;
    using attribute_types = mock_intermediate_model_factory::attribute_types;

    if (types_parsed) {
        if (pt == attribute_types::value_object)
            r.parsed_type(mock_name_tree(*name));
        else if (pt == attribute_types::boost_shared_ptr)
            r.parsed_type(mock_name_tree_shared_ptr(*name));
        else
            r.parsed_type(mock_name_tree(pt));
    } else
        BOOST_LOG_SEV(lg, debug) << "Not generating parsed type.";

    if (pt == attribute_types::value_object)
        r.unparsed_type(mock_unparsed_type(*name));
    else if (pt == attribute_types::boost_shared_ptr)
        r.unparsed_type(mock_unparsed_type_shared_ptr(*name));
    else
        r.unparsed_type(mock_unparsed_type(pt));

    return r;
}

template<typename StatefulAndNameable>
void add_attribute(StatefulAndNameable& sn, const bool attributes_indexed,
    const bool types_parsed, const unsigned int n = 0,
    const dogen::yarn::test::mock_intermediate_model_factory::
    attribute_types pt =
    dogen::yarn::test::mock_intermediate_model_factory::attribute_types::
    unsigned_int,
    boost::optional<dogen::yarn::name> name =
    boost::optional<dogen::yarn::name>()) {


    const auto p(mock_attribute(sn.name(), types_parsed, n, pt, name));
    sn.local_attributes().push_back(p);

    if (attributes_indexed)
        sn.all_attributes().push_back(p);
}

const bool add_leaf(true);

void model_concept(const bool attributes_indexed,
    dogen::yarn::object& o, const dogen::yarn::concept& c) {

    o.modeled_concepts().push_back(c.name());
    if (attributes_indexed) {
        for (const auto& p : c.all_attributes()) {
            o.local_attributes().push_back(p);
            o.all_attributes().push_back(p);
        }
    }
}

void parent_to_child(const bool attributes_indexed,
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

    if (attributes_indexed) {
        const auto pair(
            std::make_pair(parent.name(), parent.all_attributes()));
        child.inherited_attributes().insert(pair);

        if (!parent.all_attributes().empty()) {
            child.all_attributes().insert(child.all_attributes().end(),
                parent.all_attributes().begin(), parent.all_attributes().end());
        }
    }
}

void parent_to_child(const bool attributes_indexed,
    dogen::yarn::object& parent, dogen::yarn::object& child,
    const bool add_leaf_relationship = true) {
    parent_to_child(attributes_indexed, parent, child, parent,
        add_leaf_relationship);
}

template<typename Nameable>
void insert_nameable(std::unordered_map<std::string, Nameable>& map,
    const Nameable& n) {
    map.insert(std::make_pair(n.name().id(), n));
}

void insert_object(dogen::yarn::intermediate_model& m,
    const dogen::yarn::object& o) {
    m.objects().insert(std::make_pair(o.name().id(), o));
}

void add_test_annotationss(dogen::annotations::annotation& a) {
    using namespace dogen::annotations;

    value_factory f;
    a.entries().insert(std::make_pair(licence_name_key,
            f.make_text(licence_name_value)));

    a.entries().insert(std::make_pair(copyright_notices_key,
            f.make_text(copyright_notices_value)));

    a.entries().insert(std::make_pair(modeline_group_name_key,
            f.make_text(modeline_group_name_value)));

    a.entries().insert(std::make_pair(code_generation_marker_message_key,
            f.make_text(code_generation_marker_message_value)));

    a.entries().insert(std::make_pair(generate_preamble_key,
            f.make_text(generate_preamble_value)));
}

}

namespace dogen {
namespace yarn {
namespace test {

mock_intermediate_model_factory::flags::flags(const bool tagged,
    const bool merged, const bool resolved,
    const bool concepts_indexed, const bool attributes_indexed,
    const bool associations_indexed, const bool types_parsed) :
    tagged_(tagged), merged_(merged), resolved_(resolved),
    concepts_indexed_(concepts_indexed),
    attributes_indexed_(attributes_indexed),
    associations_indexed_(associations_indexed),
    types_parsed_(types_parsed) { }

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

bool mock_intermediate_model_factory::flags::attributes_indexed() const {
    return attributes_indexed_;
}

void mock_intermediate_model_factory::flags::attributes_indexed(const bool v) {
    attributes_indexed_ = v;
}

bool mock_intermediate_model_factory::flags::associations_indexed() const {
    return associations_indexed_;
}

void mock_intermediate_model_factory::flags::types_parsed(const bool v) {
    types_parsed_ = v;
}

bool mock_intermediate_model_factory::flags::types_parsed() const {
    return types_parsed_;
}

void mock_intermediate_model_factory::flags::
associations_indexed(const bool v) {
    associations_indexed_ = v;
}

mock_intermediate_model_factory::
mock_intermediate_model_factory(const flags& f,
    annotation_function_type fn) : flags_(f),
      annotation_function_(fn ? fn : add_test_annotationss) { }

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
simple_attribute_name(const unsigned int n) const {
    return ::attribute_name(n);
}

name mock_intermediate_model_factory::
model_name(const unsigned int n) const {
    return ::mock_model_name(n);
}

bool mock_intermediate_model_factory::
is_model_n(const unsigned int n, const name& name) const {
    const auto mmp(name.location().model_modules());
    if (mmp.empty())
        return false;

    const auto mn(name.location().model_modules().back());
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

    const auto module(make_module(m.name(), m.origin_type(), documentation));
    insert_nameable(m.modules(), module);
}

builtin mock_intermediate_model_factory::
make_builtin(const unsigned int i, const name& model_name,
        const origin_types ot, const unsigned int module_n) const {

    const auto sn(type_name(i));
    const auto ipp(make_internal_modules(module_n));

    dogen::yarn::helpers::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, sn, ipp));

    builtin r;
    r.name(n);
    r.documentation(documentation);
    r.origin_type(ot);

    return r;
}

object mock_intermediate_model_factory::make_value_object(const unsigned int i,
    const name& model_name, const origin_types ot,
    const unsigned int module_n) const {

    object r;
    populate_object(r, i, model_name, module_n, ot);

    if (flags_.tagged())
        annotation_function_(r.annotation());

    return r;
}

object mock_intermediate_model_factory::make_value_object_with_attribute(
    const unsigned int i, const name& model_name,
    const origin_types ot, const unsigned int module_n) const {

    auto r(make_value_object(i, model_name, ot, module_n));
    add_attribute(r, flags_.attributes_indexed(), flags_.types_parsed());
    return r;
}

object mock_intermediate_model_factory::make_value_object(unsigned int i,
    const origin_types ot, const unsigned int module_n) const {
    return make_value_object(i, mock_model_name(i), ot, module_n);
}

concept mock_intermediate_model_factory::make_concept(const unsigned int i,
    const name& model_name, const origin_types ot) const {

    dogen::yarn::helpers::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, concept_name(i)));

    concept r;
    r.name(n);
    r.documentation(documentation);
    r.origin_type(ot);

    if (flags_.tagged())
        annotation_function_(r.annotation());

    return r;
}

enumeration mock_intermediate_model_factory::
make_enumeration(const unsigned int i, const name& model_name,
    const origin_types ot, const unsigned int module_n) const {

    const auto sn(type_name(i));
    const auto ipp(make_internal_modules(module_n));

    dogen::yarn::helpers::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, sn, ipp));

    enumeration r;
    r.name(n);
    r.documentation(documentation);
    r.origin_type(ot);

    name ue;
    ue.simple(unsigned_int);
    r.underlying_element(ue);

    const auto lambda([&](const unsigned int pos) -> enumerator {
            enumerator r;
            r.name(nf.build_attribute_name(n, type_name(pos)));;
            r.value(boost::lexical_cast<std::string>(pos));
            return r;
        });

    r.enumerators().push_back(lambda(0));
    r.enumerators().push_back(lambda(1));

    if (flags_.tagged())
        annotation_function_(r.annotation());

    return r;
}

exception mock_intermediate_model_factory::make_exception(const unsigned int i,
    const name& model_name, const origin_types ot,
    const unsigned int module_n) const {

    const auto sn(type_name(i));
    const auto ipp(make_internal_modules(module_n));

    dogen::yarn::helpers::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, sn, ipp));

    exception r;
    r.name(n);
    r.documentation(documentation);
    r.origin_type(ot);

    if (flags_.tagged())
        annotation_function_(r.annotation());

    return r;
}

module mock_intermediate_model_factory::make_module(const yarn::name& n,
    const origin_types ot, const std::string& documentation) const {
    module r;
    r.name(n);
    r.documentation(documentation);
    r.origin_type(ot);

    if (flags_.tagged())
        annotation_function_(r.annotation());

    return r;
}

module mock_intermediate_model_factory::make_module(const unsigned int module_n,
    const yarn::name& model_name, const origin_types ot,
    const std::list<std::string>& internal_modules,
    const std::string& documentation) const {

    helpers::name_factory nf;
    const auto mn(module_name(module_n));
    const auto n(nf.build_module_name(model_name, mn, internal_modules));
    return make_module(n, ot, documentation);
}

name mock_intermediate_model_factory::make_name(const unsigned int model_n,
    const unsigned int simple_n) const {

    helpers::name_builder b;
    b.simple_name(simple_type_name(simple_n));
    b.model_name(simple_model_name(model_n));
    return b.build();
}

intermediate_model mock_intermediate_model_factory::make_empty_model(
    const origin_types ot, const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r;
    populate_simple_model_attributes(r, n, ot);
    handle_model_module(add_model_module, r);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_single_type_model(const origin_types ot, const unsigned int n,
    const object_types objt, const bool add_model_module) const {
    return make_multi_type_model(n, 1, ot, objt, 0, add_model_module);
}

intermediate_model mock_intermediate_model_factory::
make_single_type_model_in_module(const origin_types ot, const unsigned int n,
    const object_types objt, const unsigned int mod_n,
    const bool add_model_module) const {
    return make_multi_type_model(n, 1, ot, objt, mod_n, add_model_module);
}

intermediate_model mock_intermediate_model_factory::
make_multi_type_model(const unsigned int n, const unsigned int type_n,
    const origin_types ot, const object_types objt,
    const unsigned int mod_n, const bool add_model_module) const {

    intermediate_model r(make_empty_model(ot, n, add_model_module));

    std::list<std::string> internal_modules;
    for (unsigned int i(0); i < mod_n; ++i) {
        const auto m(make_module(i, r.name(), ot, internal_modules,
                documentation));
        insert_nameable(r.modules(), m);
        internal_modules.push_back(module_name(i));
    }

    switch (objt) {
    case object_types::value_object:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto o(make_value_object(i, r.name(), ot, mod_n));
            insert_object(r, o);
        }
        break;
    case object_types::enumeration:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(make_enumeration(i, r.name(), ot, mod_n));
            insert_nameable(r.enumerations(), e);
        }
        break;
    case object_types::exception:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(make_exception(i, r.name(), ot, mod_n));
            insert_nameable(r.exceptions(), e);
        }
        break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(helpers::building_error(invalid_object_type));
    }

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_single_concept_model(const origin_types ot, const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));

    const auto ui(::make_builtin(unsigned_int));
    r.builtins().insert(std::make_pair(ui.name().id(), ui));

    concept c(make_concept(0, r.name(), ot));
    add_attribute(c, flags_.attributes_indexed(), flags_.types_parsed());
    insert_nameable(r.concepts(), c);

    auto o(make_value_object(0, r.name(), ot));
    add_attribute(o, flags_.attributes_indexed(), flags_.types_parsed(), 1);

    model_concept(flags_.attributes_indexed(), o, c);
    insert_object(r, o);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_first_degree_concepts_model(const origin_types ot, const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));

    const auto ui(::make_builtin(unsigned_int));
    r.builtins().insert(std::make_pair(ui.name().id(), ui));

    concept c0(make_concept(0, r.name(), ot));
    add_attribute(c0, flags_.attributes_indexed(), flags_.types_parsed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name(), ot));
    add_attribute(c1, flags_.attributes_indexed(), flags_.types_parsed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    auto o0(make_value_object(0, r.name(), ot));
    model_concept(flags_.attributes_indexed(), o0, c0);
    insert_object(r, o0);

    auto o1(make_value_object(1, r.name(), ot));
    add_attribute(o1, flags_.attributes_indexed(), flags_.types_parsed(), 2);

    if (flags_.concepts_indexed())
        model_concept(flags_.attributes_indexed(), o1, c0);

    model_concept(flags_.attributes_indexed(), o1, c1);
    insert_object(r, o1);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_second_degree_concepts_model(const origin_types ot, const unsigned int n,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));

    const auto ui(::make_builtin(unsigned_int));
    r.builtins().insert(std::make_pair(ui.name().id(), ui));

    concept c0(make_concept(0, r.name(), ot));
    add_attribute(c0, flags_.attributes_indexed(), flags_.types_parsed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name(), ot));
    add_attribute(c1, flags_.attributes_indexed(), flags_.types_parsed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    concept c2(make_concept(2, r.name(), ot));
    add_attribute(c2, flags_.attributes_indexed(), flags_.types_parsed(), 2);

    if (flags_.concepts_indexed())
        c2.refines().push_back(c0.name());

    c2.refines().push_back(c1.name());
    insert_nameable(r.concepts(), c2);

    auto o0(make_value_object(0, r.name(), ot));
    model_concept(flags_.attributes_indexed(), o0, c0);
    insert_object(r, o0);

    auto o1(make_value_object(1, r.name(), ot));
    if (flags_.concepts_indexed())
        model_concept(flags_.attributes_indexed(), o1, c0);

    model_concept(flags_.attributes_indexed(), o1, c1);
    insert_object(r, o1);

    auto o2(make_value_object(2, r.name(), ot));
    add_attribute(o2, flags_.attributes_indexed(), flags_.types_parsed(), 3);
    if (flags_.concepts_indexed()) {
        model_concept(flags_.attributes_indexed(), o2, c0);
        model_concept(flags_.attributes_indexed(), o2, c1);
    }
    model_concept(flags_.attributes_indexed(), o2, c2);
    insert_object(r, o2);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_multiple_inheritance_concepts_model(const origin_types ot,
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));

    const auto ui(::make_builtin(unsigned_int));
    r.builtins().insert(std::make_pair(ui.name().id(), ui));

    concept c0(make_concept(0, r.name(), ot));
    add_attribute(c0, flags_.attributes_indexed(), flags_.types_parsed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name(), ot));
    add_attribute(c1, flags_.attributes_indexed(), flags_.types_parsed(), 1);
    insert_nameable(r.concepts(), c1);

    concept c2(make_concept(1, r.name(), ot));
    add_attribute(c2, flags_.attributes_indexed(), flags_.types_parsed(), 2);
    c2.refines().push_back(c0.name());
    c2.refines().push_back(c1.name());
    insert_nameable(r.concepts(), c2);

    auto o0(make_value_object(0, r.name(), ot));
    model_concept(flags_.attributes_indexed(), o0, c2);
    insert_object(r, o0);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_diamond_inheritance_concepts_model(const origin_types ot,
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));

    const auto ui(::make_builtin(unsigned_int));
    r.builtins().insert(std::make_pair(ui.name().id(), ui));

    concept c0(make_concept(0, r.name(), ot));
    add_attribute(c0, flags_.attributes_indexed(), flags_.types_parsed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name(), ot));
    add_attribute(c1, flags_.attributes_indexed(), flags_.types_parsed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    concept c2(make_concept(2, r.name(), ot));
    add_attribute(c2, flags_.attributes_indexed(), flags_.types_parsed(), 2);
    c2.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c2);

    concept c3(make_concept(3, r.name(), ot));
    add_attribute(c3, flags_.attributes_indexed(), flags_.types_parsed(), 3);
    if (flags_.concepts_indexed())
        c3.refines().push_back(c0.name());

    c3.refines().push_back(c1.name());
    c3.refines().push_back(c2.name());
    insert_nameable(r.concepts(), c3);

    auto o0(make_value_object(0, r.name(), ot));
    if (flags_.concepts_indexed()) {
        model_concept(flags_.attributes_indexed(), o0, c0);
        model_concept(flags_.attributes_indexed(), o0, c1);
        model_concept(flags_.attributes_indexed(), o0, c2);
    }
    model_concept(flags_.attributes_indexed(), o0, c3);
    insert_object(r, o0);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_object_with_parent_that_models_concept(const origin_types ot,
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));

    const auto ui(::make_builtin(unsigned_int));
    r.builtins().insert(std::make_pair(ui.name().id(), ui));

    concept c0(make_concept(0, r.name(), ot));
    add_attribute(c0, flags_.attributes_indexed(), flags_.types_parsed());
    insert_nameable(r.concepts(), c0);

    auto o0(make_value_object(0, r.name(), ot));
    model_concept(flags_.attributes_indexed(), o0, c0);

    insert_object(r, o0);

    auto o1(make_value_object(1, r.name(), ot));
    parent_to_child(flags_.attributes_indexed(), o0, o1);
    o0.is_parent(true);
    insert_object(r, o1);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_object_with_parent_that_models_a_refined_concept(const origin_types ot,
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));

    const auto ui(::make_builtin(unsigned_int));
    r.builtins().insert(std::make_pair(ui.name().id(), ui));

    concept c0(make_concept(0, r.name(), ot));
    add_attribute(c0, flags_.attributes_indexed(), flags_.types_parsed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name(), ot));
    add_attribute(c1, flags_.attributes_indexed(), flags_.types_parsed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    auto o0(make_value_object(0, r.name(), ot));

    model_concept(flags_.attributes_indexed(), o0, c1);
    if (flags_.concepts_indexed())
        model_concept(flags_.attributes_indexed(), o0, c0);

    insert_object(r, o0);

    auto o1(make_value_object(1, r.name(), ot));
    parent_to_child(flags_.attributes_indexed(), o0, o1);
    o0.is_parent(true);
    insert_object(r, o1);

    return r;
}

intermediate_model mock_intermediate_model_factory::
make_concept_that_refines_missing_concept(const origin_types ot,
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));
    concept c0(make_concept(0, r.name(), ot));
    concept c1(make_concept(1, r.name(), ot));
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_object_that_models_missing_concept(const origin_types ot,
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));

    const auto ui(::make_builtin(unsigned_int));
    r.builtins().insert(std::make_pair(ui.name().id(), ui));

    concept c0(make_concept(0, r.name(), ot));
    add_attribute(c0, flags_.attributes_indexed(), flags_.types_parsed());

    auto o0(make_value_object(0, r.name(), ot));

    model_concept(flags_.attributes_indexed(), o0, c0);
    insert_object(r, o0);
    return r;
}

intermediate_model mock_intermediate_model_factory::
make_object_that_models_concept_with_missing_parent(const origin_types ot,
    const unsigned int n, const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, n, add_model_module));

    const auto ui(::make_builtin(unsigned_int));
    r.builtins().insert(std::make_pair(ui.name().id(), ui));

    concept c0(make_concept(0, r.name(), ot));
    add_attribute(c0, flags_.attributes_indexed(), flags_.types_parsed());
    insert_nameable(r.concepts(), c0);

    auto o0(make_value_object(0, r.name(), ot));
    auto o1(make_value_object(1, r.name(), ot));
    parent_to_child(flags_.attributes_indexed(), o0, o1);
    o0.is_parent(true);

    model_concept(flags_.attributes_indexed(), o1, c0);
    insert_object(r, o1);

    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_both_transparent_and_opaque_associations(const origin_types ot,
    const bool add_model_module) const {
    intermediate_model r(make_empty_model(ot, 0, add_model_module));
    const auto mn(mock_model_name(0));
    auto o1(make_value_object(1, mn, ot));
    insert_object(r, o1);

    object o0(make_value_object(0, mn, ot));
    const auto vo(attribute_types::value_object);
    const auto tp(flags_.types_parsed());
    attribute p0(mock_attribute(o0.name(), tp, 0, vo, o1.name()));
    o0.local_attributes().push_back(p0);
    if (flags_.attributes_indexed())
        o0.all_attributes().push_back(p0);

    if (flags_.associations_indexed())
        o0.transparent_associations().push_back(o1.name());

    dogen::yarn::helpers::name_factory nf;
    object o2;
    o2.name(nf.build_element_name("boost", "shared_ptr"));
    o2.object_type(dogen::yarn::object_types::smart_pointer);
    insert_object(r, o2);

    const auto bsp(attribute_types::boost_shared_ptr);
    attribute p1(mock_attribute(o0.name(), tp, 1, bsp, o1.name()));
    o0.local_attributes().push_back(p1);
    if (flags_.attributes_indexed())
        o0.all_attributes().push_back(p1);

    if (flags_.associations_indexed())
        o0.opaque_associations().push_back(o1.name());

    object o3(make_value_object(3, mn, ot));
    insert_object(r, o3);

    attribute p2(mock_attribute(o0.name(), tp, 2, bsp, o3.name()));
    o0.local_attributes().push_back(p2);
    if (flags_.attributes_indexed())
        o0.all_attributes().push_back(p2);

    if (flags_.associations_indexed())
        o0.opaque_associations().push_back(o3.name());

    object o4;
    o4.name(nf.build_element_name("std", "string"));
    insert_object(r, o4);

    attribute p3(mock_attribute(o0.name(), tp, 3, vo, o4.name()));
    o0.local_attributes().push_back(p3);

    if (flags_.attributes_indexed())
        o0.all_attributes().push_back(p3);

    if (flags_.associations_indexed())
        o0.transparent_associations().push_back(o4.name());

    insert_object(r, o0);
    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_attribute(const origin_types ot, const object_types objt,
    const attribute_types pt, const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o1(make_value_object(1, mn, ot));

    object o0;
    if (objt == object_types::value_object)
        o0 = make_value_object(0, mn, ot);
    else {
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(helpers::building_error(invalid_object_type));
    }

    const auto tp(flags_.types_parsed());
    attribute p(mock_attribute(o0.name(), tp, 0, pt, o1.name()));
    o0.local_attributes().push_back(p);
    if (flags_.attributes_indexed())
        o0.all_attributes().push_back(p);

    dogen::yarn::helpers::name_factory nf;
    intermediate_model r(make_empty_model(ot, 0, add_model_module));
    if (pt == attribute_types::value_object ||
        pt == attribute_types::boost_shared_ptr) {
        insert_object(r, o1);

        if (flags_.associations_indexed())
            o0.transparent_associations().push_back(o1.name());
    }

    if (pt == attribute_types::unsigned_int || pt == attribute_types::boolean) {
        builtin ui;
        ui.name(p.parsed_type().current());
        insert_nameable(r.builtins(), ui);

        if (flags_.associations_indexed())
            o0.transparent_associations().push_back(ui.name());

    } else if (pt == attribute_types::boost_shared_ptr) {
        object o2;
        o2.name(nf.build_element_name("boost", "shared_ptr"));
        o2.object_type(dogen::yarn::object_types::smart_pointer);
        insert_object(r, o2);

        if (flags_.associations_indexed())
            o0.opaque_associations().push_back(o2.name());

    } else if (pt == attribute_types::std_pair) {
        const auto b(::make_builtin(boolean));
        r.builtins().insert(std::make_pair(b.name().id(), b));

        if (flags_.associations_indexed())
            o0.transparent_associations().push_back(b.name());

        object o2;
        o2.name(nf.build_element_name("std", "pair"));

        if (flags_.associations_indexed())
            o0.transparent_associations().push_back(o2.name());

        insert_object(r, o2);
    } else if (pt == attribute_types::boost_variant) {
        const auto b(::make_builtin(boolean));
        r.builtins().insert(std::make_pair(b.name().id(), b));

        if (flags_.associations_indexed())
            o0.transparent_associations().push_back(b.name());

        const auto ui(::make_builtin(unsigned_int));
        r.builtins().insert(std::make_pair(ui.name().id(), ui));

        if (flags_.associations_indexed())
            o0.transparent_associations().push_back(ui.name());

        object o2;
        o2.name(nf.build_element_name("boost", "variant"));
        insert_object(r, o2);

        if (flags_.associations_indexed())
            o0.transparent_associations().push_back(o2.name());

    } else if (pt == attribute_types::std_string) {
        object o2;
        o2.name(nf.build_element_name("std", "string"));
        insert_object(r, o2);

        if (flags_.associations_indexed())
            o0.transparent_associations().push_back(o2.name());
    }
    insert_object(r, o0);
    return r;
}

std::array<intermediate_model, 2>
mock_intermediate_model_factory::object_with_attribute_type_in_different_model(
    const bool add_model_module) const {
    const auto tg(origin_types::target);
    auto o0(make_value_object(0, tg));

    const auto npr(origin_types::non_proxy_reference);
    auto o1(make_value_object(1, npr));

    add_attribute(o0, flags_.attributes_indexed(), flags_.types_parsed(),
        0, attribute_types::value_object, o1.name());

    intermediate_model m0(make_empty_model(tg, 0, add_model_module));
    insert_object(m0, o0);
    handle_model_module(add_model_module, m0);

    intermediate_model m1(make_empty_model(npr, 1, add_model_module));
    insert_object(m1, o1);
    handle_model_module(add_model_module, m1);

    return std::array<intermediate_model, 2> {{ m0, m1 }};
}

intermediate_model mock_intermediate_model_factory::
object_with_missing_attribute_type(const origin_types ot,
    const bool add_model_module) const {
    auto o0(make_value_object(0, origin_types::target));
    auto o1(make_value_object(1, origin_types::non_proxy_reference));

    add_attribute(o0, flags_.attributes_indexed(), flags_.types_parsed(), 0,
        attribute_types::value_object, o1.name());

    if (flags_.associations_indexed())
        o0.transparent_associations().push_back(o1.name());

    intermediate_model r(make_empty_model(ot, 0, add_model_module));
    insert_object(r, o0);

    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_parent_in_the_same_model(const origin_types ot,
    const bool has_attribute, const bool add_model_module) const {
    const auto mn(mock_model_name(0));

    auto r(make_empty_model(ot, 0, add_model_module));
    if (has_attribute) {
        const auto ui(::make_builtin(unsigned_int));
        r.builtins().insert(std::make_pair(ui.name().id(), ui));
    }

    auto o0(make_value_object(0, mn, ot));
    if (has_attribute)
        add_attribute(o0, flags_.attributes_indexed(), flags_.types_parsed());


    auto o1(make_value_object(1, mn, ot));
    if (has_attribute) {
        add_attribute(o1, flags_.attributes_indexed(),
            flags_.types_parsed(), 1);
    }

    parent_to_child(flags_.attributes_indexed(), o1, o0);
    insert_object(r, o0);
    insert_object(r, o1);

    o1.is_parent(true);
    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_missing_parent_in_the_same_model(const origin_types ot,
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o0(make_value_object(0, mn, ot));
    auto o1(make_value_object(1, mn, ot));
    o1.is_parent(true);
    parent_to_child(flags_.attributes_indexed(), o1, o0);
    auto r(make_empty_model(ot, 0, add_model_module));
    insert_object(r, o1);

    return r;
}

std::array<intermediate_model, 2> mock_intermediate_model_factory::
object_with_parent_in_different_models(const bool add_model_module) const {
    const auto tg(origin_types::target);
    auto o0(make_value_object(0, tg));

    const auto npr(origin_types::non_proxy_reference);
    auto o1(make_value_object(1, npr));
    parent_to_child(flags_.attributes_indexed(), o1, o0);
    o1.is_parent(true);

    auto m0(make_empty_model(tg, 0, add_model_module));
    insert_object(m0, o0);

    auto m1(make_empty_model(npr, 1, add_model_module));
    insert_object(m1, o1);

    return std::array<intermediate_model, 2> {{ m0, m1 }};
}

intermediate_model mock_intermediate_model_factory::
object_with_three_children_in_same_model(const origin_types ot,
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o0(make_value_object(0, mn, ot));
    auto o1(make_value_object(1, mn, ot));
    auto o2(make_value_object(2, mn, ot));
    auto o3(make_value_object(3, mn, ot));

    parent_to_child(flags_.attributes_indexed(), o3, o0);
    parent_to_child(flags_.attributes_indexed(), o3, o1);
    parent_to_child(flags_.attributes_indexed(), o3, o2);

    o3.is_parent(true);

    auto r(make_empty_model(ot, 0, add_model_module));
    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    insert_object(r, o3);
    r.name(mn);
    return r;
}

intermediate_model mock_intermediate_model_factory::
object_with_third_degree_parent_in_same_model(const origin_types ot,
    const bool has_attribute, const bool add_model_module) const {
    const auto mn(mock_model_name(0));

    auto r(make_empty_model(ot, 0, add_model_module));
    if (has_attribute) {
        const auto ui(::make_builtin(unsigned_int));
        r.builtins().insert(std::make_pair(ui.name().id(), ui));
    }

    auto o3(make_value_object(3, mn, ot));
    if (has_attribute) {
        add_attribute(o3, flags_.attributes_indexed(),
            flags_.types_parsed(), 3);
    }

    auto o2(make_value_object(2, mn, ot));
    if (has_attribute) {
        add_attribute(o2, flags_.attributes_indexed(),
            flags_.types_parsed(), 2);
    }

    parent_to_child(flags_.attributes_indexed(), o3, o2, o3, !add_leaf);

    auto o1(make_value_object(1, mn, ot));
    if (has_attribute) {
        add_attribute(o1, flags_.attributes_indexed(),
            flags_.types_parsed(), 1);
    }
    parent_to_child(flags_.attributes_indexed(), o2, o1, o3, !add_leaf);

    auto o0(make_value_object(0, mn, ot));
    if (has_attribute)
        add_attribute(o0, flags_.attributes_indexed(), flags_.types_parsed());

    parent_to_child(flags_.attributes_indexed(), o1, o0, o3, !add_leaf);

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
object_with_third_degree_parent_missing(const origin_types ot,
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o0(make_value_object(0, mn, ot));
    auto o1(make_value_object(1, mn, ot));
    auto o2(make_value_object(2, mn, ot));
    auto o3(make_value_object(3, mn, ot));

    parent_to_child(flags_.attributes_indexed(), o1, o0, o3, !add_leaf);
    parent_to_child(flags_.attributes_indexed(), o2, o1, o3, !add_leaf);
    parent_to_child(flags_.attributes_indexed(), o3, o2, o3, !add_leaf);

    o1.is_parent(true);
    o1.leaves().push_back(o0.name());

    o2.is_parent(true);
    o2.leaves().push_back(o0.name());

    o3.is_parent(true);
    o3.leaves().push_back(o0.name());

    auto r(make_empty_model(ot, 0, add_model_module));
    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    r.name(mn);
    return r;
}

std::array<intermediate_model, 4> mock_intermediate_model_factory::
object_with_third_degree_parent_in_different_models(
    const bool add_model_module) const {
    const auto npr(origin_types::non_proxy_reference);
    auto o0(make_value_object(0, origin_types::target));
    auto o1(make_value_object(1, npr));
    auto o2(make_value_object(2, npr));
    auto o3(make_value_object(3, npr));

    parent_to_child(flags_.attributes_indexed(), o1, o0, o3, !add_leaf);
    parent_to_child(flags_.attributes_indexed(), o2, o1, o3, !add_leaf);
    parent_to_child(flags_.attributes_indexed(), o3, o2, o3, !add_leaf);

    o1.is_parent(true);
    o1.leaves().push_back(o0.name());

    o2.is_parent(true);
    o2.leaves().push_back(o0.name());

    o3.is_parent(true);
    o3.leaves().push_back(o0.name());

    auto m0(make_empty_model(origin_types::target, 0, add_model_module));
    insert_object(m0, o0);

    auto m1(make_empty_model(npr, 1, add_model_module));
    insert_object(m1, o1);

    auto m2(make_empty_model(npr, 2, add_model_module));
    insert_object(m2, o2);

    auto m3(make_empty_model(npr, 3, add_model_module));
    insert_object(m3, o3);

    return std::array<intermediate_model, 4>{{ m0, m1, m2, m3 }};
}

std::array<intermediate_model, 4> mock_intermediate_model_factory::
object_with_missing_third_degree_parent_in_different_models(
    const bool add_model_module) const {
    const auto npr(origin_types::non_proxy_reference);
    auto o0(make_value_object(0, origin_types::target));
    auto o1(make_value_object(1, npr));
    auto o2(make_value_object(2, npr));
    auto o3(make_value_object(3, npr));

    parent_to_child(flags_.attributes_indexed(), o1, o0, o3, !add_leaf);
    parent_to_child(flags_.attributes_indexed(), o2, o1, o3, !add_leaf);
    parent_to_child(flags_.attributes_indexed(), o3, o2, o3, !add_leaf);

    o1.is_parent(true);
    o1.leaves().push_back(o0.name());

    o2.is_parent(true);
    o2.leaves().push_back(o0.name());

    o3.is_parent(true);
    o3.leaves().push_back(o0.name());

    auto m0(make_empty_model(origin_types::target, 0, add_model_module));
    insert_object(m0, o0);

    auto m1(make_empty_model(npr, 1, add_model_module));
    insert_object(m1, o1);

    auto m2(make_empty_model(npr, 2, add_model_module));
    insert_object(m2, o2);

    return std::array<intermediate_model, 4>{{ m0, m1, m2 }};
}

intermediate_model mock_intermediate_model_factory::
object_with_group_of_attributes_of_different_types(const origin_types ot,
    const bool repeat_group, const bool add_model_module) const {
    auto r(make_empty_model(ot, 0, add_model_module));
    const auto mn(r.name());

    auto o0(make_value_object(0, mn, ot));
    const auto lambda([&](const attribute& p) {
            o0.local_attributes().push_back(p);
            if (flags_.attributes_indexed())
                o0.all_attributes().push_back(p);
        });

    auto o1(make_value_object(1, mn, ot));
    const auto vo(attribute_types::value_object);
    const auto tp(flags_.types_parsed());
    auto p0(mock_attribute(o0.name(), tp, 0, vo, o1.name()));
    lambda(p0);
    insert_object(r, o1);

    auto p1(mock_attribute(o0.name(), tp, 1));
    lambda(p1);
    builtin ui;
    ui.name(p1.parsed_type().current());
    insert_nameable(r.builtins(), ui);

    auto o3(make_value_object(3, mn, ot));
    insert_object(r, o3);
    const auto bsp(attribute_types::boost_shared_ptr);
    auto p2(mock_attribute(o0.name(), tp, 2, bsp, o3.name()));
    lambda(p2);

    object o2;
    dogen::yarn::helpers::name_factory nf;
    o2.name(nf.build_element_name("boost", "shared_ptr"));
    o2.object_type(dogen::yarn::object_types::smart_pointer);
    insert_object(r, o2);

    auto o4(make_value_object(4, mn, ot));
    insert_object(r, o4);
    auto p3(mock_attribute(o0.name(), tp, 3, vo, o4.name()));
    lambda(p3);

    if (repeat_group) {
        auto p4(mock_attribute(o0.name(), tp, 4, vo, o1.name()));
        lambda(p4);

        auto p5(mock_attribute(o0.name(), tp, 5));
        lambda(p5);

        auto p6(mock_attribute(o0.name(), tp, 6, bsp, o3.name()));
        lambda(p6);

        auto p7(mock_attribute(o0.name(), tp, 7, vo, o4.name()));
        lambda(p7);
    }
    insert_object(r, o0);
    return r;
}

} } }
