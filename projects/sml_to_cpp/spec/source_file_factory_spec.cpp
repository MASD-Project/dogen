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
#include "dogen/sml_to_cpp/types/includer.hpp"
#include "dogen/cpp/io/all_io.hpp"
#include "dogen/cpp/types/building_error.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/config/test/mock_settings_factory.hpp"
#include "dogen/sml_to_cpp/types/source_file_factory.hpp"

using dogen::config::cpp_facet_types;
using dogen::config::test::mock_settings_factory;
using dogen::config::cpp_facet_types;
using dogen::cpp::file_types;
using dogen::cpp::aspect_types;
using dogen::cpp::content_types;

namespace {

const std::string test_module("sml_to_cpp");
const std::string test_suite("source_file_factory_spec");

using dogen::sml::test::mock_model_factory;
const mock_model_factory::flags flags;
const mock_model_factory model_factory(flags);

const std::string src_dir("__source_directory__");
const std::string inc_dir("__include_directory__");

std::list<dogen::cpp::content_descriptor>
mock_descriptors(const dogen::sml::qname& qn) {
    std::list<dogen::cpp::content_descriptor> r;

    dogen::cpp::content_descriptor cd;
    cd.name(qn);
    cd.facet_type(cpp_facet_types::types);
    cd.file_type(file_types::header);
    cd.aspect_type(aspect_types::main);
    r.push_back(cd);

    cd.facet_type(cpp_facet_types::serialization);
    r.push_back(cd);

    cd.facet_type(cpp_facet_types::hash);
    r.push_back(cd);

    return r;
}

std::list<dogen::cpp::content_descriptor>
mock_descriptor_for_includer(const dogen::config::cpp_facet_types ft) {
    std::list<dogen::cpp::content_descriptor> r;

    dogen::sml::qname qn;
    qn.simple_name(model_factory.type_name());
    qn.model_name(model_factory.model_name());

    dogen::cpp::content_descriptor cd;
    cd.name(qn);
    cd.facet_type(ft);
    cd.file_type(file_types::header);
    cd.aspect_type(aspect_types::main);
    cd.content_type(content_types::value_object);
    r.push_back(cd);

    return r;
}

std::list<dogen::cpp::content_descriptor> mock_descriptor_for_registrar() {
    std::list<dogen::cpp::content_descriptor> r;

    dogen::sml::qname qn;
    qn.simple_name(model_factory.type_name());
    qn.model_name(model_factory.model_name());

    dogen::cpp::content_descriptor cd;
    cd.name(qn);
    cd.facet_type(cpp_facet_types::serialization);
    cd.file_type(file_types::header);
    cd.aspect_type(aspect_types::main);
    cd.content_type(content_types::registrar);
    r.push_back(cd);

    return r;
}

}

using dogen::utility::test::contains_checker;
typedef dogen::sml::test::mock_model_factory::object_types object_types;
typedef dogen::sml::test::mock_model_factory::property_types property_types;

BOOST_AUTO_TEST_SUITE(source_file_factory)

BOOST_AUTO_TEST_CASE(creating_source_file_for_enumeration_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_source_file_for_enumeration_produces_expected_results");

    const auto ot(object_types::enumeration);
    const auto m(model_factory.build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::sml_to_cpp::locator l(m.name().simple_name(), s);
    dogen::sml_to_cpp::source_file_factory f(l);
    const auto ei((dogen::cpp::enum_info()));
    const auto en(m.enumerations().begin()->second);
    const auto md(mock_descriptors(en.name()));
    const auto il((dogen::sml_to_cpp::inclusion_lists()));

    std::list<dogen::cpp::source_file> infos;
    for (const auto& cd : md)
        infos.push_back(f.create(ei, cd, il));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.descriptor().facet_type());
        BOOST_CHECK(fi.enum_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.descriptor().file_type() == file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.descriptor().file_type() == file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }

    BOOST_CHECK(found_facets.size() == md.size());
    for (const auto& d : md)
        BOOST_CHECK(found_facets.find(d.facet_type()) != found_facets.end());
}

BOOST_AUTO_TEST_CASE(creating_source_file_for_exception_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_source_file_for_exception_produces_expected_results");

    const auto ot(object_types::exception);
    const auto m(model_factory.build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::sml_to_cpp::locator l(m.name().simple_name(), s);
    dogen::sml_to_cpp::source_file_factory f(l);
    const auto& ex(m.objects().begin()->second);
    const auto md(mock_descriptors(ex.name()));
    const auto ei((dogen::cpp::exception_info()));
    const auto il((dogen::sml_to_cpp::inclusion_lists()));

    std::list<dogen::cpp::source_file> infos;
    for (const auto& cd : md)
        infos.push_back(f.create(ei, cd, il));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.descriptor().facet_type());
        BOOST_CHECK(!fi.enum_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        if (fi.descriptor().file_type() == file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.descriptor().file_type() == file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }

    BOOST_CHECK(found_facets.size() == md.size());
    for (const auto& d : md)
        BOOST_CHECK(found_facets.find(d.facet_type()) != found_facets.end());
}

BOOST_AUTO_TEST_CASE(creating_source_file_for_module_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_source_file_for_module_produces_expected_results");

    const auto ot(object_types::exception);
    const auto m(model_factory.build_single_type_model_in_module(0, ot, 1));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.modules().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::sml_to_cpp::locator l(m.name().simple_name(), s);
    dogen::sml_to_cpp::source_file_factory f(l);
    const auto p(m.modules().begin()->second);
    const auto md(mock_descriptors(p.name()));
    const auto ni((dogen::cpp::namespace_info()));

    std::list<dogen::cpp::source_file> infos;
    for (const auto& cd : md)
        infos.push_back(f.create(ni, cd));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.descriptor().facet_type());
        BOOST_CHECK(!fi.enum_info());
        BOOST_CHECK(!fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        using dogen::cpp::file_types;
        if (fi.descriptor().file_type() == file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.descriptor().file_type() == file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }

    BOOST_CHECK(found_facets.size() == md.size());
    for (const auto& d : md)
        BOOST_CHECK(found_facets.find(d.facet_type()) != found_facets.end());
}

BOOST_AUTO_TEST_CASE(creating_source_file_for_object_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_source_file_for_object_produces_expected_results");

    const auto m(model_factory.build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::sml_to_cpp::locator l(m.name().simple_name(), s);
    dogen::sml_to_cpp::source_file_factory f(l);
    const auto& p(m.objects().begin()->second);
    const auto md(mock_descriptors(p.name()));
    const auto ci((dogen::cpp::class_info()));
    const auto il((dogen::sml_to_cpp::inclusion_lists()));

    std::list<dogen::cpp::source_file> infos;
    for (const auto& cd : md)
        infos.push_back(f.create(ci, cd, il));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    std::set<dogen::config::cpp_facet_types> found_facets;
    for (const auto& fi : infos) {
        found_facets.insert(fi.descriptor().facet_type());
        BOOST_CHECK(!fi.enum_info());
        BOOST_CHECK(fi.class_info());
        BOOST_CHECK(!fi.exception_info());
        BOOST_CHECK(!fi.namespace_info());
        BOOST_CHECK(!fi.registrar_info());
        BOOST_CHECK(!fi.visitor_info());
        BOOST_CHECK(!fi.file_path().empty());

        using dogen::cpp::file_types;
        if (fi.descriptor().file_type() == file_types::header)
            BOOST_CHECK(!fi.header_guard().empty());
        else if (fi.descriptor().file_type() == file_types::implementation)
            BOOST_CHECK(fi.header_guard().empty());
    }

    BOOST_CHECK(found_facets.size() == md.size());
    for (const auto& d : md)
        BOOST_CHECK(found_facets.find(d.facet_type()) != found_facets.end());
}

BOOST_AUTO_TEST_CASE(creating_non_empty_includer_source_file_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_non_empty_includer_source_file_produces_expected_results");

    const auto m(model_factory.build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::sml_to_cpp::locator l(m.name().simple_name(), s);
    dogen::sml_to_cpp::includer i(m, l, s);
    dogen::sml_to_cpp::source_file_factory f(l);

    const auto ft(dogen::config::cpp_facet_types::types);
    i.register_header(ft, model_factory.type_name(0));
    i.register_header(ft, model_factory.type_name(1));
    const auto md(mock_descriptor_for_includer(ft));

    std::list<dogen::cpp::source_file> includer_infos;
    for (const auto& cd : md) {
        const auto il(i.includes_for_includer_files(cd));
        includer_infos.push_back(f.create_includer(cd, il));
    }
    BOOST_LOG_SEV(lg, debug) << "includer file infos: " << includer_infos;

    BOOST_REQUIRE(includer_infos.size() == 1);
    const auto fi(includer_infos.front());

    BOOST_CHECK(fi.descriptor().facet_type() == ft);
    BOOST_CHECK(fi.descriptor().aspect_type() == aspect_types::main);
    BOOST_CHECK(fi.descriptor().content_type() == content_types::includer);
    BOOST_CHECK(!fi.enum_info());
    BOOST_CHECK(!fi.class_info());
    BOOST_CHECK(!fi.exception_info());
    BOOST_CHECK(!fi.namespace_info());
    BOOST_CHECK(!fi.registrar_info());
    BOOST_CHECK(!fi.visitor_info());
    BOOST_CHECK(!fi.file_path().empty());
    BOOST_CHECK(fi.descriptor().file_type() == file_types::header);

    bool found_0(false), found_1(false);
    for (const auto& ui : fi.user_includes()) {
        if (ui == model_factory.type_name(0))
            found_0 = true;
        else if (ui == model_factory.type_name(1))
            found_1 = true;
    }
    BOOST_CHECK(found_0);
    BOOST_CHECK(found_1);
}

BOOST_AUTO_TEST_CASE(creating_empty_includer_source_file_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_empty_includer_source_file_produces_expected_results");

    const auto m(model_factory.build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::sml_to_cpp::locator l(m.name().simple_name(), s);
    dogen::sml_to_cpp::includer i(m, l, s);
    dogen::sml_to_cpp::source_file_factory f(l);

    const auto ft1(dogen::config::cpp_facet_types::types);
    i.register_header(ft1, model_factory.type_name(0));
    i.register_header(ft1, model_factory.type_name(1));

    const auto ft2(dogen::config::cpp_facet_types::serialization);
    const auto md(mock_descriptor_for_includer(ft2));
    const auto il((dogen::sml_to_cpp::inclusion_lists()));

    std::list<dogen::cpp::source_file> includer_infos;
    for (const auto& cd : md)
        includer_infos.push_back(f.create_includer(cd, il));
    BOOST_LOG_SEV(lg, debug) << "includer file infos: " << includer_infos;

    BOOST_REQUIRE(includer_infos.size() == 1);
    const auto fi(includer_infos.front());

    BOOST_CHECK(fi.descriptor().facet_type() == ft2);
    BOOST_CHECK(fi.descriptor().aspect_type() == aspect_types::main);
    BOOST_CHECK(fi.descriptor().content_type() == content_types::includer);
    BOOST_CHECK(!fi.enum_info());
    BOOST_CHECK(!fi.class_info());
    BOOST_CHECK(!fi.exception_info());
    BOOST_CHECK(!fi.namespace_info());
    BOOST_CHECK(!fi.registrar_info());
    BOOST_CHECK(!fi.visitor_info());
    BOOST_CHECK(!fi.file_path().empty());
    BOOST_CHECK(fi.descriptor().file_type() == file_types::header);
    BOOST_CHECK(fi.user_includes().empty());
}

BOOST_AUTO_TEST_CASE(creating_source_file_for_registrar_produces_expected_results) {
    SETUP_TEST_LOG_SOURCE("creating_source_file_for_registrar_produces_expected_results");

    const auto m(model_factory.build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto s(mock_settings_factory::build_cpp_settings(src_dir, inc_dir));
    dogen::sml_to_cpp::locator l(m.name().simple_name(), s);
    dogen::sml_to_cpp::includer i(m, l, s);
    dogen::sml_to_cpp::source_file_factory f(l);

    const auto md(mock_descriptor_for_registrar());
    const auto ri((dogen::cpp::registrar_info()));
    const auto il((dogen::sml_to_cpp::inclusion_lists()));

    std::list<dogen::cpp::source_file> infos;
    for (const auto& cd : md)
        infos.push_back(f.create_registrar(ri, cd, il));
    BOOST_LOG_SEV(lg, debug) << "file infos: " << infos;

    BOOST_REQUIRE(infos.size() == 1);
    const auto fi(infos.front());

    const auto ft(cpp_facet_types::serialization);
    BOOST_CHECK(fi.descriptor().facet_type() == ft);
    BOOST_CHECK(fi.descriptor().aspect_type() == aspect_types::main);
    BOOST_CHECK(fi.descriptor().content_type() == content_types::registrar);
    BOOST_CHECK(!fi.enum_info());
    BOOST_CHECK(!fi.class_info());
    BOOST_CHECK(!fi.exception_info());
    BOOST_CHECK(!fi.namespace_info());
    BOOST_CHECK(fi.registrar_info());
    BOOST_CHECK(!fi.visitor_info());
    BOOST_CHECK(!fi.file_path().empty());
    BOOST_CHECK(fi.descriptor().file_type() == file_types::header);
}

BOOST_AUTO_TEST_SUITE_END()
