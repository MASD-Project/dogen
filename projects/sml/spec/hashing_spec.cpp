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
#include "dogen/sml/hash/all_hash.hpp"
#include "dogen/sml/io/all_io.hpp"
#include "dogen/sml/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("sml");
const std::string test_suite("hashing_spec");

}

using namespace dogen::sml;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(hashing)

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");

    test_hashing<generation_types_generator>();
    // FIXME: bug in composition?
    // test_hashing<nested_qname_generator>();
    // test_hashing<node_generator>();
    test_hashing<property_generator>();
    test_hashing<qname_generator>();
    test_hashing<primitive_generator>();
    test_hashing<enumerator_generator>();
    test_hashing<enumeration_generator>();
    test_hashing<module_generator>();
    test_hashing<object_generator>();
    test_hashing<concept_generator>();
    test_hashing<concept_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
