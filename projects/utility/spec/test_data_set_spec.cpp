/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Dogen Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <functional>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test_data/xml_reader.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"

namespace {

const std::string test_module("utility");
const std::string test_suite("test_data_set_spec");

const std::string dia_extension(".dia");
const std::string xml_extension(".xml");

const std::string xml_reader_dir("xml_reader");
const std::string xml_reader_input_dir("xml_reader/input");
const std::string xml_reader_expected_dir("xml_reader/expected");
const std::string xml_reader_actual_dir("xml_reader/actual");

const std::string dia_sml_dir("dia_sml");
const std::string dia_sml_input_dir("dia_sml/input");
const std::string dia_sml_expected_dir("dia_sml/expected");
const std::string dia_sml_actual_dir("dia_sml/actual");

const std::string boolean_values_file("xml_reader/input/boolean_values.xml");
const std::string class_namespace_file_dia(
    "dia_sml/input/class_in_a_package.dia");
const std::string class_namespace_file_diaxml(
    "dia_sml/expected/class_in_a_package.diaxml");
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

void test_non_existent_file(boost::filesystem::path path, std::string extension) {
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

BOOST_AUTO_TEST_SUITE(test_data_set)

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

BOOST_AUTO_TEST_CASE(dia_sml_passes_sanity_checks) {
    SETUP_TEST_LOG("dia_sml_passes_sanity_checks");
    using dogen::utility::test_data::dia_sml;
    test_main_directory(dia_sml::data_set(), dia_sml_dir);
    test_main_directory(dia_sml::input(), dia_sml_input_dir);
    test_main_directory(dia_sml::expected(), dia_sml_expected_dir);
    test_main_directory(dia_sml::actual(), dia_sml_actual_dir);
    test_non_existent_file(dia_sml::non_existent_file(), dia_extension);

    test_valid_file(dia_sml::input_class_in_a_package_dia(),
        class_namespace_file_dia);
    test_valid_file(dia_sml::expected_class_in_a_package_dia_xml(),
        class_namespace_file_diaxml);
}

BOOST_AUTO_TEST_SUITE_END()
