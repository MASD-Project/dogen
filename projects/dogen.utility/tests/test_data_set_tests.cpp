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
#include <functional>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test_data/xml_reader.hpp"

namespace {

const std::string test_module("dogen.utility.tests");
const std::string test_suite("test_data_set_tests");

const std::string dia_extension(".dia");
const std::string xml_extension(".xml");

const std::string xml_reader_dir("xml_reader");
const std::string xml_reader_input_dir("xml_reader/input");
const std::string xml_reader_expected_dir("xml_reader/expected");
const std::string xml_reader_actual_dir("xml_reader/actual");

const std::string boolean_values_file("xml_reader/input/boolean_values.xml");
const std::string non_existent_file_name("non_existent_file");

void test_main_directory(boost::filesystem::path path, std::string data_set) {
    using namespace dogen::utility::log;
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << data_set << " main directory: " << path;
    BOOST_CHECK(path.is_absolute());
    BOOST_CHECK(boost::filesystem::exists(path));
    BOOST_CHECK(boost::filesystem::is_directory(path));
    BOOST_CHECK(boost::ends_with(path.string(), data_set));
}

void test_non_existent_file(
    boost::filesystem::path path, std::string extension) {
    using namespace dogen::utility::log;
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "Non-existent file:" << path;
    BOOST_CHECK(path.is_absolute());
    BOOST_CHECK(!boost::filesystem::exists(path));
    BOOST_CHECK(boost::ends_with(path.string(),
            non_existent_file_name + extension));
}

void test_valid_file(boost::filesystem::path path, std::string postfix) {
    using namespace dogen::utility::log;
    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "File:" << path;
    BOOST_CHECK(path.is_absolute());
    BOOST_CHECK(boost::filesystem::exists(path));
    BOOST_CHECK(boost::filesystem::is_regular_file(path));
    BOOST_CHECK(boost::ends_with(path.string(), postfix));
}

}

BOOST_AUTO_TEST_SUITE(test_data_set_tests)

BOOST_AUTO_TEST_CASE(xml_reader_passes_sanity_checks) {
    SETUP_TEST_LOG("xml_reader_passes_sanity_checks");
    using dogen::utility::test_data::xml_reader;

    test_main_directory(xml_reader::data_set(), xml_reader_dir);
    test_main_directory(xml_reader::input(), xml_reader_input_dir);
    test_main_directory(xml_reader::expected(), xml_reader_expected_dir);
    test_main_directory(xml_reader::actual(), xml_reader_actual_dir);

    test_non_existent_file(xml_reader::non_existent_file(), xml_extension);
    test_valid_file(xml_reader::input_boolean_values(), boolean_values_file);
}

BOOST_AUTO_TEST_SUITE_END()
