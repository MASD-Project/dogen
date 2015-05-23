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
#ifndef DOGEN_UTILITY_TEST_EOS_SERIALIZATION_TESTER_HPP
#define DOGEN_UTILITY_TEST_EOS_SERIALIZATION_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include <boost/test/unit_test.hpp>
#define NO_EXPLICIT_TEMPLATE_INSTANTIATION
#include <eos/portable_iarchive.hpp>
#include <eos/portable_oarchive.hpp>
#include "dogen/utility/io/jsonify_io.hpp"
#include "dogen/utility/log/logger.hpp"

template<typename Archive> void register_types(Archive& ar);

namespace dogen {
namespace utility {
namespace test {

/**
 * @brief Provides canned tests for serialisation of domain entities
 * using EOS.
 *
 * Follows the same logic as the generic boost serialisation tests.
 *
 */
template<typename Entity>
class eos_serialization_tester {
public:
    typedef Entity entity_type;

public:
    template<typename InputArchive, typename OutputArchive>
    static void roundtrip_produces_the_same_entity(const entity_type& a) {
        using dogen::utility::streaming::jsonify;
        using namespace dogen::utility::log;
        logger lg(logger_factory("utility.test.serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "original: " << jsonify(a);
        std::ostringstream os;
        {
            OutputArchive oa(os);
            register_types<OutputArchive>(oa);
            oa << a;
        }

        entity_type b = entity_type();
        BOOST_LOG_SEV(lg, debug) << "before load: " << jsonify(b);
        std::istringstream is(os.str());
        {
            InputArchive ia(is);
            register_types<InputArchive>(ia);
            ia >> b;
        }
        BOOST_LOG_SEV(lg, debug) << "after load: " << jsonify(b);
        BOOST_CHECK(a == b);
        log_if_test_has_failed();
    }

public:
    /**
     * @brief Test round-trip using a EOS portable archive.
     */
    static void eos_roundtrip_produces_the_same_entity(const entity_type& a) {

        using namespace dogen::utility::log;
        logger lg(logger_factory("utility.test.serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "Portable binary serialization: ";

        roundtrip_produces_the_same_entity<eos::portable_iarchive,
                                           eos::portable_oarchive>(a);
    }

    /**
     * @brief Test that all supported archives round-trip correctly.
     */
    static void all_roundtrips_produce_the_same_entity(const entity_type& a) {
        eos_roundtrip_produces_the_same_entity(a);
    }
};

} } }

#endif
