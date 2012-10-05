/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/sequence_tester.hpp"
#include "dogen/config/version.hpp"
#include "dogen/prototype/domain/currency.hpp"
#include "dogen/prototype/test_data/currency_td.hpp"
#include "dogen/prototype/test_data/repository_factory.hpp"
#include "dogen/utility/io/jsonify_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/prototype/io/currency_io.hpp"
#include "dogen/prototype/io/versioned_key_io.hpp"
#include "dogen/prototype/io/unversioned_key_io.hpp"
#include "dogen/prototype/io/repository_io.hpp"

namespace  {

const std::string test_module("org");
const std::string test_suite("org_test_data_spec");

}

BOOST_AUTO_TEST_SUITE(org_test_data)

BOOST_AUTO_TEST_CASE(exercise_currency_sequences) {
    SETUP_TEST_LOG("exercise_currency_sequences");
    using dogen::utility::test::sequence_tester;

    sequence_tester<dogen::prototype::complete_currency_sequence>::
        validate_sequence_length();

    sequence_tester<dogen::prototype::majors_currency_sequence>::
        validate_sequence_length();

    sequence_tester<dogen::prototype::unrealistic_currency_sequence>::
        validate_sequence_length();
}

BOOST_AUTO_TEST_CASE(exercise_repository_factory) {
    SETUP_TEST_LOG_SOURCE("exercise_repository_factory");
    const dogen::prototype::repository repository(
        dogen::prototype::repository_factory::create_majors());
    BOOST_LOG_SEV(lg, debug) << "repository:" << repository;
    BOOST_CHECK(true); // eye balling required
}

BOOST_AUTO_TEST_SUITE_END()
