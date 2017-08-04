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
#include <sstream>
#include <initializer_list>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/io/meta_model/object_io.hpp"
#include "dogen/yarn/io/meta_model/enumeration_io.hpp"
#include "dogen/yarn/io/meta_model/module_io.hpp"
#include "dogen/yarn/io/meta_model/exception_io.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"
#include "dogen/yarn.dia/types/transformation_error.hpp"
#include "dogen/yarn.dia/io/context_io.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/test/mock_processed_object_factory.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::yarn::dia;
using dogen::utility::test::asserter;
using mock_factory = dogen::yarn::dia::test::mock_processed_object_factory;

namespace  {

const std::string test_module("yarn.dia");
const std::string test_suite("transformer_tests");

const std::string empty;
const std::string model_name("test");
const std::string empty_name("Dia object name is empty");
const std::string missing_mapping("Dia package ID is not mapped to");
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


dogen::yarn::meta_model::name mock_model_name(const std::string& mn) {
    dogen::yarn::helpers::name_factory nf;
    return nf.build_model_name(mn);;
}

dogen::yarn::dia::context empty_context;

}

using dogen::yarn::dia::transformation_error;
using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(transformer_tests)

BOOST_AUTO_TEST_CASE(empty_named_uml_class_throws) {
    SETUP_TEST_LOG_SOURCE("empty_named_uml_class_throws");

    auto ctx(empty_context);
    contains_checker<transformation_error> cc(empty_name);
    const auto po(mock_factory::make_empty_named_class());
    transformer t(ctx, mock_model_name(model_name));
    BOOST_CHECK_EXCEPTION(t.to_object(po), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_with_no_stereotype_transforms_into_expected_value_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_no_stereotype_transforms_into_expected_value_object");
    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto po(mock_factory::make_class());
    const auto ptr(t.to_object(po));
    const auto& o(*ptr);
    BOOST_LOG_SEV(lg, debug) << "Object: " << o;

    BOOST_CHECK(o.name().simple() == po.name());
    BOOST_REQUIRE(o.parents().empty());
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() == model_name);
    BOOST_CHECK(o.local_attributes().empty());
    BOOST_CHECK(!o.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_transforms_into_expected_enumeration");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto st(enumeration_stereotype);
    const auto po(mock_factory::make_class(0, st));
    const auto ptr(t.to_enumeration(po));
    const auto& e(*ptr);
    BOOST_LOG_SEV(lg, debug) << "Enumeration: " << e;

    BOOST_CHECK(e.name().simple() == po.name());
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() == model_name);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_transforms_into_expected_exception) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_transforms_into_expected_exception");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto st(exception_stereotype);
    const auto po(mock_factory::make_class(0, st));
    const auto ptr(t.to_enumeration(po));
    const auto& e(*ptr);
    BOOST_LOG_SEV(lg, debug) << "Exception: " << e;

    BOOST_CHECK(e.name().simple() == po.name());
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() == model_name);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_large_package_transforms_into_expected_module) {
    SETUP_TEST_LOG_SOURCE("uml_large_package_transforms_into_expected_module");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto po(mock_factory::make_large_package());
    const auto ptr(t.to_module(po));
    const auto& m(*ptr);
    BOOST_LOG_SEV(lg, debug) << "Module: " << m;

    BOOST_CHECK(m.name().simple() == po.name());
    BOOST_REQUIRE(m.name().simple() == po.name());
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() == model_name);
    BOOST_CHECK(m.name().location().internal_modules().empty());
    BOOST_CHECK(!m.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_in_package_transforms_into_expected_elements) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_package_transforms_into_expected_elements");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto pos(mock_factory::make_class_inside_large_package());
    const auto ptr1(t.to_module(pos[0]));
    const auto& m(*ptr1);
    BOOST_LOG_SEV(lg, debug) << "Module: " << m;

    BOOST_CHECK(m.name().simple() == pos[0].name());
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() == model_name);
    BOOST_CHECK(m.name().location().internal_modules().empty());
    BOOST_CHECK(!m.documentation().empty());
    std::string module_name(m.name().simple());

    ctx.dia_id_to_module()[pos[0].id()] = ptr1;

    const auto ptr2(t.to_object(pos[1]));
    const auto o(*ptr2);
    BOOST_LOG_SEV(lg, debug) << "Object: " << o;

    BOOST_CHECK(o.name().simple() == pos[1].name());
    BOOST_REQUIRE(o.parents().empty());
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() == model_name);
    BOOST_CHECK(o.local_attributes().empty());
    BOOST_REQUIRE(o.name().location().internal_modules().size() == 1);
    BOOST_CHECK(o.name().location().internal_modules().front() == module_name);
    BOOST_CHECK(!o.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_in_package_transforms_into_expected_elements) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_in_package_transforms_into_expected_elements");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto st(enumeration_stereotype);
    const auto pos(mock_factory::make_class_inside_large_package(0, st));
    const auto ptr1(t.to_module(pos[0]));
    const auto& m(*ptr1);
    BOOST_LOG_SEV(lg, debug) << "Module: " << m;

    BOOST_CHECK(m.name().simple() == pos[0].name());
    BOOST_REQUIRE(m.name().simple() == pos[0].name());
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() == model_name);
    BOOST_CHECK(m.name().location().internal_modules().empty());
    BOOST_CHECK(!m.documentation().empty());
    std::string module_name(m.name().simple());

    ctx.dia_id_to_module()[pos[0].id()] = ptr1;

    const auto ptr2(t.to_enumeration(pos[1]));
    const auto& e(*ptr2);
    BOOST_LOG_SEV(lg, debug) << "Enumeration: " << e;

    BOOST_CHECK(e.name().simple() == pos[1].name());
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() == model_name);
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() == model_name);
    BOOST_REQUIRE(e.name().location().internal_modules().size() == 1);
    BOOST_CHECK(e.name().location().internal_modules().front() == module_name);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_in_package_transforms_into_expected_elements) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_in_package_transforms_into_expected_elements");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto st(exception_stereotype);
    const auto pos(mock_factory::make_class_inside_large_package(0, st));
    const auto ptr1(t.to_module(pos[0]));
    const auto& m(*ptr1);
    BOOST_LOG_SEV(lg, debug) << "Module: " << m;

    BOOST_CHECK(m.name().simple() == pos[0].name());
    BOOST_CHECK(m.name().simple() == pos[0].name());
    BOOST_REQUIRE(m.name().location().model_modules().size() == 1);
    BOOST_CHECK(m.name().location().model_modules().front() == model_name);
    BOOST_CHECK(m.name().location().internal_modules().empty());
    BOOST_CHECK(!m.documentation().empty());
    std::string module_name(m.name().simple());

    ctx.dia_id_to_module()[pos[0].id()] = ptr1;

    const auto ptr2(t.to_exception(pos[1]));
    const auto e(*ptr2);
    BOOST_LOG_SEV(lg, debug) << "Exception: " << e;

    BOOST_CHECK(e.name().simple() == pos[1].name());
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() == model_name);
    BOOST_REQUIRE(e.name().location().internal_modules().size() == 1);
    BOOST_CHECK(e.name().location().internal_modules().front() == module_name);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_in_non_existing_package_throws) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_non_existing_package_throws");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    auto pos(mock_factory::make_class_inside_large_package());
    contains_checker<transformation_error> cc(missing_mapping);
    BOOST_CHECK_EXCEPTION(t.to_object(pos[1]), transformation_error, cc);

    auto st(enumeration_stereotype);
    pos = mock_factory::make_class_inside_large_package(0 , st);
    BOOST_CHECK_EXCEPTION(t.to_object(pos[1]), transformation_error, cc);

    st = exception_stereotype;
    pos = mock_factory::make_class_inside_large_package(0 , st);
    BOOST_CHECK_EXCEPTION(t.to_object(pos[1]), transformation_error, cc);

    st = service_stereotype;
    pos = mock_factory::make_class_inside_large_package(0 , st);
    BOOST_CHECK_EXCEPTION(t.to_object(pos[1]), transformation_error, cc);
}

BOOST_AUTO_TEST_CASE(uml_class_in_two_packages_transforms_into_expected_elements) {
    SETUP_TEST_LOG_SOURCE("uml_class_in_two_packages_transforms_into_expected_elements");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto st(exception_stereotype);
    const auto pos(mock_factory::make_class_inside_two_large_packages());
    const auto ptr0(t.to_module(pos[0]));
    const auto& m0(*ptr0);
    BOOST_LOG_SEV(lg, debug) << "Module 0: " << m0;

    BOOST_CHECK(m0.name().simple() == pos[0].name());
    BOOST_REQUIRE(m0.name().location().model_modules().size() == 1);
    BOOST_CHECK(m0.name().location().model_modules().front() == model_name);
    BOOST_CHECK(m0.name().location().internal_modules().empty());
    BOOST_CHECK(!m0.documentation().empty());
    std::string m0_name(m0.name().simple());

    ctx.dia_id_to_module()[pos[0].id()] = ptr0;

    const auto ptr1(t.to_module(pos[1]));
    const auto& m1(*ptr1);
    BOOST_LOG_SEV(lg, debug) << "Module 1: " << m1;

    BOOST_CHECK(m1.name().simple() == pos[1].name());
    BOOST_REQUIRE(m1.name().location().model_modules().size() == 1);
    BOOST_CHECK(m1.name().location().model_modules().front() == model_name);
    BOOST_REQUIRE(m1.name().location().internal_modules().size() == 1);
    BOOST_CHECK(m1.name().location().internal_modules().front() == m0_name);
    std::string m1_name(m1.name().simple());

    ctx.dia_id_to_module()[pos[1].id()] = ptr1;

    const auto ptr2(t.to_object(pos[2]));
    const auto& o(*ptr2);
    BOOST_LOG_SEV(lg, debug) << "Object: " << o;

    BOOST_CHECK(o.name().simple() == pos[2].name());
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() == model_name);
    BOOST_CHECK(o.local_attributes().empty());
    BOOST_REQUIRE(o.name().location().internal_modules().size() == 2);
    BOOST_CHECK(o.name().location().internal_modules().front() == m0_name);
    BOOST_CHECK(o.name().location().internal_modules().back() == m1_name);
    BOOST_CHECK(!o.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_enumeration_stereotype_in_two_packages_transforms_into_expected_elements) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_enumeration_stereotype_in_two_packages_transforms_into_expected_elements");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto st(exception_stereotype);
    const auto pos(mock_factory::make_class_inside_two_large_packages());
    const auto ptr0(t.to_module(pos[0]));
    const auto& m0(*ptr0);
    BOOST_LOG_SEV(lg, debug) << "Module 0: " << m0;

    BOOST_CHECK(m0.name().simple() == pos[0].name());
    BOOST_REQUIRE(m0.name().location().model_modules().size() == 1);
    BOOST_CHECK(m0.name().location().model_modules().front() == model_name);
    BOOST_CHECK(m0.name().location().internal_modules().empty());
    BOOST_CHECK(!m0.documentation().empty());
    std::string m0_name(m0.name().simple());

    ctx.dia_id_to_module()[pos[0].id()] = ptr0;

    const auto ptr1(t.to_module(pos[1]));
    const auto& m1(*ptr1);
    BOOST_LOG_SEV(lg, debug) << "Module 1: " << m1;

    BOOST_CHECK(m1.name().simple() == pos[1].name());
    BOOST_REQUIRE(m1.name().location().model_modules().size() == 1);
    BOOST_CHECK(m1.name().location().model_modules().front() == model_name);
    BOOST_REQUIRE(m1.name().location().internal_modules().size() == 1);
    BOOST_CHECK(m1.name().location().internal_modules().front() == m0_name);
    std::string m1_name(m1.name().simple());

    ctx.dia_id_to_module()[pos[1].id()] = ptr1;

    const auto ptr2(t.to_enumeration(pos[2]));
    const auto& e(*ptr2);
    BOOST_LOG_SEV(lg, debug) << "Enumeration: " << e;

    BOOST_CHECK(e.name().simple() == pos[2].name());
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() == model_name);
    BOOST_REQUIRE(e.name().location().internal_modules().size() == 2);
    BOOST_CHECK(e.name().location().internal_modules().front() == m0_name);
    BOOST_CHECK(e.name().location().internal_modules().back() == m1_name);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_exception_stereotype_in_two_packages_transforms_into_expected_elements) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_exception_stereotype_in_two_packages_transforms_into_expected_elements");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto st(exception_stereotype);
    const auto pos(mock_factory::make_class_inside_two_large_packages());
    const auto ptr0(t.to_module(pos[0]));
    const auto& m0(*ptr0);
    BOOST_LOG_SEV(lg, debug) << "Module 0: " << m0;

    BOOST_CHECK(m0.name().simple() == pos[0].name());
    BOOST_REQUIRE(m0.name().location().model_modules().size() == 1);
    BOOST_CHECK(m0.name().location().model_modules().front() == model_name);
    BOOST_CHECK(m0.name().location().internal_modules().empty());
    BOOST_CHECK(!m0.documentation().empty());
    std::string m0_name(m0.name().simple());

    ctx.dia_id_to_module()[pos[0].id()] = ptr0;

    const auto ptr1(t.to_module(pos[1]));
    const auto& m1(*ptr1);
    BOOST_LOG_SEV(lg, debug) << "Module 1: " << m1;

    BOOST_CHECK(m1.name().simple() == pos[1].name());
    BOOST_REQUIRE(m1.name().location().model_modules().size() == 1);
    BOOST_CHECK(m1.name().location().model_modules().front() == model_name);
    BOOST_REQUIRE(m1.name().location().internal_modules().size() == 1);
    BOOST_CHECK(m1.name().location().internal_modules().front() == m0_name);
    std::string m1_name(m1.name().simple());

    ctx.dia_id_to_module()[pos[1].id()] = ptr1;

    const auto ptr2(t.to_exception(pos[2]));
    const auto& e(*ptr2);
    BOOST_LOG_SEV(lg, debug) << "Exception: " << e;

    BOOST_CHECK(e.name().simple() == pos[2].name());
    BOOST_REQUIRE(e.name().location().model_modules().size() == 1);
    BOOST_CHECK(e.name().location().model_modules().front() == model_name);
    BOOST_REQUIRE(e.name().location().internal_modules().size() == 2);
    BOOST_CHECK(e.name().location().internal_modules().front() == m0_name);
    BOOST_CHECK(e.name().location().internal_modules().back() == m1_name);
    BOOST_CHECK(!e.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_inheritance_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_inheritance_results_in_expected_object");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto pos(mock_factory::make_generalization());
    const auto con(pos[0].connection());
    BOOST_REQUIRE(con);

    const auto ptr0(t.to_object(pos[1]));
    const auto& p(*ptr0);
    BOOST_LOG_SEV(lg, debug) << "Parent: " << p;

    ctx.child_dia_id_to_parent_names()[con->second].push_back(p.name());

    BOOST_REQUIRE(p.parents().empty());
    BOOST_CHECK(p.name().simple() == pos[1].name());
    BOOST_REQUIRE(p.name().location().model_modules().size() == 1);
    BOOST_CHECK(p.name().location().model_modules().front() == model_name);
    BOOST_CHECK(p.local_attributes().empty());
    BOOST_REQUIRE(p.name().location().internal_modules().empty());
    BOOST_CHECK(!p.documentation().empty());

    const auto ptr1(t.to_object(pos[2]));
    const auto& c(*ptr1);
    BOOST_LOG_SEV(lg, debug) << "Child: " << c;
    BOOST_REQUIRE(c.parents().size() == 1);
    BOOST_CHECK(c.parents().front() == p.name());
    BOOST_CHECK(c.name().simple() == pos[2].name());
    BOOST_REQUIRE(c.name().location().model_modules().size() == 1);
    BOOST_CHECK(c.name().location().model_modules().front() == model_name);
    BOOST_CHECK(c.local_attributes().empty());
    BOOST_REQUIRE(c.name().location().internal_modules().empty());
    BOOST_CHECK(!c.documentation().empty());
}

BOOST_AUTO_TEST_CASE(uml_class_with_one_attribute_transforms_into_object_with_one_attribute) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_one_attribute_transforms_into_object_with_one_attribute");

    auto ctx(empty_context);
    transformer t(ctx, mock_model_name(model_name));

    const auto po(mock_factory::make_class_with_attribute());
    const auto ptr0(t.to_object(po));
    const auto& o(*ptr0);
    BOOST_LOG_SEV(lg, debug) << "Object: " << o;

    BOOST_REQUIRE(o.parents().empty());
    BOOST_CHECK(o.name().simple() == po.name());
    BOOST_REQUIRE(o.name().location().model_modules().size() == 1);
    BOOST_CHECK(o.name().location().model_modules().front() == model_name);
    BOOST_REQUIRE(o.name().location().internal_modules().empty());
    BOOST_REQUIRE(o.local_attributes().size() == 1);
    BOOST_CHECK(!o.documentation().empty());
    BOOST_CHECK(o.local_attributes().front().name().simple() == po.name());
    BOOST_CHECK(!o.local_attributes().front().documentation().empty());
}

BOOST_AUTO_TEST_SUITE_END()
