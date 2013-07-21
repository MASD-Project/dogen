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
#include "dogen/cpp/io/context_io.hpp"

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
typedef dogen::sml::test::mock_model_factory factory;

BOOST_AUTO_TEST_SUITE(transformer)

BOOST_AUTO_TEST_CASE(transforming_enumeration_results_in_expected_enum_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_results_in_expected_enum_info");

    const auto ot(object_types::enumeration);
    const auto m(factory::build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*m.objects().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.enumerations().size() == 1);
    const auto e(c.enumerations().begin()->second);
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
    const auto m0(factory::build_single_type_model_in_module(0, ot, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.objects().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m0, c);
    t.from_type(*m0.objects().begin()->second);
    BOOST_REQUIRE(c.enumerations().size() == 1);
    const auto e0(c.enumerations().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "enumeration 0: " << e0;

    BOOST_CHECK(is_type_zero(e0.name()));
    BOOST_CHECK(!e0.documentation().empty());
    BOOST_REQUIRE(e0.namespaces().size() == 2);
    BOOST_CHECK(is_model_zero(e0.namespaces().front()));
    BOOST_CHECK(is_module_zero(e0.namespaces().back()));

    BOOST_REQUIRE(e0.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e0.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e0.enumerators().back().name()));

    const auto m1(factory::build_single_type_model_in_module(0, ot, 2));
    BOOST_LOG_SEV(lg, debug) << "model 1: " << m1;
    BOOST_REQUIRE(m0.enumerations().size() == 2);

    t.from_type(*m1.objects().begin()->second);
    BOOST_REQUIRE(c.enumerations().size() == 3);
    bool found_zero(false);
    for (const auto& pair : c.enumerations()) {
        if (is_type_zero(pair.first.simple_name())) {
            found_zero = true;
            const auto e1(pair.second);
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
    }
    BOOST_REQUIRE(found_zero);
}

BOOST_AUTO_TEST_CASE(transforming_enumeration_in_external_module_results_in_expected_enum_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_in_external_module_results_in_expected_enum_info");

    const auto ot(object_types::enumeration);
    auto m(factory::build_single_type_model_in_module(0, ot));
    BOOST_REQUIRE(m.objects().size() == 1);
    auto enumeration(m.enumerations().begin()->second);
    enumeration.name().external_module_path().push_back(external_module);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*m.objects().begin()->second);
    BOOST_REQUIRE(c.enumerations().size() == 1);
    const auto e(c.enumerations().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "enumeration: " << e;

    BOOST_REQUIRE(e.namespaces().size() == 2);
    BOOST_CHECK(e.namespaces().front() == external_module);
    BOOST_CHECK(is_model_zero(e.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_exception_results_in_expected_exception_info) {
    SETUP_TEST_LOG_SOURCE("transforming_exception_results_in_expected_exception_info");

    const auto ot(object_types::exception);
    const auto m(factory::build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*m.objects().begin()->second);
    BOOST_REQUIRE(c.exceptions().size() == 1);
    const auto e(c.exceptions().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "exception: " << e;

    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());
    BOOST_REQUIRE(e.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(e.namespaces().front()));
}

BOOST_AUTO_TEST_CASE(transforming_exception_in_module_results_in_expected_exception_info) {
    SETUP_TEST_LOG_SOURCE("transforming_exception_in_module_results_in_expected_exception_info");

    const auto ot(object_types::exception);
    const auto m0(factory::build_single_type_model_in_module(0, ot, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.objects().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m0, c);
    t.from_type(*m0.objects().begin()->second);
    BOOST_REQUIRE(c.exceptions().size() == 1);
    const auto e0(c.exceptions().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "exception 0: " << e0;

    BOOST_CHECK(is_type_zero(e0.name()));
    BOOST_CHECK(!e0.documentation().empty());
    BOOST_REQUIRE(e0.namespaces().size() == 2);
    BOOST_CHECK(is_model_zero(e0.namespaces().front()));
    BOOST_CHECK(is_module_zero(e0.namespaces().back()));

    c.exceptions().clear();
    const auto m1(factory::build_single_type_model_in_module(0, ot, 2));
    BOOST_LOG_SEV(lg, debug) << "model 1: " << m1;
    BOOST_REQUIRE(m0.objects().size() == 2);

    t.from_type(*m1.objects().begin()->second);
    BOOST_REQUIRE(c.exceptions().size() == 2);
    bool found_zero(false);
    for (const auto& pair : c.exceptions()) {
        if (is_type_one(pair.first.simple_name())) {
            found_zero = true;
            const auto& e(pair.second);
            BOOST_LOG_SEV(lg, debug) << "exception 1: " << e;
            BOOST_CHECK(is_type_zero(e.name()));
            BOOST_CHECK(!e.documentation().empty());
            BOOST_REQUIRE(e.namespaces().size() == 3);
            BOOST_CHECK(is_model_zero(e.namespaces().front()));
            BOOST_CHECK(is_module_one(e.namespaces().back()));
        }
    }
    BOOST_REQUIRE(found_zero);
}

BOOST_AUTO_TEST_CASE(transforming_exception_in_external_module_results_in_expected_exception_info) {
    SETUP_TEST_LOG_SOURCE("transforming_exception_in_external_module_results_in_expected_exception_info");

    const auto ot(object_types::exception);
    auto m(factory::build_single_type_model_in_module(0, ot));
    BOOST_REQUIRE(m.objects().size() == 1);
    auto& exception(*m.objects().begin()->second);
    exception.name().external_module_path().push_back(external_module);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*m.objects().begin()->second);
    BOOST_REQUIRE(c.exceptions().size() == 1);
    const auto e(c.exceptions().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "exception: " << e;

    BOOST_REQUIRE(e.namespaces().size() == 2);
    BOOST_CHECK(e.namespaces().front() == external_module);
    BOOST_CHECK(is_model_zero(e.namespaces().back()));
}
/*
BOOST_AUTO_TEST_CASE(transforming_module_results_in_expected_namespace_info) {
    SETUP_TEST_LOG_SOURCE("transforming_module_results_in_expected_namespace_info");

    const auto ot(object_types::exception);
    const auto m0(factory::build_single_type_model_in_module(0, ot, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.modules().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m0, c);
    t.from_type(*m0.objects().begin()->second);

    BOOST_REQUIRE(c.namespaces().size() == 2);
    bool found_zero(false);
    for (const auto& pair : c.exceptions()) {
        if (is_type_one(pair.first.simple_name())) {

    const auto n0(c.namespaces().front());
    BOOST_LOG_SEV(lg, debug) << "namespace 0: " << n0;

    BOOST_CHECK(!n0.documentation().empty());
    BOOST_REQUIRE(n0.namespaces().size() == 1);
    BOOST_CHECK(is_module_zero(n0.namespaces().front()));

    const auto m1(factory::build_single_type_model_in_module(0, ot, 2));
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
    const auto m(factory::build_single_type_model_in_module(0, ot));
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
    auto m(factory::build_single_type_model_in_module(0, ot, 1));
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

BOOST_AUTO_TEST_CASE(transforming_object_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_object_results_in_expected_class_info");

    auto m(factory::build_single_type_model_in_module());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*m.objects().begin()->second);

    BOOST_REQUIRE(c.classes().size() == 1);
    const auto ci(c.classes().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "class: " << ci;
    BOOST_CHECK(is_type_zero(ci.name()));
    BOOST_CHECK(!ci.documentation().empty());
    BOOST_REQUIRE(ci.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(ci.namespaces().back()));

    BOOST_CHECK(ci.properties().empty());
    BOOST_CHECK(ci.all_properties().empty());
    BOOST_CHECK(!ci.has_primitive_properties());
    BOOST_CHECK(!ci.requires_stream_manipulators());
    BOOST_CHECK(!ci.requires_manual_move_constructor());
    BOOST_CHECK(!ci.requires_manual_default_constructor());
    BOOST_CHECK(ci.parents().empty());
    BOOST_CHECK(!ci.is_parent());
    BOOST_CHECK(ci.original_parent_name().empty());
    BOOST_CHECK(ci.original_parent_name_qualified().empty());
    BOOST_CHECK(ci.leaves().empty());
    BOOST_CHECK(ci.implementation_specific_parameters().empty());
    BOOST_CHECK(!ci.is_comparable());
    BOOST_CHECK(!ci.is_visitable());
    BOOST_CHECK(!ci.is_immutable());
    BOOST_CHECK(!ci.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_object_with_property_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_object_with_property_results_in_expected_class_info");

    auto m(factory::object_with_property());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    auto i(m.objects().begin());
    if (!is_type_zero(i->first.simple_name()) && i != m.objects().end())
        ++i;

    BOOST_REQUIRE(i != m.objects().end());

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*i->second);

    BOOST_REQUIRE(c.classes().size() == 1);
    const auto ci(c.classes().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "class: " << ci;

    BOOST_CHECK(ci.all_properties().size() == 1);
    BOOST_REQUIRE(ci.properties().size() == 1);
    const auto type(ci.properties().begin()->type());
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

    BOOST_CHECK(is_type_zero(ci.name()));
    BOOST_CHECK(!ci.documentation().empty());
    BOOST_REQUIRE(ci.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(ci.namespaces().back()));
    BOOST_CHECK(!ci.has_primitive_properties());
    BOOST_CHECK(!ci.requires_stream_manipulators());
    BOOST_CHECK(!ci.requires_manual_move_constructor());
    BOOST_CHECK(!ci.requires_manual_default_constructor());
    BOOST_CHECK(ci.parents().empty());
    BOOST_CHECK(!ci.is_parent());
    BOOST_CHECK(ci.original_parent_name().empty());
    BOOST_CHECK(ci.original_parent_name_qualified().empty());
    BOOST_CHECK(ci.leaves().empty());
    BOOST_CHECK(ci.implementation_specific_parameters().empty());
    BOOST_CHECK(!ci.is_comparable());
    BOOST_CHECK(!ci.is_visitable());
    BOOST_CHECK(!ci.is_immutable());
    BOOST_CHECK(!ci.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_object_with_bool_property_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_object_bool_with_property_results_in_expected_class_info");

    auto ot(object_types::value_object);
    auto pt(property_types::boolean);
    auto m(factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    auto i(m.objects().begin());
    if (!is_type_zero(i->first.simple_name()) && i != m.objects().end())
        ++i;

    BOOST_REQUIRE(i != m.objects().end());

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*i->second);

    BOOST_REQUIRE(c.classes().size() == 1);
    const auto ci(c.classes().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "class: " << ci;

    BOOST_CHECK(ci.all_properties().size() == 1);
    BOOST_REQUIRE(ci.properties().size() == 1);
    const auto type(ci.properties().begin()->type());
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

    BOOST_CHECK(is_type_zero(ci.name()));
    BOOST_CHECK(!ci.documentation().empty());
    BOOST_REQUIRE(ci.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(ci.namespaces().back()));
    BOOST_CHECK(ci.has_primitive_properties());
    BOOST_CHECK(ci.requires_stream_manipulators());
    BOOST_CHECK(!ci.requires_manual_move_constructor());
    BOOST_CHECK(ci.requires_manual_default_constructor());
    BOOST_CHECK(ci.parents().empty());
    BOOST_CHECK(!ci.is_parent());
    BOOST_CHECK(ci.original_parent_name().empty());
    BOOST_CHECK(ci.original_parent_name_qualified().empty());
    BOOST_CHECK(ci.leaves().empty());
    BOOST_CHECK(ci.implementation_specific_parameters().empty());
    BOOST_CHECK(!ci.is_comparable());
    BOOST_CHECK(!ci.is_visitable());
    BOOST_CHECK(!ci.is_immutable());
    BOOST_CHECK(!ci.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_object_with_unsigned_int_property_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_object_unsigned_int_with_property_results_in_expected_class_info");

    auto ot(object_types::value_object);
    auto ptfactory::property_types::unsigned_int);
    auto m(factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    auto i(m.objects().begin());
    if (!is_type_zero(i->first.simple_name()) && i != m.objects().end())
        ++i;

    BOOST_REQUIRE(i != m.objects().end());

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*i->second);

    BOOST_REQUIRE(c.classes().size() == 1);
    const auto ci(c.classes().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "class: " << ci;

    BOOST_CHECK(ci.all_properties().size() == 1);
    BOOST_REQUIRE(ci.properties().size() == 1);

    const auto type(ci.properties().begin()->type());
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

    BOOST_CHECK(is_type_zero(ci.name()));
    BOOST_CHECK(!ci.documentation().empty());
    BOOST_REQUIRE(ci.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(ci.namespaces().back()));
    BOOST_CHECK(ci.has_primitive_properties());
    BOOST_CHECK(!ci.requires_stream_manipulators());
    BOOST_CHECK(!ci.requires_manual_move_constructor());
    BOOST_CHECK(ci.requires_manual_default_constructor());
    BOOST_CHECK(ci.parents().empty());
    BOOST_CHECK(!ci.is_parent());
    BOOST_CHECK(ci.original_parent_name().empty());
    BOOST_CHECK(ci.original_parent_name_qualified().empty());
    BOOST_CHECK(ci.leaves().empty());
    BOOST_CHECK(ci.implementation_specific_parameters().empty());
    BOOST_CHECK(!ci.is_comparable());
    BOOST_CHECK(!ci.is_visitable());
    BOOST_CHECK(!ci.is_immutable());
    BOOST_CHECK(!ci.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_object_with_boost_variant_property_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_object_boost_variant_with_property_results_in_expected_class_info");

    auto ot(object_types::value_object);
    auto pt(factory::property_types::boost_variant);
    auto m(factory::object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    auto i(m.objects().begin());
    if (!is_type_zero(i->first.simple_name()) && i != m.objects().end())
        ++i;

    BOOST_REQUIRE(i != m.objects().end());

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    t.from_type(*i->second);

    BOOST_REQUIRE(c.classes().size() == 1);
    const auto ci(c.classes().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "class: " << ci;

    BOOST_CHECK(ci.all_properties().size() == 1);
    BOOST_REQUIRE(ci.properties().size() == 1);

    const auto type(ci.properties().begin()->type());
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

    BOOST_CHECK(is_type_zero(ci.name()));
    BOOST_CHECK(!ci.documentation().empty());
    BOOST_REQUIRE(ci.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(ci.namespaces().back()));
    BOOST_CHECK(!ci.has_primitive_properties());
    BOOST_CHECK(!ci.requires_stream_manipulators());
    BOOST_CHECK(ci.requires_manual_move_constructor());
    BOOST_CHECK(!ci.requires_manual_default_constructor());
    BOOST_CHECK(ci.parents().empty());
    BOOST_CHECK(!ci.is_parent());
    BOOST_CHECK(ci.original_parent_name().empty());
    BOOST_CHECK(ci.original_parent_name_qualified().empty());
    BOOST_CHECK(ci.leaves().empty());
    BOOST_CHECK(ci.implementation_specific_parameters().empty());
    BOOST_CHECK(!ci.is_comparable());
    BOOST_CHECK(!ci.is_visitable());
    BOOST_CHECK(!ci.is_immutable());
    BOOST_CHECK(!ci.is_original_parent_visitable());
}

BOOST_AUTO_TEST_CASE(transforming_object_with_parent_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_object_with_parent_results_in_expected_class_info");

    auto m(factory::object_with_parent_in_the_same_model(true));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    bool found_one(false);
    for (const auto& pair : m.objects()) {
        if (is_type_one(pair.first.simple_name())) {
            found_one = true;
            t.from_type(*pair.second);

            BOOST_REQUIRE(c.classes().size() == 1);
            const auto i(c.classes().find(pair.first));
            BOOST_REQUIRE(i != c.classes().end());
            const auto c1(i->second);
            BOOST_LOG_SEV(lg, debug) << "class 1: " << c1;

            BOOST_CHECK(is_type_one(c1.name()));
            BOOST_CHECK(c1.all_properties().size() == 1);
            BOOST_CHECK(c1.properties().size() == 1);
            BOOST_CHECK(c1.parents().empty());
            BOOST_CHECK(c1.is_parent());
            BOOST_CHECK(c1.original_parent_name().empty());
            BOOST_CHECK(c1.original_parent_name_qualified().empty());
            BOOST_CHECK(c1.leaves().size() == 1);
            BOOST_CHECK(!c1.is_original_parent_visitable());
        }
    }
    BOOST_CHECK(found_one);

    bool found_zero(false);
    for (const auto& pair : m.objects()) {
        if (is_type_zero(pair.first.simple_name())) {
            found_zero = true;
            t.from_type(*pair.second);

            BOOST_REQUIRE(c.classes().size() == 2);
            const auto i(c.classes().find(pair.first));
            BOOST_REQUIRE(i != c.classes().end());
            const auto c0(i->second);
            BOOST_LOG_SEV(lg, debug) << "class 0: " << c0;

            BOOST_CHECK(is_type_zero(c0.name()));
            BOOST_CHECK(c0.all_properties().size() == 2);
            BOOST_CHECK(c0.properties().size() == 1);
            BOOST_CHECK(c0.parents().size() == 1);
            BOOST_CHECK(!c0.is_parent());
            BOOST_CHECK(is_type_one(c0.parents().front().name()));
            BOOST_CHECK(is_type_one(c0.original_parent_name()));
            BOOST_CHECK(!c0.original_parent_name_qualified().empty());
            BOOST_CHECK(c0.leaves().empty());
            BOOST_CHECK(!c0.is_original_parent_visitable());
        }
    }
    BOOST_CHECK(found_zero);
}

BOOST_AUTO_TEST_CASE(supplying_parent_class_info_for_type_without_parent_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_parent_class_info_for_type_without_parent_throws");

    const auto m(factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    const auto& ao(*m.objects().begin()->second);
    t.from_type(ao);

    using dogen::cpp::transformation_error;
    contains_checker<transformation_error> cc(unexpected_parent_info);
    BOOST_CHECK_EXCEPTION(t.from_type(ao), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(not_supplying_parent_class_info_for_type_with_parent_throws) {
    SETUP_TEST_LOG_SOURCE("not_supplying_parent_class_info_for_type_with_parent_throws");

    auto m(factory::object_with_parent_in_the_same_model(true));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    bool found_zero(false);
    for (const auto& pair : m.objects()) {
        if (is_type_zero(pair.first.simple_name())) {
            found_zero = true;
            using dogen::cpp::transformation_error;
            contains_checker<transformation_error> cc(no_parent_info);
            const auto& ao(*pair.second);
            BOOST_CHECK_EXCEPTION(t.from_type(ao), transformation_error, cc);
        }
    }
    BOOST_CHECK(found_zero);
}

BOOST_AUTO_TEST_CASE(not_supplying_original_parent_class_info_for_type_with_parent_throws) {
    SETUP_TEST_LOG_SOURCE("not_supplying_original_parent_class_info_for_type_with_parent_throws");

    auto m(factory::object_with_parent_in_the_same_model(true));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    bool found_one(false);
    for (const auto& pair : m.objects()) {
        if (is_type_one(pair.first.simple_name())) {
            found_one = true;
            t.from_type(*pair.second);

            BOOST_REQUIRE(c.classes().size() == 1);
            const auto i(c.classes().find(pair.first));
            BOOST_REQUIRE(i != c.classes().end());
            const auto c1(i->second);
            BOOST_LOG_SEV(lg, debug) << "class 1: " << c1;
        }
    }
    BOOST_CHECK(found_one);

    bool found_zero(false);
    for (const auto& pair : m.objects()) {
        if (is_type_zero(pair.first.simple_name())) {
            found_zero = true;
            using dogen::cpp::transformation_error;
            contains_checker<transformation_error> cc(no_parent_info);
            const auto& ao(*pair.second);
            BOOST_CHECK_EXCEPTION(t.from_type(ao), transformation_error, cc);
        }
    }
    BOOST_CHECK(found_zero);
}

BOOST_AUTO_TEST_CASE(transforming_third_degree_object_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_third_degree_object_results_in_expected_class_info");

    auto m(factory::
        object_with_third_degree_parent_in_same_model(true));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::context c;
    dogen::cpp::transformer t(m, c);
    bool found_three(false);
    for (const auto& pair : m.objects()) {
        if (is_type_three(pair.first.simple_name())) {
            found_three = true;
            t.from_type(*pair.second);
        }
    }
    BOOST_CHECK(found_three);

    bool found_two(false);
    for (const auto& pair : m.objects()) {
        if (is_type_two(pair.first.simple_name())) {
            found_two = true;
            t.from_type(*pair.second);
        }
    }
    BOOST_CHECK(found_two);

    bool found_one(false);
    for (const auto& pair : m.objects()) {
        if (is_type_one(pair.first.simple_name())) {
            found_one = true;
            t.from_type(*pair.second);
        }
    }
    BOOST_CHECK(found_one);

    bool found_zero(false);
    for (const auto& pair : m.objects()) {
        if (is_type_zero(pair.first.simple_name())) {
            found_zero = true;
            t.from_type(*pair.second);
        }
    }
    BOOST_CHECK(found_zero);

    BOOST_REQUIRE(c.classes().size() == 4);
    for (const auto& pair : c.classes()) {
        const auto& ci(pair.second);
        if (is_type_three(ci.name())) {
            BOOST_LOG_SEV(lg, debug) << "class 3: " << ci;
            BOOST_CHECK(is_type_three(ci.name()));
            BOOST_CHECK(ci.all_properties().size() == 1);
            BOOST_CHECK(ci.properties().size() == 1);
            BOOST_CHECK(ci.parents().empty());
            BOOST_CHECK(ci.is_parent());
            BOOST_CHECK(ci.original_parent_name().empty());
            BOOST_CHECK(ci.original_parent_name_qualified().empty());
            BOOST_REQUIRE(ci.leaves().size() == 1);
            BOOST_CHECK(ends_with_type_zero(ci.leaves().front()));
        } else if (is_type_two(ci.name())) {
            BOOST_LOG_SEV(lg, debug) << "class 2: " << ci;
            BOOST_CHECK(ci.all_properties().size() == 2);
            BOOST_CHECK(ci.properties().size() == 1);
            BOOST_CHECK(!ci.parents().empty());
            BOOST_CHECK(ci.is_parent());
            BOOST_CHECK(is_type_three(ci.original_parent_name()));
            BOOST_CHECK(!ci.original_parent_name_qualified().empty());
            BOOST_REQUIRE(ci.leaves().size() == 1);
            BOOST_CHECK(ends_with_type_zero(ci.leaves().front()));
        } else if (is_type_one(ci.name())) {
            found_one = true;
            BOOST_LOG_SEV(lg, debug) << "class 1: " << ci;
            BOOST_CHECK(is_type_one(ci.name()));
            BOOST_CHECK(ci.all_properties().size() == 3);
            BOOST_CHECK(ci.properties().size() == 1);
            BOOST_REQUIRE(ci.parents().size() == 1);
            BOOST_CHECK(ci.is_parent());
            BOOST_CHECK(is_type_two(ci.parents().front().name()));
            BOOST_CHECK(is_type_three(ci.original_parent_name()));
            BOOST_CHECK(!ci.original_parent_name_qualified().empty());
            BOOST_REQUIRE(ci.leaves().size() == 1);
            BOOST_CHECK(ends_with_type_zero(ci.leaves().front()));
        } else if (is_type_zero(ci.name())) {
            BOOST_LOG_SEV(lg, debug) << "class 0: " << ci;
            BOOST_CHECK(is_type_zero(ci.name()));
            BOOST_CHECK(ci.all_properties().size() == 4);
            BOOST_CHECK(ci.properties().size() == 1);
            BOOST_REQUIRE(ci.parents().size() == 1);
            BOOST_CHECK(!ci.is_parent());
            BOOST_CHECK(is_type_one(ci.parents().front().name()));
            BOOST_CHECK(is_type_three(ci.original_parent_name()));
            BOOST_CHECK(!ci.original_parent_name_qualified().empty());
            BOOST_CHECK(ci.leaves().empty());
        }
    }
}
*/
BOOST_AUTO_TEST_SUITE_END()
