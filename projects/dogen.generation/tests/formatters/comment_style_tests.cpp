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
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen.generation/io/formatters/comment_style_io.hpp"
#include "dogen.generation/types/formatters/comment_style.hpp"
#include "dogen.generation/test_data/formatters/comment_style_td.hpp"
#include "dogen.generation/lexical_cast/formatters/comment_style_lc.hpp"

BOOST_AUTO_TEST_SUITE(comment_style_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::generation::formatters::comment_style_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::generation::formatters::comment_style;
    comment_style r;

    r = boost::lexical_cast<comment_style>(std::string("invalid"));
    BOOST_CHECK(r == comment_style::invalid);
    r = boost::lexical_cast<comment_style>(std::string("comment_style::invalid"));
    BOOST_CHECK(r == comment_style::invalid);

    r = boost::lexical_cast<comment_style>(std::string("c_style"));
    BOOST_CHECK(r == comment_style::c_style);
    r = boost::lexical_cast<comment_style>(std::string("comment_style::c_style"));
    BOOST_CHECK(r == comment_style::c_style);

    r = boost::lexical_cast<comment_style>(std::string("cpp_style"));
    BOOST_CHECK(r == comment_style::cpp_style);
    r = boost::lexical_cast<comment_style>(std::string("comment_style::cpp_style"));
    BOOST_CHECK(r == comment_style::cpp_style);

    r = boost::lexical_cast<comment_style>(std::string("csharp_style"));
    BOOST_CHECK(r == comment_style::csharp_style);
    r = boost::lexical_cast<comment_style>(std::string("comment_style::csharp_style"));
    BOOST_CHECK(r == comment_style::csharp_style);

    r = boost::lexical_cast<comment_style>(std::string("shell_style"));
    BOOST_CHECK(r == comment_style::shell_style);
    r = boost::lexical_cast<comment_style>(std::string("comment_style::shell_style"));
    BOOST_CHECK(r == comment_style::shell_style);

    r = boost::lexical_cast<comment_style>(std::string("sql_style"));
    BOOST_CHECK(r == comment_style::sql_style);
    r = boost::lexical_cast<comment_style>(std::string("comment_style::sql_style"));
    BOOST_CHECK(r == comment_style::sql_style);

    r = boost::lexical_cast<comment_style>(std::string("xml_style"));
    BOOST_CHECK(r == comment_style::xml_style);
    r = boost::lexical_cast<comment_style>(std::string("comment_style::xml_style"));
    BOOST_CHECK(r == comment_style::xml_style);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::generation::formatters::comment_style;
    BOOST_CHECK_THROW(boost::lexical_cast<comment_style>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::generation::formatters::comment_style;
    std::string r;

    r = boost::lexical_cast<std::string>(comment_style::invalid);
    BOOST_CHECK(r == "comment_style::invalid");

    r = boost::lexical_cast<std::string>(comment_style::c_style);
    BOOST_CHECK(r == "comment_style::c_style");

    r = boost::lexical_cast<std::string>(comment_style::cpp_style);
    BOOST_CHECK(r == "comment_style::cpp_style");

    r = boost::lexical_cast<std::string>(comment_style::csharp_style);
    BOOST_CHECK(r == "comment_style::csharp_style");

    r = boost::lexical_cast<std::string>(comment_style::shell_style);
    BOOST_CHECK(r == "comment_style::shell_style");

    r = boost::lexical_cast<std::string>(comment_style::sql_style);
    BOOST_CHECK(r == "comment_style::sql_style");

    r = boost::lexical_cast<std::string>(comment_style::xml_style);
    BOOST_CHECK(r == "comment_style::xml_style");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma gcc diagnostic push
#pragma gcc diagnostic ignored "-Werror=conversion"
#endif
    using dogen::generation::formatters::comment_style;
    const comment_style r(static_cast<comment_style>(17));
#if BOOST_COMP_GNUC
#pragma gcc diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
