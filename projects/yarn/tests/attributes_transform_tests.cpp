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
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/endomodel.hpp"
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/io/meta_model/object_io.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/test/mock_endomodel_factory.hpp"
#include "dogen/yarn/types/transforms/attributes_transform.hpp"

namespace {

const std::string test_module("yarn");
const std::string test_suite("attributes_transform_tests");

const std::string concept_not_found("Concept not found");
const std::string object_not_found("Object not found in model");

using dogen::yarn::test::mock_endomodel_factory;

/**
 * @brief We require the concepts to have been indexed or else we
 * won't work.
 */
const mock_endomodel_factory::flags
flags(false/*tagged*/, false/*resolved*/, false/*merged*/,
    true/*concepts_indexed*/, false/*attributes_indexed*/,
    true/*types parsed*/);
const mock_endomodel_factory factory(flags);

template<typename Stateful>
bool has_duplicate_attribute_names(const Stateful& s,
    dogen::utility::log::logger& lg) {
    std::unordered_map<std::string, unsigned int> count;

    for (const auto& pair : s.inherited_attributes())
        for (const auto& p : pair.second)
            count[p.name().simple()]++;

    for (const auto& p : s.local_attributes())
        count[p.name().simple()]++;

    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "Inherited/local attributes for "
                             << s.name().id() << ": " << count;

    for (const auto& pair : count)
        if (pair.second > 1)
            return true;

    count.clear();
    for (const auto& p : s.all_attributes())
        count[p.name().simple()]++;

    BOOST_LOG_SEV(lg, debug) << "All attributes for "
                             << s.name().id() << ": " << count;

    for (const auto& pair : count)
        if (pair.second > 1)
            return true;

    return false;
}

}

using dogen::utility::test::contains_checker;
using dogen::yarn::transforms::transformation_error;
using dogen::utility::test::asserter;
using dogen::yarn::transforms::attributes_transform;
using dogen::yarn::meta_model::origin_types;
using object_types = dogen::yarn::test::mock_endomodel_factory::
object_types;
using attribute_types = dogen::yarn::test::mock_endomodel_factory::
attribute_types;

BOOST_AUTO_TEST_SUITE(attributes_transform_tests)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_attributes_transform) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_attributes_transform");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    attributes_transform::transform(a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_attributes_is_untouched_by_attributes_transform) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_attributes_is_untouched_by_attributes_transform");

    auto a(factory.make_single_type_model());
    const auto e(factory.make_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    attributes_transform::transform(a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_attribute_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_attribute_results_in_expected_indices");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto at(attribute_types::unsigned_int);
    auto m(factory.object_with_attribute(ot, objt, at));
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);

    const auto& o(*m.objects().begin()->second);
    BOOST_CHECK(o.local_attributes() == o.all_attributes());
    BOOST_CHECK(o.inherited_attributes().empty());
}

BOOST_AUTO_TEST_CASE(model_with_single_concept_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_single_concept_results_in_expected_indices");

    auto m(factory.make_single_concept_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.concepts().size() == 1);
    const auto& c(*(m.concepts().begin()->second));
    BOOST_CHECK(c.local_attributes().size() == 1);
    BOOST_CHECK(c.inherited_attributes().empty());
    BOOST_CHECK(c.local_attributes() == c.all_attributes());

    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& o(*(m.objects().begin()->second));
    BOOST_CHECK(o.local_attributes().size() == 2);
    BOOST_CHECK(o.inherited_attributes().empty());
    BOOST_CHECK(o.all_attributes().size() == 2);
    // FIXME
    // for (const auto& a : o.all_attributes()) {
    //     BOOST_CHECK(a == *o.local_attributes().begin() ||
    //         a == *c.local_attributes().begin());
    // }
    BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
}

BOOST_AUTO_TEST_CASE(model_with_one_level_of_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_one_level_of_concept_inheritance_results_in_expected_indices");

    auto m(factory.make_first_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    for (const auto& pair : m.concepts()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n)) {
            BOOST_CHECK(c.inherited_attributes().empty());
            BOOST_CHECK(c.all_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes() == c.local_attributes());
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, n)) {
            BOOST_CHECK(c.refines().size() == 1);
            BOOST_REQUIRE(c.inherited_attributes().size() == 1);
            const auto props(c.inherited_attributes().begin()->second);
            BOOST_REQUIRE(props.size() == 1);

            BOOST_CHECK(c.all_attributes().size() == 2);
            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(!has_duplicate_attribute_names(c, lg));
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.all_attributes().size() == 1);
            BOOST_CHECK(o.local_attributes().size() == 1);
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.all_attributes().size() == 3);
            BOOST_CHECK(o.local_attributes().size() == 3);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_two_levels_of_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_two_levels_of_concept_inheritance_results_in_expected_indices");

    auto m(factory.make_second_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.concepts().size() == 3);
    for (const auto& pair : m.concepts()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n)) {
            BOOST_CHECK(c.inherited_attributes().empty());
            BOOST_CHECK(c.all_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes() == c.local_attributes());
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, n)) {
            BOOST_REQUIRE(c.inherited_attributes().size() == 1);
            const auto props(c.inherited_attributes().begin()->second);
            BOOST_REQUIRE(props.size() == 1);

            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes().size() == 2);
            BOOST_CHECK(c.refines().size() == 1);
            BOOST_CHECK(!has_duplicate_attribute_names(c, lg));
        } else if (factory.is_concept_name_n(2, n)) {
            BOOST_CHECK(c.inherited_attributes().size() == 2);
            for (const auto& pair : c.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes().size() == 3);
            BOOST_CHECK(c.refines().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(c, lg));
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 3);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 1);
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 2);
            BOOST_CHECK(o.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else if (factory.is_type_name_n(2, n)) {
            BOOST_REQUIRE(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 4);
            BOOST_CHECK(o.all_attributes().size() == 4);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_diamond_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_diamond_concept_inheritance_results_in_expected_indices");

    auto m(factory.make_diamond_inheritance_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;
    BOOST_CHECK(m.concepts().size() == 4);
    for (const auto& pair : m.concepts()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n)) {
            BOOST_CHECK(c.inherited_attributes().empty());
            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes() == c.local_attributes());
        } else if (factory.is_concept_name_n(1, n)) {
            BOOST_CHECK(c.inherited_attributes().size() == 1);
            for (const auto& pair : c.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(c, lg));
        } else if (factory.is_concept_name_n(2, n)) {
            BOOST_CHECK(c.inherited_attributes().size() == 1);
            for (const auto& pair : c.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(c, lg));
        } else if (factory.is_concept_name_n(3, n)) {
            BOOST_CHECK(c.inherited_attributes().size() == 3);
            for (const auto& pair : c.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes().size() == 4);
            BOOST_CHECK(!has_duplicate_attribute_names(c, lg));
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& o(*(m.objects().begin()->second));
        BOOST_CHECK(o.inherited_attributes().empty());
        BOOST_CHECK(o.local_attributes().size() == 4);
        BOOST_CHECK(o.all_attributes().size() == 4);
        BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
    }
}

BOOST_AUTO_TEST_CASE(model_with_single_parent_that_does_not_model_concepts_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_single_parent_that_does_not_model_concepts_results_in_expected_indices");

    auto a(factory.object_with_parent_in_the_same_model());
    auto e(factory.object_with_parent_in_the_same_model());
    for (auto& pair : e.objects()) {
        auto& o(*pair.second);
        if (!o.parents().empty()) {
            BOOST_REQUIRE(o.parents().size() == 1);
            o.inherited_attributes()[o.parents().front()];
        }
    }

    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    BOOST_REQUIRE(a.objects().size() == 2);
    BOOST_REQUIRE(a.concepts().empty());

    attributes_transform::transform(a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_third_degree_inheritance_that_does_not_model_concepts_and_has_no_attributes_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_third_degree_inheritance_that_does_not_model_concepts_and_has_no_attributes_results_in_expected_indices");

    auto a(factory.object_with_third_degree_parent_in_same_model());
    auto e(factory.object_with_third_degree_parent_in_same_model());
    for (auto& pair : e.objects()) {
        auto& o(*pair.second);
        if (!o.parents().empty()) {
            BOOST_REQUIRE(o.parents().size() == 1);
            o.inherited_attributes()[o.parents().front()];
        }
    }

    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    BOOST_REQUIRE(a.objects().size() == 4);
    BOOST_REQUIRE(a.concepts().empty());

    attributes_transform::transform(a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_third_degree_inheritance_that_does_not_model_concepts_but_has_attributes_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_third_degree_inheritance_that_does_not_model_concepts_but_has_attributes_results_in_expected_indices");

    auto m(factory.object_with_third_degree_parent_in_same_model(
            origin_types::target, true/*has_attribute*/));
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    BOOST_REQUIRE(m.objects().size() == 4);
    BOOST_REQUIRE(m.concepts().empty());

    attributes_transform::transform(m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;
    BOOST_REQUIRE(m.objects().size() == 4);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(3, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes() == o.local_attributes());
        } else if (factory.is_type_name_n(2, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 2);
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 2);

            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 3);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 3);

            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 4);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_containing_object_with_parent_that_models_concept_is_untouched_by_attributes_transform) {
    SETUP_TEST_LOG_SOURCE("model_containing_object_with_parent_that_models_concept_is_untouched_by_attributes_transform");

    auto m(factory.make_object_with_parent_that_models_concept());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_CHECK(m.concepts().size() == 1);
    for (const auto& pair : m.concepts()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n)) {
            BOOST_CHECK(c.inherited_attributes().empty());
            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes() == c.local_attributes());
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 1);
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(o.local_attributes().empty());
            BOOST_CHECK(o.all_attributes().size() == 1);
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_containing_object_with_parent_that_models_a_refined_concept_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_containing_object_with_parent_that_models_a_refined_concept_results_in_expected_indices");

    auto m(factory.make_object_with_parent_that_models_a_refined_concept());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_CHECK(m.concepts().size() == 2);
    for (const auto& pair : m.concepts()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_concept_name_n(0, n)) {
            BOOST_CHECK(c.inherited_attributes().empty());
            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes() == c.local_attributes());
        } else if (factory.is_concept_name_n(1, n)) {
            BOOST_CHECK(c.inherited_attributes().size() == 1);
            for (const auto& pair : c.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(c, lg));
        } else
            BOOST_FAIL("Unexpected concept: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 2);
            BOOST_CHECK(o.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 2);

            BOOST_CHECK(o.local_attributes().empty());
            BOOST_CHECK(o.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_concept_that_refines_missing_concept_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_concept_that_refines_missing_concept_throws");

    auto m(factory.make_concept_that_refines_missing_concept());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    contains_checker<transformation_error> c(concept_not_found);
    BOOST_CHECK_EXCEPTION(
        attributes_transform::transform(m), transformation_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_that_models_missing_concept_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_that_models_missing_concept_throws");

    auto m(factory.make_object_that_models_missing_concept());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    contains_checker<transformation_error> c(concept_not_found);
    BOOST_CHECK_EXCEPTION(
        attributes_transform::transform(m), transformation_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_with_missing_parent_throws) {
    SETUP_TEST_LOG_SOURCE("model_object_that_models_concept_with_missing_parent");

    auto m(factory.make_object_that_models_concept_with_missing_parent());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    contains_checker<transformation_error> c(object_not_found);
    BOOST_CHECK_EXCEPTION(
        attributes_transform::transform(m), transformation_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
