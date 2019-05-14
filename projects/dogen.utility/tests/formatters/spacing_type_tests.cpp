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
#include "dogen.utility/io/formatters/spacing_type_io.hpp"
#include "dogen.utility/types/formatters/spacing_type.hpp"
#include "dogen.utility/test_data/formatters/spacing_type_td.hpp"
#include "dogen.utility/lexical_cast/formatters/spacing_type_lc.hpp"

BOOST_AUTO_TEST_SUITE(spacing_type_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::utility::formatters::spacing_type_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::utility::formatters::spacing_type;
    spacing_type r;

    r = boost::lexical_cast<spacing_type>(std::string("invalid"));
    BOOST_CHECK(r == spacing_type::invalid);
    r = boost::lexical_cast<spacing_type>(std::string("spacing_type::invalid"));
    BOOST_CHECK(r == spacing_type::invalid);

    r = boost::lexical_cast<spacing_type>(std::string("no_space"));
    BOOST_CHECK(r == spacing_type::no_space);
    r = boost::lexical_cast<spacing_type>(std::string("spacing_type::no_space"));
    BOOST_CHECK(r == spacing_type::no_space);

    r = boost::lexical_cast<spacing_type>(std::string("left_space"));
    BOOST_CHECK(r == spacing_type::left_space);
    r = boost::lexical_cast<spacing_type>(std::string("spacing_type::left_space"));
    BOOST_CHECK(r == spacing_type::left_space);

    r = boost::lexical_cast<spacing_type>(std::string("right_space"));
    BOOST_CHECK(r == spacing_type::right_space);
    r = boost::lexical_cast<spacing_type>(std::string("spacing_type::right_space"));
    BOOST_CHECK(r == spacing_type::right_space);

    r = boost::lexical_cast<spacing_type>(std::string("left_and_right_space"));
    BOOST_CHECK(r == spacing_type::left_and_right_space);
    r = boost::lexical_cast<spacing_type>(std::string("spacing_type::left_and_right_space"));
    BOOST_CHECK(r == spacing_type::left_and_right_space);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::utility::formatters::spacing_type;
    BOOST_CHECK_THROW(boost::lexical_cast<spacing_type>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::utility::formatters::spacing_type;
    std::string r;

    r = boost::lexical_cast<std::string>(spacing_type::invalid);
    BOOST_CHECK(r == "spacing_type::invalid");

    r = boost::lexical_cast<std::string>(spacing_type::no_space);
    BOOST_CHECK(r == "spacing_type::no_space");

    r = boost::lexical_cast<std::string>(spacing_type::left_space);
    BOOST_CHECK(r == "spacing_type::left_space");

    r = boost::lexical_cast<std::string>(spacing_type::right_space);
    BOOST_CHECK(r == "spacing_type::right_space");

    r = boost::lexical_cast<std::string>(spacing_type::left_and_right_space);
    BOOST_CHECK(r == "spacing_type::left_and_right_space");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
    using dogen::utility::formatters::spacing_type;
    const spacing_type r(static_cast<spacing_type>(15));
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
