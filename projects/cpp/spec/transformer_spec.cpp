/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/cpp/io/all_io.hpp"
#include "dogen/cpp/types/transformation_error.hpp"
#include "dogen/cpp/types/transformer.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string empty;
const std::string test_module("cpp");
const std::string test_suite("transformer_spec");
const std::string external_module("some_module");

const std::string no_parent_info("Type has a parent ");
const std::string unexpected_parent_info("Type does not have a parent");

bool ends_with_type_zero(const std::string& n) {
    return boost::ends_with(n, mock_model_factory::simple_name(0));
}

bool is_type_zero(const std::string& n) {
    return mock_model_factory::simple_name(0) == n;
}

bool is_type_one(const std::string& n) {
    return mock_model_factory::simple_name(1) == n;
}

bool is_type_two(const std::string& n) {
    return mock_model_factory::simple_name(2) == n;
}

bool is_type_three(const std::string& n) {
    return mock_model_factory::simple_name(3) == n;
}

bool is_module_zero(const std::string& n) {
    return mock_model_factory::module_name(0) == n;
}

bool is_module_one(const std::string& n) {
    return mock_model_factory::module_name(1) == n;
}

bool is_model_zero(const std::string& n) {
    return mock_model_factory::model_name(0) == n;
}

bool check_name(const std::string& n) {
    return
        !boost::contains(n, ":") && !boost::contains(n, " ") &&
        !boost::contains(n, "<") && !boost::contains(n, ">") &&
        !boost::contains(n, ",");
}

bool check_scoped_name(const std::string& n) {
    return boost::contains(n, "::");
}

}

using dogen::utility::test::contains_checker;
typedef dogen::sml::test::mock_model_factory::object_types object_types;
typedef dogen::sml::test::mock_model_factory::property_types property_types;

BOOST_AUTO_TEST_SUITE(transformer)

BOOST_AUTO_TEST_CASE(transforming_enumeration_results_in_expected_enum_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_results_in_expected_enum_info");

    const auto ot(object_types::enumeration);
    const auto m(mock_model_factory::build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*m.objects().begin()->second);

    BOOST_REQUIRE(c.enumerations().size() == 1);
    const auto e(c.enumerations().front());
    BOOST_LOG_SEV(lg, debug) << "enumeration: " << e;

    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());
    BOOST_REQUIRE(e.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(e.namespaces().front()));
    BOOST_REQUIRE(e.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e.enumerators().back().name()));
}

BOOST_AUTO_TEST_CASE(transforming_enumeration_in_module_results_in_expected_enum_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_in_module_results_in_expected_enum_info");

    const auto ot(object_types::enumeration);
    const auto m0(
        mock_model_factory::build_single_type_model_in_module(0, ot, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.objects().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m0, c);
    BOOST_REQUIRE(c.enumerations().size() == 1);
    t.from_type(*m0.objects().begin()->second);
    const auto e0(c.enumerations().front());
    BOOST_LOG_SEV(lg, debug) << "enumeration 0: " << e0;

    BOOST_CHECK(is_type_zero(e0.name()));
    BOOST_CHECK(!e0.documentation().empty());
    BOOST_REQUIRE(e0.namespaces().size() == 2);
    BOOST_CHECK(is_model_zero(e0.namespaces().front()));
    BOOST_CHECK(is_module_zero(e0.namespaces().back()));

    BOOST_REQUIRE(e0.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e0.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e0.enumerators().back().name()));

    const auto m1(
        mock_model_factory::build_single_type_model_in_module(0, ot, 2));
    BOOST_LOG_SEV(lg, debug) << "model 1: " << m1;
    BOOST_REQUIRE(m0.enumerations().size() == 1);

    t.from_type(*m1.objects().begin()->second);
    const auto e1(c.enumerations().front());
    BOOST_LOG_SEV(lg, debug) << "enumeration 1: " << e1;
    BOOST_CHECK(is_type_zero(e1.name()));
    BOOST_CHECK(!e1.documentation().empty());
    BOOST_REQUIRE(e1.namespaces().size() == 3);
    BOOST_CHECK(is_model_zero(e1.namespaces().front()));
    BOOST_CHECK(is_module_one(e1.namespaces().back()));

    BOOST_REQUIRE(e1.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e1.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e1.enumerators().back().name()));
}

BOOST_AUTO_TEST_CASE(transforming_enumeration_in_external_module_results_in_expected_enum_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_in_external_module_results_in_expected_enum_info");

    const auto ot(object_types::enumeration);
    auto m(mock_model_factory::build_single_type_model_in_module(0, ot));
    BOOST_REQUIRE(m.objects().size() == 1);
    auto enumeration(m.enumerations().begin()->second);
    enumeration.name().external_module_path().push_back(external_module);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*m.objects().begin()->second);
    const auto e(c.enumerations().front());
    BOOST_LOG_SEV(lg, debug) << "enumeration: " << e;

    BOOST_REQUIRE(e.namespaces().size() == 2);
    BOOST_CHECK(e.namespaces().front() == external_module);
    BOOST_CHECK(is_model_zero(e.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_exception_results_in_expected_exception_info) {
    SETUP_TEST_LOG_SOURCE("transforming_exception_results_in_expected_exception_info");

    const auto ot(object_types::exception);
    const auto m(mock_model_factory::build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*m.objects().begin()->second);
    const auto e(c.exceptions().front());
    BOOST_LOG_SEV(lg, debug) << "exception: " << e;

    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());
    BOOST_REQUIRE(e.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(e.namespaces().front()));
}

BOOST_AUTO_TEST_CASE(transforming_exception_in_module_results_in_expected_exception_info) {
    SETUP_TEST_LOG_SOURCE("transforming_exception_in_module_results_in_expected_exception_info");

    const auto ot(object_types::exception);
    const auto m0(
        mock_model_factory::build_single_type_model_in_module(0, ot, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.objects().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m0, c);
    t.from_type(*m0.objects().begin()->second);
    const auto e0(c.exceptions().front());
    BOOST_LOG_SEV(lg, debug) << "exception 0: " << e0;

    BOOST_CHECK(is_type_zero(e0.name()));
    BOOST_CHECK(!e0.documentation().empty());
    BOOST_REQUIRE(e0.namespaces().size() == 2);
    BOOST_CHECK(is_model_zero(e0.namespaces().front()));
    BOOST_CHECK(is_module_zero(e0.namespaces().back()));

    const auto m1(
        mock_model_factory::build_single_type_model_in_module(0, ot, 2));
    BOOST_LOG_SEV(lg, debug) << "model 1: " << m1;
    BOOST_REQUIRE(m0.objects().size() == 1);

    t.from_type(*m1.objects().begin()->second);
    const auto e1(c.exceptions().front());
    BOOST_LOG_SEV(lg, debug) << "exception 1: " << e1;
    BOOST_CHECK(is_type_zero(e1.name()));
    BOOST_CHECK(!e1.documentation().empty());
    BOOST_REQUIRE(e1.namespaces().size() == 3);
    BOOST_CHECK(is_model_zero(e1.namespaces().front()));
    BOOST_CHECK(is_module_one(e1.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_exception_in_external_module_results_in_expected_exception_info) {
    SETUP_TEST_LOG_SOURCE("transforming_exception_in_external_module_results_in_expected_exception_info");

    const auto ot(object_types::exception);
    auto m(mock_model_factory::build_single_type_model_in_module(0, ot));
    BOOST_REQUIRE(m.objects().size() == 1);
    auto& exception(*m.objects().begin()->second);
    exception.name().external_module_path().push_back(external_module);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*m.objects().begin()->second);
    const auto e(c.exceptions().front());
    BOOST_LOG_SEV(lg, debug) << "exception: " << e;

    BOOST_REQUIRE(e.namespaces().size() == 2);
    BOOST_CHECK(e.namespaces().front() == external_module);
    BOOST_CHECK(is_model_zero(e.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_module_results_in_expected_namespace_info) {
    SETUP_TEST_LOG_SOURCE("transforming_module_results_in_expected_namespace_info");

    const auto ot(object_types::exception);
    const auto m0(
        mock_model_factory::build_single_type_model_in_module(0, ot, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.modules().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m0, c);
    t.from_type(*m0.objects().begin()->second);
    const auto n0(c.namespaces().front());
    BOOST_LOG_SEV(lg, debug) << "namespace 0: " << n0;

    BOOST_CHECK(!n0.documentation().empty());
    BOOST_REQUIRE(n0.namespaces().size() == 1);
    BOOST_CHECK(is_module_zero(n0.namespaces().front()));

    const auto m1(
        mock_model_factory::build_single_type_model_in_module(0, ot, 2));
    BOOST_LOG_SEV(lg, debug) << "model 1: " << m1;
    BOOST_REQUIRE(m1.modules().size() == 2);

    auto i(m1.modules().begin());
    if (!is_module_one(i->first.simple_name()) && i != m1.modules().end())
        ++i;

    BOOST_REQUIRE(i != m1.modules().end());

    BOOST_CHECK(is_module_one(i->first.simple_name()));
    t.to_namespace_info(m0.modules().begin()->second);
    const auto p1(c.namespaces().front());

    BOOST_LOG_SEV(lg, debug) << "module 1: " << p1;

    BOOST_CHECK(!p1.documentation().empty());
    BOOST_REQUIRE(p1.namespaces().size() == 2);
    BOOST_CHECK(is_module_zero(p1.namespaces().front()));
    BOOST_CHECK(is_module_one(p1.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_model_results_in_expected_namespace_info) {
    SETUP_TEST_LOG_SOURCE("transforming_model_results_in_expected_namespace_info");

    const auto ot(object_types::exception);
    const auto m(mock_model_factory::build_single_type_model_in_module(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.model_to_namespace_info();
    const auto n(c.namespaces().front());
    BOOST_LOG_SEV(lg, debug) << "namespace: " << n;

    BOOST_CHECK(!n.documentation().empty());
    BOOST_REQUIRE(n.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(n.namespaces().front()));
}

BOOST_AUTO_TEST_CASE(transforming_module_in_external_module_results_in_expected_namespace_info) {
    SETUP_TEST_LOG_SOURCE("transforming_module_in_external_module_results_in_expected_namespace_info");

    const auto ot(object_types::value_object);
    auto m(mock_model_factory::build_single_type_model_in_module(0, ot, 1));
    m.name().external_module_path().push_back(external_module);
    BOOST_REQUIRE(m.modules().size() == 1);
    auto module(m.modules().begin()->second);
    module.name().external_module_path().push_back(external_module);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.to_namespace_info(module);
    const auto n0(c.namespaces().front());
    BOOST_LOG_SEV(lg, debug) << "module 0: " << n0;

    BOOST_REQUIRE(n0.namespaces().size() == 2);
    BOOST_CHECK(n0.namespaces().front() == external_module);
    BOOST_CHECK(is_module_zero(n0.namespaces().back()));

    t.model_to_namespace_info();
    const auto n1(c.namespaces().front());
    BOOST_LOG_SEV(lg, debug) << "module 1: " << n1;

    BOOST_REQUIRE(n1.namespaces().size() == 2);
    BOOST_CHECK(n1.namespaces().front() == external_module);
    BOOST_CHECK(is_model_zero(n1.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_pod_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_pod_results_in_expected_class_info");

    auto m(mock_model_factory::build_single_type_model_in_module());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    const auto ot(object_types::exception);
    const auto p(t.from_type(*m.objects().begin()->second));
    t.from_type(*m0.objects().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "class: " << p;
    BOOST_CHECK(is_type_zero(p.name()));
    BOOST_CHECK(!p.documentation().empty());
    BOOST_REQUIRE(p.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(p.namespaces().back()));

    BOOST_CHECK(p.properties().empty());
    BOOST_CHECK(p.all_properties().empty());
    BOOST_CHECK(!p.has_primitive_properties());
    BOOST_CHECK(!p.requires_stream_manipulators());
    BOOST_CHECK(!p.requires_manual_move_constructor());
    BOOST_CHECK(!p.requires_manual_default_constructor());
    BOOST_CHECK(p.parents().empty());
    BOOST_CHECK(!p.is_parent());
    BOOST_CHECK(p.original_parent_name().empty());
    BOOST_CHECK(p.original_parent_name_qualified().empty());
    BOOST_CHECK(p.leaves().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
    BOOST_CHECK(!p.is_comparable());
    BOOST_CHECK(!p.is_visitable());
    BOOST_CHECK(!p.is_immutable());
    BOOST_CHECK(!p.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_pod_with_property_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_pod_with_property_results_in_expected_class_info");

    auto m(mock_model_factory::pod_with_property());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    auto i(m.pods().begin());
    if (!is_type_zero(i->first.type_name()) && i != m.pods().end())
        ++i;

    BOOST_REQUIRE(i != m.pods().end());

    dogen::cpp::transformer t(m);
    const auto p(t.transform(i->second));
    BOOST_LOG_SEV(lg, debug) << "class: " << p;
    
    BOOST_CHECK(p.all_properties().size() == 1);
    BOOST_REQUIRE(p.properties().size() == 1);
    const auto type(p.properties().begin()->type());
    BOOST_CHECK(!type.is_enumeration());
    BOOST_CHECK(!type.is_primitive());
    BOOST_CHECK(!type.is_char_like());
    BOOST_CHECK(!type.is_int_like());
    BOOST_CHECK(!type.is_string_like());
    BOOST_CHECK(!type.is_optional_like());
    BOOST_CHECK(!type.is_pair());
    BOOST_CHECK(!type.is_variant_like());
    BOOST_CHECK(!type.is_filesystem_path());
    BOOST_CHECK(!type.is_date());
    BOOST_CHECK(!type.is_ptime());
    BOOST_CHECK(!type.is_time_duration());
    BOOST_CHECK(!type.is_sequence_container());
    BOOST_CHECK(!type.is_associative_container());
    BOOST_CHECK(!type.is_smart_pointer());
    BOOST_CHECK(type.children().empty());

    BOOST_CHECK(is_type_zero(p.name()));
    BOOST_CHECK(!p.documentation().empty());
    BOOST_REQUIRE(p.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(p.namespaces().back()));
    BOOST_CHECK(!p.has_primitive_properties());
    BOOST_CHECK(!p.requires_stream_manipulators());
    BOOST_CHECK(!p.requires_manual_move_constructor());
    BOOST_CHECK(!p.requires_manual_default_constructor());
    BOOST_CHECK(p.parents().empty());
    BOOST_CHECK(!p.is_parent());
    BOOST_CHECK(p.original_parent_name().empty());
    BOOST_CHECK(p.original_parent_name_qualified().empty());
    BOOST_CHECK(p.leaves().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
    BOOST_CHECK(!p.is_comparable());
    BOOST_CHECK(!p.is_visitable());
    BOOST_CHECK(!p.is_immutable());
    BOOST_CHECK(!p.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_pod_with_bool_property_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_pod_bool_with_property_results_in_expected_class_info");

    auto pt(mock_model_factory::property_types::boolean);
    auto m(mock_model_factory::pod_with_property(pt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    auto i(m.pods().begin());
    if (!is_type_zero(i->first.type_name()) && i != m.pods().end())
        ++i;

    BOOST_REQUIRE(i != m.pods().end());

    dogen::cpp::transformer t(m);
    const auto p(t.transform(i->second));
    BOOST_LOG_SEV(lg, debug) << "class: " << p;

    BOOST_CHECK(p.all_properties().size() == 1);
    BOOST_REQUIRE(p.properties().size() == 1);
    const auto type(p.properties().begin()->type());
    BOOST_CHECK(check_name(type.name()));
    BOOST_CHECK(check_name(type.complete_name()));
    BOOST_CHECK(check_name(type.identifiable_name()));
    BOOST_CHECK(check_name(type.complete_identifiable_name()));
    BOOST_CHECK(!type.is_enumeration());
    BOOST_CHECK(type.is_primitive());
    BOOST_CHECK(!type.is_char_like());
    BOOST_CHECK(!type.is_int_like());
    BOOST_CHECK(!type.is_string_like());
    BOOST_CHECK(!type.is_optional_like());
    BOOST_CHECK(!type.is_pair());
    BOOST_CHECK(!type.is_variant_like());
    BOOST_CHECK(!type.is_filesystem_path());
    BOOST_CHECK(!type.is_date());
    BOOST_CHECK(!type.is_ptime());
    BOOST_CHECK(!type.is_time_duration());
    BOOST_CHECK(!type.is_sequence_container());
    BOOST_CHECK(!type.is_associative_container());
    BOOST_CHECK(!type.is_smart_pointer());
    BOOST_CHECK(type.children().empty());

    BOOST_CHECK(is_type_zero(p.name()));
    BOOST_CHECK(!p.documentation().empty());
    BOOST_REQUIRE(p.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(p.namespaces().back()));
    BOOST_CHECK(p.has_primitive_properties());
    BOOST_CHECK(p.requires_stream_manipulators());
    BOOST_CHECK(!p.requires_manual_move_constructor());
    BOOST_CHECK(p.requires_manual_default_constructor());
    BOOST_CHECK(p.parents().empty());
    BOOST_CHECK(!p.is_parent());
    BOOST_CHECK(p.original_parent_name().empty());
    BOOST_CHECK(p.original_parent_name_qualified().empty());
    BOOST_CHECK(p.leaves().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
    BOOST_CHECK(!p.is_comparable());
    BOOST_CHECK(!p.is_visitable());
    BOOST_CHECK(!p.is_immutable());
    BOOST_CHECK(!p.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_pod_with_unsigned_int_property_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_pod_unsigned_int_with_property_results_in_expected_class_info");

    auto pt(mock_model_factory::property_types::unsigned_int);
    auto m(mock_model_factory::pod_with_property(pt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    auto i(m.pods().begin());
    if (!is_type_zero(i->first.type_name()) && i != m.pods().end())
        ++i;

    BOOST_REQUIRE(i != m.pods().end());

    dogen::cpp::transformer t(m);
    const auto p(t.transform(i->second));
    BOOST_LOG_SEV(lg, debug) << "class: " << p;

    BOOST_CHECK(p.all_properties().size() == 1);
    BOOST_REQUIRE(p.properties().size() == 1);

    const auto type(p.properties().begin()->type());
    BOOST_CHECK(check_name(type.identifiable_name()));
    BOOST_CHECK(check_name(type.complete_identifiable_name()));
    BOOST_CHECK(!type.is_enumeration());
    BOOST_CHECK(type.is_primitive());
    BOOST_CHECK(!type.is_char_like());
    BOOST_CHECK(type.is_int_like());
    BOOST_CHECK(!type.is_string_like());
    BOOST_CHECK(!type.is_optional_like());
    BOOST_CHECK(!type.is_pair());
    BOOST_CHECK(!type.is_variant_like());
    BOOST_CHECK(!type.is_filesystem_path());
    BOOST_CHECK(!type.is_date());
    BOOST_CHECK(!type.is_ptime());
    BOOST_CHECK(!type.is_time_duration());
    BOOST_CHECK(!type.is_sequence_container());
    BOOST_CHECK(!type.is_associative_container());
    BOOST_CHECK(!type.is_smart_pointer());
    BOOST_CHECK(type.children().empty());

    BOOST_CHECK(is_type_zero(p.name()));
    BOOST_CHECK(!p.documentation().empty());
    BOOST_REQUIRE(p.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(p.namespaces().back()));
    BOOST_CHECK(p.has_primitive_properties());
    BOOST_CHECK(!p.requires_stream_manipulators());
    BOOST_CHECK(!p.requires_manual_move_constructor());
    BOOST_CHECK(p.requires_manual_default_constructor());
    BOOST_CHECK(p.parents().empty());
    BOOST_CHECK(!p.is_parent());
    BOOST_CHECK(p.original_parent_name().empty());
    BOOST_CHECK(p.original_parent_name_qualified().empty());
    BOOST_CHECK(p.leaves().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
    BOOST_CHECK(!p.is_comparable());
    BOOST_CHECK(!p.is_visitable());
    BOOST_CHECK(!p.is_immutable());
    BOOST_CHECK(!p.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_pod_with_boost_variant_property_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_pod_boost_variant_with_property_results_in_expected_class_info");

    auto pt(mock_model_factory::property_types::boost_variant);
    auto m(mock_model_factory::pod_with_property(pt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    auto i(m.pods().begin());
    if (!is_type_zero(i->first.type_name()) && i != m.pods().end())
        ++i;

    BOOST_REQUIRE(i != m.pods().end());

    dogen::cpp::transformer t(m);
    const auto p(t.transform(i->second));
    BOOST_LOG_SEV(lg, debug) << "class: " << p;

    BOOST_CHECK(p.all_properties().size() == 1);
    BOOST_REQUIRE(p.properties().size() == 1);

    const auto type(p.properties().begin()->type());
    BOOST_CHECK(check_scoped_name(type.name()));
    BOOST_CHECK(check_scoped_name(type.complete_name()));
    BOOST_CHECK(check_name(type.identifiable_name()));
    BOOST_CHECK(check_name(type.complete_identifiable_name()));
    BOOST_CHECK(!type.is_enumeration());
    BOOST_CHECK(!type.is_primitive());
    BOOST_CHECK(!type.is_char_like());
    BOOST_CHECK(!type.is_int_like());
    BOOST_CHECK(!type.is_string_like());
    BOOST_CHECK(!type.is_optional_like());
    BOOST_CHECK(!type.is_pair());
    BOOST_CHECK(type.is_variant_like());
    BOOST_CHECK(!type.is_filesystem_path());
    BOOST_CHECK(!type.is_date());
    BOOST_CHECK(!type.is_ptime());
    BOOST_CHECK(!type.is_time_duration());
    BOOST_CHECK(!type.is_sequence_container());
    BOOST_CHECK(!type.is_associative_container());
    BOOST_CHECK(!type.is_smart_pointer());
    BOOST_CHECK(type.children().size() == 2);

    BOOST_CHECK(is_type_zero(p.name()));
    BOOST_CHECK(!p.documentation().empty());
    BOOST_REQUIRE(p.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(p.namespaces().back()));
    BOOST_CHECK(!p.has_primitive_properties());
    BOOST_CHECK(!p.requires_stream_manipulators());
    BOOST_CHECK(p.requires_manual_move_constructor());
    BOOST_CHECK(!p.requires_manual_default_constructor());
    BOOST_CHECK(p.parents().empty());
    BOOST_CHECK(!p.is_parent());
    BOOST_CHECK(p.original_parent_name().empty());
    BOOST_CHECK(p.original_parent_name_qualified().empty());
    BOOST_CHECK(p.leaves().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
    BOOST_CHECK(!p.is_comparable());
    BOOST_CHECK(!p.is_visitable());
    BOOST_CHECK(!p.is_immutable());
    BOOST_CHECK(!p.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_pod_with_parent_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_pod_with_parent_results_in_expected_class_info");

    auto m(mock_model_factory::pod_with_parent_in_the_same_model(true));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::transformer t(m);
    dogen::cpp::class_info p1;
    bool found_one(false);
    for (const auto& pair : m.pods()) {
        if (is_type_one(pair.first.type_name())) {
            found_one = true;
            p1 = t.transform(pair.second);
            BOOST_LOG_SEV(lg, debug) << "class 1: " << p1;

            BOOST_CHECK(is_type_one(p1.name()));
            BOOST_CHECK(p1.all_properties().size() == 1);
            BOOST_CHECK(p1.properties().size() == 1);
            BOOST_CHECK(p1.parents().empty());
            BOOST_CHECK(p1.is_parent());
            BOOST_CHECK(p1.original_parent_name().empty());
            BOOST_CHECK(p1.original_parent_name_qualified().empty());
            BOOST_CHECK(p1.leaves().size() == 1);
            BOOST_CHECK(!p1.is_original_parent_visitable());
        }
    }
    BOOST_CHECK(found_one);

    bool found_zero(false);
    for (const auto& pair : m.pods()) {
        if (is_type_zero(pair.first.type_name())) {
            found_zero = true;
            const auto p(t.transform(pair.second, p1, p1));
            BOOST_LOG_SEV(lg, debug) << "class 0: " << p;

            BOOST_CHECK(is_type_zero(p.name()));
            BOOST_CHECK(p.all_properties().size() == 2);
            BOOST_CHECK(p.properties().size() == 1);
            BOOST_CHECK(p.parents().size() == 1);
            BOOST_CHECK(!p.is_parent());
            BOOST_CHECK(is_type_one(p.parents().front().name()));
            BOOST_CHECK(is_type_one(p.original_parent_name()));
            BOOST_CHECK(!p.original_parent_name_qualified().empty());
            BOOST_CHECK(p.leaves().empty());
            BOOST_CHECK(!p.is_original_parent_visitable());
        }
    }
    BOOST_CHECK(found_zero);
}

BOOST_AUTO_TEST_CASE(supplying_parent_class_info_for_type_without_parent_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_parent_class_info_for_type_without_parent_throws");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);

    dogen::cpp::transformer t(m);
    const auto pod0(m.pods().begin()->second);
    const auto p(t.transform(pod0));

    using dogen::cpp::transformation_error;
    contains_checker<transformation_error> c(unexpected_parent_info);
    BOOST_CHECK_EXCEPTION(t.transform(pod0, p, p), transformation_error, c);
}

BOOST_AUTO_TEST_CASE(not_supplying_parent_class_info_for_type_with_parent_throws) {
    SETUP_TEST_LOG_SOURCE("not_supplying_parent_class_info_for_type_with_parent_throws");

    auto m(mock_model_factory::pod_with_parent_in_the_same_model(true));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.pods().size() == 2);

    dogen::cpp::transformer t(m);
    bool found_zero(false);
    for (const auto& pair : m.pods()) {
        if (is_type_zero(pair.first.type_name())) {
            found_zero = true;
            using dogen::cpp::transformation_error;
            contains_checker<transformation_error> c(no_parent_info);
            const auto p(pair.second);
            BOOST_CHECK_EXCEPTION(t.transform(p), transformation_error, c);
        }
    }
    BOOST_CHECK(found_zero);
}

BOOST_AUTO_TEST_CASE(not_supplying_original_parent_class_info_for_type_with_parent_throws) {
    SETUP_TEST_LOG_SOURCE("not_supplying_original_parent_class_info_for_type_with_parent_throws");

    auto m(mock_model_factory::pod_with_parent_in_the_same_model(true));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::transformer t(m);
    dogen::cpp::class_info p1;
    bool found_one(false);
    for (const auto& pair : m.pods()) {
        if (is_type_one(pair.first.type_name())) {
            found_one = true;
            p1 = t.transform(pair.second);
            BOOST_LOG_SEV(lg, debug) << "class 1: " << p1;
        }
    }
    BOOST_CHECK(found_one);

    bool found_zero(false);
    for (const auto& pair : m.pods()) {
        if (is_type_zero(pair.first.type_name())) {
            found_zero = true;
            using dogen::cpp::transformation_error;
            contains_checker<transformation_error> c(no_parent_info);
            const auto p(pair.second);
            BOOST_CHECK_EXCEPTION(t.transform(p, p1), transformation_error, c);
        }
    }
    BOOST_CHECK(found_zero);
}

BOOST_AUTO_TEST_CASE(transforming_third_degree_pod_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_third_degree_pod_results_in_expected_class_info");

    auto m(
        mock_model_factory::pod_with_third_degree_parent_in_same_model(true));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::transformer t(m);
    dogen::cpp::class_info p3;
    bool found_three(false);
    for (const auto& pair : m.pods()) {
        if (is_type_three(pair.first.type_name())) {
            found_three = true;
            p3 = t.transform(pair.second);
            BOOST_LOG_SEV(lg, debug) << "class 3: " << p3;

            BOOST_CHECK(is_type_three(p3.name()));
            BOOST_CHECK(p3.all_properties().size() == 1);
            BOOST_CHECK(p3.properties().size() == 1);
            BOOST_CHECK(p3.parents().empty());
            BOOST_CHECK(p3.is_parent());
            BOOST_CHECK(p3.original_parent_name().empty());
            BOOST_CHECK(p3.original_parent_name_qualified().empty());
            BOOST_REQUIRE(p3.leaves().size() == 1);
            BOOST_CHECK(ends_with_type_zero(p3.leaves().front()));
        }
    }
    BOOST_CHECK(found_three);

    dogen::cpp::class_info p2;
    bool found_two(false);
    for (const auto& pair : m.pods()) {
        if (is_type_two(pair.first.type_name())) {
            found_two = true;
            p2 = t.transform(pair.second, p3, p3);
            BOOST_LOG_SEV(lg, debug) << "class 2: " << p2;

            BOOST_CHECK(is_type_two(p2.name()));
            BOOST_CHECK(p2.all_properties().size() == 2);
            BOOST_CHECK(p2.properties().size() == 1);
            BOOST_CHECK(!p2.parents().empty());
            BOOST_CHECK(p2.is_parent());
            BOOST_CHECK(is_type_three(p2.original_parent_name()));
            BOOST_CHECK(!p2.original_parent_name_qualified().empty());
            BOOST_REQUIRE(p2.leaves().size() == 1);
            BOOST_CHECK(ends_with_type_zero(p2.leaves().front()));
        }
    }
    BOOST_CHECK(found_two);

    dogen::cpp::class_info p1;
    bool found_one(false);
    for (const auto& pair : m.pods()) {
        if (is_type_one(pair.first.type_name())) {
            found_one = true;
            p1 = t.transform(pair.second, p2, p3);
            BOOST_LOG_SEV(lg, debug) << "class 1: " << p1;

            BOOST_CHECK(is_type_one(p1.name()));
            BOOST_CHECK(p1.all_properties().size() == 3);
            BOOST_CHECK(p1.properties().size() == 1);
            BOOST_REQUIRE(p1.parents().size() == 1);
            BOOST_CHECK(p1.is_parent());
            BOOST_CHECK(is_type_two(p1.parents().front().name()));
            BOOST_CHECK(is_type_three(p1.original_parent_name()));
            BOOST_CHECK(!p1.original_parent_name_qualified().empty());
            BOOST_REQUIRE(p1.leaves().size() == 1);
            BOOST_CHECK(ends_with_type_zero(p1.leaves().front()));
        }
    }
    BOOST_CHECK(found_one);

    bool found_zero(false);
    for (const auto& pair : m.pods()) {
        if (is_type_zero(pair.first.type_name())) {
            found_zero = true;
            const auto p(t.transform(pair.second, p1, p3));
            BOOST_LOG_SEV(lg, debug) << "class 0: " << p;

            BOOST_CHECK(is_type_zero(p.name()));
            BOOST_CHECK(p.all_properties().size() == 4);
            BOOST_CHECK(p.properties().size() == 1);
            BOOST_REQUIRE(p.parents().size() == 1);
            BOOST_CHECK(!p.is_parent());
            BOOST_CHECK(is_type_one(p.parents().front().name()));
            BOOST_CHECK(is_type_three(p.original_parent_name()));
            BOOST_CHECK(!p.original_parent_name_qualified().empty());
            BOOST_CHECK(p.leaves().empty());
        }
    }
    BOOST_CHECK(found_zero);
}

BOOST_AUTO_TEST_SUITE_END()
