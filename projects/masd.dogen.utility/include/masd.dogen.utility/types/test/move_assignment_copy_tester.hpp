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
#ifndef MASD_DOGEN_UTILITY_TEST_MOVE_ASSIGNMENT_COPY_TESTER_HPP
#define MASD_DOGEN_UTILITY_TEST_MOVE_ASSIGNMENT_COPY_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/test/unit_test.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"

namespace masd::dogen::utility::test {

/**
 * @brief Provides tests for copy construction, as well as move and
 * assignment operators.
 */
template<typename Entity>
class move_assignment_copy_tester {
private:
    typedef Entity entity_type;

public:
    /**
     * @brief Objects moved using the move constructor keep their
     * state.
     */
    static void moved_objects_are_equal(const entity_type& a) {
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.move_assignment_copy"));
        BOOST_LOG_SEV(lg, debug) << "a: " << a;

        // ensure a is different from a default object
        const entity_type b = entity_type();
        BOOST_LOG_SEV(lg, debug) << "b: " << b;
        BOOST_CHECK(a != b);

        // rely on copy constructor to work
        const entity_type c = std::move(entity_type(a));
        BOOST_LOG_SEV(lg, debug) << "c: " << c;
        BOOST_CHECK(a == c);
        log_if_test_has_failed();
    }

    /**
     * @brief Objects assigned using the assignment operator keep
     * their state.
     */
    static void assigned_objects_are_equal(const entity_type& a) {
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.move_assignment_copy"));
        BOOST_LOG_SEV(lg, debug) << "a: " << a;

        // ensure a is different from a default object
        const entity_type b = entity_type();
        BOOST_LOG_SEV(lg, debug) << "b: " << b;
        BOOST_CHECK(a != b);

        // rely on copy constructor to work
        const entity_type c = std::move(entity_type(a));
        BOOST_LOG_SEV(lg, debug) << "c: " << c;
        BOOST_CHECK(a == c);
        log_if_test_has_failed();
    }

    /**
     * @brief Objects copied using the copy constructor keep their
     * state.
     */
    static void copy_constructed_objects_are_equal(const entity_type& a) {
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.move_assignment_copy"));
        BOOST_LOG_SEV(lg, debug) << "a: " << a;

        // ensure a is different from a default object
        const entity_type b = entity_type();
        BOOST_LOG_SEV(lg, debug) << "b: " << b;
        BOOST_CHECK(a != b);

        const entity_type c = entity_type(a);
        BOOST_LOG_SEV(lg, debug) << "c: " << c;
        BOOST_CHECK(a == c);
        log_if_test_has_failed();
    }
};

}

#endif
