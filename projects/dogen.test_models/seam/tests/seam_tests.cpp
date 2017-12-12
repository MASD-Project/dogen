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
#include "dogen.utility/test/asserter.hpp"
#include "dogen.utility/test/logging.hpp"
#include "simple_template.hpp"
#include "complex_template.hpp"

namespace  {

const std::string test_module("seam");
const std::string test_suite("seam_tests");

const std::string simple_template_output(R"(this is a simple template
)");
const std::string complex_template_output(R"(this is a relatively more
    complex (0)
    complex (1)
    complex (2)

  template
)");

}

using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(seam_tests)

BOOST_AUTO_TEST_CASE(simple_template_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("simple_template_produces_expected_output");

    std::ostringstream s;
    simple_template(s);
    const auto r(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(simple_template_output, r));
}

BOOST_AUTO_TEST_CASE(complex_template_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("complex_template_produces_expected_output");

    std::ostringstream s;
    complex_template(s);
    const auto r(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(complex_template_output, r));
}

BOOST_AUTO_TEST_SUITE_END()
