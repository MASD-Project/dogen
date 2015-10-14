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
#ifndef DOGEN_UTILITY_TEST_LESS_THAN_TESTER_HPP
#define DOGEN_UTILITY_TEST_LESS_THAN_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace utility {
namespace test {

template<typename Entity, typename Sequence>
class less_than_tester {
private:
    typedef Entity entity_type;
    typedef Sequence sequence_type;

public:
    static void equal_objects_are_not_smaller_or_greater_than_each_other() {
        sequence_type sequence;
        const entity_type a(sequence());
        const entity_type b(a);

        using dogen::utility::streaming::jsonify;
        using namespace dogen::utility::log;
        logger lg(logger_factory("utility.test.less_than"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
        BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
        BOOST_CHECK(!(a < b));
        BOOST_CHECK(!(b < a));
        log_if_test_has_failed();
    }

    static void unequal_objects_are_not_both_smaller_and_greater_than_each_other() {
        sequence_type sequence;
        const entity_type a(sequence());
        const entity_type b(sequence());

        using dogen::utility::streaming::jsonify;
        using namespace dogen::utility::log;
        logger lg(logger_factory("utility.test.less_than"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
        BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
        BOOST_CHECK(a != b);
        BOOST_CHECK((a < b && (!(b < a))) || (b < a && (!(a < b))));
        log_if_test_has_failed();
    }
};

} } }

#endif
