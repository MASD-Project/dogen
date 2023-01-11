/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include <boost/serialization/nvp.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.org/io/entities/drawer_type_io.hpp"
#include "dogen.org/types/entities/drawer_type.hpp"
#include "dogen.org/hash/entities/drawer_type_hash.hpp"
#include "dogen.org/test_data/entities/drawer_type_td.hpp"
#include "dogen.org/lexical_cast/entities/drawer_type_lc.hpp"
#include "dogen.org/serialization/entities/drawer_type_ser.hpp"

BOOST_AUTO_TEST_SUITE(drawer_type_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::org::entities::drawer_type_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::org::entities::drawer_type;
    drawer_type r;

    r = boost::lexical_cast<drawer_type>(std::string("invalid"));
    BOOST_CHECK(r == drawer_type::invalid);
    r = boost::lexical_cast<drawer_type>(std::string("drawer_type::invalid"));
    BOOST_CHECK(r == drawer_type::invalid);

    r = boost::lexical_cast<drawer_type>(std::string("regular"));
    BOOST_CHECK(r == drawer_type::regular);
    r = boost::lexical_cast<drawer_type>(std::string("drawer_type::regular"));
    BOOST_CHECK(r == drawer_type::regular);

    r = boost::lexical_cast<drawer_type>(std::string("property_drawer"));
    BOOST_CHECK(r == drawer_type::property_drawer);
    r = boost::lexical_cast<drawer_type>(std::string("drawer_type::property_drawer"));
    BOOST_CHECK(r == drawer_type::property_drawer);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::org::entities::drawer_type;
    BOOST_CHECK_THROW(boost::lexical_cast<drawer_type>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::org::entities::drawer_type;
    std::string r;

    r = boost::lexical_cast<std::string>(drawer_type::invalid);
    BOOST_CHECK(r == "drawer_type::invalid");

    r = boost::lexical_cast<std::string>(drawer_type::regular);
    BOOST_CHECK(r == "drawer_type::regular");

    r = boost::lexical_cast<std::string>(drawer_type::property_drawer);
    BOOST_CHECK(r == "drawer_type::property_drawer");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::org::entities::drawer_type;
    const drawer_type r(static_cast<drawer_type>(13));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(xml_roundtrip_produces_the_same_entity) {
    dogen::org::entities::drawer_type_generator g;
    const auto a(g());

    using namespace boost::archive;
    std::ostringstream os;
    {
        xml_oarchive oa(os);
        oa << BOOST_SERIALIZATION_NVP(a);
    }

    dogen::org::entities::drawer_type b = dogen::org::entities::drawer_type();
    std::istringstream is(os.str());
    {
        xml_iarchive ia(is);
        ia >> BOOST_SERIALIZATION_NVP(b);
    }
    BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(text_roundtrip_produces_the_same_entity) {
    dogen::org::entities::drawer_type_generator g;
    const auto a(g());

    using namespace boost::archive;
    std::ostringstream os;
    {
        xml_oarchive oa(os);
        oa << BOOST_SERIALIZATION_NVP(a);
    }

    dogen::org::entities::drawer_type b = dogen::org::entities::drawer_type();
    std::istringstream is(os.str());
    {
        xml_iarchive ia(is);
        ia >> BOOST_SERIALIZATION_NVP(b);
    }
    BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(binary_roundtrip_produces_the_same_entity) {
    dogen::org::entities::drawer_type_generator g;
    const auto a(g());

    using namespace boost::archive;
    std::ostringstream os;
    {
        text_oarchive oa(os);
        oa << a;
    }

    dogen::org::entities::drawer_type b = dogen::org::entities::drawer_type();
    std::istringstream is(os.str());
    {
        text_iarchive ia(is);
        ia >> b;
    }
    BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(equal_enums_generate_the_same_hash) {
    dogen::org::entities::drawer_type_generator g;
    g();
    const auto a(g());
    const auto b(a);

    std::hash<dogen::org::entities::drawer_type> hasher;
    BOOST_CHECK(hasher(a) == hasher(b));
}

BOOST_AUTO_TEST_CASE(different_enums_generate_different_hashes) {
    dogen::org::entities::drawer_type_generator g;
    g();
    const auto a(g());
    const auto b(g());

    std::hash<dogen::org::entities::drawer_type> hasher;
    BOOST_CHECK(hasher(a) != hasher(b));
}

BOOST_AUTO_TEST_SUITE_END()
