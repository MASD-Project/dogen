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
// #include "masd.dogen.utility/types/test/asserter.hpp"
// #include "masd.dogen.utility/types/test/logging.hpp"
// #include "masd.dogen.utility/types/io/list_io.hpp"
// #include "masd.dogen.utility/types/filesystem/path.hpp"
// #include "masd.dogen.utility/types/io/unordered_map_io.hpp"
// #include "masd.dogen.extraction/test/mock_decoration_properties_factory.hpp"
// #include "masd.dogen.extraction/types/csharp/boilerplate_formatter.hpp"

// namespace {

// const std::string test_module("masd.dogen.extraction.tests");
// const std::string test_suite("csharp_boilerplate_formatter_tests");
// const std::string empty;

// masd::dogen::extraction::test::mock_decoration_properties_factory factory_;
// const bool generate_premable(true);









// const std::string includes_with_top_modeline(R"(// -*- a_field: a_value -*-
// //
// // this is a marker
// //
// // a_holder
// //
// // licence text
// //
// using System
// using System.Linq
// using ICSharpCode.NRefactory.Editor
// )");

// const std::string disabled_preamble(R"(using System
// using System.Linq
// using ICSharpCode.NRefactory.Editor
// )");

// std::string format(const masd::dogen::extraction::decoration_properties& dc,
//     const std::list<std::string>& usings,
//     const bool generate_premable = true) {

//     std::ostringstream s;
//     boost::iostreams::filtering_ostream fo;
//     masd::dogen::extraction::indent_filter::push(fo, 4);
//     fo.push(s);

//     masd::dogen::extraction::csharp::boilerplate_formatter f(generate_premable);
//     f.format_begin(fo, dc, usings);
//     f.format_end(fo, dc);
//     return s.str();
// }

// }

// using namespace masd::dogen::extraction;
// using namespace masd::dogen::utility::test;
// using masd::dogen::utility::test::asserter;

// BOOST_AUTO_TEST_SUITE(csharp_boilerplate_formatter_tests)










// BOOST_IGNORE_AUTO_TEST_CASE(usings_are_formatted_correctly) {
//     SETUP_TEST_LOG_SOURCE("usings_are_formatted_correctly");
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

//     const decoration_properties dc(factory_.make_decoration_properties());
//     const auto us(factory_.make_usings());
//     const auto r(format(dc, us));

//     BOOST_CHECK(asserter::assert_equals_string(includes_with_top_modeline, r));
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
// }

// BOOST_IGNORE_AUTO_TEST_CASE(disabled_preamble_is_formatted_correctly) {
//     SETUP_TEST_LOG_SOURCE("disabled_preamble_is_formatted_correctly");
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

//     const decoration_properties dc(factory_.make_decoration_properties());
//     const auto us(factory_.make_usings());
//     const auto r(format(dc, us, !generate_premable));

//     BOOST_CHECK(asserter::assert_equals_string(disabled_preamble, r));
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
// }

// BOOST_AUTO_TEST_SUITE_END()
