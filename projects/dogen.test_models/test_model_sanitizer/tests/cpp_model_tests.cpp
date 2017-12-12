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
#include "dogen.utility/io/vector_io.hpp"
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/test/canned_tests.hpp"
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
