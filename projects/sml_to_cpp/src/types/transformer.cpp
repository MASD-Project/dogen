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
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/schema/types/content_extensions.hpp"
#include "dogen/cpp/types/formatters/odb/field_definitions.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/io/object_types_io.hpp"
#include "dogen/sml/types/object.hpp"
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

const std::string unsupported_object_type("Object type is not supported: ");
const std::string concept_not_found("Concept not found in concept container: ");
const std::string parent_class_info_not_found(
    "Type has a parent but no parent class info found: ");

const std::string too_many_parents(
    "Type has more than one parent but multiple inheritance not supported: ");

const std::string no_visitees("Visitor is not visiting any types: ");

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

std::list<std::pair<std::string, std::string> >
transformer::obtain_opaque_parameters(const dynamic::schema::object& o) const {
    std::list<std::pair<std::string, std::string> > r;

    using namespace dynamic::schema;
    using fd = cpp::formatters::odb::field_definitions;
    if (!has_field(o, fd::odb_pragma()))
        return r;

    const auto sn(fd::odb_pragma().name().simple());
    const auto tc(get_text_collection_content(o, fd::odb_pragma()));
    for (const auto& e : tc)
        r.push_back(std::make_pair(sn, e));

    return r;
}

std::string transformer::to_qualified_name(const sml::qname& qn) const {
    std::list<std::string> l(to_namespace_list(qn));
    l.push_back(qn.simple_name());
    return boost::algorithm::join(l, namespace_separator);
}

std::list<std::string>
transformer::to_namespace_list(const sml::qname& qn) const {
    std::list<std::string> r(qn.external_module_path());

    // if there is no module name, it won't contribute to the namespaces.
    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    // all modules in the module path contribute to namespaces.
    const auto mp(qn.module_path());
    r.insert(r.end(), mp.begin(), mp.end());

    // if the qname belongs to a module, the simple name will
    // contribute to the namespaces (since it is a module), unless we
    // are dealing with the model's synthetic module.
    const auto i(model_.modules().find(qn));
    const bool is_module(i != model_.modules().end());
    const bool is_synthetic_module(qn.simple_name() == qn.model_name());
    if (is_module && !is_synthetic_module)
        r.push_back(qn.simple_name());

    return r;
}

void transformer::to_nested_type_info(const sml::nested_qname& nqn,
    cpp::formattables::nested_type_info& nti, std::string& complete_name,
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
        const auto ot(k->second.object_type());
        using sml::object_types;
        nti.is_sequence_container(ot == object_types::sequence_container);
        nti.is_associative_container(ot == object_types::ordered_container ||
            ot == object_types::hash_container);
        nti.is_smart_pointer(ot == object_types::smart_pointer);
    }

    using dogen::cpp::formattables::nested_type_info;
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

std::tuple<cpp::formattables::property_info, bool, bool, bool, bool>
transformer::to_property_info(const sml::property p, const bool is_immutable,
    const bool is_fluent) const {

    cpp::formattables::property_info pi;
    pi.name(p.name());
    pi.documentation(p.documentation());
    pi.is_immutable(is_immutable);
    pi.is_fluent(is_fluent);

    bool has_primitive_properties(false);
    bool requires_stream_manipulators(false);
    bool requires_manual_move_constructor(false);
    bool requires_manual_default_constructor(false);

    cpp::formattables::nested_type_info nti;
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
    pi.opaque_parameters(obtain_opaque_parameters(p.extensions()));

    return std::make_tuple(pi,
        has_primitive_properties,
        requires_stream_manipulators,
        requires_manual_move_constructor,
        requires_manual_default_constructor);
}

cpp::formattables::enumerator_info
transformer::to_enumerator_info(const sml::enumerator& e) const {
    cpp::formattables::enumerator_info r;
    r.name(e.name());
    r.value(e.value());
    r.documentation(e.documentation());
    return r;
}

boost::shared_ptr<cpp::formattables::enum_info>
transformer::to_enumeration_info(const sml::enumeration& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: "
                             << sml::string_converter::convert(e.name());

    auto r(boost::make_shared<cpp::formattables::enum_info>());
    r->name(e.name().simple_name());
    r->namespaces(to_namespace_list(e.name()));
    r->documentation(e.documentation());
    r->type(e.underlying_type().simple_name());

    for (const auto& en : e.enumerators())
        r->enumerators().push_back(to_enumerator_info(en));

    BOOST_LOG_SEV(lg, debug) << "Transformed enumeration.";
    return r;
}

boost::shared_ptr<cpp::formattables::exception_info>
transformer::to_exception_info(const sml::object& o) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exception: "
                             << sml::string_converter::convert(o.name());

    auto r(boost::make_shared<cpp::formattables::exception_info>());
    r->name(o.name().simple_name());
    r->namespaces(to_namespace_list(o.name()));
    r->documentation(o.documentation());

    BOOST_LOG_SEV(lg, debug) << "Transformed exception.";
    return r;
}

boost::shared_ptr<cpp::formattables::class_info>
transformer::to_class_info(const sml::object& o) const {
    auto r(boost::make_shared<cpp::formattables::class_info>());

    r->name(o.name().simple_name());
    r->namespaces(to_namespace_list(o.name()));
    r->documentation(o.documentation());
    r->is_immutable(o.is_immutable());
    r->is_visitable(o.is_visitable());
    r->is_parent(o.is_parent());
    r->generation_type(o.generation_type());
    r->class_type(cpp::formattables::class_types::user_defined);
    r->opaque_parameters(obtain_opaque_parameters(o.extensions()));

    auto i(o.relationships().find(sml::relationship_types::parents));
    if (i != o.relationships().end()) {
        for (const auto& qn : i->second) {
            cpp::formattables::parent_info pi;
            pi.name(qn.simple_name());
            pi.namespaces(to_namespace_list(qn));

            const auto j(o.inherited_properties().find(qn));
            if (j != o.inherited_properties().end()) {
                for (const auto& prop : j->second) {
                    const auto tuple(to_property_info(
                            prop, o.is_immutable(), o.is_fluent()));
                    pi.properties().push_back(std::get<0>(tuple));
                }
            }
            r->parents().push_back(pi);
        }
    }

    i = o.relationships().find(sml::relationship_types::original_parents);
    if (i != o.relationships().end() && !i->second.empty()) {
        if (i->second.size() > 1) {
            const auto n(sml::string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << too_many_parents << n;
            BOOST_THROW_EXCEPTION(transformation_error(too_many_parents + n));
        }

        const auto opn(i->second.front());
        const auto j(context_.classes().find(opn));
        if (j == context_.classes().end()) {
            const auto n(sml::string_converter::convert(opn));
            BOOST_LOG_SEV(lg, error) << parent_class_info_not_found << n;
            BOOST_THROW_EXCEPTION(transformation_error(
                    parent_class_info_not_found + n));
        }

        const auto opci(j->second);
        std::list<std::string> ns(opci->namespaces());
        ns.push_back(opci->name());

        using boost::join;
        r->original_parent_name_qualified(join(ns, namespace_separator));
        r->original_parent_name(opci->name());
        r->is_original_parent_visitable(opci->is_visitable());
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
            r->has_primitive_properties(true);

        if (std::get<2>(tuple))
            r->requires_stream_manipulators(true);

        if (std::get<3>(tuple))
            r->requires_manual_move_constructor(true);

        if (std::get<4>(tuple))
            r->requires_manual_default_constructor(true);
    }

    i = o.relationships().find(sml::relationship_types::leaves);
    if (i != o.relationships().end()) {
        for (const auto l : i->second)
            r->leaves().push_back(to_qualified_name(l));
    }

    return r;
}

boost::shared_ptr<cpp::formattables::visitor_info>
transformer::to_visitor(const sml::object& o) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming visitor: "
                             << sml::string_converter::convert(o.name());

    auto r(boost::make_shared<cpp::formattables::visitor_info>());
    r->name(o.name().simple_name());
    r->namespaces(to_namespace_list(o.name()));

    auto i(o.relationships().find(sml::relationship_types::visits));
    if (i == o.relationships().end() || i->second.empty()) {
        const auto n(sml::string_converter::convert(o.name()));
        BOOST_LOG_SEV(lg, error) << no_visitees << n;
        BOOST_THROW_EXCEPTION(transformation_error(no_visitees + n));
    }

    for (const auto qn : i->second)
        r->types().push_back(to_qualified_name(qn));

    BOOST_LOG_SEV(lg, debug) << "Transformed visitor.";
    return r;
}

void transformer::add_class(const sml::qname& qn,
    boost::shared_ptr<cpp::formattables::class_info> ci) {
    context_.classes().insert(std::make_pair(qn, ci));
}

void transformer::visit(const dogen::sml::enumeration& e) {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: "
                             << sml::string_converter::convert(e.name());
    auto ei(to_enumeration_info(e));
    context_.enumerations().insert(std::make_pair(e.name(), ei));
    BOOST_LOG_SEV(lg, debug) << "Transformed enumeration.";
}

void transformer::visit(const dogen::sml::object& o) {
    BOOST_LOG_SEV(lg, debug) << "Transforming object: "
                             << sml::string_converter::convert(o.name());

    auto ci(to_class_info(o));
    switch(o.object_type()) {
    case sml::object_types::factory:
        ci->class_type(cpp::formattables::class_types::service); // FIXME: mega-hack
        add_class(o.name(), ci);
        break;
    case sml::object_types::user_defined_service:
        ci->class_type(cpp::formattables::class_types::service);
        add_class(o.name(), ci);
        break;
    case sml::object_types::visitor:
        context_.visitors().insert(std::make_pair(o.name(), to_visitor(o)));
        break;
    case sml::object_types::entity:
    case sml::object_types::keyed_entity:
        ci->class_type(cpp::formattables::class_types::user_defined);
        add_class(o.name(), ci);
        break;

    case sml::object_types::exception: {
        const auto e(to_exception_info(o));
        context_.exceptions().insert(std::make_pair(o.name(), e));
        break;
    }
    case sml::object_types::user_defined_value_object: {
        add_class(o.name(), to_class_info(o));
        break;
    }
    case sml::object_types::versioned_key: {
        auto ci(to_class_info(o));
        ci->class_type(cpp::formattables::class_types::versioned_key);
        add_class(o.name(), ci);
        break;
    }
    case sml::object_types::unversioned_key: {
        auto ci(to_class_info(o));
        ci->class_type(cpp::formattables::class_types::unversioned_key);
        add_class(o.name(), ci);
        break;
    }
    default: {
        const auto n(sml::string_converter::convert(o.name()));
        BOOST_LOG_SEV(lg, error) << unsupported_object_type << o.object_type()
                                 << " name: " << n;
        BOOST_THROW_EXCEPTION(
            transformation_error(unsupported_object_type + n));
    } };

    BOOST_LOG_SEV(lg, debug) << "Transformed object.";
}

void transformer::from_type(const sml::type& t) {
    t.accept(*this);
}

void transformer::to_namespace_info(const sml::module& m) {
    BOOST_LOG_SEV(lg, debug) << "Transforming module: "
                             << sml::string_converter::convert(m.name());

    auto ni(boost::make_shared<cpp::formattables::namespace_info>());
    ni->documentation(m.documentation());
    ni->namespaces(to_namespace_list(m.name()));
    context_.namespaces().insert(std::make_pair(m.name(), ni));

    BOOST_LOG_SEV(lg, debug) << "Transformed module.";
}

void transformer::model_to_registrar_info() {
    BOOST_LOG_SEV(lg, debug) << "Transforming model into registrar: "
                             << sml::string_converter::convert(model_.name());

    auto ri(boost::make_shared<cpp::formattables::registrar_info>());
    ri->namespaces(to_namespace_list(model_.name()));

    for (const auto& pair : model_.references()) {
        if (pair.second != sml::origin_types::system) {
            const auto l(to_namespace_list(pair.first));
            const auto s(boost::algorithm::join(l, namespace_separator));
            ri->model_dependencies().push_back(s);
        }
    }

    for (const auto& l : model_.leaves())
        ri->leaves().push_back(to_qualified_name(l));
    ri->leaves().sort();

    sml::qname qn;
    qn.simple_name(registrar_name);
    qn.model_name(model_.name().model_name());
    qn.external_module_path(model_.name().external_module_path());
    context_.registrars().insert(std::make_pair(qn, ri));

    BOOST_LOG_SEV(lg, debug) << "Transformed model into registrar.";
}

} }
