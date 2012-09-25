/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_ORG_SPEC_LESS_THAN_HPP
#define DOGEN_ORG_SPEC_LESS_THAN_HPP

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
class less_than {
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
        logger lg(logger_factory("less_than"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
        BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
        BOOST_CHECK(!(a < b));
        BOOST_CHECK(!(b < a));
    }

    static void unequal_objects_are_not_both_smaller_and_greater_than_each_other() {
        sequence_type sequence;
        const entity_type a(sequence());
        const entity_type b(sequence());

        using dogen::utility::streaming::jsonify;
        using namespace dogen::utility::log;
        logger lg(logger_factory("less_than"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
        BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
        BOOST_CHECK(a != b);
        BOOST_CHECK((a < b && (!(b < a))) || (b < a && (!(a < b))));
    }
};

} } }

#endif
