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
#include "dogen/utility/io/vector_io.hpp"
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

const std::string public_location("projects/test_models/common");
const std::string private_location("projects/test_models");

}

BOOST_AUTO_TEST_SUITE(hydrator_tests)

BOOST_AUTO_TEST_CASE(hydrating_config_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_config_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_test_model_configuration_xml());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate_config(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;

    BOOST_CHECK(a.directory().public_location() == public_location);
    BOOST_CHECK(a.directory().private_location() == private_location);

    BOOST_REQUIRE(a.schema_refs().size() == 2);
    BOOST_CHECK(a.schema_refs()[0].name() == "Zeta");
    BOOST_CHECK(
        a.schema_refs()[0].file() == "test_data/upsilon/Zeta.Model.xml");
    BOOST_CHECK(a.schema_refs()[1].name() == "Phi");
    BOOST_CHECK(a.schema_refs()[1].file() == "test_data/upsilon/Phi.Model.xml");

    BOOST_REQUIRE(a.outputs().size() == 1);
    const auto& o(a.outputs()[0]);
    BOOST_REQUIRE(o.representations().size() == 3);

    using dogen::upsilon::target_types;
    BOOST_CHECK(o.representations()[0].target() == target_types::java);
    BOOST_CHECK(!o.representations()[0].pof());
    BOOST_CHECK(o.representations()[1].target() == target_types::cpp);
    BOOST_CHECK(o.representations()[1].pof());
    BOOST_CHECK(o.representations()[2].target() == target_types::cs);
    BOOST_CHECK(!o.representations()[2].pof());
}

BOOST_AUTO_TEST_CASE(hydrating_phi_model_typeinfos_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_phi_model_typeinfos_model_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_phi_model_xml_typeinfos());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate_type_information(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;

    BOOST_REQUIRE(a.size() == 4);
    BOOST_CHECK(a[0].name() == "Date");
    BOOST_CHECK(a[0].pof_id() == "5123");

    BOOST_CHECK(a[1].name() == "TestType");
    BOOST_CHECK(a[1].pof_id() == "5124");

    BOOST_CHECK(a[2].name() == "CollectionTestType");
    BOOST_CHECK(a[2].pof_id() == "5125");

    BOOST_CHECK(a[3].name() == "Enumeration");
    BOOST_CHECK(a[3].pof_id() == "5154");
}

BOOST_AUTO_TEST_CASE(hydrating_phi_schema_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_phi_schema_model_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_phi_model_xml());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate_schema(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;

    BOOST_CHECK(a.name() == "Phi");
    BOOST_CHECK(a.id_min() == "1001");
    BOOST_CHECK(a.id_max() == "10000");
    BOOST_CHECK(a.base_guid() == "469C1EBC-57F8-458A-A892-1FF640846124");

    BOOST_REQUIRE(a.dependencies().size() == 1);
    BOOST_CHECK(a.dependencies()[0].name() == "Zeta");

    BOOST_REQUIRE(a.tags().size() == 2);
    BOOST_CHECK(a.tags()[0].name() == "Configuration");
    BOOST_CHECK(a.tags()[0].comment() ==
        "Types that represent configurations.");
    BOOST_CHECK(a.tags()[1].name() == "AnotherTag");
    BOOST_CHECK(a.tags()[1].comment() == "Another Comment");
}

BOOST_AUTO_TEST_CASE(hydrating_zeta_model_typeinfos_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_zeta_model_typeinfos_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_zeta_model_xml_typeinfos());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate_type_information(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;

    BOOST_REQUIRE(a.size() == 5);
    BOOST_CHECK(a[0].name() == "MissingValue");
    BOOST_CHECK(a[0].pof_id() == "1123");

    BOOST_CHECK(a[1].name() == "Binary");
    BOOST_CHECK(a[1].pof_id() == "1124");

    BOOST_CHECK(a[2].name() == "Date");
    BOOST_CHECK(a[2].pof_id() == "1125");

    BOOST_CHECK(a[3].name() == "ModelValues");
    BOOST_CHECK(a[3].pof_id() == "1154");

    BOOST_CHECK(a[4].name() == "Binaries");
    BOOST_CHECK(a[4].pof_id() == "1155");
}

BOOST_AUTO_TEST_CASE(hydrating_zeta_schema_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_zeta_schema_model_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_zeta_model_xml());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate_schema(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;

    BOOST_CHECK(a.name() == "Zeta");
    BOOST_CHECK(a.id_min() == "1100");
    BOOST_CHECK(a.id_max() == "1500");
    BOOST_CHECK(a.base_guid() == "23188BEF-A85B-4CC2-AE27-508CE5EE286E");
    BOOST_CHECK(a.dependencies().empty());

    BOOST_REQUIRE(a.tags().size() == 1);
    BOOST_CHECK(a.tags()[0].name() == "ZetaTypes");
    BOOST_CHECK(a.tags()[0].comment().empty());
}

BOOST_AUTO_TEST_SUITE_END()
