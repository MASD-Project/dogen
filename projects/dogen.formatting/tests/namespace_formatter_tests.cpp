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
#include "dogen.formatting/types/indent_filter.hpp"
#include "dogen.utility/test/asserter.hpp"
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/io/list_io.hpp"
#include "dogen.utility/io/unordered_map_io.hpp"
#include "dogen.formatting/types/cpp/namespace_formatter.hpp"

namespace {

const std::string test_module("formatting");
const std::string test_suite("namespace_formatter_tests");
const std::string empty;

const std::string default_configuration_begin(R"(namespace abc {
)");

}

using namespace dogen::utility::test;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(namespace_formatter_tests)

BOOST_AUTO_TEST_CASE(default_configuration_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("default_configuration_generates_expected_cpp_namespaces");

    const std::string simple_input("abc");
    BOOST_LOG_SEV(lg, debug) << "Input: " << simple_input;

    std::ostringstream s;
    dogen::formatting::cpp::namespace_formatter nsf;
    nsf.format_begin(s, simple_input);
    const auto beg(s.str());
    BOOST_LOG_SEV(lg, debug) << "Begin: '" << beg << "'";
    BOOST_CHECK(beg == default_configuration_begin);
    s.str("");

    nsf.format_end(s, simple_input);
    const auto end(s.str());
    BOOST_LOG_SEV(lg, debug) << "End: '" << end << "'";;
    BOOST_CHECK(end == "}");
}

BOOST_AUTO_TEST_SUITE_END()
