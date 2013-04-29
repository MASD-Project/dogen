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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/types/all.hpp"
#include "dogen/sml/io/all_io.hpp"
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/sml/test_data/all_td.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/nested_qname_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/merging_error.hpp"
#include "dogen/sml/types/merger.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string test_module("sml");
const std::string test_suite("merger_spec");

const std::string invalid_model_name("INVALID");
const std::string invalid_type_name("INVALID");
const std::string zero_postfix("_0");
const std::string one_postfix("_1");
const std::string two_postfix("_2");

const std::string incorrect_model("Pod does not belong to this model");
const std::string inconsistent_kvp("Inconsistency between key and value");
const std::string missing_target("No target model found");
const std::string too_many_targets("Only one target expected.");
const std::string undefined_type("Pod has property with undefined type");
const std::string missing_parent("Pod's parent could not be located");
const std::string incorrect_meta_type("Pod has incorrect meta_type");

bool is_model_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::model_name(0) == qn.model_name();
}

bool is_model_one(const dogen::sml::qname& qn) {
    return mock_model_factory::model_name(1) == qn.model_name();
}

bool is_type_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::pod_name(0) == qn.type_name();
}

bool is_type_one(const dogen::sml::qname& qn) {
    return mock_model_factory::pod_name(1) == qn.type_name();
}

bool is_type_two(const dogen::sml::qname& qn) {
    return mock_model_factory::pod_name(2) == qn.type_name();
}

bool is_pod(const dogen::sml::qname& qn) {
    using dogen::sml::meta_types;
    return qn.meta_type() == meta_types::pod;
}

}

using dogen::utility::test::contains_checker;
using dogen::sml::merging_error;

BOOST_AUTO_TEST_SUITE(merger)

BOOST_AUTO_TEST_CASE(merging_n_distinct_models_with_one_pod_each_results_in_n_pods_in_merged_model) {
    SETUP_TEST_LOG_SOURCE("merging_n_distinct_models_with_one_pod_each_results_in_n_pods_in_merged_model");
    const unsigned int n(5);
    dogen::sml::merger mg;
    for (unsigned int i(0); i < n; ++i) {
        const auto m(mock_model_factory::build_single_pod_model(i));
        i == 0 ? mg.add_target(m) : mg.add(m);
    }

    const auto combined(mg.merge());
    BOOST_CHECK(combined.pods().size() == n);
    BOOST_CHECK(combined.primitives().empty());

    std::set<std::string> pod_names;
    std::set<std::string> model_names;
    for (const auto& pair : combined.pods()) {
        pod_names.insert(pair.first.type_name());
        model_names.insert(pair.first.model_name());
    }

    auto pod_i(pod_names.cbegin());
    auto model_i(model_names.cbegin());
    for (unsigned int i(0); i < n; ++i) {
        BOOST_LOG_SEV(lg, debug) << "pod name: " << *pod_i;
        BOOST_LOG_SEV(lg, debug) << "model name: " << *model_i;

        std::ostringstream ss;
        ss << "_" << i;
        const auto s(ss.str());
        BOOST_LOG_SEV(lg, debug) << "expected prefix: " << s;
        BOOST_CHECK(boost::ends_with(*pod_i, s));
        BOOST_CHECK(boost::ends_with(*model_i, s));
        ++pod_i;
        ++model_i;
    }
}

BOOST_AUTO_TEST_CASE(merging_empty_model_results_in_empty_merged_model) {
    SETUP_TEST_LOG("merging_empty_model_results_in_empty_merged_model");
    dogen::sml::merger mg;
    dogen::sml::model m;
    mg.add_target(m);

    const auto combined(mg.merge());
    BOOST_CHECK(combined.pods().empty());
    BOOST_CHECK(combined.primitives().empty());
}

BOOST_AUTO_TEST_CASE(type_with_incorrect_model_name_throws) {
    SETUP_TEST_LOG("type_with_incorrect_model_name_throws");
    auto m(mock_model_factory::build_single_pod_model(0));
    m.name(invalid_model_name);

    dogen::sml::merger mg;
    mg.add_target(m);

    contains_checker<merging_error> c(incorrect_model);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_CASE(type_with_inconsistent_key_value_pair_throws) {
    SETUP_TEST_LOG("type_with_inconsistent_key_value_pair_throws");

    auto m(mock_model_factory::build_multi_pod_model(0, 2));
    m.pods().begin()->second.name().type_name(invalid_type_name);

    dogen::sml::merger mg;
    mg.add_target(m);

    contains_checker<merging_error> c(inconsistent_kvp);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_CASE(not_adding_a_target_throws) {
    SETUP_TEST_LOG("not_adding_a_target_throws");

    const auto m(mock_model_factory::build_single_pod_model(0));
    dogen::sml::merger mg;
    mg.add(m);

    contains_checker<merging_error> c(missing_target);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_CASE(adding_more_than_one_target_throws) {
    SETUP_TEST_LOG("adding_more_than_one_target_throws");
    const auto m0(mock_model_factory::build_single_pod_model(0));
    const auto m1(mock_model_factory::build_single_pod_model(1));

    dogen::sml::merger mg;
    mg.add_target(m0);

    contains_checker<merging_error> c(too_many_targets);
    BOOST_CHECK_EXCEPTION(mg.add_target(m1), merging_error, c);
}

BOOST_AUTO_TEST_CASE(pod_with_property_type_in_the_same_model_results_in_successful_merge) {
    SETUP_TEST_LOG_SOURCE("pod_with_property_type_in_the_same_model_results_in_successful_merge");
    dogen::sml::merger mg;
    mg.add_target(mock_model_factory::pod_with_property());

    const auto combined(mg.merge());
    BOOST_CHECK(combined.pods().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    bool found(false);
    for (const auto pair : combined.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;

            found = true;
            BOOST_CHECK(pair.second.properties().size() == 1);
            const auto prop(pair.second.properties()[0]);
            BOOST_LOG_SEV(lg, debug) << "property: " << prop;
            BOOST_CHECK(is_type_one(prop.type_name().type()));
            BOOST_CHECK(is_model_zero(prop.type_name().type()));
            BOOST_CHECK(is_pod(prop.type_name().type()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(pod_with_property_type_in_different_model_results_in_successful_merge) {
    SETUP_TEST_LOG_SOURCE("pod_with_property_type_in_different_model_results_in_successful_merge");

    const auto m(mock_model_factory::pod_with_property_type_in_different_model());
    dogen::sml::merger mg;
    mg.add_target(m[0]);
    mg.add(m[1]);

    const auto combined(mg.merge());
    BOOST_CHECK(combined.pods().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    bool found(false);
    for (const auto pair : combined.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            found = true;
            BOOST_CHECK(pair.second.properties().size() == 1);
            const auto prop(pair.second.properties()[0]);
            BOOST_LOG_SEV(lg, debug) << "property: " << prop;

            BOOST_CHECK(is_type_one(prop.type_name().type()));
            BOOST_CHECK(is_model_one(prop.type_name().type()));
            BOOST_CHECK(is_pod(prop.type_name().type()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(pod_with_missing_property_type_throws) {
    SETUP_TEST_LOG("pod_with_missing_property_type_throws");
    dogen::sml::merger mg;
    const auto m(mock_model_factory::pod_with_missing_property_type());
    mg.add_target(m);
    contains_checker<merging_error> c(undefined_type);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_CASE(pod_with_parent_in_the_same_model_merges_successfully) {
    SETUP_TEST_LOG_SOURCE("pod_with_parent_in_the_same_model_merges_successfully");
    dogen::sml::merger mg;
    const auto m(mock_model_factory::pod_with_parent_in_the_same_model());
    mg.add_target(m);
    const auto combined(mg.merge());
    BOOST_CHECK(combined.pods().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    bool found(false);
    for (const auto pair : combined.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            found = true;
            const auto pn(pair.second.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_one(*pn));
            BOOST_CHECK(is_model_zero(*pn));
            BOOST_CHECK(is_pod(*pn));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(pod_with_parent_in_different_models_merges_successfully) {
    SETUP_TEST_LOG_SOURCE("pod_with_parent_in_different_models_merges_successfully");
    const auto m(mock_model_factory::pod_with_parent_in_different_models());
    dogen::sml::merger mg;
    mg.add_target(m[0]);
    mg.add(m[1]);
    const auto combined(mg.merge());
    BOOST_CHECK(combined.pods().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    bool found(false);
    for (const auto pair : combined.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            found = true;
            const auto pn(pair.second.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_one(*pn));
            BOOST_CHECK(is_model_one(*pn));
            BOOST_CHECK(is_pod(*pn));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(pod_with_third_degree_parent_in_same_model_merges_successfully) {
    SETUP_TEST_LOG_SOURCE("pod_with_third_degree_parent_in_same_model_merges_successfully");
    const auto m(mock_model_factory::pod_with_third_degree_parent_in_same_model());
    dogen::sml::merger mg;
    mg.add_target(m);

    const auto combined(mg.merge());
    BOOST_CHECK(combined.pods().size() == 4);
    BOOST_CHECK(combined.primitives().empty());

    bool found_one(false);
    bool found_two(false);
    for (const auto pair : combined.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            found_one = true;
            const auto pn(pair.second.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_one(*pn));
            BOOST_CHECK(is_model_zero(*pn));
            BOOST_CHECK(is_pod(*pn));
        } else if (is_type_one(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            found_two = true;
            const auto pn(pair.second.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_two(*pn));
            BOOST_CHECK(is_model_zero(*pn));
            BOOST_CHECK(is_pod(*pn));
        }
    }
    BOOST_CHECK(found_one);
    BOOST_CHECK(found_two);
}

BOOST_AUTO_TEST_CASE(pod_with_third_degree_parent_missing_within_single_model_throws) {
    SETUP_TEST_LOG("pod_with_third_degree_parent_missing_within_single_model_throws");
    dogen::sml::merger mg;
    const auto m(mock_model_factory::pod_with_third_degree_parent_missing());
    mg.add_target(m);
    contains_checker<merging_error> c(missing_parent);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_CASE(pod_with_third_degree_parent_in_different_models_merges_successfully) {
    SETUP_TEST_LOG_SOURCE("pod_with_third_degree_parent_in_different_models_merges_successfully");

    const auto a(mock_model_factory::pod_with_third_degree_parent_in_different_models());
    dogen::sml::merger mg;
    mg.add_target(a[0]);
    mg.add(a[1]);
    mg.add(a[2]);
    mg.add(a[3]);

    const auto combined(mg.merge());
    BOOST_CHECK(combined.pods().size() == 4);
    BOOST_CHECK(combined.primitives().empty());

    bool found(false);
    for (const auto pair : combined.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            found = true;
            const auto pn(pair.second.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_one(*pn));
            BOOST_CHECK(is_model_one(*pn));
            BOOST_CHECK(is_pod(*pn));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(pod_with_missing_third_degree_parent_in_different_models_throws) {
    SETUP_TEST_LOG("pod_with_missing_third_degree_parent_in_different_models_throws");
    dogen::sml::merger mg;
    const auto a(mock_model_factory::pod_with_missing_third_degree_parent_in_different_models());
    mg.add_target(a[0]);
    mg.add(a[1]);
    mg.add(a[2]);

    contains_checker<merging_error> c(missing_parent);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_CASE(pod_incorrect_meta_type_throws) {
    SETUP_TEST_LOG("pod_incorrect_meta_type_throws");

    auto m(mock_model_factory::build_single_pod_model(0));
    BOOST_CHECK(m.pods().size() == 1);

    auto p(m.pods().begin()->second);
    p.name().meta_type(dogen::sml::meta_types::primitive);
    m.pods().clear();
    m.pods().insert(std::make_pair(p.name(), p));

    dogen::sml::merger mg;
    mg.add_target(m);

    contains_checker<merging_error> c(incorrect_meta_type);
    BOOST_CHECK_EXCEPTION(mg.merge(), merging_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
