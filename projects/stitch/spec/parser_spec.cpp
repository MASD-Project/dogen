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
#include "dogen/stitch/io/text_template_io.hpp"
#include "dogen/stitch/types/parser.hpp"

namespace {

const std::string empty;
const std::string test_module("stitch");
const std::string test_suite("parser_spec");

const std::string only_text_content_in_single_line("some text content");

dogen::stitch::text_template parse(const std::string& s) {
    dogen::stitch::parser p;
    return p.parse(s);
}

}

BOOST_AUTO_TEST_SUITE(parser)

BOOST_AUTO_TEST_CASE(empty_string_results_in_empty_template) {
    SETUP_TEST_LOG_SOURCE("empty_string_results_in_empty_template");
    const auto tt(parse(empty));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;
    BOOST_CHECK(tt.content().empty());
}

BOOST_AUTO_TEST_CASE(string_with_only_text_content_in_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("string_with_only_text_content_in_single_line_results_in_expected_template");
    const auto tt(parse(only_text_content_in_single_line));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_REQUIRE(tt.content().size() == 1);
    const auto& block(tt.content().front());
    const auto& mcb(boost::get<dogen::stitch::mixed_content_block>(block));

    BOOST_REQUIRE(mcb.content().size() == 1);
    const auto& line(mcb.content().front());
    const auto s(boost::get<std::string>(line));
    BOOST_CHECK(s == only_text_content_in_single_line);
}

BOOST_AUTO_TEST_SUITE_END()
