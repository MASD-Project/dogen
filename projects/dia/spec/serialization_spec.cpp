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
