/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/cpp/io/enumeration_info_io.hpp"
#include "dogen/cpp/types/transformer.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string empty;
const std::string test_module("cpp");
const std::string test_suite("transformer_spec");

bool is_type_zero(const std::string& n) {
    return mock_model_factory::type_name(0) == n;
}

bool is_type_one(const std::string& n) {
    return mock_model_factory::type_name(1) == n;
}

bool is_package_zero(const std::string& n) {
    return mock_model_factory::package_name(0) == n;
}

bool is_package_one(const std::string& n) {
    return mock_model_factory::package_name(1) == n;
}

bool is_model_zero(const std::string& n) {
    return mock_model_factory::model_name(0) == n;
}

}

BOOST_AUTO_TEST_SUITE(transformer)

BOOST_AUTO_TEST_CASE(transforming_enumeration_results_in_expected_enumeration_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_results_in_expected_enumeration_info");

    const auto mt(dogen::sml::meta_types::enumeration);
    const auto m(mock_model_factory::build_single_type_model(0, mt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    dogen::cpp::transformer t;
    const auto e(t.transform(m.enumerations().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "enumeration: " << e;

    BOOST_CHECK(is_type_zero(e.name()));
    BOOST_CHECK(!e.documentation().empty());
    BOOST_CHECK(e.namespaces().size() == 1);
    BOOST_CHECK(is_model_zero(e.namespaces().front()));
    BOOST_CHECK(e.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e.enumerators().back().name()));
}

BOOST_AUTO_TEST_CASE(transforming_enumeration_in_package_results_in_expected_enumeration_info) {
    SETUP_TEST_LOG_SOURCE("transforming_enumeration_in_package_results_in_expected_enumeration_info");

    const auto mt(dogen::sml::meta_types::enumeration);
    const auto m0(
        mock_model_factory::build_single_type_model_in_package(0, mt, 1));
    BOOST_LOG_SEV(lg, debug) << "model 0: " << m0;
    BOOST_REQUIRE(m0.enumerations().size() == 1);

    dogen::cpp::transformer t;
    const auto e0(t.transform(m0.enumerations().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "enumeration 0: " << e0;

    BOOST_CHECK(is_type_zero(e0.name()));
    BOOST_CHECK(!e0.documentation().empty());
    BOOST_CHECK(e0.namespaces().size() == 2);
    BOOST_CHECK(is_model_zero(e0.namespaces().front()));
    BOOST_CHECK(is_package_zero(e0.namespaces().back()));

    BOOST_CHECK(e0.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e0.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e0.enumerators().back().name()));

    const auto m1(
        mock_model_factory::build_single_type_model_in_package(0, mt, 2));
    BOOST_LOG_SEV(lg, debug) << "model 1: " << m1;
    BOOST_REQUIRE(m0.enumerations().size() == 1);

    const auto e1(t.transform(m1.enumerations().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "enumeration 1: " << e1;
    BOOST_CHECK(is_type_zero(e1.name()));
    BOOST_CHECK(!e1.documentation().empty());
    BOOST_CHECK(e1.namespaces().size() == 3);
    BOOST_CHECK(is_model_zero(e1.namespaces().front()));
    BOOST_CHECK(is_package_one(e1.namespaces().back()));

    BOOST_CHECK(e1.enumerators().size() == 2);
    BOOST_CHECK(is_type_zero(e1.enumerators().front().name()));
    BOOST_CHECK(is_type_one(e1.enumerators().back().name()));
}

BOOST_AUTO_TEST_SUITE_END()
