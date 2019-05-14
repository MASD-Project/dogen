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
#include "dogen.variability/io/meta_model/binding_point_io.hpp"
#include "dogen.variability/types/meta_model/binding_point.hpp"
#include "dogen.variability/test_data/meta_model/binding_point_td.hpp"
#include "dogen.variability/lexical_cast/meta_model/binding_point_lc.hpp"

BOOST_AUTO_TEST_SUITE(binding_point_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::variability::meta_model::binding_point_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::variability::meta_model::binding_point;
    binding_point r;

    r = boost::lexical_cast<binding_point>(std::string("invalid"));
    BOOST_CHECK(r == binding_point::invalid);
    r = boost::lexical_cast<binding_point>(std::string("binding_point::invalid"));
    BOOST_CHECK(r == binding_point::invalid);

    r = boost::lexical_cast<binding_point>(std::string("any"));
    BOOST_CHECK(r == binding_point::any);
    r = boost::lexical_cast<binding_point>(std::string("binding_point::any"));
    BOOST_CHECK(r == binding_point::any);

    r = boost::lexical_cast<binding_point>(std::string("global"));
    BOOST_CHECK(r == binding_point::global);
    r = boost::lexical_cast<binding_point>(std::string("binding_point::global"));
    BOOST_CHECK(r == binding_point::global);

    r = boost::lexical_cast<binding_point>(std::string("element"));
    BOOST_CHECK(r == binding_point::element);
    r = boost::lexical_cast<binding_point>(std::string("binding_point::element"));
    BOOST_CHECK(r == binding_point::element);

    r = boost::lexical_cast<binding_point>(std::string("property"));
    BOOST_CHECK(r == binding_point::property);
    r = boost::lexical_cast<binding_point>(std::string("binding_point::property"));
    BOOST_CHECK(r == binding_point::property);

    r = boost::lexical_cast<binding_point>(std::string("operation"));
    BOOST_CHECK(r == binding_point::operation);
    r = boost::lexical_cast<binding_point>(std::string("binding_point::operation"));
    BOOST_CHECK(r == binding_point::operation);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::variability::meta_model::binding_point;
    BOOST_CHECK_THROW(boost::lexical_cast<binding_point>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::variability::meta_model::binding_point;
    std::string r;

    r = boost::lexical_cast<std::string>(binding_point::invalid);
    BOOST_CHECK(r == "binding_point::invalid");

    r = boost::lexical_cast<std::string>(binding_point::any);
    BOOST_CHECK(r == "binding_point::any");

    r = boost::lexical_cast<std::string>(binding_point::global);
    BOOST_CHECK(r == "binding_point::global");

    r = boost::lexical_cast<std::string>(binding_point::element);
    BOOST_CHECK(r == "binding_point::element");

    r = boost::lexical_cast<std::string>(binding_point::property);
    BOOST_CHECK(r == "binding_point::property");

    r = boost::lexical_cast<std::string>(binding_point::operation);
    BOOST_CHECK(r == "binding_point::operation");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
    using dogen::variability::meta_model::binding_point;
    const binding_point r(static_cast<binding_point>(16));
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
