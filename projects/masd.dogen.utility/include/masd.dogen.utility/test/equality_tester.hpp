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
#ifndef MASD_DOGEN_UTILITY_TEST_EQUALITY_TESTER_HPP
#define MASD_DOGEN_UTILITY_TEST_EQUALITY_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/test/unit_test.hpp>
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.utility/io/jsonify_io.hpp"

namespace masd::dogen::utility::test {

/**
 * @brief Provides tests for different aspects of equality of domain
 * objects.
 */
template<typename Entity>
class equality_tester {
private:
    typedef Entity entity_type;

public:
    static void
    identical_objects_are_equal(const entity_type& a, const entity_type& b) {
        using dogen::utility::streaming::jsonify;
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.equality_tester"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
        BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);

        BOOST_CHECK(a == b);
        BOOST_CHECK(b == a);
        BOOST_CHECK(!(a != b));
        log_if_test_has_failed();
    }

    static void an_object_is_equal_to_itself(const entity_type& a) {
        using dogen::utility::streaming::jsonify;
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.equality_tester"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);

        BOOST_CHECK(a == a);
        BOOST_CHECK(!(a != a));
        log_if_test_has_failed();
    }

    /**
     * @brief Objects with distinct states are unequal.
     *
     * This cannot be proved for the general case, but we're trying to
     * catch silly errors here.
     */
    static void
    distinct_objects_are_unequal(const entity_type& a, const entity_type& b) {
        using dogen::utility::streaming::jsonify;
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.equality_tester"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
        BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);

        BOOST_CHECK(!(a == b));
        BOOST_CHECK(a != b);
        log_if_test_has_failed();
    }
};

}

#endif
