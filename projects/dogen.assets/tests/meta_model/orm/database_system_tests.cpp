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
#include "dogen.assets/io/meta_model/orm/database_system_io.hpp"
#include "dogen.assets/types/meta_model/orm/database_system.hpp"
#include "dogen.assets/hash/meta_model/orm/database_system_hash.hpp"
#include "dogen.assets/test_data/meta_model/orm/database_system_td.hpp"
#include "dogen.assets/lexical_cast/meta_model/orm/database_system_lc.hpp"

BOOST_AUTO_TEST_SUITE(database_system_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::assets::meta_model::orm::database_system_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::assets::meta_model::orm::database_system;
    database_system r;

    r = boost::lexical_cast<database_system>(std::string("invalid"));
    BOOST_CHECK(r == database_system::invalid);
    r = boost::lexical_cast<database_system>(std::string("database_system::invalid"));
    BOOST_CHECK(r == database_system::invalid);

    r = boost::lexical_cast<database_system>(std::string("mysql"));
    BOOST_CHECK(r == database_system::mysql);
    r = boost::lexical_cast<database_system>(std::string("database_system::mysql"));
    BOOST_CHECK(r == database_system::mysql);

    r = boost::lexical_cast<database_system>(std::string("postgresql"));
    BOOST_CHECK(r == database_system::postgresql);
    r = boost::lexical_cast<database_system>(std::string("database_system::postgresql"));
    BOOST_CHECK(r == database_system::postgresql);

    r = boost::lexical_cast<database_system>(std::string("oracle"));
    BOOST_CHECK(r == database_system::oracle);
    r = boost::lexical_cast<database_system>(std::string("database_system::oracle"));
    BOOST_CHECK(r == database_system::oracle);

    r = boost::lexical_cast<database_system>(std::string("sql_server"));
    BOOST_CHECK(r == database_system::sql_server);
    r = boost::lexical_cast<database_system>(std::string("database_system::sql_server"));
    BOOST_CHECK(r == database_system::sql_server);

    r = boost::lexical_cast<database_system>(std::string("sqlite"));
    BOOST_CHECK(r == database_system::sqlite);
    r = boost::lexical_cast<database_system>(std::string("database_system::sqlite"));
    BOOST_CHECK(r == database_system::sqlite);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::assets::meta_model::orm::database_system;
    BOOST_CHECK_THROW(boost::lexical_cast<database_system>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::assets::meta_model::orm::database_system;
    std::string r;

    r = boost::lexical_cast<std::string>(database_system::invalid);
    BOOST_CHECK(r == "database_system::invalid");

    r = boost::lexical_cast<std::string>(database_system::mysql);
    BOOST_CHECK(r == "database_system::mysql");

    r = boost::lexical_cast<std::string>(database_system::postgresql);
    BOOST_CHECK(r == "database_system::postgresql");

    r = boost::lexical_cast<std::string>(database_system::oracle);
    BOOST_CHECK(r == "database_system::oracle");

    r = boost::lexical_cast<std::string>(database_system::sql_server);
    BOOST_CHECK(r == "database_system::sql_server");

    r = boost::lexical_cast<std::string>(database_system::sqlite);
    BOOST_CHECK(r == "database_system::sqlite");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::assets::meta_model::orm::database_system;
    const database_system r(static_cast<database_system>(16));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(equal_enums_generate_the_same_hash) {
    dogen::assets::meta_model::orm::database_system_generator g;
    g();
    const auto a(g());
    const auto b(a);

    std::hash<dogen::assets::meta_model::orm::database_system> hasher;
    BOOST_CHECK(hasher(a) == hasher(b));
}

BOOST_AUTO_TEST_CASE(different_enums_generate_different_hashes) {
    dogen::assets::meta_model::orm::database_system_generator g;
    g();
    const auto a(g());
    const auto b(g());

    std::hash<dogen::assets::meta_model::orm::database_system> hasher;
    BOOST_CHECK(hasher(a) != hasher(b));
}

BOOST_AUTO_TEST_SUITE_END()
