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
#include <unordered_map>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/sml/types/all.hpp"
#include "dogen/sml/io/all_io.hpp"
#include "dogen/sml/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("sml");
const std::string test_suite("equality_spec");

}

using namespace dogen::sml;
using dogen::utility::test::asserter;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(equality)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");

    test_equality<category_types_generator>();
    test_equality<generation_types_generator>();
    test_equality<meta_types_generator>();
    test_equality<model_generator>();
    test_equality<nested_qname_generator>();
    test_equality<pod_generator>();
    test_equality<pod_types_generator>();
    test_equality<property_generator>();
    test_equality<qname_generator>();
    test_equality<value_generator>();
    test_equality<entity_generator>();
    test_equality<service_generator>();
    test_equality<module_generator>();
    test_equality<repository_generator>();
    test_equality<factory_generator>();
    test_equality<concept_generator>();
}

BOOST_AUTO_TEST_CASE(moving_a_value_results_in_an_equal_object) {
    SETUP_TEST_LOG_SOURCE("moving_a_value_results_in_an_equal_object");

    value_generator g;
    const auto e(g());
    auto tmp(e);
    const auto a(std::move(tmp));
    BOOST_CHECK(asserter::assert_object(e, a));

    std::unordered_map<dogen::sml::qname, dogen::sml::value> map;
    map.insert(std::make_pair(e.name(), e));
    BOOST_LOG_SEV(lg, debug) << "map: " << map;
    BOOST_CHECK(asserter::assert_object(e, map.begin()->second));
}

BOOST_AUTO_TEST_CASE(assigning_a_value_results_in_an_equal_object) {
    SETUP_TEST_LOG_SOURCE("assigning_a_value_results_in_an_equal_object");

    value_generator g;
    const auto e(g());
    dogen::sml::value a;
    BOOST_CHECK(!asserter::assert_object(e, a));

    a = e;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_SUITE_END()
