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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/helpers/resolution_error.hpp"
#include "dogen/yarn/types/transforms/merge_transform.hpp"
#include "dogen/yarn/types/helpers/indexer.hpp"
#include "dogen/yarn/types/helpers/indices.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/io/attribute_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/yarn/test/mock_intermediate_model_factory.hpp"
#include "dogen/yarn/types/helpers/resolver.hpp"

namespace {

const std::string test_module("yarn");
const std::string test_suite("resolver_tests");

using dogen::yarn::test::mock_intermediate_model_factory;

/*
 * FIXME: we need to update the mock factory to generate merged
 * models. for now as a quick hack, we just  used the merger.
 *
 * FIXME: all attributes have model name set and need to be manually
 * unset.
 *
 * FIXME: we followed the anti-pattern of merger with indexer. Ideally
 * the factory should generate an indexed model.
 *
 * Flag was added but does nothing yet.
 */
const mock_intermediate_model_factory::flags flags(false/*tagged*/,
    true/*merged*/, false/*resolved*/, false/*concepts_indexed*/,
    false/*attributes_indexed*/, false/*associations_indexed*/,
    true/*types parsed*/);

const mock_intermediate_model_factory factory(flags);

const auto idx = dogen::yarn::helpers::indices();

const std::string incorrect_model("Object does not belong to this model");
const std::string inconsistent_kvp("Inconsistency between key and value");
const std::string missing_target("No target model found");
const std::string too_many_targets("Only one target expected.");
const std::string undefined_type("Object has attribute with undefined type");
const std::string missing_parent("Object's parent could not be located");
const std::string incorrect_meta_type("Object has incorrect meta_type");

}

using dogen::utility::test::contains_checker;
using dogen::yarn::helpers::resolution_error;

BOOST_AUTO_TEST_SUITE(resolver_tests)

BOOST_AUTO_TEST_CASE(object_with_attribute_type_in_the_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_attribute_type_in_the_same_model_resolves_successfully");
    auto m(factory.object_with_attribute());
    BOOST_CHECK(m.objects().size() == 2);
    BOOST_CHECK(m.builtins().empty());

    for (auto& pair : m.objects()) {
        auto& o(pair.second);
        BOOST_CHECK(o.local_attributes().size() == 1 ||
            o.local_attributes().empty());
        if (o.local_attributes().size() == 1) {
            auto& t(o.local_attributes().begin()->parsed_type().current());
            t.location().model_modules().clear();
            t.id(t.simple());
        }
    }
    using dogen::yarn::helpers::indexer;
    const auto idx(indexer::index(m));

    const auto original(m);
    BOOST_LOG_SEV(lg, debug) << "original: " << original;

    using dogen::yarn::helpers::resolver;
    resolver::resolve(idx, m);
    BOOST_LOG_SEV(lg, debug) << "resolved: " << m;
    BOOST_CHECK(m != original);

    bool found(false);
    for (const auto pair : m.objects()) {
        const auto& n(pair.second.name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();
            found = true;

            const auto& o(pair.second);
            BOOST_CHECK(o.local_attributes().size() == 1);
            const auto& prop(o.local_attributes().front());
            BOOST_LOG_SEV(lg, debug) << "attribute: " << prop;
            BOOST_CHECK(factory.is_type_name_n(1, prop.parsed_type().current()));
            BOOST_CHECK(factory.is_model_n(0, prop.parsed_type().current()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_attribute_type_in_different_model_results_in_successful_merge) {
    SETUP_TEST_LOG_SOURCE("object_with_attribute_type_in_different_model_results_in_successful_merge");

    const auto m(factory.object_with_attribute_type_in_different_model());

    using dogen::yarn::transforms::merge_transform;
    const std::list<dogen::yarn::intermediate_model> refs = { m[1] };
    auto combined(merge_transform::transform(m[0], refs));
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.builtins().empty());

    using dogen::yarn::helpers::indexer;
    const auto idx(indexer::index(combined));

    using dogen::yarn::helpers::resolver;
    resolver::resolve(idx, combined);

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.second.name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();
            found = true;

            const auto& o(pair.second);
            BOOST_CHECK(o.local_attributes().size() == 1);
            const auto& prop(o.local_attributes().front());
            BOOST_LOG_SEV(lg, debug) << "attribute: " << prop;

            BOOST_CHECK(
                factory.is_type_name_n(1, prop.parsed_type().current()));
            BOOST_CHECK(factory.is_model_n(1, prop.parsed_type().current()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_missing_attribute_type_throws) {
    SETUP_TEST_LOG("object_with_missing_attribute_type_throws");

    auto m(factory.object_with_missing_attribute_type());
    using dogen::yarn::helpers::resolver;
    contains_checker<resolution_error> c(undefined_type);
    BOOST_CHECK_EXCEPTION(resolver::resolve(idx, m), resolution_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_parent_in_the_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_parent_in_the_same_model_resolves_successfully");
    using dogen::yarn::transforms::merge_transform;
    const auto m(factory.object_with_parent_in_the_same_model());

    const std::list<dogen::yarn::intermediate_model> refs;
    auto combined(merge_transform::transform(m, refs));
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.builtins().empty());

    using dogen::yarn::helpers::resolver;
    resolver::resolve(idx, combined);

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.second.name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();
            found = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.id();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(0, pn));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_parent_in_different_models_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_parent_in_different_models_resolves_successfully");


    const auto m(factory.object_with_parent_in_different_models());

    using dogen::yarn::transforms::merge_transform;
    const std::list<dogen::yarn::intermediate_model> refs = { m[1] };
    auto combined(merge_transform::transform(m[0], refs));
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.builtins().empty());

    using dogen::yarn::helpers::resolver;
    resolver::resolve(idx, combined);

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.second.name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();
            found = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.id();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(1, pn));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_in_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_third_degree_parent_in_same_model_resolves_successfully");
    const auto m(factory.object_with_third_degree_parent_in_same_model());
    using dogen::yarn::transforms::merge_transform;
    const std::list<dogen::yarn::intermediate_model> refs;

    auto combined(merge_transform::transform(m, refs));
    BOOST_CHECK(combined.objects().size() == 4);
    BOOST_CHECK(combined.builtins().empty());

    using dogen::yarn::helpers::resolver;
    resolver::resolve(idx, combined);

    bool found_one(false);
    bool found_two(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.second.name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();
            found_one = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.id();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(0, pn));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();
            found_two = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.id();
            BOOST_CHECK(factory.is_type_name_n(2, pn));
            BOOST_CHECK(factory.is_model_n(0, pn));
        }
    }
    BOOST_CHECK(found_one);
    BOOST_CHECK(found_two);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_missing_within_single_model_throws) {
    SETUP_TEST_LOG("object_with_third_degree_parent_missing_within_single_model_throws");
    auto m(factory.object_with_third_degree_parent_missing());
    contains_checker<resolution_error> c(missing_parent);
    using dogen::yarn::helpers::resolver;
    BOOST_CHECK_EXCEPTION(resolver::resolve(idx, m), resolution_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_in_different_models_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_third_degree_parent_in_different_models_resolves_successfully");

    const auto a(factory.object_with_third_degree_parent_in_different_models());
    const std::list<dogen::yarn::intermediate_model>
        refs = { a[1], a[2], a[3] };

    using dogen::yarn::transforms::merge_transform;
    auto combined(merge_transform::transform(a[0], refs));
    BOOST_CHECK(combined.objects().size() == 4);
    BOOST_CHECK(combined.builtins().empty());

    using dogen::yarn::helpers::resolver;
    resolver::resolve(idx, combined);

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.second.name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.id();
            found = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.id();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(1, pn));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_missing_third_degree_parent_in_different_models_throws) {
    SETUP_TEST_LOG("object_with_missing_third_degree_parent_in_different_models_throws");
    using dogen::yarn::transforms::merge_transform;
    const auto a(
        factory.object_with_missing_third_degree_parent_in_different_models());

    const std::list<dogen::yarn::intermediate_model> refs = { a[1], a[2] };

    auto combined(merge_transform::transform(a[0], refs));
    using dogen::yarn::helpers::resolver;

    contains_checker<resolution_error> c(missing_parent);
    BOOST_CHECK_EXCEPTION(
        resolver::resolve(idx, combined), resolution_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
