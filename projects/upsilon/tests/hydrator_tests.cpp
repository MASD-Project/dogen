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
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/yarn_upsilon.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/upsilon/serialization/registrar_ser.hpp"
#include "dogen/upsilon/types/model.hpp"
#include "dogen/upsilon/serialization/model_ser.hpp"
#include "dogen/upsilon/types/type.hpp"
#include "dogen/upsilon/types/primitive.hpp"
#include "dogen/upsilon/types/enumeration.hpp"
#include "dogen/upsilon/types/compound.hpp"
#include "dogen/upsilon/types/collection.hpp"
#include "dogen/upsilon/types/schema.hpp"
#include "dogen/upsilon/types/config.hpp"
#include "dogen/upsilon/types/type_information.hpp"
#include "dogen/upsilon/io/model_io.hpp"
#include "dogen/upsilon/io/schema_io.hpp"
#include "dogen/upsilon/io/config_io.hpp"
#include "dogen/upsilon/io/type_information_io.hpp"
#include "dogen/upsilon/types/hydration_error.hpp"
#include "dogen/upsilon/types/hydrator.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::upsilon::register_types<Archive>(ar);
}

namespace {

const std::string empty;
const std::string test_module("upsilon");
const std::string test_suite("hydrator_tests");

const std::string public_location("projects/test_models/common");
const std::string private_location("projects/test_models");

const std::string schema_not_found("Could not locate schema: ");

}

using dogen::utility::test::contains_checker;

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
        a.schema_refs()[0].file() ==
        "test_data/yarn.upsilon/input/Zeta.Model.xml");
    BOOST_CHECK(a.schema_refs()[1].name() == "Phi");
    BOOST_CHECK(a.schema_refs()[1].file() ==
        "test_data/yarn.upsilon/input/Phi.Model.xml");

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

    const auto& entries(a.entries());
    BOOST_REQUIRE(entries.size() == 4);
    BOOST_CHECK(entries[0].name() == "Date");
    BOOST_CHECK(entries[0].pof_id() == "5123");

    BOOST_CHECK(entries[1].name() == "TestType");
    BOOST_CHECK(entries[1].pof_id() == "5124");

    BOOST_CHECK(entries[2].name() == "CollectionTestType");
    BOOST_CHECK(entries[2].pof_id() == "5125");

    BOOST_CHECK(entries[3].name() == "Enumeration");
    BOOST_CHECK(entries[3].pof_id() == "5154");
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

    BOOST_REQUIRE(a.types().size() == 5);

    const auto& type_0(*a.types()[0]);
    BOOST_CHECK(type_0.name() == "Date");
    BOOST_CHECK(type_0.extends().empty());
    BOOST_CHECK(type_0.pof_id() == "1125");
    BOOST_REQUIRE(type_0.tag_refs().size() == 1);
    BOOST_CHECK(type_0.tag_refs()[0] == "ZetaTypes");

    const auto ptr_0(dynamic_cast<const dogen::upsilon::primitive*>(&type_0));
    BOOST_REQUIRE(ptr_0 != nullptr);

    const auto& primitive(*ptr_0);
    using dogen::upsilon::intrinsic_types;
    BOOST_CHECK(primitive.intrinsic() == intrinsic_types::date);
    BOOST_CHECK(primitive.default_value() == "1970-01-01");

    const auto& type_1(*a.types()[1]);
    BOOST_CHECK(type_1.name() == "TestType");
    BOOST_CHECK(type_1.extends() == "ModelValue");
    BOOST_CHECK(type_1.pof_id().empty());
    BOOST_REQUIRE(type_1.tag_refs().size() == 1);
    BOOST_CHECK(type_1.tag_refs()[0] == "Configuration");

    const auto ptr_1(dynamic_cast<const dogen::upsilon::compound*>(&type_1));
    BOOST_REQUIRE(ptr_1 != nullptr);
    const auto& compound(*ptr_1);
    BOOST_REQUIRE(compound.fields().size() == 2);

    const auto& field_0(compound.fields()[0]);
    BOOST_CHECK(field_0.name() == "Version");
    BOOST_CHECK(field_0.type_name().name() == "String");
    BOOST_CHECK(field_0.type_name().schema_name() == "Zeta");
    BOOST_CHECK(field_0.comment() == "Some comment");

    const auto& field_1(compound.fields()[1]);
    BOOST_CHECK(field_1.name() == "AField");
    BOOST_CHECK(field_1.type_name().name() == "String");
    BOOST_CHECK(field_1.type_name().schema_name() == "Zeta");
    BOOST_CHECK(field_1.comment().empty());

    const auto& type_3(*a.types()[3]);
    BOOST_CHECK(type_3.name() == "NoFields");

    const auto ptr_3(dynamic_cast<const dogen::upsilon::compound*>(&type_3));
    BOOST_REQUIRE(ptr_3 != nullptr);
    const auto& compound_3(*ptr_3);
    BOOST_REQUIRE(compound_3.fields().empty());

    const auto& type_4(*a.types()[4]);
    BOOST_CHECK(type_4.name() == "SomeEnum");
    BOOST_CHECK(type_4.extends().empty());
    BOOST_CHECK(type_4.pof_id().empty());
    BOOST_REQUIRE(type_4.tag_refs().empty());

    const auto ptr_4(dynamic_cast<const dogen::upsilon::enumeration*>(&type_4));
    BOOST_REQUIRE(ptr_4 != nullptr);
    const auto& enumeration(*ptr_4);
    BOOST_REQUIRE(enumeration.values().size() == 3);
    BOOST_CHECK(enumeration.values()[0] == "AValue");
    BOOST_CHECK(enumeration.values()[1] == "AnotherValue");
    BOOST_CHECK(enumeration.values()[2] == "FinalValue");
    BOOST_CHECK(enumeration.default_value() == "AnotherValue");
}

BOOST_AUTO_TEST_CASE(hydrating_zeta_model_typeinfos_results_in_expected_object) {
    SETUP_TEST_LOG_SOURCE("hydrating_zeta_model_typeinfos_results_in_expected_object");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_zeta_model_xml_typeinfos());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate_type_information(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;

    const auto& entries(a.entries());
    BOOST_REQUIRE(entries.size() == 5);
    BOOST_CHECK(entries[0].name() == "MissingValue");
    BOOST_CHECK(entries[0].pof_id() == "1123");

    BOOST_CHECK(entries[1].name() == "Binary");
    BOOST_CHECK(entries[1].pof_id() == "1124");

    BOOST_CHECK(entries[2].name() == "Date");
    BOOST_CHECK(entries[2].pof_id() == "1125");

    BOOST_CHECK(entries[3].name() == "ModelValues");
    BOOST_CHECK(entries[3].pof_id() == "1154");

    BOOST_CHECK(entries[4].name() == "Binaries");
    BOOST_CHECK(entries[4].pof_id() == "1155");
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

    BOOST_REQUIRE(a.types().size() == 6);
    const auto& type_4(*a.types()[4]);
    BOOST_CHECK(type_4.name() == "ModelValues");
    BOOST_CHECK(type_4.extends().empty());
    BOOST_CHECK(type_4.pof_id() == "1154");
    BOOST_REQUIRE(type_4.tag_refs().size() == 1);
    BOOST_CHECK(type_4.tag_refs()[0] == "ZetaTypes");

    const auto ptr_4(dynamic_cast<const dogen::upsilon::collection*>(&type_4));
    BOOST_REQUIRE(ptr_4 != nullptr);
    const auto& collection(*ptr_4);
    BOOST_CHECK(collection.type_name().name() == "ModelValue");
    BOOST_CHECK(collection.type_name().schema_name().empty());
}

BOOST_AUTO_TEST_CASE(full_hydration_of_test_data_config_results_in_expected_model) {
    SETUP_TEST_LOG_SOURCE("full_hydration_of_test_data_config_results_in_expected_model");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_test_model_configuration_xml());
    dogen::upsilon::hydrator h;
    const auto a(h.hydrate(input));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;

    const auto expected(yarn_upsilon::expected_test_model_upsilon_xml());
    const auto actual(yarn_upsilon::actual_test_model_upsilon_xml());

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_object(expected, actual, a));
}

BOOST_AUTO_TEST_CASE(full_hydration_of_dodgy_test_data_config_throws) {
    SETUP_TEST_LOG_SOURCE("full_hydration_of_dodgy_test_data_config_throws");

    using dogen::utility::test_data::yarn_upsilon;
    const auto input(yarn_upsilon::input_dodgy_model_configuration_xml());
    dogen::upsilon::hydrator h;

    using dogen::upsilon::hydration_error;
    contains_checker<hydration_error> c(schema_not_found);
    BOOST_CHECK_EXCEPTION(h.hydrate(input), hydration_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
