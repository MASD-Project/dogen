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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test_data/yarn_upsilon.hpp"
#include "dogen/upsilon/types/model.hpp"
#include "dogen/upsilon/types/schema.hpp"
#include "dogen/upsilon/types/config.hpp"
#include "dogen/upsilon/types/type_information.hpp"
#include "dogen/upsilon/io/model_io.hpp"
#include "dogen/upsilon/io/schema_io.hpp"
#include "dogen/upsilon/io/config_io.hpp"
#include "dogen/upsilon/io/type_information_io.hpp"
#include "dogen/upsilon/types/hydrator.hpp"

namespace {

const std::string empty;
const std::string test_module("upsilon");
const std::string test_suite("hydrator_tests");

}

BOOST_AUTO_TEST_SUITE(hydrator_tests)

BOOST_AUTO_TEST_CASE(hydrating_config_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_config_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_test_model_configuration_xml());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate_config(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;
}

BOOST_AUTO_TEST_CASE(hydrating_phi_model_typeinfos_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_phi_model_typeinfos_model_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_phi_model_xml_typeinfos());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate_type_information(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;
}

BOOST_AUTO_TEST_CASE(hydrating_phi_model_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_phi_model_model_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_phi_model_xml());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;
}

BOOST_AUTO_TEST_CASE(hydrating_zeta_model_typeinfos_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_phi_model_typeinfos_model_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_zeta_model_xml_typeinfos());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;
}

BOOST_AUTO_TEST_CASE(hydrating_zeta_model_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_zeta_model_model_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_zeta_model_xml());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;
}

BOOST_AUTO_TEST_SUITE_END()
