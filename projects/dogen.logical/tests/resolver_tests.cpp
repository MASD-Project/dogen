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
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/helpers/resolution_error.hpp"
#include "dogen.logical/types/transforms/merge_transform.hpp"
#include "dogen.logical/types/helpers/indexer.hpp"
#include "dogen.logical/types/helpers/indices.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/attribute_io.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"
#include "dogen.logical/test/mock_context_factory.hpp"
#include "dogen.logical/test/mock_model_factory.hpp"
#include "dogen.logical/types/helpers/resolver.hpp"

namespace {

const std::string test_module("dogen.logical.tests");
const std::string test_suite("resolver_tests");

using dogen::logical::test::mock_model_factory;

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
const mock_model_factory::flags flags(false/*tagged*/,
    true/*merged*/, false/*resolved*/, false/*object_templates_indexed*/,
    false/*attributes_indexed*/, false/*associations_indexed*/,
    true/*types parsed*/);

const mock_model_factory factory(flags);

const auto idx = dogen::logical::helpers::indices();

const std::string inconsistent_kvp("Inconsistency between key and value");
const std::string missing_target("No target model found");
const std::string too_many_targets("Only one target expected.");
const std::string undefined_type("Object has attribute with undefined type");
const std::string missing_parent("Object's parent could not be located");

}

using dogen::utility::test::contains_checker;
using dogen::logical::helpers::resolution_error;
using dogen::logical::helpers::indexer;
using dogen::logical::helpers::resolver;
using dogen::logical::transforms::merge_transform;
using dogen::logical::entities::model;
using dogen::logical::test::mock_context_factory;

BOOST_AUTO_TEST_SUITE(resolver_tests)

BOOST_AUTO_TEST_CASE(object_with_attribute_type_in_the_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_attribute_type_in_the_same_model_resolves_successfully");
    auto m(factory.object_with_attribute());
    BOOST_CHECK(m.structural_elements().objects().size() == 2);
    BOOST_CHECK(m.structural_elements().builtins().empty());

    for (auto& pair : m.structural_elements().objects()) {
        auto& o(*pair.second);
        BOOST_CHECK(o.local_attributes().size() == 1 ||
            o.local_attributes().empty());
        if (o.local_attributes().size() == 1) {
            auto& t(o.local_attributes().begin()->parsed_type().current());
            t.location().model_modules().clear();
            using dogen::identification::entities::qualified_representations;
            const qualified_representations
                qr(t.simple(), t.simple(), t.simple());
            t.qualified(qr);
        }
    }
    const auto idx(indexer::index(m));
    using namespace dogen::logical::entities::structural;
    const auto original([](const model& im) {
            auto r(im);
            r.structural_elements().objects().clear();
            for (const auto& pair : im.structural_elements().objects()) {
                auto o(boost::make_shared<object>(*pair.second));
                r.structural_elements().objects().insert(std::make_pair(pair.first, o));
            }
            return r;
        }(m));
    BOOST_LOG_SEV(lg, debug) << "original: " << original;

    resolver::resolve(idx, m);
    BOOST_LOG_SEV(lg, debug) << "resolved: " << m;
    BOOST_CHECK(m != original);

    bool found(false);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& n(pair.second->name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();
            found = true;

            const auto& o(*pair.second);
            BOOST_CHECK(o.local_attributes().size() == 1);
            const auto& a(o.local_attributes().front());
            BOOST_LOG_SEV(lg, debug) << "attribute: " << a;
            BOOST_CHECK(factory.is_type_name_n(1, a.parsed_type().current()));
            BOOST_CHECK(factory.is_model_n(0, a.parsed_type().current()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_attribute_type_in_different_model_results_in_successful_merge) {
    SETUP_TEST_LOG_SOURCE("object_with_attribute_type_in_different_model_results_in_successful_merge");

    dogen::logical::entities::input_model_set ms;
    const auto m(factory.object_with_attribute_type_in_different_model());
    ms.target(m[0]);
    ms.references().push_back(m[1]);
    const auto ctx(mock_context_factory::make());
    auto combined(merge_transform::apply(ctx, ms));
    BOOST_CHECK(combined.structural_elements().objects().size() == 2);
    BOOST_CHECK(combined.structural_elements().builtins().empty());

    const auto idx(indexer::index(combined));
    resolver::resolve(idx, combined);

    bool found(false);
    for (const auto& pair : combined.structural_elements().objects()) {
        const auto& n(pair.second->name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();
            found = true;

            const auto& o(*pair.second);
            BOOST_CHECK(o.local_attributes().size() == 1);
            const auto& a(o.local_attributes().front());
            BOOST_LOG_SEV(lg, debug) << "attribute: " << a;

            BOOST_CHECK(factory.is_type_name_n(1, a.parsed_type().current()));
            BOOST_CHECK(factory.is_model_n(1, a.parsed_type().current()));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_missing_attribute_type_throws) {
    SETUP_TEST_LOG("object_with_missing_attribute_type_throws");

    auto m(factory.object_with_missing_attribute_type());
    contains_checker<resolution_error> c(undefined_type);
    BOOST_CHECK_EXCEPTION(resolver::resolve(idx, m), resolution_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_parent_in_the_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_parent_in_the_same_model_resolves_successfully");
    dogen::logical::entities::input_model_set ms;
    ms.target(factory.object_with_parent_in_the_same_model());

    const auto ctx(mock_context_factory::make());
    auto combined(merge_transform::apply(ctx, ms));
    BOOST_CHECK(combined.structural_elements().objects().size() == 2);
    BOOST_CHECK(combined.structural_elements().builtins().empty());

    resolver::resolve(idx, combined);

    bool found(false);
    for (const auto& pair : combined.structural_elements().objects()) {
        const auto& n(pair.second->name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();
            found = true;

            const auto& o(*pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified().dot();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(0, pn));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_parent_in_different_models_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_parent_in_different_models_resolves_successfully");

    dogen::logical::entities::input_model_set ms;
    const auto m(factory.object_with_parent_in_different_models());
    ms.target(m[0]);
    ms.references().push_back(m[1]);
    const auto ctx(mock_context_factory::make());
    auto combined(merge_transform::apply(ctx, ms));
    BOOST_CHECK(combined.structural_elements().objects().size() == 2);
    BOOST_CHECK(combined.structural_elements().builtins().empty());

    resolver::resolve(idx, combined);

    bool found(false);
    for (const auto& pair : combined.structural_elements().objects()) {
        const auto& n(pair.second->name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();
            found = true;

            const auto& o(*pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified().dot();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(1, pn));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_in_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_third_degree_parent_in_same_model_resolves_successfully");
    dogen::logical::entities::input_model_set ms;
    ms.target(factory.object_with_third_degree_parent_in_same_model());

    const auto ctx(mock_context_factory::make());
    auto combined(merge_transform::apply(ctx, ms));
    BOOST_CHECK(combined.structural_elements().objects().size() == 4);
    BOOST_CHECK(combined.structural_elements().builtins().empty());

    resolver::resolve(idx, combined);

    bool found_one(false);
    bool found_two(false);
    for (const auto& pair : combined.structural_elements().objects()) {
        const auto& n(pair.second->name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();
            found_one = true;

            const auto& o(*pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified().dot();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(0, pn));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();
            found_two = true;

            const auto& o(*pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified().dot();
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
    using dogen::logical::helpers::resolver;
    BOOST_CHECK_EXCEPTION(resolver::resolve(idx, m), resolution_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_in_different_models_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_third_degree_parent_in_different_models_resolves_successfully");

    dogen::logical::entities::input_model_set ms;
    const auto a(factory.object_with_third_degree_parent_in_different_models());
    ms.target(a[0]);
    ms.references().push_back(a[1]);
    ms.references().push_back(a[2]);
    ms.references().push_back(a[3]);

    const auto ctx(mock_context_factory::make());
    auto combined(merge_transform::apply(ctx, ms));
    BOOST_CHECK(combined.structural_elements().objects().size() == 4);
    BOOST_CHECK(combined.structural_elements().builtins().empty());

    resolver::resolve(idx, combined);

    bool found(false);
    for (const auto& pair : combined.structural_elements().objects()) {
        const auto& n(pair.second->name());
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();
            found = true;

            const auto& o(*pair.second);
            BOOST_REQUIRE(o.parents().size() == 1);
            const auto& pn(o.parents().front());
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified().dot();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(1, pn));
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_missing_third_degree_parent_in_different_models_throws) {
    SETUP_TEST_LOG("object_with_missing_third_degree_parent_in_different_models_throws");
    dogen::logical::entities::input_model_set ms;
    const auto a(
        factory.object_with_missing_third_degree_parent_in_different_models());
    ms.target(a[0]);
    ms.references().push_back(a[1]);
    ms.references().push_back(a[2]);

    const auto ctx(mock_context_factory::make());
    auto combined(merge_transform::apply(ctx, ms));

    contains_checker<resolution_error> c(missing_parent);
    BOOST_CHECK_EXCEPTION(
        resolver::resolve(idx, combined), resolution_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
