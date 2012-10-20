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
#include "dogen/generator/backends/cpp/cpp_location_manager.hpp"
#include "dogen/generator/backends/cpp/cpp_location_request.hpp"
#include "dogen/generator/test/mock_settings_factory.hpp"
#include "dogen/generator/backends/cpp/cpp_inclusion_manager.hpp"

using namespace dogen::generator::backends::cpp;

namespace  {

const std::string test_suite("inclusion_manager_spec");
const std::string test_module("generator");
const std::string domain("domain");
const std::string hash("hash");
const std::string test_data("test_data");
const std::string io("io");
const std::string database("database");
const std::string serialization("serialization");
const std::string versioned_key("versioned_key");
const std::string ostream("ostream");
const std::string state_saver("ios_state.hpp");
const std::string functional("functional");
const std::string vector("vector");
const std::string boost_optional("optional.hpp");
const std::string boost_nvp("nvp.hpp");
const std::string pqxx_connection("connection.hxx");
const std::string boost_format("format.hpp");
const std::string pqxx_result("result.hxx");
const std::string pqxx_transaction("transaction.hxx");
const std::string iosfwd("iosfwd");
const std::string algorithm("algorithm");
const std::string hash_combine("combine.hpp");
const std::string generator_include("generator.hpp");
const std::string sequence_include("sequence.hpp");

const std::string io_postfix("_io.hpp");
const std::string database_postfix("_db.hpp");
const std::string serialization_postfix("_ser.hpp");
const std::string hash_postfix("_hash.hpp");
const std::string test_data_postfix("_td.hpp");
const std::string one_pod_model_name("one_pod");
const std::string pod_parent_name("parent");
const std::string pod_name("pod0");
const std::string pod_child_name("child");
const boost::filesystem::path project_dir("project directory");
const boost::filesystem::path src_dir("source directory");
const boost::filesystem::path include_dir("include directory");

const std::vector<cpp_facet_types> facets =
{
    cpp_facet_types::domain,
    cpp_facet_types::serialization,
    cpp_facet_types::hash,
    cpp_facet_types::io,
    cpp_facet_types::database,
    cpp_facet_types::test_data
};

dogen::generator::config::cpp_settings mock_settings() {
    return dogen::generator::test::mock_settings_factory::
        build_cpp_settings(project_dir);
}

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

dogen::sml::model one_pod_model() {
    const auto p(mock_pod(pod_name, one_pod_model_name));
    const std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> pods {
        { p.name(), p }
    };
    dogen::sml::model r;
    r.name(one_pod_model_name);
    r.pods(pods);
    return r;
}

cpp_inclusion_manager default_inclusion_manager(const dogen::sml::model& m) {
    auto s(mock_settings());
    s.use_integrated_io(false);
    s.disable_versioning(false);

    cpp_location_manager lm(m.name(), s);
    return cpp_inclusion_manager(m, lm, s);
}

cpp_inclusion_manager
inclusion_manager_with_no_keys(const dogen::sml::model& m) {
    auto s(mock_settings());
    s.use_integrated_io(false);
    s.disable_versioning(true);
    cpp_location_manager lm(m.name(), s);
    return cpp_inclusion_manager(m, lm, s);
}

typedef std::function<
    cpp_inclusion_manager
    (const dogen::sml::model&)
    > inclusion_manager_factory;

std::vector<std::list<std::string> >
includes_for_one_pod_model(cpp_facet_types ft,
    const inclusion_manager_factory& factory) {
    const auto m(one_pod_model());
    const auto pods(m.pods());
    BOOST_REQUIRE(pods.size() == 1);
    const auto p(pods.begin()->second);

    auto im(factory(m));
    std::vector<std::list<std::string> > r;
    r.reserve(4);

    const cpp_aspect_types main(cpp_aspect_types::main);
    const auto i0(im.includes_for_pod(p, ft,  cpp_file_types::header, main));
    r.push_back(i0.system);
    r.push_back(i0.user);

    const auto i1(im.includes_for_pod(p, ft,  cpp_file_types::implementation, main));
    r.push_back(i1.system);
    r.push_back(i1.user);
    return r;
}

const unsigned int header_system(0);
const unsigned int header_user(1);
const unsigned int implementation_system(2);
const unsigned int implementation_user(3);

}

using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(inclusion_manager)

BOOST_AUTO_TEST_CASE(processing_one_pod_model_with_default_configuration_generates_expected_domain_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_pod_model_with_default_configuration_generates_expected_domain_includes");

    const auto f(default_inclusion_manager);
    const auto i(includes_for_one_pod_model(cpp_facet_types::domain, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);
    BOOST_CHECK(asserter::assert_contains(versioned_key, hu.front()));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header  system dependencies: " << hs;
    BOOST_REQUIRE(hs.size() == 1);
    BOOST_CHECK(boost::ends_with(hs.front(), algorithm));

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;
    BOOST_REQUIRE(iu.size() == 1);
    BOOST_CHECK(boost::contains(iu.front(), pod_name) &&
        boost::contains(iu.front(), domain));

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_REQUIRE(is.empty());
}

BOOST_AUTO_TEST_CASE(processing_one_pod_model_with_default_configuration_generates_expected_io_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_pod_model_with_default_configuration_generates_expected_io_includes");

    const auto f(default_inclusion_manager);
    const auto i(includes_for_one_pod_model(cpp_facet_types::io, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);
    BOOST_CHECK(asserter::assert_contains(pod_name, hu.front()));
    BOOST_CHECK(asserter::assert_contains(domain, hu.front()));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header system dependencies: " << hs;
    BOOST_REQUIRE(hs.size() == 1);
    BOOST_CHECK(asserter::assert_contains(iosfwd, hs.front()));

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;
    BOOST_REQUIRE(iu.size() == 2);
    for (const auto s : iu) {
        BOOST_CHECK(
            (boost::contains(s, pod_name) && boost::contains(s, io)) ||
            (boost::contains(s, versioned_key) && boost::contains(s, io)));
    }

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_REQUIRE(is.size() == 1);
    BOOST_CHECK(asserter::assert_contains(ostream, is.front()));
}

BOOST_AUTO_TEST_CASE(processing_one_pod_model_with_default_configuration_generates_expected_serialisation_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_pod_model_with_default_configuration_generates_expected_serialisation_includes");

    const auto f(default_inclusion_manager);
    const auto i(includes_for_one_pod_model(cpp_facet_types::serialization, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 2);
    auto a(hu.front());
    auto b(hu.back());
    if (!boost::ends_with(b, serialization_postfix))
        std::swap(a,b);

    BOOST_CHECK(asserter::assert_contains(pod_name, a));
    BOOST_CHECK(asserter::assert_contains(domain, a));

    BOOST_CHECK(asserter::assert_contains(versioned_key, b));
    BOOST_CHECK(asserter::assert_contains(serialization, b));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header system dependencies: " << hs;
    BOOST_REQUIRE(hs.size() == 1);
    BOOST_CHECK(asserter::assert_contains(boost_nvp, hs.front()));

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;

    a = iu.front();
    BOOST_CHECK(boost::ends_with(a, serialization_postfix));
    BOOST_CHECK(asserter::assert_contains(pod_name, a));
    BOOST_CHECK(asserter::assert_contains(serialization, a));

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_CHECK(is.empty());
}

BOOST_AUTO_TEST_CASE(processing_one_pod_model_with_default_configuration_generates_expected_hash_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_pod_model_with_default_configuration_generates_expected_hash_includes");

    const auto f(default_inclusion_manager);
    const auto i(includes_for_one_pod_model(cpp_facet_types::hash, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);
    BOOST_CHECK(boost::contains(hu.front(), pod_name) &&
        boost::contains(hu.front(), domain));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header system dependencies: " << hs;
    BOOST_REQUIRE(hs.size() == 1);
    BOOST_CHECK(asserter::assert_contains(hs.front(), functional));

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;
    BOOST_REQUIRE(iu.size() == 3);
    for (const auto s : iu) {
        BOOST_CHECK(
            (boost::contains(s, pod_name) && boost::contains(s, hash)) ||
            (boost::contains(s, versioned_key) && boost::contains(s, hash)) ||
            (boost::ends_with(s, hash_combine)));
    }

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_CHECK(is.empty());
}

BOOST_AUTO_TEST_CASE(processing_one_pod_model_with_default_configuration_generates_expected_test_data_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_pod_model_with_default_configuration_generates_expected_test_data_includes");

    const auto f(default_inclusion_manager);
    const auto i(includes_for_one_pod_model(cpp_facet_types::test_data, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);
    BOOST_CHECK(boost::contains(hu.front(), pod_name) &&
        boost::contains(hu.front(), domain));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header system dependencies: " << hs;
    BOOST_CHECK(hs.empty());

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;
    BOOST_REQUIRE(iu.size() == 2);
    for (const auto s : iu) {
        BOOST_CHECK(
            (boost::contains(s, pod_name) && boost::contains(s, test_data)) ||
            (boost::contains(s, versioned_key) && boost::contains(s, test_data)));
    }

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_CHECK(is.empty());
}

BOOST_AUTO_TEST_CASE(processing_one_pod_model_with_default_configuration_generates_expected_database_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_pod_model_with_default_configuration_generates_expected_database_includes");

    const auto f(default_inclusion_manager);
    const auto i(includes_for_one_pod_model(cpp_facet_types::database, f));
    BOOST_REQUIRE(i.size() == 4);

    // header
    const auto hu(i[header_user]);
    BOOST_LOG_SEV(lg, debug) << "header user dependencies: " << hu;
    BOOST_REQUIRE(hu.size() == 1);

    BOOST_CHECK(asserter::assert_contains(pod_name, hu.front()));
    BOOST_CHECK(asserter::assert_contains(domain, hu.front()));

    const auto hs(i[header_system]);
    BOOST_LOG_SEV(lg, debug) << "header system dependencies: " << hs;
    BOOST_REQUIRE(hs.size() == 3);
    for (const auto s : hs) {
        BOOST_CHECK(
            boost::ends_with(s, vector) ||
            boost::ends_with(s, boost_optional) ||
            boost::ends_with(s, pqxx_connection));
    }

    // implementation
    const auto iu(i[implementation_user]);
    BOOST_LOG_SEV(lg, debug) << "implementation user dependencies: " << iu;
    BOOST_REQUIRE(iu.size() == 1);

    const auto a(iu.front());
    BOOST_CHECK(boost::ends_with(a, database_postfix));
    BOOST_CHECK(asserter::assert_contains(pod_name, a));
    BOOST_CHECK(asserter::assert_contains(database, a));

    const auto is(i[implementation_system]);
    BOOST_LOG_SEV(lg, debug) << "implementation system dependencies: " << is;
    BOOST_REQUIRE(hs.size() == 3);
    for (const auto s : is) {
        BOOST_CHECK(
            boost::ends_with(s, boost_format) ||
            boost::ends_with(s, pqxx_result) ||
            boost::ends_with(s, pqxx_transaction));
    }
}

BOOST_AUTO_TEST_CASE(processing_one_pod_model_with_no_keys_configuration_generates_no_key_includes) {
    SETUP_TEST_LOG_SOURCE("processing_one_pod_model_with_no_keys_configuration_generates_no_key_includes");

    const auto f(inclusion_manager_with_no_keys);
    for (const auto facet : facets) {
        auto i(includes_for_one_pod_model(facet, f));
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
