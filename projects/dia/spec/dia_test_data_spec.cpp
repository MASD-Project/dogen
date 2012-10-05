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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
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
#include "dogen/dia/test_data/dia_test_data.hpp"
#include "dogen/utility/test/sequence_tester.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/dia/io/dia_io.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("dia_test_data_spec");

}

BOOST_AUTO_TEST_SUITE(dia_test_data)

BOOST_AUTO_TEST_CASE(sequences_have_the_expected_lengths) {
    SETUP_TEST_LOG_SOURCE("sequences_have_the_expected_lengths");
    using dogen::utility::test::sequence_tester;
    using namespace dogen::dia::test_data;

    sequence_tester<string_sequence>::validate_sequence_length();
    sequence_tester<rectangle_sequence>::validate_sequence_length();
    sequence_tester<real_sequence>::validate_sequence_length();
    sequence_tester<integer_sequence>::validate_sequence_length();
    sequence_tester<color_sequence>::validate_sequence_length();
    sequence_tester<font_sequence>::validate_sequence_length();
    sequence_tester<point_sequence>::validate_sequence_length();
    sequence_tester<boolean_sequence>::validate_sequence_length();
    sequence_tester<simple_attribute_sequence>::validate_sequence_length();
    sequence_tester<composite_attribute_sequence>::validate_sequence_length();
    sequence_tester<simple_composite_sequence>::validate_sequence_length();
    sequence_tester<composite_composite_sequence>::validate_sequence_length();
    sequence_tester<child_node_sequence>::validate_sequence_length();
    sequence_tester<object_sequence>::validate_sequence_length();
    sequence_tester<layer_sequence>::validate_sequence_length();
    sequence_tester<diagram_data_sequence>::validate_sequence_length();
    sequence_tester<diagram_sequence>::validate_sequence_length();
}

BOOST_AUTO_TEST_SUITE_END()
