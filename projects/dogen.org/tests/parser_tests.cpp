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
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"

namespace {

const std::string empty;
const std::string test_module("dogen.org.tests");
const std::string test_suite("parser_tests");

const std::string only_text_content_in_single_line("some text content");
const std::string only_text_content_muti_line(R"(some text content
other text content)");

const std::string inline_standard_control_block(R"(<#+ single line #>)");
const std::string empty_standard_control_block(R"(<#+
#>)");

const std::string single_line_standard_control_block(R"(<#+
single line
#>)");

// dogen::templating::stitch::text_template_body
// parse(const std::string& s) {
//     dogen::templating::stitch::parser p;
//     return p.parse(s);
// }

}

BOOST_AUTO_TEST_SUITE(stitch_parser_tests)

BOOST_AUTO_TEST_CASE(empty_string_results_in_empty_template) {
    SETUP_TEST_LOG_SOURCE("empty_string_results_in_empty_template");
    // const auto body(parse(empty));
    // BOOST_CHECK(body.lines().empty());
}

BOOST_AUTO_TEST_SUITE_END()
