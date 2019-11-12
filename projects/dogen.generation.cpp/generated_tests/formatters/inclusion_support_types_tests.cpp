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
#include <boost/predef.h>
#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen.generation.cpp/io/formatters/inclusion_support_types_io.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_support_types.hpp"
#include "dogen.generation.cpp/test_data/formatters/inclusion_support_types_td.hpp"
#include "dogen.generation.cpp/lexical_cast/formatters/inclusion_support_types_lc.hpp"

BOOST_AUTO_TEST_SUITE(inclusion_support_types_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::generation::cpp::formatters::inclusion_support_types_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::generation::cpp::formatters::inclusion_support_types;
    inclusion_support_types r;

    r = boost::lexical_cast<inclusion_support_types>(std::string("invalid"));
    BOOST_CHECK(r == inclusion_support_types::invalid);
    r = boost::lexical_cast<inclusion_support_types>(std::string("inclusion_support_types::invalid"));
    BOOST_CHECK(r == inclusion_support_types::invalid);

    r = boost::lexical_cast<inclusion_support_types>(std::string("not_supported"));
    BOOST_CHECK(r == inclusion_support_types::not_supported);
    r = boost::lexical_cast<inclusion_support_types>(std::string("inclusion_support_types::not_supported"));
    BOOST_CHECK(r == inclusion_support_types::not_supported);

    r = boost::lexical_cast<inclusion_support_types>(std::string("regular_support"));
    BOOST_CHECK(r == inclusion_support_types::regular_support);
    r = boost::lexical_cast<inclusion_support_types>(std::string("inclusion_support_types::regular_support"));
    BOOST_CHECK(r == inclusion_support_types::regular_support);

    r = boost::lexical_cast<inclusion_support_types>(std::string("canonical_support"));
    BOOST_CHECK(r == inclusion_support_types::canonical_support);
    r = boost::lexical_cast<inclusion_support_types>(std::string("inclusion_support_types::canonical_support"));
    BOOST_CHECK(r == inclusion_support_types::canonical_support);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::generation::cpp::formatters::inclusion_support_types;
    BOOST_CHECK_THROW(boost::lexical_cast<inclusion_support_types>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::generation::cpp::formatters::inclusion_support_types;
    std::string r;

    r = boost::lexical_cast<std::string>(inclusion_support_types::invalid);
    BOOST_CHECK(r == "inclusion_support_types::invalid");

    r = boost::lexical_cast<std::string>(inclusion_support_types::not_supported);
    BOOST_CHECK(r == "inclusion_support_types::not_supported");

    r = boost::lexical_cast<std::string>(inclusion_support_types::regular_support);
    BOOST_CHECK(r == "inclusion_support_types::regular_support");

    r = boost::lexical_cast<std::string>(inclusion_support_types::canonical_support);
    BOOST_CHECK(r == "inclusion_support_types::canonical_support");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::generation::cpp::formatters::inclusion_support_types;
    const inclusion_support_types r(static_cast<inclusion_support_types>(14));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
