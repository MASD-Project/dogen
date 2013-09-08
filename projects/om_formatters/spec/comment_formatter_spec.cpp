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
#include "dogen/om/types/modeline.hpp"
#include "dogen/om_formatters/types/all.hpp"
#include "dogen/om_formatters/io/all_io.hpp"
#include "dogen/om_formatters/test_data/all_td.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string empty;
const std::string test_module("om_formatters");
const std::string test_suite("comment_formatter_spec");

const std::string c_style_empty(R"(/*
 *
 */
)");

}

using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(comment_formatter)

BOOST_AUTO_TEST_CASE(formatting_empty_string_as_a_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_empty_string_as_a_c_style_comment_produces_expected_output");

    dogen::om_formatters::comment_formatter f;
    const auto r(f.format(empty));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl << c_style_empty;
    BOOST_CHECK(r == c_style_empty);
}

BOOST_AUTO_TEST_SUITE_END()
