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
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/stand_alone_class/domain/all.hpp"
#include "dogen/stand_alone_class/io/all_io.hpp"
#include "dogen/stand_alone_class/serialization/all_ser.hpp"
#include "dogen/stand_alone_class/serialization/registrar_ser.hpp"
#include "dogen/stand_alone_class/test_data/all_td.hpp"
#include "dogen/stand_alone_class/hash/all_hash.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::stand_alone_class::register_types<Archive>(ar);
}

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("stand_alone_class");

}

using namespace dogen::stand_alone_class;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(stand_alone_class)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<class_1_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    rountrip_type<class_1_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<class_1_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_hashing");
    test_swap<class_1_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<class_1_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
