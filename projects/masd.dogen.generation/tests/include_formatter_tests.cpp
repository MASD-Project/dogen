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
// #include <boost/test/unit_test.hpp>
// #include "masd.dogen.extraction/types/indent_filter.hpp"
// #include "masd.dogen.utility/types/test/logging.hpp"
// #include "masd.dogen.utility/types/io/list_io.hpp"
// #include "masd.dogen.utility/types/filesystem/path.hpp"
// #include "masd.dogen.utility/types/io/unordered_map_io.hpp"
// #include "masd.dogen.utility/types/test/asserter.hpp"
// #include "masd.dogen.extraction/types/cpp/include_formatter.hpp"

// namespace {

// const std::string empty;
// const std::string test_module("masd.dogen.extraction.tests");
// const std::string test_suite("include_formatter_tests");
// const auto empty_includes(std::list<std::string>{});

// const std::string with_includes(R"(#include <win32/system_inc_1>
// #include <unix/system_inc_2>
// #include "user_inc_1"
// #include "user_inc_2"
// )");

// }

// using namespace masd::dogen::utility::test;
// using masd::dogen::utility::test::asserter;

// BOOST_AUTO_TEST_SUITE(include_formatter_tests)

// BOOST_IGNORE_AUTO_TEST_CASE(non_empty_includes_produces_expected_preprocessor_includes) {
//     SETUP_TEST_LOG_SOURCE("non_empty_includes_produces_expected_preprocessor_includes");
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

//     std::list<std::string> includes;
//     // FIXME: not using windows formatting for now, problems with
//     // FIXME: boost path.
//     // i.system().push_back("win32\\system_inc_1");
//     includes.push_back("<win32/system_inc_1>");
//     includes.push_back("<unix/system_inc_2>");
//     includes.push_back("\"user_inc_1\"");
//     includes.push_back("\"user_inc_2\"");

//     std::ostringstream s;
//     boost::iostreams::filtering_ostream fo;
//     masd::dogen::extraction::indent_filter::push(fo, 4);
//     fo.push(s);

//     masd::dogen::extraction::cpp::include_formatter f;
//     f.format(fo, includes);
//     BOOST_CHECK(asserter::assert_equals_string(with_includes, s.str()));
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
// }

// BOOST_IGNORE_AUTO_TEST_CASE(empty_includes_produces_no_preprocessor_includes) {
//     SETUP_TEST_LOG_SOURCE("empty_includes_produces_no_preprocessor_includes");
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

//     std::ostringstream s;
//     boost::iostreams::filtering_ostream fo;
//     masd::dogen::extraction::indent_filter::push(fo, 4);
//     fo.push(s);

//     masd::dogen::extraction::cpp::include_formatter f;
//     f.format(fo, empty_includes);
//     BOOST_CHECK(asserter::assert_equals_string(empty, s.str()));
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
// }

// BOOST_AUTO_TEST_SUITE_END()
