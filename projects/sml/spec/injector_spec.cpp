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
#include <array>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/types/all.hpp"
#include "dogen/sml/io/all_io.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/types/injection_error.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/injector.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string test_module("sml");
const std::string test_suite("injector_spec");
const std::string key("IDENTITY_ATTRIBUTE");
const std::string value("true");
const std::string version_name("version");
const std::string versioned_postfix("_versioned");
const std::string unversioned_postfix("_unversioned");
const std::string missing_identity(
    "Expected entity to have at least one identity");

bool is_type_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::type_name(0) == qn.type_name();
}

bool is_type_zero_unversioned(const dogen::sml::qname& qn) {
    const auto s(qn.type_name());
    return
        boost::contains(s, mock_model_factory::type_name(0)) &&
        boost::contains(s, unversioned_postfix);
}

bool is_type_zero_versioned(const dogen::sml::qname& qn) {
    const auto s(qn.type_name());
    return
        boost::contains(s, mock_model_factory::type_name(0)) &&
        boost::contains(s, versioned_postfix);
}

}

using dogen::utility::test::contains_checker;
using dogen::sml::injection_error;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(injector)

BOOST_AUTO_TEST_CASE(model_that_doesnt_require_any_new_types_is_untouched_by_injector) {
    SETUP_TEST_LOG_SOURCE("model_that_doesnt_require_any_new_types_is_untouched_by_injector");

    auto a(mock_model_factory::build_single_type_model());
    BOOST_REQUIRE(a.pods().size() == 1);

    const auto e(a);
    dogen::sml::injector i;
    i.inject(a);
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(entity_pod_does_not_result_in_injected_keys) {
    SETUP_TEST_LOG_SOURCE("entity_pod_does_not_result_in_injected_keys");

    auto a(mock_model_factory::pod_with_property());
    BOOST_REQUIRE(a.pods().size() == 2);
    for (auto& pair : a.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            pair.second.pod_type(dogen::sml::pod_types::entity);

            BOOST_REQUIRE(pair.second.properties().size() == 1);
            pair.second.properties().front().is_identity_attribute(true);
        }
    }

    const auto e(a);
    dogen::sml::injector i;
    i.inject(a);
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(unversioned_keyed_pod_with_no_identity_attributes_throws) {
    SETUP_TEST_LOG_SOURCE("unversioned_keyed_pod_with_no_identity_attributes_throws");

    auto m(mock_model_factory::pod_with_property());
    BOOST_REQUIRE(m.pods().size() == 2);
    for (auto& pair : m.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            pair.second.pod_type(dogen::sml::pod_types::entity);
            pair.second.is_keyed(true);
            pair.second.is_versioned(false);
        }
    }

    dogen::sml::injector i;
    using dogen::sml::injection_error;
    contains_checker<injection_error> c(missing_identity);
    BOOST_CHECK_EXCEPTION(i.inject(m), injection_error, c);
}

BOOST_AUTO_TEST_CASE(unversioned_keyed_pod_has_unversioned_key_injected) {
    SETUP_TEST_LOG_SOURCE("unversioned_keyed_pod_has_unversioned_key_injected");

    auto a(mock_model_factory::pod_with_property());
    BOOST_REQUIRE(a.pods().size() == 2);
    for (auto& pair : a.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            pair.second.pod_type(dogen::sml::pod_types::entity);
            pair.second.is_keyed(true);
            pair.second.is_versioned(false);

            BOOST_REQUIRE(pair.second.properties().size() == 1);
            pair.second.properties().front().is_identity_attribute(true);
        }
    }

    const auto e(a);
    dogen::sml::injector i;
    i.inject(a);

    BOOST_CHECK(a.pods().size() == 3);
    bool type_zero(false), unversioned_key(false);
    for (auto& pair : a.pods()) {
        const auto& qn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "checking pod: " << qn;

        if (is_type_zero(qn)) {
            type_zero = true;
            BOOST_CHECK(!pair.second.versioned_key());
            BOOST_CHECK(pair.second.unversioned_key());
        }
        else if (is_type_zero_unversioned(qn))
            unversioned_key = true;
        BOOST_CHECK(!is_type_zero_versioned(qn));
    }

    BOOST_CHECK(type_zero);
    BOOST_CHECK(unversioned_key);
}

BOOST_AUTO_TEST_CASE(versioned_keyed_pod_has_both_keys_injected) {
    SETUP_TEST_LOG_SOURCE("versioned_keyed_pod_has_both_keys_injected");

    auto a(mock_model_factory::pod_with_property());
    BOOST_REQUIRE(a.pods().size() == 2);
    for (auto& pair : a.pods()) {
        if (is_type_zero(pair.first)) {
            BOOST_LOG_SEV(lg, debug) << "found pod: " << pair.first;
            pair.second.pod_type(dogen::sml::pod_types::entity);
            pair.second.is_keyed(true);
            pair.second.is_versioned(true);

            BOOST_REQUIRE(pair.second.properties().size() == 1);
            pair.second.properties().front().is_identity_attribute(true);
        }
    }

    const auto e(a);
    dogen::sml::injector i;
    i.inject(a);

    BOOST_CHECK(a.pods().size() == 4);
    bool type_zero(false), unversioned_key(false), versioned_key(false);
    for (auto& pair : a.pods()) {
        BOOST_LOG_SEV(lg, debug) << "checking pod: " << pair.first;

        if (is_type_zero(pair.first)) {
            BOOST_CHECK(pair.second.versioned_key());
            BOOST_CHECK(pair.second.unversioned_key());
            type_zero = true;
        } else if (is_type_zero_unversioned(pair.first)) {
            unversioned_key = true;
            BOOST_CHECK(!pair.second.documentation().empty());
            BOOST_CHECK(!pair.second.versioned_key());
            BOOST_CHECK(!pair.second.unversioned_key());
        } else if (is_type_zero_versioned(pair.first)) {
            versioned_key = true;
            BOOST_CHECK(!pair.second.documentation().empty());
            BOOST_CHECK(!pair.second.versioned_key());
            BOOST_CHECK(pair.second.unversioned_key());
        }
    }

    BOOST_CHECK(type_zero);
    BOOST_CHECK(unversioned_key);
    BOOST_CHECK(versioned_key);
}

BOOST_AUTO_TEST_CASE(versioned_pod_has_version_propery_injected) {
    SETUP_TEST_LOG_SOURCE("versioned_pod_has_version_propery_injected");

    auto m(mock_model_factory::build_single_type_model());
    BOOST_REQUIRE(m.pods().size() == 1);
    BOOST_REQUIRE(m.pods().begin()->second.properties().empty());

    BOOST_LOG_SEV(lg, debug) << "pod before: " << m.pods().begin()->second;
    m.pods().begin()->second.pod_type(dogen::sml::pod_types::entity);
    m.pods().begin()->second.is_keyed(false);
    m.pods().begin()->second.is_versioned(true);

    dogen::sml::injector i;
    i.inject(m);

    BOOST_LOG_SEV(lg, debug) << "pod after: " << m.pods().begin()->second;
    BOOST_CHECK(m.pods().size() == 1);
    BOOST_CHECK(!m.pods().begin()->second.versioned_key());
    BOOST_CHECK(!m.pods().begin()->second.unversioned_key());

    const auto& props(m.pods().begin()->second.properties());
    BOOST_REQUIRE(props.size() == 1);
    BOOST_CHECK(props.front().name() == version_name);
    BOOST_CHECK(!props.front().documentation().empty());
}

BOOST_AUTO_TEST_SUITE_END()
