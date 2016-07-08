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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/dia/types/all.hpp"
#include "dogen/dia/io/all_io.hpp"
#include "dogen/dia/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("dia");
const std::string test_suite("equality_tests");

}

using namespace dogen::dia;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(equality_tests)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");

    test_equality<attribute_generator>();
    test_equality<boolean_generator>();
    test_equality<child_node_generator>();
    test_equality<color_generator>();
    test_equality<composite_generator>();
    test_equality<connection_generator>();
    test_equality<diagram_data_generator>();
    test_equality<diagram_generator>();
    test_equality<enumeration_generator>();
    test_equality<font_generator>();
    test_equality<integer_generator>();
    test_equality<layer_generator>();
    test_equality<object_generator>();
    test_equality<point_generator>();
    test_equality<real_generator>();
    test_equality<rectangle_generator>();
    test_equality<string_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
