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
#include "dogen.relational/io/tracing/transform_type_io.hpp"
#include "dogen.relational/types/tracing/transform_type.hpp"
#include "dogen.relational/test_data/tracing/transform_type_td.hpp"
#include "dogen.relational/lexical_cast/tracing/transform_type_lc.hpp"

BOOST_AUTO_TEST_SUITE(transform_type_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::relational::tracing::transform_type_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::relational::tracing::transform_type;
    transform_type r;

    r = boost::lexical_cast<transform_type>(std::string("invalid"));
    BOOST_CHECK(r == transform_type::invalid);
    r = boost::lexical_cast<transform_type>(std::string("transform_type::invalid"));
    BOOST_CHECK(r == transform_type::invalid);

    r = boost::lexical_cast<transform_type>(std::string("chain"));
    BOOST_CHECK(r == transform_type::chain);
    r = boost::lexical_cast<transform_type>(std::string("transform_type::chain"));
    BOOST_CHECK(r == transform_type::chain);

    r = boost::lexical_cast<transform_type>(std::string("leaf"));
    BOOST_CHECK(r == transform_type::leaf);
    r = boost::lexical_cast<transform_type>(std::string("transform_type::leaf"));
    BOOST_CHECK(r == transform_type::leaf);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::relational::tracing::transform_type;
    BOOST_CHECK_THROW(boost::lexical_cast<transform_type>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::relational::tracing::transform_type;
    std::string r;

    r = boost::lexical_cast<std::string>(transform_type::invalid);
    BOOST_CHECK(r == "transform_type::invalid");

    r = boost::lexical_cast<std::string>(transform_type::chain);
    BOOST_CHECK(r == "transform_type::chain");

    r = boost::lexical_cast<std::string>(transform_type::leaf);
    BOOST_CHECK(r == "transform_type::leaf");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::relational::tracing::transform_type;
    const transform_type r(static_cast<transform_type>(13));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
