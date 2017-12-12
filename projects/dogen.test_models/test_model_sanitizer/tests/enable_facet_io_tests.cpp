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
#include <boost/test/unit_test.hpp>
#include "dogen.utility/io/vector_io.hpp"
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/test/canned_tests.hpp"
#include "dogen/test_models/enable_facet_io/types/all.hpp"
#include "dogen/test_models/enable_facet_io/io/all_io.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("enable_facet_io");

class first_class_generator {
public:
    typedef dogen::test_models::enable_facet_io::package1::first_class result_type;

public:
    result_type operator()() {
        result_type r;
        r.public_attribute(15 + pos_++);
        return r;
    }

private:
    unsigned int pos_ = 0;
};

}

using namespace dogen::test_models::enable_facet_io;
using namespace dogen::test_models::enable_facet_io::package1;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(enable_facet_io_tests)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<first_class_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_swap");
    test_swap<first_class_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<first_class_generator>();
}

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");
    test_move_assignment_copy<first_class_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
