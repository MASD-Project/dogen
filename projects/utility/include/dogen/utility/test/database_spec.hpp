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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_ORG_SPEC_DATABASE_HPP
#define DOGEN_ORG_SPEC_DATABASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/test/unit_test.hpp>
#include <pqxx/connection.hxx>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test_data/generate_container.hpp"
#include "dogen/utility/io/vector_io.hpp"

#ifdef DOGEN_DATABASE_SUPPORT

namespace dogen {
namespace utility {
namespace test {

/**
 * @brief Requirements for code interfacing with the database.
 */
template<typename Entity, typename Sequence, typename DataExchanger>
class database {
private:
    typedef Entity entity_type;
    typedef Sequence sequence_type;
    typedef DataExchanger data_exchanger_type;
    typedef std::vector<entity_type> entities_type;

private:
    enum generation_mode { do_one, do_all };

    static entities_type
    generate_entities(const generation_mode mode = do_all) {
        const unsigned int exhaust_sequence(0);
        const unsigned int size(mode == do_one ? 1 : exhaust_sequence);

        using dogen::utility::test_data::generate_vector;
        entities_type e(generate_vector<sequence_type>(size));
        BOOST_CHECK((size == 1 && e.size() == 1) || (e.size() >= 2));
        return(e);
    }

    static std::string connection_string() {
        return("dbname=musseque user=build password=build");
    }

    static void next_revision_shall_be_equivalent(const entity_type& a,
        const entity_type& b) {
        using namespace dogen::utility::log;
        logger lg(logger_factory("database"));
        BOOST_LOG_SEV(lg, debug) << "a: " << a << " b: " << b;

        BOOST_CHECK_EQUAL(b.versioned_key().id(), a.versioned_key().id());
        BOOST_CHECK(b.is_equivalent(a));
        BOOST_CHECK(b.versioned_key().version() == a.versioned_key().version() + 1);
    }

    static void saving_shall_increment_revision(const generation_mode mode) {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type saved(generate_entities(mode));
        entities_type original(saved);
        exchanger.save(connection, saved);

        BOOST_CHECK_EQUAL(original.size(), saved.size());
        for (unsigned int i(0); i < original.size(); ++i) {
            next_revision_shall_be_equivalent(original[i], saved[i]);
        }
    }

public:
    static void saving_zero_entities_shall_do_nothing() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type e;
        exchanger.save(connection, e);
        BOOST_CHECK(e.empty());
    }

    static void saving_one_entity_shall_increment_revision() {
        saving_shall_increment_revision(do_one);
    }

    static void saving_n_entities_shall_increment_revision() {
        saving_shall_increment_revision(do_all);
    }

    static void saving_with_wrong_version_shall_fail() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type saved(generate_entities());
        entities_type copy(saved);
        exchanger.save(connection, saved);
        using namespace dogen::utility::log;
        logger lg(logger_factory("database"));
        BOOST_LOG_SEV(lg, debug) << "copy: " << copy;

        try {
            exchanger.save(connection, copy);
            BOOST_FAIL("Expected database exception to be thrown.");
        } catch(const std::exception& e) {
            BOOST_LOG_SEV(lg, debug) << "Exception thrown as expected: "
                                     << e.what();
            BOOST_CHECK(true);
        }
    }

    static void loading_by_existing_key_shall_load_one_entity() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type saved(generate_entities());
        exchanger.save(connection, saved);
        using namespace dogen::utility::log;
        logger lg(logger_factory("database"));
        BOOST_LOG_SEV(lg, debug) << "saved: " << saved;

        const entity_type a(saved[0]);
        entities_type loaded(exchanger.load(connection, a.versioned_key()));
        BOOST_LOG_SEV(lg, debug) << "loaded: " << loaded;
        BOOST_CHECK(!loaded.empty());
        BOOST_CHECK_EQUAL(loaded.size(), 1);

        const entity_type b(loaded[0]);
        BOOST_CHECK(a == b);
    }

    static void loading_by_non_existing_key_shall_load_zero_entities() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type original(generate_entities());
        typename entities_type::const_iterator i(original.begin());
        entities_type saved;
        saved.push_back(*i);
        exchanger.save(connection, saved);

        using namespace dogen::utility::log;
        logger lg(logger_factory("database"));
        BOOST_LOG_SEV(lg, debug) << "saved: " << saved;
        BOOST_CHECK_EQUAL(saved.size(), 1);

        ++i;
        entities_type loaded(exchanger.load(connection, (*i).versioned_key()));
        BOOST_LOG_SEV(lg, debug) << "loaded: " << loaded;
        BOOST_CHECK(loaded.empty());
    }

    static void loading_all_when_none_exist_shall_load_zero_entities() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type loaded(exchanger.load(connection));
        using namespace dogen::utility::log;
        logger lg(logger_factory("database"));
        BOOST_LOG_SEV(lg, debug) << "loaded: " << loaded;
        BOOST_CHECK(loaded.empty());
    }

    static void erasing_all_when_none_exist_shall_do_nothing() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        exchanger.erase(connection);
        BOOST_CHECK(true);
    }

    static void roundtrip_shall_produce_equal_entities() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type saved(generate_entities());
        exchanger.save(connection, saved);
        using namespace dogen::utility::log;
        logger lg(logger_factory("database"));
        BOOST_LOG_SEV(lg, debug) << "saved: " << saved;

        entities_type loaded(exchanger.load(connection));
        BOOST_LOG_SEV(lg, debug) << "loaded: " << loaded;

        BOOST_CHECK_EQUAL(saved.size(), loaded.size());
        BOOST_CHECK(saved == loaded);
    }

    static void loading_entity_by_key_shall_be_supported() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type saved(generate_entities());
        exchanger.save(connection, saved);
        using namespace dogen::utility::log;
        logger lg(logger_factory("database"));
        BOOST_LOG_SEV(lg, debug) << "saved: " << saved;

        entities_type loaded;
        loaded = exchanger.load(connection, saved[0].versioned_key());
        BOOST_LOG_SEV(lg, debug) << "loaded: " << loaded;

        BOOST_CHECK_EQUAL(loaded.size(), 1);
        BOOST_CHECK(saved[0] == loaded[0]);
    }

    static void erasing_entity_by_key_shall_be_supported() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type saved(generate_entities());
        exchanger.save(connection, saved);
        using namespace dogen::utility::log;
        logger lg(logger_factory("database"));
        BOOST_LOG_SEV(lg, debug) << "saved: " << saved;

        const auto vk(saved[0].versioned_key());
        exchanger.erase(connection, vk);
        BOOST_LOG_SEV(lg, debug) << "erased id: " << vk;

        entities_type loaded;
        loaded = exchanger.load(connection, vk);
        BOOST_LOG_SEV(lg, debug) << "loaded: " << loaded;
        BOOST_CHECK(loaded.empty());
    }

    static void erasing_all_entities_shall_be_supported() {
        pqxx::connection connection(connection_string());
        data_exchanger_type exchanger;
        exchanger.erase(connection);

        entities_type saved(generate_entities());
        exchanger.save(connection, saved);
        using namespace dogen::utility::log;
        logger lg(logger_factory("database"));
        BOOST_LOG_SEV(lg, debug) << "saved: " << saved;

        exchanger.erase(connection);

        entities_type loaded;
        loaded = exchanger.load(connection);
        BOOST_LOG_SEV(lg, debug) << "loaded: " << loaded;
        BOOST_CHECK(loaded.empty());
    }
};

} } }

#else

namespace dogen {
namespace utility {
namespace test {

template<typename Entity, typename Sequence, typename DataExchanger>
class database {
public:
    static void saving_zero_entities_shall_do_nothing() {}
    static void saving_one_entity_shall_increment_revision() {}
    static void saving_n_entities_shall_increment_revision() {}
    static void saving_with_wrong_version_shall_fail() {}
    static void loading_by_existing_key_shall_load_one_entity() {}
    static void loading_by_non_existing_key_shall_load_zero_entities() {}
    static void loading_all_when_none_exist_shall_load_zero_entities() {}
    static void erasing_all_when_none_exist_shall_do_nothing() {}
    static void roundtrip_shall_produce_equal_entities() {}
    static void loading_entity_by_key_shall_be_supported() {}
    static void erasing_entity_by_key_shall_be_supported() {}
    static void erasing_all_entities_shall_be_supported() {}
};

} } }

#endif

#endif
