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
#include "dogen/io/tracing_level_io.hpp"
#include "dogen/types/tracing_level.hpp"
#include "dogen/test_data/tracing_level_td.hpp"
#include "dogen/lexical_cast/tracing_level_lc.hpp"

BOOST_AUTO_TEST_SUITE(tracing_level_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::tracing_level_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::tracing_level;
    tracing_level r;

    r = boost::lexical_cast<tracing_level>(std::string("invalid"));
    BOOST_CHECK(r == tracing_level::invalid);
    r = boost::lexical_cast<tracing_level>(std::string("tracing_level::invalid"));
    BOOST_CHECK(r == tracing_level::invalid);

    r = boost::lexical_cast<tracing_level>(std::string("detail"));
    BOOST_CHECK(r == tracing_level::detail);
    r = boost::lexical_cast<tracing_level>(std::string("tracing_level::detail"));
    BOOST_CHECK(r == tracing_level::detail);

    r = boost::lexical_cast<tracing_level>(std::string("summary"));
    BOOST_CHECK(r == tracing_level::summary);
    r = boost::lexical_cast<tracing_level>(std::string("tracing_level::summary"));
    BOOST_CHECK(r == tracing_level::summary);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::tracing_level;
    BOOST_CHECK_THROW(boost::lexical_cast<tracing_level>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::tracing_level;
    std::string r;

    r = boost::lexical_cast<std::string>(tracing_level::invalid);
    BOOST_CHECK(r == "tracing_level::invalid");

    r = boost::lexical_cast<std::string>(tracing_level::detail);
    BOOST_CHECK(r == "tracing_level::detail");

    r = boost::lexical_cast<std::string>(tracing_level::summary);
    BOOST_CHECK(r == "tracing_level::summary");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma gcc diagnostic push
#pragma gcc diagnostic ignored "-Werror=conversion"
#endif
    using dogen::tracing_level;
    const tracing_level r(static_cast<tracing_level>(13));
#if BOOST_COMP_GNUC
#pragma gcc diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
