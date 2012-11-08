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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/hash_tester.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/domain/sml_domain.hpp"
#include "dogen/sml/io/sml_io.hpp"
#include "dogen/sml/test_data/qualified_name_sequence.hpp"
#include "dogen/sml/hash/qualified_name_hash.hpp"
#include "dogen/sml/domain/sml_domain.hpp"
#include "dogen/sml/io/sml_io.hpp"
#include "dogen/sml/serialization/sml_ser.hpp"
#include "dogen/sml/test_data/sml_test_data.hpp"

namespace {

const std::string test_module("hashing");
const std::string test_suite("sml_spec");
const std::string documentation("@brief sample doc");

template<typename Sequence>
void test_hashing() {
    dogen::utility::test::hash_tester<Sequence>::
        equal_objects_must_generate_the_same_hash();

    dogen::utility::test::hash_tester<Sequence>::
        unequal_objects_must_generate_different_hashes();
}

}

BOOST_AUTO_TEST_SUITE(hashing)

BOOST_AUTO_TEST_CASE(validate_qualified_name_hashing) {
    SETUP_TEST_LOG("validate_qualified_name_hashing");
    test_hashing<dogen::sml::test_data::qualified_name_sequence>();
}

BOOST_AUTO_TEST_SUITE_END()
