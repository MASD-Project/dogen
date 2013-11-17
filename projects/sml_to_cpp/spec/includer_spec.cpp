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
#include <functional>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/tds_test_good.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/config/io/cpp_facet_types_io.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml_to_cpp/types/locator.hpp"
#include "dogen/config/test/mock_settings_factory.hpp"
#include "dogen/sml_to_cpp/types/includer.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"

using dogen::config::cpp_facet_types;

namespace  {

const std::string test_suite("includer_spec");
const std::string test_module("sml_to_cpp");

using dogen::sml::test::mock_model_factory;
const mock_model_factory model_factory;

const std::string types("types");
const std::string hash("hash");
const std::string test_data("test_data");
const std::string io("io");
const std::string serialization("serialization");
const std::string versioned_key("versioned_key");
const std::string ostream("ostream");
const std::string state_saver("ios_state.hpp");
const std::string functional("functional");
const std::string vector("vector");
const std::string boost_optional("optional.hpp");
const std::string boost_split_free("split_free.hpp");
const std::string boost_format("format.hpp");
const std::string iosfwd("iosfwd");
const std::string algorithm("algorithm");
const std::string generator_include("generator.hpp");
const std::string sequence_include("sequence.hpp");

const std::string io_postfix("_io.hpp");
const std::string serialization_postfix("_ser.hpp");
const std::string fwd_serialization_postfix("fwd_ser.hpp");
const std::string hash_postfix("_hash.hpp");
const std::string test_data_postfix("_td.hpp");

const boost::filesystem::path project_dir("project directory");
const boost::filesystem::path src_dir("source directory");
const boost::filesystem::path include_dir("include directory");

const std::vector<cpp_facet_types> facets =
{
    cpp_facet_types::types,
    cpp_facet_types::serialization,
    cpp_facet_types::hash,
    cpp_facet_types::io,
    cpp_facet_types::test_data
};

dogen::config::cpp_settings mock_settings() {
    return dogen::config::test::mock_settings_factory::
        build_cpp_settings(project_dir);
}

std::string object_name() {
    return model_factory.simple_name(0);
}

dogen::sml_to_cpp::includer default_includer(const dogen::sml::model& m) {
    auto s(mock_settings());
    s.use_integrated_io(false);

    dogen::sml_to_cpp::locator lm(m.name().simple_name(), s);
    return dogen::sml_to_cpp::includer(m, lm, s);
}

dogen::sml_to_cpp::includer includer_with_no_keys(const dogen::sml::model& m) {
    auto s(mock_settings());
    s.use_integrated_io(false);
    dogen::sml_to_cpp::locator lm(m.name().simple_name(), s);
    return dogen::sml_to_cpp::includer(m, lm, s);
}

typedef std::function<
    dogen::sml_to_cpp::includer
    (const dogen::sml::model&)
    > includer_factory;

std::vector<std::list<std::string> >
includes_for_one_object_model(cpp_facet_types ft,
    const includer_factory& factory) {
    using dogen::sml::test::mock_model_factory;
    const auto m(model_factory.build_single_type_model());
    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& p(*m.objects().begin()->second);

    auto im(factory(m));
    std::vector<std::list<std::string> > r;
    r.reserve(4);

    const auto main(dogen::cpp::aspect_types::main);
    dogen::cpp::content_descriptor cd;
    cd.name(p.name());
    cd.facet_type(ft);
    cd.file_type(dogen::cpp::file_types::header);
    cd.aspect_type(main);
    cd.content_type(dogen::cpp::content_types::value_object);
    dogen::sml_to_cpp::relationships rel;
    const auto i0(im.includes_for_object(cd, rel));
    r.push_back(i0.system());
    r.push_back(i0.user());

    cd.file_type(dogen::cpp::file_types::implementation);
    const auto i1(im.includes_for_object(cd, rel));
    r.push_back(i1.system());
    r.push_back(i1.user());
    return r;
}

const unsigned int header_system(0);
const unsigned int header_user(1);
const unsigned int implementation_system(2);
const unsigned int implementation_user(3);

}

using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(includer)

BOOST_AUTO_TEST_CASE(processing_one_object_model_with_default_configuration_generates_expected_domain_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_object_model_with_default_configuration_generates_expected_domain_includes");

    const auto f(default_includer);
    const auto i(includes_for_one_object_model(cpp_facet_types::types, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);
    BOOST_CHECK(boost::ends_with(hu.front(), fwd_serialization_postfix));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header  system dependencies: " << hs;
    BOOST_REQUIRE(hs.size() == 1);
    BOOST_CHECK(boost::ends_with(hs.front(), algorithm));

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;
    BOOST_REQUIRE(iu.size() == 1);
    BOOST_CHECK(boost::contains(iu.front(), object_name()) &&
        boost::contains(iu.front(), types));

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_REQUIRE(is.empty());
}

BOOST_AUTO_TEST_CASE(processing_one_object_model_with_default_configuration_generates_expected_io_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_object_model_with_default_configuration_generates_expected_io_includes");

    const auto f(default_includer);
    const auto i(includes_for_one_object_model(cpp_facet_types::io, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);
    BOOST_CHECK(asserter::assert_contains(object_name(), hu.front()));
    BOOST_CHECK(asserter::assert_contains(types, hu.front()));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header system dependencies: " << hs;
    BOOST_REQUIRE(hs.size() == 1);
    BOOST_CHECK(asserter::assert_contains(iosfwd, hs.front()));

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;
    BOOST_REQUIRE(iu.size() == 1);
    BOOST_CHECK(boost::contains(iu.front(), object_name()) &&
        boost::contains(iu.front(), io));

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_REQUIRE(is.size() == 1);
    BOOST_CHECK(asserter::assert_contains(ostream, is.front()));
}

BOOST_AUTO_TEST_CASE(processing_one_object_model_with_default_configuration_generates_expected_serialisation_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_object_model_with_default_configuration_generates_expected_serialisation_includes");

    const auto f(default_includer);
    const auto i(includes_for_one_object_model(cpp_facet_types::serialization, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);
    BOOST_CHECK(asserter::assert_contains(object_name(), hu.front()));
    BOOST_CHECK(asserter::assert_contains(types, hu.front()));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header system dependencies: " << hs;
    BOOST_REQUIRE(hs.size() == 1);
    BOOST_CHECK(asserter::assert_contains(boost_split_free, hs.front()));

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;

    BOOST_CHECK(boost::ends_with(iu.front(), serialization_postfix));
    BOOST_CHECK(asserter::assert_contains(object_name(), iu.front()));
    BOOST_CHECK(asserter::assert_contains(serialization, iu.front()));

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_REQUIRE(is.size() == 9);
}

BOOST_AUTO_TEST_CASE(processing_one_object_model_with_default_configuration_generates_expected_hash_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_object_model_with_default_configuration_generates_expected_hash_includes");

    const auto f(default_includer);
    const auto i(includes_for_one_object_model(cpp_facet_types::hash, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);
    BOOST_CHECK(boost::contains(hu.front(), object_name()) &&
        boost::contains(hu.front(), types));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header system dependencies: " << hs;
    BOOST_REQUIRE(hs.size() == 1);
    BOOST_CHECK(asserter::assert_contains(hs.front(), functional));

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;
    BOOST_REQUIRE(iu.size() == 1);
    BOOST_CHECK(boost::contains(iu.front(), object_name()) &&
        boost::contains(iu.front(), hash));

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_CHECK(is.empty());
}

BOOST_AUTO_TEST_CASE(processing_one_object_model_with_default_configuration_generates_expected_test_data_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_object_model_with_default_configuration_generates_expected_test_data_includes");

    const auto f(default_includer);
    const auto i(includes_for_one_object_model(cpp_facet_types::test_data, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);
    BOOST_CHECK(boost::contains(hu.front(), object_name()) &&
        boost::contains(hu.front(), types));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header system dependencies: " << hs;
    BOOST_CHECK(hs.empty());

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;
    BOOST_REQUIRE(iu.size() == 1);
    BOOST_CHECK(boost::contains(iu.front(), object_name()) &&
        boost::contains(iu.front(), test_data));

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_CHECK(is.empty());
}

BOOST_AUTO_TEST_CASE(processing_one_object_model_with_no_keys_configuration_generates_no_key_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_object_model_with_no_keys_configuration_generates_no_key_includes");

    const auto f(includer_with_no_keys);
    for (const auto facet : facets) {
        auto i(includes_for_one_object_model(facet, f));
        BOOST_REQUIRE(i.size() == 4);

        auto all(i[header_user]);
        all.splice(all.end(), i[header_system]);
        all.splice(all.end(), i[implementation_user]);
        all.splice(all.end(), i[implementation_system]);
        BOOST_LOG_SEV(lg, debug) << "all dependencies for facet "
                                 << facet << ": "
                                 << all;

        BOOST_CHECK(!all.empty());
        for (const auto s : all)
            BOOST_CHECK(!boost::contains(s, versioned_key));
    }
}

BOOST_AUTO_TEST_SUITE_END()
