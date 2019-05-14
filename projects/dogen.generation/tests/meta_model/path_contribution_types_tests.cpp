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
#include "dogen.generation/io/meta_model/path_contribution_types_io.hpp"
#include "dogen.generation/types/meta_model/path_contribution_types.hpp"
#include "dogen.generation/test_data/meta_model/path_contribution_types_td.hpp"
#include "dogen.generation/lexical_cast/meta_model/path_contribution_types_lc.hpp"

BOOST_AUTO_TEST_SUITE(path_contribution_types_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::generation::meta_model::path_contribution_types_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::generation::meta_model::path_contribution_types;
    path_contribution_types r;

    r = boost::lexical_cast<path_contribution_types>(std::string("invalid"));
    BOOST_CHECK(r == path_contribution_types::invalid);
    r = boost::lexical_cast<path_contribution_types>(std::string("path_contribution_types::invalid"));
    BOOST_CHECK(r == path_contribution_types::invalid);

    r = boost::lexical_cast<path_contribution_types>(std::string("none"));
    BOOST_CHECK(r == path_contribution_types::none);
    r = boost::lexical_cast<path_contribution_types>(std::string("path_contribution_types::none"));
    BOOST_CHECK(r == path_contribution_types::none);

    r = boost::lexical_cast<path_contribution_types>(std::string("as_folders"));
    BOOST_CHECK(r == path_contribution_types::as_folders);
    r = boost::lexical_cast<path_contribution_types>(std::string("path_contribution_types::as_folders"));
    BOOST_CHECK(r == path_contribution_types::as_folders);

    r = boost::lexical_cast<path_contribution_types>(std::string("as_path_components"));
    BOOST_CHECK(r == path_contribution_types::as_path_components);
    r = boost::lexical_cast<path_contribution_types>(std::string("path_contribution_types::as_path_components"));
    BOOST_CHECK(r == path_contribution_types::as_path_components);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::generation::meta_model::path_contribution_types;
    BOOST_CHECK_THROW(boost::lexical_cast<path_contribution_types>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::generation::meta_model::path_contribution_types;
    std::string r;

    r = boost::lexical_cast<std::string>(path_contribution_types::invalid);
    BOOST_CHECK(r == "path_contribution_types::invalid");

    r = boost::lexical_cast<std::string>(path_contribution_types::none);
    BOOST_CHECK(r == "path_contribution_types::none");

    r = boost::lexical_cast<std::string>(path_contribution_types::as_folders);
    BOOST_CHECK(r == "path_contribution_types::as_folders");

    r = boost::lexical_cast<std::string>(path_contribution_types::as_path_components);
    BOOST_CHECK(r == "path_contribution_types::as_path_components");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::generation::meta_model::path_contribution_types;
    const path_contribution_types r(static_cast<path_contribution_types>(14));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
