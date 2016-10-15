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
#include "dogen/yarn.dia/types/all.hpp"
#include "dogen/yarn.dia/io/all_io.hpp"
#include "dogen/yarn.dia/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("yarn.dia");
const std::string test_suite("equality_tests");

}

using namespace dogen::yarn::dia;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(equality_tests)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");

    test_equality<repository_generator>();
    test_equality<yarn_object_types_generator>();
    test_equality<dia_object_types_generator>();
    test_equality<processed_object_generator>();
    test_equality<processed_attribute_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
