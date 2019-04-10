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
#include <boost/test/unit_test.hpp>
#include "masd.dogen.utility/types/test/asserter.hpp"
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.coding/types/meta_model/technical_space.hpp"
#include "masd.dogen.generation/types/formatters/indent_filter.hpp"
#include "masd.dogen.generation/test/mock_boilerplate_properties_factory.hpp"
#include "masd.dogen.generation/io/formatters/boilerplate_properties_io.hpp"
#include "masd.dogen.generation/types/formatters/boilerplate_formatter.hpp"

namespace {

const std::string test_module("masd.dogen.generation.tests");
const std::string test_suite("boilerplate_formatter_tests");
const std::string empty;

// const bool generate_premable(true);

const std::string expected_cpp_modeline_top(
    R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
)");

const std::string expected_cpp_guards_with_top_modeline(
    R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
#ifndef A_PATH_HPP
#define A_PATH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#endif
)");

const std::string expected_cpp_guards_with_bottom_modeline(
    R"(/*
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
#ifndef A_PATH_HPP
#define A_PATH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/*
 * Local variables:
 * a_field: a_value
 * End:
 */
#endif
)");

const std::string expected_cpp_disabled_preamble(
    R"(#ifndef A_PATH_HPP
#define A_PATH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <win32/system_inc_1>
#include <unix/system_inc_2>
#include "user_inc_1"
#include "user_inc_2"

#endif
)");

using masd::dogen::generation::formatters::boilerplate_properties;

std::string format(const boilerplate_properties& bp) {

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    masd::dogen::generation::formatters::indent_filter::push(fo, 4);
    fo.push(s);

    masd::dogen::generation::formatters::boilerplate_formatter f(s, bp);
    f.format_begin();
    f.format_end();
    return s.str();
}

}

using namespace masd::dogen::generation::formatters;
using namespace masd::dogen::utility::test;
using masd::dogen::utility::test::asserter;
using factory =
    masd::dogen::generation::test::mock_boilerplate_properties_factory;

BOOST_AUTO_TEST_SUITE(boilerplate_formatter_tests)

BOOST_AUTO_TEST_CASE(cpp_top_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_top_modeline_is_formatted_correctly");

    BOOST_LOG_SEV(lg, debug) << "Logging to disable modeline at the top.";
    const auto bp(factory::make_cpp_top_modeline_single_line());

    BOOST_LOG_SEV(lg, debug) << "Input" << bp;
    const auto r(format(bp));

    BOOST_CHECK(asserter::assert_equals_string(expected_cpp_modeline_top, r));
    BOOST_LOG_SEV(lg, debug) << "Logging to disable modeline at the bottom";
}

// BOOST_IGNORE_AUTO_TEST_CASE(header_guards_with_top_modeline_are_formatted_correctly) {
//     SETUP_TEST_LOG_SOURCE("header_guards_with_top_modeline_are_formatted_correctly");
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

//     const decoration_properties dc(factory_.make_decoration_properties());
//     const auto inc(factory_.make_includes(true/*is_empty*/));
//     const auto hg(factory_.make_header_guard());
//     const auto r(format(dc, inc, hg));

//     BOOST_CHECK(r == guards_with_top_modeline);
//     BOOST_CHECK(asserter::assert_equals_string(guards_with_top_modeline, r));
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
// }

// BOOST_IGNORE_AUTO_TEST_CASE(header_guards_with_bottom_modeline_are_formatted_correctly) {
//     SETUP_TEST_LOG_SOURCE("header_guards_with_bottom_modeline_are_formatted_correctly");
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

//     const decoration_properties
//         dc(factory_.make_decoration_properties(modeline_locations::bottom));
//     const auto inc(factory_.make_includes(true/*is_empty*/));
//     const auto hg(factory_.make_header_guard());
//     const auto r(format(dc, inc, hg));

//     BOOST_CHECK(asserter::assert_equals_string(guards_with_bottom_modeline, r));
//     BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
// }


BOOST_AUTO_TEST_SUITE_END()
