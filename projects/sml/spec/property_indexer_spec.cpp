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
#include <array>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/indexing_error.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/abstract_object_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/property_indexer.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("property_indexer_spec");

using dogen::sml::test::mock_model_factory;

/**
 * @brief We require the concepts to have been indexed or else we
 * won't work.
 */
const mock_model_factory factory(false/*tagged*/, false/*merged*/,
    true/*concepts_indexed*/, false/*properties_indexed*/);

}

using dogen::utility::test::contains_checker;
using dogen::sml::indexing_error;
using dogen::utility::test::asserter;
using object_types = dogen::sml::test::mock_model_factory::object_types;
using property_types = dogen::sml::test::mock_model_factory::property_types;

BOOST_AUTO_TEST_SUITE(property_indexer)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_property_indexer) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_property_indexer");

    auto a(factory.build_empty_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    const auto e(a);
    dogen::sml::property_indexer i;
    i.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_properties_is_untouched_by_property_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_properties_is_untouched_by_property_indexer");

    auto a(factory.build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    const auto e(a);
    dogen::sml::property_indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_property_results_in_expected_indices");

    auto m(factory.object_with_property(object_types::value_object,
            property_types::unsigned_int));
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::sml::property_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);

    const auto& o(*m.objects().begin()->second);
    BOOST_CHECK(o.local_properties() == o.all_properties());
    BOOST_CHECK(o.inherited_properties().empty());
}

BOOST_AUTO_TEST_CASE(model_with_single_concept_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_single_concept_results_in_expected_indices");

    auto m(factory.build_single_concept_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;
    dogen::sml::property_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    BOOST_REQUIRE(m.concepts().size() == 1);
    const auto& c(m.concepts().begin()->second);
    BOOST_CHECK(c.local_properties().size() == 1);
    BOOST_REQUIRE(c.inherited_properties().empty());
    BOOST_CHECK(c.local_properties() == c.all_properties());

    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& o(*m.objects().begin()->second);
    BOOST_CHECK(o.local_properties().size() == 1);
    BOOST_CHECK(o.inherited_properties().empty());
    BOOST_CHECK(o.all_properties().size() == 2);
    for (const auto& p : o.all_properties()) {
        BOOST_CHECK(p == *o.local_properties().begin() ||
            p == *c.local_properties().begin());
    }
}

// BOOST_AUTO_TEST_CASE_IGNORE(model_with_one_level_of_concept_inheritance_results_in_expected_indices) {
//     SETUP_TEST_LOG_SOURCE("model_with_one_level_of_concept_inheritance_results_in_expected_indices");

//     auto m(factory.build_first_degree_concepts_model());
//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

//     dogen::sml::property_indexer ind;
//     ind.index(m);
//     BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

//     for (const auto& pair : m.concepts()) {
//         const auto& qn(pair.first);
//         const auto& c(pair.second);

//         if (factory.is_concept_name_n(0, qn)) {
//             BOOST_CHECK(c.inherited_properties().empty());
//             BOOST_CHECK(c.all_properties().size() == 1);
//             BOOST_CHECK(c.all_properties() == c.local_properties());
//             BOOST_CHECK(c.refines().empty());
//         } else if (factory.is_concept_name_n(1, qn)) {
//             BOOST_CHECK(c.refines().size() == 1);
//             BOOST_REQUIRE(c.inherited_properties().size() == 1);
//             const auto props(c.inherited_properties().begin()->second);
//             BOOST_REQUIRE(props.size() == 1);

//             BOOST_CHECK(c.all_properties().size() == 2);
//             BOOST_CHECK(c.local_properties().size() == 1);
//         } else
//             BOOST_FAIL("Unexpected concept: " << qn);
//     }

//     BOOST_REQUIRE(m.objects().size() == 2);
//     for (const auto& pair : m.objects()) {
//         const auto& qn(pair.first);
//         const auto& o(*pair.second);

//         if (factory.is_type_name_n(0, qn)) {
//             BOOST_CHECK(o.inherited_properties().empty());
//             BOOST_CHECK(o.all_properties().size() == 1);
//             BOOST_CHECK(o.local_properties().empty());
//         } else if (factory.is_type_name_n(1, qn)) {
//             BOOST_CHECK(o.inherited_properties().empty());
//             BOOST_CHECK(o.all_properties().size() == 3);
//             BOOST_CHECK(o.local_properties().size() == 1);
//         } else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }
// }

// BOOST_AUTO_TEST_CASE_IGNORE(model_with_two_levels_of_concept_inheritance_results_in_expected_indices) {
//     SETUP_TEST_LOG_SOURCE("model_with_two_levels_of_concept_inheritance_results_in_expected_indices");

//     auto m(factory.build_second_degree_concepts_model());
//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

//     dogen::sml::property_indexer ind;
//     ind.index(m);
//     BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

//     BOOST_REQUIRE(m.concepts().size() == 3);
//     for (const auto& pair : m.concepts()) {
//         const auto& qn(pair.first);
//         const auto& c(pair.second);

//         if (factory.is_concept_name_n(0, qn)) {
//             BOOST_CHECK(c.inherited_properties().empty());
//             BOOST_CHECK(c.all_properties().size() == 1);
//             BOOST_CHECK(c.all_properties() == c.local_properties());
//             BOOST_CHECK(c.refines().empty());
//         } else if (factory.is_concept_name_n(1, qn)) {
//             BOOST_CHECK(c.inherited_properties().size() == 1);
//             BOOST_CHECK(c.local_properties().size() == 1);
//             BOOST_CHECK(c.all_properties().size() == 2);
//             BOOST_CHECK(c.refines().size() == 1);
//         } else if (factory.is_concept_name_n(2, qn)) {
//             BOOST_REQUIRE(c.inherited_properties().size() == 1);
//             const auto props(c.inherited_properties().begin()->second);
//             BOOST_REQUIRE(props.size() == 2);

//             BOOST_CHECK(c.local_properties().size() == 1);
//             BOOST_CHECK(c.all_properties().size() == 3);
//             BOOST_CHECK(c.refines().size() == 1);
//         } else
//             BOOST_FAIL("Unexpected concept: " << qn);
//     }

//     BOOST_REQUIRE(m.objects().size() == 3);
//     for (const auto& pair : m.objects()) {
//         const auto& qn(pair.first);
//         const auto& o(*pair.second);

//         if (factory.is_type_name_n(0, qn)) {
//             BOOST_CHECK(o.inherited_properties().empty());
//             BOOST_CHECK(o.local_properties().empty());
//             BOOST_CHECK(o.all_properties().size() == 1);
//         } else if (factory.is_type_name_n(1, qn)) {
//             BOOST_REQUIRE(o.inherited_properties().empty());
//             BOOST_CHECK(o.local_properties().empty());
//             BOOST_CHECK(o.all_properties().size() == 2);
//         } else if (factory.is_type_name_n(2, qn)) {
//             BOOST_REQUIRE(o.inherited_properties().empty());
//             BOOST_CHECK(o.local_properties().size() == 1);
//             BOOST_CHECK(o.all_properties().size() == 4);
//         } else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }
// }

// BOOST_AUTO_TEST_CASE_IGNORE(model_with_diamond_concept_inheritance_results_in_expected_indices) {
//     SETUP_TEST_LOG_SOURCE("model_with_diamond_concept_inheritance_results_in_expected_indices");

//     auto m(factory.build_diamond_inheritance_concepts_model());
//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

//     dogen::sml::property_indexer ind;
//     ind.index(m);
//     BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;
//     BOOST_CHECK(m.concepts().size() == 4);
//     for (const auto& pair : m.concepts()) {
//         const auto& qn(pair.first);
//         const auto& c(pair.second);

//         if (factory.is_concept_name_n(0, qn)) {
//             BOOST_CHECK(c.inherited_properties().empty());
//             BOOST_CHECK(c.local_properties().size() == 1);
//             BOOST_CHECK(c.all_properties() == c.local_properties());
//         } else if (factory.is_concept_name_n(1, qn)) {
//             BOOST_CHECK(c.inherited_properties().size() == 1);
//             BOOST_CHECK(c.local_properties().size() == 1);
//             BOOST_CHECK(c.all_properties().size() == 2);
//         } else if (factory.is_concept_name_n(2, qn)) {
//             BOOST_CHECK(c.inherited_properties().size() == 1);
//             BOOST_CHECK(c.local_properties().size() == 1);
//             BOOST_CHECK(c.all_properties().size() == 2);
//         } else if (factory.is_concept_name_n(3, qn)) {
//             BOOST_CHECK(c.inherited_properties().size() == 2);
//             BOOST_CHECK(c.local_properties().size() == 1);
//             BOOST_CHECK(c.all_properties().size() == 3);
//         } else
//             BOOST_FAIL("Unexpected concept: " << qn);
//     }

//     BOOST_REQUIRE(m.objects().size() == 1);
//     {
//         const auto& qn(m.objects().begin()->first);
//         const auto& o(*(m.objects().begin()->second));

//         const auto i(o.relationships().find(mc));
//         BOOST_REQUIRE(i != o.relationships().end());

//         BOOST_CHECK(factory.is_type_name_n(0, qn));
//         BOOST_CHECK(i->second.size() == 4);
//     }
// }

// BOOST_AUTO_TEST_CASE_IGNORE(model_with_single_parent_that_does_not_model_concepts_is_untouched_by_property_indexer) {
//     SETUP_TEST_LOG_SOURCE("model_with_single_parent_that_does_not_model_concepts_is_untouched_by_property_indexer");

//     auto a(factory.object_with_parent_in_the_same_model());
//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

//     BOOST_REQUIRE(a.objects().size() == 2);
//     BOOST_REQUIRE(a.concepts().empty());

//     const auto e(a);
//     dogen::sml::property_indexer ind;
//     ind.index(a);
//     BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
//     BOOST_CHECK(asserter::assert_object(e, a));
// }

// BOOST_AUTO_TEST_CASE_IGNORE(model_with_third_degree_inheritance_that_does_not_model_concepts_is_untouched_by_property_indexer) {
//     SETUP_TEST_LOG_SOURCE("model_with_third_degree_inheritance_that_does_not_model_concepts_is_untouched_by_property_indexer");

//     auto a(factory.object_with_third_degree_parent_in_same_model());
//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

//     BOOST_REQUIRE(a.objects().size() == 4);
//     BOOST_REQUIRE(a.concepts().empty());

//     const auto e(a);
//     dogen::sml::property_indexer ind;
//     ind.index(a);
//     BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
//     BOOST_CHECK(asserter::assert_object(e, a));
// }

// BOOST_AUTO_TEST_CASE_IGNORE(model_containing_object_with_parent_that_models_concept_is_untouched_by_property_indexer) {
//     SETUP_TEST_LOG_SOURCE("model_containing_object_with_parent_that_models_concept_is_untouched_by_property_indexer");

//     auto a(factory.build_object_with_parent_that_models_concept());
//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

//     BOOST_REQUIRE(a.concepts().size() == 1);
//     for (const auto& pair : a.concepts()) {
//         const auto& qn(pair.first);
//         const auto& c(pair.second);

//         if (factory.is_concept_name_n(0, qn))
//             BOOST_REQUIRE(c.refines().empty());
//         else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }

//     using dogen::sml::relationship_types;
//     const auto mc(relationship_types::modeled_concepts);
//     const auto par(relationship_types::parents);

//     BOOST_REQUIRE(a.objects().size() == 2);
//     for (const auto& pair : a.objects()) {
//         const auto& qn(pair.first);
//         const auto& o(*pair.second);

//         auto i(o.relationships().find(mc));
//         if (factory.is_type_name_n(0, qn)) {
//             BOOST_REQUIRE(i != o.relationships().end());
//             BOOST_REQUIRE(i->second.size() == 1);
//             BOOST_REQUIRE(factory.is_concept_name_n(0, i->second.front()));
//         } else if (factory.is_type_name_n(1, qn)) {
//             BOOST_REQUIRE(i == o.relationships().end());

//             i = o.relationships().find(par);
//             BOOST_REQUIRE(i != o.relationships().end());
//             BOOST_REQUIRE(i->second.size() == 1);
//             BOOST_REQUIRE(factory.is_type_name_n(0, i->second.front()));
//         } else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }

//     const auto e(a);
//     dogen::sml::property_indexer ind;
//     ind.index(a);
//     BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
//     BOOST_CHECK(asserter::assert_object(e, a));
// }

// BOOST_AUTO_TEST_CASE_IGNORE(model_with_containing_object_with_parent_that_models_a_refined_concept_results_in_expected_indices) {
//     SETUP_TEST_LOG_SOURCE("model_with_containing_object_with_parent_that_models_a_refined_concept_results_in_expected_indices");

//     auto m(factory.build_object_with_parent_that_models_a_refined_concept());
//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

//     BOOST_REQUIRE(m.concepts().size() == 2);
//     for (const auto& pair : m.concepts()) {
//         const auto& qn(pair.first);
//         const auto& c(pair.second);

//         if (factory.is_concept_name_n(0, qn))
//             BOOST_REQUIRE(c.refines().empty());
//         else if (factory.is_concept_name_n(1, qn)) {
//             BOOST_REQUIRE(c.refines().size() == 1);
//             BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
//         } else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }

//     using dogen::sml::relationship_types;
//     const auto mc(relationship_types::modeled_concepts);
//     const auto par(relationship_types::parents);

//     BOOST_REQUIRE(m.objects().size() == 2);
//     for (const auto& pair : m.objects()) {
//         const auto& qn(pair.first);
//         const auto& o(*pair.second);

//         auto i(o.relationships().find(mc));
//         if (factory.is_type_name_n(0, qn)) {
//             BOOST_REQUIRE(i != o.relationships().end());
//             BOOST_REQUIRE(i->second.size() == 1);
//             BOOST_REQUIRE(factory.is_concept_name_n(1, i->second.front()));
//         } else if (factory.is_type_name_n(1, qn)) {
//             BOOST_REQUIRE(i == o.relationships().end());

//             i = o.relationships().find(par);
//             BOOST_REQUIRE(i != o.relationships().end());
//             BOOST_REQUIRE(i->second.size() == 1);
//             BOOST_REQUIRE(factory.is_type_name_n(0, i->second.front()));
//         } else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }

//     dogen::sml::property_indexer ind;
//     ind.index(m);
//     BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

//     BOOST_CHECK(m.concepts().size() == 2);
//     for (const auto& pair : m.concepts()) {
//         const auto& qn(pair.first);
//         const auto& c(pair.second);

//         if (factory.is_concept_name_n(0, qn)) {
//             BOOST_CHECK(c.refines().empty());
//         } else if (factory.is_concept_name_n(1, qn)) {
//             BOOST_CHECK(c.refines().size() == 1);
//             BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
//         } else
//             BOOST_FAIL("Unexpected concept: " << qn);
//     }

//     BOOST_REQUIRE(m.objects().size() == 2);
//     for (const auto& pair : m.objects()) {
//         const auto& qn(pair.first);
//         const auto& o(*pair.second);

//         auto i(o.relationships().find(mc));
//         if (factory.is_type_name_n(0, qn)) {
//             BOOST_REQUIRE(i->second.size() == 2);
//             BOOST_REQUIRE(
//                 factory.is_concept_name_n(0, i->second.front()) ||
//                 factory.is_concept_name_n(1, i->second.front()));
//             BOOST_REQUIRE(
//                 factory.is_concept_name_n(0, i->second.back()) ||
//                 factory.is_concept_name_n(1, i->second.back()));
//         } else if (factory.is_type_name_n(1, qn)) {
//             BOOST_REQUIRE(i == o.relationships().end());

//             i = o.relationships().find(par);
//             BOOST_REQUIRE(i != o.relationships().end());
//             BOOST_REQUIRE(i->second.size() == 1);
//             BOOST_REQUIRE(factory.is_type_name_n(0, i->second.front()));
//         } else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }
// }

// BOOST_AUTO_TEST_CASE_IGNORE(model_with_concept_that_refines_missing_concept_throws) {
//     SETUP_TEST_LOG_SOURCE("model_with_concept_that_refines_missing_concept_throws");

//     auto m(factory.build_concept_that_refines_missing_concept());
//     BOOST_REQUIRE(m.objects().empty());
//     BOOST_REQUIRE(m.concepts().size() == 1);
//     {
//         const auto& qn(m.concepts().begin()->first);
//         const auto& c(m.concepts().begin()->second);

//         if (factory.is_concept_name_n(1, qn)) {
//             BOOST_REQUIRE(c.refines().size() == 1);
//             BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
//         } else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }

//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

//     dogen::sml::property_indexer i;
//     using dogen::sml::indexing_error;
//     contains_checker<indexing_error> c(concept_not_found);
//     BOOST_CHECK_EXCEPTION(i.index(m), indexing_error, c);
// }

// BOOST_AUTO_TEST_CASE_IGNORE(model_with_object_that_models_missing_concept_throws) {
//     SETUP_TEST_LOG_SOURCE("model_with_object_that_models_missing_concept_throws");

//     auto m(factory.build_object_that_models_missing_concept());
//     BOOST_REQUIRE(m.concepts().empty());
//     BOOST_REQUIRE(m.objects().size() == 1);
//     {
//         const auto& qn(m.objects().begin()->first);
//         if (!factory.is_type_name_n(0, qn))
//             BOOST_FAIL("Unexpected object: " << qn);

//         const auto& o(*m.objects().begin()->second);
//         using dogen::sml::relationship_types;
//         const auto mc(relationship_types::modeled_concepts);
//         auto i(o.relationships().find(mc));

//         BOOST_REQUIRE(i != o.relationships().end());
//         BOOST_REQUIRE(i->second.size() == 1);
//         BOOST_REQUIRE(factory.is_concept_name_n(0, i->second.front()));
//     }

//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

//     dogen::sml::property_indexer i;
//     using dogen::sml::indexing_error;
//     contains_checker<indexing_error> c(concept_not_found);
//     BOOST_CHECK_EXCEPTION(i.index(m), indexing_error, c);
// }

// BOOST_AUTO_TEST_CASE_IGNORE(model_with_object_with_missing_parent_throws) {
//     SETUP_TEST_LOG_SOURCE("build_object_that_models_concept_with_missing_parent");

//     auto m(factory.build_object_that_models_concept_with_missing_parent());
//     BOOST_REQUIRE(m.concepts().size() == 1);
//     {
//         const auto& qn(m.concepts().begin()->first);
//         const auto& c(m.concepts().begin()->second);

//         if (factory.is_concept_name_n(0, qn))
//             BOOST_REQUIRE(c.refines().empty());
//         else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }

//     BOOST_REQUIRE(m.objects().size() == 1);
//     {
//         const auto& qn(m.objects().begin()->first);
//         const auto& o(*m.objects().begin()->second);

//         using dogen::sml::relationship_types;
//         const auto mc(relationship_types::modeled_concepts);

//         auto i(o.relationships().find(mc));
//         if (factory.is_type_name_n(1, qn)) {
//             BOOST_REQUIRE(i != o.relationships().end());
//             BOOST_REQUIRE(i->second.size() == 1);
//             BOOST_REQUIRE(factory.is_concept_name_n(0, i->second.front()));

//             const auto par(relationship_types::parents);
//             i = o.relationships().find(par);
//             BOOST_REQUIRE(i != o.relationships().end());
//             BOOST_REQUIRE(i->second.size() == 1);
//             BOOST_REQUIRE(factory.is_type_name_n(0, i->second.front()));
//         } else
//             BOOST_FAIL("Unexpected object: " << qn);
//     }

//     BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

//     dogen::sml::property_indexer i;
//     using dogen::sml::indexing_error;
//     contains_checker<indexing_error> c(object_not_found);
//     BOOST_CHECK_EXCEPTION(i.index(m), indexing_error, c);
// }

BOOST_AUTO_TEST_SUITE_END()
