/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/test/unit_test.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/class_in_a_package/domain/all.hpp"
#include "dogen/class_in_a_package/io/all_io.hpp"
#include "dogen/class_in_a_package/serialization/all_ser.hpp"
#include "dogen/class_in_a_package/test_data/all_sequence.hpp"
#include "dogen/class_in_a_package/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("class_in_a_package");

}

using namespace dogen::class_in_a_package;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(class_in_a_package)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<package1::first_class_sequence>();
    test_equality<versioned_key_sequence>();
    test_equality<unversioned_key_sequence>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    rountrip_type<package1::first_class_sequence>();
    rountrip_type<versioned_key_sequence>();
    rountrip_type<unversioned_key_sequence>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<package1::first_class_sequence>();
    test_hashing<versioned_key_sequence>();
    test_hashing<unversioned_key_sequence>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_hashing");
    test_swap<package1::first_class_sequence>();
    test_swap<versioned_key_sequence>();
    test_swap<unversioned_key_sequence>();
}

BOOST_AUTO_TEST_SUITE_END()
