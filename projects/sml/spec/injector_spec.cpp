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
const std::string version_name("version");
const std::string versioned_postfix("_versioned");
const std::string unversioned_postfix("_unversioned");
const std::string missing_identity("Identity must have at least");

bool is_type_zero(const dogen::sml::qname& qn) {
    return mock_model_factory::type_name(0) == qn.simple_name();
}

bool is_type_zero_unversioned(const dogen::sml::qname& qn) {
    const auto s(qn.simple_name());
    return
        boost::contains(s, mock_model_factory::type_name(0)) &&
        boost::contains(s, unversioned_postfix);
}

bool is_type_zero_versioned(const dogen::sml::qname& qn) {
    const auto s(qn.simple_name());
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
    BOOST_REQUIRE(a.objects().size() == 1);

    const auto e(a);
    dogen::sml::injector i;
    i.inject(a);
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(entity_object_does_not_result_in_injected_keys) {
    SETUP_TEST_LOG_SOURCE("entity_object_does_not_result_in_injected_keys");

    const auto ot(mock_model_factory::object_types::entity);
    auto a(mock_model_factory::object_with_property(ot));
    BOOST_REQUIRE(a.objects().size() == 2);
    for (const auto& pair : a.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            const auto& o(dynamic_cast<dogen::sml::entity&>(*pair.second));
            BOOST_REQUIRE(o.properties().size() == 1);
            BOOST_REQUIRE(!o.identity().empty());
        }
    }

    const auto e(a);
    dogen::sml::injector i;
    i.inject(a);
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(unversioned_keyed_object_with_no_identity_attributes_throws) {
    SETUP_TEST_LOG_SOURCE("unversioned_keyed_object_with_no_identity_attributes_throws");

    const auto ot(mock_model_factory::object_types::keyed_entity);
    auto m(mock_model_factory::object_with_property(ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_REQUIRE(m.objects().size() == 2);
    for (auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            using dogen::sml::keyed_entity;
            auto& o(dynamic_cast<keyed_entity&>(*pair.second));
            BOOST_REQUIRE(o.properties().size() == 1);
            BOOST_REQUIRE(!o.is_versioned());
            o.identity().clear();
        }
    }

    dogen::sml::injector i;
    using dogen::sml::injection_error;
    contains_checker<injection_error> c(missing_identity);
    BOOST_CHECK_EXCEPTION(i.inject(m), injection_error, c);
}

BOOST_AUTO_TEST_CASE(unversioned_keyed_object_has_unversioned_key_injected) {
    SETUP_TEST_LOG_SOURCE("unversioned_keyed_object_has_unversioned_key_injected");

    const auto ot(mock_model_factory::object_types::keyed_entity);
    auto m(mock_model_factory::object_with_property(ot));
    BOOST_REQUIRE(m.objects().size() == 2);
    for (auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            auto& ae(dynamic_cast<dogen::sml::abstract_entity&>(*pair.second));
            BOOST_REQUIRE(ae.properties().size() == 1);
            BOOST_REQUIRE(!ae.is_versioned());
            BOOST_REQUIRE(ae.identity().size() == 1);
        }
    }

    dogen::sml::injector i;
    i.inject(m);

    BOOST_CHECK(m.objects().size() == 3);
    bool type_zero(false);
    dogen::sml::qname ukqn;
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            type_zero = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            using dogen::sml::keyed_entity;
            const auto& ae(dynamic_cast<const keyed_entity&>(*pair.second));
            BOOST_REQUIRE(!ae.is_versioned());
            BOOST_CHECK(!ae.versioned_key());
            ukqn = ae.unversioned_key();

            BOOST_CHECK(is_type_zero_unversioned(ukqn));
            BOOST_CHECK(!is_type_zero_versioned(ukqn));
            BOOST_LOG_SEV(lg, debug) << "Found unversioned key qname: " << ukqn;
        }
    }

    BOOST_REQUIRE(type_zero);
    const auto j(m.objects().find(ukqn));
    BOOST_REQUIRE(j != m.objects().end());

    const auto& uk(dynamic_cast<const dogen::sml::value_object&>(*(j->second)));
    BOOST_LOG_SEV(lg, debug) << "Found unversioned key: " << uk;
    BOOST_REQUIRE(!uk.is_versioned());
}

BOOST_AUTO_TEST_CASE(versioned_keyed_object_has_both_keys_injected) {
    SETUP_TEST_LOG_SOURCE("versioned_keyed_object_has_both_keys_injected");

    const auto ot(mock_model_factory::object_types::keyed_entity);
    auto m(mock_model_factory::object_with_property(ot));
    BOOST_REQUIRE(m.objects().size() == 2);
    for (auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            auto& ae(dynamic_cast<dogen::sml::abstract_entity&>(*pair.second));
            BOOST_REQUIRE(ae.properties().size() == 1);
            BOOST_REQUIRE(!ae.is_versioned());
            BOOST_REQUIRE(ae.identity().size() == 1);
            ae.is_versioned(true);
        }
    }

    dogen::sml::injector i;
    i.inject(m);

    BOOST_CHECK(m.objects().size() == 4);
    bool type_zero(false);
    dogen::sml::qname ukqn, vkqn;
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (is_type_zero(qn)) {
            type_zero = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            using dogen::sml::keyed_entity;
            const auto& ae(dynamic_cast<const keyed_entity&>(*pair.second));
            BOOST_REQUIRE(ae.is_versioned());

            BOOST_CHECK(ae.versioned_key());
            vkqn = *ae.versioned_key();
            BOOST_CHECK(!is_type_zero_unversioned(vkqn));
            BOOST_CHECK(is_type_zero_versioned(vkqn));

            ukqn = ae.unversioned_key();
            BOOST_CHECK(is_type_zero_unversioned(ukqn));
            BOOST_CHECK(!is_type_zero_versioned(ukqn));
            BOOST_LOG_SEV(lg, debug) << "Found unversioned key qname: " << ukqn;
        }
    }

    BOOST_REQUIRE(type_zero);
    auto j(m.objects().find(ukqn));
    BOOST_REQUIRE(j != m.objects().end());

    const auto& uk(dynamic_cast<const dogen::sml::value_object&>(*(j->second)));
    BOOST_LOG_SEV(lg, debug) << "Found unversioned key: " << uk;
    BOOST_REQUIRE(!uk.is_versioned());

    j = m.objects().find(vkqn);
    BOOST_REQUIRE(j != m.objects().end());

    const auto& vk(dynamic_cast<const dogen::sml::value_object&>(*(j->second)));
    BOOST_LOG_SEV(lg, debug) << "Found versioned key: " << vk;
    BOOST_REQUIRE(!vk.is_versioned());
}

BOOST_AUTO_TEST_CASE(versioned_object_has_version_propery_injected) {
    SETUP_TEST_LOG_SOURCE("versioned_object_has_version_propery_injected");

    auto m(mock_model_factory::build_single_type_model());
    BOOST_REQUIRE(m.objects().size() == 1);
    auto& ob(*m.objects().begin()->second);
    BOOST_REQUIRE(ob.properties().empty());
    ob.is_versioned(true);
    BOOST_LOG_SEV(lg, debug) << "before: " << ob;

    dogen::sml::injector i;
    i.inject(m);

    BOOST_REQUIRE(m.objects().size() == 1);
    auto& oa(*m.objects().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "object after: " << oa;
    BOOST_REQUIRE(oa.properties().size() == 1);
    BOOST_CHECK(oa.properties().front().name() == version_name);
    BOOST_CHECK(!oa.properties().front().documentation().empty());
}

BOOST_AUTO_TEST_SUITE_END()
