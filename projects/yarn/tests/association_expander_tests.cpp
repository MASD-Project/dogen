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
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/io/object_io.hpp"
#include "dogen/yarn/test/mock_intermediate_model_factory.hpp"
#include "dogen/yarn/types/association_expander.hpp"

namespace {

const std::string test_module("yarn");
const std::string test_suite("association_expander_tests");
const std::string object_not_found("Object not found in");

using dogen::yarn::test::mock_intermediate_model_factory;

/* @note tagging should make no difference to tests, and not having tags
 * makes the model dumps easier to understand.
 *
 * However, strictly speaking, tagging happens before expansion so it
 * would be more truthful to use a tagged model in the tests.
 */
const mock_intermediate_model_factory::flags flags(
    false/*tagged*/, false/*merged*/, false/*resolved*/,
    true/*concepts_indexed*/, true/*attributes_indexed*/,
    false/*associations_indexed*/, true/*types parsed*/);
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

BOOST_AUTO_TEST_SUITE(association_expander_tests)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_association_expander) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_association_expander");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_REQUIRE(a.objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;

    dogen::yarn::association_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_attributes_is_untouched_by_association_expander) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_attributes_is_untouched_by_association_expander");

    auto a(factory.make_single_type_model());
    const auto e(factory.make_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;
    BOOST_REQUIRE(a.objects().size() == 1);

    dogen::yarn::association_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_attribute_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_attribute_results_in_expected_indices");

    auto m(factory.object_with_attribute(
            origin_types::target,
            object_types::value_object,
            attribute_types::unsigned_int));
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);

    const auto& o(m.objects().begin()->second);
    BOOST_CHECK(o.transparent_associations().size() == 1);
    BOOST_CHECK(o.opaque_associations().empty());
}

BOOST_AUTO_TEST_CASE(model_with_single_concept_is_untouched_by_association_expander) {
    SETUP_TEST_LOG_SOURCE("model_with_single_concept_is_untouched_by_association_expander");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_REQUIRE(a.objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << a;

    dogen::yarn::association_expander ex;
    ex.expand(a);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_more_than_one_attribute_of_the_same_type_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_more_than_one_attribute_of_the_same_type_results_in_expected_indices");

    auto m(factory.make_first_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n) || factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.transparent_associations().size() == 1);
            BOOST_CHECK(o.opaque_associations().empty());
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_object_with_multiple_attributes_of_different_types_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_object_with_multiple_attributes_of_different_types_results_in_expected_indices");

    auto m(factory.object_with_group_of_attributes_of_different_types());
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    bool found0(false), found1(false), found3(false);
    BOOST_REQUIRE(m.objects().size() == 5);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found0 = true;
            BOOST_CHECK(o.transparent_associations().size() == 4);

            std::vector<bool> found;
            found.resize(4);
            for (const auto& n : o.transparent_associations()) {
                if (n.simple() == "shared_ptr")
                    found[0] = true;

                if (n.simple() == "unsigned int")
                    found[1] = true;

                if (factory.is_type_name_n(1, n.simple()))
                    found[2] = true;

                if (factory.is_type_name_n(4, n.simple()))
                    found[3] = true;
            }

            for (const auto b : found)
                BOOST_CHECK(b);

            BOOST_REQUIRE(o.opaque_associations().size() == 1);
            const auto sn(o.opaque_associations().front().simple());
            BOOST_CHECK(factory.is_type_name_n(3, sn));
        } else if (factory.is_type_name_n(1, n)) {
            found1 = true;
            BOOST_CHECK(o.transparent_associations().empty());
            BOOST_CHECK(o.opaque_associations().empty());
        } else if (factory.is_type_name_n(3, n)) {
            found3 = true;
            BOOST_CHECK(o.transparent_associations().empty());
            BOOST_CHECK(o.opaque_associations().empty());
        }
        // ignore boost shared ptr, pair, etc
    }

    BOOST_CHECK(found0);
    BOOST_CHECK(found1);
    BOOST_CHECK(found3);
}

BOOST_AUTO_TEST_CASE(model_with_object_with_multiple_attributes_of_different_types_that_are_repeated_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_object_with_multiple_attributes_of_different_types_that_are_repeated_results_in_expected_indices");

    auto m(factory.object_with_group_of_attributes_of_different_types(
            origin_types::target, true/*repeat_group*/));
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    bool found0(false), found1(false), found3(false);
    BOOST_REQUIRE(m.objects().size() == 5);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found0 = true;
            BOOST_CHECK(o.transparent_associations().size() == 4);
            std::vector<bool> found;
            found.resize(4);
            for (const auto& n : o.transparent_associations()) {
                if (n.simple() == "shared_ptr")
                    found[0] = true;

                if (n.simple() == "unsigned int")
                    found[1] = true;

                if (factory.is_type_name_n(1, n.simple()))
                    found[2] = true;

                if (factory.is_type_name_n(4, n.simple()))
                    found[3] = true;
            }

            for (const auto b : found)
                BOOST_CHECK(b);

            BOOST_REQUIRE(o.opaque_associations().size() == 1);
            const auto sn(o.opaque_associations().front().simple());
            BOOST_CHECK(factory.is_type_name_n(3, sn));
        } else if (factory.is_type_name_n(1, n)) {
            found1 = true;
            BOOST_CHECK(o.transparent_associations().empty());
            BOOST_CHECK(o.opaque_associations().empty());
        } else if (factory.is_type_name_n(3, n)) {
            found3 = true;
            BOOST_CHECK(o.transparent_associations().empty());
            BOOST_CHECK(o.opaque_associations().empty());
        }
        // ignore boost shared ptr, pair, etc
    }

    BOOST_CHECK(found0);
    BOOST_CHECK(found1);
    BOOST_CHECK(found3);
}

BOOST_AUTO_TEST_CASE(object_with_unsigned_int_attribute_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_unsigned_int_attribute_results_in_expected_indices");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::unsigned_int);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_REQUIRE(m.objects().size() == 1);
    BOOST_REQUIRE(m.objects().begin()->second.local_attributes().size() == 1);
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.transparent_associations().size() == 1);
            const auto sn(o.transparent_associations().begin()->simple());
            BOOST_CHECK(sn == "unsigned int");
            BOOST_CHECK(o.opaque_associations().empty());
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(object_with_bool_attribute_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_bool_attribute_results_in_expected_indices");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::boolean);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_REQUIRE(m.objects().size() == 1);
    BOOST_REQUIRE(m.objects().begin()->second.local_attributes().size() == 1);
    BOOST_LOG_SEV(lg, debug) << "before expansion: " << m;

    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.transparent_associations().size() == 1);
            const auto sn(o.transparent_associations().begin()->simple());
            BOOST_CHECK(sn == "bool");
            BOOST_CHECK(o.opaque_associations().empty());
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(object_with_object_attribute_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_object_attribute_results_in_expected_indices");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::value_object);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);

    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.transparent_associations().size() == 1);
            const auto sn(o.transparent_associations().begin()->simple());
            BOOST_CHECK(factory.is_type_name_n(1, sn));
            BOOST_CHECK(o.opaque_associations().empty());
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.transparent_associations().empty());
            BOOST_CHECK(o.opaque_associations().empty());
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_object_with_missing_object_attribute_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_with_missing_object_attribute_throws");

    auto m(factory.object_with_missing_attribute_type());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    dogen::yarn::association_expander ex;
    contains_checker<expansion_error> c(object_not_found);
    BOOST_CHECK_EXCEPTION(ex.expand(m), expansion_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_std_pair_attribute_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_std_pair_attribute_results_in_expected_indices");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::std_pair);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;

    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    bool found(false);
    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found = true;
            BOOST_CHECK(o.transparent_associations().size() == 2);
            const auto front_sn(o.transparent_associations().front().simple());
            BOOST_CHECK(front_sn == "bool" || front_sn == "pair");
            const auto back_sn(o.transparent_associations().back().simple());
            BOOST_CHECK(back_sn == "bool" || back_sn == "pair");
            BOOST_CHECK(o.opaque_associations().empty());
        }
        // ignore std pair, etc.
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_boost_variant_attribute_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_boost_variant_attribute_results_in_expected_indices");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::boost_variant);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);
    BOOST_REQUIRE(m.builtins().size() == 2);

    bool found(false);
    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();

            BOOST_REQUIRE(o.transparent_associations().size() == 3);
            bool found_uint(false), found_bool(false), found_variant(false);
            for (const auto& n : o.transparent_associations()) {
                const auto sn(n.simple());
                if (sn == "unsigned int")
                    found_uint = true;
                else if (sn == "bool")
                    found_bool = true;
                else if (sn == "variant")
                    found_variant = true;
            }
            BOOST_CHECK(found_uint);
            BOOST_CHECK(found_bool);
            BOOST_CHECK(found_variant);
            BOOST_CHECK(o.opaque_associations().empty());
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_std_string_attribute_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_std_string_attribute_results_in_expected_indices");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::std_string);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;

    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    bool found(false);
    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found = true;
            BOOST_REQUIRE(o.transparent_associations().size() == 1);
            BOOST_CHECK(o.transparent_associations().front().simple() == "string");
            BOOST_CHECK(o.opaque_associations().empty());
        }
        // ignore std pair, etc.
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_boost_shared_ptr_attribute_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_boost_shared_ptr_attribute_results_in_expected_indices");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::boost_shared_ptr);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 3);

    bool found(false);
    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();

            BOOST_REQUIRE(o.transparent_associations().size() == 1);
            const auto sn(o.transparent_associations().front().simple());
            BOOST_CHECK(sn == "shared_ptr");

            BOOST_REQUIRE(o.opaque_associations().size() == 1);
            BOOST_CHECK(factory.is_type_name_n(1,
                    o.opaque_associations().front().simple()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_both_regular_and_opaque_associations_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_both_regular_and_opaque_associations_results_in_expected_indices");

    auto m(factory.object_with_both_transparent_and_opaque_associations());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 5);

    bool found(false);
    dogen::yarn::association_expander ex;
    ex.expand(m);
    BOOST_LOG_SEV(lg, debug) << "after expansion: " << m;

    for (const auto& pair : m.objects()) {
        const auto& o(pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();

            BOOST_REQUIRE(o.transparent_associations().size() == 3);
            std::vector<bool> found;
            found.resize(3);
            for (const auto& n : o.transparent_associations()) {
                if (n.simple() == "shared_ptr")
                    found[0] = true;

                if (n.simple() == "string")
                    found[1] = true;

                if (factory.is_type_name_n(1, n.simple()))
                    found[2] = true;
            }

            for (const auto b : found)
                BOOST_CHECK(b);

            BOOST_REQUIRE(o.opaque_associations().size() == 1);
            BOOST_CHECK(factory.is_type_name_n(3,
                    o.opaque_associations().front().simple()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_SUITE_END()
