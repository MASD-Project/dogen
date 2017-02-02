/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <memory>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/test_models/trivial_inheritance/types/all.hpp"
#include "dogen/test_models/trivial_inheritance/types/base_visitor.hpp"
#include "dogen/test_models/trivial_inheritance/io/all_io.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/all_ser.hpp"
#include "dogen/test_models/test_model_sanitizer/register_types.hpp"
#include "dogen/test_models/trivial_inheritance/test_data/all_td.hpp"
#include "dogen/test_models/trivial_inheritance/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("trivial_inheritance_tests");

class mock_visitor
    : public dogen::test_models::trivial_inheritance::base_visitor {
public:
    mock_visitor() { reset(); }

public:
    using dogen::test_models::trivial_inheritance::base_visitor::visit;

public:
    virtual void visit(
        const dogen::test_models::trivial_inheritance::descendant2&
        ) const override {
        visited |= 0x02;
    }

    virtual void visit(
        const dogen::test_models::trivial_inheritance::descendant2&) override {
        visited |= 0x04;
    }

    virtual void visit(
        dogen::test_models::trivial_inheritance::descendant2&) const override {
        visited |= 0x08;
    }

    virtual void visit(
        dogen::test_models::trivial_inheritance::descendant2&
        ) override {
        visited |= 0x10;
    }

    virtual void visit(
        const dogen::test_models::trivial_inheritance::descendant3&
        ) const override {
        visited |= 0x20;
    }

    virtual void visit(
        const dogen::test_models::trivial_inheritance::descendant3&) override {
        visited |= 0x30;
    }

    virtual void visit(
        dogen::test_models::trivial_inheritance::descendant3& d
        ) const override {
        d.prop_0(true);
        visited |= 0x40;
    }

    virtual void visit(
        dogen::test_models::trivial_inheritance::descendant3& d) override {
        d.prop_0(true);
        visited |= 0x50;
    }

    void reset() const { visited = 0; }

    mutable unsigned int visited;
};

}

using namespace dogen::test_models::trivial_inheritance;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(trivial_inheritance_tests)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<child_with_members_generator>();
    test_equality<second_child_without_members_generator>();
    test_equality<child_of_a_child1_generator>();
    test_equality<child_of_a_child2_generator>();
    test_equality<pkg1::child_generator>();
    test_equality<pkg3::child_generator>();
    test_equality<pkg4::child_generator>();
    test_equality<move_ctor_descendant_generator>();
    test_equality<move_ctor_empty_descendant_generator>();
    test_equality<child_via_settings_generator>();
    test_equality<pkg1::child_via_settings_generator>();
    test_equality<pkg3::child_via_settings_generator>();
    test_equality<pkg4::child_via_settings_generator>();
    test_equality<non_final_leaf_generator>();
    test_equality<non_final_orphan_generator>();
    test_equality<descendant2_generator>();
    test_equality<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    roundtrip_type<child_with_members_generator>();
    roundtrip_type<second_child_without_members_generator>();
    roundtrip_type<child_of_a_child1_generator>();
    roundtrip_type<child_of_a_child2_generator>();
    roundtrip_type<pkg1::child_generator>();
    roundtrip_type<pkg3::child_generator>();
    roundtrip_type<pkg4::child_generator>();
    roundtrip_type<move_ctor_descendant_generator>();
    roundtrip_type<move_ctor_empty_descendant_generator>();
    roundtrip_type<child_via_settings_generator>();
    roundtrip_type<pkg1::child_via_settings_generator>();
    roundtrip_type<pkg3::child_via_settings_generator>();
    roundtrip_type<pkg4::child_via_settings_generator>();
    roundtrip_type<non_final_leaf_generator>();
    roundtrip_type<non_final_orphan_generator>();
    roundtrip_type<descendant2_generator>();
    roundtrip_type<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<child_with_members_generator>();
    test_hashing<second_child_without_members_generator>();
    test_hashing<child_of_a_child1_generator>();
    test_hashing<child_of_a_child2_generator>();
    test_hashing<pkg1::child_generator>();
    test_hashing<pkg3::child_generator>();
    test_hashing<pkg4::child_generator>();
    test_hashing<move_ctor_descendant_generator>();
    test_hashing<move_ctor_empty_descendant_generator>();
    test_hashing<child_via_settings_generator>();
    test_hashing<pkg1::child_via_settings_generator>();
    test_hashing<pkg3::child_via_settings_generator>();
    test_hashing<pkg4::child_via_settings_generator>();
    test_hashing<non_final_leaf_generator>();
    test_hashing<non_final_orphan_generator>();
    test_hashing<descendant2_generator>();
    test_hashing<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_swap");
    test_swap<child_with_members_generator>();
    test_swap<second_child_without_members_generator>();
    test_swap<child_of_a_child1_generator>();
    test_swap<child_of_a_child2_generator>();
    test_swap<pkg1::child_generator>();
    test_swap<pkg3::child_generator>();
    test_swap<pkg4::child_generator>();
    test_swap<move_ctor_descendant_generator>();
    test_swap<move_ctor_empty_descendant_generator>();
    test_swap<child_via_settings_generator>();
    test_swap<pkg1::child_via_settings_generator>();
    test_swap<pkg3::child_via_settings_generator>();
    test_swap<pkg4::child_via_settings_generator>();
    test_swap<non_final_leaf_generator>();
    test_swap<non_final_orphan_generator>();
    test_swap<descendant2_generator>();
    test_swap<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<child_with_members_generator>();
    test_io<second_child_without_members_generator>();
    test_io<child_of_a_child1_generator>();
    test_io<child_of_a_child2_generator>();
    test_io<pkg1::child_generator>();
    test_io<pkg3::child_generator>();
    test_io<pkg4::child_generator>();
    test_io<move_ctor_descendant_generator>();
    test_io<move_ctor_empty_descendant_generator>();
    test_io<child_via_settings_generator>();
    test_io<pkg1::child_via_settings_generator>();
    test_io<pkg3::child_via_settings_generator>();
    test_io<pkg4::child_via_settings_generator>();
    test_io<non_final_leaf_generator>();
    test_io<non_final_orphan_generator>();
    test_io<descendant2_generator>();
    test_io<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");

    test_move_assignment_copy<child_with_members_generator>();
    test_move_assignment_copy<second_child_without_members_generator>();
    test_move_assignment_copy<child_of_a_child1_generator>();
    test_move_assignment_copy<child_of_a_child2_generator>();
    test_move_assignment_copy<pkg1::child_generator>();
    test_move_assignment_copy<pkg3::child_generator>();
    test_move_assignment_copy<pkg4::child_generator>();
    test_move_assignment_copy<move_ctor_descendant_generator>();
    test_move_assignment_copy<move_ctor_empty_descendant_generator>();
    test_move_assignment_copy<child_via_settings_generator>();
    test_move_assignment_copy<pkg1::child_via_settings_generator>();
    test_move_assignment_copy<pkg3::child_via_settings_generator>();
    test_move_assignment_copy<pkg4::child_via_settings_generator>();
    test_move_assignment_copy<non_final_leaf_generator>();
    test_move_assignment_copy<non_final_orphan_generator>();
    test_move_assignment_copy<descendant2_generator>();
    test_move_assignment_copy<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(visitor_dispatches_to_the_correct_classes) {
    SETUP_TEST_LOG_SOURCE("visitor_dispatches_to_the_correct_classes");

    using namespace dogen::test_models::trivial_inheritance;
    std::unique_ptr<base> b1(descendant3_generator::create_ptr(0));

    mock_visitor v;
    b1->accept(v);
    BOOST_LOG_SEV(lg, debug) << v.visited;
    BOOST_CHECK(v.visited == 0x50);
    v.reset();

    const mock_visitor cv;
    b1->accept(cv);
    BOOST_LOG_SEV(lg, debug) << cv.visited;
    BOOST_CHECK(cv.visited == 0x40);
    cv.reset();

    std::unique_ptr<const base> b2(descendant3_generator::create_ptr(0));
    b2->accept(v);
    BOOST_LOG_SEV(lg, debug) << v.visited;
    BOOST_CHECK(v.visited == 0x30);
    v.reset();

    b2->accept(cv);
    BOOST_LOG_SEV(lg, debug) << cv.visited;
    BOOST_CHECK(cv.visited == 0x20);
    cv.reset();

    std::unique_ptr<descendant1> d1(descendant3_generator::create_ptr(0));
    d1->accept(v);
    BOOST_LOG_SEV(lg, debug) << v.visited;
    BOOST_CHECK(v.visited == 0x50);
    v.reset();

    d1->accept(cv);
    BOOST_LOG_SEV(lg, debug) << cv.visited;
    BOOST_CHECK(cv.visited == 0x40);
    cv.reset();

    std::unique_ptr<const descendant1> d2(descendant3_generator::create_ptr(0));
    d2->accept(v);
    BOOST_LOG_SEV(lg, debug) << v.visited;
    BOOST_CHECK(v.visited == 0x30);
    v.reset();

    d2->accept(cv);
    BOOST_LOG_SEV(lg, debug) << cv.visited;
    BOOST_CHECK(cv.visited == 0x20);
    cv.reset();

    std::unique_ptr<base> b3(descendant2_generator::create_ptr(0));
    b3->accept(v);
    BOOST_LOG_SEV(lg, debug) << v.visited;
    BOOST_CHECK(v.visited == 0x10);
    v.reset();

    b3->accept(cv);
    BOOST_LOG_SEV(lg, debug) << cv.visited;
    BOOST_CHECK(cv.visited == 0x08);
    cv.reset();

    std::unique_ptr<const base> b4(descendant2_generator::create_ptr(0));
    b4->accept(v);
    BOOST_LOG_SEV(lg, debug) << v.visited;
    BOOST_CHECK(v.visited == 0x04);
    v.reset();

    b4->accept(cv);
    BOOST_LOG_SEV(lg, debug) << cv.visited;
    BOOST_CHECK(cv.visited == 0x02);
    cv.reset();
}

BOOST_AUTO_TEST_SUITE_END()
