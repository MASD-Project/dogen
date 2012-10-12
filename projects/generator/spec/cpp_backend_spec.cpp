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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/test/unit_test.hpp>
#include "dogen/generator/backends/cpp/view_models/sml_to_cpp_view_model.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/xml_serialization_helper.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
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

const std::string domain("domain");
const std::string versioned_key("versioned_key");
const std::string pod_with_parent_model_name("pod_with_parent");
const std::string pod_parent_name("parent");
const std::string pod_child_name("child");
const boost::filesystem::path project_dir("project directory");
const boost::filesystem::path src_dir("source directory");
const boost::filesystem::path include_dir("include directory");

dogen::sml::pod
mock_pod(const std::string& type_name, const std::string& model_name) {
    dogen::sml::qualified_name qn;
    qn.model_name(model_name);
    qn.type_name(type_name);
    qn.meta_type(dogen::sml::meta_types::pod);

    dogen::sml::pod r;
    r.name(qn);
    r.generate(true);
    return r;
}

dogen::sml::model pod_with_parent_model() {
    const auto p(mock_pod(pod_parent_name, pod_with_parent_model_name));
    auto c(mock_pod(pod_child_name, pod_with_parent_model_name));
    c.parent_name(p.name());
    const std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> pods {
        { p.name(), p }, { c.name(), c }
    };
    dogen::sml::model r;
    r.name(pod_with_parent_model_name);
    r.pods(pods);
    return r;
}

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

    using dogen::generator::backends::cpp::view_models::sml_to_cpp_view_model;
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
        BOOST_CHECK(!class_vm.is_parent());

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

    using dogen::generator::backends::cpp::view_models::sml_to_cpp_view_model;
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

    bool no_includers(false);
    bool no_keys(true);
    const bool no_iio(false);
    const bool disable_io(false);
    using dogen::generator::backends::cpp::view_models::sml_to_cpp_view_model;
    sml_to_cpp_view_model t(lm, ft, input, no_includers, no_keys, no_iio,
        disable_io);

    using namespace dogen::generator::backends::cpp::view_models;
    std::vector<file_view_model> actual(t.transform());

    BOOST_CHECK(actual.size() == 3);
    using dogen::generator::backends::cpp::cpp_aspect_types;
    for (const auto f : actual) {
        BOOST_CHECK(f.aspect_type() != cpp_aspect_types::versioned_key);
        BOOST_CHECK(f.aspect_type() != cpp_aspect_types::unversioned_key);
    }
}

BOOST_AUTO_TEST_CASE(is_parent_flag_is_correctly_set_on_view_models) {
    SETUP_TEST_LOG_SOURCE("is_parent_flag_is_correctly_set_on_view_models");
    const auto m(pod_with_parent_model());
    const auto pods(m.pods());
    BOOST_CHECK(pods.size() == 2);
    const auto pod(pods.begin()->second);

    using dogen::generator::test::mock_settings_factory;
    const auto s(mock_settings_factory::build_cpp_settings(empty, empty));

    using namespace dogen::generator::backends::cpp;
    cpp_location_manager lm(m.name(), s);

    bool no_includers(true);
    bool no_keys(true);
    bool integrated_io(false);
    bool disable_io(false);

    using dogen::generator::backends::cpp::cpp_dependency_manager;
    cpp_dependency_manager dm(m, lm, no_keys, integrated_io, disable_io);

    using dogen::generator::backends::cpp::cpp_facet_types;
    std::set<cpp_facet_types> ft;
    ft.insert(cpp_facet_types::domain);

    using dogen::generator::backends::cpp::view_models::sml_to_cpp_view_model;
    sml_to_cpp_view_model t(lm, ft, m, no_includers, no_keys, integrated_io,
        disable_io);

    using namespace dogen::generator::backends::cpp::view_models;
    std::vector<file_view_model> actual(t.transform());

    // 2 headers and 2 implementation files
    BOOST_CHECK(actual.size() == 4);
    BOOST_LOG_SEV(lg, debug) << "files generated: " << actual.size();
    using dogen::generator::backends::cpp::cpp_aspect_types;
    for (const auto fvm : actual) {
        BOOST_LOG_SEV(lg, debug) << "file: " << fvm.file_path();
        BOOST_CHECK(fvm.aspect_type() == cpp_aspect_types::main);
        const auto o(fvm.class_vm());
        BOOST_REQUIRE(o);

        const auto cvm(*o);
        if (cvm.name() == pod_parent_name)
            BOOST_CHECK(cvm.is_parent());
        else {
            BOOST_CHECK(cvm.name() == pod_child_name);
            BOOST_CHECK(!cvm.is_parent());
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
