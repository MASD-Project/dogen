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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/cpp/io/all_io.hpp"
#include "dogen/cpp/types/building_error.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/config/test/mock_settings_factory.hpp"
#include "dogen/cpp/types/file_info_factory.hpp"

using dogen::config::cpp_facet_types;
using dogen::sml::test::mock_model_factory;
using dogen::config::test::mock_settings_factory;

namespace {

const std::string test_module("cpp");
const std::string test_suite("file_info_factory_spec");
const std::string src_dir("__source_directory__");
const std::string inc_dir("__include_directory__");

std::list<dogen::cpp::content_descriptor>
mock_descriptors(const dogen::sml::qname& qn) {
    std::list<dogen::cpp::content_descriptor> r;

    dogen::cpp::content_descriptor cd;
    cd.name(qn);
    cd.facet_type(dogen::config::cpp_facet_types::types);
    cd.file_type(dogen::cpp::file_types::header);
    cd.aspect_type(dogen::cpp::aspect_types::main);
    cd.category_type(dogen::sml::category_types::user_defined);
    r.push_back(cd);

    cd.facet_type(dogen::config::cpp_facet_types::serialization);
    r.push_back(cd);

    cd.facet_type(dogen::config::cpp_facet_types::hash);
    r.push_back(cd);

    return r;
}

std::list<dogen::cpp::content_descriptor>
mock_descriptor_for_includer(const dogen::config::cpp_facet_types ft) {
    std::list<dogen::cpp::content_descriptor> r;

    dogen::sml::qname qn;
    qn.type_name(mock_model_factory::type_name());
    qn.meta_type(dogen::sml::meta_types::pod);
    qn.model_name(mock_model_factory::model_name());

    dogen::cpp::content_descriptor cd;
    cd.name(qn);
    cd.facet_type(ft);
    cd.file_type(dogen::cpp::file_types::header);
    cd.aspect_type(dogen::cpp::aspect_types::includers);
    cd.category_type(dogen::sml::category_types::user_defined);
    r.push_back(cd);

    return r;
}

std::list<dogen::cpp::content_descriptor> mock_descriptor_for_registrar() {
    std::list<dogen::cpp::content_descriptor> r;

    dogen::sml::qname qn;
    qn.type_name(mock_model_factory::type_name());
    qn.meta_type(dogen::sml::meta_types::pod);
    qn.model_name(mock_model_factory::model_name());

    dogen::cpp::content_descriptor cd;
    cd.name(qn);
    cd.facet_type(dogen::config::cpp_facet_types::serialization);
    cd.file_type(dogen::cpp::file_types::header);
    cd.aspect_type(dogen::cpp::aspect_types::registrar);
    cd.category_type(dogen::sml::category_types::user_defined);
    r.push_back(cd);

    return r;
}

}

using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(file_info_factory)

BOOST_AUTO_TEST_CASE(creating_file_info_for_enumeration_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_enumeration_produces_expected_results");

    const auto mt(dogen::sml::meta_types::enumeration);
    const auto m(mock_model_factory::build_single_type_model(0, mt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);

    dogen::cpp::file_info_factory f(l, i);
    const auto ei((dogen::cpp::enum_info()));
    const auto en(m.enumerations().begin()->second);
    const auto md(mock_descriptors(en.name()));
    const auto il((dogen::cpp::inclusion_lists()));

    std::list<dogen::cpp::file_info> infos;
    for (const auto& cd : md)
        infos.push_back(f.create(ei, cd, il));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == dogen::sml::meta_types::enumeration);
        BOOST_CHECK(fi.enum_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets.size() == md.size());
    for (const auto& d : md)
        BOOST_CHECK(found_facets.find(d.facet_type()) != found_facets.end());
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_exception_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_exception_produces_expected_results");

    const auto mt(dogen::sml::meta_types::exception);
    const auto m(mock_model_factory::build_single_type_model(0, mt));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.exceptions().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::file_info_factory f(l, i);
    const auto ex(m.exceptions().begin()->second);
    const auto md(mock_descriptors(ex.name()));
    const auto ei((dogen::cpp::exception_info()));
    const auto il((dogen::cpp::inclusion_lists()));

    std::list<dogen::cpp::file_info> infos;
    for (const auto& cd : md)
        infos.push_back(f.create(ei, cd, il));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == ex.name().meta_type());
        BOOST_CHECK(!fi.enum_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets.size() == md.size());
    for (const auto& d : md)
        BOOST_CHECK(found_facets.find(d.facet_type()) != found_facets.end());
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_package_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_package_produces_expected_results");

    const auto mt(dogen::sml::meta_types::pod);
    const auto m(
        mock_model_factory::build_single_type_model_in_package(0, mt, 1));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.packages().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::file_info_factory f(l, i);
    const auto p(m.packages().begin()->second);
    const auto md(mock_descriptors(p.name()));
    const auto ni((dogen::cpp::namespace_info()));

    std::list<dogen::cpp::file_info> infos;
    for (const auto& cd : md)
        infos.push_back(f.create(ni, cd));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == p.name().meta_type());
        BOOST_CHECK(!fi.enum_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets.size() == md.size());
    for (const auto& d : md)
        BOOST_CHECK(found_facets.find(d.facet_type()) != found_facets.end());
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_pod_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_pod_produces_expected_results");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::file_info_factory f(l, i);
    const auto p(m.pods().begin()->second);
    const auto md(mock_descriptors(p.name()));
    const auto ci((dogen::cpp::class_info()));
    const auto il((dogen::cpp::inclusion_lists()));

    std::list<dogen::cpp::file_info> infos;
    for (const auto& cd : md)
        infos.push_back(f.create(ci, cd, il));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.facet_type());
        BOOST_CHECK(fi.meta_type() == p.name().meta_type());
        BOOST_CHECK(!fi.enum_info());
        BOOST_CHECK(fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.file_type() == dogen::cpp::file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.file_type() == dogen::cpp::file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }
    BOOST_CHECK(found_facets.size() == md.size());
    for (const auto& d : md)
        BOOST_CHECK(found_facets.find(d.facet_type()) != found_facets.end());
}

BOOST_AUTO_TEST_CASE(creating_non_empty_includer_file_info_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_non_empty_includer_file_info_produces_expected_results");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::file_info_factory f(l, i);

    const auto ft(dogen::config::cpp_facet_types::types);
    i.register_header(ft, mock_model_factory::type_name(0));
    i.register_header(ft, mock_model_factory::type_name(1));
    const auto md(mock_descriptor_for_includer(ft));

    std::list<dogen::cpp::file_info> includer_infos;
    for (const auto& cd : md) {
        const auto il(i.includes_for_includer_files(cd));
        includer_infos.push_back(f.create_includer(cd, il));
    }
    BOOST_LOG_SEV(lg, debug) << "includer file infos: " << includer_infos;

    BOOST_REQUIRE(includer_infos.size() == 1);
    const auto fi(includer_infos.front());

    BOOST_CHECK(fi.facet_type() == ft);
    BOOST_CHECK(fi.aspect_type() == dogen::cpp::aspect_types::includers);
    BOOST_CHECK(!fi.enum_info());
    BOOST_CHECK(!fi.class_info());
    BOOST_CHECK(!fi.exception_info());
    BOOST_CHECK(!fi.namespace_info());
    BOOST_CHECK(!fi.registrar_info());
    BOOST_CHECK(!fi.visitor_info());
    BOOST_CHECK(!fi.file_path().empty());
    BOOST_CHECK(fi.file_type() == dogen::cpp::file_types::header);

    bool found_0(false), found_1(false);
    for (const auto& ui : fi.user_includes()) {
        if (ui == mock_model_factory::type_name(0))
            found_0 = true;
        else if (ui == mock_model_factory::type_name(1))
            found_1 = true;
    }
    BOOST_CHECK(found_0);
    BOOST_CHECK(found_1);
}

BOOST_AUTO_TEST_CASE(creating_empty_includer_file_info_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_empty_includer_file_info_produces_expected_results");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.pods().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::file_info_factory f(l, i);

    const auto ft1(dogen::config::cpp_facet_types::types);
    i.register_header(ft1, mock_model_factory::type_name(0));
    i.register_header(ft1, mock_model_factory::type_name(1));

    const auto ft2(dogen::config::cpp_facet_types::serialization);
    const auto md(mock_descriptor_for_includer(ft2));
    const auto il((dogen::cpp::inclusion_lists()));

    std::list<dogen::cpp::file_info> includer_infos;
    for (const auto& cd : md)
        includer_infos.push_back(f.create_includer(cd, il));
    BOOST_LOG_SEV(lg, debug) << "includer file infos: " << includer_infos;

    BOOST_REQUIRE(includer_infos.size() == 1);
    const auto fi(includer_infos.front());

    BOOST_CHECK(fi.facet_type() == ft2);
    BOOST_CHECK(fi.aspect_type() == dogen::cpp::aspect_types::includers);
    BOOST_CHECK(!fi.enum_info());
    BOOST_CHECK(!fi.class_info());
    BOOST_CHECK(!fi.exception_info());
    BOOST_CHECK(!fi.namespace_info());
    BOOST_CHECK(!fi.registrar_info());
    BOOST_CHECK(!fi.visitor_info());
    BOOST_CHECK(!fi.file_path().empty());
    BOOST_CHECK(fi.file_type() == dogen::cpp::file_types::header);
    BOOST_CHECK(fi.user_includes().empty());
}

BOOST_AUTO_TEST_CASE(creating_file_info_for_registrar_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_file_info_for_registrar_produces_expected_results");

    const auto m(mock_model_factory::build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::cpp::locator l(m.name(), s);
    dogen::cpp::includer i(m, l, s);
    dogen::cpp::file_info_factory f(l, i);

    const auto md(mock_descriptor_for_registrar());
    const auto ri((dogen::cpp::registrar_info()));
    const auto il((dogen::cpp::inclusion_lists()));

    std::list<dogen::cpp::file_info> infos;
    for (const auto& cd : md)
        infos.push_back(f.create_registrar(ri, cd, il));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    BOOST_REQUIRE(infos.size() == 1);
    const auto fi(infos.front());

    const auto ft(dogen::config::cpp_facet_types::serialization);
    BOOST_CHECK(fi.facet_type() == ft);
    BOOST_CHECK(fi.aspect_type() == dogen::cpp::aspect_types::registrar);
    BOOST_CHECK(!fi.enum_info());
    BOOST_CHECK(!fi.class_info());
    BOOST_CHECK(!fi.exception_info());
    BOOST_CHECK(!fi.namespace_info());
    BOOST_CHECK(fi.registrar_info());
    BOOST_CHECK(!fi.visitor_info());
    BOOST_CHECK(!fi.file_path().empty());
    BOOST_CHECK(fi.file_type() == dogen::cpp::file_types::header);
}

BOOST_AUTO_TEST_SUITE_END()
