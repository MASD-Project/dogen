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
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/meta_data_reader.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/io/value_object_types_io.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/io/service_types_io.hpp"
#include "dogen/sml/types/factory.hpp"
#include "dogen/sml/types/repository.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/sml_to_cpp/types/transformation_error.hpp"
#include "dogen/sml_to_cpp/types/transformer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml_to_cpp.transformer"));

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
const std::string registrar_name("registrar");

const std::string int8_t_type("std::int8_t");
const std::string int16_t_type("std::int16_t");
const std::string int32_t_type("std::int32_t");
const std::string int64_t_type("std::int64_t");
const std::string uint8_t_type("std::uint8_t");
const std::string uint16_t_type("std::uint16_t");
const std::string uint32_t_type("std::uint32_t");
const std::string uint64_t_type("std::uint64_t");

const std::string unsupported_service_type("Service type is not supported: ");
const std::string unsupported_value_object_type(
    "Value object type is not supported: ");

const std::string concept_not_found("Concept not found in concept container: ");
const std::string parent_class_info_not_found(
    "Type has a parent but no parent class info found: ");

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
namespace sml_to_cpp {

transformer::transformer(const sml::model& m, context& c)
    : model_(m), context_(c) { }

void transformer::properties_for_concept(const sml::qname& qn,
    std::list<sml::property>& properties,
    std::unordered_set<sml::qname>& processed_qnames) const {

    if (processed_qnames.find(qn) != processed_qnames.end())
        return;

    processed_qnames.insert(qn);
    const auto i(model_.concepts().find(qn));
    if (i == model_.concepts().end()) {
        const auto& sn(qn.simple_name());
        BOOST_LOG_SEV(lg, error) << concept_not_found << sn;
        BOOST_THROW_EXCEPTION(transformation_error(concept_not_found + sn));
    }

    const auto& concept(i->second);
    const auto& cp(concept.properties());
    properties.insert(properties.end(), cp.begin(), cp.end());
}

std::string transformer::to_qualified_name(const sml::qname& qn) const {
    std::list<std::string> l(to_namespace_list(qn));
    l.push_back(qn.simple_name());
    return boost::algorithm::join(l, namespace_separator);
}

std::list<std::string>
transformer::to_namespace_list(const sml::qname& qn) const {
    std::list<std::string> r(qn.external_module_path());

    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    const auto mp(qn.module_path());
    r.insert(r.end(), mp.begin(), mp.end());

    const auto i(model_.modules().find(qn));
    if (i != model_.modules().end())
        r.push_back(qn.simple_name());

    return r;
}

void transformer::to_nested_type_info(const sml::nested_qname& nqn,
    cpp::nested_type_info& nti, std::string& complete_name,
    bool& requires_stream_manipulators) const {

    const auto qn(nqn.type());
    const auto qualified_name(to_qualified_name(qn));
    nti.name(qualified_name);
    nti.namespaces(to_namespace_list(qn));

    const auto i(model_.enumerations().find(qn));
    const bool is_enumeration(i != model_.enumerations().end());
    nti.is_enumeration(is_enumeration);

    const auto j(model_.primitives().find(qn));
    const bool is_primitive(j != model_.primitives().end());
    nti.is_primitive(is_primitive);

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

    const auto k(model_.objects().find(qn));
    if (k != model_.objects().end()) {
        using boost::dynamic_pointer_cast;
        const auto vo(dynamic_pointer_cast<const sml::value_object>(k->second));
        if (vo) {
            const auto pt(vo->type());
            typedef sml::value_object_types vot;
            nti.is_sequence_container(pt == vot::sequence_container);
            nti.is_associative_container(pt == vot::associative_container);
            nti.is_smart_pointer(pt == vot::smart_pointer);
        }
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
        to_nested_type_info(c, ci, my_complete_name,
            requires_stream_manipulators);
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

std::tuple<cpp::property_info, bool, bool, bool, bool>
transformer::to_property_info(const sml::property p, const bool is_immutable,
    const bool is_fluent) const {

    cpp::property_info pi;
    pi.name(p.name());
    pi.documentation(p.documentation());
    pi.is_immutable(is_immutable);
    pi.is_fluent(is_fluent);

    bool has_primitive_properties(false);
    bool requires_stream_manipulators(false);
    bool requires_manual_move_constructor(false);
    bool requires_manual_default_constructor(false);

    cpp::nested_type_info nti;
    std::string complete_name;
    const auto t(p.type());
    if (::requires_manual_move_constructor(t.type().simple_name()))
        requires_manual_move_constructor = true;

    to_nested_type_info(t, nti, complete_name, requires_stream_manipulators);
    if (nti.is_primitive()) {
        has_primitive_properties = true;
        requires_manual_default_constructor = true;
    } else if (nti.is_enumeration())
        requires_manual_default_constructor = true;

    nti.complete_name(complete_name);
    pi.type(nti);
    sml::meta_data_reader reader(p.meta_data());
    pi.opaque_parameters(reader.odb_pragma());

    return std::make_tuple(pi,
        has_primitive_properties,
        requires_stream_manipulators,
        requires_manual_move_constructor,
        requires_manual_default_constructor);
}

cpp::enumerator_info
transformer::to_enumerator_info(const sml::enumerator& e) const {
    cpp::enumerator_info r;
    r.name(e.name());
    r.value(e.value());
    r.documentation(e.documentation());
    return r;
}

cpp::enum_info
transformer::to_enumeration_info(const sml::enumeration& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: " << e.name();

    cpp::enum_info r;
    r.name(e.name().simple_name());
    r.namespaces(to_namespace_list(e.name()));
    r.documentation(e.documentation());
    r.type(e.underlying_type().simple_name());

    for (const auto& en : e.enumerators())
        r.enumerators().push_back(to_enumerator_info(en));

    BOOST_LOG_SEV(lg, debug) << "Transformed enumeration: " << e.name();

    return r;
}

cpp::exception_info
transformer::to_exception_info(const sml::value_object& vo) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exception: " << vo.name();

    cpp::exception_info r;
    r.name(vo.name().simple_name());
    r.namespaces(to_namespace_list(vo.name()));
    r.documentation(vo.documentation());

    BOOST_LOG_SEV(lg, debug) << "Transformed exception: " << vo.name();

    return r;
}

cpp::class_info
transformer::to_class_info(const sml::abstract_object& ao) const {
    cpp::class_info r;
    r.name(ao.name().simple_name());
    r.namespaces(to_namespace_list(ao.name()));
    r.documentation(ao.documentation());
    r.is_immutable(ao.is_immutable());
    r.is_visitable(ao.is_visitable());
    r.is_parent(ao.is_parent());
    r.generation_type(ao.generation_type());
    r.class_type(cpp::class_types::user_defined);

    sml::meta_data_reader reader(ao.meta_data());
    r.opaque_parameters(reader.odb_pragma());

    const auto pn(ao.parent_name());
    if (pn) {
        const auto i(context_.classes().find(*ao.parent_name()));
        if (i == context_.classes().end()) {
            const auto& sn(ao.parent_name()->simple_name());
            BOOST_LOG_SEV(lg, error) << parent_class_info_not_found << sn;
            BOOST_THROW_EXCEPTION(transformation_error(
                    parent_class_info_not_found + sn));
        }

        const auto pci(i->second);
        cpp::parent_info pi;
        pi.name(pci.name());
        pi.properties(pci.all_properties());
        pi.namespaces(pci.namespaces());
        r.parents().push_back(pi);
        r.all_properties(pci.all_properties());
    }

    const auto opn(ao.original_parent_name());
    if (opn) {
        const auto i(context_.classes().find(*opn));
        if (i == context_.classes().end()) {
            const auto& sn(ao.parent_name()->simple_name());
            BOOST_LOG_SEV(lg, error) << parent_class_info_not_found << sn;
            BOOST_THROW_EXCEPTION(transformation_error(
                    parent_class_info_not_found + sn));
        }

        const auto opci(i->second);
        std::list<std::string> ns(opci.namespaces());
        ns.push_back(opci.name());

        using boost::join;
        r.original_parent_name_qualified(join(ns, namespace_separator));
        r.original_parent_name(opci.name());
        r.is_original_parent_visitable(opci.is_visitable());
    }

    std::list<sml::property> props;
    std::unordered_set<sml::qname> processed_qnames;
    for (const auto& qn : ao.modeled_concepts())
        properties_for_concept(qn, props, processed_qnames);

    props.insert(props.end(), ao.properties().begin(), ao.properties().end());

    for (const auto& prop : props) {
        const auto tuple(to_property_info(
                prop, ao.is_immutable(), ao.is_fluent()));

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

    for (const auto l : ao.leaves())
        r.leaves().push_back(to_qualified_name(l));

    return r;
}

cpp::visitor_info transformer::to_visitor(const sml::service& s) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming visitor: " << s.name();

    cpp::visitor_info r;
    r.name(s.name().simple_name());
    r.namespaces(to_namespace_list(s.name()));

    for (const auto op : s.operations()) {
        for (const auto p : op.parameters())
            r.types().push_back(to_qualified_name(p.type().type()));
    }

    return r;
}

void transformer::add_class(const sml::qname& qn, const cpp::class_info& ci) {
    context_.classes().insert(std::make_pair(qn, ci));
}

void transformer::visit(const dogen::sml::service& s) {
    BOOST_LOG_SEV(lg, debug) << "Transforming service: " << s.name();

    switch(s.type()) {
    case sml::service_types::user_defined: {
        auto ci(to_class_info(s));
        ci.class_type(cpp::class_types::service); // FIXME: mega-hack
        add_class(s.name(), ci);
        break;
    }
    case sml::service_types::visitor:
        context_.visitors().insert(std::make_pair(s.name(), to_visitor(s)));
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_service_type << s.type()
                                 << " service: " << s.name();
        BOOST_THROW_EXCEPTION(transformation_error(unsupported_service_type +
                boost::lexical_cast<std::string>(s.type())));
    };

    BOOST_LOG_SEV(lg, debug) << "Transformed service: " << s.name();
}

void transformer::visit(const dogen::sml::factory& f) {
    BOOST_LOG_SEV(lg, debug) << "Transforming service: " << f.name();

    auto ci(to_class_info(f));
    ci.class_type(cpp::class_types::service); // FIXME: mega-hack
    add_class(f.name(), ci);

    BOOST_LOG_SEV(lg, debug) << "Transformed service: " << f.name();
}

void transformer::visit(const dogen::sml::repository& r) {
    BOOST_LOG_SEV(lg, debug) << "Transforming service: " << r.name();

    auto ci(to_class_info(r));
    ci.class_type(cpp::class_types::service); // FIXME: mega-hack
    add_class(r.name(), ci);

    BOOST_LOG_SEV(lg, debug) << "Transformed service: " << r.name();
}

void transformer::visit(const dogen::sml::enumeration& e) {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: " << e.name();

    cpp::enum_info ei;
    ei.name(e.name().simple_name());
    ei.namespaces(to_namespace_list(e.name()));
    ei.documentation(e.documentation());
    ei.type(e.underlying_type().simple_name());

    for (const auto& en : e.enumerators())
        ei.enumerators().push_back(to_enumerator_info(en));

    context_.enumerations().insert(std::make_pair(e.name(), ei));

    BOOST_LOG_SEV(lg, debug) << "Transformed enumeration: " << e.name();
}

void transformer::visit(const dogen::sml::value_object& vo) {
    BOOST_LOG_SEV(lg, debug) << "Transforming value object: " << vo.name();

    switch(vo.type()) {
    case sml::value_object_types::exception: {
        const auto e(to_exception_info(vo));
        context_.exceptions().insert(std::make_pair(vo.name(), e));
        break;
    }
    case sml::value_object_types::plain: {
        add_class(vo.name(), to_class_info(vo));
        break;
    }
    case sml::value_object_types::versioned_key: {
        auto ci(to_class_info(vo));
        ci.class_type(cpp::class_types::versioned_key);
        add_class(vo.name(), ci);
        break;
    }
    case sml::value_object_types::unversioned_key: {
        auto ci(to_class_info(vo));
        ci.class_type(cpp::class_types::unversioned_key);
        add_class(vo.name(), ci);
        break;
    }
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_value_object_type << vo.type();
        BOOST_THROW_EXCEPTION(transformation_error(
                unsupported_value_object_type +
                boost::lexical_cast<std::string>(vo.type())));
    };

    BOOST_LOG_SEV(lg, debug) << "Transformed value object: " << vo.name();
}

void transformer::visit(const dogen::sml::keyed_entity& ke) {
    BOOST_LOG_SEV(lg, debug) << "Transforming keyed entity: " << ke.name();

    auto ci(to_class_info(ke));
    add_class(ke.name(), ci);

    BOOST_LOG_SEV(lg, debug) << "Transformed keyed entity: " << ke.name();
}

void transformer::visit(const dogen::sml::entity& e) {
    BOOST_LOG_SEV(lg, debug) << "Transforming entity: " << e.name();

    auto ci(to_class_info(e));
    add_class(e.name(), ci);

    BOOST_LOG_SEV(lg, debug) << "Transformed entity: " << e.name();
}

void transformer::from_type(const sml::type& t) {
    t.accept(*this);
}

void transformer::to_namespace_info(const sml::module& m) {
    BOOST_LOG_SEV(lg, debug) << "Transforming module: " << m.name();

    cpp::namespace_info ni;
    ni.documentation(m.documentation());
    ni.namespaces(to_namespace_list(m.name()));

    context_.namespaces().insert(std::make_pair(m.name(), ni));

    BOOST_LOG_SEV(lg, debug) << "Transformed module: " << m.name();
}

void transformer::model_to_namespace_info() {
    const std::string n(model_.name().simple_name());
    BOOST_LOG_SEV(lg, debug) << "Transforming model into namespace: " << n;

    cpp::namespace_info ni;
    ni.documentation(model_.documentation());
    ni.namespaces(to_namespace_list(model_.name()));

    context_.namespaces().insert(std::make_pair(model_.name(), ni));

    BOOST_LOG_SEV(lg, debug) << "Transformed model into namespace: " << n;
}

void transformer::model_to_registrar_info() {
    const std::string n(model_.name().simple_name());
    BOOST_LOG_SEV(lg, debug) << "Transforming model into registrar: " << n;

    cpp::registrar_info ri;
    ri.namespaces(to_namespace_list(model_.name()));

    for (const auto& pair : model_.references()) {
        if (pair.second != sml::origin_types::system)
            ri.model_dependencies().push_back(pair.first.model_name());
    }

    for (const auto& l : model_.leaves())
        ri.leaves().push_back(to_qualified_name(l));
    ri.leaves().sort();

    sml::qname qn;
    qn.simple_name(registrar_name);
    qn.model_name(model_.name().model_name());
    qn.external_module_path(model_.name().external_module_path());
    context_.registrars().insert(std::make_pair(qn, ri));

    BOOST_LOG_SEV(lg, debug) << "Transformed model into registrar: " << n;
}

} }
