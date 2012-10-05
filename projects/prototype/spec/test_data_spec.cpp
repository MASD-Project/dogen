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

const std::string test_module("prototype");
const std::string test_suite("test_data_spec");

}

BOOST_AUTO_TEST_SUITE(test_data)

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
