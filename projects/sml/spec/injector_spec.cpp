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
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/types/all.hpp"
#include "dogen/sml/io/all_io.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/types/injection_error.hpp"
#include "dogen/sml/types/injector.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string test_module("sml");
const std::string test_suite("injector_spec");
const std::string key("IDENTITY_ATTRIBUTE");
const std::string value("true");
const std::string missing_identity(
    "Expected entity to have at least one identity");

bool is_type_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::pod_name(0) == qn.type_name();
}

bool is_type_one(const dogen::sml::qname& qn) {
    return mock_model_factory::pod_name(1) == qn.type_name();
}

}

using dogen::utility::test::contains_checker;
using dogen::sml::injection_error;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(injector)

BOOST_AUTO_TEST_CASE(model_that_doesnt_require_any_new_types_is_untouched_by_injector) {
    SETUP_TEST_LOG_SOURCE("model_that_doesnt_require_any_new_types_is_untouched_by_injector");

    auto a(mock_model_factory::build_single_pod_model());
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


BOOST_AUTO_TEST_CASE(unversioned_keyed_pod_does_has_unversioned_key_injected) {
    SETUP_TEST_LOG_SOURCE("keyed_pod_does_has_unversioned_key_injected");

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
    BOOST_CHECK(e.pods().size() == 2);
}

BOOST_AUTO_TEST_SUITE_END()
