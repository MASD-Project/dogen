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
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/injection_error.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/value_object_io.hpp"
#include "dogen/sml/io/service_io.hpp"
#include "dogen/sml/io/abstract_object_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/injector.hpp"

namespace {

using dogen::sml::test::mock_model_factory;
const mock_model_factory factory;

const std::string test_module("sml");
const std::string test_suite("injector_spec");
const std::string version_name("version");
const std::string missing_identity("Identity must have at least");
const std::string no_leaves("Type marked as visitable but has no leaves");

}

using dogen::utility::test::contains_checker;
using dogen::sml::injection_error;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(injector)

BOOST_AUTO_TEST_CASE(model_that_doesnt_require_any_new_types_is_untouched_by_injector) {
    SETUP_TEST_LOG_SOURCE("model_that_doesnt_require_any_new_types_is_untouched_by_injector");

    auto a(factory.build_single_type_model());
    BOOST_REQUIRE(a.objects().size() == 1);

    const auto e(a);
    dogen::sml::injector i;
    i.inject(a);
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(entity_object_does_not_result_in_injected_keys) {
    SETUP_TEST_LOG_SOURCE("entity_object_does_not_result_in_injected_keys");

    const auto ot(mock_model_factory::object_types::entity);
    auto a(factory.object_with_property(ot));
    BOOST_REQUIRE(a.objects().size() == 2);
    for (const auto& pair : a.objects()) {
        const auto& qn(pair.first);
        if (factory.is_simple_name_n(0, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            const auto& o(dynamic_cast<dogen::sml::entity&>(*pair.second));
            BOOST_REQUIRE(o.local_properties().size() == 1);
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
    auto m(factory.object_with_property(ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_REQUIRE(m.objects().size() == 2);
    for (auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.is_simple_name_n(0, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            using dogen::sml::keyed_entity;
            auto& o(dynamic_cast<keyed_entity&>(*pair.second));
            BOOST_REQUIRE(o.local_properties().size() == 1);
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
    auto m(factory.object_with_property(ot));
    BOOST_REQUIRE(m.objects().size() == 2);
    for (auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.is_simple_name_n(0, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            auto& ae(dynamic_cast<dogen::sml::abstract_entity&>(*pair.second));
            BOOST_REQUIRE(ae.local_properties().size() == 1);
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
        if (factory.is_simple_name_n(0, qn)) {
            type_zero = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            using dogen::sml::keyed_entity;
            const auto& ae(dynamic_cast<const keyed_entity&>(*pair.second));
            BOOST_REQUIRE(!ae.is_versioned());
            BOOST_CHECK(!ae.versioned_key());
            ukqn = ae.unversioned_key();

            BOOST_CHECK(factory.is_simple_name_n_unversioned(0, ukqn));
            BOOST_CHECK(!factory.is_simple_name_n_versioned(0, ukqn));
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
    auto m(factory.object_with_property(ot));
    BOOST_REQUIRE(m.objects().size() == 2);
    for (auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.is_simple_name_n(0, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            auto& ae(dynamic_cast<dogen::sml::abstract_entity&>(*pair.second));
            BOOST_REQUIRE(ae.local_properties().size() == 1);
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
        if (factory.is_simple_name_n(0, qn)) {
            type_zero = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            using dogen::sml::keyed_entity;
            const auto& ae(dynamic_cast<const keyed_entity&>(*pair.second));
            BOOST_REQUIRE(ae.is_versioned());

            BOOST_CHECK(ae.versioned_key());
            vkqn = *ae.versioned_key();
            BOOST_CHECK(!factory.is_simple_name_n_unversioned(0, vkqn));
            BOOST_CHECK(factory.is_simple_name_n_versioned(0, vkqn));

            ukqn = ae.unversioned_key();
            BOOST_CHECK(factory.is_simple_name_n_unversioned(0, ukqn));
            BOOST_CHECK(!factory.is_simple_name_n_versioned(0, ukqn));
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

    auto m(factory.build_single_type_model());
    BOOST_REQUIRE(m.objects().size() == 1);
    auto& ob(*m.objects().begin()->second);
    BOOST_REQUIRE(ob.local_properties().empty());
    ob.is_versioned(true);
    BOOST_LOG_SEV(lg, debug) << "before: " << ob;

    dogen::sml::injector i;
    i.inject(m);

    BOOST_REQUIRE(m.objects().size() == 1);
    auto& oa(*m.objects().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "object after: " << oa;
    BOOST_REQUIRE(oa.local_properties().size() == 1);
    BOOST_CHECK(oa.local_properties().front().name() == version_name);
    BOOST_CHECK(!oa.local_properties().front().documentation().empty());
}

BOOST_AUTO_TEST_CASE(visitable_object_with_no_leaves_throws) {
    SETUP_TEST_LOG_SOURCE("visitable_object_with_no_leaves_throws");

    auto m(factory.build_single_type_model());
    BOOST_REQUIRE(m.objects().size() == 1);
    auto& ob(*m.objects().begin()->second);
    ob.is_visitable(true);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::sml::injector i;
    contains_checker<injection_error> c(no_leaves);
    BOOST_CHECK_EXCEPTION(i.inject(m), injection_error, c);
}

BOOST_AUTO_TEST_CASE(visitable_object_has_visitor_injected) {
    SETUP_TEST_LOG_SOURCE("visitable_object_has_visitor_injected");

    auto m(factory.object_with_parent_in_the_same_model());
    BOOST_REQUIRE(m.objects().size() == 2);
    for (auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.is_simple_name_n(1, qn)) {
            auto& ao(*pair.second);
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            ao.is_visitable(true);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "before: " << m;

    dogen::sml::injector i;
    i.inject(m);
    BOOST_LOG_SEV(lg, debug) << "after: " << m;

    BOOST_CHECK(m.objects().size() == 3);
    bool type_one(false), visitor(false);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.is_simple_name_n(1, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            type_one = true;
            BOOST_REQUIRE(!pair.second->is_versioned());
        } else if (factory.is_simple_name_n_visitor(1, qn)) {
            visitor = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;

            using dogen::sml::service;
            const auto& s(dynamic_cast<const service&>(*pair.second));
            BOOST_CHECK(!s.is_versioned());
            BOOST_CHECK(!s.is_visitable());
            BOOST_CHECK(!s.is_immutable());
            BOOST_CHECK(!s.parent_name());
            BOOST_CHECK(!s.original_parent_name());
            BOOST_CHECK(s.leaves().empty());
            BOOST_CHECK(s.modeled_concepts().empty());
            BOOST_CHECK(s.number_of_type_arguments() == 0);

            BOOST_REQUIRE(s.operations().size() == 1);
            const auto op(s.operations().front());
            BOOST_CHECK(!op.name().empty());
            BOOST_CHECK(!op.documentation().empty());
            BOOST_REQUIRE(op.parameters().size() == 1);
            BOOST_CHECK(factory.is_simple_name_n(0,
                    op.parameters().front().type().type()));
        }
    }

    BOOST_CHECK(type_one);
    BOOST_CHECK(visitor);
}

BOOST_AUTO_TEST_SUITE_END()
