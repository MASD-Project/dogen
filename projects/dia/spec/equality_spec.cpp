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
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/dia/domain/dia_domain.hpp"
#include "dogen/dia/io/dia_io.hpp"
#include "dogen/dia/test_data/dia_test_data.hpp"

namespace {

const std::string test_module("dia");
const std::string test_suite("equality_spec");

template<typename Sequence>
void test_empty_attribute() {
    using namespace dogen::utility::log;
    logger lg(logger_factory(test_suite));

    Sequence sequence;
    std::vector<dogen::dia::attribute::attribute_value> v1, v2;
    v1.push_back(sequence());
    dogen::dia::attribute a("background", v1);
    dogen::dia::attribute b("background", v2);

    using dogen::utility::streaming::jsonify;
    BOOST_LOG_SEV(lg, debug) << "a: " << jsonify(a);
    BOOST_LOG_SEV(lg, debug) << "b: " << jsonify(b);

    BOOST_CHECK(a != b);
    BOOST_CHECK(b != a);
}

template<typename Sequence>
void test_equality() {
    Sequence sequence;
    const typename Sequence::value_type a(sequence());
    const typename Sequence::value_type b(a);
    const typename Sequence::value_type c(sequence());

    typedef dogen::utility::test::equality_tester
        <typename Sequence::value_type> equality_tester;
    equality_tester::an_object_is_equal_to_itself(a);
    equality_tester::identical_objects_are_equal(a, b);
    equality_tester::distinct_objects_are_unequal(a, c);
}

}

BOOST_AUTO_TEST_SUITE(equality)

BOOST_AUTO_TEST_CASE(equality_operator_behaves_correctly) {
    SETUP_TEST_LOG_SOURCE("equality_operator_behaves_correctly");
    using namespace dogen::dia::test_data;

    test_equality<string_sequence>();
    test_equality<rectangle_sequence>();
    test_equality<real_sequence>();
    test_equality<integer_sequence>();
    test_equality<color_sequence>();
    test_equality<font_sequence>();
    test_equality<point_sequence>();
    test_equality<boolean_sequence>();
    test_equality<simple_attribute_sequence>();
    test_equality<composite_attribute_sequence>();
    test_equality<simple_composite_sequence>();
    test_equality<composite_composite_sequence>();
    test_equality<child_node_sequence>();
    test_equality<object_sequence>();
    test_equality<layer_sequence>();
    test_equality<diagram_data_sequence>();
    test_equality<diagram_sequence>();
}

BOOST_AUTO_TEST_CASE(attributes_with_empty_values_are_only_equal_to_other_attributes_with_empty_values) {
    SETUP_TEST_LOG_SOURCE("attributes_with_empty_values_are_only_equal_to_other_attributes_with_empty_values");
    using namespace dogen::dia::test_data;

    test_empty_attribute<string_sequence>();
    test_empty_attribute<rectangle_sequence>();
    test_empty_attribute<real_sequence>();
    test_empty_attribute<integer_sequence>();
    test_empty_attribute<color_sequence>();
    test_empty_attribute<font_sequence>();
    test_empty_attribute<point_sequence>();
    test_empty_attribute<boolean_sequence>();

    // empty must be equal to itself
    std::vector<dogen::dia::attribute::attribute_value> v1;
    dogen::dia::attribute a("test", v1);
    dogen::dia::attribute b("test", v1);
    BOOST_CHECK(a == b);
    BOOST_CHECK(b == a);
}

BOOST_AUTO_TEST_CASE(objects_with_different_attributes_are_not_equal) {
    SETUP_TEST_LOG_SOURCE("objects_with_different_attributes_are_not_equal");
    dogen::dia::test_data::simple_attribute_sequence sequence;
    std::vector<dogen::dia::attribute> attributes;
    attributes.push_back(sequence());

    boost::optional<dogen::dia::child_node> child;
    dogen::dia::object a("UML - LargePackage", 0, "O0", attributes, child);

    attributes.push_back(sequence());
    dogen::dia::object b("UML - LargePackage", 0, "O0", attributes, child);

    BOOST_CHECK(a != b);
    BOOST_CHECK(b != a);
}

BOOST_AUTO_TEST_SUITE_END()
