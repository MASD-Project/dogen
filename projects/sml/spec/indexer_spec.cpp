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
#include "dogen/sml/types/indexer.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("indexer_spec");

using dogen::sml::test::mock_model_factory;

/* @note tagging should make no difference to tests, and not having tags
 * makes the model dumps easier to understand.
 *
 * However, strictly speaking, tagging happens before indexing so it
 * would be more truthful to use a tagged model in the tests.
 */
const mock_model_factory factory(false/*tagged*/, false/*indexed*/);

}

using dogen::utility::test::contains_checker;
using dogen::sml::indexing_error;
using dogen::utility::test::asserter;
using object_types = dogen::sml::test::mock_model_factory::object_types;
using property_types = dogen::sml::test::mock_model_factory::property_types;

BOOST_AUTO_TEST_SUITE(indexer)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_indexer) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_indexer");

    auto a(factory.build_empty_model());
    BOOST_REQUIRE(a.objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    const auto e(a);
    dogen::sml::indexer i;
    i.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_properties_is_untouched_by_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_properties_is_untouched_by_indexer");

    auto a(factory.build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;
    BOOST_REQUIRE(a.objects().size() == 1);

    const auto e(a);
    dogen::sml::indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_property_results_in_expected_indices");

    auto m(factory.object_with_property(object_types::value_object,
            property_types::unsigned_int));
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    BOOST_REQUIRE(m.concepts().empty());
    BOOST_REQUIRE(m.enumerations().empty());
    BOOST_REQUIRE(m.primitives().size() == 1);

    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& o(*m.objects().begin()->second);
    BOOST_REQUIRE(o.local_properties().size() == 1);
    BOOST_REQUIRE(o.inherited_properties().empty());
    BOOST_REQUIRE(o.all_properties().empty());
    BOOST_REQUIRE(o.relationships().empty());

    dogen::sml::indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    BOOST_CHECK(m.concepts().empty());
    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.primitives().size() == 1);

    BOOST_CHECK(o.local_properties() == o.all_properties());
    BOOST_CHECK(o.inherited_properties().empty());
    BOOST_CHECK(o.relationships().empty());
}

BOOST_AUTO_TEST_CASE(model_with_single_concept_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_single_concept_results_in_expected_indices");

    auto m(factory.build_single_concept_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& o(*m.objects().begin()->second);
    BOOST_REQUIRE(o.local_properties().size() == 1);
    BOOST_REQUIRE(o.all_properties().empty());

    using dogen::sml::relationship_types;
    const auto rt(relationship_types::modeled_concepts);
    const auto i(o.relationships().find(rt));
    BOOST_REQUIRE(i != o.relationships().end());
    BOOST_REQUIRE(i->second.size() == 1);

    BOOST_REQUIRE(m.concepts().size() == 1);
    const auto& c(m.concepts().begin()->second);
    BOOST_REQUIRE(c.local_properties().size() == 1);
    BOOST_REQUIRE(c.inherited_properties().empty());
    BOOST_REQUIRE(c.all_properties().empty());

    dogen::sml::indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    BOOST_CHECK(c.local_properties().size() == 1);
    BOOST_REQUIRE(c.inherited_properties().empty());
    BOOST_CHECK(c.local_properties() == c.all_properties());
    BOOST_CHECK(i->second.size() == 1);

    BOOST_CHECK(o.local_properties().size() == 1);
    BOOST_CHECK(o.inherited_properties().empty());
    BOOST_CHECK(o.all_properties().size() == 2);
    for (const auto& p : o.all_properties()) {
        BOOST_CHECK(p == *o.local_properties().begin() ||
            p == *c.local_properties().begin());
    }
}

BOOST_AUTO_TEST_CASE(model_with_one_level_of_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_one_level_of_concept_inheritance_results_in_expected_indices");

    auto m(factory.build_first_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(*pair.second);

        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(o.local_properties().empty());
            BOOST_REQUIRE(o.inherited_properties().empty());
            BOOST_REQUIRE(o.all_properties().empty());
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(o.local_properties().size() == 1);
            BOOST_REQUIRE(o.inherited_properties().empty());
            BOOST_REQUIRE(o.all_properties().empty());
            BOOST_REQUIRE(o.modeled_concepts().size() == 1);
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }

    BOOST_REQUIRE(m.concepts().size() == 2);
    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        BOOST_REQUIRE(c.local_properties().size() == 1);
        BOOST_REQUIRE(c.all_properties().empty());
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(c.refines().empty());
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(c.refines().size() == 1);
        } else
            BOOST_FAIL("Unexpected concept: " << qn);
    }

    dogen::sml::indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_type_name_n(0, qn)) {
            BOOST_CHECK(c.local_properties().size() == 1);
            BOOST_CHECK(c.inherited_properties().empty());
            BOOST_CHECK(c.local_properties() == c.all_properties());
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_CHECK(c.local_properties().size() == 1);
            BOOST_CHECK(c.inherited_properties().size() == 1);
            BOOST_CHECK(c.all_properties().size() == 2);
        } else
            BOOST_FAIL("Unexpected concept: " << qn);
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(*pair.second);

        if (factory.is_type_name_n(0, qn)) {
            BOOST_CHECK(o.local_properties().empty());
            BOOST_CHECK(o.inherited_properties().empty());
            BOOST_CHECK(o.all_properties().size() == 1);
            BOOST_CHECK(o.modeled_concepts().size() == 1);
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_CHECK(o.local_properties().size() == 1);
            BOOST_CHECK(o.inherited_properties().empty());
            // BOOST_CHECK(o.all_properties().size() == 3);
            // BOOST_CHECK(o.modeled_concepts().size() == 2);
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }
}

BOOST_AUTO_TEST_SUITE_END()
