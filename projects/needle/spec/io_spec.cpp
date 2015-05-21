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
#include "dogen/utility/test/asserter.hpp"
#include "dogen/needle/core/io/jsonify_io.hpp"
#include "dogen/utility/test/logging.hpp"

namespace {

const std::string empty;
const std::string test_module("needle");
const std::string test_suite("io_spec");

}

using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(io)

BOOST_AUTO_TEST_CASE(jsonification_of_numbers_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_numbers_produces_expected_result");

    const unsigned int n(10);
    const std::string expected("10");
    std::ostringstream s;
    s << dogen::needle::core::io::jsonify(n);
    BOOST_CHECK(asserter::assert_object(s.str(), expected));
}

BOOST_AUTO_TEST_SUITE_END()
