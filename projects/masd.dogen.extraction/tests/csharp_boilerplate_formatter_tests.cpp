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
#include "masd.dogen.extraction/types/indent_filter.hpp"
#include "masd.dogen.utility/types/test/asserter.hpp"
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.extraction/test/mock_decoration_properties_factory.hpp"
#include "masd.dogen.extraction/types/csharp/boilerplate_formatter.hpp"

namespace {

const std::string test_module("masd.dogen.extraction.tests");
const std::string test_suite("csharp_boilerplate_formatter_tests");
const std::string empty;

masd::dogen::extraction::test::mock_decoration_properties_factory factory_;
const bool generate_premable(true);

const std::string modeline_top(R"(// -*- a_field: a_value -*-
//
// this is a marker
//
// a_holder
//
// licence text
//
)");

const std::string multiline_licence(R"(// -*- a_field: a_value -*-
//
// this is a marker
//
// a_holder
// another_holder
//
// first line of licence text
// second line of licence text
//
)");

const std::string modeline_bottom(R"(//
// this is a marker
//
// a_holder
//
// licence text
//
//
// Local variables:
// a_field: a_value
// End:
)");

const std::string no_marker(R"(// -*- a_field: a_value -*-
//
// a_holder
//
// licence text
//
)");

const std::string no_licence(R"(// -*- a_field: a_value -*-
//
// this is a marker
//
)");

const std::string licence_no_text(R"(// -*- a_field: a_value -*-
//
// this is a marker
//
// a_holder
//
)");

const std::string licence_no_copyright_notices(R"(// -*- a_field: a_value -*-
//
// this is a marker
//
// licence text
//
)");

const std::string just_marker(R"(//
// this is a marker
//
)");

const std::string just_modeline_top(R"(// -*- a_field: a_value -*-
)");

const std::string just_modeline_bottom(R"(//
// Local variables:
// a_field: a_value
// End:
)");

const std::string includes_with_top_modeline(R"(// -*- a_field: a_value -*-
//
// this is a marker
//
// a_holder
//
// licence text
//
using System
using System.Linq
using ICSharpCode.NRefactory.Editor
)");

const std::string disabled_preamble(R"(using System
using System.Linq
using ICSharpCode.NRefactory.Editor
)");

std::string format(const masd::dogen::extraction::decoration_properties& dc,
    const std::list<std::string>& usings,
    const bool generate_premable = true) {

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    masd::dogen::extraction::indent_filter::push(fo, 4);
    fo.push(s);

    masd::dogen::extraction::csharp::boilerplate_formatter f(generate_premable);
    f.format_begin(fo, dc, usings);
    f.format_end(fo, dc);
    return s.str();
}

}

using namespace masd::dogen::extraction;
using namespace masd::dogen::utility::test;
using masd::dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(csharp_boilerplate_formatter_tests)

BOOST_AUTO_TEST_CASE(top_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("top_modeline_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";
    const auto dc(factory_.make_decoration_properties());
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto hg(factory_.make_header_guard(true/*is_empty*/));
    const auto r(format(dc, us));

    BOOST_CHECK(asserter::assert_equals_marker(modeline_top, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(top_modeline_and_multiline_licence_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("top_modeline_and_multiline_licence_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto dc(factory_.make_decoration_properties(modeline_locations::top,
            true/*multiline licence*/));
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

    BOOST_CHECK(asserter::assert_equals_marker(multiline_licence, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(bottom_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("bottom_modeline_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto dc(factory_.make_decoration_properties(
            modeline_locations::bottom));
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

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
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

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
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

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
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

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
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

    BOOST_CHECK(
        asserter::assert_equals_marker(licence_no_copyright_notices, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(preamble_with_just_marker_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("preamble_with_just_marker_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    auto dc(factory_.make_empty_decoration_properties());
    dc.code_generation_marker(factory_.make_marker());
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

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
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

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
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

    BOOST_CHECK(asserter::assert_equals_marker(just_modeline_bottom, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(not_supplying_content_results_in_no_boilerplate) {
    SETUP_TEST_LOG_SOURCE("not_supplying_content_results_in_no_boilerplate");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties
        dc(factory_.make_empty_decoration_properties());
    const auto us(factory_.make_usings(true/*is_empty*/));
    const auto r(format(dc, us));

    BOOST_CHECK(asserter::assert_equals_marker(empty, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(usings_are_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("usings_are_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties dc(factory_.make_decoration_properties());
    const auto us(factory_.make_usings());
    const auto r(format(dc, us));

    BOOST_CHECK(asserter::assert_equals_marker(includes_with_top_modeline, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(disabled_preamble_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("disabled_preamble_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const decoration_properties dc(factory_.make_decoration_properties());
    const auto us(factory_.make_usings());
    const auto r(format(dc, us, !generate_premable));

    BOOST_CHECK(asserter::assert_equals_marker(disabled_preamble, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_SUITE_END()
