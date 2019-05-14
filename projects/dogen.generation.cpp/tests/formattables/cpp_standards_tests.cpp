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
#include "dogen.generation.cpp/io/formattables/cpp_standards_io.hpp"
#include "dogen.generation.cpp/types/formattables/cpp_standards.hpp"
#include "dogen.generation.cpp/test_data/formattables/cpp_standards_td.hpp"
#include "dogen.generation.cpp/lexical_cast/formattables/cpp_standards_lc.hpp"

BOOST_AUTO_TEST_SUITE(cpp_standards_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::generation::cpp::formattables::cpp_standards_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::generation::cpp::formattables::cpp_standards;
    cpp_standards r;

    r = boost::lexical_cast<cpp_standards>(std::string("invalid"));
    BOOST_CHECK(r == cpp_standards::invalid);
    r = boost::lexical_cast<cpp_standards>(std::string("cpp_standards::invalid"));
    BOOST_CHECK(r == cpp_standards::invalid);

    r = boost::lexical_cast<cpp_standards>(std::string("cpp_98"));
    BOOST_CHECK(r == cpp_standards::cpp_98);
    r = boost::lexical_cast<cpp_standards>(std::string("cpp_standards::cpp_98"));
    BOOST_CHECK(r == cpp_standards::cpp_98);

    r = boost::lexical_cast<cpp_standards>(std::string("cpp_11"));
    BOOST_CHECK(r == cpp_standards::cpp_11);
    r = boost::lexical_cast<cpp_standards>(std::string("cpp_standards::cpp_11"));
    BOOST_CHECK(r == cpp_standards::cpp_11);

    r = boost::lexical_cast<cpp_standards>(std::string("cpp_14"));
    BOOST_CHECK(r == cpp_standards::cpp_14);
    r = boost::lexical_cast<cpp_standards>(std::string("cpp_standards::cpp_14"));
    BOOST_CHECK(r == cpp_standards::cpp_14);

    r = boost::lexical_cast<cpp_standards>(std::string("cpp_17"));
    BOOST_CHECK(r == cpp_standards::cpp_17);
    r = boost::lexical_cast<cpp_standards>(std::string("cpp_standards::cpp_17"));
    BOOST_CHECK(r == cpp_standards::cpp_17);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::generation::cpp::formattables::cpp_standards;
    BOOST_CHECK_THROW(boost::lexical_cast<cpp_standards>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::generation::cpp::formattables::cpp_standards;
    std::string r;

    r = boost::lexical_cast<std::string>(cpp_standards::invalid);
    BOOST_CHECK(r == "cpp_standards::invalid");

    r = boost::lexical_cast<std::string>(cpp_standards::cpp_98);
    BOOST_CHECK(r == "cpp_standards::cpp_98");

    r = boost::lexical_cast<std::string>(cpp_standards::cpp_11);
    BOOST_CHECK(r == "cpp_standards::cpp_11");

    r = boost::lexical_cast<std::string>(cpp_standards::cpp_14);
    BOOST_CHECK(r == "cpp_standards::cpp_14");

    r = boost::lexical_cast<std::string>(cpp_standards::cpp_17);
    BOOST_CHECK(r == "cpp_standards::cpp_17");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::generation::cpp::formattables::cpp_standards;
    const cpp_standards r(static_cast<cpp_standards>(15));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
