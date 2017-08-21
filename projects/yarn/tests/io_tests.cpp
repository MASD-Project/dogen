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
#include "dogen/yarn/types/all.hpp"
#include "dogen/yarn/io/all_io.hpp"
#include "dogen/yarn/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("yarn");
const std::string test_suite("io_tests");

}

using namespace dogen::yarn::helpers;
using namespace dogen::yarn::meta_model;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(io_tests)

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");

    test_io<origin_types_generator>();
    test_io<name_tree_generator>();
    test_io<node_generator>();
    test_io<attribute_generator>();
    test_io<name_generator>();
    test_io<builtin_generator>();
    test_io<enumerator_generator>();
    test_io<enumeration_generator>();
    test_io<module_generator>();
    test_io<object_generator>();
    test_io<concept_generator>();
    test_io<endomodel_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
