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
#include "masd.dogen.formatting/types/indent_filter.hpp"
#include "masd.dogen.utility/test/asserter.hpp"
#include "masd.dogen.utility/test/logging.hpp"
#include "masd.dogen.utility/io/list_io.hpp"
#include "masd.dogen.utility/filesystem/path.hpp"
#include "masd.dogen.utility/io/unordered_map_io.hpp"
#include "masd.dogen.formatting/test/mock_decoration_properties_factory.hpp"
#include "masd.dogen.formatting/types/cpp/boilerplate_formatter.hpp"

namespace {

const std::string test_module("formatting");
const std::string test_suite("cpp_boilerplate_formatter_tests");
const std::string empty;

masd::dogen::formatting::test::mock_decoration_properties_factory factory_;
const bool generate_premable(true);

const std::string modeline_top(R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
)");

const std::string multiline_licence(R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 * another_holder
 *
 * first line of licence text
 * second line of licence text
 *
 */
)");

const std::string modeline_bottom(R"(/*
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
/*
 * Local variables:
 * a_field: a_value
 * End:
 */
)");

const std::string no_marker(R"(/* -*- a_field: a_value -*-
 *
 * a_holder
 *
 * licence text
 *
 */
)");

const std::string no_licence(R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 */
)");

const std::string licence_no_text(R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 *
 */
)");

const std::string licence_no_copyright_notices(R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * licence text
 *
 */
)");

const std::string just_marker(R"(/*
 * this is a marker
 *
 */
)");

const std::string just_modeline_top(R"(// -*- a_field: a_value -*-
)");

const std::string just_modeline_bottom(R"(/*
 * Local variables:
 * a_field: a_value
 * End:
 */
)");

const std::string guards_with_top_modeline(R"(/* -*- a_field: a_value -*-
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

const std::string guards_with_bottom_modeline(R"(/*
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

const std::string includes_with_top_modeline(R"(/* -*- a_field: a_value -*-
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

#include <win32/system_inc_1>
#include <unix/system_inc_2>
#include "user_inc_1"
#include "user_inc_2"

#endif
)");

const std::string disabled_preamble(R"(#ifndef A_PATH_HPP
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

std::string format(const masd::dogen::formatting::decoration_properties& dc,
    const std::list<std::string>& includes, const std::string& header_guard,
    const bool generate_premable = true) {

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    masd::dogen::formatting::indent_filter::push(fo, 4);
    fo.push(s);

    masd::dogen::formatting::cpp::boilerplate_formatter f(generate_premable);
    f.format_begin(fo, dc, includes, header_guard);
    f.format_end(fo, dc, header_guard);
    return s.str();
}

}

using namespace masd::dogen::formatting;
using namespace masd::dogen::utility::test;
using masd::dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(cpp_boilerplate_formatter_tests)

BOOST_AUTO_TEST_CASE(top_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("top_modeline_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";
    const auto dc(factory_.make_decoration_properties());
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(modeline_top, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(top_modeline_and_multiline_licence_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("top_modeline_and_multiline_licence_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto dc(factory_.make_decoration_properties(modeline_locations::top,
            true/*multiline licence*/));
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(multiline_licence, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(bottom_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("bottom_modeline_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto dc(factory_.make_decoration_properties(
            modeline_locations::bottom));
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(modeline_bottom, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(no_marker_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("no_marker_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto dc(factory_.make_decoration_properties(modeline_locations::top,
            false/*multiline licence*/,
            false/*use_empty_licence*/,
            true/*use_empty_marker*/));
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(no_marker, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(no_licence_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("no_licence_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto dc(factory_.make_decoration_properties(modeline_locations::top,
            false/*use_multiline licence*/,
            true/*use_empty_licence*/,
            false/*use_empty_marker*/));
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(no_licence, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(licence_with_holder_but_no_text_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("licence_with_holder_but_no_text_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(factory_.make_modeline(modeline_locations::top));
    licence l;
    l.copyright_notices().push_back("a_holder");
    const decoration_properties dc(true/*generate_preamble*/, m, l,
        factory_.make_marker());
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(licence_no_text, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(licence_with_text_but_no_copyright_notices_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("licence_with_text_but_no_copyright_notices_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(factory_.make_modeline(modeline_locations::top));
    licence l;
    l.text("licence text");
    const decoration_properties dc(true/*generate_preamble*/, m, l,
        factory_.make_marker());
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(
        asserter::assert_equals_marker(licence_no_copyright_notices, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(preamble_with_just_marker_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("preamble_with_just_marker_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    auto dc(factory_.make_empty_decoration_properties());
    dc.code_generation_marker(factory_.make_marker());
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(just_marker, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(preamble_with_just_modeline_at_the_top_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("preamble_with_just_modeline_at_the_top_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties dc(factory_.make_decoration_properties(
            modeline_locations::top,
            false/*use_multiline licence*/,
            true/*use_empty_licence*/,
            true/*use_empty_marker*/));
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(just_modeline_top, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(postamble_with_just_modeline_at_the_bottom_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("postamble_with_just_modeline_at_the_bottom_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties dc(factory_.make_decoration_properties(
            modeline_locations::bottom,
            false/*use_multiline licence*/,
            true/*use_empty_licence*/,
            true/*use_empty_marker*/));
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(just_modeline_bottom, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(not_supplying_content_results_in_no_boilerplate) {
    SETUP_TEST_LOG_SOURCE("not_supplying_content_results_in_no_boilerplate");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties
        dc(factory_.make_empty_decoration_properties());
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(empty, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(header_guards_with_top_modeline_are_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("header_guards_with_top_modeline_are_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties dc(factory_.make_decoration_properties());
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard());
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(r == guards_with_top_modeline);
    BOOST_CHECK(asserter::assert_equals_marker(guards_with_top_modeline, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(header_guards_with_bottom_modeline_are_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("header_guards_with_bottom_modeline_are_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties
        dc(factory_.make_decoration_properties(modeline_locations::bottom));
    const auto inc(factory_.make_includes(true/*is_empty*/));
    const auto hg(factory_.make_header_guard());
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(guards_with_bottom_modeline, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(includes_are_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("includes_are_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties dc(factory_.make_decoration_properties());
    const auto inc(factory_.make_includes());
    const auto hg(factory_.make_header_guard());
    const auto r(format(dc, inc, hg));

    BOOST_CHECK(asserter::assert_equals_marker(includes_with_top_modeline, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(disabled_preamble_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("disabled_preamble_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties dc(factory_.make_decoration_properties());
    const auto inc(factory_.make_includes());
    const auto hg(factory_.make_header_guard());
    const auto r(format(dc, inc, hg, !generate_premable));

    BOOST_CHECK(asserter::assert_equals_marker(disabled_preamble, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_SUITE_END()
