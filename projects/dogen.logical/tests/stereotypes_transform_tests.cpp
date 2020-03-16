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
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/structural/object_io.hpp"
#include "dogen.logical/test/mock_context_factory.hpp"
#include "dogen.logical/test/mock_model_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/entities/static_stereotypes.hpp"
#include "dogen.logical/types/transforms/stereotypes_transform.hpp"

namespace {

using dogen::logical::test::mock_model_factory;
const mock_model_factory::flags flags;
const mock_model_factory factory(flags);

const std::string test_module("dogen.logical.tests");
const std::string test_suite("stereotypes_transform_tests");
const std::string version_name("version");
const std::string missing_identity("Identity must have at least");
const std::string no_leaves("Type marked as visitable but has no leaves");

}

using dogen::logical::entities::static_stereotypes;
using dogen::utility::test::contains_checker;
using dogen::logical::transforms::transformation_error;
using dogen::utility::test::asserter;
using dogen::logical::transforms::stereotypes_transform;
using dogen::logical::test::mock_context_factory;

BOOST_AUTO_TEST_SUITE(stereotypes_transform_tests)

BOOST_AUTO_TEST_CASE(expanding_non_visitable_type_does_nothing) {
    SETUP_TEST_LOG_SOURCE("expanding_non_visitable_type_does_nothing");

    auto a(factory.make_single_type_model());
    BOOST_REQUIRE(a.structural_elements().objects().size() == 1);
    BOOST_CHECK(a.structural_elements().objects().begin()->second->contained_by().empty());
    BOOST_REQUIRE(a.structural_elements().modules().empty());
    BOOST_REQUIRE(a.structural_elements().builtins().empty());
    BOOST_REQUIRE(a.structural_elements().enumerations().empty());
    BOOST_REQUIRE(a.structural_elements().object_templates().empty());
    BOOST_REQUIRE(a.structural_elements().visitors().empty());

    stereotypes_transform::apply(mock_context_factory::make(), a);

    BOOST_CHECK(a.structural_elements().objects().size() == 1);
    BOOST_CHECK(a.structural_elements().visitors().empty());
    BOOST_CHECK(a.structural_elements().modules().empty());
    BOOST_CHECK(a.structural_elements().builtins().empty());
    BOOST_CHECK(a.structural_elements().enumerations().empty());
    BOOST_CHECK(a.structural_elements().object_templates().empty());
    BOOST_CHECK(a.structural_elements().visitors().empty());
}

BOOST_AUTO_TEST_CASE(visitable_object_with_no_leaves_throws) {
    SETUP_TEST_LOG_SOURCE("visitable_object_with_no_leaves_throws");

    auto m(factory.make_single_type_model());
    BOOST_REQUIRE(m.structural_elements().objects().size() == 1);
    auto& o(*(m.structural_elements().objects().begin()->second));
    o.static_stereotypes().push_back(static_stereotypes::visitable);
    o.is_visitation_root(true);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto ctx(mock_context_factory::make());
    contains_checker<transformation_error> c(no_leaves);
    BOOST_CHECK_EXCEPTION(
        stereotypes_transform::apply(ctx, m), transformation_error, c);
}

BOOST_AUTO_TEST_CASE(visitable_object_has_visitor_injected) {
    SETUP_TEST_LOG_SOURCE("visitable_object_has_visitor_injected");

    auto m(factory.object_with_parent_in_the_same_model());
    BOOST_REQUIRE(m.structural_elements().objects().size() == 2);
    for (auto& pair : m.structural_elements().objects()) {
        const auto& n(pair.second->name());
        if (factory.is_type_name_n(1, n)) {
            auto& o(*pair.second);
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();
            o.is_visitation_root(true);
            o.static_stereotypes().push_back(static_stereotypes::visitable);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "before: " << m;

    const auto ctx(mock_context_factory::make());
    stereotypes_transform::apply(ctx, m);
    BOOST_LOG_SEV(lg, debug) << "after: " << m;

    BOOST_CHECK(m.structural_elements().objects().size() == 2);
    bool type_one(false);
    for (const auto& pair : m.structural_elements().objects()) {
        const auto& n(pair.second->name());
        if (factory.is_type_name_n(1, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified().dot();
            type_one = true;
        }
    }
    BOOST_CHECK(type_one);

    BOOST_REQUIRE(m.structural_elements().visitors().size() == 1);
    const auto v(*(m.structural_elements().visitors().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "found visitor: " << v.name().qualified().dot();
    BOOST_CHECK(factory.is_type_name_n_visitor(1, v.name()));
    BOOST_REQUIRE(v.visits().size() == 1);
    BOOST_CHECK(factory.is_type_name_n(0, v.visits().front()));
}

BOOST_AUTO_TEST_SUITE_END()
