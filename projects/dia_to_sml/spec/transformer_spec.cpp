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
#include "dogen/dia_to_sml/types/transformer.hpp"
#include "dogen/dia_to_sml/types/transformation_error.hpp"
#include "dogen/dia_to_sml/io/context_io.hpp"
#include "dogen/dia_to_sml/test/mock_processed_object_factory.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("transformer_spec");
const std::string model_name("test");
const std::string missing_name("Could not find name");
const std::string empty_name("Dia object name is empty");
const std::string missing_qname("Missing QName for dia object ID");

const std::string enumeration_stereotype("enumeration");
const std::string exception_stereotype("exception");

}

using dogen::utility::test::contains_checker;
using dogen::dia_to_sml::test::mock_processed_object_factory;

BOOST_AUTO_TEST_SUITE(transformer)

BOOST_AUTO_TEST_CASE(uml_class_with_no_stereotype_transforms_into_expected_pod) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_no_stereotype_transforms_into_expected_pod");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    t.transform(mock_processed_object_factory::build_class(0));

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
    const auto o(mock_processed_object_factory::build_empty_named_class(0));
    contains_checker<transformation_error> cc(empty_name);
    BOOST_CHECK_EXCEPTION(t.transform(o), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto st(enumeration_stereotype);
    t.transform(mock_processed_object_factory::build_stereotyped_class(st, 0));

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
    t.transform(mock_processed_object_factory::build_stereotyped_class(st, 0));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().pods().empty());
    BOOST_REQUIRE(c.model().exceptions().size() == 1);

    const auto e(c.model().exceptions().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().type_name().empty());
}

BOOST_AUTO_TEST_CASE(uml_large_package_transforms_into_expected_package) {
    SETUP_TEST_LOG_SOURCE("uml_large_package_transforms_into_expected_package");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    t.transform(mock_processed_object_factory::build_large_package(0));

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
        mock_processed_object_factory::build_class_inside_large_package(0));
    t.transform(a[0]);
    t.transform(a[1]);

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

BOOST_AUTO_TEST_CASE(uml_class_in_non_existing_package_throws) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_non_existing_package_throws");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0));
    contains_checker<transformation_error> cc(missing_qname);
    BOOST_CHECK_EXCEPTION(t.transform(a[1]), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_in_two_packages_transforms_into_expected_pod) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_two_packages_transforms_into_expected_pod");
    dogen::dia_to_sml::context c;
    c.model().name(model_name);

    dogen::dia_to_sml::transformer t(c);
    const auto a(
        mock_processed_object_factory::build_class_inside_two_large_packages(0));
    t.transform(a[0]);
    t.transform(a[1]);
    t.transform(a[2]);

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

BOOST_AUTO_TEST_CASE(uml_note_with_marker_transforms_into_model_comments) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_two_packages_transforms_into_expected_pod");

    dogen::dia_to_sml::context c;
    c.model().name(model_name);
    dogen::dia_to_sml::transformer t(c);
    t.transform(mock_processed_object_factory::build_uml_note_with_marker(0));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(!c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().size() == 1);
}

BOOST_AUTO_TEST_CASE(uml_note_with_text_but_no_marker_does_nothing) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_text_but_no_marker_does_nothing");

    dogen::dia_to_sml::context c;
    c.model().name(model_name);
    dogen::dia_to_sml::transformer t(c);
    t.transform(mock_processed_object_factory::build_uml_note(0));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(empty_uml_note_does_nothing) {
    SETUP_TEST_LOG_SOURCE("empty_uml_note_does_nothing");

    dogen::dia_to_sml::context c;
    c.model().name(model_name);
    dogen::dia_to_sml::transformer t(c);
    t.transform(mock_processed_object_factory::build_empty_uml_note(0));

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
        build_uml_note_with_marker_inside_large_package(0));
    t.transform(a[0]);
    t.transform(a[1]);

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
        build_uml_note_inside_large_package(0));
    t.transform(a[0]);
    t.transform(a[1]);

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
        build_empty_uml_note_inside_large_package(0));
    t.transform(a[0]);
    t.transform(a[1]);

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
    BOOST_REQUIRE(c.model().packages().size() == 1);

    const auto p(c.model().packages().begin()->second);
    BOOST_CHECK(p.documentation().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_SUITE_END()
