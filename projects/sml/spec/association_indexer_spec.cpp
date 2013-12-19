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
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/object_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/association_indexer.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("association_indexer_spec");

using dogen::sml::test::mock_model_factory;

/* @note tagging should make no difference to tests, and not having tags
 * makes the model dumps easier to understand.
 *
 * However, strictly speaking, tagging happens before indexing so it
 * would be more truthful to use a tagged model in the tests.
 */
const mock_model_factory::flags flags(false/*tagged*/, false/*resolved*/,
    false/*merged*/, true/*concepts_indexed*/, true/*properties_indexed*/);
const mock_model_factory factory(flags);

}

using dogen::utility::test::contains_checker;
using dogen::sml::indexing_error;
using dogen::utility::test::asserter;
using object_types = dogen::sml::test::mock_model_factory::object_types;
using property_types = dogen::sml::test::mock_model_factory::property_types;

BOOST_AUTO_TEST_SUITE(association_indexer)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_association_indexer) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_association_indexer");

    auto a(factory.build_empty_model());
    const auto e(factory.build_empty_model());
    BOOST_REQUIRE(a.objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    dogen::sml::association_indexer i;
    i.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_properties_is_untouched_by_association_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_properties_is_untouched_by_association_indexer");

    auto a(factory.build_single_type_model());
    const auto e(factory.build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;
    BOOST_REQUIRE(a.objects().size() == 1);

    dogen::sml::association_indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_property_results_in_expected_indices");

    auto m(factory.object_with_property(object_types::value_object,
            property_types::unsigned_int));
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::sml::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);

    const auto& o(m.objects().begin()->second);
    using dogen::sml::relationship_types;
    const auto ra(relationship_types::regular_associations);
    auto i(o.relationships().find(ra));
    BOOST_REQUIRE(i != o.relationships().end());
    BOOST_REQUIRE(i->second.size() == 1);

    const auto pa(relationship_types::pointer_associations);
    i = o.relationships().find(pa);
    BOOST_REQUIRE(i == o.relationships().end());
}

BOOST_AUTO_TEST_CASE(model_with_single_concept_is_untouched_by_association_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_single_concept_is_untouched_by_association_indexer");

    auto a(factory.build_empty_model());
    const auto e(factory.build_empty_model());
    BOOST_REQUIRE(a.objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    dogen::sml::association_indexer i;
    i.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_more_than_one_property_of_the_same_type_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_more_than_one_property_of_the_same_type_results_in_expected_indices");

    auto m(factory.build_first_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::sml::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    using dogen::sml::relationship_types;
    const auto ra(relationship_types::regular_associations);
    const auto pa(relationship_types::pointer_associations);

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        auto i(o.relationships().find(ra));
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);

            i = o.relationships().find(pa);
            BOOST_REQUIRE(i == o.relationships().end());
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);

            i = o.relationships().find(pa);
            BOOST_REQUIRE(i == o.relationships().end());
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }
}

BOOST_AUTO_TEST_CASE(model_with_object_with_multiple_properties_of_different_types_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_object_with_multiple_properties_of_different_types_results_in_expected_indices");

    auto m(factory.object_with_group_of_properties_of_different_types());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::sml::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    // using dogen::sml::relationship_types;
    // const auto ra(relationship_types::regular_associations);
    // const auto pa(relationship_types::pointer_associations);

    // BOOST_REQUIRE(m.objects().size() == 4);
    // for (const auto& pair : m.objects()) {
    //     const auto& qn(pair.first);
    //     const auto& o(pair.second);

    //     auto i(o.relationships().find(ra));
    //     if (factory.is_type_name_n(0, qn)) {
    //         BOOST_REQUIRE(i != o.relationships().end());
    //         BOOST_REQUIRE(i->second.size() == 4);

    //         i = o.relationships().find(pa);
    //         BOOST_REQUIRE(i == o.relationships().end());
    //     } else if (factory.is_type_name_n(1, qn)) {
    //         BOOST_REQUIRE(i == o.relationships().end());
    //         i = o.relationships().find(pa);
    //         BOOST_REQUIRE(i == o.relationships().end());
    //     } else if (factory.is_type_name_n(2, qn)) {
    //         BOOST_REQUIRE(i == o.relationships().end());
    //         i = o.relationships().find(pa);
    //         BOOST_REQUIRE(i == o.relationships().end());
    //     } else if (factory.is_type_name_n(3, qn)) {
    //         BOOST_REQUIRE(i == o.relationships().end());
    //         i = o.relationships().find(pa);
    //         BOOST_REQUIRE(i == o.relationships().end());
    //     } else
    //         BOOST_FAIL("Unexpected object: " << qn);
    // }
}

BOOST_AUTO_TEST_SUITE_END()
