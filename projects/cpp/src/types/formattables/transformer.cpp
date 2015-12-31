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
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/utility/io/shared_ptr_io.hpp"
#include "dogen/yarn/io/object_types_io.hpp"
#include "dogen/cpp/io/formattables/formattable_io.hpp"
#include "dogen/cpp/types/formattables/name_builder.hpp"
#include "dogen/cpp/types/formattables/transformation_error.hpp"
#include "dogen/cpp/types/formattables/transformer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.transformer"));

const std::string empty;
const std::string dot(".");
const std::string comma(",");
const std::string space(" ");
const std::string less_than("<");
const std::string more_than(">");
const std::string separator("_");
const std::string extension("HPP");
const std::string namespace_separator("::");

const std::string bool_type("bool");
const std::string string_type("std::string");
const std::string char_type("char");
const std::string uchar_type("unsigned char");
const std::string short_type("short");
const std::string ushort_type("unsigned short");
const std::string int_type("int");
const std::string uint_type("unsigned int");
const std::string long_type("long");
const std::string ulong_type("unsigned long");
const std::string long_long_type("long long");
const std::string ulong_long_type("unsigned long long");
const std::string double_type("double");
const std::string float_type("float");
const std::string optional_type("boost::optional");
const std::string variant_type("boost::variant");
const std::string filesystem_path_type("boost::filesystem::path");
const std::string gregorian_date_type("boost::gregorian::date");
const std::string ptime_type("boost::posix_time::ptime");
const std::string time_duration_type("boost::posix_time::time_duration");
const std::string ptree_type("boost::property_tree::ptree");
const std::string pair_type("std::pair");
const std::string visitor_comments("Accept visits for type ");

const std::string int8_t_type("std::int8_t");
const std::string int16_t_type("std::int16_t");
const std::string int32_t_type("std::int32_t");
const std::string int64_t_type("std::int64_t");
const std::string uint8_t_type("std::uint8_t");
const std::string uint16_t_type("std::uint16_t");
const std::string uint32_t_type("std::uint32_t");
const std::string uint64_t_type("std::uint64_t");

const std::string unsupported_object_type("Object type is not supported: ");
const std::string concept_not_found("Concept not found in concept container: ");
const std::string parent_class_info_not_found(
    "Type has a parent but no parent class info found: ");
const std::string too_many_parents(
    "Type has more than one parent but multiple inheritance not supported: ");
const std::string type_has_no_file_properties(
    "Could not find file properties for type: ");
const std::string type_has_no_inclusion_dependencies(
    "Could not find inclusion dependencies for type: ");
const std::string type_has_no_inclusion("Could not find inclusion for type: ");
const std::string no_visitees("Visitor is not visiting any types: ");
const std::string formatter_properties_missing(
    "Could not find formatter properties for type: ");
const std::string settings_bundle_missing(
    "Could not find settings bundle for type: ");
const std::string cast_failure("Failed to cast type: ");

bool is_char_like(const std::string& type_name) {
    return
        type_name == char_type || type_name == uchar_type ||
        type_name == int8_t_type || type_name == uint8_t_type;
}

bool is_string_like(const std::string& type_name) {
    return is_char_like(type_name) || type_name == string_type;
}

bool is_optional_like(const std::string& type_name) {
    return type_name == optional_type;
}

bool is_pair(const std::string& type_name) {
    return type_name == pair_type;
}

bool is_filesystem_path(const std::string& type_name) {
    return type_name == filesystem_path_type;
}

bool is_gregorian_date(const std::string& type_name) {
    return type_name == gregorian_date_type;
}

bool is_ptime(const std::string& type_name) {
    return type_name == ptime_type;
}

bool is_time_duration(const std::string& type_name) {
    return type_name == time_duration_type;
}

bool is_ptree(const std::string& type_name) {
    return type_name == ptree_type;
}

bool is_variant_like(const std::string& type_name) {
    return type_name == variant_type;
}

bool is_int_like(const std::string& type_name) {
    return
        type_name == short_type ||
        type_name == ushort_type ||
        type_name == int_type ||
        type_name == uint_type ||
        type_name == long_type ||
        type_name == ulong_type ||
        type_name == long_long_type ||
        type_name == ulong_long_type ||
        type_name == double_type ||
        type_name == float_type ||
        type_name == int16_t_type ||
        type_name == int32_t_type ||
        type_name == int64_t_type ||
        type_name == uint16_t_type ||
        type_name == uint32_t_type ||
        type_name == uint64_t_type;
}

bool requires_stream_manipulators(const std::string type_name) {
    return
        type_name == bool_type ||
        type_name == double_type ||
        type_name == float_type;
}

bool requires_manual_move_constructor(const std::string type_name) {
    return
        type_name == "optional" ||
        type_name == "path" ||
        type_name == "variant" ||
        type_name == "time_duration" ||
        type_name == "ptree";
}

}

namespace dogen {
namespace cpp {
namespace formattables {

template<typename YarnConcreteElement>
inline const YarnConcreteElement& convert(const yarn::element& e) {
    auto ptr(dynamic_cast<YarnConcreteElement const*>(&e));
    if (!ptr) {
        const auto qn(e.name().qualified());
        BOOST_LOG_SEV(lg, error) << cast_failure << qn;
        BOOST_THROW_EXCEPTION(transformation_error(cast_failure + qn));
    }
    return *ptr;
}

template<typename YarnConcreteElement>
inline bool is(const boost::shared_ptr<yarn::element> e) {
    auto ptr(boost::dynamic_pointer_cast<YarnConcreteElement>(e));
    return ptr != nullptr;
}

template<typename YarnConcreteElement>
inline bool is(const yarn::model& m, const yarn::name& n) {
    const auto i(m.elements().find(n.qualified()));
    if (i == m.elements().end())
        return false;
    return is<YarnConcreteElement>(i->second);
}

transformer::transformer(const settings::opaque_settings_builder& osb,
    const settings::bundle_repository& brp,
    const formatter_properties_repository& frp,
    const yarn::model& m)
    : opaque_settings_builder_(osb), bundle_repository_(brp),
      formatter_properties_repository_(frp), model_(m) {}

void transformer::
populate_formattable_properties(const yarn::name& n, formattable& f) const {
    f.identity(n.qualified());
}

void transformer::populate_entity_properties(const yarn::name& n,
    const std::string& documentation, entity& e) const {

    populate_formattable_properties(n, e);

    e.name(n.simple());
    e.documentation(documentation);

    const auto& fpn(formatter_properties_repository_.
        formatter_properties_by_name());
    const auto i(fpn.find(n));
    if (i == fpn.end()) {
        const auto qn(n.qualified());
        BOOST_LOG_SEV(lg, error) << formatter_properties_missing << qn;
        BOOST_THROW_EXCEPTION(
            transformation_error(formatter_properties_missing + qn));
    }
    e.formatter_properties(i->second);

    name_builder b;
    e.namespaces(b.namespace_list(model_, n));

    const auto& bn(bundle_repository_.bundles_by_name());
    const auto j(bn.find(n));
    if (j == bn.end()) {
        const auto qn(n.qualified());
        BOOST_LOG_SEV(lg, error) << settings_bundle_missing << qn;
        BOOST_THROW_EXCEPTION(
            transformation_error(settings_bundle_missing + qn));
    }
    e.settings(j->second);

    std::list<std::string> ns(e.namespaces());
    ns.push_back(e.name());

    using boost::join;
    e.qualified_name(join(ns, namespace_separator));
}

void transformer::to_nested_type_info(const yarn::nested_name& nn,
    nested_type_info& nti, std::string& complete_name,
    bool& requires_stream_manipulators) const {

    const auto n(nn.parent());
    name_builder b;
    const auto qualified_name(b.qualified_name(model_, n));
    nti.name(qualified_name);
    nti.namespaces(b.namespace_list(model_, n));
    nti.is_enumeration(is<yarn::enumeration>(model_, n));
    nti.is_primitive(is<yarn::primitive>(model_, n));

    if (nti.is_primitive()) {
        if (::requires_stream_manipulators(nti.name()))
            requires_stream_manipulators = true;

        nti.is_char_like(is_char_like(nti.name()));
        nti.is_int_like(is_int_like(nti.name()));
    }
    nti.is_string_like(is_string_like(nti.name()));
    nti.is_optional_like(is_optional_like(nti.name()));
    nti.is_pair(is_pair(nti.name()));
    nti.is_variant_like(is_variant_like(nti.name()));
    nti.is_filesystem_path(is_filesystem_path(nti.name()));
    nti.is_date(is_gregorian_date(nti.name()));
    nti.is_ptime(is_ptime(nti.name()));
    nti.is_time_duration(is_time_duration(nti.name()));
    nti.is_ptree(is_ptree(nti.name()));

    const auto k(model_.elements().find(n.qualified()));
    if (k != model_.elements().end() && is<yarn::object>(k->second)) {
        const auto& o(convert<yarn::object>(*k->second));
        const auto ot(o.object_type());
        using yarn::object_types;
        nti.is_sequence_container(ot == object_types::sequence_container);
        nti.is_associative_container(ot == object_types::ordered_container ||
            ot == object_types::hash_container);
        nti.is_smart_pointer(ot == object_types::smart_pointer);
    }

    const auto nn_children(nn.children());

    std::string my_complete_name(nti.name());
    auto lambda([&](char c) {
            if (!nn_children.empty()) {
                if (my_complete_name[my_complete_name.length() - 1] == c)
                    my_complete_name += " ";
                my_complete_name += c;
            }
        });

    std::list<nested_type_info> children;
    lambda('<');
    bool is_first(true);
    for (const auto c : nn.children()) {
        if (!is_first)
            my_complete_name += ", ";

        nested_type_info ci;
        to_nested_type_info(c, ci, my_complete_name,
            requires_stream_manipulators);
        children.push_back(ci);
        is_first = false;
    }
    lambda('>');

    nti.identifiable_name(b.identifiable_name(qualified_name));
    nti.complete_identifiable_name(b.identifiable_name(my_complete_name));
    nti.complete_name(my_complete_name);
    nti.children(children);
    complete_name += my_complete_name;
}

std::tuple<property_info, bool, bool, bool>
transformer::to_property_info(const yarn::property p, const bool is_immutable,
    const bool is_fluent) const {

    property_info pi;
    pi.name(p.name().simple());
    pi.documentation(p.documentation());
    pi.is_immutable(is_immutable);
    pi.is_fluent(is_fluent);

    bool requires_stream_manipulators(false);
    bool requires_manual_move_constructor(false);
    bool requires_manual_default_constructor(false);

    nested_type_info nti;
    std::string complete_name;
    const auto t(p.type());
    if (::requires_manual_move_constructor(t.parent().simple()))
        requires_manual_move_constructor = true;

    to_nested_type_info(t, nti, complete_name, requires_stream_manipulators);
    if (nti.is_primitive()) {
        requires_manual_default_constructor = true;
    } else if (nti.is_enumeration())
        requires_manual_default_constructor = true;

    nti.complete_name(complete_name);
    pi.type(nti);
    pi.opaque_settings(opaque_settings_builder_.build(p.extensions()));

    return std::make_tuple(pi,
        requires_stream_manipulators,
        requires_manual_move_constructor,
        requires_manual_default_constructor);
}

enumerator_info
transformer::to_enumerator_info(const yarn::enumerator& e) const {
    enumerator_info r;
    r.name(e.name());
    r.value(e.value());
    r.documentation(e.documentation());
    return r;
}

std::shared_ptr<enum_info>
transformer::to_enum_info(const yarn::enumeration& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: "
                             << e.name().qualified();

    auto r(std::make_shared<enum_info>());
    populate_entity_properties(e.name(), e.documentation(), *r);

    // FIXME: Yarn is not setting this properly.
    // r->type(e.underlying_type().simple_name());
    r->type("unsigned int");

    for (const auto& en : e.enumerators())
        r->enumerators().push_back(to_enumerator_info(en));

    BOOST_LOG_SEV(lg, debug) << "Transformed enumeration.";
    return r;
}

std::shared_ptr<namespace_info> transformer::
to_namespace_info(const yarn::module& m) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming module: "
                             << m.name().qualified();

    auto r(std::make_shared<namespace_info>());
    populate_entity_properties(m.name(), m.documentation(), *r);

    BOOST_LOG_SEV(lg, debug) << "Transformed module.";
    return r;
}

std::shared_ptr<exception_info>
transformer::to_exception_info(const yarn::exception& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exception: "
                             << e.name().qualified();

    auto r(std::make_shared<exception_info>());
    populate_entity_properties(e.name(), e.documentation(), *r);

    BOOST_LOG_SEV(lg, debug) << "Transformed exception.";
    return r;
}

std::shared_ptr<class_info>
transformer::to_class_info(const yarn::object& o) const {
    auto r(std::make_shared<class_info>());
    populate_entity_properties(o.name(), o.documentation(), *r);

    r->is_immutable(o.is_immutable());
    r->is_visitable(o.is_visitable());
    r->is_parent(o.is_parent());
    r->is_final(o.is_final());
    r->generation_type(o.generation_type());

    name_builder b;
    for (const auto& n : o.parents()) {
        parent_info pi;
        pi.name(n.simple());
        pi.namespaces(b.namespace_list(model_, n));

        std::list<std::string> ns(pi.namespaces());
        ns.push_back(pi.name());

        using boost::join;
        pi.qualified_name(join(ns, namespace_separator));

        const auto j(o.inherited_properties().find(n));
        if (j != o.inherited_properties().end()) {
            for (const auto& prop : j->second) {
                const auto tuple(to_property_info(
                        prop, o.is_immutable(), o.is_fluent()));
                pi.properties().push_back(std::get<0>(tuple));
            }
        }
        r->parents().push_back(pi);
    }

    if (!o.root_parents().empty()) {
        if (o.root_parents().size() > 1) {
            const auto qn(o.name().qualified());
            BOOST_LOG_SEV(lg, error) << too_many_parents << qn;
            BOOST_THROW_EXCEPTION(transformation_error(too_many_parents + qn));
        }

        const auto opn(o.root_parents().front());
        std::list<std::string> ns(b.namespace_list(model_, opn));
        ns.push_back(opn.simple());

        using boost::join;
        r->root_parent_name_qualified(join(ns, namespace_separator));
        r->root_parent_name(opn.simple());
        r->is_root_parent_visitable(o.is_root_parent_visitable());
    }

    for (const auto& prop : o.all_properties()) {
        const auto tuple(to_property_info(
                prop, o.is_immutable(), o.is_fluent()));
        r->all_properties().push_back(std::get<0>(tuple));
    }

    for (const auto& prop : o.local_properties()) {
        const auto tuple(to_property_info(
                prop, o.is_immutable(), o.is_fluent()));

        r->properties().push_back(std::get<0>(tuple));

        if (std::get<1>(tuple))
            r->requires_stream_manipulators(true);

        if (std::get<2>(tuple))
            r->requires_manual_move_constructor(true);

        if (std::get<3>(tuple))
            r->requires_manual_default_constructor(true);
    }

    if (r->all_properties().empty())
        r->requires_manual_move_constructor(false);

    for (const auto l : o.leaves())
        r->leaves().push_back(b.qualified_name(model_, l));

    return r;
}

std::shared_ptr<visitor_info>
transformer::to_visitor_info(const yarn::visitor& v) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming visitor: "
                             << v.name().qualified();

    auto r(std::make_shared<visitor_info>());
    populate_entity_properties(v.name(), v.documentation(), *r);

    if (v.visits().empty()) {
        const auto& qn(v.name().qualified());
        BOOST_LOG_SEV(lg, error) << no_visitees << qn;
        BOOST_THROW_EXCEPTION(transformation_error(no_visitees + qn));
    }

    name_builder b;
    for (const auto n : v.visits()) {
        cpp::formattables::visited_type_info vti;
        vti.qualified_name(b.qualified_name(model_, n));
        vti.name(n.simple());
        vti.documentation(visitor_comments + vti.qualified_name());
        r->types().push_back(vti);
    }

    BOOST_LOG_SEV(lg, debug) << "Transformed visitor.";
    return r;
}

std::shared_ptr<forward_declarations_info> transformer::
to_forward_declarations_info(const yarn::object& o) const {
    auto r(std::make_shared<forward_declarations_info>());
    populate_entity_properties(o.name(), o.documentation(), *r);
    return r;
}

std::shared_ptr<forward_declarations_info> transformer::
to_forward_declarations_info(const yarn::visitor& v) const {
    auto r(std::make_shared<forward_declarations_info>());
    populate_entity_properties(v.name(), v.documentation(), *r);
    return r;
}

std::shared_ptr<forward_declarations_info> transformer::
to_forward_declarations_info(const yarn::exception& e) const {
    auto r(std::make_shared<forward_declarations_info>());
    r->is_exception(true);
    populate_entity_properties(e.name(), e.documentation(), *r);
    return r;
}

std::shared_ptr<forward_declarations_info> transformer::
to_forward_declarations_info(const yarn::enumeration& e) const {
    auto r(std::make_shared<forward_declarations_info>());
    populate_entity_properties(e.name(), e.documentation(), *r);
    r->is_enum(true);
    r->enum_type("unsigned int"); // FIXME
    return r;
}

std::forward_list<std::shared_ptr<formattable> >
transformer::transform(const yarn::enumeration& e) const {
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(to_enum_info(e));
    r.push_front(to_forward_declarations_info(e));
    return r;
}

std::forward_list<std::shared_ptr<formattable> > transformer::
transform(const yarn::module& m) const {
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(to_namespace_info(m));
    return r;
}

std::forward_list<std::shared_ptr<formattable> >
transformer::transform(const yarn::concept& /*c*/) const {
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(std::make_shared<concept_info>());
    return r;
}

std::forward_list<std::shared_ptr<formattable> >
transformer::transform(const yarn::primitive& /*p*/) const {
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(std::make_shared<primitive_info>());
    return r;
}

std::forward_list<std::shared_ptr<formattable> > transformer::
transform(const yarn::object& o) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming object: "
                             << o.name().qualified();

    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(to_forward_declarations_info(o));

    switch(o.object_type()) {
    case yarn::object_types::user_defined_value_object:
    case yarn::object_types::user_defined_service:
        r.push_front(to_class_info(o));
        break;
    default: {
        const auto qn(o.name().qualified());
        BOOST_LOG_SEV(lg, error) << unsupported_object_type << o.object_type()
                                 << " name: " << qn;
        BOOST_THROW_EXCEPTION(transformation_error(unsupported_object_type +
                boost::lexical_cast<std::string>(o.object_type())));
    } };

    for (const auto& i : r)
        BOOST_LOG_SEV(lg, debug) << "Transformed object: " << *i;
    return r;
}

std::forward_list<std::shared_ptr<formattable> >
transformer::transform(const yarn::exception& e) const {
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(to_exception_info(e));
    r.push_front(to_forward_declarations_info(e));
    return r;
}

std::forward_list<std::shared_ptr<formattable> >
transformer::transform(const yarn::visitor& v) const {
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(to_visitor_info(v));

    // FIXME: disable visitor forward declarations for now because we
    // are generating them for serialisation, where it does not make
    // any sense.
    // r.push_front(to_forward_declarations_info(v));
    return r;
}

} } }
