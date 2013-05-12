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
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/dia_to_sml/types/transformer.hpp"
#include "dogen/dia_to_sml/types/profiler.hpp"
#include "dogen/dia_to_sml/types/transformation_error.hpp"
#include "dogen/dia_to_sml/io/context_io.hpp"
#include "dogen/dia_to_sml/test/mock_processed_object_factory.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;
using dogen::dia_to_sml::test::mock_processed_object_factory;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("transformer_spec");
const std::string model_name("test");
const std::string missing_name("Could not find name");
const std::string empty_name("Dia object name is empty");
const std::string missing_qname("Missing QName for dia object ID");
const std::string immutability_inheritance(
    "Immutability not supported with inheritance");

const std::string enumeration_stereotype("enumeration");
const std::string exception_stereotype("exception");
const std::string service_stereotype("service");
const std::string immutable_stereotype("immutable");

dogen::dia_to_sml::object_profile
profile(const dogen::dia_to_sml::processed_object& o) {
    profiler profiler;
    return profiler.profile(o);
}

bool is_type_one(const dogen::sml::qname& qn) {
    return mock_processed_object_factory::to_object_name(1) == qn.type_name();
}

bool is_type_two(const dogen::sml::qname& qn) {
    return mock_processed_object_factory::to_object_name(2) == qn.type_name();
}

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(transformer)

BOOST_AUTO_TEST_CASE(uml_class_with_no_stereotype_transforms_into_expected_pod) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_no_stereotype_transforms_into_expected_pod");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    const auto o(mock_processed_object_factory::build_class());
    dogen::dia_to_sml::transformer t(c);
    t.transform(o, profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_REQUIRE(c.model().pods().size() == 1);

    const auto p(c.model().pods().begin()->second);
    BOOST_CHECK(p.name().model_name() == model_name);
    BOOST_CHECK(!p.name().type_name().empty());
    BOOST_CHECK(p.properties().empty());
    BOOST_CHECK(p.pod_type() == dogen::sml::pod_types::value);
}

BOOST_AUTO_TEST_CASE(empty_named_uml_class_throws) {
    SETUP_TEST_LOG_SOURCE("empty_named_uml_class_throws");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_empty_named_class());
    contains_checker<transformation_error> cc(empty_name);
    BOOST_CHECK_EXCEPTION(t.transform(o, profile(o)), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto st(enumeration_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().pods().empty());
    BOOST_REQUIRE(c.model().enumerations().size() == 1);

    const auto e(c.model().enumerations().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().type_name().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_transforms_into_expected_exception) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_transforms_into_expected_exception");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto st(exception_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().pods().empty());
    BOOST_REQUIRE(c.model().exceptions().size() == 1);

    const auto e(c.model().exceptions().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().type_name().empty());
}

// BOOST_IGNORE_AUTO_TEST_CASE(uml_class_with_service_stereotype_transforms_into_expected_service) {
//     SETUP_TEST_LOG_SOURCE("uml_class_with_service_stereotype_transforms_into_expected_service");
//     dogen::dia_to_sml::context c;
//     c.model().name(model_name);

//     dogen::dia_to_sml::transformer t(c);
//     const auto st(service_stereotype);
//     const auto o(mock_processed_object_factory::build_class(0, st));
//     t.transform(o, profile(o));

//     BOOST_LOG_SEV(lg, debug) << "context: " << c;
//     BOOST_CHECK(c.model().pods().empty());
//     BOOST_REQUIRE(c.model().services().size() == 1);

//     const auto s(c.model().services().begin()->second);
//     BOOST_CHECK(s.name().model_name() == model_name);
//     BOOST_CHECK(!s.name().type_name().empty());
//     BOOST_CHECK(s.service_type() == dogen::sml::service_types::user_defined);
// }

BOOST_AUTO_TEST_CASE(uml_large_package_transforms_into_expected_package) {
    SETUP_TEST_LOG_SOURCE("uml_large_package_transforms_into_expected_package");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_large_package());
    t.transform(o, profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().pods().empty());

    BOOST_REQUIRE(c.model().packages().size() == 1);
    const auto p(c.model().packages().begin()->second);
    BOOST_CHECK(p.name().model_name() == model_name);
    BOOST_CHECK(!p.name().type_name().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_in_package_transforms_into_expected_pod) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_package_transforms_into_expected_pod");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package());
    t.transform(a[0], profile(a[0]));
    t.transform(a[1], profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().packages().size() == 1);
    const auto pkg(c.model().packages().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().type_name().empty());
    BOOST_CHECK(pkg.name().package_path().empty());

    BOOST_REQUIRE(c.model().pods().size() == 1);
    const auto p(c.model().pods().begin()->second);
    BOOST_CHECK(p.name().model_name() == model_name);
    BOOST_CHECK(!p.name().type_name().empty());
    BOOST_CHECK(p.properties().empty());
    BOOST_CHECK(p.pod_type() == dogen::sml::pod_types::value);
    BOOST_REQUIRE(p.name().package_path().size() == 1);
    BOOST_CHECK(p.name().package_path().front() == pkg.name().type_name());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_in_package_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_in_package_transforms_into_expected_enumeration");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto st(enumeration_stereotype);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0, st));
    t.transform(a[0], profile(a[0]));
    t.transform(a[1], profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().packages().size() == 1);
    const auto pkg(c.model().packages().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().type_name().empty());
    BOOST_CHECK(pkg.name().package_path().empty());

    BOOST_REQUIRE(c.model().enumerations().size() == 1);
    const auto e(c.model().enumerations().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().type_name().empty());
    BOOST_REQUIRE(e.name().package_path().size() == 1);
    BOOST_CHECK(e.name().package_path().front() == pkg.name().type_name());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_in_package_transforms_into_expected_exception) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_in_package_transforms_into_expected_exception");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto st(exception_stereotype);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0, st));
    t.transform(a[0], profile(a[0]));
    t.transform(a[1], profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().packages().size() == 1);
    const auto pkg(c.model().packages().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().type_name().empty());
    BOOST_CHECK(pkg.name().package_path().empty());

    BOOST_REQUIRE(c.model().exceptions().size() == 1);
    const auto e(c.model().exceptions().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().type_name().empty());
    BOOST_REQUIRE(e.name().package_path().size() == 1);
    BOOST_CHECK(e.name().package_path().front() == pkg.name().type_name());
}

// BOOST_IGNORE_AUTO_TEST_CASE(uml_class_with_service_stereotype_in_package_transforms_into_expected_service) {
//     SETUP_TEST_LOG_SOURCE("uml_class_with_service_stereotype_in_package_transforms_into_expected_service");
//     dogen::dia_to_sml::context c;
//     c.model().name(model_name);

//     dogen::dia_to_sml::transformer t(c);
//     const auto st(service_stereotype);
//     const auto a(
//         mock_processed_object_factory::build_class_inside_large_package(0, st));
//     t.transform(a[0], profile(a[0]));
//     t.transform(a[1], profile(a[1]));

//     BOOST_LOG_SEV(lg, debug) << "context: " << c;

//     BOOST_REQUIRE(c.model().packages().size() == 1);
//     const auto pkg(c.model().packages().begin()->second);
//     BOOST_CHECK(pkg.name().model_name() == model_name);
//     BOOST_CHECK(!pkg.name().type_name().empty());
//     BOOST_CHECK(pkg.name().package_path().empty());

//     BOOST_REQUIRE(c.model().services().size() == 1);
//     const auto e(c.model().services().begin()->second);
//     BOOST_CHECK(e.name().model_name() == model_name);
//     BOOST_CHECK(!e.name().type_name().empty());
//     BOOST_REQUIRE(e.name().package_path().size() == 1);
//     BOOST_CHECK(e.name().package_path().front() == pkg.name().type_name());
// }

BOOST_AUTO_TEST_CASE(uml_class_in_non_existing_package_throws) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_non_existing_package_throws");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    auto a(
        mock_processed_object_factory::build_class_inside_large_package());
    auto o(a[1]);
    auto op(profile(o));
    contains_checker<transformation_error> cc(missing_qname);
    BOOST_CHECK_EXCEPTION(t.transform(o, op), transformation_error, cc);

    auto st(enumeration_stereotype);
    a = mock_processed_object_factory::build_class_inside_large_package(0 , st);
    o = a[1];
    op = profile(o);
    BOOST_CHECK_EXCEPTION(t.transform(o, op), transformation_error, cc);

    st = exception_stereotype;
    a = mock_processed_object_factory::build_class_inside_large_package(0 , st);
    o = a[1];
    op = profile(o);
    BOOST_CHECK_EXCEPTION(t.transform(o, op), transformation_error, cc);

    st = service_stereotype;
    a = mock_processed_object_factory::build_class_inside_large_package(0 , st);
    o = a[1];
    op = profile(o);
    BOOST_CHECK_EXCEPTION(t.transform(o, op), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_in_two_packages_transforms_into_expected_pod) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_two_packages_transforms_into_expected_pod");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto a(
        mock_processed_object_factory::build_class_inside_two_large_packages());
    t.transform(a[0], profile(a[0]));
    t.transform(a[1], profile(a[1]));
    t.transform(a[2], profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().packages().size() == 2);
    auto i(c.model().packages().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().type_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().type_name().empty());

    BOOST_CHECK(
        pkg1.name().package_path().empty() ||
        pkg2.name().package_path().empty());

    BOOST_CHECK(
        !pkg1.name().package_path().empty() ||
        !pkg2.name().package_path().empty());

    std::string first, second;
    if (pkg1.name().package_path().empty()) {
        first = pkg1.name().type_name();
        second = pkg2.name().type_name();
        BOOST_CHECK(pkg2.name().package_path().front() == first);
    } else {
        first = pkg2.name().type_name();
        second = pkg1.name().type_name();
        BOOST_CHECK(pkg1.name().package_path().front() == first);
    }

    BOOST_REQUIRE(c.model().pods().size() == 1);
    const auto p(c.model().pods().begin()->second);
    BOOST_CHECK(p.name().model_name() == model_name);
    BOOST_CHECK(!p.name().type_name().empty());
    BOOST_CHECK(p.properties().empty());
    BOOST_CHECK(p.pod_type() == dogen::sml::pod_types::value);
    BOOST_REQUIRE(p.name().package_path().size() == 2);
    BOOST_CHECK(p.name().package_path().front() == first);
    BOOST_CHECK(p.name().package_path().back() == second);
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_in_two_packages_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_in_two_packages_transforms_into_expected_enumeration");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto st(enumeration_stereotype);
    const auto a(mock_processed_object_factory::
        build_class_inside_two_large_packages(0, st));
    t.transform(a[0], profile(a[0]));
    t.transform(a[1], profile(a[1]));
    t.transform(a[2], profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().packages().size() == 2);
    auto i(c.model().packages().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().type_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().type_name().empty());

    BOOST_CHECK(
        pkg1.name().package_path().empty() ||
        pkg2.name().package_path().empty());

    BOOST_CHECK(
        !pkg1.name().package_path().empty() ||
        !pkg2.name().package_path().empty());

    std::string first, second;
    if (pkg1.name().package_path().empty()) {
        first = pkg1.name().type_name();
        second = pkg2.name().type_name();
        BOOST_CHECK(pkg2.name().package_path().front() == first);
    } else {
        first = pkg2.name().type_name();
        second = pkg1.name().type_name();
        BOOST_CHECK(pkg1.name().package_path().front() == first);
    }

    BOOST_REQUIRE(c.model().enumerations().size() == 1);
    const auto e(c.model().enumerations().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().type_name().empty());
    BOOST_REQUIRE(e.name().package_path().size() == 2);
    BOOST_CHECK(e.name().package_path().front() == first);
    BOOST_CHECK(e.name().package_path().back() == second);
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_in_two_packages_transforms_into_expected_exception) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_in_two_packages_transforms_into_expected_exception");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto st(exception_stereotype);
    const auto a(mock_processed_object_factory::
        build_class_inside_two_large_packages(0, st));
    t.transform(a[0], profile(a[0]));
    t.transform(a[1], profile(a[1]));
    t.transform(a[2], profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().packages().size() == 2);
    auto i(c.model().packages().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().type_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().type_name().empty());

    BOOST_CHECK(
        pkg1.name().package_path().empty() ||
        pkg2.name().package_path().empty());

    BOOST_CHECK(
        !pkg1.name().package_path().empty() ||
        !pkg2.name().package_path().empty());

    std::string first, second;
    if (pkg1.name().package_path().empty()) {
        first = pkg1.name().type_name();
        second = pkg2.name().type_name();
        BOOST_CHECK(pkg2.name().package_path().front() == first);
    } else {
        first = pkg2.name().type_name();
        second = pkg1.name().type_name();
        BOOST_CHECK(pkg1.name().package_path().front() == first);
    }

    BOOST_REQUIRE(c.model().exceptions().size() == 1);
    const auto e(c.model().exceptions().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().type_name().empty());
    BOOST_REQUIRE(e.name().package_path().size() == 2);
    BOOST_CHECK(e.name().package_path().front() == first);
    BOOST_CHECK(e.name().package_path().back() == second);
}

// BOOST_IGNORE_AUTO_TEST_CASE(uml_class_with_service_stereotype_in_two_packages_transforms_into_expected_service) {
//     SETUP_TEST_LOG_SOURCE("uml_class_with_service_stereotype_in_two_packages_transforms_into_expected_service");
//     dogen::dia_to_sml::context c;
//     c.model().name(model_name);

//     dogen::dia_to_sml::transformer t(c);
//     const auto st(service_stereotype);
//     const auto a(mock_processed_object_factory::
//         build_class_inside_two_large_packages(0, st));
//     t.transform(a[0], profile(a[0]));
//     t.transform(a[1], profile(a[1]));
//     t.transform(a[2], profile(a[2]));

//     BOOST_LOG_SEV(lg, debug) << "context: " << c;

//     BOOST_REQUIRE(c.model().packages().size() == 2);
//     auto i(c.model().packages().begin());

//     const auto pkg1(i->second);
//     BOOST_CHECK(pkg1.name().model_name() == model_name);
//     BOOST_CHECK(!pkg1.name().type_name().empty());

//     const auto pkg2((++i)->second);
//     BOOST_CHECK(pkg2.name().model_name() == model_name);
//     BOOST_CHECK(!pkg2.name().type_name().empty());

//     BOOST_CHECK(
//         pkg1.name().package_path().empty() ||
//         pkg2.name().package_path().empty());

//     BOOST_CHECK(
//         !pkg1.name().package_path().empty() ||
//         !pkg2.name().package_path().empty());

//     std::string first, second;
//     if (pkg1.name().package_path().empty()) {
//         first = pkg1.name().type_name();
//         second = pkg2.name().type_name();
//         BOOST_CHECK(pkg2.name().package_path().front() == first);
//     } else {
//         first = pkg2.name().type_name();
//         second = pkg1.name().type_name();
//         BOOST_CHECK(pkg1.name().package_path().front() == first);
//     }

//     BOOST_REQUIRE(c.model().services().size() == 1);
//     const auto e(c.model().services().begin()->second);
//     BOOST_CHECK(e.name().model_name() == model_name);
//     BOOST_CHECK(!e.name().type_name().empty());
//     BOOST_REQUIRE(e.name().package_path().size() == 2);
//     BOOST_CHECK(e.name().package_path().front() == first);
//     BOOST_CHECK(e.name().package_path().back() == second);
// }

BOOST_AUTO_TEST_CASE(uml_note_with_marker_transforms_into_model_comments) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_two_packages_transforms_into_expected_pod");

    dogen::dia_to_sml::context c;
    c.model().name(model_name);
    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_uml_note_with_marker());
    t.transform(o, profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(!c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().size() == 1);
}

BOOST_AUTO_TEST_CASE(uml_note_with_text_but_no_marker_does_nothing) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_text_but_no_marker_does_nothing");

    dogen::dia_to_sml::context c;
    c.model().name(model_name);
    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_uml_note());
    t.transform(o, profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(empty_uml_note_does_nothing) {
    SETUP_TEST_LOG_SOURCE("empty_uml_note_does_nothing");

    dogen::dia_to_sml::context c;
    c.model().name(model_name);
    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_empty_uml_note());
    t.transform(o, profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(uml_note_with_marker_inside_package_transforms_into_package_comments) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_marker_inside_package_transforms_into_package_comments");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);
    dogen::dia_to_sml::transformer t(c);
    const auto a(mock_processed_object_factory::
        build_uml_note_with_marker_inside_large_package());
    t.transform(a[0], profile(a[0]));
    t.transform(a[1], profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
    BOOST_REQUIRE(c.model().packages().size() == 1);

    const auto p(c.model().packages().begin()->second);
    BOOST_CHECK(!p.documentation().empty());
    BOOST_CHECK(!p.implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(uml_note_with_text_but_no_marker_inside_package_does_nothing) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_text_but_no_marker_inside_package_does_nothing");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);
    dogen::dia_to_sml::transformer t(c);
    const auto a(mock_processed_object_factory::
        build_uml_note_inside_large_package());
    t.transform(a[0], profile(a[0]));
    t.transform(a[1], profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
    BOOST_REQUIRE(c.model().packages().size() == 1);

    const auto p(c.model().packages().begin()->second);
    BOOST_CHECK(p.documentation().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(empty_uml_note_inside_package_does_nothing) {
    SETUP_TEST_LOG_SOURCE("empty_uml_note_inside_package_does_nothing");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);
    dogen::dia_to_sml::transformer t(c);
    const auto a(mock_processed_object_factory::
        build_empty_uml_note_inside_large_package());
    t.transform(a[0], profile(a[0]));
    t.transform(a[1], profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
    BOOST_REQUIRE(c.model().packages().size() == 1);

    const auto p(c.model().packages().begin()->second);
    BOOST_CHECK(p.documentation().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(inheritance_with_immutability_throws) {
    SETUP_TEST_LOG_SOURCE("inheritance_with_immutability_throws");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    const auto a(mock_processed_object_factory::build_generalization());
    const auto con(a[0].connection());
    BOOST_REQUIRE(con);
    c.child_to_parent().insert(std::make_pair(con->second, con->first));

    dogen::dia_to_sml::transformer t1(c);
    t1.transform(a[1], profile(a[1]));
    auto po1(a[2]);
    po1.stereotype(immutable_stereotype);
    const auto op1(profile(po1));
    contains_checker<transformation_error> cc(immutability_inheritance);
    BOOST_CHECK_EXCEPTION(t1.transform(po1, op1), transformation_error, cc);

    c.child_to_parent().clear();
    c.parent_ids().insert(con->first);
    dogen::dia_to_sml::transformer t2(c);
    auto po2(a[1]);
    po2.stereotype(immutable_stereotype);
    const auto op2(profile(po2));
    BOOST_CHECK_EXCEPTION(t1.transform(po2, op2), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_with_inheritance_results_in_expected_pod) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_inheritance_results_in_expected_pod");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    const auto a(mock_processed_object_factory::build_generalization());
    const auto con(a[0].connection());
    BOOST_REQUIRE(con);
    c.child_to_parent().insert(std::make_pair(con->second, con->first));
    c.parent_ids().insert(con->first);

    dogen::dia_to_sml::transformer t1(c);
    t1.transform(a[1], profile(a[1]));
    t1.transform(a[2], profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_CHECK(c.model().packages().empty());
    BOOST_REQUIRE(c.model().pods().size() == 2);
    for (const auto& p : c.model().pods()) {
        if (is_type_one(p.first)) {
            BOOST_CHECK(!p.second.parent_name());
            BOOST_CHECK(!p.second.original_parent_name());
        } else if (is_type_two(p.first)) {
            BOOST_REQUIRE(p.second.parent_name());
            BOOST_REQUIRE(is_type_one(*p.second.parent_name()));
        } else {
            BOOST_LOG_SEV(lg, error) << "Unexpected type name: " << p.first;
            BOOST_FAIL("Unexpected type name");
        }
    }
}

// BOOST_IGNORE_AUTO_TEST_CASE(uml_class_with_servivce_stereotype_and_inheritance_results_in_expected_service) {
//     SETUP_TEST_LOG_SOURCE("uml_class_with_servivce_stereotype_and_inheritance_results_in_expected_service");
//     dogen::dia_to_sml::context c;
//     c.model().name(model_name);

//     const auto st(service_stereotype);
//     const auto a(mock_processed_object_factory::build_generalization(0, st));
//     const auto con(a[0].connection());
//     BOOST_REQUIRE(con);
//     c.child_to_parent().insert(std::make_pair(con->second, con->first));
//     c.parent_ids().insert(con->first);

//     dogen::dia_to_sml::transformer t1(c);
//     t1.transform(a[1], profile(a[1]));
//     t1.transform(a[2], profile(a[2]));

//     BOOST_LOG_SEV(lg, debug) << "context: " << c;

//     BOOST_CHECK(c.model().packages().empty());
//     BOOST_REQUIRE(c.model().services().size() == 2);
//     for (const auto& p : c.model().services()) {
//         if (is_type_one(p.first)) {
//             BOOST_CHECK(!p.second.parent_name());
//             BOOST_CHECK(!p.second.original_parent_name());
//         } else if (is_type_two(p.first)) {
//             BOOST_REQUIRE(p.second.parent_name());
//             BOOST_REQUIRE(is_type_one(*p.second.parent_name()));
//         } else {
//             BOOST_LOG_SEV(lg, error) << "Unexpected type name: " << p.first;
//             BOOST_FAIL("Unexpected type name");
//         }
//     }
// }

BOOST_AUTO_TEST_SUITE_END()
