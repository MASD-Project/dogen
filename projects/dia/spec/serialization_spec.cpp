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
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/serialization_tester.hpp"
#include "dogen/dia/domain/dia_domain.hpp"
#include "dogen/dia/io/dia_io.hpp"
#include "dogen/dia/serialization/dia_ser.hpp"
#include "dogen/dia/test_data/dia_test_data.hpp"

namespace {

const std::string test_module("dia");
const std::string test_suite("serialization_spec");

/**
 * @brief Performs a serialisation round-trip using a test object
 * read from Sequence.
 */

template<typename Sequence>
void rountrip_type() {
    Sequence sequence;
    dogen::utility::test::serialization_tester<
        typename Sequence::value_type>::
        all_roundtrips_produce_the_same_entity(sequence());
}

}

BOOST_AUTO_TEST_SUITE(serialization)

BOOST_AUTO_TEST_CASE(roundtrips_of_the_same_type_produce_the_same_entity) {
    SETUP_TEST_LOG_SOURCE("roundtrips_of_the_same_type_produce_the_same_entity");
    using namespace dogen::dia::test_data;

    rountrip_type<string_sequence>();
    rountrip_type<rectangle_sequence>();
    rountrip_type<real_sequence>();
    rountrip_type<integer_sequence>();
    rountrip_type<color_sequence>();
    rountrip_type<font_sequence>();
    rountrip_type<point_sequence>();
    rountrip_type<boolean_sequence>();
    rountrip_type<simple_attribute_sequence>();
    rountrip_type<composite_attribute_sequence>();
    rountrip_type<simple_composite_sequence>();
    rountrip_type<composite_composite_sequence>();
    rountrip_type<child_node_sequence>();
    rountrip_type<object_sequence>();
    rountrip_type<layer_sequence>();
    rountrip_type<diagram_data_sequence>();
    rountrip_type<diagram_sequence>();
}

BOOST_AUTO_TEST_SUITE_END()
