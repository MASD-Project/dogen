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

/*
#include <sstream>
#include <initializer_list>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/annotations/test/mock_workflow_factory.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"
#include "dogen/yarn.dia/types/profiler.hpp"
#include "dogen/yarn.dia/types/transformation_error.hpp"
#include "dogen/yarn.dia/io/repository_io.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/test/mock_processed_object_factory.hpp"
#include "dogen/annotations/test/mock_repository_factory.hpp"
#include "dogen/annotations/test/mock_workflow_factory.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::yarn::dia;
using dogen::utility::test::asserter;
using dogen::yarn::dia::test::mock_processed_object_factory;

namespace  {

const std::string test_module("yarn.dia");
const std::string test_suite("transformer_tests");

const std::string empty;
const std::string model_name("test");
const std::string empty_name("Dia object name is empty");
const std::string missing_name("Missing name for dia object ID");
const std::string immutability_inheritance(
    "Immutability not supported with inheritance");

const std::string enumeration_stereotype("enumeration");
const std::string value_object_stereotype("value object");
const std::string exception_stereotype("exception");
const std::string entity_stereotype("entity");
const std::string keyed_entity_stereotype("keyed entity");
const std::string service_stereotype("service");
const std::string factory_stereotype("factory");
const std::string repository_stereotype("repository");

const std::string immutable_stereotype("immutable");

dogen::yarn::dia::profile
mock_profile(const dogen::yarn::dia::processed_object& o) {
    // FIXME: we should really be mocking the profile
    profiler profiler;
    return profiler.generate(o);
}

bool is_type_zero(const std::string& s) {
    return mock_processed_object_factory::to_object_name(0) == s;
}

bool is_type_zero(const dogen::yarn::name& n) {
    return is_type_zero(n.simple());
}

bool is_type_one(const dogen::yarn::name& n) {
    return mock_processed_object_factory::to_object_name(1) == n.simple();
}

bool is_type_two(const dogen::yarn::name& n) {
    return mock_processed_object_factory::to_object_name(2) == n.simple();
}

dogen::yarn::name mock_model_name(const std::string& mn) {
    dogen::yarn::name_factory nf;
    return nf.build_model_name(mn);;
}

dogen::yarn::dia::repository mock_repository(const std::string& model_name) {
    dogen::yarn::dia::repository r;
    r.model().name(mock_model_name(model_name));

    dogen::yarn::module m;
    m.name(r.model().name());
    r.model().modules().insert(std::make_pair(m.name().id(), m));
    return r;
}

dogen::yarn::dia::repository mock_repository() {
    return mock_repository(model_name);
}

dogen::annotations::repository empty_repository;

void transform(dogen::yarn::dia::repository& c,
    std::initializer_list<dogen::yarn::dia::processed_object> lpo) {

    using namespace dogen::annotations::test;
    mock_repository_factory rf;
    const auto rp(rf.make());
    const auto w(mock_workflow_factory::non_validating_workflow(rp));
    dogen::yarn::dia::transformer t(w, c);

    for (const auto& po : lpo)
        t.transform(po, mock_profile(po));
}

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(transformer_tests)

BOOST_AUTO_TEST_CASE(empty_named_uml_class_throws) {
    SETUP_TEST_LOG_SOURCE("empty_named_uml_class_throws");

    auto c(mock_repository());
    contains_checker<transformation_error> cc(empty_name);
    const auto po(mock_processed_object_factory::make_empty_named_class());
    BOOST_CHECK_EXCEPTION(transform(c, {po}), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_with_no_stereotype_transforms_into_expected_value_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_no_stereotype_transforms_into_expected_value_object");
    const auto po(mock_processed_object_factory::make_class());
    auto c(mock_repository(model_name));
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& o(c.model().objects().begin()->second);
    BOOST_CHECK(o.object_type() ==
        dogen::yarn::object_types::user_defined_value_object);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!o.name().simple().empty());
    BOOST_CHECK(o.local_attributes().empty());
    BOOST_CHECK(!o.documentation().empty());

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto& m(c.model().modules().begin()->second);
    BOOST_CHECK(m.name().simple() == model_name);
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(m.name().location().internal_modules().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_value_object_stereotype_transforms_into_expected_value_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_value_object_stereotype_transforms_into_expected_value_object");

    auto c(mock_repository());
    const auto st(value_object_stereotype);
    const auto po(mock_processed_object_factory::make_class(0, st));
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& o(c.model().objects().begin()->second);
    BOOST_CHECK(o.object_type() ==
        dogen::yarn::object_types::user_defined_value_object);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(is_type_zero(o.name()));
    BOOST_CHECK(!o.documentation().empty());

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto& m(c.model().modules().begin()->second);
    BOOST_CHECK(m.name().simple() == model_name);
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(m.name().location().internal_modules().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration");

    auto c(mock_repository());
    const auto st(enumeration_stereotype);
    const auto po(mock_processed_object_factory::make_class(0, st));
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_CHECK(c.model().objects().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().enumerations().size() == 1);

    const auto e(c.model().enumerations().begin()->second);
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto& m(c.model().modules().begin()->second);
    BOOST_CHECK(m.name().simple() == model_name);
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(m.name().location().internal_modules().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_transforms_into_expected_value_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_transforms_into_expected_value_object");

    auto c(mock_repository());
    const auto st(exception_stereotype);
    const auto po(mock_processed_object_factory::make_class(0, st));
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_CHECK(c.model().objects().empty());
    BOOST_REQUIRE(c.model().exceptions().size() == 1);

    const auto& e(c.model().exceptions().begin()->second);
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto& m(c.model().modules().begin()->second);
    BOOST_CHECK(m.name().simple() == model_name);
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(m.name().location().internal_modules().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_service_stereotype_transforms_into_expected_service) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_service_stereotype_transforms_into_expected_service");

    auto c(mock_repository());
    const auto st(service_stereotype);
    const auto po(mock_processed_object_factory::make_class(0, st));
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& o(c.model().objects().begin()->second);
    BOOST_CHECK(o.object_type() ==
        dogen::yarn::object_types::user_defined_service);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(is_type_zero(o.name()));
    BOOST_CHECK(!o.documentation().empty());

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto& m(c.model().modules().begin()->second);
    BOOST_CHECK(m.name().simple() == model_name);
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(m.name().location().internal_modules().empty());
}

BOOST_AUTO_TEST_CASE(uml_large_package_transforms_into_expected_module) {
    SETUP_TEST_LOG_SOURCE("uml_large_package_transforms_into_expected_module");

    auto c(mock_repository(model_name));
    const auto po(mock_processed_object_factory::make_large_package());
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_CHECK(c.model().objects().empty());
    BOOST_REQUIRE(c.model().modules().size() == 2);

    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
        BOOST_CHECK(m.name().location().model_modules().front() ==
            model_name);
        BOOST_CHECK(m.name().location().internal_modules().empty());

        if (m.name().simple() != model_name) {
            BOOST_CHECK(!m.name().simple().empty());
            BOOST_CHECK(m.documentation().empty());
        }
    }
}

BOOST_AUTO_TEST_CASE(uml_class_in_package_transforms_into_expected_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_package_transforms_into_expected_object");

    auto c(mock_repository(model_name));
    const auto po(
        mock_processed_object_factory::make_class_inside_large_package());
    transform(c, {po[0], po[1]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    std::string module_name;
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
        BOOST_CHECK(m.name().location().model_modules().front() ==
            model_name);
        BOOST_CHECK(m.name().location().internal_modules().empty());

        if (m.name().simple() != model_name) {
            BOOST_CHECK(!m.name().simple().empty());
            BOOST_CHECK(m.documentation().empty());
            module_name = m.name().simple();
        }
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& o(c.model().objects().begin()->second);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
            model_name);
    BOOST_CHECK(!o.name().simple().empty());

    BOOST_CHECK(o.local_attributes().empty());

    BOOST_CHECK(o.object_type() ==
        dogen::yarn::object_types::user_defined_value_object);
    BOOST_REQUIRE(o.name().location().internal_modules().size() == 1);
    BOOST_CHECK(o.name().location().internal_modules().front() ==
        module_name);
    BOOST_CHECK(!o.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_in_package_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_in_package_transforms_into_expected_enumeration");

    auto c(mock_repository(model_name));
    const auto st(enumeration_stereotype);
    const auto po(
        mock_processed_object_factory::make_class_inside_large_package(0, st));
    transform(c, {po[0], po[1]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    std::string module_name;
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
        BOOST_CHECK(m.name().location().model_modules().front() ==
            model_name);
        BOOST_CHECK(m.name().location().internal_modules().empty());

        if (m.name().simple() != model_name) {
            BOOST_CHECK(!m.name().simple().empty());
            BOOST_CHECK(m.documentation().empty());
            module_name = m.name().simple();
        }
    }

    BOOST_REQUIRE(c.model().enumerations().size() == 1);
    const auto e(c.model().enumerations().begin()->second);
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() ==
        model_name);
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() ==
            model_name);

    BOOST_CHECK(!e.name().simple().empty());
    BOOST_REQUIRE(e.name().location().internal_modules().size() == 1);
    BOOST_CHECK(e.name().location().internal_modules().front() ==
        module_name);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_in_package_transforms_into_expected_exception) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_in_package_transforms_into_expected_exception");

    auto c(mock_repository(model_name));
    const auto st(exception_stereotype);
    const auto po(
        mock_processed_object_factory::make_class_inside_large_package(0, st));
    transform(c, {po[0], po[1]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    std::string module_name;
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
        BOOST_CHECK(m.name().location().model_modules().front() ==
            model_name);
        BOOST_CHECK(m.name().location().internal_modules().empty());

        if (m.name().simple() != model_name) {
            BOOST_CHECK(!m.name().simple().empty());
            BOOST_CHECK(m.documentation().empty());
            module_name = m.name().simple();
        }
    }

    BOOST_REQUIRE(c.model().exceptions().size() == 1);
    const auto& o(c.model().exceptions().begin()->second);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!o.name().simple().empty());
    BOOST_REQUIRE(o.name().location().internal_modules().size() == 1);
    BOOST_CHECK(o.name().location().internal_modules().front() ==
        module_name);
    BOOST_CHECK(!o.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_service_stereotype_in_package_transforms_into_expected_service) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_service_stereotype_in_package_transforms_into_expected_service");

    auto c(mock_repository(model_name));
    const auto st(service_stereotype);
    const auto po(
        mock_processed_object_factory::make_class_inside_large_package(0, st));
    transform(c, {po[0], po[1]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    std::string module_name;
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
        BOOST_CHECK(m.name().location().model_modules().front() ==
            model_name);
        BOOST_CHECK(m.name().location().internal_modules().empty());

        if (m.name().simple() != model_name) {
            BOOST_CHECK(!m.name().simple().empty());
            BOOST_CHECK(m.documentation().empty());
            module_name = m.name().simple();
        }
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& o(c.model().objects().begin()->second);
    BOOST_CHECK(o.object_type() ==
        dogen::yarn::object_types::user_defined_service);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!o.name().simple().empty());
    BOOST_REQUIRE(o.name().location().internal_modules().size() == 1);
    BOOST_CHECK(o.name().location().internal_modules().front() ==
        module_name);
    BOOST_CHECK(!o.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_in_non_existing_package_throws) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_non_existing_package_throws");
    auto c(mock_repository(model_name));
    auto po(mock_processed_object_factory::make_class_inside_large_package());
    contains_checker<transformation_error> cc(missing_name);
    BOOST_CHECK_EXCEPTION(transform(c, {po[1]}), transformation_error, cc);

    auto st(enumeration_stereotype);
    po = mock_processed_object_factory::make_class_inside_large_package(0 , st);
    BOOST_CHECK_EXCEPTION(transform(c, {po[1]}), transformation_error, cc);

    st = exception_stereotype;
    po = mock_processed_object_factory::make_class_inside_large_package(0 , st);
    BOOST_CHECK_EXCEPTION(transform(c, {po[1]}), transformation_error, cc);

    st = service_stereotype;
    po = mock_processed_object_factory::make_class_inside_large_package(0 , st);
    BOOST_CHECK_EXCEPTION(transform(c, {po[1]}), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_in_two_packages_transforms_into_expected_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_two_packages_transforms_into_expected_object");

    auto c(mock_repository(model_name));
    const auto po(
        mock_processed_object_factory::make_class_inside_two_large_packages());
    transform(c, {po[0], po[1], po[2]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 3);
    std::list<dogen::yarn::module> module_list;
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        if (m.name().simple() != model_name)
            module_list.push_back(m);
    }
    BOOST_REQUIRE(module_list.size() == 2);

    const auto m1(module_list.front());
    BOOST_REQUIRE(m1.name().location().model_modules().size() == 1);
    BOOST_CHECK(m1.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!m1.name().simple().empty());

    const auto m2(module_list.back());
    BOOST_REQUIRE(m2.name().location().model_modules().size() == 1);
    BOOST_CHECK(m2.name().location().model_modules().front() ==
        model_name);

    BOOST_CHECK(!m2.name().simple().empty());

    BOOST_CHECK(
        m1.name().location().internal_modules().empty() ||
        m2.name().location().internal_modules().empty());

    BOOST_CHECK(
        !m1.name().location().internal_modules().empty() ||
        !m2.name().location().internal_modules().empty());

    std::string first, second;
    if (m1.name().location().internal_modules().empty()) {
        first = m1.name().simple();
        second = m2.name().simple();
        BOOST_CHECK(m2.name().location().internal_modules().front() ==
            first);
    } else {
        first = m2.name().simple();
        second = m1.name().simple();
        BOOST_CHECK(m1.name().location().internal_modules().front() == first);
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& o(c.model().objects().begin()->second);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!o.name().simple().empty());
    BOOST_CHECK(o.local_attributes().empty());
    BOOST_CHECK(o.object_type() ==
        dogen::yarn::object_types::user_defined_value_object);
    BOOST_REQUIRE(o.name().location().internal_modules().size() == 2);
    BOOST_CHECK(o.name().location().internal_modules().front() == first);
    BOOST_CHECK(o.name().location().internal_modules().back() == second);
    BOOST_CHECK(!o.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_in_two_packages_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_in_two_packages_transforms_into_expected_enumeration");

    auto c(mock_repository(model_name));
    const auto st(enumeration_stereotype);
    const auto po(mock_processed_object_factory::
        make_class_inside_two_large_packages(0, st));
    transform(c, {po[0], po[1], po[2]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 3);
    std::list<dogen::yarn::module> module_list;
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        if (m.name().simple() != model_name)
            module_list.push_back(m);
    }
    BOOST_REQUIRE(module_list.size() == 2);

    const auto m1(module_list.front());
    BOOST_REQUIRE(m1.name().location().model_modules().size() == 1);
    BOOST_CHECK(m1.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!m1.name().simple().empty());

    const auto m2(module_list.back());
    BOOST_REQUIRE(m2.name().location().model_modules().size() == 1);
    BOOST_CHECK(m2.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!m2.name().simple().empty());

    BOOST_CHECK(
        m1.name().location().internal_modules().empty() ||
        m2.name().location().internal_modules().empty());

    BOOST_CHECK(
        !m1.name().location().internal_modules().empty() ||
        !m2.name().location().internal_modules().empty());

    std::string first, second;
    if (m1.name().location().internal_modules().empty()) {
        first = m1.name().simple();
        second = m2.name().simple();
        BOOST_CHECK(m2.name().location().internal_modules().front() ==
            first);
    } else {
        first = m2.name().simple();
        second = m1.name().simple();
        BOOST_CHECK(m1.name().location().internal_modules().front() ==
            first);
    }

    BOOST_REQUIRE(c.model().enumerations().size() == 1);
    const auto e(c.model().enumerations().begin()->second);
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!e.name().simple().empty());
    BOOST_REQUIRE(e.name().location().internal_modules().size() == 2);
    BOOST_CHECK(e.name().location().internal_modules().front() == first);
    BOOST_CHECK(e.name().location().internal_modules().back() == second);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_in_two_packages_transforms_into_expected_exception) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_in_two_packages_transforms_into_expected_exception");

    auto c(mock_repository(model_name));
    const auto st(exception_stereotype);
    const auto po(mock_processed_object_factory::
        make_class_inside_two_large_packages(0, st));
    transform(c, {po[0], po[1], po[2]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 3);
    std::list<dogen::yarn::module> module_list;
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        if (m.name().simple() != model_name)
            module_list.push_back(m);
    }
    BOOST_REQUIRE(module_list.size() == 2);

    const auto m1(module_list.front());
    BOOST_REQUIRE(m1.name().location().model_modules().size() == 1);
    BOOST_CHECK(m1.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!m1.name().simple().empty());

    const auto m2(module_list.back());
    BOOST_REQUIRE(m2.name().location().model_modules().size() == 1);
    BOOST_CHECK(m2.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!m2.name().simple().empty());

    BOOST_CHECK(
        m1.name().location().internal_modules().empty() ||
        m2.name().location().internal_modules().empty());

    BOOST_CHECK(
        !m1.name().location().internal_modules().empty() ||
        !m2.name().location().internal_modules().empty());

    std::string first, second;
    if (m1.name().location().internal_modules().empty()) {
        first = m1.name().simple();
        second = m2.name().simple();
        BOOST_CHECK(m2.name().location().internal_modules().front() == first);
    } else {
        first = m2.name().simple();
        second = m1.name().simple();
        BOOST_CHECK(m1.name().location().internal_modules().front()
            == first);
    }

    BOOST_REQUIRE(c.model().exceptions().size() == 1);
    const auto& o(c.model().exceptions().begin()->second);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!o.name().simple().empty());
    BOOST_REQUIRE(o.name().location().internal_modules().size() == 2);
    BOOST_CHECK(o.name().location().internal_modules().front() == first);
    BOOST_CHECK(o.name().location().internal_modules().back() == second);
    BOOST_CHECK(!o.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_service_stereotype_in_two_packages_transforms_into_expected_service) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_service_stereotype_in_two_packages_transforms_into_expected_service");

    auto c(mock_repository(model_name));
    const auto st(service_stereotype);
    const auto po(mock_processed_object_factory::
        make_class_inside_two_large_packages(0, st));
    transform(c, {po[0], po[1], po[2]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 3);
    std::list<dogen::yarn::module> module_list;
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        if (m.name().simple() != model_name)
            module_list.push_back(m);
    }
    BOOST_REQUIRE(module_list.size() == 2);

    const auto m1(module_list.front());
    BOOST_REQUIRE(m1.name().location().model_modules().size() == 1);
    BOOST_CHECK(m1.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!m1.name().simple().empty());

    const auto m2(module_list.back());
    BOOST_REQUIRE(m2.name().location().model_modules().size() == 1);
    BOOST_CHECK(m2.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!m2.name().simple().empty());

    BOOST_CHECK(
        m1.name().location().internal_modules().empty() ||
        m2.name().location().internal_modules().empty());

    BOOST_CHECK(
        !m1.name().location().internal_modules().empty() ||
        !m2.name().location().internal_modules().empty());

    std::string first, second;
    if (m1.name().location().internal_modules().empty()) {
        first = m1.name().simple();
        second = m2.name().simple();
        BOOST_CHECK(m2.name().location().internal_modules().front() ==
            first);
    } else {
        first = m2.name().simple();
        second = m1.name().simple();
        BOOST_CHECK(m1.name().location().internal_modules().front() ==
            first);
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& o(c.model().objects().begin()->second);
    BOOST_CHECK(o.object_type() ==
        dogen::yarn::object_types::user_defined_service);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(!o.name().simple().empty());
    BOOST_REQUIRE(o.name().location().internal_modules().size() == 2);
    BOOST_CHECK(o.name().location().internal_modules().front() == first);
    BOOST_CHECK(o.name().location().internal_modules().back() == second);
    BOOST_CHECK(!o.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_note_with_marker_transforms_into_model_comments) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_marker_transforms_into_model_comments");

    auto c(mock_repository(model_name));
    const auto po(mock_processed_object_factory::make_uml_note_with_marker());
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto m(c.model().modules().begin()->second);
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(m.name().simple() == model_name);
    BOOST_CHECK(!m.documentation().empty());
    BOOST_CHECK(m.annotations().fields().size() == 1);
}

BOOST_AUTO_TEST_CASE(uml_note_with_text_but_no_marker_does_nothing) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_text_but_no_marker_does_nothing");

    auto c(mock_repository(model_name));
    const auto po(mock_processed_object_factory::make_uml_note());
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto m(c.model().modules().begin()->second);
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(m.name().simple() == model_name);
    BOOST_CHECK(m.documentation().empty());
    BOOST_CHECK(m.annotations().fields().empty());
}

BOOST_AUTO_TEST_CASE(empty_uml_note_does_nothing) {
    SETUP_TEST_LOG_SOURCE("empty_uml_note_does_nothing");

    auto c(mock_repository(model_name));
    const auto po(mock_processed_object_factory::make_empty_uml_note());
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    const auto m(c.model().modules().begin()->second);
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(m.name().simple() == model_name);
    BOOST_CHECK(m.documentation().empty());
    BOOST_CHECK(m.annotations().fields().empty());
}

BOOST_AUTO_TEST_CASE(uml_note_with_marker_inside_package_transforms_into_package_comments) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_marker_inside_package_transforms_into_package_comments");

    auto c(mock_repository(model_name));
    const auto po(mock_processed_object_factory::
        make_uml_note_with_marker_inside_large_package());
    transform(c, {po[0], po[1]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);

        if (m.name().simple() == model_name) {
            const auto& l(m.name().location());
            BOOST_REQUIRE(l.model_modules().size() == 1);
            BOOST_CHECK(l.model_modules().front() == model_name);
            BOOST_CHECK(m.name().simple() == model_name);
            BOOST_CHECK(m.documentation().empty());
            BOOST_CHECK(m.annotations().fields().empty());
        } else {
            BOOST_CHECK(!m.name().simple().empty());
            BOOST_CHECK(!m.documentation().empty());
            BOOST_CHECK(!m.annotations().fields().empty());
        }
    }
}

BOOST_AUTO_TEST_CASE(uml_note_with_text_but_no_marker_inside_package_does_nothing) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_text_but_no_marker_inside_package_does_nothing");
    auto c(mock_repository(model_name));
    const auto po(mock_processed_object_factory::
        make_uml_note_inside_large_package());
    transform(c, {po[0], po[1]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_REQUIRE(c.model().modules().size() == 2);

    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        if (m.name().simple() == model_name) {
            const auto& l(m.name().location());
            BOOST_REQUIRE(l.model_modules().size() == 1);
            BOOST_CHECK(l.model_modules().front() == model_name);
            BOOST_CHECK(m.name().simple() == model_name);
            BOOST_CHECK(m.documentation().empty());
            BOOST_CHECK(m.annotations().fields().empty());
        } else {
            BOOST_CHECK(!m.name().simple().empty());
            BOOST_CHECK(m.documentation().empty());
            BOOST_CHECK(m.annotations().fields().empty());
        }
    }
}

BOOST_AUTO_TEST_CASE(empty_uml_note_inside_package_does_nothing) {
    SETUP_TEST_LOG_SOURCE("empty_uml_note_inside_package_does_nothing");

    auto c(mock_repository(model_name));
    const auto po(mock_processed_object_factory::
        make_empty_uml_note_inside_large_package());
    transform(c, {po[0], po[1]});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_REQUIRE(c.model().modules().size() == 2);
    for (const auto& pair : c.model().modules()) {
        const auto& m(pair.second);
        if (m.name().simple() == model_name) {
            const auto& l(m.name().location());
            BOOST_REQUIRE(l.model_modules().size() == 1);
            BOOST_CHECK(l.model_modules().front() == model_name);
            BOOST_CHECK(m.name().simple() == model_name);
            BOOST_CHECK(m.documentation().empty());
            BOOST_CHECK(m.annotations().fields().empty());
        } else {
            BOOST_CHECK(!m.name().simple().empty());
            BOOST_CHECK(m.documentation().empty());
            BOOST_CHECK(m.annotations().fields().empty());
        }
    }
}

BOOST_AUTO_TEST_CASE(uml_class_with_inheritance_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_inheritance_results_in_expected_object");

    auto c(mock_repository(model_name));
    const auto po(mock_processed_object_factory::make_generalization());
    const auto con(po[0].connection());
    BOOST_REQUIRE(con);
    const auto parents = std::list<std::string> { con->first };
    c.child_id_to_parent_ids().insert(std::make_pair(con->second, parents));

    transform(c, {po[1], po[2]});
    BOOST_LOG_SEV(lg, debug) << "repository: " << c;

    BOOST_CHECK(c.model().modules().size() == 1);
    const auto m(c.model().modules().begin()->second);
    BOOST_CHECK(m.name().simple() == model_name);

    BOOST_REQUIRE(c.model().objects().size() == 2);
    for (const auto& pair : c.model().objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (is_type_one(n)) {
            BOOST_CHECK(!o.parent());
            BOOST_CHECK(!o.root_parent());
        } else if (is_type_two(n)) {
            BOOST_REQUIRE(o.parent());
            BOOST_CHECK(is_type_one(*o.parent()));
        } else {
            BOOST_LOG_SEV(lg, error) << "Unexpected type name: " << n.id();
            BOOST_FAIL("Unexpected type name");
        }
    }
}

BOOST_AUTO_TEST_CASE(uml_class_with_one_attribute_transforms_into_value_object_with_one_attribute) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_one_attribute_transforms_into_value_object_with_one_attribute");

    auto c(mock_repository());
    const auto po(mock_processed_object_factory::make_class_with_attribute());
    transform(c, {po});

    BOOST_LOG_SEV(lg, debug) << "repository: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    BOOST_CHECK(c.model().modules().size() == 1);
    const auto m(c.model().modules().begin()->second);
    BOOST_CHECK(m.name().simple() == model_name);

    const auto& o(c.model().objects().begin()->second);
    BOOST_CHECK(o.object_type() ==
        dogen::yarn::object_types::user_defined_value_object);
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() ==
        model_name);
    BOOST_CHECK(is_type_zero(o.name()));
    BOOST_CHECK(!o.documentation().empty());
    BOOST_REQUIRE(o.local_attributes().size() == 1);
    BOOST_CHECK(is_type_zero(o.local_attributes().front().name()));
    BOOST_CHECK(!o.local_attributes().front().documentation().empty());
}

BOOST_AUTO_TEST_SUITE_END()
*/
