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
#include "dogen.variability/io/meta_model/template_kind_io.hpp"
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.variability/test_data/meta_model/template_kind_td.hpp"
#include "dogen.variability/lexical_cast/meta_model/template_kind_lc.hpp"

BOOST_AUTO_TEST_SUITE(template_kind_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::variability::meta_model::template_kind_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(casting_valid_strings_produces_expected_enumeration) {
    using dogen::variability::meta_model::template_kind;
    template_kind r;

    r = boost::lexical_cast<template_kind>(std::string("invalid"));
    BOOST_CHECK(r == template_kind::invalid);
    r = boost::lexical_cast<template_kind>(std::string("template_kind::invalid"));
    BOOST_CHECK(r == template_kind::invalid);

    r = boost::lexical_cast<template_kind>(std::string("instance"));
    BOOST_CHECK(r == template_kind::instance);
    r = boost::lexical_cast<template_kind>(std::string("template_kind::instance"));
    BOOST_CHECK(r == template_kind::instance);

    r = boost::lexical_cast<template_kind>(std::string("recursive_template"));
    BOOST_CHECK(r == template_kind::recursive_template);
    r = boost::lexical_cast<template_kind>(std::string("template_kind::recursive_template"));
    BOOST_CHECK(r == template_kind::recursive_template);

    r = boost::lexical_cast<template_kind>(std::string("backend_template"));
    BOOST_CHECK(r == template_kind::backend_template);
    r = boost::lexical_cast<template_kind>(std::string("template_kind::backend_template"));
    BOOST_CHECK(r == template_kind::backend_template);

    r = boost::lexical_cast<template_kind>(std::string("facet_template"));
    BOOST_CHECK(r == template_kind::facet_template);
    r = boost::lexical_cast<template_kind>(std::string("template_kind::facet_template"));
    BOOST_CHECK(r == template_kind::facet_template);

    r = boost::lexical_cast<template_kind>(std::string("archetype_template"));
    BOOST_CHECK(r == template_kind::archetype_template);
    r = boost::lexical_cast<template_kind>(std::string("template_kind::archetype_template"));
    BOOST_CHECK(r == template_kind::archetype_template);
}

BOOST_AUTO_TEST_CASE(casting_invalid_string_throws) {
    using dogen::variability::meta_model::template_kind;
    BOOST_CHECK_THROW(boost::lexical_cast<template_kind>(std::string("DOGEN_THIS_IS_INVALID_DOGEN")),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(casting_valid_enumerations_produces_expected_strings) {
    using dogen::variability::meta_model::template_kind;
    std::string r;

    r = boost::lexical_cast<std::string>(template_kind::invalid);
    BOOST_CHECK(r == "template_kind::invalid");

    r = boost::lexical_cast<std::string>(template_kind::instance);
    BOOST_CHECK(r == "template_kind::instance");

    r = boost::lexical_cast<std::string>(template_kind::recursive_template);
    BOOST_CHECK(r == "template_kind::recursive_template");

    r = boost::lexical_cast<std::string>(template_kind::backend_template);
    BOOST_CHECK(r == "template_kind::backend_template");

    r = boost::lexical_cast<std::string>(template_kind::facet_template);
    BOOST_CHECK(r == "template_kind::facet_template");

    r = boost::lexical_cast<std::string>(template_kind::archetype_template);
    BOOST_CHECK(r == "template_kind::archetype_template");
}

BOOST_AUTO_TEST_CASE(casting_invalid_enumeration_throws) {
#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    using dogen::variability::meta_model::template_kind;
    const template_kind r(static_cast<template_kind>(16));
#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif
    BOOST_CHECK_THROW(boost::lexical_cast<std::string>(r),
        boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
