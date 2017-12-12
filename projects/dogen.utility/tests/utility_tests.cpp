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
#include <array>
#include <string>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/io/jsonify_io.hpp"
#include "dogen.utility/io/vector_io.hpp"
#include "dogen.utility/io/pair_io.hpp"
#include "dogen.utility/io/map_io.hpp"
#include "dogen.utility/io/array_io.hpp"
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/log/life_cycle_manager.hpp"
#include "dogen.utility/log/scoped_life_cycle_manager.hpp"
#include "dogen.utility/log/logger.hpp"
#include "dogen.utility/exception/utility_exception.hpp"
#include "dogen.utility/test/json_validator.hpp"

namespace this_is_a_test {

class test_entity {
public:
    test_entity() : a_property_(10) {}

public:
    int a_property() const { return a_property_; }
    void a_property(int value) { a_property_ = value; }

private:
    int a_property_;
};

inline std::ostream&
operator<<(std::ostream& stream, const test_entity& value) {

    return stream << "\"test_entity\" {"
                  << " \"a_property\": " << value.a_property()
                  << "}";
}

}

namespace {

class complex_type {
public:
    explicit complex_type(const int i) : i_(i) { }
    int get() const { return(i_); }

private:
    int i_;
};

inline std::ostream&
operator<<(std::ostream& stream, const complex_type& insertee) {
    stream << "complex_type: { " << insertee.get() << " } ";
    return(stream);
}

class test_exception_class : public dogen::utility::exception::exception {
public:
    test_exception_class(const char* message) :
        dogen::utility::exception::exception(message) { }
};

const std::string test_suite("utility_tests");
const std::string test_module("utility");
const std::string prefix("log/utility/utility_tests/");

std::string log_file_name(std::string function, unsigned int postfix = 0) {
    std::ostringstream stream;
    stream << prefix << function;
    if (postfix != 0)
        stream << postfix;
    return stream.str();
}

}

BOOST_AUTO_TEST_SUITE(utility_tests)

BOOST_AUTO_TEST_CASE(exercise_log_life_cycle_manager) {
    // exericise 1: write a simple type to log file.
    using namespace dogen::utility::log;
    life_cycle_manager lcm;
    lcm.initialise(log_file_name("exercise_log_life_cycle_manager", 1),
        severity_level::debug);

    using namespace boost::log;
    logger lg(logger_factory(test_suite));

    BOOST_LOG_SEV(lg, warn) << "this is a streamed number: " << 123 << ".";
    BOOST_LOG_SEV(lg, debug) << "this is a debug statement";

    // exericise 2: write an entity to log file.
    this_is_a_test::test_entity entity;
    entity.a_property(20);
    BOOST_LOG_SEV(lg, info) << "this is an entity: " << entity;

    // exercise 3: write something at a log level lower than the
    // current log level.
    BOOST_LOG_SEV(lg, trace) << "this statement should not appear";

    // exercise 4: exercise error log levels
    BOOST_LOG_SEV(lg, error) << "this statement is an error";

    // exercise 5: shutdown logging and initialise it with different settings.
    lcm.shutdown();
    lcm.initialise(log_file_name("exercise_log_life_cycle_manager", 2),
        severity_level::warn);
    BOOST_LOG_SEV(lg, debug) << "this statement should not appear";
    BOOST_LOG_SEV(lg, error) << "this statement should appear";
    lcm.shutdown();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(exercise_scoped_log_life_cycle_manager) {
    using namespace dogen::utility::log;
    logger lg(logger_factory(test_suite));

    {
        scoped_life_cycle_manager slcm(
            log_file_name("exercise_scoped_log_life_cycle_manager", 1),
            severity_level::debug);
        BOOST_LOG_SEV(lg, trace)
            << "scoped1: " << "this statement should not appear";
        BOOST_LOG_SEV(lg, error)
            << "scoped2: " << "this statement should appear";
    }

    {
        scoped_life_cycle_manager slcm(
            log_file_name("exercise_scoped_log_life_cycle_manager", 2),
            severity_level::trace);
        BOOST_LOG_SEV(lg, trace)
            << "scoped3: " << "this statement should appear";
        BOOST_LOG_SEV(lg, error)
            << "scoped4: " << "this statement should appear";
    }
}

BOOST_AUTO_TEST_CASE(exericise_exception_derived_classes) {
    SETUP_TEST_LOG_SOURCE("exericise_exception_derived_classes");
    const std::string message("test message");

    // exercise 1: as a standard exception
    try {
        BOOST_THROW_EXCEPTION(test_exception_class(message.c_str()));
        BOOST_FAIL("Expected test_exception to be thrown.");
    } catch(const std::exception& e) {
        const std::string what(e.what());
        BOOST_CHECK(what == message);
        BOOST_LOG_SEV(lg, info) << "Exception thrown as expected. what: "
                                << e.what();
    }

    // exercise 2: as a boost exception
    try {
        BOOST_THROW_EXCEPTION(test_exception_class(message.c_str()));
        BOOST_FAIL("Expected test_exception to be thrown.");
    } catch(const boost::exception& e) {
        BOOST_LOG_SEV(lg, info)
            << "Exception test_exception thrown as expected.";
        BOOST_LOG_SEV(lg, info) << "diagnostic: "
                                << boost::diagnostic_information(e);
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_CASE(exception_shall_be_usable_as_a_standard_exception) {
    SETUP_TEST_LOG_SOURCE("exception_shall_be_usable_as_a_standard_exception");
    const std::string message("test message");
    try {
        throw(dogen::utility::exception::exception(message.c_str()));
        BOOST_FAIL("dogen::utility::exception::exception not thrown.");
    } catch(const std::exception& e) {
        const std::string what(e.what());
        BOOST_CHECK(what == message);
        BOOST_LOG_SEV(lg, info) << "Exception thrown as expected. what: "
                                << e.what();
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_CASE(exception_shall_be_usable_as_a_boost_exception) {
    SETUP_TEST_LOG_SOURCE("exception_shall_be_usable_as_a_boost_exception");
    const std::string message("test message");
    try {
        BOOST_THROW_EXCEPTION(
            dogen::utility::exception::exception(message.c_str()));
        BOOST_FAIL("dogen::utility::exception::exception not thrown.");
    } catch(const boost::exception& e) {
        BOOST_LOG_SEV(lg, debug) << "Exception thrown as expected. diagnostic: "
                                 << boost::diagnostic_information(e);
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_CASE(exercise_vector_inserter) {
    SETUP_TEST_LOG_SOURCE("exercise_vector_inserter");
    std::vector<int> ints;
    ints.push_back(10);
    ints.push_back(20);
    ints.push_back(30);
    BOOST_LOG_SEV(lg, debug) << "ints: " << ints;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(exercise_map_inserter) {
    SETUP_TEST_LOG_SOURCE("exercise_map_inserter");
    std::map<std::string, std::string> strings;
    strings.insert(std::make_pair("first key", "first value"));
    strings.insert(std::make_pair("second key", "second value"));
    strings.insert(std::make_pair("third key", "third value"));
    BOOST_LOG_SEV(lg, debug) << "strings: " << strings;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(exercise_pair_inserter) {
    SETUP_TEST_LOG_SOURCE("exercise_pair_inserter");
    std::pair<int, std::string> pair(std::make_pair(12, "test"));
    BOOST_LOG_SEV(lg, debug) << "pair: " << pair;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(exercise_jsonify_inserter) {
    SETUP_TEST_LOG_SOURCE("exercise_jsonify_inserter");
    using dogen::utility::streaming::jsonify;

    // exercise 1: strings
    BOOST_LOG_SEV(lg, debug) << "std::string: "
                             << jsonify(std::string("abc def"));
    BOOST_LOG_SEV(lg, debug) << "unsigned char: "
                             << jsonify((unsigned char)'a');
    BOOST_LOG_SEV(lg, debug) << "char: " << jsonify('b');

    // exercise 2: complex types
    complex_type ct(12);
    BOOST_LOG_SEV(lg, debug) << "complex_type: " << jsonify(ct);

    // exercise 3: numbers
    BOOST_LOG_SEV(lg, debug) << "unsigned int: " << jsonify((unsigned int)123);
    BOOST_LOG_SEV(lg, debug) << "int: " << jsonify((int)457);
    BOOST_LOG_SEV(lg, debug) << "unsigned short: "
                             << jsonify((unsigned short)10);
    BOOST_LOG_SEV(lg, debug) << "short: " << jsonify((short)15);
    BOOST_LOG_SEV(lg, debug) << "unsigned long: "
                             << jsonify((unsigned long)12345);
    BOOST_LOG_SEV(lg, debug) << "long: " << jsonify((long)54321);
    BOOST_LOG_SEV(lg, debug) << "float: " << jsonify((float)12.123);
    BOOST_LOG_SEV(lg, debug) << "double: " << jsonify((double)3.14);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(valid_json_parses_successfully) {
    SETUP_TEST_LOG_SOURCE("valid_json_parses_successfully");

    std::stringstream s;
    s << "{ \"__type__\": \"class_b\", \"prop_0\":  { \"__type__\": \"class_a\", \"prop_0\": 0, \"versioned_key\":  { \"__type__\": \"versioned_key\", \"id\": 1, \"version\": 2 } }, \"versioned_key\":  { \"__type__\": \"versioned_key\", \"id\": 0, \"version\": 1 } }";
    BOOST_CHECK(dogen::utility::test::json_validator::validate(s));
}

BOOST_AUTO_TEST_CASE(invalid_json_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("invalid_json_fails_to_parse");

    std::stringstream s;
    s << "{ \"__type__\": \"class_b\", \"prop_0\":  { \"__type__\": \"class_a\", \"prop_0\": 0, \"versioned_key\":  { \"__type__\": \"versioned_key\", \"id\": 1, \"version\": 2 } }, \"versioned_key\":  { \"__type__\": \"versioned_key\", \"id\": 0, \"version\": 1";
    BOOST_CHECK(!dogen::utility::test::json_validator::validate(s));
}

BOOST_AUTO_TEST_SUITE_END()
