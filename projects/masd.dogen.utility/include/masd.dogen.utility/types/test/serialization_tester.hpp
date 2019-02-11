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
#ifndef MASD_DOGEN_UTILITY_TEST_SERIALIZATION_TESTER_HPP
#define MASD_DOGEN_UTILITY_TEST_SERIALIZATION_TESTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "masd.dogen.utility/types/io/jsonify_io.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"

template<typename Archive> void register_types(Archive& ar);

namespace masd::dogen::utility::test {

template<typename T>
void check(const T& a, const T& b) {
    BOOST_CHECK(a == b);
}

template<typename T>
void check(const boost::shared_ptr<T>& a, const boost::shared_ptr<T>& b) {
    BOOST_CHECK(*a == *b);
}

template<typename T>
void dump(dogen::utility::log::logger& lg, const T& a, const std::string& msg) {
    using dogen::utility::streaming::jsonify;
    using namespace masd::dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << msg << jsonify(a);
}

template<typename T>
void dump(dogen::utility::log::logger& lg, const boost::shared_ptr<T>& a,
    const std::string& msg) {

    if (!a) {
        using namespace masd::dogen::utility::log;
        BOOST_LOG_SEV(lg, debug) << msg << "<empty>";
        return;
    }
    dump(lg, *a, msg);
}

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
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.serialization_tester"));
        dump(lg, a, "original: ");
        std::ostringstream os;
        {
            OutputArchive oa(os);
            ::register_types<OutputArchive>(oa);
            oa << BOOST_SERIALIZATION_NVP(a);
        }

        entity_type b = entity_type();
        dump(lg, b, "before load: ");
        std::istringstream is(os.str());
        {
            InputArchive ia(is);
            ::register_types<InputArchive>(ia);
            ia >> BOOST_SERIALIZATION_NVP(b);
        }
        dump(lg, b, "after load: ");
        check(a, b);
        log_if_test_has_failed();
    }

public:
    /**
     * @brief Test round-trip using an XML archive.
     */
    static void xml_roundtrip_produces_the_same_entity(const entity_type& a) {
        using namespace boost::archive;
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "XML serialization: ";
        roundtrip_produces_the_same_entity<xml_iarchive, xml_oarchive>(a);
    }

    /**
     * @brief Test round-trip using a text archive.
     */
    static void text_roundtrip_produces_the_same_entity(const entity_type& a) {
        using namespace boost::archive;
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "text serialization: ";
        roundtrip_produces_the_same_entity<text_iarchive, text_oarchive>(a);
    }

    /**
     * @brief Test round-trip using a binary archive.
     */
    static void binary_roundtrip_produces_the_same_entity(const entity_type& a) {
        using namespace boost::archive;
        using namespace masd::dogen::utility::log;
        logger lg(logger_factory("utility.test.serialization_tester"));
        BOOST_LOG_SEV(lg, debug) << "binary serialization: ";
        roundtrip_produces_the_same_entity<binary_iarchive, binary_oarchive>(a);
    }

    /**
     * @brief Test that all supported archives round-trip correctly.
     */
    static void all_roundtrips_produce_the_same_entity(const entity_type& a) {
        xml_roundtrip_produces_the_same_entity(a);
        text_roundtrip_produces_the_same_entity(a);
        binary_roundtrip_produces_the_same_entity(a);
    }
};

}

#endif
