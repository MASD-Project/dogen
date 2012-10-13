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

namespace  {

const std::string test_suite("inclusion_manager_spec");
const std::string test_module("generator");
const std::string domain("domain");
const std::string io("io");
const std::string versioned_key("versioned_key");
const std::string io_postfix("_io.hpp");
const std::string only_one_pod_model_name("only_one_pod");
const std::string pod_parent_name("parent");
const std::string pod_name("pod0");
const std::string pod_child_name("child");
const boost::filesystem::path project_dir("project directory");
const boost::filesystem::path src_dir("source directory");
const boost::filesystem::path include_dir("include directory");

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

dogen::sml::model only_one_pod_model() {
    const auto p(mock_pod(pod_name, only_one_pod_model_name));
    const std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> pods {
        { p.name(), p }
    };
    dogen::sml::model r;
    r.name(only_one_pod_model_name);
    r.pods(pods);
    return r;
}

dogen::generator::backends::cpp::cpp_inclusion_manager
default_inclusion_manager(const dogen::sml::model& m) {
    const auto s(mock_settings());

    using namespace dogen::generator::backends::cpp;
    cpp_location_manager lm(m.name(), s);

    bool no_keys(false);
    bool integrated_io(false);
    bool no_io(false);
    return cpp_inclusion_manager(m, lm, no_keys, integrated_io, no_io);
}

std::list<std::string>
domain_header_user_deps(
    const dogen::generator::backends::cpp::cpp_inclusion_manager& d,
    const dogen::sml::pod& p) {

    using namespace dogen::generator::backends::cpp;
    cpp_facet_types ft(cpp_facet_types::domain);
    cpp_file_types flt(cpp_file_types::header);
    cpp_aspect_types at(cpp_aspect_types::main);
    return d.user(p, ft, flt, at);
}

}

using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(inclusion_manager)

BOOST_AUTO_TEST_CASE(validate_dependencies_for_model_with_only_one_pod_and_default_location_manager) {
    SETUP_TEST_LOG_SOURCE("validate_dependencies_for_model_with_only_one_pod_and_default_location_manager");

    const auto m(only_one_pod_model());
    const auto pods(m.pods());
    BOOST_CHECK(pods.size() == 1);
    const auto pod(pods.begin()->second);

    auto dm(default_inclusion_manager(m));
    using namespace dogen::generator::backends::cpp;
    auto lambda([&](cpp_facet_types ft, cpp_file_types flt) {
            return dm.user(pod, ft, flt, cpp_aspect_types::main);
        });

    auto pi([&](cpp_facet_types ft, cpp_file_types flt) {
            return dm.system(pod, ft, flt, cpp_aspect_types::main);
        });

    // domain header
    auto r(lambda(cpp_facet_types::domain, cpp_file_types::header));
    BOOST_LOG_SEV(lg, debug) << "domain header user dependencies: " << r;
    BOOST_CHECK(r.size() == 1);
    BOOST_CHECK(asserter::assert_contains(versioned_key, r.front()));

    // FIXME: no iosfwd, expected with current impl
    r = pi(cpp_facet_types::domain, cpp_file_types::header);
    BOOST_LOG_SEV(lg, debug) << "domain header  system dependencies: " << r;
    BOOST_CHECK(r.empty());

    // domain implementation
    r = lambda(cpp_facet_types::domain, cpp_file_types::implementation);
    BOOST_LOG_SEV(lg, debug) << "domain imp user dependencies: " << r;
    BOOST_CHECK(r.size() == 2);
    if (boost::ends_with(r.front(), io_postfix)) {
        BOOST_CHECK(asserter::assert_contains(versioned_key, r.front()));
        BOOST_CHECK(asserter::assert_contains(io, r.front()));
    } else {
        BOOST_CHECK(asserter::assert_contains(pod_name, r.front()));
        BOOST_CHECK(asserter::assert_contains(domain, r.front()));
    }

    r = pi(cpp_facet_types::domain, cpp_file_types::implementation);
    BOOST_LOG_SEV(lg, debug) << "domain impl system dependencies: " << r;
    BOOST_CHECK(r.empty());

    // io header
    r = lambda(cpp_facet_types::io, cpp_file_types::header);
    BOOST_LOG_SEV(lg, debug) << "io header user dependencies: " << r;
    BOOST_CHECK(r.size() == 1);
    BOOST_CHECK(asserter::assert_contains(pod_name, r.front()));
    BOOST_CHECK(asserter::assert_contains(domain, r.front()));

    // FIXME: no iosfwd, expected with current impl
    r = pi(cpp_facet_types::io, cpp_file_types::header);
    BOOST_LOG_SEV(lg, debug) << "io impl system dependencies: " << r;
    BOOST_CHECK(r.empty());

    // io implementation
    r = lambda(cpp_facet_types::io, cpp_file_types::implementation);
    BOOST_LOG_SEV(lg, debug) << "io imp user dependencies: " << r;
    BOOST_CHECK(r.size() == 1);
    BOOST_CHECK(asserter::assert_contains(pod_name, r.front()));
    BOOST_CHECK(asserter::assert_contains(io, r.front()));

    // FIXME: no ostream
    r = pi(cpp_facet_types::io, cpp_file_types::implementation);
    BOOST_LOG_SEV(lg, debug) << "io impl system dependencies: " << r;
    BOOST_CHECK(r.empty());
}

BOOST_AUTO_TEST_SUITE_END()
