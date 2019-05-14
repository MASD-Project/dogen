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
#include "dogen.generation.csharp/io/formattables/auxiliary_function_types_io.hpp"
#include "dogen.generation.csharp/types/formattables/auxiliary_function_types.hpp"
#include "dogen.generation.csharp/test_data/formattables/auxiliary_function_types_td.hpp"
#include "dogen.generation.csharp/lexical_cast/formattables/auxiliary_function_types_lc.hpp"

BOOST_AUTO_TEST_SUITE(auxiliary_function_types_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::generation::csharp::formattables::auxiliary_function_types_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::generation::csharp::formattables::auxiliary_function_types;
    auxiliary_function_types r;

    r = boost::lexical_cast<auxiliary_function_types>(std::string("invalid"));
    BOOST_CHECK(r == auxiliary_function_types::invalid);
    r = boost::lexical_cast<auxiliary_function_types>(std::string("auxiliary_function_types::invalid"));
    BOOST_CHECK(r == auxiliary_function_types::invalid);

    r = boost::lexical_cast<auxiliary_function_types>(std::string("assistant"));
    BOOST_CHECK(r == auxiliary_function_types::assistant);
    r = boost::lexical_cast<auxiliary_function_types>(std::string("auxiliary_function_types::assistant"));
    BOOST_CHECK(r == auxiliary_function_types::assistant);

    r = boost::lexical_cast<auxiliary_function_types>(std::string("helper"));
    BOOST_CHECK(r == auxiliary_function_types::helper);
    r = boost::lexical_cast<auxiliary_function_types>(std::string("auxiliary_function_types::helper"));
    BOOST_CHECK(r == auxiliary_function_types::helper);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::generation::csharp::formattables::auxiliary_function_types;
    BOOST_CHECK_THROW(boost::lexical_cast<auxiliary_function_types>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::generation::csharp::formattables::auxiliary_function_types;
    std::string r;

    r = boost::lexical_cast<std::string>(auxiliary_function_types::invalid);
    BOOST_CHECK(r == "auxiliary_function_types::invalid");

    r = boost::lexical_cast<std::string>(auxiliary_function_types::assistant);
    BOOST_CHECK(r == "auxiliary_function_types::assistant");

    r = boost::lexical_cast<std::string>(auxiliary_function_types::helper);
    BOOST_CHECK(r == "auxiliary_function_types::helper");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
    using dogen::generation::csharp::formattables::auxiliary_function_types;
    const auxiliary_function_types r(static_cast<auxiliary_function_types>(13));
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
