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
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/io/entities/structural/object_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/test/mock_context_factory.hpp"
#include "dogen.logical/test/mock_model_factory.hpp"
#include "dogen.logical/types/transforms/associations_transform.hpp"

namespace {

const std::string test_module("dogen.logical.tests");
const std::string test_suite("associations_transform_tests");
const std::string object_not_found("Object not found in");

using dogen::logical::test::mock_model_factory;

/* @note tagging should make no difference to tests, and not having tags
 * makes the model dumps easier to understand.
 *
 * However, strictly speaking, tagging happens before transform so it
 * would be more truthful to use a tagged model in the tests.
 */
const mock_model_factory::flags flags(
    false/*tagged*/, false/*merged*/, false/*resolved*/,
    true/*object_templates_indexed*/, true/*attributes_indexed*/,
    false/*associations_indexed*/, true/*types parsed*/);
const mock_model_factory factory(flags);

}

using dogen::utility::test::asserter;
using dogen::identification::entities::model_type;
using dogen::logical::transforms::associations_transform;
using object_types =
    dogen::logical::test::mock_model_factory::object_types;
using attribute_types =
    dogen::logical::test::mock_model_factory::attribute_types;
using dogen::logical::test::mock_context_factory;

BOOST_AUTO_TEST_SUITE(associations_transform_tests)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_associations_transform) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_associations_transform");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_REQUIRE(a.structural_elements().objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    associations_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_attributes_is_untouched_by_associations_transform) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_attributes_is_untouched_by_associations_transform");

    auto a(factory.make_single_type_model());
    const auto e(factory.make_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;
    BOOST_REQUIRE(a.structural_elements().objects().size() == 1);

    associations_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_attribute_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_attribute_results_in_expected_associations");

    auto m(factory.object_with_attribute(
            model_type::target,
            object_types::value_object,
            attribute_types::unsigned_int));
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);

    const auto& o(*m.structural_elements().objects().begin()->second);
    BOOST_CHECK(o.transparent_associations().size() == 1);
    BOOST_CHECK(o.opaque_associations().empty());
}

BOOST_AUTO_TEST_CASE(model_with_single_object_templates_is_untouched_by_associations_transform) {
    SETUP_TEST_LOG_SOURCE("model_with_single_object_templates_is_untouched_by_associations_transform");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_REQUIRE(a.structural_elements().objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    associations_transform::apply(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_more_than_one_attribute_of_the_same_type_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("model_with_more_than_one_attribute_of_the_same_type_results_in_expected_associations");

    auto m(factory.make_first_degree_object_templates_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n) || factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.transparent_associations().size() == 1);
            BOOST_CHECK(o.opaque_associations().empty());
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }
}

BOOST_AUTO_TEST_CASE(model_with_object_with_multiple_attributes_of_different_types_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("model_with_object_with_multiple_attributes_of_different_types_results_in_expected_associations");

    auto m(factory.object_with_group_of_attributes_of_different_types());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    bool found0(false), found1(false), found3(false);
    BOOST_REQUIRE(m.structural_elements().objects().size() == 5);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
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

BOOST_AUTO_TEST_CASE(model_with_object_with_multiple_attributes_of_different_types_that_are_repeated_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("model_with_object_with_multiple_attributes_of_different_types_that_are_repeated_results_in_expected_associations");

    auto m(factory.object_with_group_of_attributes_of_different_types(
            model_type::target, true/*repeat_group*/));
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    bool found0(false), found1(false), found3(false);
    BOOST_REQUIRE(m.structural_elements().objects().size() == 5);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
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

BOOST_AUTO_TEST_CASE(object_with_unsigned_int_attribute_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("object_with_unsigned_int_attribute_results_in_expected_associations");

    const auto mt(model_type::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::unsigned_int);
    auto m(factory.object_with_attribute(mt, objt, pt));
    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);
    BOOST_REQUIRE(m.structural_elements().objects().
        begin()->second->local_attributes().size() == 1);
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.transparent_associations().size() == 1);
            const auto sn(o.transparent_associations().begin()->simple());
            BOOST_CHECK(sn == "unsigned int");
            BOOST_CHECK(o.opaque_associations().empty());
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }
}

BOOST_AUTO_TEST_CASE(object_with_bool_attribute_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("object_with_bool_attribute_results_in_expected_associations");

    const auto mt(model_type::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::boolean);
    auto m(factory.object_with_attribute(mt, objt, pt));
    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);
    BOOST_REQUIRE(m.structural_elements().objects().
        begin()->second->local_attributes().size() == 1);
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_REQUIRE(o.transparent_associations().size() == 1);
            const auto sn(o.transparent_associations().begin()->simple());
            BOOST_CHECK(sn == "bool");
            BOOST_CHECK(o.opaque_associations().empty());
        } else
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }
}

BOOST_AUTO_TEST_CASE(object_with_object_attribute_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("object_with_object_attribute_results_in_expected_associations");

    const auto ot(model_type::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::value_object);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);

    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
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
            BOOST_FAIL("Unexpected object: " << n.qualified().dot());
    }
}

BOOST_AUTO_TEST_CASE(object_with_std_pair_attribute_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("object_with_std_pair_attribute_results_in_expected_associations");

    const auto ot(model_type::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::std_pair);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;

    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    bool found(false);
    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
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

BOOST_AUTO_TEST_CASE(object_with_boost_variant_attribute_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("object_with_boost_variant_attribute_results_in_expected_associations");

    const auto ot(model_type::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::boost_variant);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);
    BOOST_REQUIRE(m.structural_elements().builtins().size() == 2);

    bool found(false);
    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();

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

BOOST_AUTO_TEST_CASE(object_with_std_string_attribute_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("object_with_std_string_attribute_results_in_expected_associations");

    const auto ot(model_type::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::std_string);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;

    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    bool found(false);
    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
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

BOOST_AUTO_TEST_CASE(object_with_boost_shared_ptr_attribute_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("object_with_boost_shared_ptr_attribute_results_in_expected_associations");

    const auto ot(model_type::target);
    const auto objt(object_types::value_object);
    const auto pt(attribute_types::boost_shared_ptr);
    auto m(factory.object_with_attribute(ot, objt, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.structural_elements().objects().size() == 3);

    bool found(false);
    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();

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

BOOST_AUTO_TEST_CASE(object_with_both_regular_and_opaque_associations_results_in_expected_associations) {
    SETUP_TEST_LOG_SOURCE("object_with_both_regular_and_opaque_associations_results_in_expected_associations");

    auto m(factory.object_with_both_transparent_and_opaque_associations());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.structural_elements().objects().size() == 5);

    bool found(false);
    associations_transform::apply(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    for (const auto& pair : m.structural_elements().objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            found = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();

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
