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
const std::string external_package("some_package");

const std::string no_parent_info("Type has a parent ");
const std::string unexpected_parent_info("Type does not have a parent");

bool is_type_zero(const std::string& n) {
    return mock_model_factory::type_name(0) == n;
}

bool is_type_one(const std::string& n) {
    return mock_model_factory::type_name(1) == n;
}

bool is_package_zero(const std::string& n) {
    return mock_model_factory::package_name(0) == n;
}

bool is_package_one(const std::string& n) {
    return mock_model_factory::package_name(1) == n;
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

BOOST_AUTO_TEST_SUITE(transformer)

BOOST_AUTO_TEST_CASE(transforming_enumeration_results_in_expected_enumeration_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_results_in_expected_enumeration_info");

    const auto mt(dogen::sml::meta_types::enumeration);
    const auto m(mock_model_factory::build_single_type_model(0, mt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    dogen::cpp::transformer t(m);
    const auto e(t.transform(m.enumerations().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "enumeration: " << e;

    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());
    BOOST_CHECK(e.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(e.namespaces().front()));
    BOOST_CHECK(e.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e.enumerators().back().name()));
}

BOOST_AUTO_TEST_CASE(transforming_enumeration_in_package_results_in_expected_enumeration_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_in_package_results_in_expected_enumeration_info");

    const auto mt(dogen::sml::meta_types::enumeration);
    const auto m0(
        mock_model_factory::build_single_type_model_in_package(0, mt, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.enumerations().size() == 1);

    dogen::cpp::transformer t(m0);
    const auto e0(t.transform(m0.enumerations().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "enumeration 0: " << e0;

    BOOST_CHECK(is_type_zero(e0.name()));
    BOOST_CHECK(!e0.documentation().empty());
    BOOST_CHECK(e0.namespaces().size() == 2);
    BOOST_CHECK(is_model_zero(e0.namespaces().front()));
    BOOST_CHECK(is_package_zero(e0.namespaces().back()));

    BOOST_CHECK(e0.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e0.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e0.enumerators().back().name()));

    const auto m1(
        mock_model_factory::build_single_type_model_in_package(0, mt, 2));
    BOOST_LOG_SEV(lg, debug) << "model 1: " << m1;
    BOOST_REQUIRE(m0.enumerations().size() == 1);

    const auto e1(t.transform(m1.enumerations().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "enumeration 1: " << e1;
    BOOST_CHECK(is_type_zero(e1.name()));
    BOOST_CHECK(!e1.documentation().empty());
    BOOST_CHECK(e1.namespaces().size() == 3);
    BOOST_CHECK(is_model_zero(e1.namespaces().front()));
    BOOST_CHECK(is_package_one(e1.namespaces().back()));

    BOOST_CHECK(e1.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e1.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e1.enumerators().back().name()));
}

BOOST_AUTO_TEST_CASE(transforming_enumeration_in_external_package_results_in_expected_enumeration_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_in_external_package_results_in_expected_enumeration_info");

    const auto mt(dogen::sml::meta_types::enumeration);
    auto m(mock_model_factory::build_single_type_model_in_package(0, mt));
    BOOST_REQUIRE(m.enumerations().size() == 1);
    auto enumeration(m.enumerations().begin()->second);
    enumeration.name().external_package_path().push_back(external_package);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::transformer t(m);
    const auto e(t.transform(enumeration));
    BOOST_LOG_SEV(lg, debug) << "enumeration: " << e;

    BOOST_CHECK(e.namespaces().size() == 2);
    BOOST_CHECK(e.namespaces().front() == external_package);
    BOOST_CHECK(is_model_zero(e.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_exception_results_in_expected_exception_info) {
    SETUP_TEST_LOG_SOURCE("transforming_exception_results_in_expected_exception_info");

    const auto mt(dogen::sml::meta_types::exception);
    const auto m(mock_model_factory::build_single_type_model(0, mt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.exceptions().size() == 1);

    dogen::cpp::transformer t(m);
    const auto e(t.transform(m.exceptions().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "exception: " << e;

    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());
    BOOST_CHECK(e.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(e.namespaces().front()));
}

BOOST_AUTO_TEST_CASE(transforming_exception_in_package_results_in_expected_exception_info) {
    SETUP_TEST_LOG_SOURCE("transforming_exception_in_package_results_in_expected_exception_info");

    const auto mt(dogen::sml::meta_types::exception);
    const auto m0(
        mock_model_factory::build_single_type_model_in_package(0, mt, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.exceptions().size() == 1);

    dogen::cpp::transformer t(m0);
    const auto e0(t.transform(m0.exceptions().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "exception 0: " << e0;

    BOOST_CHECK(is_type_zero(e0.name()));
    BOOST_CHECK(!e0.documentation().empty());
    BOOST_CHECK(e0.namespaces().size() == 2);
    BOOST_CHECK(is_model_zero(e0.namespaces().front()));
    BOOST_CHECK(is_package_zero(e0.namespaces().back()));

    const auto m1(
        mock_model_factory::build_single_type_model_in_package(0, mt, 2));
    BOOST_LOG_SEV(lg, debug) << "model 1: " << m1;
    BOOST_REQUIRE(m0.exceptions().size() == 1);

    const auto e1(t.transform(m1.exceptions().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "exception 1: " << e1;
    BOOST_CHECK(is_type_zero(e1.name()));
    BOOST_CHECK(!e1.documentation().empty());
    BOOST_CHECK(e1.namespaces().size() == 3);
    BOOST_CHECK(is_model_zero(e1.namespaces().front()));
    BOOST_CHECK(is_package_one(e1.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_exception_in_external_package_results_in_expected_exception_info) {
    SETUP_TEST_LOG_SOURCE("transforming_exception_in_external_package_results_in_expected_exception_info");

    const auto mt(dogen::sml::meta_types::exception);
    auto m(mock_model_factory::build_single_type_model_in_package(0, mt));
    BOOST_REQUIRE(m.exceptions().size() == 1);
    auto exception(m.exceptions().begin()->second);
    exception.name().external_package_path().push_back(external_package);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::transformer t(m);
    const auto e(t.transform(exception));
    BOOST_LOG_SEV(lg, debug) << "exception: " << e;

    BOOST_CHECK(e.namespaces().size() == 2);
    BOOST_CHECK(e.namespaces().front() == external_package);
    BOOST_CHECK(is_model_zero(e.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_package_results_in_expected_package_info) {
    SETUP_TEST_LOG_SOURCE("transforming_package_results_in_expected_package_info");

    const auto mt(dogen::sml::meta_types::pod);
    const auto m0(
        mock_model_factory::build_single_type_model_in_package(0, mt, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.packages().size() == 1);

    dogen::cpp::transformer t(m0);
    const auto p0(t.transform(m0.packages().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "package 0: " << p0;

    BOOST_CHECK(!p0.documentation().empty());
    BOOST_CHECK(p0.namespaces().size() == 1);
    BOOST_CHECK(is_package_zero(p0.namespaces().front()));

    const auto m1(
        mock_model_factory::build_single_type_model_in_package(0, mt, 2));
    BOOST_LOG_SEV(lg, debug) << "model 1: " << m1;
    BOOST_REQUIRE(m1.packages().size() == 2);

    auto i(m1.packages().begin());
    if (!is_package_one(i->first.type_name()) && i != m1.packages().end())
        ++i;

    BOOST_REQUIRE(i != m1.packages().end());

    BOOST_CHECK(is_package_one(i->first.type_name()));
    const auto p1(t.transform(i->second));
    BOOST_LOG_SEV(lg, debug) << "package 1: " << p1;

    BOOST_CHECK(!p1.documentation().empty());
    BOOST_CHECK(p1.namespaces().size() == 2);
    BOOST_CHECK(is_package_zero(p1.namespaces().front()));
    BOOST_CHECK(is_package_one(p1.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_model_results_in_expected_package_info) {
    SETUP_TEST_LOG_SOURCE("transforming_model_results_in_expected_package_info");

    const auto mt(dogen::sml::meta_types::pod);
    const auto m(mock_model_factory::build_single_type_model_in_package(0, mt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::transformer t(m);
    const auto p(t.transform(m));
    BOOST_LOG_SEV(lg, debug) << "package: " << p;

    BOOST_CHECK(!p.documentation().empty());
    BOOST_CHECK(p.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(p.namespaces().front()));
}

BOOST_AUTO_TEST_CASE(transforming_package_in_external_package_results_in_expected_package_info) {
    SETUP_TEST_LOG_SOURCE("transforming_package_in_external_package_results_in_expected_package_info");

    const auto mt(dogen::sml::meta_types::pod);
    auto m(mock_model_factory::build_single_type_model_in_package(0, mt, 1));
    m.external_package_path().push_back(external_package);
    BOOST_REQUIRE(m.packages().size() == 1);
    auto package(m.packages().begin()->second);
    package.name().external_package_path().push_back(external_package);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::transformer t(m);
    const auto p0(t.transform(package));
    BOOST_LOG_SEV(lg, debug) << "package 0: " << p0;

    BOOST_CHECK(p0.namespaces().size() == 2);
    BOOST_CHECK(p0.namespaces().front() == external_package);
    BOOST_CHECK(is_package_zero(p0.namespaces().back()));

    const auto p1(t.transform(m));
    BOOST_LOG_SEV(lg, debug) << "package 1: " << p1;

    BOOST_CHECK(p1.namespaces().size() == 2);
    BOOST_CHECK(p1.namespaces().front() == external_package);
    BOOST_CHECK(is_model_zero(p1.namespaces().back()));
}

BOOST_AUTO_TEST_CASE(transforming_pod_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_pod_results_in_expected_class_info");

    auto m(mock_model_factory::build_single_type_model_in_package());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::cpp::transformer t(m);
    const auto p(t.transform(m.pods().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "class: " << p;
    BOOST_CHECK(is_type_zero(p.name()));
    BOOST_CHECK(!p.documentation().empty());
    BOOST_CHECK(p.namespaces().size() == 1);
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
    BOOST_CHECK(p.properties().size() == 1);
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
    BOOST_CHECK(p.namespaces().size() == 1);
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
    BOOST_CHECK(p.properties().size() == 1);
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
    BOOST_CHECK(p.namespaces().size() == 1);
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
    BOOST_CHECK(p.properties().size() == 1);

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
    BOOST_CHECK(p.namespaces().size() == 1);
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
    BOOST_CHECK(p.properties().size() == 1);

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
    BOOST_CHECK(p.namespaces().size() == 1);
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

BOOST_AUTO_TEST_CASE(transforming_with_parent_results_in_expected_class_info) {
    SETUP_TEST_LOG_SOURCE("transforming_with_parent_results_in_expected_class_info");

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
            BOOST_CHECK(!p1.is_parent());
            BOOST_CHECK(p1.original_parent_name().empty());
            BOOST_CHECK(p1.original_parent_name_qualified().empty());
            BOOST_CHECK(p1.leaves().size() == 1);
            BOOST_CHECK(p1.implementation_specific_parameters().empty());
            BOOST_CHECK(!p1.is_comparable());
            BOOST_CHECK(!p1.is_visitable());
            BOOST_CHECK(!p1.is_immutable());
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
            BOOST_CHECK(p.implementation_specific_parameters().empty());
            BOOST_CHECK(!p.is_comparable());
            BOOST_CHECK(!p.is_visitable());
            BOOST_CHECK(!p.is_immutable());
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

BOOST_AUTO_TEST_SUITE_END()
