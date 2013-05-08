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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia_to_sml/types/processed_object.hpp"
#include "dogen/dia_to_sml/types/profiler.hpp"
#include "dogen/dia_to_sml/types/profiling_error.hpp"
#include "dogen/dia_to_sml/io/context_io.hpp"
#include "dogen/dia_to_sml/io/processed_object_io.hpp"
#include "dogen/dia_to_sml/test/mock_processed_object_factory.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::dia_to_sml;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("dia_to_sml");
const std::string test_suite("profiler_spec");

bool has_stereotypes(const object_profile& op) {
    return
        op.is_enumeration() ||
        op.is_exception() ||
        op.is_entity() ||
        op.is_value() ||
        op.is_service() ||
        op.is_non_generatable() ||
        op.is_versioned() ||
        op.is_keyed() ||
        op.is_visitable() ||
        op.is_immutable() ||
        op.is_fluent() ||
        op.is_aggregate_root() ||
        op.is_string_table();
}

}

using dogen::utility::test::contains_checker;
using dogen::dia_to_sml::test::mock_processed_object_factory;

BOOST_AUTO_TEST_SUITE(profiler)

BOOST_AUTO_TEST_CASE(uml_class_with_no_stereotypes_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_no_stereotypes_transforms_into_expected_profile");

    const auto o(mock_processed_object_factory::build_class(0));
    dogen::dia_to_sml::profiler p;
    const auto op(p.profile(o));

    BOOST_CHECK(op.is_uml_class());
    BOOST_CHECK(!op.is_uml_large_package());
    BOOST_CHECK(!op.is_uml_generalization());
    BOOST_CHECK(!op.is_uml_association());
    BOOST_CHECK(!op.is_uml_note());
    BOOST_CHECK(!op.is_uml_message());
    BOOST_CHECK(!op.is_uml_realization());
    BOOST_CHECK(!has_stereotypes(op));
}

BOOST_AUTO_TEST_CASE(uml_note_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_note_transforms_into_expected_profile");

    const auto o(mock_processed_object_factory::build_uml_note(0));
    dogen::dia_to_sml::profiler p;
    const auto op(p.profile(o));

    BOOST_CHECK(!op.is_uml_class());
    BOOST_CHECK(!op.is_uml_large_package());
    BOOST_CHECK(!op.is_uml_generalization());
    BOOST_CHECK(!op.is_uml_association());
    BOOST_CHECK(op.is_uml_note());
    BOOST_CHECK(!op.is_uml_message());
    BOOST_CHECK(!op.is_uml_realization());
    BOOST_CHECK(!has_stereotypes(op));
}

BOOST_AUTO_TEST_CASE(uml_large_package_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_large_package_transforms_into_expected_profile");

    const auto o(mock_processed_object_factory::build_large_package(0));
    dogen::dia_to_sml::profiler p;
    const auto op(p.profile(o));

    BOOST_CHECK(!op.is_uml_class());
    BOOST_CHECK(op.is_uml_large_package());
    BOOST_CHECK(!op.is_uml_generalization());
    BOOST_CHECK(!op.is_uml_association());
    BOOST_CHECK(!op.is_uml_note());
    BOOST_CHECK(!op.is_uml_message());
    BOOST_CHECK(!op.is_uml_realization());
    BOOST_CHECK(!has_stereotypes(op));
}

BOOST_AUTO_TEST_CASE(uml_generalization_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_generalization_transforms_into_expected_profile");

    const auto a(mock_processed_object_factory::build_generalization(0));
    dogen::dia_to_sml::profiler p;
    const auto op(p.profile(a[0]));

    BOOST_CHECK(!op.is_uml_class());
    BOOST_CHECK(!op.is_uml_large_package());
    BOOST_CHECK(op.is_uml_generalization());
    BOOST_CHECK(!op.is_uml_association());
    BOOST_CHECK(!op.is_uml_note());
    BOOST_CHECK(!op.is_uml_message());
    BOOST_CHECK(!op.is_uml_realization());
    BOOST_CHECK(!has_stereotypes(op));
}

BOOST_AUTO_TEST_CASE(uml_association_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_association_transforms_into_expected_profile");

    const auto a(mock_processed_object_factory::build_association(0));
    dogen::dia_to_sml::profiler p;
    const auto op(p.profile(a[2]));

    BOOST_CHECK(!op.is_uml_class());
    BOOST_CHECK(!op.is_uml_large_package());
    BOOST_CHECK(!op.is_uml_generalization());
    BOOST_CHECK(op.is_uml_association());
    BOOST_CHECK(!op.is_uml_note());
    BOOST_CHECK(!op.is_uml_message());
    BOOST_CHECK(!op.is_uml_realization());
    BOOST_CHECK(!has_stereotypes(op));
}

BOOST_AUTO_TEST_CASE(uml_message_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_message_transforms_into_expected_profile");

    const auto o(mock_processed_object_factory::build_uml_message(0));
    dogen::dia_to_sml::profiler p;
    const auto op(p.profile(o));

    BOOST_CHECK(!op.is_uml_class());
    BOOST_CHECK(!op.is_uml_large_package());
    BOOST_CHECK(!op.is_uml_generalization());
    BOOST_CHECK(!op.is_uml_association());
    BOOST_CHECK(!op.is_uml_note());
    BOOST_CHECK(op.is_uml_message());
    BOOST_CHECK(!op.is_uml_realization());
    BOOST_CHECK(!has_stereotypes(op));
}

BOOST_AUTO_TEST_CASE(uml_realization_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_realization_transforms_into_expected_profile");

    const auto a(mock_processed_object_factory::build_realization(0));
    dogen::dia_to_sml::profiler p;
    const auto op(p.profile(a[0]));

    BOOST_CHECK(!op.is_uml_class());
    BOOST_CHECK(!op.is_uml_large_package());
    BOOST_CHECK(!op.is_uml_generalization());
    BOOST_CHECK(!op.is_uml_association());
    BOOST_CHECK(!op.is_uml_note());
    BOOST_CHECK(!op.is_uml_message());
    BOOST_CHECK(op.is_uml_realization());
    BOOST_CHECK(!has_stereotypes(op));
}

BOOST_AUTO_TEST_SUITE_END()
