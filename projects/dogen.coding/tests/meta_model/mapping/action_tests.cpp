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
#include "dogen.coding/io/meta_model/mapping/action_io.hpp"
#include "dogen.coding/types/meta_model/mapping/action.hpp"
#include "dogen.coding/test_data/meta_model/mapping/action_td.hpp"
#include "dogen.coding/lexical_cast/meta_model/mapping/action_lc.hpp"

BOOST_AUTO_TEST_SUITE(action_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::coding::meta_model::mapping::action_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::coding::meta_model::mapping::action;
    action r;

    r = boost::lexical_cast<action>(std::string("invalid"));
    BOOST_CHECK(r == action::invalid);
    r = boost::lexical_cast<action>(std::string("action::invalid"));
    BOOST_CHECK(r == action::invalid);

    r = boost::lexical_cast<action>(std::string("translate"));
    BOOST_CHECK(r == action::translate);
    r = boost::lexical_cast<action>(std::string("action::translate"));
    BOOST_CHECK(r == action::translate);

    r = boost::lexical_cast<action>(std::string("erase"));
    BOOST_CHECK(r == action::erase);
    r = boost::lexical_cast<action>(std::string("action::erase"));
    BOOST_CHECK(r == action::erase);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::coding::meta_model::mapping::action;
    BOOST_CHECK_THROW(boost::lexical_cast<action>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::coding::meta_model::mapping::action;
    std::string r;

    r = boost::lexical_cast<std::string>(action::invalid);
    BOOST_CHECK(r == "action::invalid");

    r = boost::lexical_cast<std::string>(action::translate);
    BOOST_CHECK(r == "action::translate");

    r = boost::lexical_cast<std::string>(action::erase);
    BOOST_CHECK(r == "action::erase");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::coding::meta_model::mapping::action;
    const action r(static_cast<action>(13));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
