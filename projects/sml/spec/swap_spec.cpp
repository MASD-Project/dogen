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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/sml/types/all.hpp"
#include "dogen/sml/io/all_io.hpp"
#include "dogen/sml/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("sml");
const std::string test_suite("swap_spec");

}

using namespace dogen::sml;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(swap)

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_swap");

    test_swap<category_types_generator>();
    test_swap<entry_generator>();
    test_swap<enumeration_generator>();
    test_swap<enumerator_generator>();
    test_swap<exception_generator>();
    test_swap<generation_types_generator>();
    test_swap<meta_types_generator>();
    test_swap<model_generator>();
    test_swap<nested_qname_generator>();
    test_swap<package_generator>();
    test_swap<pod_generator>();
    test_swap<pod_types_generator>();
    test_swap<primitive_generator>();
    test_swap<property_generator>();
    test_swap<qname_generator>();
    test_swap<reference_generator>();
    test_swap<string_table_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
