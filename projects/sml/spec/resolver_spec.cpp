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
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/resolution_error.hpp"
#include "dogen/sml/types/merger.hpp"
#include "dogen/sml/types/resolver.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string test_module("sml");
const std::string test_suite("resolver_spec");

const std::string zero_postfix("_0");
const std::string one_postfix("_1");
const std::string two_postfix("_2");

const std::string incorrect_model("Object does not belong to this model");
const std::string inconsistent_kvp("Inconsistency between key and value");
const std::string missing_target("No target model found");
const std::string too_many_targets("Only one target expected.");
const std::string undefined_type("Object has property with undefined type");
const std::string missing_parent("Object's parent could not be located");
const std::string incorrect_meta_type("Object has incorrect meta_type");

bool is_model_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::model_name(0) == qn.model_name();
}

bool is_model_one(const dogen::sml::qname& qn) {
    return mock_model_factory::model_name(1) == qn.model_name();
}

bool is_type_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::simple_name(0) == qn.simple_name();
}

bool is_type_one(const dogen::sml::qname& qn) {
    return mock_model_factory::simple_name(1) == qn.simple_name();
}

bool is_type_two(const dogen::sml::qname& qn) {
    return mock_model_factory::simple_name(2) == qn.simple_name();
}

}

using dogen::utility::test::contains_checker;
using dogen::sml::resolution_error;

/*
 * FIXME: we need to update the mock factory to generate merged
 * models. for now as a quick hack, we just  used the merger.
 */
BOOST_AUTO_TEST_SUITE(resolver)

BOOST_AUTO_TEST_CASE(object_with_property_type_in_the_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_property_type_in_the_same_model_resolves_successfully");
    dogen::sml::merger mg;
    mg.add_target(mock_model_factory::object_with_property());

    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    dogen::sml::resolver res(combined);
    BOOST_CHECK(!res.has_resolved());
    res.resolve();
    BOOST_CHECK(res.has_resolved());

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            found = true;

            const auto& o(*pair.second);
            BOOST_CHECK(o.properties().size() == 1);
            const auto& prop(o.properties().front());
            BOOST_LOG_SEV(lg, debug) << "property: " << prop;
            BOOST_CHECK(is_type_one(prop.type().type()));
            BOOST_CHECK(is_model_zero(prop.type().type()));
            dynamic_cast<const dogen::sml::value_object&>(o);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_property_type_in_different_model_results_in_successful_merge) {
    SETUP_TEST_LOG_SOURCE("object_with_property_type_in_different_model_results_in_successful_merge");

    const auto m(mock_model_factory::object_with_property_type_in_different_model());
    dogen::sml::merger mg;
    mg.add_target(m[0]);
    mg.add(m[1]);

    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    dogen::sml::resolver res(combined);
    res.resolve();

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            found = true;

            const auto& o(*pair.second);
            BOOST_CHECK(o.properties().size() == 1);
            const auto& prop(o.properties().front());
            BOOST_LOG_SEV(lg, debug) << "property: " << prop;

            BOOST_CHECK(is_type_one(prop.type().type()));
            BOOST_CHECK(is_model_one(prop.type().type()));
            dynamic_cast<const dogen::sml::value_object&>(o);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_missing_property_type_throws) {
    SETUP_TEST_LOG("object_with_missing_property_type_throws");

    auto m(mock_model_factory::object_with_missing_property_type());
    dogen::sml::resolver res(m);
    contains_checker<resolution_error> c(undefined_type);
    BOOST_CHECK_EXCEPTION(res.resolve(), resolution_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_parent_in_the_same_model_merges_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_parent_in_the_same_model_merges_successfully");
    dogen::sml::merger mg;
    const auto m(mock_model_factory::object_with_parent_in_the_same_model());
    mg.add_target(m);
    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    dogen::sml::resolver res(combined);
    res.resolve();

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            found = true;

            const auto& o(*pair.second);
            const auto pn(o.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_one(*pn));
            BOOST_CHECK(is_model_zero(*pn));
            dynamic_cast<const dogen::sml::value_object&>(o);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_parent_in_different_models_merges_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_parent_in_different_models_merges_successfully");
    const auto m(mock_model_factory::object_with_parent_in_different_models());
    dogen::sml::merger mg;
    mg.add_target(m[0]);
    mg.add(m[1]);
    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    dogen::sml::resolver res(combined);
    res.resolve();

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            found = true;

            const auto& o(*pair.second);
            const auto pn(o.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_one(*pn));
            BOOST_CHECK(is_model_one(*pn));
            dynamic_cast<const dogen::sml::value_object&>(o);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_in_same_model_merges_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_third_degree_parent_in_same_model_merges_successfully");
    const auto m(mock_model_factory::object_with_third_degree_parent_in_same_model());
    dogen::sml::merger mg;
    mg.add_target(m);

    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 4);
    BOOST_CHECK(combined.primitives().empty());

    dogen::sml::resolver res(combined);
    res.resolve();

    bool found_one(false);
    bool found_two(false);
    for (const auto pair : combined.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            found_one = true;

            const auto& o(*pair.second);
            const auto pn(o.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_one(*pn));
            BOOST_CHECK(is_model_zero(*pn));
            dynamic_cast<const dogen::sml::value_object&>(o);
        } else if (is_type_one(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            found_two = true;

            const auto& o(*pair.second);
            const auto pn(o.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_two(*pn));
            BOOST_CHECK(is_model_zero(*pn));
            dynamic_cast<const dogen::sml::value_object&>(o);
        }
    }
    BOOST_CHECK(found_one);
    BOOST_CHECK(found_two);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_missing_within_single_model_throws) {
    SETUP_TEST_LOG("object_with_third_degree_parent_missing_within_single_model_throws");
    dogen::sml::merger mg;
    auto m(mock_model_factory::object_with_third_degree_parent_missing());
    mg.add_target(m);
    mg.merge();

    contains_checker<resolution_error> c(missing_parent);
    dogen::sml::resolver res(m);
    BOOST_CHECK_EXCEPTION(res.resolve(), resolution_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_in_different_models_merges_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_third_degree_parent_in_different_models_merges_successfully");

    const auto a(mock_model_factory::object_with_third_degree_parent_in_different_models());
    dogen::sml::merger mg;
    mg.add_target(a[0]);
    mg.add(a[1]);
    mg.add(a[2]);
    mg.add(a[3]);

    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 4);
    BOOST_CHECK(combined.primitives().empty());

    dogen::sml::resolver res(combined);
    res.resolve();

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            found = true;

            const auto& o(*pair.second);
            const auto pn(o.parent_name());
            BOOST_REQUIRE(pn);
            BOOST_LOG_SEV(lg, debug) << "parent: " << *pn;
            BOOST_CHECK(is_type_one(*pn));
            BOOST_CHECK(is_model_one(*pn));
            dynamic_cast<const dogen::sml::value_object&>(o);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_missing_third_degree_parent_in_different_models_throws) {
    SETUP_TEST_LOG("object_with_missing_third_degree_parent_in_different_models_throws");
    dogen::sml::merger mg;
    const auto a(mock_model_factory::object_with_missing_third_degree_parent_in_different_models());
    mg.add_target(a[0]);
    mg.add(a[1]);
    mg.add(a[2]);

    auto combined(mg.merge());
    dogen::sml::resolver res(combined);

    contains_checker<resolution_error> c(missing_parent);
    BOOST_CHECK_EXCEPTION(res.resolve(), resolution_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
