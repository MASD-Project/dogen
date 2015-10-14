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
#include <set>
#include <array>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/tack/types/name.hpp"
#include "dogen/tack/io/name_io.hpp"
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/io/model_io.hpp"
#include "dogen/tack/types/object.hpp"
#include "dogen/tack/types/merger.hpp"
#include "dogen/tack/types/merging_error.hpp"
#include "dogen/tack/test/mock_model_factory.hpp"

namespace {

const std::string test_module("tack");
const std::string test_suite("merger_spec");

using dogen::tack::test::mock_model_factory;
const mock_model_factory::flags flags;
const mock_model_factory factory(flags);

const std::string invalid_simple_name("INVALID");
const std::string invalid_model_name("INVALID");
const std::string some_path("some_path");

const std::string incorrect_model("Type does not belong to this model");
const std::string double_merging("Attempt to merge more than once");
const std::string inconsistent_kvp("Inconsistency between key and value");

const std::string missing_target("Target model not present");
const std::string too_many_targets("Only one target expected.");
const std::string incorrect_meta_type("Type has incorrect meta_type");

}

using dogen::utility::test::contains_checker;
using dogen::tack::merging_error;

BOOST_AUTO_TEST_SUITE(merger)

BOOST_AUTO_TEST_CASE(merging_n_distinct_models_with_one_object_each_results_in_n_objects_in_merged_model) {
    SETUP_TEST_LOG_SOURCE("merging_n_distinct_models_with_one_object_each_results_in_n_objects_in_merged_model");

    auto target(factory.make_single_type_model(0));
    target.is_target(true);
    const unsigned int n(5);
    for (unsigned int i(1); i < n; ++i) {
        dogen::tack::name n;
        n.location().original_model_name(factory.model_name(i));
        const auto ot(dogen::tack::origin_types::unknown);
        target.references().insert(std::make_pair(n, ot));
    }

    dogen::tack::merger mg;
    mg.add(target);

    for (unsigned int i(1); i < n; ++i) {
        auto m(factory.make_single_type_model(i));
        m.name().location().external_module_path().push_back(some_path);
        mg.add(m);
    }

    BOOST_CHECK(!mg.has_merged());
    const auto combined(mg.merge());
    BOOST_CHECK(mg.has_merged());
    BOOST_CHECK(combined.objects().size() == n);
    BOOST_CHECK(combined.primitives().empty());
    BOOST_CHECK(combined.enumerations().empty());
    BOOST_CHECK(combined.concepts().empty());
    BOOST_CHECK(combined.modules().empty());
    BOOST_CHECK(combined.references().size() == 4);

    for (const auto pair : combined.references()) {
        BOOST_CHECK(pair.first.location().external_module_path().front() ==
            some_path);
        BOOST_CHECK(pair.second == dogen::tack::origin_types::user);
    }

    std::set<std::string> object_names;
    std::set<std::string> model_names;
    for (const auto& pair : combined.objects()) {
        const auto& n(pair.first);
        object_names.insert(n.location().original_model_name() + "_"
            + n.simple());
        model_names.insert(n.location().original_model_name());
    }

    BOOST_REQUIRE(object_names.size() == n);
    BOOST_REQUIRE(model_names.size() == n);

    auto object_i(object_names.cbegin());
    auto model_i(model_names.cbegin());
    for (unsigned int i(0); i < n; ++i) {
        BOOST_REQUIRE(object_i != object_names.cend());
        BOOST_REQUIRE(model_i != model_names.cend());

        BOOST_LOG_SEV(lg, debug) << "object name: " << *object_i;
        BOOST_LOG_SEV(lg, debug) << "model name: " << *model_i;

        const auto expected_model_name(factory.model_name(i));
        const auto expected_object_name(factory.type_name(0));
        BOOST_LOG_SEV(lg, debug) << "expected object name: "
                                 << expected_object_name;
        BOOST_LOG_SEV(lg, debug) << "expected model name: "
                                 << expected_model_name;

        BOOST_CHECK(boost::ends_with(*object_i, expected_object_name));
        BOOST_CHECK(boost::starts_with(*object_i, expected_model_name));
        BOOST_CHECK(*model_i == expected_model_name);
        ++object_i;
        ++model_i;
    }
}

BOOST_AUTO_TEST_CASE(merging_empty_model_results_in_empty_merged_model) {
    SETUP_TEST_LOG("merging_empty_model_results_in_empty_merged_model");
    dogen::tack::merger mg;
    dogen::tack::model m;
    m.is_target(true);
    BOOST_CHECK(!mg.has_target());
    mg.add(m);
    BOOST_CHECK(mg.has_target());

    const auto combined(mg.merge());
    BOOST_CHECK(combined.objects().empty());
    BOOST_CHECK(combined.primitives().empty());
    BOOST_CHECK(combined.enumerations().empty());
    BOOST_CHECK(combined.modules().empty());
}

BOOST_AUTO_TEST_CASE(type_with_incorrect_model_name_throws) {
    SETUP_TEST_LOG("type_with_incorrect_model_name_throws");
    auto m(factory.make_single_type_model());
    m.is_target(true);
    m.name().location().original_model_name(invalid_model_name);

    dogen::tack::merger mg;
    mg.add(m);

    contains_checker<merging_error> c(incorrect_model);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_CASE(type_with_inconsistent_key_value_pair_throws) {
    SETUP_TEST_LOG("type_with_inconsistent_key_value_pair_throws");

    auto m(factory.make_multi_type_model(0, 2));
    m.is_target(true);
    m.objects().begin()->second.name().simple(invalid_simple_name);

    dogen::tack::merger mg;
    mg.add(m);

    contains_checker<merging_error> c(inconsistent_kvp);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_CASE(not_adding_a_target_throws) {
    SETUP_TEST_LOG("not_adding_a_target_throws");

    const auto m(factory.make_single_type_model());
    dogen::tack::merger mg;
    mg.add(m);

    contains_checker<merging_error> c(missing_target);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_CASE(adding_more_than_one_target_throws) {
    SETUP_TEST_LOG("adding_more_than_one_target_throws");
    auto m0(factory.make_single_type_model(0));
    m0.is_target(true);

    auto m1(factory.make_single_type_model(1));
    m1.is_target(true);

    dogen::tack::merger mg;
    mg.add(m0);

    contains_checker<merging_error> c(too_many_targets);
    BOOST_CHECK_EXCEPTION(mg.add(m1), merging_error, c);
}

BOOST_AUTO_TEST_CASE(merging_more_than_once_throws) {
    SETUP_TEST_LOG("merging_more_than_once_throws");
    auto m(factory.make_single_type_model());
    m.is_target(true);

    dogen::tack::merger mg;
    mg.add(m);
    mg.merge();

    contains_checker<merging_error> c(double_merging);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
