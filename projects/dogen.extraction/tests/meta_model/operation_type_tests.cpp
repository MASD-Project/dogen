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
#include "dogen.extraction/io/meta_model/operation_type_io.hpp"
#include "dogen.extraction/types/meta_model/operation_type.hpp"
#include "dogen.extraction/hash/meta_model/operation_type_hash.hpp"
#include "dogen.extraction/test_data/meta_model/operation_type_td.hpp"
#include "dogen.extraction/lexical_cast/meta_model/operation_type_lc.hpp"

BOOST_AUTO_TEST_SUITE(operation_type_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::extraction::meta_model::operation_type_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::extraction::meta_model::operation_type;
    operation_type r;

    r = boost::lexical_cast<operation_type>(std::string("invalid"));
    BOOST_CHECK(r == operation_type::invalid);
    r = boost::lexical_cast<operation_type>(std::string("operation_type::invalid"));
    BOOST_CHECK(r == operation_type::invalid);

    r = boost::lexical_cast<operation_type>(std::string("create_only"));
    BOOST_CHECK(r == operation_type::create_only);
    r = boost::lexical_cast<operation_type>(std::string("operation_type::create_only"));
    BOOST_CHECK(r == operation_type::create_only);

    r = boost::lexical_cast<operation_type>(std::string("write"));
    BOOST_CHECK(r == operation_type::write);
    r = boost::lexical_cast<operation_type>(std::string("operation_type::write"));
    BOOST_CHECK(r == operation_type::write);

    r = boost::lexical_cast<operation_type>(std::string("ignore"));
    BOOST_CHECK(r == operation_type::ignore);
    r = boost::lexical_cast<operation_type>(std::string("operation_type::ignore"));
    BOOST_CHECK(r == operation_type::ignore);

    r = boost::lexical_cast<operation_type>(std::string("remove"));
    BOOST_CHECK(r == operation_type::remove);
    r = boost::lexical_cast<operation_type>(std::string("operation_type::remove"));
    BOOST_CHECK(r == operation_type::remove);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::extraction::meta_model::operation_type;
    BOOST_CHECK_THROW(boost::lexical_cast<operation_type>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::extraction::meta_model::operation_type;
    std::string r;

    r = boost::lexical_cast<std::string>(operation_type::invalid);
    BOOST_CHECK(r == "operation_type::invalid");

    r = boost::lexical_cast<std::string>(operation_type::create_only);
    BOOST_CHECK(r == "operation_type::create_only");

    r = boost::lexical_cast<std::string>(operation_type::write);
    BOOST_CHECK(r == "operation_type::write");

    r = boost::lexical_cast<std::string>(operation_type::ignore);
    BOOST_CHECK(r == "operation_type::ignore");

    r = boost::lexical_cast<std::string>(operation_type::remove);
    BOOST_CHECK(r == "operation_type::remove");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
    using dogen::extraction::meta_model::operation_type;
    const operation_type r(static_cast<operation_type>(15));
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(equal_enums_generate_the_same_hash) {
    dogen::extraction::meta_model::operation_type_generator g;
    g();
    const auto a(g());
    const auto b(a);

    std::hash<dogen::extraction::meta_model::operation_type> hasher;
    BOOST_CHECK(hasher(a) == hasher(b));
}

BOOST_AUTO_TEST_CASE(different_enums_generate_different_hashes) {
    dogen::extraction::meta_model::operation_type_generator g;
    g();
    const auto a(g());
    const auto b(g());

    std::hash<dogen::extraction::meta_model::operation_type> hasher;
    BOOST_CHECK(hasher(a) != hasher(b));
}

BOOST_AUTO_TEST_SUITE_END()
