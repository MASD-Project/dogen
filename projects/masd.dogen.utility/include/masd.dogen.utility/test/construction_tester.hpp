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
#ifndef MASD_DOGEN_UTILITY_TEST_CONSTRUCTION_TESTER_HPP
#define MASD_DOGEN_UTILITY_TEST_CONSTRUCTION_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.utility/io/jsonify_io.hpp"
#include "masd.dogen.utility/log/logger.hpp"

namespace masd::dogen::utility::test {

/**
 * @brief Requirements for object construction.
 *
 * These requirements should only cover behaviour which is not already
 * covered by other requirements such as equality or less_than, etc.
 */
template<class Entity, class Sequence>
class construction_tester {
private:
    typedef Entity entity_type;
    typedef Sequence sequence_type;

public:
    static void assigning_an_object_to_itself_results_in_the_same_object() {
        sequence_type sequence;
        entity_type a(sequence());
        entity_type b(a);

        using dogen::utility::streaming::jsonify;
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.equality_tester"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
        BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);

        a = a;
        BOOST_LOG_SEV(lg, debug) << "a after assignment: " << jsonify(a);
        BOOST_CHECK(a == b);
        log_if_test_has_failed();
    }

    /**
     * @brief An object created by the default constructor shall have
     * all public properties set to appropriate default values, as
     * defined by their type.
     *
     * - Numeric types are expected to be zero;
     * - Boolean properties are expected to be false;
     * - For complex types which implement empty(), the property is
     *   expected to be empty();
     * - For any other complex types the expected value is as given by
     *   their default constructor.
     */
    // virtual void
    // default_constructed_object_has_all_properties_initialised() = 0;

    /**
     * @brief An object created by the complete constructor shall have
     * all public properties set to the values passed in to the
     * complete constructor.
     *
     * A complete constructor is defined to be a constructor which has
     * as arguments values for every settable public property
     * available on a class.
     */
    // virtual void
    // complete_constructed_object_matches_properties_set_object() = 0;
};

}

#endif
