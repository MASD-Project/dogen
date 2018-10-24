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
#include <vector>
#include <functional>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "masd.dogen.utility/test/logging.hpp"
#include "masd.dogen.utility/test/macros.hpp"
#include "masd.dogen.utility/test_data/test_data.hpp"
#include "masd.dogen.utility/test_data/xml_reader.hpp"
#include "masd.dogen.utility/xml/exception.hpp"
#include "masd.dogen.utility/exception/invalid_enum_value.hpp"
#include "masd.dogen.utility/xml/text_reader.hpp"
#include "masd.dogen.utility/xml/text_reader_io.hpp"
#include "masd.dogen.utility/xml/node_types.hpp"
#include "masd.dogen.utility/xml/node_types_io.hpp"

using namespace masd::dogen::utility::log;
using masd::dogen::utility::xml::exception;
using masd::dogen::utility::xml::node_types;
using masd::dogen::utility::xml::text_reader;
using masd::dogen::utility::test_data::xml_reader;

namespace {

const std::string test_module("utility");
const std::string test_suite("xml_tests");

/*
 * labels used in tests
 */
const std::string label_root_name("root-name");
const std::string label_simple_node("node");
const std::string label_no_attributes("no-attributes");
const std::string label_one_attribute("one-attribute");
const std::string label_two_attribute("two-attribute");
const std::string label_three_attribute("three-attribute");
const std::string label_four_attribute("four-attribute");
const std::string label_non_existent_attribute("non-existent-attribute");
const std::string label_level_1_parameter_2("level-1-parameter-2");
const std::string label_level_2_parameter_2("level-2-parameter-2");
const std::string label_first_attribute_0("first-attribute0");
const std::string label_first_attribute_1("first-attribute1");
const std::string label_first_attribute_2("first-attribute2");
const std::string label_first_attribute_3("first-attribute3");
const std::string label_second_attribute_1("second-attribute1");
const std::string label_second_attribute_2("second-attribute2");
const std::string label_second_attribute_3("second-attribute3");
const std::string label_third_attribute_2("third-attribute2");
const std::string label_third_attribute_3("third-attribute3");
const std::string label_some_value_1("some value 1");
const std::string label_some_value_2("some value 2");
const std::string label_some_value_3("some value 3");
const std::string label_text("#text");
const std::string label_text_info("text info goes here");
const std::string label_text_info_nl("\ntext info goes here\n");

/*
 *Error messages
 */
const std::string message_error_convert_int("Error converting int value");
const std::string message_error_convert_long("Error converting long value");
const std::string message_error_convert_double("Error converting double value");
const std::string message_error_convert_boolean(
    "Error converting boolean value");
const std::string message_error_read_node("Error reading node");
const std::string message_error_get_attribute(
    "Error getting attribute: 'non-existent-attribute'");
const std::string message_error_unsupported_type(
    "Value not specialised for this type");
const std::string message_error_file_not_found("File does not exist: ");
const std::string message_error_file_not_regular(
    "File is not a regular file: ");

/**
 * @brief Performs n-consecutive reads. Each read must return true.
 */
void read_n_times(text_reader& reader, int n) {
    logger lg(logger_factory(test_suite));
    for (int i = 0; i < n; ++i)
        BOOST_CHECK(reader.read());
    BOOST_LOG_SEV(lg, debug) << reader;
}

bool check_xml_exception(const exception& exception,
    std::string expected_message) {
    return boost::starts_with(exception.what(), expected_message);
}

/**
 * @brief Creates a reader with an invalid file name and checks the
 * exception thrown.
 */
void check_invalid_filename(
    boost::filesystem::path path, std::string message) {

    using namespace std::placeholders;
    BOOST_CHECK_EXCEPTION(text_reader reader(path), exception,
        std::bind(check_xml_exception, _1, message)
        );
}

/**
 * @brief Performs a read on an invalid file and checks the exception
 * thrown.
 *
 * FIXME: commented out since the only test using it is ignored at
 * present.
 */
/*void check_invalid_content(text_reader& reader, std::string message) {

    using namespace std::placeholders;
    BOOST_CHECK_EXCEPTION(reader.read(), exception,
        std::bind(check_xml_exception, _1, message));
}*/

/**
 * @brief Checks the state of the reader before reading the first
 * element.
 */
void check_before_first_element(text_reader& reader) {
    BOOST_CHECK(reader.node_type() == node_types::none);
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << reader;
}

/**
 * @brief Reads the current element and checks the state of the reader
 * after the read.
 */
void check_element(text_reader& reader, node_types node_type,
    std::string name = std::string()) {

    BOOST_CHECK(reader.read());
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << reader;

    BOOST_CHECK(reader.name() == name);
    BOOST_CHECK(reader.node_type() == node_type);
}

/**
 * @brief Checks the state of the reader after reading past the last
 * element.
 */
void check_after_last_element(masd::dogen::utility::xml::text_reader& reader) {
    BOOST_CHECK(!reader.read());

    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << reader;
    BOOST_CHECK(reader.node_type() == node_types::none);
}

}

BOOST_AUTO_TEST_SUITE(xml_tests)

BOOST_AUTO_TEST_CASE(text_reader_throws_if_file_does_not_exist) {
    SETUP_TEST_LOG("text_reader_throws_if_file_does_not_exist");
    boost::filesystem::path path(xml_reader::non_existent_file());
    check_invalid_filename(path, message_error_file_not_found);
}

BOOST_AUTO_TEST_CASE(text_reader_throws_if_file_name_is_a_directory) {
    SETUP_TEST_LOG("text_reader_throws_if_file_name_is_a_directory");
    const boost::filesystem::path path(xml_reader::data_set());
    check_invalid_filename(path, message_error_file_not_regular);
}

// FIXME: test ignored because it outputs a libxml error to the
// console, which is quite distracting - it appears its a build
// error.
// BOOST_IGNORE_AUTO_TEST_CASE(text_reader_throws_if_file_is_empty) {
//     SETUP_TEST_LOG("text_reader_throws_if_file_is_empty");
//     text_reader reader(xml_reader::input_empty_file());
//     check_invalid_content(reader, message_error_read_node);
// }

BOOST_AUTO_TEST_CASE(text_reader_parses_file_one_node_inlined) {
    SETUP_TEST_LOG("text_reader_parses_file_one_node_inlined");
    text_reader reader(xml_reader::input_one_node_inlined());
    check_before_first_element(reader);
    check_element(reader, node_types::element, label_simple_node);
    check_element(reader, node_types::end_element, label_simple_node);
    check_after_last_element(reader);
}

BOOST_AUTO_TEST_CASE(text_reader_parses_file_one_node_indented) {
    SETUP_TEST_LOG("text_reader_parses_file_one_node_indented");
    text_reader reader(xml_reader::input_one_node_indented());

    check_before_first_element(reader);
    check_element(reader, node_types::element, label_simple_node);
    check_element(reader, node_types::significant_whitespace, label_text);
    check_element(reader, node_types::end_element, label_simple_node);
    check_after_last_element(reader);
}

BOOST_AUTO_TEST_CASE(text_reader_parses_file_one_node_self_closing) {
    SETUP_TEST_LOG("text_reader_parses_file_one_node_self_closing");
    text_reader reader(xml_reader::input_one_node_self_closing());

    check_before_first_element(reader);
    check_element(reader, node_types::element, label_simple_node);

    BOOST_CHECK(reader.is_empty());
    check_after_last_element(reader);
}

BOOST_AUTO_TEST_CASE(nodes_that_are_not_self_closing_are_not_empty) {
    SETUP_TEST_LOG("nodes_that_are_not_self_closing_are_not_empty");
    text_reader reader(xml_reader::input_one_node_indented());

    check_before_first_element(reader);
    check_element(reader, node_types::element, label_simple_node);
    BOOST_CHECK(!reader.is_empty());

    check_element(reader, node_types::significant_whitespace, label_text);
    BOOST_CHECK(!reader.is_empty());

    check_element(reader, node_types::end_element, label_simple_node);
    BOOST_CHECK(!reader.is_empty());

    check_after_last_element(reader);
}

BOOST_AUTO_TEST_CASE(text_reader_parses_file_xml_declaration_one_node_indented) {
    SETUP_TEST_LOG("text_reader_parses_file_xml_declaration_one_node_indented");
    text_reader reader(xml_reader::input_xml_declaration_one_node_indented());

    check_before_first_element(reader);
    check_element(reader, node_types::element, label_simple_node);
    check_element(reader, node_types::significant_whitespace, label_text);
    check_element(reader, node_types::end_element, label_simple_node);
    check_after_last_element(reader);
}

BOOST_AUTO_TEST_CASE(text_reader_reads_indented_string_value_correctly) {
    SETUP_TEST_LOG_SOURCE("text_reader_reads_indented_string_value_correctly");
    text_reader reader(xml_reader::input_string_value_indented());

    BOOST_CHECK(reader.read());
    BOOST_LOG_SEV(lg, debug) << reader;

    BOOST_CHECK(reader.read());
    BOOST_LOG_SEV(lg, debug) << reader;

    const std::string expected(label_text_info_nl);
    const std::string actual(reader.value_as_string());
    BOOST_CHECK(expected == actual);
}

BOOST_AUTO_TEST_CASE(text_reader_reads_inlined_string_value_correctly) {
    SETUP_TEST_LOG_SOURCE("text_reader_reads_inlined_string_value_correctly");
    text_reader reader(xml_reader::input_string_value_inlined());

    BOOST_CHECK(reader.read());
    BOOST_LOG_SEV(lg, debug) << reader;

    BOOST_CHECK(reader.read());
    BOOST_LOG_SEV(lg, debug) << reader;

    const std::string expected(label_text_info);
    const std::string actual(reader.value_as_string());
    BOOST_CHECK(expected == actual);
}

BOOST_AUTO_TEST_CASE(text_reader_identifies_nodes_with_values_correctly) {
    SETUP_TEST_LOG_SOURCE("text_reader_identifies_nodes_with_values_correctly");
    text_reader reader(xml_reader::input_string_value_indented());

    auto check_value([&](bool expects_value) {
            BOOST_CHECK(reader.read());
            BOOST_LOG_SEV(lg, debug) << reader;
            BOOST_CHECK(!(expects_value != reader.has_value()));
            BOOST_CHECK(!(expects_value != !reader.value_as_string().empty()));
        });

    check_value(false);
    check_value(true);
    check_value(false);
}

BOOST_AUTO_TEST_CASE(text_reader_reads_boolean_values_correctly) {
    SETUP_TEST_LOG_SOURCE("text_reader_reads_boolean_values_correctly");
    text_reader reader(xml_reader::input_boolean_values());

    read_n_times(reader, 4);
    BOOST_CHECK(reader.value_as_boolean());

    read_n_times(reader, 4);
    BOOST_CHECK(!reader.value_as_boolean());

    read_n_times(reader, 4);
    using namespace std::placeholders;
    BOOST_CHECK_EXCEPTION(
        reader.value_as_boolean(),
        exception,
        std::bind(check_xml_exception, _1, message_error_convert_boolean));

    read_n_times(reader, 4);
    BOOST_LOG_SEV(lg, debug) << reader;
    BOOST_CHECK_EXCEPTION(
        reader.value_as_boolean(),
        exception,
        std::bind(check_xml_exception, _1, message_error_convert_boolean));
}

BOOST_AUTO_TEST_CASE(text_reader_reads_double_values_correctly) {
    SETUP_TEST_LOG("text_reader_reads_double_values_correctly");
    text_reader reader(xml_reader::input_double_values());

    auto check_value([&](double expected) {
            read_n_times(reader, 4);
            BOOST_CHECK_CLOSE(reader.value_as_double(), expected, 0.000001);
        });

    check_value(3.14159);
    check_value(-12345.6789);
    check_value(3.0);
    check_value(-12345);

    read_n_times(reader, 4);
    using namespace std::placeholders;
    BOOST_CHECK_EXCEPTION(
        reader.value_as_double(), // this is a string
        exception,
        std::bind(check_xml_exception, _1, message_error_convert_double));
}

BOOST_AUTO_TEST_CASE(text_reader_reads_int_values_correctly) {
    SETUP_TEST_LOG("text_reader_reads_int_values_correctly");
    text_reader reader(xml_reader::input_int_values());

    auto check_value([&](int expected) {
            read_n_times(reader, 4);
            BOOST_CHECK(reader.value_as_int() == expected);
        });

    check_value(3);
    check_value(-12345);

    auto check_errors([&]() {
            read_n_times(reader, 4);
            using namespace std::placeholders;
            BOOST_CHECK_EXCEPTION(
                reader.value_as_int(),
                exception,
                std::bind(check_xml_exception, _1, message_error_convert_int)
                );
        });

    check_errors(); // 3.14159
    check_errors(); // -12345.6789
    check_errors(); // 9223372036854775808
    check_errors(); // this is a string
}

BOOST_AUTO_TEST_CASE(text_reader_reads_long_values_correctly) {
    SETUP_TEST_LOG("text_reader_reads_long_values_correctly");
    text_reader reader(xml_reader::input_long_values());

    auto check_value([&](long expected) {
            read_n_times(reader, 4);
            BOOST_CHECK(reader.value_as_int() == expected);
        });

    check_value(3);
    check_value(-12345);

    auto check_errors([&]() {
            read_n_times(reader, 4);
            using namespace std::placeholders;
            BOOST_CHECK_EXCEPTION(
                reader.value_as_long(),
                exception,
                std::bind(check_xml_exception, _1, message_error_convert_long)
                );
        });

    check_errors(); // 3.14159
    check_errors(); // -12345.6789
    check_errors(); // 9223372036854775808
    check_errors(); // this is a string
}

BOOST_AUTO_TEST_CASE(text_reader_cannot_be_copied) {
    SETUP_TEST_LOG("text_reader_cannot_be_copied");

    // to run these test cases un-comment each scenario and verify
    // that the code does not compile as expected.
    text_reader reader1(xml_reader::input_one_node_indented());

#ifdef DOGEN_COMPILE_BROKEN_CODE
    // text reader is non-copyable
    text_reader reader2(reader1);

    // text reader is not default-constructible
    text_reader reader3;

    // text reader is not assignable
    text_reader reader4 = reader1;
#endif

    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_attribute_returns_true_for_existent_attributes) {
    SETUP_TEST_LOG("has_attribute_returns_true_for_existent_attributes");
    text_reader reader(xml_reader::input_node_with_attributes());

    read_n_times(reader, 3);
    BOOST_CHECK(reader.has_attribute(label_first_attribute_0));
}

BOOST_AUTO_TEST_CASE(has_attribute_returns_false_for_non_existent_attributes) {
    SETUP_TEST_LOG("has_attribute_returns_false_for_non_existent_attributes");
    text_reader reader(xml_reader::input_node_with_attributes());

    read_n_times(reader, 3);
    BOOST_CHECK(reader.has_attribute(label_first_attribute_0)); // control
    BOOST_CHECK(!reader.has_attribute(label_non_existent_attribute));
}

BOOST_AUTO_TEST_CASE(getting_existent_attributes_returns_expected_values) {
    SETUP_TEST_LOG_SOURCE("getting_existent_attributes_returns_expected_values");
    text_reader reader(xml_reader::input_node_with_attributes());

    auto check_string_attribute([&](std::string name, std::string expected) {
            const std::string actual(reader.get_attribute_as_string(name));
            BOOST_LOG_SEV(lg, debug) << "expected: " << expected
                                     << " actual: " << actual;
            BOOST_CHECK(expected == actual);

            const std::string actual_template(
                reader.get_attribute<std::string>(name));
            BOOST_CHECK(expected == actual_template);
        }
        );

    read_n_times(reader, 3);
    check_string_attribute(label_first_attribute_0, label_some_value_1);

    read_n_times(reader, 4);
    check_string_attribute(label_first_attribute_1, label_some_value_2);
    check_string_attribute(label_second_attribute_1, label_some_value_3);

    auto check_bool_attribute([&](std::string name, bool expected) {
            const bool actual(reader.get_attribute_as_boolean(name));
            BOOST_LOG_SEV(lg, debug) << "expected: " << expected
                                     << " actual: " << actual;
            BOOST_CHECK(expected == actual);

            const bool actual_template(reader.get_attribute<bool>(name));
            BOOST_CHECK(expected == actual_template);
        });

    // tests for bool attributes
    read_n_times(reader, 4);
    check_bool_attribute(label_first_attribute_2, true);
    check_bool_attribute(label_second_attribute_2, false);

    using namespace std::placeholders;
    BOOST_CHECK_EXCEPTION(
        reader.get_attribute_as_boolean(label_third_attribute_2),
        exception,
        std::bind(check_xml_exception, _1, message_error_convert_boolean));

    BOOST_CHECK_EXCEPTION(
        reader.get_attribute<bool>(label_third_attribute_2),
        exception,
        std::bind(check_xml_exception, _1, message_error_convert_boolean));

    BOOST_CHECK_EXCEPTION(
        reader.get_attribute<std::vector<std::string>>(label_third_attribute_2),
        exception,
        std::bind(check_xml_exception, _1, message_error_unsupported_type));

    // tests for int attributes
    auto check_int_attribute([&](std::string name, int expected) {
            const int actual(reader.get_attribute_as_int(name));
            BOOST_LOG_SEV(lg, debug) << "expected: " << expected
                                     << " actual: " << actual;
            BOOST_CHECK(expected == actual);

            const int actual_template(reader.get_attribute<int>(name));
            BOOST_CHECK(expected == actual_template);
        });

    read_n_times(reader, 4);
    check_int_attribute(label_first_attribute_3, 13);
    check_int_attribute(label_second_attribute_3, -15);

    using namespace std::placeholders;
    BOOST_CHECK_EXCEPTION(
        reader.get_attribute_as_int(label_third_attribute_3),
        exception,
        std::bind(check_xml_exception, _1, message_error_convert_int));

    BOOST_CHECK_EXCEPTION(
        reader.get_attribute<int>(label_third_attribute_3),
        exception,
        std::bind(check_xml_exception, _1, message_error_convert_int));

    BOOST_CHECK_EXCEPTION(
        reader.get_attribute<std::vector<std::string>>(label_third_attribute_3),
        exception,
        std::bind(check_xml_exception, _1, message_error_unsupported_type));
}

BOOST_AUTO_TEST_CASE(getting_non_existent_attributes_throws) {
    SETUP_TEST_LOG("getting_non_existent_attributes_throws");
    text_reader reader(xml_reader::input_one_node_indented());

    read_n_times(reader, 3);

    using namespace std::placeholders;
    BOOST_CHECK_EXCEPTION(
        reader.get_attribute_as_string(label_non_existent_attribute),
        exception,
        std::bind(check_xml_exception, _1, message_error_get_attribute));
}

BOOST_AUTO_TEST_CASE(closing_an_open_text_reader_does_not_throw) {
    SETUP_TEST_LOG_SOURCE("closing_an_open_text_reader_does_not_throw");
    text_reader reader(xml_reader::input_one_node_indented());

    read_n_times(reader, 2);
    reader.close();
    BOOST_LOG_SEV(lg, debug) << reader;
}

BOOST_AUTO_TEST_CASE(closing_a_closed_text_reader_does_not_throw) {
    SETUP_TEST_LOG("closing_a_closed_text_reader_does_not_throw");
    text_reader reader(xml_reader::input_one_node_indented());

    read_n_times(reader, 2);
    reader.close();
    reader.close();
}

BOOST_AUTO_TEST_CASE(reading_from_a_closed_text_reader_throws) {
    SETUP_TEST_LOG("reading_from_a_closed_text_reader_throws");
    text_reader reader(xml_reader::input_one_node_indented());
    reader.close();

    using namespace std::placeholders;
    BOOST_CHECK_EXCEPTION(
        reader.read(),
        exception,
        std::bind(check_xml_exception, _1, message_error_read_node));
}

BOOST_AUTO_TEST_CASE(skipping_root_node_does_not_throw) {
    SETUP_TEST_LOG("skipping_root_node_does_not_throw");
    text_reader reader(xml_reader::input_three_nested_elements());

    BOOST_CHECK(reader.read());
    BOOST_CHECK(!reader.skip());
    BOOST_CHECK(!reader.has_value());
}

BOOST_AUTO_TEST_CASE(skipping_node_goes_to_next_same_level_node) {
    SETUP_TEST_LOG("skipping_node_goes_to_next_same_level_node");
    text_reader reader(xml_reader::input_three_nested_elements());

    read_n_times(reader, 3);
    BOOST_CHECK(reader.skip());
    read_n_times(reader, 1); // ignore the whitespace
    BOOST_CHECK(reader.name() == label_level_1_parameter_2);

    read_n_times(reader, 2);
    BOOST_CHECK(reader.skip());
    read_n_times(reader, 1); // ignore the whitespace
    BOOST_CHECK(reader.name() == label_level_2_parameter_2);
}

BOOST_AUTO_TEST_CASE(value_template_methods_are_equivalent_to_as_methods) {
    SETUP_TEST_LOG_SOURCE("value_template_methods_are_equivalent_to_as_methods");
    text_reader reader(xml_reader::input_values_of_all_types());

    read_n_times(reader, 4);
    const bool lhs_bool(reader.value_as_boolean());
    const bool rhs_bool(reader.value<bool>());
    BOOST_LOG_SEV(lg, debug) << "lhs: " << lhs_bool << " rhs: " << rhs_bool;
    BOOST_CHECK(lhs_bool == rhs_bool);

    read_n_times(reader, 4);
    const double lhs_double(reader.value_as_double());
    const double rhs_double(reader.value<double>());
    BOOST_LOG_SEV(lg, debug) << "lhs: " << lhs_double << " rhs: " << rhs_double;
    BOOST_CHECK(lhs_double == rhs_double);

    read_n_times(reader, 4);
    const int lhs_int(reader.value_as_int());
    const int rhs_int(reader.value<int>());
    BOOST_LOG_SEV(lg, debug) << "lhs: " << lhs_int << " rhs: " << rhs_int;
    BOOST_CHECK(lhs_int == rhs_int);

    read_n_times(reader, 4);
    const long lhs_long(reader.value_as_long());
    const long rhs_long(reader.value<long>());
    BOOST_LOG_SEV(lg, debug) << "lhs: " << lhs_long << " rhs: " << rhs_long;
    BOOST_CHECK(lhs_long == rhs_long);

    read_n_times(reader, 4);
    const std::string lhs_str(reader.value_as_string());
    const std::string rhs_str(reader.value<std::string>());
    BOOST_LOG_SEV(lg, debug) << "lhs: " << lhs_str << " rhs: " << rhs_str;
    BOOST_CHECK(lhs_str == rhs_str);
}

BOOST_AUTO_TEST_CASE(value_template_method_with_invalid_type_throws) {
    SETUP_TEST_LOG_SOURCE("value_template_method_with_invalid_type_throws");
    text_reader reader(xml_reader::input_string_value_inlined());
    read_n_times(reader, 2);

    const std::string expected(label_text_info);
    const std::string actual(reader.value<std::string>());
    BOOST_LOG_SEV(lg, debug) << "expected: " << expected << " actual: "
                             << actual;
    BOOST_CHECK(actual == expected);

    using namespace std::placeholders;
    BOOST_CHECK_EXCEPTION(
        reader.value<std::ostringstream>(),
        exception,
        std::bind(check_xml_exception, _1, message_error_unsupported_type));
}

BOOST_AUTO_TEST_CASE(reading_with_skip_whitespace_reads_all_expected_elements) {
    SETUP_TEST_LOG_SOURCE("reading_with_skip_whitespace_reads_all_expected_elements");
    const bool skip_ws(true);
    text_reader reader(xml_reader::input_node_with_attributes(), skip_ws);

    auto check_element([&](std::string name, node_types node_type) {
            BOOST_CHECK(reader.read());
            BOOST_LOG_SEV(lg, debug) << reader;
            BOOST_CHECK(reader.name() == name);
            BOOST_CHECK(reader.node_type() == node_type);
        });

    check_element(label_root_name, node_types::element);
    check_element(label_one_attribute, node_types::element);
    check_element(label_text, node_types::text);
    check_element(label_one_attribute, node_types::end_element);
    check_element(label_two_attribute, node_types::element);
    check_element(label_text, node_types::text);
    check_element(label_two_attribute, node_types::end_element);
    check_element(label_three_attribute, node_types::element);
    check_element(label_text, node_types::text);
    check_element(label_three_attribute, node_types::end_element);
    check_element(label_four_attribute, node_types::element);
    check_element(label_text, node_types::text);
    check_element(label_four_attribute, node_types::end_element);
    check_element(label_no_attributes, node_types::element);
    check_element(label_no_attributes, node_types::end_element);
    check_element(label_root_name, node_types::end_element);
}

BOOST_AUTO_TEST_CASE(skipping_with_skip_whitespace_skips_all_expected_elements) {
    SETUP_TEST_LOG_SOURCE("skipping_with_skip_whitespace_skips_all_expected_elements");
    const bool skip_ws(true);
    text_reader reader(xml_reader::input_three_nested_elements(), skip_ws);

    read_n_times(reader, 2);
    BOOST_CHECK(reader.skip());
    BOOST_LOG_SEV(lg, debug) << reader;
    BOOST_CHECK(reader.name() == label_level_1_parameter_2);

    read_n_times(reader, 1);
    BOOST_CHECK(reader.skip());
    BOOST_LOG_SEV(lg, debug) << reader;
    BOOST_CHECK(reader.name() == label_level_2_parameter_2);
}

BOOST_AUTO_TEST_CASE(is_end_element_is_true_for_end_elements_false_otherwise) {
    SETUP_TEST_LOG("is_end_element_is_true_for_end_elements_false_otherwise");
    text_reader reader(xml_reader::input_one_node_indented());

    BOOST_CHECK(reader.read());
    BOOST_CHECK(reader.name() == label_simple_node);
    BOOST_CHECK(!reader.is_end_element());

    BOOST_CHECK(reader.read());
    BOOST_CHECK(reader.name() == label_text);
    BOOST_CHECK(!reader.is_end_element());

    BOOST_CHECK(reader.read());
    BOOST_CHECK(reader.name() == label_simple_node);
    BOOST_CHECK(reader.is_end_element());
}

BOOST_AUTO_TEST_CASE(is_start_element_is_true_for_start_elements_false_otherwise) {
    SETUP_TEST_LOG("is_start_element_is_true_for_start_elements_false_otherwise");
    text_reader reader(xml_reader::input_one_node_indented());

    BOOST_CHECK(reader.read());
    BOOST_CHECK(reader.name() == label_simple_node);
    BOOST_CHECK(reader.is_start_element());

    BOOST_CHECK(reader.read());
    BOOST_CHECK(reader.name() == label_text);
    BOOST_CHECK(!reader.is_start_element());

    BOOST_CHECK(reader.read());
    BOOST_CHECK(reader.name() == label_simple_node);
    BOOST_CHECK(!reader.is_start_element());
}

BOOST_AUTO_TEST_SUITE_END()
