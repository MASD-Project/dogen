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
#include <boost/test/unit_test.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/test_models/cpp_model/types/all.hpp"
#include "dogen/test_models/cpp_model/io/all_io.hpp"
#include "dogen/test_models/cpp_model/serialization/all_ser.hpp"
#include "dogen/test_models/test_model_sanitizer/register_types.hpp"
#include "dogen/test_models/cpp_model/test_data/all_td.hpp"
#include "dogen/test_models/cpp_model/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("cpp_model_tests");

class mock_visitor
    : public dogen::test_models::cpp_model::base_visitor {
public:
    mock_visitor() { reset(); }

public:
    using dogen::test_models::cpp_model::base_visitor::visit;

public:
    virtual void visit(
        const dogen::test_models::cpp_model::descendant2&
        ) const override {
        visited |= 0x02;
    }

    virtual void visit(
        const dogen::test_models::cpp_model::descendant2&) override {
        visited |= 0x04;
    }

    virtual void visit(
        dogen::test_models::cpp_model::descendant2&) const override {
        visited |= 0x08;
    }

    virtual void visit(
        dogen::test_models::cpp_model::descendant2&
        ) override {
        visited |= 0x10;
    }

    virtual void visit(
        const dogen::test_models::cpp_model::descendant3&
        ) const override {
        visited |= 0x20;
    }

    virtual void visit(
        const dogen::test_models::cpp_model::descendant3&) override {
        visited |= 0x30;
    }

    virtual void visit(
        dogen::test_models::cpp_model::descendant3& d
        ) const override {
        d.prop_0(true);
        visited |= 0x40;
    }

    virtual void visit(
        dogen::test_models::cpp_model::descendant3& d) override {
        d.prop_0(true);
        visited |= 0x50;
    }

    void reset() const { visited = 0; }

    mutable unsigned int visited;
};

}

using namespace dogen::test_models::cpp_model;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(cpp_model_tests)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<a_class_generator>();
    test_equality<class_1_generator>();

    test_equality<package_1::class_1_generator>();
    test_equality<package_1::class_2_generator>();
    test_equality<package_1::class_3_generator>();
    test_equality<package_1::class_4_generator>();
    test_equality<package_1::class_5_generator>();
    test_equality<package_2::class_1_generator>();

    test_equality<book_types_generator>();
    test_equality<colour_types_generator>();
    test_equality<package_4::shape_types_generator>();
    test_equality<a_class_generator>();

    test_equality<short_primitive_generator>();
    test_equality<ushort_primitive_generator>();
    test_equality<long_primitive_generator>();
    test_equality<ulong_primitive_generator>();
    test_equality<int_primitive_generator>();
    test_equality<uint_primitive_generator>();
    test_equality<char_primitive_generator>();
    test_equality<uchar_primitive_generator>();
    test_equality<double_primitive_generator>();
    test_equality<float_primitive_generator>();
    test_equality<bool_primitive_generator>();
    test_equality<immutable_primitive_generator>();

    test_equality<consumer_generator>();

    test_equality<value_generator>();
    test_equality<immutable_four_generator>();
    test_equality<immutable_one_non_builtin_generator>();
    test_equality<immutable_one_builtin_generator>();
    test_equality<immutable_two_generator>();
    test_equality<fluent_generator>();
    test_equality<fluent_generator>();
    test_equality<simple_concept_model_generator>();
    test_equality<base_concept_model_generator>();
    test_equality<refinement_concept_model_generator>();
    test_equality<multiple_refinement_concept_model_generator>();
    test_equality<multi_concept_model_generator>();
    test_equality<further_refined_generator>();

    test_equality<class_a_generator>();
    test_equality<class_b_generator>();

    test_equality<child_with_members_generator>();
    test_equality<second_child_without_members_generator>();
    test_equality<child_of_a_child1_generator>();
    test_equality<child_of_a_child2_generator>();
    test_equality<package_6::child_generator>();
    test_equality<package_8::child_generator>();
    test_equality<package_9::child_generator>();
    test_equality<move_ctor_descendant_generator>();
    test_equality<move_ctor_empty_descendant_generator>();
    test_equality<child_via_settings_generator>();
    test_equality<package_6::child_via_settings_generator>();
    test_equality<package_8::child_via_settings_generator>();
    test_equality<package_9::child_via_settings_generator>();
    test_equality<non_final_leaf_generator>();
    test_equality<non_final_orphan_generator>();
    test_equality<descendant2_generator>();
    test_equality<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    roundtrip_type<a_class_generator>();
    roundtrip_type<class_1_generator>();

    roundtrip_type<package_1::class_1_generator>();
    roundtrip_type<package_1::class_2_generator>();
    roundtrip_type<package_1::class_3_generator>();
    roundtrip_type<package_1::class_4_generator>();
    roundtrip_type<package_1::class_5_generator>();
    roundtrip_type<package_2::class_1_generator>();

    roundtrip_type<book_types_generator>();
    roundtrip_type<colour_types_generator>();
    roundtrip_type<package_4::shape_types_generator>();
    roundtrip_type<a_class_generator>();

    roundtrip_type<short_primitive_generator>();
    roundtrip_type<ushort_primitive_generator>();
    roundtrip_type<long_primitive_generator>();
    roundtrip_type<ulong_primitive_generator>();
    roundtrip_type<int_primitive_generator>();
    roundtrip_type<uint_primitive_generator>();
    roundtrip_type<char_primitive_generator>();
    roundtrip_type<uchar_primitive_generator>();
    roundtrip_type<double_primitive_generator>();
    roundtrip_type<float_primitive_generator>();
    roundtrip_type<bool_primitive_generator>();
    roundtrip_type<immutable_primitive_generator>();

    roundtrip_type<consumer_generator>();

    roundtrip_type<value_generator>();
    roundtrip_type<immutable_four_generator>();
    roundtrip_type<immutable_one_non_builtin_generator>();
    roundtrip_type<immutable_one_builtin_generator>();
    roundtrip_type<immutable_two_generator>();
    roundtrip_type<fluent_generator>();
    roundtrip_type<fluent_generator>();
    roundtrip_type<simple_concept_model_generator>();
    roundtrip_type<base_concept_model_generator>();
    roundtrip_type<refinement_concept_model_generator>();
    roundtrip_type<multiple_refinement_concept_model_generator>();
    roundtrip_type<multi_concept_model_generator>();
    roundtrip_type<further_refined_generator>();

    roundtrip_type<class_a_generator>();
    roundtrip_type<class_b_generator>();

    roundtrip_type<child_with_members_generator>();
    roundtrip_type<second_child_without_members_generator>();
    roundtrip_type<child_of_a_child1_generator>();
    roundtrip_type<child_of_a_child2_generator>();
    roundtrip_type<package_6::child_generator>();
    roundtrip_type<package_8::child_generator>();
    roundtrip_type<package_9::child_generator>();
    roundtrip_type<move_ctor_descendant_generator>();
    roundtrip_type<move_ctor_empty_descendant_generator>();
    roundtrip_type<child_via_settings_generator>();
    roundtrip_type<package_6::child_via_settings_generator>();
    roundtrip_type<package_8::child_via_settings_generator>();
    roundtrip_type<package_9::child_via_settings_generator>();
    roundtrip_type<non_final_leaf_generator>();
    roundtrip_type<non_final_orphan_generator>();
    roundtrip_type<descendant2_generator>();
    roundtrip_type<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<a_class_generator>();
    test_hashing<class_1_generator>();

    test_hashing<package_1::class_1_generator>();
    test_hashing<package_1::class_2_generator>();
    test_hashing<package_1::class_3_generator>();
    test_hashing<package_1::class_4_generator>();
    test_hashing<package_1::class_5_generator>();
    test_hashing<package_2::class_1_generator>();

    test_hashing<book_types_generator>();
    test_hashing<colour_types_generator>();
    test_hashing<package_4::shape_types_generator>();
    test_hashing<a_class_generator>();

    test_hashing<short_primitive_generator>();
    test_hashing<ushort_primitive_generator>();
    test_hashing<long_primitive_generator>();
    test_hashing<ulong_primitive_generator>();
    test_hashing<int_primitive_generator>();
    test_hashing<uint_primitive_generator>();
    test_hashing<char_primitive_generator>();
    test_hashing<uchar_primitive_generator>();
    test_hashing<double_primitive_generator>();
    test_hashing<float_primitive_generator>();
    test_hashing<bool_primitive_generator>();
    test_hashing<immutable_primitive_generator>();

    test_hashing<consumer_generator>();

    test_hashing<value_generator>();
    test_hashing<immutable_four_generator>();
    test_hashing<immutable_one_non_builtin_generator>();
    test_hashing<immutable_one_builtin_generator>();
    test_hashing<immutable_two_generator>();
    test_hashing<fluent_generator>();
    test_hashing<fluent_generator>();
    test_hashing<simple_concept_model_generator>();
    test_hashing<base_concept_model_generator>();
    test_hashing<refinement_concept_model_generator>();
    test_hashing<multi_concept_model_generator>();
    test_hashing<further_refined_generator>();

    test_hashing<class_a_generator>();
    test_hashing<class_b_generator>();

    test_hashing<child_with_members_generator>();
    test_hashing<second_child_without_members_generator>();
    test_hashing<child_of_a_child1_generator>();
    test_hashing<child_of_a_child2_generator>();
    test_hashing<package_6::child_generator>();
    test_hashing<package_8::child_generator>();
    test_hashing<package_9::child_generator>();
    test_hashing<move_ctor_descendant_generator>();
    test_hashing<move_ctor_empty_descendant_generator>();
    test_hashing<child_via_settings_generator>();
    test_hashing<package_6::child_via_settings_generator>();
    test_hashing<package_8::child_via_settings_generator>();
    test_hashing<package_9::child_via_settings_generator>();
    test_hashing<non_final_leaf_generator>();
    test_hashing<non_final_orphan_generator>();
    test_hashing<descendant2_generator>();
    test_hashing<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_swap");
    test_swap<a_class_generator>();
    test_swap<class_1_generator>();

    test_swap<package_1::class_1_generator>();
    test_swap<package_1::class_2_generator>();
    test_swap<package_1::class_3_generator>();
    test_swap<package_1::class_4_generator>();
    test_swap<package_1::class_5_generator>();
    test_swap<package_2::class_1_generator>();

    test_swap<book_types_generator>();
    test_swap<colour_types_generator>();
    test_swap<package_4::shape_types_generator>();
    test_swap<a_class_generator>();

    test_swap<short_primitive_generator>();
    test_swap<ushort_primitive_generator>();
    test_swap<long_primitive_generator>();
    test_swap<ulong_primitive_generator>();
    test_swap<int_primitive_generator>();
    test_swap<uint_primitive_generator>();
    test_swap<char_primitive_generator>();
    test_swap<uchar_primitive_generator>();
    test_swap<double_primitive_generator>();
    test_swap<float_primitive_generator>();
    test_swap<bool_primitive_generator>();

    test_swap<consumer_generator>();

    test_swap<value_generator>();
    test_swap<fluent_generator>();
    test_swap<simple_concept_model_generator>();
    test_swap<base_concept_model_generator>();
    test_swap<refinement_concept_model_generator>();
    test_swap<multiple_refinement_concept_model_generator>();

    test_swap<class_a_generator>();
    test_swap<class_b_generator>();

    test_swap<child_with_members_generator>();
    test_swap<second_child_without_members_generator>();
    test_swap<child_of_a_child1_generator>();
    test_swap<child_of_a_child2_generator>();
    test_swap<package_6::child_generator>();
    test_swap<package_8::child_generator>();
    test_swap<package_9::child_generator>();
    test_swap<move_ctor_descendant_generator>();
    test_swap<move_ctor_empty_descendant_generator>();
    test_swap<child_via_settings_generator>();
    test_swap<package_6::child_via_settings_generator>();
    test_swap<package_8::child_via_settings_generator>();
    test_swap<package_9::child_via_settings_generator>();
    test_swap<non_final_leaf_generator>();
    test_swap<non_final_orphan_generator>();
    test_swap<descendant2_generator>();
    test_swap<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<a_class_generator>();
    test_io<class_1_generator>();

    test_io<package_1::class_1_generator>();
    test_io<package_1::class_2_generator>();
    test_io<package_1::class_3_generator>();
    test_io<package_1::class_4_generator>();
    test_io<package_1::class_5_generator>();
    test_io<package_2::class_1_generator>();

    test_io<book_types_generator>();
    test_io<colour_types_generator>();
    test_io<package_4::shape_types_generator>();
    test_io<a_class_generator>();

    test_io<short_primitive_generator>();
    test_io<ushort_primitive_generator>();
    test_io<long_primitive_generator>();
    test_io<ulong_primitive_generator>();
    test_io<int_primitive_generator>();
    test_io<uint_primitive_generator>();
    test_io<char_primitive_generator>();
    test_io<uchar_primitive_generator>();
    test_io<double_primitive_generator>();
    test_io<float_primitive_generator>();
    test_io<bool_primitive_generator>();
    test_io<immutable_primitive_generator>();

    test_io<consumer_generator>();

    test_io<value_generator>();
    test_io<immutable_four_generator>();
    test_io<immutable_one_non_builtin_generator>();
    test_io<immutable_one_builtin_generator>();
    test_io<immutable_two_generator>();
    test_io<immutable_zero_generator>();
    test_io<fluent_generator>();
    test_io<fluent_generator>();
    test_io<simple_concept_model_generator>();
    test_io<base_concept_model_generator>();
    test_io<refinement_concept_model_generator>();
    test_io<multiple_refinement_concept_model_generator>();
    test_io<multi_concept_model_generator>();
    test_io<further_refined_generator>();

    test_io<class_a_generator>();
    test_io<class_b_generator>();

    test_io<child_with_members_generator>();
    test_io<second_child_without_members_generator>();
    test_io<child_of_a_child1_generator>();
    test_io<child_of_a_child2_generator>();
    test_io<package_6::child_generator>();
    test_io<package_8::child_generator>();
    test_io<package_9::child_generator>();
    test_io<move_ctor_descendant_generator>();
    test_io<move_ctor_empty_descendant_generator>();
    test_io<child_via_settings_generator>();
    test_io<package_6::child_via_settings_generator>();
    test_io<package_8::child_via_settings_generator>();
    test_io<package_9::child_via_settings_generator>();
    test_io<non_final_leaf_generator>();
    test_io<non_final_orphan_generator>();
    test_io<descendant2_generator>();
    test_io<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");
    test_move_assignment_copy<a_class_generator>();

    test_move_assignment_copy<package_1::class_1_generator>();
    test_move_assignment_copy<package_1::class_2_generator>();
    test_move_assignment_copy<package_1::class_3_generator>();
    test_move_assignment_copy<package_1::class_4_generator>();
    test_move_assignment_copy<package_1::class_5_generator>();

    test_move_assignment_copy<book_types_generator>();
    test_move_assignment_copy<colour_types_generator>();
    test_move_assignment_copy<package_4::shape_types_generator>();
    test_move_assignment_copy<a_class_generator>();

    test_move_assignment_copy<short_primitive_generator>();
    test_move_assignment_copy<ushort_primitive_generator>();
    test_move_assignment_copy<long_primitive_generator>();
    test_move_assignment_copy<ulong_primitive_generator>();
    test_move_assignment_copy<int_primitive_generator>();
    test_move_assignment_copy<uint_primitive_generator>();
    test_move_assignment_copy<char_primitive_generator>();
    test_move_assignment_copy<uchar_primitive_generator>();
    test_move_assignment_copy<double_primitive_generator>();
    test_move_assignment_copy<float_primitive_generator>();
    // FIXME: commented out due to the well-known oscillation problems
    // with booleans.
    // test_move_assignment_copy<bool_primitive_generator>();
    test_move_assignment_copy<immutable_primitive_generator>();

    test_move_assignment_copy<consumer_generator>();

    // NOTE: skipping immutable_one_builtin because boolean types
    // don't play well with our requirement that the parameter passed
    // in must not be equal to a default constructed type.
    test_move_assignment_copy<value_generator>();
    test_move_assignment_copy<immutable_four_generator>();
    test_move_assignment_copy<immutable_one_non_builtin_generator>();
    test_move_assignment_copy<immutable_two_generator>();
    test_move_assignment_copy<fluent_generator>();
    test_move_assignment_copy<fluent_generator>();
    test_move_assignment_copy<simple_concept_model_generator>();
    test_move_assignment_copy<base_concept_model_generator>();
    test_move_assignment_copy<refinement_concept_model_generator>();
    test_move_assignment_copy<multiple_refinement_concept_model_generator>();
    test_move_assignment_copy<multi_concept_model_generator>();
    test_move_assignment_copy<further_refined_generator>();

    test_move_assignment_copy<class_a_generator>();
    test_move_assignment_copy<class_b_generator>();

    test_move_assignment_copy<child_with_members_generator>();
    test_move_assignment_copy<second_child_without_members_generator>();
    test_move_assignment_copy<child_of_a_child1_generator>();
    test_move_assignment_copy<child_of_a_child2_generator>();
    test_move_assignment_copy<package_6::child_generator>();
    test_move_assignment_copy<package_8::child_generator>();
    test_move_assignment_copy<package_9::child_generator>();
    test_move_assignment_copy<move_ctor_descendant_generator>();
    test_move_assignment_copy<move_ctor_empty_descendant_generator>();
    test_move_assignment_copy<child_via_settings_generator>();
    test_move_assignment_copy<package_6::child_via_settings_generator>();
    test_move_assignment_copy<package_8::child_via_settings_generator>();
    test_move_assignment_copy<package_9::child_via_settings_generator>();
    test_move_assignment_copy<non_final_leaf_generator>();
    test_move_assignment_copy<non_final_orphan_generator>();
    test_move_assignment_copy<descendant2_generator>();
    test_move_assignment_copy<descendant3_generator>();
}

BOOST_AUTO_TEST_CASE(exception_shall_be_usable_as_a_standard_exception) {
    SETUP_TEST_LOG_SOURCE("exception_shall_be_usable_as_a_standard_exception");
    const std::string message("test message");
    try {
        throw(my_error(message));
        BOOST_FAIL("Expected exception to be thrown.");
    } catch(const std::exception& e) {
        const std::string what(e.what());
        BOOST_CHECK(what == message);
        BOOST_LOG_SEV(lg, info) << "Exception thrown as expected. what: "
                                << e.what();
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_CASE(exception_shall_be_usable_as_a_boost_exception) {
    SETUP_TEST_LOG_SOURCE("exception_shall_be_usable_as_a_boost_exception");
    const std::string message("test message");
    try {
        BOOST_THROW_EXCEPTION(my_error(message));
        BOOST_FAIL("Expected exception to be thrown.");
    } catch(const boost::exception& e) {
        BOOST_LOG_SEV(lg, debug) << "Exception thrown as expected. diagnostic: "
                                 << boost::diagnostic_information(e);
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_CASE(setting_properties_using_the_fluent_interface_produces_expected_result) {
    SETUP_TEST_LOG("setting_properties_using_the_fluent_interface_produces_expected_result");

    const value z(15);
    const std::string s("a string");
    const fluent e(1234, s, z);
    fluent a;
    a.prop_0(1234).prop_1(s).prop_2(z);
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(visitor_dispatches_to_the_correct_classes) {
    SETUP_TEST_LOG_SOURCE("visitor_dispatches_to_the_correct_classes");

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
