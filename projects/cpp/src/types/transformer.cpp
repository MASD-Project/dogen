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
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/types/transformation_error.hpp"
#include "dogen/cpp/types/transformer.hpp"

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
const std::string visitor_postfix("_visitor");

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
const std::string pair_type("std::pair");

const std::string int8_t_type("std::int8_t");
const std::string int16_t_type("std::int16_t");
const std::string int32_t_type("std::int32_t");
const std::string int64_t_type("std::int64_t");
const std::string uint8_t_type("std::uint8_t");
const std::string uint16_t_type("std::uint16_t");
const std::string uint32_t_type("std::uint32_t");
const std::string uint64_t_type("std::uint64_t");

const std::string pod_not_found("pod not found in pod container: ");
const std::string concept_not_found("Concept not found in concept container: ");
const std::string parent_info_not_supplied(
    "Type has a parent but no parent info supplied: ");
const std::string parent_info_supplied(
    "Type does not have a parent parent info was supplied: ");
const std::string non_visitable_pod_supplied("Pod is non-visitable: ");

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
        type_name == "variant";
}

std::string to_identifiable_name(const std::string n) {
    std::string r(n);

    boost::replace_all(r, namespace_separator, separator);
    boost::replace_all(r, space, separator);
    boost::replace_all(r, comma, empty);
    boost::replace_all(r, less_than, separator);
    boost::replace_all(r, more_than, empty);

    return r;
}

}

namespace dogen {
namespace cpp {

transformer::transformer(const sml::model& m) : model_(m) { }

void transformer::properties_for_concept(const sml::qname& qn,
    std::list<sml::property>& properties,
    std::unordered_set<sml::qname>& processed_qnames) const {

    if (processed_qnames.find(qn) != processed_qnames.end())
        return;

    processed_qnames.insert(qn);
    const auto i(model_.concepts().find(qn));
    if (i == model_.concepts().end()) {
        BOOST_LOG_SEV(lg, error) << concept_not_found << qn.type_name();
        BOOST_THROW_EXCEPTION(transformation_error(concept_not_found +
                qn.type_name()));
    }

    for (const auto& c : i->second.refines())
        properties_for_concept(c, properties, processed_qnames);

    const auto& props(i->second.properties());
    properties.insert(properties.end(), props.begin(), props.end());
}

std::string
transformer::transform_into_qualified_name(const sml::qname& qn) const {
    std::list<std::string> l(transform_into_namespace_list(qn));
    l.push_back(qn.type_name());

    using boost::algorithm::join;
    std::string r(join(l, namespace_separator));
    return r;
}

std::list<std::string>
transformer::transform_into_namespace_list(const sml::qname& qn) const {
    std::list<std::string> r(qn.external_module_path());

    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    const std::list<std::string> pp(qn.module_path());
    r.insert(r.end(), pp.begin(), pp.end());

    if (qn.meta_type() == sml::meta_types::module)
        r.push_back(qn.type_name());

    return r;
}

enumerator_info
transformer::transform_enumerator(const sml::property& e) const {
    enumerator_info r;
    r.name(e.name());
    r.value(e.default_value());
    r.documentation(e.documentation());
    return r;
}

enum_info transformer::transform_enumeration(const sml::value& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: " << e.name();

    enum_info r;
    r.name(e.name().type_name());
    r.namespaces(transform_into_namespace_list(e.name()));
    r.documentation(e.documentation());

    // FIXME: check the type of the first property
    for (const auto& en : e.properties())
        r.enumerators().push_back(transform_enumerator(en));

    BOOST_LOG_SEV(lg, debug) << "Transformed enumeration: " << e.name();

    return r;
}

exception_info transformer::transform_exception(const sml::value& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exception: " << e.name();

    exception_info r;
    r.name(e.name().type_name());
    r.namespaces(transform_into_namespace_list(e.name()));
    r.documentation(e.documentation());

    BOOST_LOG_SEV(lg, debug) << "Transformed exception: " << e.name();

    return r;
}

namespace_info transformer::transform(const sml::module& p) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming module: " << p.name();

    namespace_info r;
    r.documentation(p.documentation());
    r.namespaces(transform_into_namespace_list(p.name()));

    BOOST_LOG_SEV(lg, debug) << "Transformed module: " << p.name();

    return r;
}

namespace_info transformer::transform_model_into_namespace() const {
    const std::string n(model_.name());
    BOOST_LOG_SEV(lg, debug) << "Transforming model into namespace: " << n;

    namespace_info r;
    r.documentation(model_.documentation());

    sml::qname qn;
    qn.type_name(n);
    qn.external_module_path(model_.external_module_path());
    qn.meta_type(sml::meta_types::module);
    r.namespaces(transform_into_namespace_list(qn));

    BOOST_LOG_SEV(lg, debug) << "Transformed model into namespace: " << n;
    return r;
}

registrar_info transformer::transform_model_into_registrar() const {
    const std::string n(model_.name());
    BOOST_LOG_SEV(lg, debug) << "Transforming model into registrar: " << n;

    sml::qname qn;
    qn.model_name(n);
    qn.external_module_path(model_.external_module_path());
    qn.meta_type(sml::meta_types::pod);

    registrar_info r;
    r.namespaces(transform_into_namespace_list(qn));

    for (const auto& pair : model_.dependencies()) {
        const auto d(pair.second);
        if (!d.is_system())
            r.model_dependencies().push_back(d.model_name());
    }

    for (const auto& l : model_.leaves())
        r.leaves().push_back(transform_into_qualified_name(l));
    r.leaves().sort();

    BOOST_LOG_SEV(lg, debug) << "Transformed model into registrar: " << n;
    return r;
}

void transformer::transform(const sml::nested_qname& nqn,
    cpp::nested_type_info& nti, std::string& complete_name,
    bool& requires_stream_manipulators) const {

    const auto qn(nqn.type());
    const auto qualified_name(transform_into_qualified_name(qn));
    nti.name(qualified_name);
    nti.namespaces(transform_into_namespace_list(qn));

    using sml::meta_types;
    nti.is_enumeration(qn.meta_type() == meta_types::enumeration);
    nti.is_primitive(qn.meta_type() == meta_types::primitive);
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

    if (qn.meta_type() == meta_types::pod) {
        const auto i(model_.pods().find(qn));
        if (i == model_.pods().end()) {
            BOOST_LOG_SEV(lg, error) << pod_not_found << qn.type_name();
            BOOST_THROW_EXCEPTION(transformation_error(pod_not_found +
                qn.type_name()));
        }
        const auto pt(i->second.pod_type());
        using sml::pod_types;
        nti.is_sequence_container(pt == pod_types::sequence_container);
        nti.is_associative_container(pt == pod_types::associative_container);
        nti.is_smart_pointer(pt == pod_types::smart_pointer);
    }

    using dogen::cpp::nested_type_info;
    const auto nqn_children(nqn.children());

    std::string my_complete_name(nti.name());
    auto lambda([&](char c) {
            if (!nqn_children.empty()) {
                if (my_complete_name[my_complete_name.length() - 1] == c)
                    my_complete_name += " ";
                my_complete_name += c;
            }
        });

    std::list<nested_type_info> children;
    lambda('<');
    bool is_first(true);
    for (const auto c : nqn.children()) {
        if (!is_first)
            my_complete_name += ", ";

        nested_type_info ci;
        transform(c, ci, my_complete_name, requires_stream_manipulators);
        children.push_back(ci);
        is_first = false;
    }
    lambda('>');

    nti.identifiable_name(to_identifiable_name(qualified_name));
    nti.complete_identifiable_name(to_identifiable_name(my_complete_name));
    nti.complete_name(my_complete_name);
    nti.children(children);
    complete_name += my_complete_name;
}

std::tuple<property_info, bool, bool, bool, bool>
transformer::transform(const sml::property p, const bool is_immutable,
    const bool is_fluent) const {

    property_info pi;
    pi.name(p.name());
    pi.documentation(p.documentation());
    pi.is_immutable(is_immutable);
    pi.is_fluent(is_fluent);

    bool has_primitive_properties(false);
    bool requires_stream_manipulators(false);
    bool requires_manual_move_constructor(false);
    bool requires_manual_default_constructor(false);

    nested_type_info nti;
    std::string complete_name;
    if (::requires_manual_move_constructor(p.type_name().type().type_name()))
        requires_manual_move_constructor = true;

    transform(p.type_name(), nti, complete_name, requires_stream_manipulators);
    if (nti.is_primitive()) {
        has_primitive_properties = true;
        requires_manual_default_constructor = true;
    } else if (nti.is_enumeration())
        requires_manual_default_constructor = true;

    nti.complete_name(complete_name);
    pi.type(nti);
    pi.implementation_specific_parameters(
        p.implementation_specific_parameters());

    return std::make_tuple(pi,
        has_primitive_properties,
        requires_stream_manipulators,
        requires_manual_move_constructor,
        requires_manual_default_constructor);
}

class_info transformer::
transform(const sml::pod& p, const optional_class_info pci,
    const optional_class_info opci) const {

    if (p.parent_name() && (!pci || !opci)) {
        BOOST_LOG_SEV(lg, error) << parent_info_not_supplied
                                 << p.name().type_name();
        BOOST_THROW_EXCEPTION(
            transformation_error(parent_info_not_supplied +
                p.name().type_name()));
    } else if (!p.parent_name() && (pci || opci)) {
        BOOST_LOG_SEV(lg, error) << parent_info_supplied
                                 << p.name().type_name();
        BOOST_THROW_EXCEPTION(
            transformation_error(parent_info_supplied +
                p.name().type_name()));
    }

    class_info r;
    r.name(p.name().type_name());
    r.namespaces(transform_into_namespace_list(p.name()));
    r.documentation(p.documentation());
    r.is_immutable(p.is_immutable());
    r.is_visitable(p.is_visitable());
    r.is_parent(p.is_parent());
    r.implementation_specific_parameters(
        p.implementation_specific_parameters());

    if (p.parent_name()) {
        parent_info pi;
        pi.name(pci->name());
        pi.properties(pci->all_properties());
        pi.namespaces(pci->namespaces());
        r.parents().push_back(pi);
        r.all_properties(pci->all_properties());
    }

    if (opci) {
        std::list<std::string> ns(opci->namespaces());
        ns.push_back(opci->name());

        using boost::join;
        r.original_parent_name_qualified(join(ns, namespace_separator));
        r.original_parent_name(opci->name());
        r.is_original_parent_visitable(opci->is_visitable());
    }

    std::list<sml::property> props;
    std::unordered_set<sml::qname> processed_qnames;
    for (const auto& qn : p.modeled_concepts())
        properties_for_concept(qn, props, processed_qnames);
    props.insert(props.end(), p.properties().begin(), p.properties().end());

    for (const auto& prop : props) {
        const auto tuple(transform(prop, p.is_immutable(), p.is_fluent()));
        r.properties().push_back(std::get<0>(tuple));
        r.all_properties().push_back(std::get<0>(tuple));

        if (std::get<1>(tuple))
            r.has_primitive_properties(true);

        if (std::get<2>(tuple))
            r.requires_stream_manipulators(true);

        if (std::get<3>(tuple))
            r.requires_manual_move_constructor(true);

        if (std::get<4>(tuple))
            r.requires_manual_default_constructor(true);
    }

    for (const auto l : p.leaves())
        r.leaves().push_back(transform_into_qualified_name(l));

    return r;
}

visitor_info transformer::transform_into_visitor(const sml::pod& p) const {
    if (!p.is_visitable()) {
        BOOST_LOG_SEV(lg, error) << non_visitable_pod_supplied
                                 << p.name().type_name();
        BOOST_THROW_EXCEPTION(
            transformation_error(non_visitable_pod_supplied +
                p.name().type_name()));
    }

    visitor_info r;
    r.name(p.name().type_name() + visitor_postfix);
    r.namespaces(transform_into_namespace_list(p.name()));

    for (const auto l : p.leaves())
        r.types().push_back(transform_into_qualified_name(l));

    return r;
}

} }
