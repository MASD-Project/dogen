/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_HASH_TESTER_HPP
#define DOGEN_UTILITY_TEST_HASH_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace utility {
namespace test {

template<typename Sequence>
class hash_tester {
private:
    typedef typename Sequence::value_type entity_type;
    typedef Sequence sequence_type;

public:
    static void equal_objects_must_generate_the_same_hash() {
        sequence_type sequence;
        const entity_type a(sequence());
        const entity_type b(a);

        using dogen::utility::streaming::jsonify;
        using namespace dogen::utility::log;
        logger lg(logger_factory("hash_tester"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
        BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
        BOOST_CHECK(a == b);

        std::hash<entity_type> hasher;
        BOOST_CHECK(hasher(a) == hasher(b));
        BOOST_LOG_SEV(lg, debug) << "Hash a: " << hasher(a);
        BOOST_LOG_SEV(lg, debug) << "Hash b: " << hasher(b);
    }

    static void unequal_objects_must_generate_different_hashes() {
        sequence_type sequence;
        const entity_type a(sequence());
        const entity_type b(sequence());

        using dogen::utility::streaming::jsonify;
        using namespace dogen::utility::log;
        logger lg(logger_factory("hash_tester"));
        BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
        BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);
        BOOST_CHECK(a != b);

        std::hash<entity_type> hasher;
        BOOST_LOG_SEV(lg, debug) << "hash a: " << hasher(a);
        BOOST_LOG_SEV(lg, debug) << "hash b: " << hasher(b);
        BOOST_CHECK(hasher(a) != hasher(b));
    }
};

} } }

#endif
