/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <utility>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/prototype/domain/repository.hpp"
#include "dogen/prototype/serialization/repository_ser.hpp"
#include "dogen/utility/test/serialization_tester.hpp"
#include "dogen/prototype/test_data/repository_factory.hpp"
#include "dogen/prototype/test_data/currency_td.hpp"
#include "dogen/utility/io/jsonify_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/prototype/io/repository_io.hpp"
#include "dogen/prototype/io/versioned_key_io.hpp"
#include "dogen/prototype/io/unversioned_key_io.hpp"
#include "dogen/prototype/io/currency_io.hpp"

namespace {

const std::string test_module("org");
const std::string test_suite("repository_spec");

typedef std::vector<dogen::prototype::currency> currencies_type;

bool check_currencies(const currencies_type& expectation,
    const dogen::prototype::repository& repository) {
    using namespace dogen::utility::log;
    logger lg(logger_factory("database"));
    using dogen::prototype::currency;
    for (const auto e: expectation) {
        const auto vk(e.versioned_key());
        using dogen::prototype::unversioned_key;
        const auto c(repository.get_currency(static_cast<unversioned_key>(vk)));

        if (!c) {
            BOOST_LOG_SEV(lg, debug) << "Could not find currency. ID: '"
                                     << vk << "'";
            return false;
        }

        if (e != *c) {
            BOOST_LOG_SEV(lg, debug)
                << "Currency has unexpected state. Expected: "
                << e << " but got: " << *c;

            return false;
        }
    }
    return true;
}

}

BOOST_AUTO_TEST_SUITE(repository)

BOOST_AUTO_TEST_CASE(roundtrips_of_the_same_type_produce_the_same_entity) {
    SETUP_TEST_LOG("roundtrips_of_the_same_type_produce_the_same_entity");
    dogen::prototype::repository
        a(dogen::prototype::repository_factory::create_majors());
    dogen::utility::test::serialization_tester<dogen::prototype::repository>::
        roundtrips_of_the_same_type_produce_the_same_entity(a);
}

BOOST_AUTO_TEST_CASE(test_update_currencies) {
    SETUP_TEST_LOG_SOURCE("test_update_currencies");
    // test 1: all added currencies must be in the object graph.
    using dogen::prototype::currency;
    dogen::prototype::majors_currency_sequence majors_sequence;
    currencies_type update;
    update.reserve(majors_sequence.length());
    std::generate_n(std::back_inserter(update),
                    majors_sequence.length(),
                    majors_sequence);
    BOOST_LOG_SEV(lg, debug) << "Generated " << update.size() << " majors.";

    dogen::prototype::repository repository;
    repository.update_currencies(update);

    using dogen::utility::streaming::jsonify;
    BOOST_LOG_SEV(lg, debug) << "Repository after update: "
                             << jsonify(repository);

    currencies_type expectation(update);
    BOOST_CHECK(check_currencies(expectation, repository));

    // test 2: currencies which are not in the object graph must not be found
    const dogen::prototype::unversioned_key nonexistent_uk(1000);
    boost::optional<currency> ccy(repository.get_currency(nonexistent_uk));
    BOOST_CHECK(!ccy);

    // test 3: updating existing currencies must result in having all
    // the previous currencies, plus the updated ones.
    const unsigned int change_how_many(2);
    BOOST_CHECK(majors_sequence.length() > change_how_many);

    update.resize(change_how_many);
    for (unsigned int i(0); i < change_how_many; ++i) {
        currency tmp(update[i]);
        tmp.name("second_update");
        update[i] = tmp;
        expectation[i] = tmp;
    }

    repository.update_currencies(update);
    BOOST_CHECK(check_currencies(expectation, repository));
    BOOST_LOG_SEV(lg, debug) << "Repository after update: "
                             << jsonify(repository);

    // test 4: adding new currencies must result in having all
    // previous ones plus the new currencies.
    const unsigned int add_how_many(5);
    update.clear();
    update.reserve(add_how_many);

    dogen::prototype::unrealistic_currency_sequence
        unrealistic_sequence;
    std::generate_n(std::back_inserter(update),
                    add_how_many,
                    unrealistic_sequence);
    std::copy(update.begin(), update.end(), std::back_inserter(expectation));
    BOOST_LOG_SEV(lg, debug) << "Generated " << update.size() << " randoms.";

    repository.update_currencies(update);
    BOOST_CHECK(check_currencies(expectation, repository));
    BOOST_LOG_SEV(lg, debug) << "Repository after update: "
                             << jsonify(repository);
}

BOOST_AUTO_TEST_SUITE_END()
