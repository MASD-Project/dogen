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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/om/types/all.hpp"
#include "dogen/om/io/all_io.hpp"
#include "dogen/om/test_data/all_td.hpp"

namespace {

const std::string test_module("om");
const std::string test_suite("cpp_file_boilerplate_formatter_spec");
const std::string marker("this is a marker");
const std::string empty_marker;
const dogen::om::licence empty_licence;
const dogen::om::cpp_includes empty_includes;
const boost::filesystem::path empty_path;
const boost::filesystem::path a_path("a/path.hpp");

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

const std::string licence_no_holders(R"(/* -*- a_field: a_value -*-
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

dogen::om::modeline mock_modeline(const dogen::om::modeline_locations l) {
    dogen::om::modeline r;
    r.editor(dogen::om::editors::emacs);
    r.location(l);

    using dogen::om::modeline_field;
    modeline_field mf;
    mf.name("a_field");
    mf.value("a_value");

    r.fields(std::list<modeline_field>{ mf });
    return r;
}

dogen::om::licence mock_licence(const bool multiline = false) {
    dogen::om::licence r;

    r.copyright_holders().push_back("a_holder");
    if (multiline)
        r.copyright_holders().push_back("another_holder");

    if (multiline) {
        std::ostringstream s;
        s << "first line of licence text" << std::endl
          << "second line of licence text" << std::endl;
        r.text(s.str());
    } else
        r.text("licence text");

    return r;
}

dogen::om::cpp_includes mock_includes() {
    dogen::om::cpp_includes r;
    r.user(std::list<std::string>{"user_include"});
    r.system(std::list<std::string>{"system_include"});
    return r;
}

}

using namespace dogen::om;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(cpp_file_boilerplate_formatter)

BOOST_AUTO_TEST_CASE(top_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("top_modeline_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::top));
    const auto l(mock_licence());

    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, l, m, marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == modeline_top);
    BOOST_LOG_SEV(lg, debug) << "expected: " << modeline_top;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(top_modeline_and_multiline_licence_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("top_modeline_and_multiline_licence_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::top));
    const auto l(mock_licence(true/*multiline licence*/));

    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, l, m, marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == multiline_licence);
    BOOST_LOG_SEV(lg, debug) << "expected: " << multiline_licence;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(bottom_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("bottom_modeline_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::bottom));
    const auto l(mock_licence());

    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, l, m, marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == modeline_bottom);
    BOOST_LOG_SEV(lg, debug) << "expected: " << modeline_bottom;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(no_marker_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("no_marker_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::top));
    const auto l(mock_licence());

    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, l, m, empty_marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == no_marker);
    BOOST_LOG_SEV(lg, debug) << "expected: " << no_marker;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(no_licence_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("no_licence_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::top));

    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, empty_licence, m, marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == no_licence);
    BOOST_LOG_SEV(lg, debug) << "expected: " << no_licence;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(licence_with_holder_but_no_text_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("licence_with_holder_but_no_text_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::top));
    dogen::om::licence l;
    l.copyright_holders().push_back("a_holder");

    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, l, m, marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == licence_no_text);
    BOOST_LOG_SEV(lg, debug) << "expected: " << licence_no_text;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(licence_with_text_but_no_holders_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("licence_with_text_but_no_holders_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::top));
    dogen::om::licence l;
    l.text("licence text");

    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, l, m, marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == licence_no_holders);
    BOOST_LOG_SEV(lg, debug) << "expected: " << licence_no_holders;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(preamble_with_just_marker_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("preamble_with_just_marker_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const modeline m;
    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, empty_licence, m, marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == just_marker);
    BOOST_LOG_SEV(lg, debug) << "expected: " << just_marker;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(preamble_with_just_modeline_at_the_top_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("preamble_with_just_modeline_at_the_top_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::top));
    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, empty_licence, m, empty_marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == just_modeline_top);
    BOOST_LOG_SEV(lg, debug) << "expected: " << just_modeline_top;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(postamble_with_just_modeline_at_the_bottom_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("postamble_with_just_modeline_at_the_bottom_is_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::bottom));
    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, empty_licence, m, empty_marker, empty_includes, empty_path);
    f.format_end(s, m, empty_path);
    const auto r(s.str());
    BOOST_CHECK(r == just_modeline_bottom);
    BOOST_LOG_SEV(lg, debug) << "expected: " << just_modeline_bottom;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(header_guards_with_top_modeline_are_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("header_guards_with_top_modeline_are_formatted_correctly");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_modeline(dogen::om::modeline_locations::top));
    const auto l(mock_licence());

    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, l, m, marker, empty_includes, a_path);
    f.format_end(s, m, a_path);
    const auto r(s.str());
    BOOST_CHECK(r == guards_with_top_modeline);
    BOOST_LOG_SEV(lg, debug) << "expected: " << guards_with_top_modeline;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_SUITE_END()
