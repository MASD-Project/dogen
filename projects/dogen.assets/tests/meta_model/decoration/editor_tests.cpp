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
#include "dogen.assets/io/meta_model/decoration/editor_io.hpp"
#include "dogen.assets/types/meta_model/decoration/editor.hpp"
#include "dogen.assets/test_data/meta_model/decoration/editor_td.hpp"
#include "dogen.assets/lexical_cast/meta_model/decoration/editor_lc.hpp"

BOOST_AUTO_TEST_SUITE(editor_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::assets::meta_model::decoration::editor_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::assets::meta_model::decoration::editor;
    editor r;

    r = boost::lexical_cast<editor>(std::string("invalid"));
    BOOST_CHECK(r == editor::invalid);
    r = boost::lexical_cast<editor>(std::string("editor::invalid"));
    BOOST_CHECK(r == editor::invalid);

    r = boost::lexical_cast<editor>(std::string("emacs"));
    BOOST_CHECK(r == editor::emacs);
    r = boost::lexical_cast<editor>(std::string("editor::emacs"));
    BOOST_CHECK(r == editor::emacs);

    r = boost::lexical_cast<editor>(std::string("vi"));
    BOOST_CHECK(r == editor::vi);
    r = boost::lexical_cast<editor>(std::string("editor::vi"));
    BOOST_CHECK(r == editor::vi);

    r = boost::lexical_cast<editor>(std::string("vim"));
    BOOST_CHECK(r == editor::vim);
    r = boost::lexical_cast<editor>(std::string("editor::vim"));
    BOOST_CHECK(r == editor::vim);

    r = boost::lexical_cast<editor>(std::string("ex"));
    BOOST_CHECK(r == editor::ex);
    r = boost::lexical_cast<editor>(std::string("editor::ex"));
    BOOST_CHECK(r == editor::ex);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::assets::meta_model::decoration::editor;
    BOOST_CHECK_THROW(boost::lexical_cast<editor>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::assets::meta_model::decoration::editor;
    std::string r;

    r = boost::lexical_cast<std::string>(editor::invalid);
    BOOST_CHECK(r == "editor::invalid");

    r = boost::lexical_cast<std::string>(editor::emacs);
    BOOST_CHECK(r == "editor::emacs");

    r = boost::lexical_cast<std::string>(editor::vi);
    BOOST_CHECK(r == "editor::vi");

    r = boost::lexical_cast<std::string>(editor::vim);
    BOOST_CHECK(r == "editor::vim");

    r = boost::lexical_cast<std::string>(editor::ex);
    BOOST_CHECK(r == "editor::ex");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::assets::meta_model::decoration::editor;
    const editor r(static_cast<editor>(15));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
