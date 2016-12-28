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
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/io/object_io.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/test/mock_intermediate_model_factory.hpp"
#include "dogen/yarn/types/concept_expander.hpp"

namespace {

const std::string test_module("yarn");
const std::string test_suite("concept_expander_tests");

const std::string concept_not_found("Concept not found");
const std::string object_not_found("Object not found in model");

using dogen::yarn::test::mock_intermediate_model_factory;

/* @note tagging should make no difference to tests, and not having tags
 * makes the model dumps easier to understand.
 *
 * However, strictly speaking, tagging happens before expansion so it
 * would be more truthful to use a tagged model in the tests.
 */
const mock_intermediate_model_factory::flags flags(false/*tagged*/,
    false/*resolved*/, false/*merged*/, false/*concepts_indexed*/,
    false/*attributes_indexed*/);

const mock_intermediate_model_factory factory(flags);

}

using dogen::utility::test::contains_checker;
using dogen::yarn::expansion_error;
using dogen::utility::test::asserter;
using origin_types = dogen::yarn::origin_types;
using object_types = dogen::yarn::test::mock_intermediate_model_factory::
    object_types;
using attribute_types = dogen::yarn::test::mock_intermediate_model_factory::
    attribute_types;

BOOST_AUTO_TEST_SUITE(concept_expander_tests)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_concept_expander) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_concept_expander");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_CHECK(a.objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;

    dogen::yarn::concept_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_attributes_is_untouched_by_concept_expander) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_attributes_is_untouched_by_concept_expander");

    auto a(factory.make_single_type_model());
    const auto e(factory.make_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;
    BOOST_CHECK(a.objects().size() == 1);

    dogen::yarn::concept_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_attribute_is_untouched_by_concept_expander) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_attribute_is_untouched_by_concept_expander");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::unsigned_int);
    auto a(factory.object_with_attribute(ot, objt, pt));
    const auto e(factory.object_with_attribute(ot, objt, pt));

    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;

    BOOST_CHECK(a.concepts().empty());
    BOOST_CHECK(a.enumerations().empty());
    BOOST_CHECK(a.primitives().size() == 1);

    BOOST_REQUIRE(a.objects().size() == 1);
    const auto& o(a.objects().begin()->second);
    BOOST_CHECK(o.local_attributes().size() == 1);
    BOOST_CHECK(o.inherited_attributes().empty());
    BOOST_CHECK(o.all_attributes().empty());
    BOOST_CHECK(o.modeled_concepts().empty());

    dogen::yarn::concept_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_concept_is_untouched_by_concept_expander) {
    SETUP_TEST_LOG_SOURCE("model_with_single_concept_is_untouched_by_concept_expander");

    auto a(factory.make_single_concept_model());
    const auto e(factory.make_single_concept_model());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;
    BOOST_REQUIRE(a.objects().size() == 1);

    const auto& o(a.objects().begin()->second);
    BOOST_CHECK(o.modeled_concepts().size() == 1);

    BOOST_REQUIRE(a.concepts().size() == 1);
    const auto& c(a.concepts().begin()->second);
    BOOST_CHECK(c.refines().empty());

    dogen::yarn::concept_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_one_level_of_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_one_level_of_concept_inheritance_results_in_expected_indices");

    auto m(factory.make_first_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
            BOOST_CHECK(factory.is_concept_name_n(0,
                    o.modeled_concepts().front()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
            BOOST_CHECK(factory.is_concept_name_n(1,
                    o.modeled_concepts().front()));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());

        BOOST_CHECK(o.parents().empty());
    }

    BOOST_REQUIRE(m.concepts().size() == 2);
    for (const auto& pair : m.concepts()) {
        const auto& c(pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n))
            BOOST_CHECK(c.refines().empty());
        else if (factory.is_concept_name_n(1, n)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_CHECK(factory.is_concept_name_n(0, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    dogen::yarn::concept_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    for (const auto& pair : m.concepts()) {
        const auto& c(pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n)) {
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, n)) {
            BOOST_CHECK(c.refines().size() == 1);
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n))
            BOOST_CHECK(o.modeled_concepts().size() == 1);
        else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.modeled_concepts().size() == 2);
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_two_levels_of_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_two_levels_of_concept_inheritance_results_in_expected_indices");

    auto m(factory.make_second_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;
    BOOST_REQUIRE(m.objects().size() == 3);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
            BOOST_CHECK(factory.is_concept_name_n(0,
                    o.modeled_concepts().front()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
            BOOST_CHECK(factory.is_concept_name_n(1,
                    o.modeled_concepts().front()));
        } else if (factory.is_type_name_n(2, n)) {
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
            BOOST_CHECK(factory.is_concept_name_n(2,
                    o.modeled_concepts().front()));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());

        BOOST_CHECK(o.parents().empty());
    }

    BOOST_REQUIRE(m.concepts().size() == 3);
    for (const auto& pair : m.concepts()) {
        const auto& c(pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n))
            BOOST_CHECK(c.refines().empty());
        else if (factory.is_concept_name_n(1, n)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_CHECK(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(2, n)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_CHECK(factory.is_concept_name_n(1, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    dogen::yarn::concept_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    for (const auto& pair : m.concepts()) {
        const auto& c(pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n)) {
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, n)) {
            BOOST_CHECK(c.refines().size() == 1);
        } else if (factory.is_concept_name_n(2, n)) {
            BOOST_CHECK(c.refines().size() == 2);
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 3);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n))
            BOOST_CHECK(o.modeled_concepts().size() == 1);
        else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.modeled_concepts().size() == 2);
        } else if (factory.is_type_name_n(2, n)) {
            BOOST_CHECK(o.modeled_concepts().size() == 3);
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_diamond_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_diamond_concept_inheritance_results_in_expected_indices");

    auto m(factory.make_diamond_inheritance_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& o(m.objects().begin()->second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
            BOOST_CHECK(factory.is_concept_name_n(3,
                    o.modeled_concepts().front()));

            BOOST_CHECK(o.parents().empty());
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }

    BOOST_REQUIRE(m.concepts().size() == 4);
    for (const auto& pair : m.concepts()) {
        const auto& c(pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, c.name()))
            BOOST_REQUIRE(c.refines().empty());
        else if (factory.is_concept_name_n(1, c.name())) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(2, c.name())) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(3, c.name())) {
            BOOST_REQUIRE(c.refines().size() == 2);
            BOOST_REQUIRE(
                factory.is_concept_name_n(1, c.refines().front()) ||
                factory.is_concept_name_n(2, c.refines().front()));
            BOOST_REQUIRE(
                factory.is_concept_name_n(1, c.refines().back()) ||
                factory.is_concept_name_n(2, c.refines().back()));
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    dogen::yarn::concept_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;
    BOOST_CHECK(m.concepts().size() == 4);
    for (const auto& pair : m.concepts()) {
        const auto& c(pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, c.name())) {
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, c.name())) {
            BOOST_CHECK(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(2, c.name())) {
            BOOST_CHECK(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(3, c.name())) {
            BOOST_CHECK(c.refines().size() == 3);
            bool found_zero(false), found_one(false), found_two(false);
            for (const auto& n : c.refines()) {
                found_zero = found_zero || factory.is_concept_name_n(0, n);
                found_one = found_one || factory.is_concept_name_n(1, n);
                found_two = found_two || factory.is_concept_name_n(2, n);
            }
            BOOST_CHECK(found_zero);
            BOOST_CHECK(found_one);
            BOOST_CHECK(found_two);
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& o(m.objects().begin()->second);
        const auto& n(o.name());
        BOOST_CHECK(factory.is_type_name_n(0, n));
        BOOST_CHECK(o.modeled_concepts().size() == 4);
    }
}

BOOST_AUTO_TEST_CASE(model_with_single_parent_that_does_not_model_concepts_is_untouched_by_concept_expander) {
    SETUP_TEST_LOG_SOURCE("model_with_single_parent_that_does_not_model_concepts_is_untouched_by_concept_expander");

    auto a(factory.object_with_parent_in_the_same_model());
    const auto e(factory.object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;

    BOOST_REQUIRE(a.objects().size() == 2);
    BOOST_REQUIRE(a.concepts().empty());

    dogen::yarn::concept_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_third_degree_inheritance_that_does_not_model_concepts_is_untouched_by_concept_expander) {
    SETUP_TEST_LOG_SOURCE("model_with_third_degree_inheritance_that_does_not_model_concepts_is_untouched_by_concept_expander");

    auto a(factory.object_with_third_degree_parent_in_same_model());
    const auto e(factory.object_with_third_degree_parent_in_same_model());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;

    BOOST_REQUIRE(a.objects().size() == 4);
    BOOST_REQUIRE(a.concepts().empty());

    dogen::yarn::concept_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_containing_object_with_parent_that_models_concept_is_untouched_by_concept_expander) {
    SETUP_TEST_LOG_SOURCE("model_containing_object_with_parent_that_models_concept_is_untouched_by_concept_expander");

    auto a(factory.make_object_with_parent_that_models_concept());
    const auto e(factory.make_object_with_parent_that_models_concept());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;

    BOOST_REQUIRE(a.concepts().size() == 1);
    for (const auto& pair : a.concepts()) {
        const auto& c(pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n))
            BOOST_REQUIRE(c.refines().empty());
        else
            BOOST_FAIL("Unexpected object: " << n.id());
    }

    BOOST_CHECK(a.objects().size() == 2);
    for (const auto& pair : a.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0,
                    o.modeled_concepts().front()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.modeled_concepts().empty());
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_REQUIRE(factory.is_type_name_n(0, pn));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }

    dogen::yarn::concept_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_containing_object_with_parent_that_models_a_refined_concept_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_containing_object_with_parent_that_models_a_refined_concept_results_in_expected_indices");

    auto m(factory.make_object_with_parent_that_models_a_refined_concept());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    BOOST_REQUIRE(m.concepts().size() == 2);
    for (const auto& pair : m.concepts()) {
        const auto& c(pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n))
            BOOST_REQUIRE(c.refines().empty());
        else if (factory.is_concept_name_n(1, n)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(1,
                    o.modeled_concepts().front()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.modeled_concepts().empty());
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_REQUIRE(factory.is_type_name_n(0, pn));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }

    dogen::yarn::concept_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    BOOST_CHECK(m.concepts().size() == 2);
    for (const auto& pair : m.concepts()) {
        const auto& c(pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n)) {
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, n)) {
            BOOST_CHECK(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        const auto& mc(o.modeled_concepts());
        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(mc.size() == 2);
            BOOST_REQUIRE(
                factory.is_concept_name_n(0, mc.front()) ||
                factory.is_concept_name_n(1, mc.front()));
            BOOST_REQUIRE(
                factory.is_concept_name_n(0, mc.back()) ||
                factory.is_concept_name_n(1, mc.back()));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(mc.empty());
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_REQUIRE(factory.is_type_name_n(0, pn));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_concept_that_refines_missing_concept_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_concept_that_refines_missing_concept_throws");

    auto m(factory.make_concept_that_refines_missing_concept());
    BOOST_REQUIRE(m.objects().empty());
    BOOST_REQUIRE(m.concepts().size() == 1);
    {
        const auto& c(m.concepts().begin()->second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(1, c.name())) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }

    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    dogen::yarn::concept_expander ex;
    contains_checker<expansion_error> c(concept_not_found);
    BOOST_CHECK_EXCEPTION(ex.expand(m), expansion_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_that_models_missing_concept_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_that_models_missing_concept_throws");

    auto m(factory.make_object_that_models_missing_concept());
    BOOST_REQUIRE(m.concepts().empty());
    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& n(m.objects().begin()->second.name());
        if (!factory.is_type_name_n(0, n))
            BOOST_FAIL("Unexpected object: " << n);

        const auto& o(m.objects().begin()->second);
        BOOST_REQUIRE(o.modeled_concepts().size() == 1);
        BOOST_REQUIRE(factory.is_concept_name_n(0,
                o.modeled_concepts().front()));
    }

    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    dogen::yarn::concept_expander ex;
    using dogen::yarn::expansion_error;
    contains_checker<expansion_error> c(concept_not_found);
    BOOST_CHECK_EXCEPTION(ex.expand(m), expansion_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_with_missing_parent_throws) {
    SETUP_TEST_LOG_SOURCE("model_object_that_models_concept_with_missing_parent");

    auto m(factory.make_object_that_models_concept_with_missing_parent());
    BOOST_REQUIRE(m.concepts().size() == 1);
    {
        const auto& n(m.concepts().begin()->first);
        const auto& c(m.concepts().begin()->second);

        if (factory.is_concept_name_n(0, c.name()))
            BOOST_REQUIRE(c.refines().empty());
        else
            BOOST_FAIL("Unexpected object: " << n);
    }

    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& o(m.objects().begin()->second);
        const auto& n(o.name());

        const auto& mc(o.modeled_concepts());
        if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(mc.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, mc.front()));

            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_REQUIRE(factory.is_type_name_n(0, pn));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }

    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    dogen::yarn::concept_expander ex;
    using dogen::yarn::expansion_error;
    contains_checker<expansion_error> c(object_not_found);
    BOOST_CHECK_EXCEPTION(ex.expand(m), expansion_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
