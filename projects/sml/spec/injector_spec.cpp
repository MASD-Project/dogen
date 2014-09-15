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
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/object_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/injector.hpp"

using dogen::sml::relationship_types;
using dogen::sml::object_types;

namespace {

using dogen::sml::test::mock_model_factory;
const mock_model_factory::flags flags;
const mock_model_factory factory(flags);

const std::string test_module("sml");
const std::string test_suite("injector_spec");
const std::string version_name("version");
const std::string missing_identity("Identity must have at least");
const std::string no_leaves("Type marked as visitable but has no leaves");

bool has_relationship(const relationship_types rt,
    const dogen::sml::object& o) {
    const auto i(o.relationships().find(rt));
    return i != o.relationships().end() && !i->second.empty();
}

std::list<dogen::sml::qname> get_relationship(const relationship_types rt,
    const dogen::sml::object& o) {
    const auto i(o.relationships().find(rt));
    BOOST_REQUIRE(i != o.relationships().end() && !i->second.empty());
    return i->second;
}

}

using dogen::utility::test::contains_checker;
using dogen::sml::injection_error;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(injector)

BOOST_AUTO_TEST_CASE(single_type_model_results_in_adding_only_global_module) {
    SETUP_TEST_LOG_SOURCE("single_type_model_results_in_adding_only_global_module");

    auto a(factory.build_single_type_model());
    BOOST_REQUIRE(a.objects().size() == 1);
    BOOST_CHECK(!a.objects().begin()->second.containing_module());
    BOOST_REQUIRE(a.modules().empty());
    BOOST_REQUIRE(a.primitives().empty());
    BOOST_REQUIRE(a.enumerations().empty());
    BOOST_REQUIRE(a.concepts().empty());

    dogen::sml::injector i;
    i.inject(a);

    BOOST_CHECK(a.objects().size() == 1);
    BOOST_CHECK(a.modules().size() == 1);

    const auto qn(a.modules().begin()->first);
    BOOST_REQUIRE(a.objects().begin()->second.containing_module());
    BOOST_REQUIRE(*a.objects().begin()->second.containing_module() == qn);
    BOOST_CHECK(a.primitives().empty());
    BOOST_CHECK(a.enumerations().empty());
    BOOST_CHECK(a.concepts().empty());
}

BOOST_AUTO_TEST_CASE(entity_object_does_not_result_in_injected_keys) {
    SETUP_TEST_LOG_SOURCE("entity_object_does_not_result_in_injected_keys");

    const auto ot(mock_model_factory::object_types::entity);
    auto a(factory.object_with_property(ot));
    BOOST_REQUIRE(a.objects().size() == 2);
    BOOST_REQUIRE(a.modules().empty());

    for (const auto& pair : a.objects()) {
        const auto& qn(pair.first);
        if (factory.is_type_name_n(0, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;

            const auto& o(pair.second);
            BOOST_CHECK(o.object_type() == object_types::entity);
            BOOST_CHECK(o.local_properties().size() == 1);
            BOOST_CHECK(!o.identity().empty());
        }
    }

    dogen::sml::injector i;
    i.inject(a);
    BOOST_CHECK(a.objects().size() == 2);
    BOOST_CHECK(a.modules().size() == 1);
}

BOOST_AUTO_TEST_CASE(unversioned_keyed_object_with_no_identity_attributes_throws) {
    SETUP_TEST_LOG_SOURCE("unversioned_keyed_object_with_no_identity_attributes_throws");

    const auto ot(mock_model_factory::object_types::keyed_entity);
    auto m(factory.object_with_property(ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_REQUIRE(m.objects().size() == 2);
    for (auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.is_type_name_n(0, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            auto& o(pair.second);
            BOOST_CHECK(o.object_type() == object_types::keyed_entity);
            BOOST_CHECK(o.local_properties().size() == 1);
            BOOST_CHECK(!o.is_versioned());
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
        if (factory.is_type_name_n(0, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            auto& o(pair.second);
            BOOST_CHECK(o.object_type() == object_types::keyed_entity);
            BOOST_REQUIRE(o.local_properties().size() == 1);
            BOOST_REQUIRE(!o.is_versioned());
            BOOST_REQUIRE(o.identity().size() == 1);
        }
    }

    dogen::sml::injector i;
    i.inject(m);

    BOOST_CHECK(m.objects().size() == 3);
    bool type_zero(false);
    dogen::sml::qname ukqn;
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.is_type_name_n(0, qn)) {
            type_zero = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            const auto& o(pair.second);
            BOOST_CHECK(o.object_type() == object_types::keyed_entity);
            BOOST_REQUIRE(!o.is_versioned());

            BOOST_CHECK(!has_relationship(relationship_types::versioned_keys,
                    o));
            BOOST_REQUIRE(has_relationship(relationship_types::unversioned_keys,
                    o));

            const auto rels(
                get_relationship(relationship_types::unversioned_keys, o));
            BOOST_REQUIRE(rels.size() == 1);
            ukqn = rels.front();

            BOOST_CHECK(factory.is_type_name_n_unversioned(0, ukqn));
            BOOST_CHECK(!factory.is_type_name_n_versioned(0, ukqn));
            BOOST_LOG_SEV(lg, debug) << "Found unversioned key qname: " << ukqn;
        }
    }

    BOOST_REQUIRE(type_zero);
    const auto j(m.objects().find(ukqn));
    BOOST_REQUIRE(j != m.objects().end());
    const auto& uk(j->second);
    BOOST_CHECK(uk.object_type() == object_types::unversioned_key);
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
        if (factory.is_type_name_n(0, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            auto& o(pair.second);
            BOOST_CHECK(o.object_type() == object_types::keyed_entity);
            BOOST_REQUIRE(o.local_properties().size() == 1);
            BOOST_REQUIRE(!o.is_versioned());
            BOOST_REQUIRE(o.identity().size() == 1);
            o.is_versioned(true);
        }
    }

    dogen::sml::injector i;
    i.inject(m);

    BOOST_CHECK(m.objects().size() == 4);
    bool type_zero(false);
    dogen::sml::qname ukqn, vkqn;
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.is_type_name_n(0, qn)) {
            type_zero = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            auto& o(pair.second);
            BOOST_CHECK(o.object_type() == object_types::keyed_entity);
            BOOST_CHECK(o.is_versioned());

            BOOST_CHECK(has_relationship(relationship_types::versioned_keys,
                    o));
            auto rels(get_relationship(relationship_types::versioned_keys, o));
            BOOST_REQUIRE(rels.size() == 1);
            vkqn = rels.front();
            BOOST_CHECK(!factory.is_type_name_n_unversioned(0, vkqn));
            BOOST_CHECK(factory.is_type_name_n_versioned(0, vkqn));

            BOOST_REQUIRE(has_relationship(relationship_types::unversioned_keys,
                    o));
            rels = get_relationship(relationship_types::unversioned_keys, o);
            ukqn = rels.front();
            BOOST_CHECK(factory.is_type_name_n_unversioned(0, ukqn));
            BOOST_CHECK(!factory.is_type_name_n_versioned(0, ukqn));
            BOOST_LOG_SEV(lg, debug) << "Found unversioned key qname: " << ukqn;
        }
    }

    BOOST_REQUIRE(type_zero);
    auto j(m.objects().find(ukqn));
    BOOST_REQUIRE(j != m.objects().end());

    const auto& uk(j->second);
    BOOST_CHECK(uk.object_type() == object_types::unversioned_key);
    BOOST_LOG_SEV(lg, debug) << "Found unversioned key: " << uk;
    BOOST_REQUIRE(!uk.is_versioned());

    j = m.objects().find(vkqn);
    BOOST_REQUIRE(j != m.objects().end());

    const auto& vk(j->second);
    BOOST_CHECK(vk.object_type() == object_types::versioned_key);
    BOOST_LOG_SEV(lg, debug) << "Found versioned key: " << vk;
    BOOST_REQUIRE(!vk.is_versioned());
}

BOOST_AUTO_TEST_CASE(versioned_object_has_version_propery_injected) {
    SETUP_TEST_LOG_SOURCE("versioned_object_has_version_propery_injected");

    auto m(factory.build_single_type_model());
    BOOST_REQUIRE(m.objects().size() == 1);
    auto& ob(m.objects().begin()->second);
    BOOST_REQUIRE(ob.local_properties().empty());
    ob.is_versioned(true);
    BOOST_LOG_SEV(lg, debug) << "before: " << ob;

    dogen::sml::injector i;
    i.inject(m);

    BOOST_REQUIRE(m.objects().size() == 1);
    auto& oa(m.objects().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "object after: " << oa;
    BOOST_REQUIRE(oa.local_properties().size() == 1);
    BOOST_CHECK(oa.local_properties().front().name() == version_name);
    BOOST_CHECK(!oa.local_properties().front().documentation().empty());
}

BOOST_AUTO_TEST_CASE(visitable_object_with_no_leaves_throws) {
    SETUP_TEST_LOG_SOURCE("visitable_object_with_no_leaves_throws");

    auto m(factory.build_single_type_model());
    BOOST_REQUIRE(m.objects().size() == 1);
    auto& ob(m.objects().begin()->second);
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
        if (factory.is_type_name_n(1, qn)) {
            auto& ao(pair.second);
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
        if (factory.is_type_name_n(1, qn)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;
            type_one = true;
            BOOST_REQUIRE(!pair.second.is_versioned());
        } else if (factory.is_type_name_n_visitor(1, qn)) {
            visitor = true;
            BOOST_LOG_SEV(lg, debug) << "found object: " << qn;

            const auto& o(pair.second);
            BOOST_CHECK(o.object_type() == object_types::visitor);
            BOOST_CHECK(!o.is_versioned());
            BOOST_CHECK(!o.is_visitable());
            BOOST_CHECK(!o.is_immutable());
            BOOST_CHECK(!has_relationship(relationship_types::parents, o));
            BOOST_CHECK(
                !has_relationship(relationship_types::original_parents, o));
            BOOST_CHECK(
                !has_relationship(relationship_types::modeled_concepts, o));
            BOOST_CHECK(
                !has_relationship(relationship_types::leaves, o));
            BOOST_CHECK(o.number_of_type_arguments() == 0);

            BOOST_REQUIRE(o.operations().empty());
        }
    }

    BOOST_CHECK(type_one);
    BOOST_CHECK(visitor);
}

BOOST_AUTO_TEST_SUITE_END()
