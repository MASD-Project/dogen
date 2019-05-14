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
#include "dogen/io/diffing_destination_io.hpp"
#include "dogen/types/diffing_destination.hpp"
#include "dogen/test_data/diffing_destination_td.hpp"
#include "dogen/lexical_cast/diffing_destination_lc.hpp"

BOOST_AUTO_TEST_SUITE(diffing_destination_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::diffing_destination_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::diffing_destination;
    diffing_destination r;

    r = boost::lexical_cast<diffing_destination>(std::string("invalid"));
    BOOST_CHECK(r == diffing_destination::invalid);
    r = boost::lexical_cast<diffing_destination>(std::string("diffing_destination::invalid"));
    BOOST_CHECK(r == diffing_destination::invalid);

    r = boost::lexical_cast<diffing_destination>(std::string("file"));
    BOOST_CHECK(r == diffing_destination::file);
    r = boost::lexical_cast<diffing_destination>(std::string("diffing_destination::file"));
    BOOST_CHECK(r == diffing_destination::file);

    r = boost::lexical_cast<diffing_destination>(std::string("console"));
    BOOST_CHECK(r == diffing_destination::console);
    r = boost::lexical_cast<diffing_destination>(std::string("diffing_destination::console"));
    BOOST_CHECK(r == diffing_destination::console);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::diffing_destination;
    BOOST_CHECK_THROW(boost::lexical_cast<diffing_destination>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::diffing_destination;
    std::string r;

    r = boost::lexical_cast<std::string>(diffing_destination::invalid);
    BOOST_CHECK(r == "diffing_destination::invalid");

    r = boost::lexical_cast<std::string>(diffing_destination::file);
    BOOST_CHECK(r == "diffing_destination::file");

    r = boost::lexical_cast<std::string>(diffing_destination::console);
    BOOST_CHECK(r == "diffing_destination::console");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::diffing_destination;
    const diffing_destination r(static_cast<diffing_destination>(13));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
