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
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/tack/io/model_io.hpp"
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/types/indexing_error.hpp"
#include "dogen/tack/types/object.hpp"
#include "dogen/tack/io/model_io.hpp"
#include "dogen/tack/types/string_converter.hpp"
#include "dogen/tack/io/object_io.hpp"
#include "dogen/tack/test/mock_model_factory.hpp"
#include "dogen/tack/types/association_indexer.hpp"

namespace {

const std::string test_module("tack");
const std::string test_suite("association_indexer_spec");
const std::string object_not_found("Object not found in");

using dogen::tack::test::mock_model_factory;

/* @note tagging should make no difference to tests, and not having tags
 * makes the model dumps easier to understand.
 *
 * However, strictly speaking, tagging happens before indexing so it
 * would be more truthful to use a tagged model in the tests.
 */
const mock_model_factory::flags flags(false/*tagged*/, false/*merged*/,
    false/*resolved*/, true/*concepts_indexed*/, true/*properties_indexed*/,
    false/*associations_indexed*/);
const mock_model_factory factory(flags);

}

using dogen::utility::test::contains_checker;
using dogen::tack::indexing_error;
using dogen::tack::string_converter;
using dogen::utility::test::asserter;
using object_types = dogen::tack::test::mock_model_factory::object_types;
using property_types = dogen::tack::test::mock_model_factory::property_types;

BOOST_AUTO_TEST_SUITE(association_indexer)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_association_indexer) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_association_indexer");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_REQUIRE(a.objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    dogen::tack::association_indexer i;
    i.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_properties_is_untouched_by_association_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_properties_is_untouched_by_association_indexer");

    auto a(factory.make_single_type_model());
    const auto e(factory.make_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;
    BOOST_REQUIRE(a.objects().size() == 1);

    dogen::tack::association_indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_property_results_in_expected_indices");

    auto m(factory.object_with_property(object_types::value_object,
            property_types::unsigned_int));
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);

    const auto& o(m.objects().begin()->second);
    using dogen::tack::relationship_types;
    const auto ra(relationship_types::regular_associations);
    auto i(o.relationships().find(ra));
    BOOST_REQUIRE(i != o.relationships().end());
    BOOST_CHECK(i->second.size() == 1);

    const auto wa(relationship_types::weak_associations);
    i = o.relationships().find(wa);
    BOOST_CHECK(i == o.relationships().end());
}

BOOST_AUTO_TEST_CASE(model_with_single_concept_is_untouched_by_association_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_single_concept_is_untouched_by_association_indexer");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_REQUIRE(a.objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    dogen::tack::association_indexer i;
    i.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_more_than_one_property_of_the_same_type_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_more_than_one_property_of_the_same_type_results_in_expected_indices");

    auto m(factory.make_first_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    using dogen::tack::relationship_types;
    const auto ra(relationship_types::regular_associations);
    const auto wa(relationship_types::weak_associations);

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        auto i(o.relationships().find(ra));
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_CHECK(i->second.size() == 1);

            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_CHECK(i->second.size() == 1);

            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        } else
            BOOST_FAIL("Unexpected object: " << string_converter::convert(qn));
    }
}

BOOST_AUTO_TEST_CASE(model_with_object_with_multiple_properties_of_different_types_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_object_with_multiple_properties_of_different_types_results_in_expected_indices");

    auto m(factory.object_with_group_of_properties_of_different_types());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    using dogen::tack::relationship_types;
    const auto ra(relationship_types::regular_associations);
    const auto wa(relationship_types::weak_associations);

    bool found0(false), found1(false), found3(false);
    BOOST_REQUIRE(m.objects().size() == 5);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        auto i(o.relationships().find(ra));
        if (factory.is_type_name_n(0, qn)) {
            found0 = true;
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_CHECK(i->second.size() == 4);

            std::vector<bool> found;
            found.resize(4);
            for (const auto& qn : i->second) {
                if (qn.simple_name() == "shared_ptr")
                    found[0] = true;

                if (qn.simple_name() == "unsigned int")
                    found[1] = true;

                if (factory.is_type_name_n(1, qn.simple_name()))
                    found[2] = true;

                if (factory.is_type_name_n(4, qn.simple_name()))
                    found[3] = true;
            }

            for (const auto b : found)
                BOOST_CHECK(b);

            i = o.relationships().find(wa);
            BOOST_CHECK(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_CHECK(factory.is_type_name_n(3,
                    i->second.front().simple_name()));
        } else if (factory.is_type_name_n(1, qn)) {
            found1 = true;
            BOOST_CHECK(i == o.relationships().end());
            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        } else if (factory.is_type_name_n(3, qn)) {
            found3 = true;
            BOOST_CHECK(i == o.relationships().end());
            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        }
        // ignore boost shared ptr, pair, etc
    }

    BOOST_CHECK(found0);
    BOOST_CHECK(found1);
    BOOST_CHECK(found3);
}

BOOST_AUTO_TEST_CASE(model_with_object_with_multiple_properties_of_different_types_that_are_repeated_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_object_with_multiple_properties_of_different_types_that_are_repeated_results_in_expected_indices");

    auto m(factory.object_with_group_of_properties_of_different_types(
            true/*repeat_group*/));
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    using dogen::tack::relationship_types;
    const auto ra(relationship_types::regular_associations);
    const auto wa(relationship_types::weak_associations);

    bool found0(false), found1(false), found3(false);
    BOOST_REQUIRE(m.objects().size() == 5);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        auto i(o.relationships().find(ra));
        if (factory.is_type_name_n(0, qn)) {
            found0 = true;
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_CHECK(i->second.size() == 4);
            std::vector<bool> found;
            found.resize(4);
            for (const auto& qn : i->second) {
                if (qn.simple_name() == "shared_ptr")
                    found[0] = true;

                if (qn.simple_name() == "unsigned int")
                    found[1] = true;

                if (factory.is_type_name_n(1, qn.simple_name()))
                    found[2] = true;

                if (factory.is_type_name_n(4, qn.simple_name()))
                    found[3] = true;
            }

            for (const auto b : found)
                BOOST_CHECK(b);

            i = o.relationships().find(wa);
            BOOST_CHECK(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_CHECK(factory.is_type_name_n(3,
                    i->second.front().simple_name()));

        } else if (factory.is_type_name_n(1, qn)) {
            found1 = true;
            BOOST_CHECK(i == o.relationships().end());
            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        } else if (factory.is_type_name_n(3, qn)) {
            found3 = true;
            BOOST_CHECK(i == o.relationships().end());
            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        }
        // ignore boost shared ptr, pair, etc
    }

    BOOST_CHECK(found0);
    BOOST_CHECK(found1);
    BOOST_CHECK(found3);
}

BOOST_AUTO_TEST_CASE(object_with_unsigned_int_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_unsigned_int_property_results_in_expected_indices");

    const auto ot(object_types::value_object);
    const auto pt(property_types::unsigned_int);
    auto m(factory.object_with_property(ot, pt));
    BOOST_REQUIRE(m.objects().size() == 1);
    BOOST_REQUIRE(m.objects().begin()->second.local_properties().size() == 1);
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        using dogen::tack::relationship_types;
        const auto ra(relationship_types::regular_associations);
        const auto wa(relationship_types::weak_associations);

        auto i(o.relationships().find(ra));
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_CHECK(i->second.size() == 1);
            BOOST_CHECK(i->second.begin()->simple_name() == "unsigned int");

            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        } else
            BOOST_FAIL("Unexpected object: " << string_converter::convert(qn));
    }
}

BOOST_AUTO_TEST_CASE(object_with_bool_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_bool_property_results_in_expected_indices");

    const auto ot(object_types::value_object);
    const auto pt(property_types::boolean);
    auto m(factory.object_with_property(ot, pt));
    BOOST_REQUIRE(m.objects().size() == 1);
    BOOST_REQUIRE(m.objects().begin()->second.local_properties().size() == 1);
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        using dogen::tack::relationship_types;
        const auto ra(relationship_types::regular_associations);
        const auto wa(relationship_types::weak_associations);

        auto i(o.relationships().find(ra));
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_CHECK(i->second.size() == 1);
            BOOST_CHECK(i->second.begin()->simple_name() == "bool");

            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        } else
            BOOST_FAIL("Unexpected object: " << string_converter::convert(qn));
    }
}

BOOST_AUTO_TEST_CASE(object_with_object_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_object_property_results_in_expected_indices");

    const auto ot(object_types::value_object);
    const auto pt(property_types::value_object);
    auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);

    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        using dogen::tack::relationship_types;
        const auto ra(relationship_types::regular_associations);
        const auto wa(relationship_types::weak_associations);

        auto i(o.relationships().find(ra));
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            const auto sn(i->second.begin()->simple_name());
            BOOST_CHECK(factory.is_type_name_n(1, sn));

            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_CHECK(i == o.relationships().end());
            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        } else
            BOOST_FAIL("Unexpected object: " << string_converter::convert(qn));
    }
}

BOOST_AUTO_TEST_CASE(model_with_object_with_missing_object_property_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_with_missing_object_property_throws");

    auto m(factory.object_with_missing_property_type());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    dogen::tack::association_indexer i;
    using dogen::tack::indexing_error;
    contains_checker<indexing_error> c(object_not_found);
    BOOST_CHECK_EXCEPTION(i.index(m), indexing_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_std_pair_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_std_pair_property_results_in_expected_indices");

    const auto ot(object_types::value_object);
    const auto pt(property_types::std_pair);
    auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;

    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    bool found(false);
    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        using dogen::tack::relationship_types;
        const auto ra(relationship_types::regular_associations);
        const auto wa(relationship_types::weak_associations);

        auto i(o.relationships().find(ra));
        if (factory.is_type_name_n(0, qn)) {
            found = true;
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_CHECK(i->second.size() == 2);
            const auto front_sn(i->second.front().simple_name());
            BOOST_CHECK(front_sn == "bool" || front_sn == "pair");
            const auto back_sn(i->second.back().simple_name());
            BOOST_CHECK(back_sn == "bool" || back_sn == "pair");

            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        }
        // ignore std pair, etc.
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_boost_variant_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_boost_variant_property_results_in_expected_indices");

    const auto ot(object_types::value_object);
    const auto pt(property_types::boost_variant);
    auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);
    BOOST_REQUIRE(m.primitives().size() == 2);

    bool found(false);
    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        if (factory.is_type_name_n(0, pair.first)) {
            found = true;
            BOOST_LOG_SEV(lg, debug) << "found object: "
                                     << string_converter::convert(qn);

            using dogen::tack::relationship_types;
            const auto ra(relationship_types::regular_associations);
            const auto wa(relationship_types::weak_associations);

            auto i(o.relationships().find(ra));
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_CHECK(i->second.size() == 3);
            bool found_uint(false), found_bool(false), found_variant(false);
            for (const auto& qn : i->second) {
                const auto sn(qn.simple_name());
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

            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_std_string_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_std_string_property_results_in_expected_indices");

    const auto ot(object_types::value_object);
    const auto pt(property_types::std_string);
    auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;

    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    bool found(false);
    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        using dogen::tack::relationship_types;
        const auto ra(relationship_types::regular_associations);
        const auto wa(relationship_types::weak_associations);

        auto i(o.relationships().find(ra));
        if (factory.is_type_name_n(0, qn)) {
            found = true;
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_CHECK(i->second.front().simple_name() == "string");

            i = o.relationships().find(wa);
            BOOST_CHECK(i == o.relationships().end());
        }
        // ignore std pair, etc.
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_boost_shared_ptr_property_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_boost_shared_ptr_property_results_in_expected_indices");

    const auto ot(object_types::value_object);
    const auto pt(property_types::boost_shared_ptr);
    auto m(factory.object_with_property(ot, pt));
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 3);

    bool found(false);
    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        if (factory.is_type_name_n(0, pair.first)) {
            found = true;
            BOOST_LOG_SEV(lg, debug) << "found object: "
                                     << string_converter::convert(qn);

            using dogen::tack::relationship_types;
            const auto ra(relationship_types::regular_associations);
            const auto wa(relationship_types::weak_associations);

            auto i(o.relationships().find(ra));
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_CHECK(i->second.front().simple_name() == "shared_ptr");

            i = o.relationships().find(wa);
            BOOST_CHECK(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_CHECK(factory.is_type_name_n(1,
                    i->second.front().simple_name()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_both_regular_and_weak_associations_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("object_with_both_regular_and_weak_associations_results_in_expected_indices");

    auto m(factory.object_with_both_regular_and_weak_associations());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_REQUIRE(m.objects().size() == 5);

    bool found(false);
    dogen::tack::association_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        if (factory.is_type_name_n(0, pair.first)) {
            found = true;
            BOOST_LOG_SEV(lg, debug) << "found object: "
                                     << string_converter::convert(qn);

            using dogen::tack::relationship_types;
            const auto ra(relationship_types::regular_associations);
            const auto wa(relationship_types::weak_associations);

            auto i(o.relationships().find(ra));
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 3);
            std::vector<bool> found;
            found.resize(3);
            for (const auto& qn : i->second) {
                if (qn.simple_name() == "shared_ptr")
                    found[0] = true;

                if (qn.simple_name() == "string")
                    found[1] = true;

                if (factory.is_type_name_n(1, qn.simple_name()))
                    found[2] = true;
            }

            for (const auto b : found)
                BOOST_CHECK(b);

            i = o.relationships().find(wa);
            BOOST_CHECK(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_CHECK(factory.is_type_name_n(3,
                    i->second.front().simple_name()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_SUITE_END()
