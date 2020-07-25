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
#include <array>
#include <boost/test/unit_test.hpp>
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/structural/object_io.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/test/mock_context_factory.hpp"
#include "dogen.logical/test/mock_model_factory.hpp"
#include "dogen.logical/types/transforms/object_templates_transform.hpp"

namespace {

const std::string test_module("dogen.logical.tests");
const std::string test_suite("object_templates_transform_tests");

const std::string object_template_not_found("Object template not found");
const std::string object_not_found("Object not found in model");

using dogen::logical::test::mock_model_factory;

/* @note tagging should make no difference to tests, and not having tags
 * makes the model dumps easier to understand.
 *
 * However, strictly speaking, tagging happens before transform so it
 * would be more truthful to use a tagged model in the tests.
 */
const mock_model_factory::flags flags(false/*tagged*/,
    false/*resolved*/, false/*merged*/, false/*object_templates_indexed*/,
    false/*attributes_indexed*/);

const mock_model_factory factory(flags);

}

using dogen::utility::test::contains_checker;
using dogen::logical::transforms::transformation_error;
using dogen::utility::test::asserter;
using dogen::logical::transforms::object_templates_transform;
using dogen::identification::entities::model_type;
using object_types = dogen::logical::test::mock_model_factory::
    object_types;
using attribute_types = dogen::logical::test::mock_model_factory::
    attribute_types;
using dogen::logical::test::mock_context_factory;

BOOST_AUTO_TEST_SUITE(object_templates_transform_tests)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_object_templates_transform) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_object_templates_transform");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_CHECK(a.structural_elements().objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    object_templates_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_attributes_is_untouched_by_object_templates_transform) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_attributes_is_untouched_by_object_templates_transform");

    auto a(factory.make_single_type_model());
    const auto e(factory.make_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;
    BOOST_CHECK(a.structural_elements().objects().size() == 1);

    object_templates_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_attribute_is_untouched_by_object_templates_transform) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_attribute_is_untouched_by_object_templates_transform");

    const auto mt(model_type::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::unsigned_int);
    auto a(factory.object_with_attribute(mt, objt, pt));
    const auto e(factory.object_with_attribute(mt, objt, pt));

    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    BOOST_CHECK(a.structural_elements().object_templates().empty());
    BOOST_CHECK(a.structural_elements().enumerations().empty());
    BOOST_CHECK(a.structural_elements().builtins().size() == 1);

    BOOST_REQUIRE(a.structural_elements().objects().size() == 1);
    const auto& o(*(a.structural_elements().objects().begin()->second));
    BOOST_CHECK(o.local_attributes().size() == 1);
    BOOST_CHECK(o.inherited_attributes().empty());
    BOOST_CHECK(o.all_attributes().empty());
    BOOST_CHECK(o.object_templates().empty());

    object_templates_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_object_template_is_untouched_by_object_templates_transform) {
    SETUP_TEST_LOG_SOURCE("model_with_single_object_template_is_untouched_by_object_templates_transform");

    auto a(factory.make_single_object_template_model());
    const auto e(factory.make_single_object_template_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;
    BOOST_REQUIRE(a.structural_elements().objects().size() == 1);

    const auto& o(*(a.structural_elements().objects().begin()->second));
    BOOST_CHECK(o.object_templates().size() == 1);

    BOOST_REQUIRE(a.structural_elements().object_templates().size() == 1);
    const auto& c(*(a.structural_elements().object_templates().begin()->second));
    BOOST_CHECK(c.parents().empty());

    object_templates_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_one_level_of_object_template_inheritance_results_in_expected_instantiation) {
    SETUP_TEST_LOG_SOURCE("model_with_one_level_of_object_template_inheritance_results_in_expected_instantiation");

    auto m(factory.make_first_degree_object_templates_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;
    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.object_templates().size() == 1);
            BOOST_CHECK(factory.is_object_template_name_n(0,
                    o.object_templates().front()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.object_templates().size() == 1);
            BOOST_CHECK(factory.is_object_template_name_n(1,
                    o.object_templates().front()));
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());

        BOOST_CHECK(o.parents().empty());
    }

    BOOST_REQUIRE(m.structural_elements().object_templates().size() == 2);
    for (const auto& pair : m.structural_elements().object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_object_template_name_n(0, n))
            BOOST_CHECK(c.parents().empty());
        else if (factory.is_object_template_name_n(1, n)) {
            BOOST_REQUIRE(c.parents().size() == 1);
            BOOST_CHECK(factory.is_object_template_name_n(0, c.parents().front()));
        } else
            BOOST_FAIL("Unexpected object template: " << n.qualified().dot());
    }

    object_templates_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    for (const auto& pair : m.structural_elements().object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_object_template_name_n(0, n)) {
            BOOST_CHECK(c.parents().empty());
        } else if (factory.is_object_template_name_n(1, n)) {
            BOOST_CHECK(c.parents().size() == 1);
        } else
            BOOST_FAIL("Unexpected object template: " << n.qualified().dot());
    }

    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n))
            BOOST_CHECK(o.object_templates().size() == 1);
        else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.object_templates().size() == 2);
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }
}

BOOST_AUTO_TEST_CASE(model_with_two_levels_of_object_template_inheritance_results_in_expected_instantiation) {
    SETUP_TEST_LOG_SOURCE("model_with_two_levels_of_object_template_inheritance_results_in_expected_instantiation");

    auto m(factory.make_second_degree_object_templates_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;
    BOOST_REQUIRE(m.structural_elements().objects().size() == 3);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.object_templates().size() == 1);
            BOOST_CHECK(factory.is_object_template_name_n(0,
                    o.object_templates().front()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.object_templates().size() == 1);
            BOOST_CHECK(factory.is_object_template_name_n(1,
                    o.object_templates().front()));
        } else if (factory.is_type_name_n(2, n)) {
            BOOST_REQUIRE(o.object_templates().size() == 1);
            BOOST_CHECK(factory.is_object_template_name_n(2,
                    o.object_templates().front()));
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());

        BOOST_CHECK(o.parents().empty());
    }

    BOOST_REQUIRE(m.structural_elements().object_templates().size() == 3);
    for (const auto& pair : m.structural_elements().object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_object_template_name_n(0, n))
            BOOST_CHECK(c.parents().empty());
        else if (factory.is_object_template_name_n(1, n)) {
            BOOST_REQUIRE(c.parents().size() == 1);
            BOOST_CHECK(factory.is_object_template_name_n(0,
                    c.parents().front()));
        } else if (factory.is_object_template_name_n(2, n)) {
            BOOST_REQUIRE(c.parents().size() == 1);
            BOOST_CHECK(factory.is_object_template_name_n(1,
                    c.parents().front()));
        } else
            BOOST_FAIL("Unexpected object template: " << n.qualified().dot());
    }

    object_templates_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    for (const auto& pair : m.structural_elements().object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_object_template_name_n(0, n)) {
            BOOST_CHECK(c.parents().empty());
        } else if (factory.is_object_template_name_n(1, n)) {
            BOOST_CHECK(c.parents().size() == 1);
        } else if (factory.is_object_template_name_n(2, n)) {
            BOOST_CHECK(c.parents().size() == 2);
        } else
            BOOST_FAIL("Unexpected object template: " << n.qualified().dot());
    }

    BOOST_REQUIRE(m.structural_elements().objects().size() == 3);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n))
            BOOST_CHECK(o.object_templates().size() == 1);
        else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.object_templates().size() == 2);
        } else if (factory.is_type_name_n(2, n)) {
            BOOST_CHECK(o.object_templates().size() == 3);
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }
}

BOOST_AUTO_TEST_CASE(model_with_diamond_object_template_inheritance_results_in_expected_instantiation) {
    SETUP_TEST_LOG_SOURCE("model_with_diamond_object_template_inheritance_results_in_expected_instantiation");

    auto m(factory.make_diamond_inheritance_object_templates_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);
    {
        const auto& o(*(m.structural_elements().objects().begin()->second));
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.object_templates().size() == 1);
            BOOST_CHECK(factory.is_object_template_name_n(3,
                    o.object_templates().front()));

            BOOST_CHECK(o.parents().empty());
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }

    BOOST_REQUIRE(m.structural_elements().object_templates().size() == 4);
    for (const auto& pair : m.structural_elements().object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_object_template_name_n(0, c.name()))
            BOOST_REQUIRE(c.parents().empty());
        else if (factory.is_object_template_name_n(1, c.name())) {
            BOOST_REQUIRE(c.parents().size() == 1);
            BOOST_REQUIRE(
                factory.is_object_template_name_n(0, c.parents().front()));
        } else if (factory.is_object_template_name_n(2, c.name())) {
            BOOST_REQUIRE(c.parents().size() == 1);
            BOOST_REQUIRE(
                factory.is_object_template_name_n(0, c.parents().front()));
        } else if (factory.is_object_template_name_n(3, c.name())) {
            BOOST_REQUIRE(c.parents().size() == 2);
            BOOST_REQUIRE(
                factory.is_object_template_name_n(1, c.parents().front()) ||
                factory.is_object_template_name_n(2, c.parents().front()));
            BOOST_REQUIRE(
                factory.is_object_template_name_n(1, c.parents().back()) ||
                factory.is_object_template_name_n(2, c.parents().back()));
        } else
            BOOST_FAIL("Unexpected object template: " << n.qualified().dot());
    }

    object_templates_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;
    BOOST_CHECK(m.structural_elements().object_templates().size() == 4);
    for (const auto& pair : m.structural_elements().object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_object_template_name_n(0, c.name())) {
            BOOST_CHECK(c.parents().empty());
        } else if (factory.is_object_template_name_n(1, c.name())) {
            BOOST_CHECK(c.parents().size() == 1);
            BOOST_REQUIRE(
                factory.is_object_template_name_n(0, c.parents().front()));
        } else if (factory.is_object_template_name_n(2, c.name())) {
            BOOST_CHECK(c.parents().size() == 1);
            BOOST_REQUIRE(
                factory.is_object_template_name_n(0, c.parents().front()));
        } else if (factory.is_object_template_name_n(3, c.name())) {
            BOOST_CHECK(c.parents().size() == 3);
            bool found_zero(false), found_one(false), found_two(false);
            for (const auto& n : c.parents()) {
                found_zero = found_zero ||
                    factory.is_object_template_name_n(0, n);
                found_one = found_one ||
                    factory.is_object_template_name_n(1, n);
                found_two = found_two ||
                    factory.is_object_template_name_n(2, n);
            }
            BOOST_CHECK(found_zero);
            BOOST_CHECK(found_one);
            BOOST_CHECK(found_two);
        } else
            BOOST_FAIL("Unexpected object template: " << n.qualified().dot());
    }

    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);
    {
        const auto& o(*(m.structural_elements().objects().begin()->second));
        const auto& n(o.name());
        BOOST_CHECK(factory.is_type_name_n(0, n));
        BOOST_CHECK(o.object_templates().size() == 4);
    }
}

BOOST_AUTO_TEST_CASE(model_with_single_parent_that_does_not_model_object_templates_is_untouched_by_object_templates_transform) {
    SETUP_TEST_LOG_SOURCE("model_with_single_parent_that_does_not_model_object_templates_is_untouched_by_object_templates_transform");

    auto a(factory.object_with_parent_in_the_same_model());
    const auto e(factory.object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    BOOST_REQUIRE(a.structural_elements().objects().size() == 2);
    BOOST_REQUIRE(a.structural_elements().object_templates().empty());

    object_templates_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_third_degree_inheritance_that_does_not_model_object_templates_is_untouched_by_object_templates_transform) {
    SETUP_TEST_LOG_SOURCE("model_with_third_degree_inheritance_that_does_not_model_object_templates_is_untouched_by_object_templates_transform");

    auto a(factory.object_with_third_degree_parent_in_same_model());
    const auto e(factory.object_with_third_degree_parent_in_same_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    BOOST_REQUIRE(a.structural_elements().objects().size() == 4);
    BOOST_REQUIRE(a.structural_elements().object_templates().empty());

    object_templates_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_containing_object_with_parent_that_models_object_template_is_untouched_by_object_templates_transform) {
    SETUP_TEST_LOG_SOURCE("model_containing_object_with_parent_that_models_object_template_is_untouched_by_object_templates_transform");

    auto& f(factory);
    auto a(f.make_object_with_parent_that_instantiates_object_template());
    const auto e(f.make_object_with_parent_that_instantiates_object_template());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    BOOST_REQUIRE(a.structural_elements().object_templates().size() == 1);
    for (const auto& pair : a.structural_elements().object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (f.is_object_template_name_n(0, n))
            BOOST_REQUIRE(c.parents().empty());
        else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }

    BOOST_CHECK(a.structural_elements().objects().size() == 2);
    for (const auto& pair : a.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (f.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.object_templates().size() == 1);
            BOOST_REQUIRE(f.is_object_template_name_n(0,
                    o.object_templates().front()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.object_templates().empty());
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_REQUIRE(f.is_type_name_n(0, pn));
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }

    object_templates_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_containing_object_with_parent_that_models_a_refined_object_template_results_in_expected_instantiation) {
    SETUP_TEST_LOG_SOURCE("model_with_containing_object_with_parent_that_models_a_refined_object_template_results_in_expected_instantiation");

    auto m(factory.make_object_with_parent_that_instantiates_a_child_object_template());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    BOOST_REQUIRE(m.structural_elements().object_templates().size() == 2);
    for (const auto& pair : m.structural_elements().object_templates()) {
        const auto& otp(*pair.second);
        const auto& n(otp.name());

        if (factory.is_object_template_name_n(0, n))
            BOOST_REQUIRE(otp.parents().empty());
        else if (factory.is_object_template_name_n(1, n)) {
            BOOST_REQUIRE(otp.parents().size() == 1);
            BOOST_REQUIRE(factory.is_object_template_name_n(0,
                    otp.parents().front()));
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }

    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.object_templates().size() == 1);
            BOOST_REQUIRE(factory.is_object_template_name_n(1,
                    o.object_templates().front()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.object_templates().empty());
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_REQUIRE(factory.is_type_name_n(0, pn));
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }

    object_templates_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_CHECK(m.structural_elements().object_templates().size() == 2);
    for (const auto& pair : m.structural_elements().object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_object_template_name_n(0, n)) {
            BOOST_CHECK(c.parents().empty());
        } else if (factory.is_object_template_name_n(1, n)) {
            BOOST_CHECK(c.parents().size() == 1);
            BOOST_REQUIRE(factory.is_object_template_name_n(
                    0, c.parents().front()));
        } else
            BOOST_FAIL("Unexpected object template: " << n.qualified().dot());
    }

    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        const auto& mc(o.object_templates());
        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(mc.size() == 2);
            BOOST_REQUIRE(
                factory.is_object_template_name_n(0, mc.front()) ||
                factory.is_object_template_name_n(1, mc.front()));
            BOOST_REQUIRE(
                factory.is_object_template_name_n(0, mc.back()) ||
                factory.is_object_template_name_n(1, mc.back()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(mc.empty());
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_REQUIRE(factory.is_type_name_n(0, pn));
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }
}

BOOST_AUTO_TEST_CASE(model_with_object_template_that_parents_missing_object_template_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_template_that_parents_missing_object_template_throws");

    auto m(factory.make_object_template_that_inherits_missing_object_template());
    BOOST_REQUIRE(m.structural_elements().objects().empty());
    BOOST_REQUIRE(m.structural_elements().object_templates().size() == 1);
    {
        const auto& otp(*(m.structural_elements().object_templates().begin()->second));
        const auto& n(otp.name());

        if (factory.is_object_template_name_n(1, otp.name())) {
            BOOST_REQUIRE(otp.parents().size() == 1);
            BOOST_REQUIRE(factory.is_object_template_name_n(0,
                    otp.parents().front()));
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }

    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    contains_checker<transformation_error> c(object_template_not_found);
    const auto ctx(mock_context_factory::make());
    BOOST_CHECK_EXCEPTION(object_templates_transform::apply(ctx, m),
        transformation_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_that_models_missing_object_template_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_that_models_missing_object_template_throws");

    auto m(factory.make_object_that_instantiates_missing_object_template());
    BOOST_REQUIRE(m.structural_elements().object_templates().empty());
    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);
    {
        const auto& n(m.structural_elements().objects().begin()->second->name());
        if (!factory.is_type_name_n(0, n))
            BOOST_FAIL("Unexpected object: " << n);

        const auto& o(*(m.structural_elements().objects().begin()->second));
        BOOST_REQUIRE(o.object_templates().size() == 1);
        BOOST_REQUIRE(factory.is_object_template_name_n(0,
                o.object_templates().front()));
    }

    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    contains_checker<transformation_error> c(object_template_not_found);
    const auto ctx(mock_context_factory::make());
    BOOST_CHECK_EXCEPTION(
        object_templates_transform::apply(ctx, m), transformation_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_with_missing_parent_throws) {
    SETUP_TEST_LOG_SOURCE("model_object_that_models_object_template_with_missing_parent");

    auto m(factory.make_object_that_instantiates_object_template_with_missing_parent());
    BOOST_REQUIRE(m.structural_elements().object_templates().size() == 1);
    {
        const auto& n(m.structural_elements().object_templates().begin()->first);
        const auto& c(*(m.structural_elements().object_templates().begin()->second));

        if (factory.is_object_template_name_n(0, c.name()))
            BOOST_REQUIRE(c.parents().empty());
        else
            BOOST_FAIL("Unexpected object: " << n);
    }

    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);
    {
        const auto& o(*(m.structural_elements().objects().begin()->second));
        const auto& n(o.name());

        const auto& mc(o.object_templates());
        if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(mc.size() == 1);
            BOOST_REQUIRE(factory.is_object_template_name_n(0, mc.front()));

            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_REQUIRE(factory.is_type_name_n(0, pn));
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }

    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    contains_checker<transformation_error> c(object_not_found);
    const auto ctx(mock_context_factory::make());
    BOOST_CHECK_EXCEPTION(
        object_templates_transform::apply(ctx, m), transformation_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
