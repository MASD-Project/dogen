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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/types/profiler.hpp"
#include "dogen/yarn.dia/io/profile_io.hpp"
#include "dogen/yarn.dia/test/mock_processed_object_factory.hpp"

using namespace dogen::yarn::dia;
using dogen::utility::test::asserter;

namespace  {

const std::string test_module("yarn.dia");
const std::string test_suite("profiler_tests");

const std::string us_str_1("AStereoType");
const std::string us_str_2("AStereoType,Another");
const std::string us_str_3("AStereoType,Another,third stereotype");

const std::string us_1("AStereoType");
const std::string us_2("Another");
const std::string us_3("third stereotype");

unsigned int stereotype_count(const profile& p) {
    unsigned int r(0);

    if (p.is_enumeration()) ++r;
    if (p.is_exception()) ++r;
    if (p.is_value_object()) ++r;
    if (p.is_service()) ++r;
    if (p.is_non_generatable()) ++r;

    return r;
}

unsigned int type_count(const profile& p) {
    unsigned int r(0);

    if (p.is_uml_class()) ++r;
    if (p.is_uml_large_package()) ++r;
    if (p.is_uml_generalization()) ++r;
    if (p.is_uml_association()) ++r;
    if (p.is_uml_note()) ++r;
    if (p.is_uml_message()) ++r;
    if (p.is_uml_realization()) ++r;

    return r;
}

unsigned int total_count(const profile& p) {
    return stereotype_count(p) + type_count(p);
}

bool is_valid_uml_class(const profile& p) {
    return p.is_uml_class() && type_count(p) == 1;
}

}

using dogen::yarn::dia::test::mock_processed_object_factory;

BOOST_AUTO_TEST_SUITE(profiler_tests)

BOOST_AUTO_TEST_CASE(uml_class_with_no_stereotypes_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_class_with_no_stereotypes_transforms_into_expected_profile");

    const auto o(mock_processed_object_factory::make_class());
    dogen::yarn::dia::profiler profiler;
    const auto p(profiler.generate(o));

    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    BOOST_CHECK(p.is_uml_class());
    BOOST_CHECK(total_count(p) == 2);
}

BOOST_AUTO_TEST_CASE(uml_note_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_note_transforms_into_expected_profile");

    const auto o(mock_processed_object_factory::make_uml_note());
    dogen::yarn::dia::profiler profiler;
    const auto p(profiler.generate(o));

    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    BOOST_CHECK(p.is_uml_note());
    BOOST_CHECK(total_count(p) == 1);
}

BOOST_AUTO_TEST_CASE(uml_large_package_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_large_package_transforms_into_expected_profile");

    const auto o(mock_processed_object_factory::make_large_package());
    dogen::yarn::dia::profiler profiler;
    const auto p(profiler.generate(o));

    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    BOOST_CHECK(p.is_uml_large_package());
    BOOST_CHECK(total_count(p) == 1);
}

BOOST_AUTO_TEST_CASE(uml_generalization_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_generalization_transforms_into_expected_profile");

    const auto a(mock_processed_object_factory::make_generalization());
    dogen::yarn::dia::profiler profiler;
    const auto p(profiler.generate(a[0]));

    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    BOOST_CHECK(p.is_uml_generalization());
    BOOST_CHECK(total_count(p) == 1);
}

BOOST_AUTO_TEST_CASE(uml_association_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_association_transforms_into_expected_profile");

    const auto a(mock_processed_object_factory::make_association());
    dogen::yarn::dia::profiler profiler;
    const auto p(profiler.generate(a[2]));

    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    BOOST_CHECK(p.is_uml_association());
    BOOST_CHECK(total_count(p) == 1);
}

BOOST_AUTO_TEST_CASE(uml_message_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_message_transforms_into_expected_profile");

    const auto o(mock_processed_object_factory::make_uml_message());
    dogen::yarn::dia::profiler profiler;
    const auto p(profiler.generate(o));

    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    BOOST_CHECK(p.is_uml_message());
    BOOST_CHECK(total_count(p) == 1);
}

BOOST_AUTO_TEST_CASE(uml_realization_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("uml_realization_transforms_into_expected_profile");

    const auto a(mock_processed_object_factory::make_realization());
    dogen::yarn::dia::profiler profiler;
    const auto p(profiler.generate(a[0]));

    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    BOOST_CHECK(p.is_uml_realization());
    BOOST_CHECK(total_count(p) == 1);
}

BOOST_AUTO_TEST_CASE(stereotyped_class_transforms_into_expected_profile) {
    SETUP_TEST_LOG_SOURCE("stereotyped_class_transforms_into_expected_profile");

    std::string s("enumeration");
    auto o(mock_processed_object_factory::make_class(0, s));
    dogen::yarn::dia::profiler profiler;
    auto p(profiler.generate(o));

    BOOST_LOG_SEV(lg, debug) << "actual 1:" << p;
    BOOST_CHECK(is_valid_uml_class(p));
    BOOST_CHECK(stereotype_count(p) == 1);
    BOOST_CHECK(p.is_enumeration());

    s = "exception, enumeration";
    o = mock_processed_object_factory::make_class(0, s);
    p = profiler.generate(o);

    BOOST_LOG_SEV(lg, debug) << "actual 2:" << p;
    BOOST_CHECK(is_valid_uml_class(p));
    BOOST_CHECK(stereotype_count(p) == 2);
    BOOST_CHECK(p.is_exception());
    BOOST_CHECK(p.is_enumeration());

    s = "nongeneratable, visitable, immutable, fluent";
    o = mock_processed_object_factory::make_class(0, s);
    p = profiler.generate(o);

    BOOST_LOG_SEV(lg, debug) << "actual 3:" << p;
    BOOST_CHECK(is_valid_uml_class(p));
    BOOST_CHECK(stereotype_count(p) == 2);
    BOOST_CHECK(p.is_non_generatable());
}

BOOST_AUTO_TEST_CASE(unknown_stereotypes_are_added_to_list) {
    SETUP_TEST_LOG_SOURCE("unknown_stereotypes_are_added_to_list");

    auto o(mock_processed_object_factory::make_class(0, us_str_1));
    dogen::yarn::dia::profiler profiler;
    auto p = profiler.generate(o);
    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    BOOST_REQUIRE(p.unknown_stereotypes().size() == 1);
    BOOST_CHECK(p.unknown_stereotypes().front() == us_1);

    o = mock_processed_object_factory::make_class(0, us_str_2);
    p = profiler.generate(o);
    BOOST_REQUIRE(p.unknown_stereotypes().size() == 2);
    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    BOOST_CHECK(p.unknown_stereotypes().front() == us_1);
    BOOST_CHECK(p.unknown_stereotypes().back() == us_2);

    o = mock_processed_object_factory::make_class(0, us_str_3);
    p = profiler.generate(o);
    BOOST_REQUIRE(p.unknown_stereotypes().size() == 3);
    BOOST_LOG_SEV(lg, debug) << "actual:" << p;
    auto i(p.unknown_stereotypes().begin());
    BOOST_CHECK(*i++ == us_1);
    BOOST_CHECK(*i++ == us_2);
    BOOST_CHECK(*i == us_3);
}

BOOST_AUTO_TEST_SUITE_END()
