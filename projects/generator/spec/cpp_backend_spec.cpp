/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/xml_serialization_helper.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/generator/backends/cpp/transformers/sml_to_cpp_view_model.hpp"
#include "dogen/generator/test/mock_settings_factory.hpp"

namespace {

const std::string empty;
const std::string test_module("generator");
const std::string test_suite("cpp_backend_spec");
const std::string test_model_name("test");
const std::string class_name("first_class");
const std::string header_guard_name(
    "CLASS_IN_A_PACKAGE_DOMAIN_PACKAGE1_FIRST_CLASS_HPP");
const std::string user_dependency(
    "class_in_a_package/domain/package1/first_class.hpp");
const std::string versioned_dependency(
    "class_in_a_package/domain/versioned_key.hpp");
const std::string unversioned_dependency(
    "class_in_a_package/domain/unversioned_key.hpp");

const std::string namespace_1("class_in_a_package");
const std::string namespace_2("package1");

const std::string property_1("public_attribute");
const std::string property_2("private_attribute");
const std::string property_type("int");

}

BOOST_AUTO_TEST_SUITE(cpp_backend)

BOOST_AUTO_TEST_CASE(view_model_transformer_correctly_transforms_domain_files) {
    SETUP_TEST_LOG_SOURCE("view_model_transformer_correctly_transforms_domain_files");
    using dogen::utility::test_data::dia_sml;
    auto input_path(dia_sml::expected_class_in_a_package_sml_xml());

    using dogen::utility::test::xml_deserialize;
    const auto input(xml_deserialize<dogen::sml::model>(input_path));

    using dogen::generator::test::mock_settings_factory;
    const auto s(mock_settings_factory::build_cpp_settings(empty, empty));

    using dogen::generator::backends::cpp::cpp_location_manager;
    cpp_location_manager lm(test_model_name, s);

    using dogen::generator::backends::cpp::cpp_facet_types;
    std::set<cpp_facet_types> ft;
    ft.insert(cpp_facet_types::domain);

    using dogen::generator::backends::cpp::transformers::sml_to_cpp_view_model;
    const bool no_includers(false);
    const bool no_keys(false);
    const bool no_iio(false);
    const bool disable_io(false);
    sml_to_cpp_view_model t(lm, ft, input, no_includers, no_keys, no_iio, disable_io);

    using namespace dogen::generator::backends::cpp::view_models;
    std::vector<file_view_model> actual(t.transform());

    BOOST_CHECK(actual.size() == 7);
    for (const auto f : actual) {
        BOOST_LOG_SEV(lg, debug) << "file: " << f.file_path();
        BOOST_CHECK(f.facet_type() == cpp_facet_types::domain);

        using dogen::generator::backends::cpp::cpp_file_types;
        BOOST_CHECK(f.file_type() == cpp_file_types::header ||
            f.file_type() == cpp_file_types::implementation);

        BOOST_LOG_SEV(lg, debug) << "sys deps: " << f.system_dependencies();
        BOOST_LOG_SEV(lg, debug) << "user deps: " << f.user_dependencies();
        BOOST_LOG_SEV(lg, debug) << "header guard:" << f.header_guard();

        BOOST_CHECK(f.system_dependencies().empty());
        using dogen::generator::backends::cpp::cpp_aspect_types;
        const auto o(f.class_vm());
        if (!o) {
            BOOST_CHECK(f.file_type() == cpp_file_types::header);
            BOOST_CHECK(f.aspect_type() == cpp_aspect_types::includers);
            BOOST_CHECK(f.header_guard().empty());
            BOOST_CHECK(f.user_dependencies().size() == 3);
            for (const auto d : f.user_dependencies()) {
                BOOST_CHECK(d == user_dependency || d == versioned_dependency ||
                    d == unversioned_dependency);
            }
            continue;
        }

        if (f.aspect_type() == cpp_aspect_types::versioned_key) {
            // FIXME
            continue;
        } else if (f.aspect_type() == cpp_aspect_types::unversioned_key) {
            // FIXME
            continue;
        }

        BOOST_CHECK(f.aspect_type() == cpp_aspect_types::main);
        if (f.file_type() == cpp_file_types::header) {
            BOOST_CHECK(f.header_guard() == header_guard_name);
        } else {
            BOOST_CHECK(f.header_guard() == empty);
            BOOST_CHECK(f.user_dependencies().size() == 2);
            BOOST_CHECK(f.user_dependencies().front() == user_dependency);
        }

        const auto class_vm(*o);
        BOOST_LOG_SEV(lg, debug) << "class name: " << class_vm.name();
        BOOST_CHECK(class_vm.name() == class_name);

        const auto ns(class_vm.namespaces());
        BOOST_LOG_SEV(lg, debug) << "namespaces: " << ns;
        BOOST_CHECK(ns.size() == 2);
        BOOST_CHECK(ns.front() == namespace_1);
        BOOST_CHECK(ns.back() == namespace_2);

        const auto properties(class_vm.properties());
        BOOST_LOG_SEV(lg, debug) << "property count: " << properties.size();
        BOOST_REQUIRE(properties.size() == 3);

        for (const auto p : properties) {
            BOOST_LOG_SEV(lg, debug) << "property type: " << p.type()
                                     << " name: " << p.name();

            if (p.name() == property_1 || p.name() == property_2)
                BOOST_CHECK(p.type() == property_type);
            else
                BOOST_CHECK(p.name() == "versioned_key");
        }
    }
}

BOOST_AUTO_TEST_CASE(disabling_facet_includers_results_in_no_facet_includers) {
    SETUP_TEST_LOG("disabling_facet_includers_results_in_no_facet_includers");
    using dogen::utility::test_data::dia_sml;
    auto input_path(dia_sml::expected_class_in_a_package_sml_xml());

    using dogen::utility::test::xml_deserialize;
    const auto input(xml_deserialize<dogen::sml::model>(input_path));

    using dogen::generator::test::mock_settings_factory;
    const auto s(mock_settings_factory::build_cpp_settings(empty, empty));

    using dogen::generator::backends::cpp::cpp_location_manager;
    cpp_location_manager lm(test_model_name, s);

    using dogen::generator::backends::cpp::cpp_facet_types;
    std::set<cpp_facet_types> ft;
    ft.insert(cpp_facet_types::domain);

    using dogen::generator::backends::cpp::transformers::sml_to_cpp_view_model;
    bool no_includers(true);
    bool no_keys(false);
    const bool no_iio(false);
    const bool disable_io(false);
    sml_to_cpp_view_model t(lm, ft, input, no_includers, no_keys, no_iio, disable_io);

    using namespace dogen::generator::backends::cpp::view_models;
    std::vector<file_view_model> actual(t.transform());

    BOOST_CHECK(actual.size() == 6);
    using dogen::generator::backends::cpp::cpp_aspect_types;
    for (const auto f : actual) {
        BOOST_CHECK(f.aspect_type() != cpp_aspect_types::includers);
        const auto o(f.class_vm());
        BOOST_CHECK(o);
    }
}

BOOST_AUTO_TEST_CASE(disabling_keys_results_in_no_keys) {
    SETUP_TEST_LOG("disabling_facet_includers_results_in_no_facet_includers");
    using dogen::utility::test_data::dia_sml;
    auto input_path(dia_sml::expected_class_in_a_package_sml_xml());

    using dogen::utility::test::xml_deserialize;
    const auto input(xml_deserialize<dogen::sml::model>(input_path));

    using dogen::generator::test::mock_settings_factory;
    const auto s(mock_settings_factory::build_cpp_settings(empty, empty));

    using dogen::generator::backends::cpp::cpp_location_manager;
    cpp_location_manager lm(test_model_name, s);

    using dogen::generator::backends::cpp::cpp_facet_types;
    std::set<cpp_facet_types> ft;
    ft.insert(cpp_facet_types::domain);

    using dogen::generator::backends::cpp::transformers::sml_to_cpp_view_model;
    bool no_includers(false);
    bool no_keys(true);
    const bool no_iio(false);
    const bool disable_io(false);
    sml_to_cpp_view_model t(lm, ft, input, no_includers, no_keys, no_iio, disable_io);

    using namespace dogen::generator::backends::cpp::view_models;
    std::vector<file_view_model> actual(t.transform());

    BOOST_CHECK(actual.size() == 3);
    using dogen::generator::backends::cpp::cpp_aspect_types;
    for (const auto f : actual) {
        BOOST_CHECK(f.aspect_type() != cpp_aspect_types::versioned_key);
        BOOST_CHECK(f.aspect_type() != cpp_aspect_types::unversioned_key);
    }
}

BOOST_AUTO_TEST_SUITE_END()
