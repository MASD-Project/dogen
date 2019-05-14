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
#include "dogen.coding/io/meta_model/technical_space_io.hpp"
#include "dogen.coding/types/meta_model/technical_space.hpp"
#include "dogen.coding/hash/meta_model/technical_space_hash.hpp"
#include "dogen.coding/test_data/meta_model/technical_space_td.hpp"
#include "dogen.coding/lexical_cast/meta_model/technical_space_lc.hpp"

BOOST_AUTO_TEST_SUITE(technical_space_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::coding::meta_model::technical_space_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::coding::meta_model::technical_space;
    technical_space r;

    r = boost::lexical_cast<technical_space>(std::string("invalid"));
    BOOST_CHECK(r == technical_space::invalid);
    r = boost::lexical_cast<technical_space>(std::string("technical_space::invalid"));
    BOOST_CHECK(r == technical_space::invalid);

    r = boost::lexical_cast<technical_space>(std::string("agnostic"));
    BOOST_CHECK(r == technical_space::agnostic);
    r = boost::lexical_cast<technical_space>(std::string("technical_space::agnostic"));
    BOOST_CHECK(r == technical_space::agnostic);

    r = boost::lexical_cast<technical_space>(std::string("cpp"));
    BOOST_CHECK(r == technical_space::cpp);
    r = boost::lexical_cast<technical_space>(std::string("technical_space::cpp"));
    BOOST_CHECK(r == technical_space::cpp);

    r = boost::lexical_cast<technical_space>(std::string("csharp"));
    BOOST_CHECK(r == technical_space::csharp);
    r = boost::lexical_cast<technical_space>(std::string("technical_space::csharp"));
    BOOST_CHECK(r == technical_space::csharp);

    r = boost::lexical_cast<technical_space>(std::string("cmake"));
    BOOST_CHECK(r == technical_space::cmake);
    r = boost::lexical_cast<technical_space>(std::string("technical_space::cmake"));
    BOOST_CHECK(r == technical_space::cmake);

    r = boost::lexical_cast<technical_space>(std::string("xml"));
    BOOST_CHECK(r == technical_space::xml);
    r = boost::lexical_cast<technical_space>(std::string("technical_space::xml"));
    BOOST_CHECK(r == technical_space::xml);

    r = boost::lexical_cast<technical_space>(std::string("odb"));
    BOOST_CHECK(r == technical_space::odb);
    r = boost::lexical_cast<technical_space>(std::string("technical_space::odb"));
    BOOST_CHECK(r == technical_space::odb);

    r = boost::lexical_cast<technical_space>(std::string("sln"));
    BOOST_CHECK(r == technical_space::sln);
    r = boost::lexical_cast<technical_space>(std::string("technical_space::sln"));
    BOOST_CHECK(r == technical_space::sln);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::coding::meta_model::technical_space;
    BOOST_CHECK_THROW(boost::lexical_cast<technical_space>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::coding::meta_model::technical_space;
    std::string r;

    r = boost::lexical_cast<std::string>(technical_space::invalid);
    BOOST_CHECK(r == "technical_space::invalid");

    r = boost::lexical_cast<std::string>(technical_space::agnostic);
    BOOST_CHECK(r == "technical_space::agnostic");

    r = boost::lexical_cast<std::string>(technical_space::cpp);
    BOOST_CHECK(r == "technical_space::cpp");

    r = boost::lexical_cast<std::string>(technical_space::csharp);
    BOOST_CHECK(r == "technical_space::csharp");

    r = boost::lexical_cast<std::string>(technical_space::cmake);
    BOOST_CHECK(r == "technical_space::cmake");

    r = boost::lexical_cast<std::string>(technical_space::xml);
    BOOST_CHECK(r == "technical_space::xml");

    r = boost::lexical_cast<std::string>(technical_space::odb);
    BOOST_CHECK(r == "technical_space::odb");

    r = boost::lexical_cast<std::string>(technical_space::sln);
    BOOST_CHECK(r == "technical_space::sln");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma gcc diagnostic push
#pragma gcc diagnostic ignored "-Werror=conversion"
#endif
    using dogen::coding::meta_model::technical_space;
    const technical_space r(static_cast<technical_space>(18));
#if BOOST_COMP_GNUC
#pragma gcc diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(equal_enums_generate_the_same_hash) {
    dogen::coding::meta_model::technical_space_generator g;
    g();
    const auto a(g());
    const auto b(a);

    std::hash<dogen::coding::meta_model::technical_space> hasher;
    BOOST_CHECK(hasher(a) == hasher(b));
}

BOOST_AUTO_TEST_CASE(different_enums_generate_different_hashes) {
    dogen::coding::meta_model::technical_space_generator g;
    g();
    const auto a(g());
    const auto b(g());

    std::hash<dogen::coding::meta_model::technical_space> hasher;
    BOOST_CHECK(hasher(a) != hasher(b));
}

BOOST_AUTO_TEST_SUITE_END()
