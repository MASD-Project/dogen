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
#include "dogen.injection.dia/io/dia_object_types_io.hpp"
#include "dogen.injection.dia/types/dia_object_types.hpp"
#include "dogen.injection.dia/test_data/dia_object_types_td.hpp"
#include "dogen.injection.dia/lexical_cast/dia_object_types_lc.hpp"

BOOST_AUTO_TEST_SUITE(dia_object_types_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::injection::dia::dia_object_types_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::injection::dia::dia_object_types;
    dia_object_types r;

    r = boost::lexical_cast<dia_object_types>(std::string("invalid"));
    BOOST_CHECK(r == dia_object_types::invalid);
    r = boost::lexical_cast<dia_object_types>(std::string("dia_object_types::invalid"));
    BOOST_CHECK(r == dia_object_types::invalid);

    r = boost::lexical_cast<dia_object_types>(std::string("uml_large_package"));
    BOOST_CHECK(r == dia_object_types::uml_large_package);
    r = boost::lexical_cast<dia_object_types>(std::string("dia_object_types::uml_large_package"));
    BOOST_CHECK(r == dia_object_types::uml_large_package);

    r = boost::lexical_cast<dia_object_types>(std::string("uml_class"));
    BOOST_CHECK(r == dia_object_types::uml_class);
    r = boost::lexical_cast<dia_object_types>(std::string("dia_object_types::uml_class"));
    BOOST_CHECK(r == dia_object_types::uml_class);

    r = boost::lexical_cast<dia_object_types>(std::string("uml_generalization"));
    BOOST_CHECK(r == dia_object_types::uml_generalization);
    r = boost::lexical_cast<dia_object_types>(std::string("dia_object_types::uml_generalization"));
    BOOST_CHECK(r == dia_object_types::uml_generalization);

    r = boost::lexical_cast<dia_object_types>(std::string("uml_association"));
    BOOST_CHECK(r == dia_object_types::uml_association);
    r = boost::lexical_cast<dia_object_types>(std::string("dia_object_types::uml_association"));
    BOOST_CHECK(r == dia_object_types::uml_association);

    r = boost::lexical_cast<dia_object_types>(std::string("uml_note"));
    BOOST_CHECK(r == dia_object_types::uml_note);
    r = boost::lexical_cast<dia_object_types>(std::string("dia_object_types::uml_note"));
    BOOST_CHECK(r == dia_object_types::uml_note);

    r = boost::lexical_cast<dia_object_types>(std::string("uml_message"));
    BOOST_CHECK(r == dia_object_types::uml_message);
    r = boost::lexical_cast<dia_object_types>(std::string("dia_object_types::uml_message"));
    BOOST_CHECK(r == dia_object_types::uml_message);

    r = boost::lexical_cast<dia_object_types>(std::string("uml_realization"));
    BOOST_CHECK(r == dia_object_types::uml_realization);
    r = boost::lexical_cast<dia_object_types>(std::string("dia_object_types::uml_realization"));
    BOOST_CHECK(r == dia_object_types::uml_realization);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::injection::dia::dia_object_types;
    BOOST_CHECK_THROW(boost::lexical_cast<dia_object_types>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::injection::dia::dia_object_types;
    std::string r;

    r = boost::lexical_cast<std::string>(dia_object_types::invalid);
    BOOST_CHECK(r == "dia_object_types::invalid");

    r = boost::lexical_cast<std::string>(dia_object_types::uml_large_package);
    BOOST_CHECK(r == "dia_object_types::uml_large_package");

    r = boost::lexical_cast<std::string>(dia_object_types::uml_class);
    BOOST_CHECK(r == "dia_object_types::uml_class");

    r = boost::lexical_cast<std::string>(dia_object_types::uml_generalization);
    BOOST_CHECK(r == "dia_object_types::uml_generalization");

    r = boost::lexical_cast<std::string>(dia_object_types::uml_association);
    BOOST_CHECK(r == "dia_object_types::uml_association");

    r = boost::lexical_cast<std::string>(dia_object_types::uml_note);
    BOOST_CHECK(r == "dia_object_types::uml_note");

    r = boost::lexical_cast<std::string>(dia_object_types::uml_message);
    BOOST_CHECK(r == "dia_object_types::uml_message");

    r = boost::lexical_cast<std::string>(dia_object_types::uml_realization);
    BOOST_CHECK(r == "dia_object_types::uml_realization");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma gcc diagnostic push
#pragma gcc diagnostic ignored "-Werror=conversion"
#endif
    using dogen::injection::dia::dia_object_types;
    const dia_object_types r(static_cast<dia_object_types>(18));
#if BOOST_COMP_GNUC
#pragma gcc diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
