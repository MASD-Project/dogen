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
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/factory.hpp"
#include "dogen/sml/types/repository.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/entity.hpp"
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
const std::string value_object_stereotype("value object");
const std::string exception_stereotype("exception");
const std::string entity_stereotype("entity");
const std::string keyed_entity_stereotype("keyed entity");
const std::string service_stereotype("service");
const std::string factory_stereotype("factory");
const std::string repository_stereotype("repository");

const std::string immutable_stereotype("immutable");

dogen::dia_to_sml::profile
mock_profile(const dogen::dia_to_sml::processed_object& o) {
    // FIXME: we should really be mocking the profile
    profiler profiler;
    return profiler.generate(o);
}

bool is_type_zero(const std::string& s) {
    return mock_processed_object_factory::to_object_name(0) == s;
}


bool is_type_zero(const dogen::sml::qname& qn) {
    return is_type_zero(qn.simple_name());
}

bool is_type_one(const dogen::sml::qname& qn) {
    return mock_processed_object_factory::to_object_name(1) == qn.simple_name();
}

bool is_type_two(const dogen::sml::qname& qn) {
    return mock_processed_object_factory::to_object_name(2) == qn.simple_name();
}

dogen::sml::qname mock_model_name(const std::string& mn) {
    dogen::sml::qname r;
    r.model_name(mn);
    return r;
}

dogen::dia_to_sml::context mock_context() {
    dogen::dia_to_sml::context r;
    r.model().name(mock_model_name(model_name));
    return r;
}

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(transformer)

BOOST_AUTO_TEST_CASE(empty_named_uml_class_throws) {
    SETUP_TEST_LOG_SOURCE("empty_named_uml_class_throws");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_empty_named_class());
    contains_checker<transformation_error> cc(empty_name);
    BOOST_CHECK_EXCEPTION(t.transform(o, mock_profile(o)), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_with_no_stereotype_transforms_into_expected_value_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_no_stereotype_transforms_into_expected_value_object");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    const auto o(mock_processed_object_factory::build_class());
    dogen::dia_to_sml::transformer t(c);
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& obj(*c.model().objects().begin()->second);
    const auto vo(dynamic_cast<const dogen::sml::value_object&>(obj));
    BOOST_CHECK(vo.name().model_name() == model_name);
    BOOST_CHECK(!vo.name().simple_name().empty());
    BOOST_CHECK(vo.properties().empty());
    BOOST_CHECK(!vo.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_value_object_stereotype_transforms_into_expected_value_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_value_object_stereotype_transforms_into_expected_value_object");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto st(value_object_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& ao(*c.model().objects().begin()->second);
    const auto vo(dynamic_cast<const dogen::sml::value_object&>(ao));
    BOOST_CHECK(vo.name().model_name() == model_name);
    BOOST_CHECK(is_type_zero(vo.name()));
    BOOST_CHECK(!vo.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto st(enumeration_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().objects().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().enumerations().size() == 1);

    const auto e(c.model().enumerations().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_transforms_into_expected_value_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_transforms_into_expected_value_object");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto st(exception_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& e(*c.model().objects().begin()->second);
    const auto vo(dynamic_cast<const dogen::sml::value_object&>(e));
    BOOST_CHECK(vo.name().model_name() == model_name);
    BOOST_CHECK(is_type_zero(vo.name()));
    BOOST_CHECK(!vo.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_service_stereotype_transforms_into_expected_service) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_service_stereotype_transforms_into_expected_service");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto st(service_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& ao(*c.model().objects().begin()->second);
    const auto s(dynamic_cast<const dogen::sml::service&>(ao));
    BOOST_CHECK(s.name().model_name() == model_name);
    BOOST_CHECK(is_type_zero(s.name()));
    BOOST_CHECK(!s.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_factory_stereotype_transforms_into_expected_factory) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_factory_stereotype_transforms_into_expected_factory");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto st(factory_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& ao(*c.model().objects().begin()->second);
    const auto f(dynamic_cast<const dogen::sml::factory&>(ao));
    BOOST_CHECK(f.name().model_name() == model_name);
    BOOST_CHECK(is_type_zero(f.name()));
    BOOST_CHECK(!f.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_repository_stereotype_transforms_into_expected_repository) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_repository_stereotype_transforms_into_expected_repository");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto st(repository_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& ao(*c.model().objects().begin()->second);
    const auto r(dynamic_cast<const dogen::sml::repository&>(ao));
    BOOST_CHECK(r.name().model_name() == model_name);
    BOOST_CHECK(is_type_zero(r.name()));
    BOOST_CHECK(!r.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_keyed_entity_stereotype_transforms_into_expected_keyed_entity) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_keyed_entity_stereotype_transforms_into_expected_keyed_entity");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto st(keyed_entity_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& ao(*c.model().objects().begin()->second);
    const auto ke(dynamic_cast<const dogen::sml::keyed_entity&>(ao));
    BOOST_CHECK(ke.name().model_name() == model_name);
    BOOST_CHECK(is_type_zero(ke.name()));
    BOOST_CHECK(!ke.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_entity_stereotype_transforms_into_expected_entity) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_entity_stereotype_transforms_into_expected_entity");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto st(entity_stereotype);
    const auto o(mock_processed_object_factory::build_class(0, st));
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& ao(*c.model().objects().begin()->second);
    const auto e(dynamic_cast<const dogen::sml::entity&>(ao));
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_large_package_transforms_into_expected_module) {
    SETUP_TEST_LOG_SOURCE("uml_large_package_transforms_into_expected_module");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_large_package());
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().objects().empty());

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto p(c.model().modules().begin()->second);
    BOOST_CHECK(p.name().model_name() == model_name);
    BOOST_CHECK(!p.name().simple_name().empty());
    BOOST_CHECK(p.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_in_package_transforms_into_expected_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_package_transforms_into_expected_object");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package());
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto pkg(c.model().modules().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().simple_name().empty());
    BOOST_CHECK(pkg.name().module_path().empty());

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& obj(*c.model().objects().begin()->second);
    BOOST_CHECK(obj.name().model_name() == model_name);
    BOOST_CHECK(!obj.name().simple_name().empty());
    BOOST_CHECK(obj.properties().empty());

    const auto vo(dynamic_cast<const dogen::sml::value_object&>(obj));
    BOOST_REQUIRE(obj.name().module_path().size() == 1);
    BOOST_CHECK(obj.name().module_path().front() == pkg.name().simple_name());
    BOOST_CHECK(!obj.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_in_package_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_in_package_transforms_into_expected_enumeration");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(enumeration_stereotype);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto pkg(c.model().modules().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().simple_name().empty());
    BOOST_CHECK(pkg.name().module_path().empty());

    BOOST_REQUIRE(c.model().enumerations().size() == 1);
    const auto e(c.model().enumerations().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().simple_name().empty());
    BOOST_REQUIRE(e.name().module_path().size() == 1);
    BOOST_CHECK(e.name().module_path().front() == pkg.name().simple_name());
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_in_package_transforms_into_expected_exception) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_in_package_transforms_into_expected_exception");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(exception_stereotype);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto pkg(c.model().modules().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().simple_name().empty());
    BOOST_CHECK(pkg.name().module_path().empty());

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto e(dynamic_cast<const dogen::sml::value_object&>(ao));
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().simple_name().empty());
    BOOST_REQUIRE(e.name().module_path().size() == 1);
    BOOST_CHECK(e.name().module_path().front() == pkg.name().simple_name());
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_service_stereotype_in_package_transforms_into_expected_service) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_service_stereotype_in_package_transforms_into_expected_service");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(service_stereotype);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto pkg(c.model().modules().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().simple_name().empty());
    BOOST_CHECK(pkg.name().module_path().empty());

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto s(dynamic_cast<const dogen::sml::service&>(ao));
    BOOST_CHECK(s.name().model_name() == model_name);
    BOOST_CHECK(!s.name().simple_name().empty());
    BOOST_REQUIRE(s.name().module_path().size() == 1);
    BOOST_CHECK(s.name().module_path().front() == pkg.name().simple_name());
    BOOST_CHECK(!s.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_factory_stereotype_in_package_transforms_into_expected_factory) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_factory_stereotype_in_package_transforms_into_expected_factory");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(factory_stereotype);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto pkg(c.model().modules().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().simple_name().empty());
    BOOST_CHECK(pkg.name().module_path().empty());

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto f(dynamic_cast<const dogen::sml::factory&>(ao));
    BOOST_CHECK(f.name().model_name() == model_name);
    BOOST_CHECK(!f.name().simple_name().empty());
    BOOST_REQUIRE(f.name().module_path().size() == 1);
    BOOST_CHECK(f.name().module_path().front() == pkg.name().simple_name());
    BOOST_CHECK(!f.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_repository_stereotype_in_package_transforms_into_expected_repository) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_repository_stereotype_in_package_transforms_into_expected_repository");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(repository_stereotype);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto pkg(c.model().modules().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().simple_name().empty());
    BOOST_CHECK(pkg.name().module_path().empty());

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto r(dynamic_cast<const dogen::sml::repository&>(ao));
    BOOST_CHECK(r.name().model_name() == model_name);
    BOOST_CHECK(!r.name().simple_name().empty());
    BOOST_REQUIRE(r.name().module_path().size() == 1);
    BOOST_CHECK(r.name().module_path().front() == pkg.name().simple_name());
    BOOST_CHECK(!r.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_entity_stereotype_in_package_transforms_into_expected_entity) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_entity_stereotype_in_package_transforms_into_expected_entity");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(entity_stereotype);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto pkg(c.model().modules().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().simple_name().empty());
    BOOST_CHECK(pkg.name().module_path().empty());

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto e(dynamic_cast<const dogen::sml::entity&>(ao));
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().simple_name().empty());
    BOOST_REQUIRE(e.name().module_path().size() == 1);
    BOOST_CHECK(e.name().module_path().front() == pkg.name().simple_name());
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_keyed_entity_stereotype_in_package_transforms_into_expected_keyed_entity) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_keyed_entity_stereotype_in_package_transforms_into_expected_keyed_entity");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(keyed_entity_stereotype);
    const auto a(
        mock_processed_object_factory::build_class_inside_large_package(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 1);
    const auto pkg(c.model().modules().begin()->second);
    BOOST_CHECK(pkg.name().model_name() == model_name);
    BOOST_CHECK(!pkg.name().simple_name().empty());
    BOOST_CHECK(pkg.name().module_path().empty());

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto ke(dynamic_cast<const dogen::sml::keyed_entity&>(ao));
    BOOST_CHECK(ke.name().model_name() == model_name);
    BOOST_CHECK(!ke.name().simple_name().empty());
    BOOST_REQUIRE(ke.name().module_path().size() == 1);
    BOOST_CHECK(ke.name().module_path().front() == pkg.name().simple_name());
    BOOST_CHECK(!ke.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_in_non_existing_package_throws) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_non_existing_package_throws");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    auto a(
        mock_processed_object_factory::build_class_inside_large_package());
    auto o(a[1]);
    auto op(mock_profile(o));
    contains_checker<transformation_error> cc(missing_qname);
    BOOST_CHECK_EXCEPTION(t.transform(o, op), transformation_error, cc);

    auto st(enumeration_stereotype);
    a = mock_processed_object_factory::build_class_inside_large_package(0 , st);
    o = a[1];
    op = mock_profile(o);
    BOOST_CHECK_EXCEPTION(t.transform(o, op), transformation_error, cc);

    st = exception_stereotype;
    a = mock_processed_object_factory::build_class_inside_large_package(0 , st);
    o = a[1];
    op = mock_profile(o);
    BOOST_CHECK_EXCEPTION(t.transform(o, op), transformation_error, cc);

    st = service_stereotype;
    a = mock_processed_object_factory::build_class_inside_large_package(0 , st);
    o = a[1];
    op = mock_profile(o);
    BOOST_CHECK_EXCEPTION(t.transform(o, op), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_in_two_packages_transforms_into_expected_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_two_packages_transforms_into_expected_object");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto a(
        mock_processed_object_factory::build_class_inside_two_large_packages());
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));
    t.transform(a[2], mock_profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    auto i(c.model().modules().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().simple_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().simple_name().empty());

    BOOST_CHECK(
        pkg1.name().module_path().empty() ||
        pkg2.name().module_path().empty());

    BOOST_CHECK(
        !pkg1.name().module_path().empty() ||
        !pkg2.name().module_path().empty());

    std::string first, second;
    if (pkg1.name().module_path().empty()) {
        first = pkg1.name().simple_name();
        second = pkg2.name().simple_name();
        BOOST_CHECK(pkg2.name().module_path().front() == first);
    } else {
        first = pkg2.name().simple_name();
        second = pkg1.name().simple_name();
        BOOST_CHECK(pkg1.name().module_path().front() == first);
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& obj(*c.model().objects().begin()->second);
    BOOST_CHECK(obj.name().model_name() == model_name);
    BOOST_CHECK(!obj.name().simple_name().empty());
    BOOST_CHECK(obj.properties().empty());
    const auto vo(dynamic_cast<const dogen::sml::value_object&>(obj));
    BOOST_REQUIRE(obj.name().module_path().size() == 2);
    BOOST_CHECK(obj.name().module_path().front() == first);
    BOOST_CHECK(obj.name().module_path().back() == second);
    BOOST_CHECK(!obj.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_in_two_packages_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_in_two_packages_transforms_into_expected_enumeration");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(enumeration_stereotype);
    const auto a(mock_processed_object_factory::
        build_class_inside_two_large_packages(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));
    t.transform(a[2], mock_profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    auto i(c.model().modules().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().simple_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().simple_name().empty());

    BOOST_CHECK(
        pkg1.name().module_path().empty() ||
        pkg2.name().module_path().empty());

    BOOST_CHECK(
        !pkg1.name().module_path().empty() ||
        !pkg2.name().module_path().empty());

    std::string first, second;
    if (pkg1.name().module_path().empty()) {
        first = pkg1.name().simple_name();
        second = pkg2.name().simple_name();
        BOOST_CHECK(pkg2.name().module_path().front() == first);
    } else {
        first = pkg2.name().simple_name();
        second = pkg1.name().simple_name();
        BOOST_CHECK(pkg1.name().module_path().front() == first);
    }

    BOOST_REQUIRE(c.model().enumerations().size() == 1);
    const auto e(c.model().enumerations().begin()->second);
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().simple_name().empty());
    BOOST_REQUIRE(e.name().module_path().size() == 2);
    BOOST_CHECK(e.name().module_path().front() == first);
    BOOST_CHECK(e.name().module_path().back() == second);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_in_two_packages_transforms_into_expected_exception) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_in_two_packages_transforms_into_expected_exception");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(exception_stereotype);
    const auto a(mock_processed_object_factory::
        build_class_inside_two_large_packages(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));
    t.transform(a[2], mock_profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    auto i(c.model().modules().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().simple_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().simple_name().empty());

    BOOST_CHECK(
        pkg1.name().module_path().empty() ||
        pkg2.name().module_path().empty());

    BOOST_CHECK(
        !pkg1.name().module_path().empty() ||
        !pkg2.name().module_path().empty());

    std::string first, second;
    if (pkg1.name().module_path().empty()) {
        first = pkg1.name().simple_name();
        second = pkg2.name().simple_name();
        BOOST_CHECK(pkg2.name().module_path().front() == first);
    } else {
        first = pkg2.name().simple_name();
        second = pkg1.name().simple_name();
        BOOST_CHECK(pkg1.name().module_path().front() == first);
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto e(dynamic_cast<const dogen::sml::value_object&>(ao));
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().simple_name().empty());
    BOOST_REQUIRE(e.name().module_path().size() == 2);
    BOOST_CHECK(e.name().module_path().front() == first);
    BOOST_CHECK(e.name().module_path().back() == second);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_service_stereotype_in_two_packages_transforms_into_expected_service) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_service_stereotype_in_two_packages_transforms_into_expected_service");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(service_stereotype);
    const auto a(mock_processed_object_factory::
        build_class_inside_two_large_packages(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));
    t.transform(a[2], mock_profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    auto i(c.model().modules().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().simple_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().simple_name().empty());

    BOOST_CHECK(
        pkg1.name().module_path().empty() ||
        pkg2.name().module_path().empty());

    BOOST_CHECK(
        !pkg1.name().module_path().empty() ||
        !pkg2.name().module_path().empty());

    std::string first, second;
    if (pkg1.name().module_path().empty()) {
        first = pkg1.name().simple_name();
        second = pkg2.name().simple_name();
        BOOST_CHECK(pkg2.name().module_path().front() == first);
    } else {
        first = pkg2.name().simple_name();
        second = pkg1.name().simple_name();
        BOOST_CHECK(pkg1.name().module_path().front() == first);
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto s(dynamic_cast<const dogen::sml::service&>(ao));
    BOOST_CHECK(s.name().model_name() == model_name);
    BOOST_CHECK(!s.name().simple_name().empty());
    BOOST_REQUIRE(s.name().module_path().size() == 2);
    BOOST_CHECK(s.name().module_path().front() == first);
    BOOST_CHECK(s.name().module_path().back() == second);
    BOOST_CHECK(!s.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_factory_stereotype_in_two_packages_transforms_into_expected_factory) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_factory_stereotype_in_two_packages_transforms_into_expected_factory");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(factory_stereotype);
    const auto a(mock_processed_object_factory::
        build_class_inside_two_large_packages(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));
    t.transform(a[2], mock_profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    auto i(c.model().modules().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().simple_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().simple_name().empty());

    BOOST_CHECK(
        pkg1.name().module_path().empty() ||
        pkg2.name().module_path().empty());

    BOOST_CHECK(
        !pkg1.name().module_path().empty() ||
        !pkg2.name().module_path().empty());

    std::string first, second;
    if (pkg1.name().module_path().empty()) {
        first = pkg1.name().simple_name();
        second = pkg2.name().simple_name();
        BOOST_CHECK(pkg2.name().module_path().front() == first);
    } else {
        first = pkg2.name().simple_name();
        second = pkg1.name().simple_name();
        BOOST_CHECK(pkg1.name().module_path().front() == first);
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto f(dynamic_cast<const dogen::sml::factory&>(ao));
    BOOST_CHECK(f.name().model_name() == model_name);
    BOOST_CHECK(!f.name().simple_name().empty());
    BOOST_REQUIRE(f.name().module_path().size() == 2);
    BOOST_CHECK(f.name().module_path().front() == first);
    BOOST_CHECK(f.name().module_path().back() == second);
    BOOST_CHECK(!f.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_repository_stereotype_in_two_packages_transforms_into_expected_repository) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_repository_stereotype_in_two_packages_transforms_into_expected_repository");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(repository_stereotype);
    const auto a(mock_processed_object_factory::
        build_class_inside_two_large_packages(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));
    t.transform(a[2], mock_profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    auto i(c.model().modules().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().simple_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().simple_name().empty());

    BOOST_CHECK(
        pkg1.name().module_path().empty() ||
        pkg2.name().module_path().empty());

    BOOST_CHECK(
        !pkg1.name().module_path().empty() ||
        !pkg2.name().module_path().empty());

    std::string first, second;
    if (pkg1.name().module_path().empty()) {
        first = pkg1.name().simple_name();
        second = pkg2.name().simple_name();
        BOOST_CHECK(pkg2.name().module_path().front() == first);
    } else {
        first = pkg2.name().simple_name();
        second = pkg1.name().simple_name();
        BOOST_CHECK(pkg1.name().module_path().front() == first);
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto r(dynamic_cast<const dogen::sml::repository&>(ao));
    BOOST_CHECK(r.name().model_name() == model_name);
    BOOST_CHECK(!r.name().simple_name().empty());
    BOOST_REQUIRE(r.name().module_path().size() == 2);
    BOOST_CHECK(r.name().module_path().front() == first);
    BOOST_CHECK(r.name().module_path().back() == second);
    BOOST_CHECK(!r.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_entity_stereotype_in_two_packages_transforms_into_expected_entity) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_entity_stereotype_in_two_packages_transforms_into_expected_entity");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(entity_stereotype);
    const auto a(mock_processed_object_factory::
        build_class_inside_two_large_packages(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));
    t.transform(a[2], mock_profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    auto i(c.model().modules().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().simple_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().simple_name().empty());

    BOOST_CHECK(
        pkg1.name().module_path().empty() ||
        pkg2.name().module_path().empty());

    BOOST_CHECK(
        !pkg1.name().module_path().empty() ||
        !pkg2.name().module_path().empty());

    std::string first, second;
    if (pkg1.name().module_path().empty()) {
        first = pkg1.name().simple_name();
        second = pkg2.name().simple_name();
        BOOST_CHECK(pkg2.name().module_path().front() == first);
    } else {
        first = pkg2.name().simple_name();
        second = pkg1.name().simple_name();
        BOOST_CHECK(pkg1.name().module_path().front() == first);
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto e(dynamic_cast<const dogen::sml::entity&>(ao));
    BOOST_CHECK(e.name().model_name() == model_name);
    BOOST_CHECK(!e.name().simple_name().empty());
    BOOST_REQUIRE(e.name().module_path().size() == 2);
    BOOST_CHECK(e.name().module_path().front() == first);
    BOOST_CHECK(e.name().module_path().back() == second);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_keyed_entity_stereotype_in_two_packages_transforms_into_expected_keyed_entity) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_keyed_entity_stereotype_in_two_packages_transforms_into_expected_keyed_entity");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto st(keyed_entity_stereotype);
    const auto a(mock_processed_object_factory::
        build_class_inside_two_large_packages(0, st));
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));
    t.transform(a[2], mock_profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_REQUIRE(c.model().modules().size() == 2);
    auto i(c.model().modules().begin());

    const auto pkg1(i->second);
    BOOST_CHECK(pkg1.name().model_name() == model_name);
    BOOST_CHECK(!pkg1.name().simple_name().empty());

    const auto pkg2((++i)->second);
    BOOST_CHECK(pkg2.name().model_name() == model_name);
    BOOST_CHECK(!pkg2.name().simple_name().empty());

    BOOST_CHECK(
        pkg1.name().module_path().empty() ||
        pkg2.name().module_path().empty());

    BOOST_CHECK(
        !pkg1.name().module_path().empty() ||
        !pkg2.name().module_path().empty());

    std::string first, second;
    if (pkg1.name().module_path().empty()) {
        first = pkg1.name().simple_name();
        second = pkg2.name().simple_name();
        BOOST_CHECK(pkg2.name().module_path().front() == first);
    } else {
        first = pkg2.name().simple_name();
        second = pkg1.name().simple_name();
        BOOST_CHECK(pkg1.name().module_path().front() == first);
    }

    BOOST_REQUIRE(c.model().objects().size() == 1);
    const auto& ao(*c.model().objects().begin()->second);
    const auto ke(dynamic_cast<const dogen::sml::keyed_entity&>(ao));
    BOOST_CHECK(ke.name().model_name() == model_name);
    BOOST_CHECK(!ke.name().simple_name().empty());
    BOOST_REQUIRE(ke.name().module_path().size() == 2);
    BOOST_CHECK(ke.name().module_path().front() == first);
    BOOST_CHECK(ke.name().module_path().back() == second);
    BOOST_CHECK(!ke.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_note_with_marker_transforms_into_model_comments) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_two_packages_transforms_into_expected_object");

    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_uml_note_with_marker());
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(!c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().size() == 1);
}

BOOST_AUTO_TEST_CASE(uml_note_with_text_but_no_marker_does_nothing) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_text_but_no_marker_does_nothing");

    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_uml_note());
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(empty_uml_note_does_nothing) {
    SETUP_TEST_LOG_SOURCE("empty_uml_note_does_nothing");

    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_empty_uml_note());
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(uml_note_with_marker_inside_package_transforms_into_package_comments) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_marker_inside_package_transforms_into_package_comments");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto a(mock_processed_object_factory::
        build_uml_note_with_marker_inside_large_package());
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
    BOOST_REQUIRE(c.model().modules().size() == 1);

    const auto p(c.model().modules().begin()->second);
    BOOST_CHECK(!p.documentation().empty());
    BOOST_CHECK(!p.implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(uml_note_with_text_but_no_marker_inside_package_does_nothing) {
    SETUP_TEST_LOG_SOURCE("uml_note_with_text_but_no_marker_inside_package_does_nothing");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto a(mock_processed_object_factory::
        build_uml_note_inside_large_package());
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
    BOOST_REQUIRE(c.model().modules().size() == 1);

    const auto p(c.model().modules().begin()->second);
    BOOST_CHECK(p.documentation().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(empty_uml_note_inside_package_does_nothing) {
    SETUP_TEST_LOG_SOURCE("empty_uml_note_inside_package_does_nothing");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    dogen::dia_to_sml::transformer t(c);
    const auto a(mock_processed_object_factory::
        build_empty_uml_note_inside_large_package());
    t.transform(a[0], mock_profile(a[0]));
    t.transform(a[1], mock_profile(a[1]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().documentation().empty());
    BOOST_CHECK(c.model().implementation_specific_parameters().empty());
    BOOST_REQUIRE(c.model().modules().size() == 1);

    const auto p(c.model().modules().begin()->second);
    BOOST_CHECK(p.documentation().empty());
    BOOST_CHECK(p.implementation_specific_parameters().empty());
}

BOOST_AUTO_TEST_CASE(inheritance_with_immutability_throws) {
    SETUP_TEST_LOG_SOURCE("inheritance_with_immutability_throws");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));


    const auto a(mock_processed_object_factory::build_generalization());
    const auto con(a[0].connection());
    BOOST_REQUIRE(con);
    const auto parents = std::list<std::string> { con->first };
    c.child_id_to_parent_ids().insert(std::make_pair(con->second, parents));

    dogen::dia_to_sml::transformer t1(c);
    t1.transform(a[1], mock_profile(a[1]));
    auto po1(a[2]);
    po1.stereotype(immutable_stereotype);
    const auto op1(mock_profile(po1));
    contains_checker<transformation_error> cc(immutability_inheritance);
    BOOST_CHECK_EXCEPTION(t1.transform(po1, op1), transformation_error, cc);

    c.child_id_to_parent_ids().clear();
    c.parent_ids().insert(con->first);
    dogen::dia_to_sml::transformer t2(c);
    auto po2(a[1]);
    po2.stereotype(immutable_stereotype);
    const auto op2(mock_profile(po2));
    BOOST_CHECK_EXCEPTION(t1.transform(po2, op2), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_with_inheritance_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_inheritance_results_in_expected_object");
    dogen::dia_to_sml::context c;
    c.model().name(mock_model_name(model_name));

    const auto a(mock_processed_object_factory::build_generalization());
    const auto con(a[0].connection());
    BOOST_REQUIRE(con);
    const auto parents = std::list<std::string> { con->first };
    c.child_id_to_parent_ids().insert(std::make_pair(con->second, parents));
    c.parent_ids().insert(con->first);

    dogen::dia_to_sml::transformer t1(c);
    t1.transform(a[1], mock_profile(a[1]));
    t1.transform(a[2], mock_profile(a[2]));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;

    BOOST_CHECK(c.model().modules().empty());
    BOOST_REQUIRE(c.model().objects().size() == 2);
    for (const auto& pair : c.model().objects()) {
        const auto& qn(pair.first);
        const auto& o(*pair.second);
        if (is_type_one(qn)) {
            BOOST_CHECK(!o.parent_name());
            BOOST_CHECK(!o.original_parent_name());
        } else if (is_type_two(qn)) {
            BOOST_REQUIRE(o.parent_name());
            BOOST_REQUIRE(is_type_one(*o.parent_name()));
        } else {
            BOOST_LOG_SEV(lg, error) << "Unexpected type name: " << qn;
            BOOST_FAIL("Unexpected type name");
        }
    }
}

BOOST_AUTO_TEST_CASE(uml_class_with_one_property_transforms_into_value_object_with_one_property) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_one_property_transforms_into_value_object_with_one_property");

    auto c(mock_context());
    dogen::dia_to_sml::transformer t(c);
    const auto o(mock_processed_object_factory::build_class_with_property());
    t.transform(o, mock_profile(o));

    BOOST_LOG_SEV(lg, debug) << "context: " << c;
    BOOST_CHECK(c.model().enumerations().empty());
    BOOST_CHECK(c.model().primitives().empty());
    BOOST_REQUIRE(c.model().objects().size() == 1);

    const auto& ao(*c.model().objects().begin()->second);
    const auto vo(dynamic_cast<const dogen::sml::value_object&>(ao));
    BOOST_CHECK(vo.name().model_name() == model_name);

    BOOST_CHECK(is_type_zero(vo.name()));
    BOOST_CHECK(!vo.documentation().empty());
    BOOST_REQUIRE(vo.properties().size() == 1);
    BOOST_CHECK(is_type_zero(vo.properties().front().name()));
    BOOST_CHECK(!vo.properties().front().type().type().simple_name().empty());
    BOOST_CHECK(!vo.properties().front().documentation().empty());
}

BOOST_AUTO_TEST_SUITE_END()
