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
#include "dogen.coding/io/meta_model/static_stereotypes_io.hpp"
#include "dogen.coding/types/meta_model/static_stereotypes.hpp"
#include "dogen.coding/test_data/meta_model/static_stereotypes_td.hpp"
#include "dogen.coding/lexical_cast/meta_model/static_stereotypes_lc.hpp"

BOOST_AUTO_TEST_SUITE(static_stereotypes_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::coding::meta_model::static_stereotypes_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::coding::meta_model::static_stereotypes;
    static_stereotypes r;

    r = boost::lexical_cast<static_stereotypes>(std::string("invalid"));
    BOOST_CHECK(r == static_stereotypes::invalid);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::invalid"));
    BOOST_CHECK(r == static_stereotypes::invalid);

    r = boost::lexical_cast<static_stereotypes>(std::string("object"));
    BOOST_CHECK(r == static_stereotypes::object);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::object"));
    BOOST_CHECK(r == static_stereotypes::object);

    r = boost::lexical_cast<static_stereotypes>(std::string("object_template"));
    BOOST_CHECK(r == static_stereotypes::object_template);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::object_template"));
    BOOST_CHECK(r == static_stereotypes::object_template);

    r = boost::lexical_cast<static_stereotypes>(std::string("exception"));
    BOOST_CHECK(r == static_stereotypes::exception);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::exception"));
    BOOST_CHECK(r == static_stereotypes::exception);

    r = boost::lexical_cast<static_stereotypes>(std::string("primitive"));
    BOOST_CHECK(r == static_stereotypes::primitive);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::primitive"));
    BOOST_CHECK(r == static_stereotypes::primitive);

    r = boost::lexical_cast<static_stereotypes>(std::string("enumeration"));
    BOOST_CHECK(r == static_stereotypes::enumeration);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::enumeration"));
    BOOST_CHECK(r == static_stereotypes::enumeration);

    r = boost::lexical_cast<static_stereotypes>(std::string("module"));
    BOOST_CHECK(r == static_stereotypes::module);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::module"));
    BOOST_CHECK(r == static_stereotypes::module);

    r = boost::lexical_cast<static_stereotypes>(std::string("builtin"));
    BOOST_CHECK(r == static_stereotypes::builtin);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::builtin"));
    BOOST_CHECK(r == static_stereotypes::builtin);

    r = boost::lexical_cast<static_stereotypes>(std::string("visitable"));
    BOOST_CHECK(r == static_stereotypes::visitable);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::visitable"));
    BOOST_CHECK(r == static_stereotypes::visitable);

    r = boost::lexical_cast<static_stereotypes>(std::string("fluent"));
    BOOST_CHECK(r == static_stereotypes::fluent);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::fluent"));
    BOOST_CHECK(r == static_stereotypes::fluent);

    r = boost::lexical_cast<static_stereotypes>(std::string("immutable"));
    BOOST_CHECK(r == static_stereotypes::immutable);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::immutable"));
    BOOST_CHECK(r == static_stereotypes::immutable);

    r = boost::lexical_cast<static_stereotypes>(std::string("orm_object"));
    BOOST_CHECK(r == static_stereotypes::orm_object);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::orm_object"));
    BOOST_CHECK(r == static_stereotypes::orm_object);

    r = boost::lexical_cast<static_stereotypes>(std::string("orm_value"));
    BOOST_CHECK(r == static_stereotypes::orm_value);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::orm_value"));
    BOOST_CHECK(r == static_stereotypes::orm_value);

    r = boost::lexical_cast<static_stereotypes>(std::string("modeline_group"));
    BOOST_CHECK(r == static_stereotypes::modeline_group);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::modeline_group"));
    BOOST_CHECK(r == static_stereotypes::modeline_group);

    r = boost::lexical_cast<static_stereotypes>(std::string("modeline"));
    BOOST_CHECK(r == static_stereotypes::modeline);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::modeline"));
    BOOST_CHECK(r == static_stereotypes::modeline);

    r = boost::lexical_cast<static_stereotypes>(std::string("generation_marker"));
    BOOST_CHECK(r == static_stereotypes::generation_marker);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::generation_marker"));
    BOOST_CHECK(r == static_stereotypes::generation_marker);

    r = boost::lexical_cast<static_stereotypes>(std::string("licence"));
    BOOST_CHECK(r == static_stereotypes::licence);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::licence"));
    BOOST_CHECK(r == static_stereotypes::licence);

    r = boost::lexical_cast<static_stereotypes>(std::string("variability_profile_template"));
    BOOST_CHECK(r == static_stereotypes::variability_profile_template);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::variability_profile_template"));
    BOOST_CHECK(r == static_stereotypes::variability_profile_template);

    r = boost::lexical_cast<static_stereotypes>(std::string("variability_feature_bundle"));
    BOOST_CHECK(r == static_stereotypes::variability_feature_bundle);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::variability_feature_bundle"));
    BOOST_CHECK(r == static_stereotypes::variability_feature_bundle);

    r = boost::lexical_cast<static_stereotypes>(std::string("variability_feature_template_initializer"));
    BOOST_CHECK(r == static_stereotypes::variability_feature_template_initializer);
    r = boost::lexical_cast<static_stereotypes>(std::string("static_stereotypes::variability_feature_template_initializer"));
    BOOST_CHECK(r == static_stereotypes::variability_feature_template_initializer);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::coding::meta_model::static_stereotypes;
    BOOST_CHECK_THROW(boost::lexical_cast<static_stereotypes>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::coding::meta_model::static_stereotypes;
    std::string r;

    r = boost::lexical_cast<std::string>(static_stereotypes::invalid);
    BOOST_CHECK(r == "static_stereotypes::invalid");

    r = boost::lexical_cast<std::string>(static_stereotypes::object);
    BOOST_CHECK(r == "static_stereotypes::object");

    r = boost::lexical_cast<std::string>(static_stereotypes::object_template);
    BOOST_CHECK(r == "static_stereotypes::object_template");

    r = boost::lexical_cast<std::string>(static_stereotypes::exception);
    BOOST_CHECK(r == "static_stereotypes::exception");

    r = boost::lexical_cast<std::string>(static_stereotypes::primitive);
    BOOST_CHECK(r == "static_stereotypes::primitive");

    r = boost::lexical_cast<std::string>(static_stereotypes::enumeration);
    BOOST_CHECK(r == "static_stereotypes::enumeration");

    r = boost::lexical_cast<std::string>(static_stereotypes::module);
    BOOST_CHECK(r == "static_stereotypes::module");

    r = boost::lexical_cast<std::string>(static_stereotypes::builtin);
    BOOST_CHECK(r == "static_stereotypes::builtin");

    r = boost::lexical_cast<std::string>(static_stereotypes::visitable);
    BOOST_CHECK(r == "static_stereotypes::visitable");

    r = boost::lexical_cast<std::string>(static_stereotypes::fluent);
    BOOST_CHECK(r == "static_stereotypes::fluent");

    r = boost::lexical_cast<std::string>(static_stereotypes::immutable);
    BOOST_CHECK(r == "static_stereotypes::immutable");

    r = boost::lexical_cast<std::string>(static_stereotypes::orm_object);
    BOOST_CHECK(r == "static_stereotypes::orm_object");

    r = boost::lexical_cast<std::string>(static_stereotypes::orm_value);
    BOOST_CHECK(r == "static_stereotypes::orm_value");

    r = boost::lexical_cast<std::string>(static_stereotypes::modeline_group);
    BOOST_CHECK(r == "static_stereotypes::modeline_group");

    r = boost::lexical_cast<std::string>(static_stereotypes::modeline);
    BOOST_CHECK(r == "static_stereotypes::modeline");

    r = boost::lexical_cast<std::string>(static_stereotypes::generation_marker);
    BOOST_CHECK(r == "static_stereotypes::generation_marker");

    r = boost::lexical_cast<std::string>(static_stereotypes::licence);
    BOOST_CHECK(r == "static_stereotypes::licence");

    r = boost::lexical_cast<std::string>(static_stereotypes::variability_profile_template);
    BOOST_CHECK(r == "static_stereotypes::variability_profile_template");

    r = boost::lexical_cast<std::string>(static_stereotypes::variability_feature_bundle);
    BOOST_CHECK(r == "static_stereotypes::variability_feature_bundle");

    r = boost::lexical_cast<std::string>(static_stereotypes::variability_feature_template_initializer);
    BOOST_CHECK(r == "static_stereotypes::variability_feature_template_initializer");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::coding::meta_model::static_stereotypes;
    const static_stereotypes r(static_cast<static_stereotypes>(30));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
