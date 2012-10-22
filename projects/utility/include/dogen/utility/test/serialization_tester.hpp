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
#ifndef DOGEN_UTILITY_TEST_SERIALIZATION_TESTER_HPP
#define DOGEN_UTILITY_TEST_SERIALIZATION_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#include "dogen/utility/io/jsonify_io.hpp"
#include "dogen/utility/log/logger.hpp"

namespace dogen {
namespace utility {
namespace test {

/**
 * @brief Provides a series of canned tests for serialisation of
 * domain entities.
 *
 * Roundtrip tests
 *
 * An entity shall produce valid serialisation round-trips for
 * supported archive types.
 *
 * A valid serialisation round-trip is defined as follows: an
 * object a shall be equal to another object b, when b is
 * initialised by saving a to an archive and loading b from it.
 */
template<typename Entity>
class serialization_tester {
public:
    typedef Entity entity_type;

private:
    template<typename InputArchive, typename OutputArchive>
    static void roundtrip_produces_the_same_entity(const entity_type& a) {
        using dogen::utility::streaming::jsonify;
        using namespace dogen::utility::log;
        logger lg(logger_factory("serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "original: " << jsonify(a);
        std::ostringstream output_stream;
        {
            OutputArchive output_archive(output_stream);
            output_archive << BOOST_SERIALIZATION_NVP(a);
        }

        entity_type b = entity_type();
        BOOST_LOG_SEV(lg, debug) << "before load: " << jsonify(b);
        std::istringstream input_stream(output_stream.str());
        {
            InputArchive input_archive(input_stream);
            input_archive >> BOOST_SERIALIZATION_NVP(b);
        }
        BOOST_LOG_SEV(lg, debug) << "after load: " << jsonify(b);
        BOOST_CHECK(a == b);
    }

public:
    /**
     * @brief Test round-trip using an XML archive.
     */
    static void xml_roundtrip_produces_the_same_entity(const entity_type& a) {
        using namespace boost::archive;
        using namespace dogen::utility::log;
        logger lg(logger_factory("serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "XML serialization: ";
        roundtrip_produces_the_same_entity<xml_iarchive, xml_oarchive>(a);
    }

    /**
     * @brief Test round-trip using a text archive.
     */
    static void text_roundtrip_produces_the_same_entity(const entity_type& a) {
        using namespace boost::archive;
        using namespace dogen::utility::log;
        logger lg(logger_factory("serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "text serialization: ";
        roundtrip_produces_the_same_entity<text_iarchive, text_oarchive>(a);
    }

    /**
     * @brief Test round-trip using a binary archive.
     */
    static void binary_roundtrip_produces_the_same_entity(const entity_type& a) {
        using namespace boost::archive;
        using namespace dogen::utility::log;
        logger lg(logger_factory("serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "binary serialization: ";
        roundtrip_produces_the_same_entity<binary_iarchive, binary_oarchive>(a);
    }

    /**
     * @brief Test round-trip using a EOS portable archive.
     */
    static void eos_roundtrip_produces_the_same_entity(const entity_type& a) {
        using namespace dogen::utility::log;
        logger lg(logger_factory("serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "Portable binary serialization: ";
        roundtrip_produces_the_same_entity<eos::portable_iarchive,
                                           eos::portable_oarchive>(a);
    }

    /**
     * @brief Test that all supported archives round-trip correctly.
     */
    static void all_roundtrips_produce_the_same_entity(const entity_type& a) {
        xml_roundtrip_produces_the_same_entity(a);
        text_roundtrip_produces_the_same_entity(a);
        binary_roundtrip_produces_the_same_entity(a);
        eos_roundtrip_produces_the_same_entity(a);
    }

    /**
     * @deprecated Legacy method to be removed.
     */
    static void
    roundtrips_of_the_same_type_produce_the_same_entity(const Entity& a) {
        using namespace boost::archive;
        roundtrip_produces_the_same_entity<text_iarchive, text_oarchive>(a);
        roundtrip_produces_the_same_entity<binary_iarchive, binary_oarchive>(a);
        roundtrip_produces_the_same_entity<eos::portable_iarchive,
            eos::portable_oarchive>(a);
    }
};

} } }

#endif
