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
#include <string>
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/io/set_io.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/filesystem/file_not_found.hpp"
#include "dogen.utility/types/test_data/filesystem_tests.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"

namespace {

const std::string test_module("dogen.utility.tests");
const std::string test_suite("file_tests");

const std::string expected_content(
    "some contentent\nmore than one line\nend\n");
const std::string non_existent_file("non_existent_file.dia");
const std::string file_not_found_message("File not found: ");
const std::string not_a_dir_message("Not a directory");
const std::string invalid_dir("INVALID_DIRECTORY__");
const std::string dir_not_found_message("Could not find directory");

bool compare_filenames(boost::filesystem::path p1, boost::filesystem::path p2) {
    return p1.filename() == p2.filename();
}

}

using dogen::utility::filesystem::write_file_content;
using dogen::utility::filesystem::read_file_content;
using dogen::utility::filesystem::file_not_found;
using dogen::utility::filesystem::find_files;
using dogen::utility::test_data::filesystem_tests;
using dogen::utility::test::contains_checker;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(file_tests)

BOOST_AUTO_TEST_CASE(read_file_content_reads_existing_non_empty_file_correctly) {
    SETUP_TEST_LOG_SOURCE("read_file_content_reads_existing_non_empty_file_correctly");

    const auto i(filesystem_tests::input_non_empty_file_txt());
    BOOST_LOG_SEV(lg, info) << "input path: " << i.string();

    const auto actual(read_file_content(i));
    BOOST_CHECK(asserter::assert_object(expected_content, actual));
}

BOOST_AUTO_TEST_CASE(read_file_content_reads_empty_file_correctly) {
    SETUP_TEST_LOG_SOURCE("read_file_content_reads_existing_non_empty_file_correctly");
    const auto i(filesystem_tests::input_empty_file_txt());
    BOOST_LOG_SEV(lg, info) << "input path: " << i.string();

    const auto actual(read_file_content(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << actual;
    BOOST_CHECK(actual.empty());
}

BOOST_AUTO_TEST_CASE(read_file_content_throws_when_reading_non_existent_file) {
    SETUP_TEST_LOG_SOURCE("read_file_content_throws_when_reading_non_existent_file");
    const auto i(filesystem_tests::non_existent_file());
    BOOST_LOG_SEV(lg, info) << "input path: " << i.string();

    auto pred([](const file_not_found& e) -> bool {
            const std::string msg(e.what());
            return boost::starts_with(msg, file_not_found_message) &&
                boost::contains(msg, non_existent_file);
        });

    BOOST_CHECK_EXCEPTION(read_file_content(i), file_not_found, pred);
}

BOOST_AUTO_TEST_CASE(write_file_content_writes_file_correctly) {
    SETUP_TEST_LOG_SOURCE("write_file_content_writes_file_correctly");
    const auto a(filesystem_tests::actual_some_file_txt());
    BOOST_LOG_SEV(lg, info) << "actual path: " << a.string();

    write_file_content(a, expected_content);

    const auto e(filesystem_tests::expected_some_file_txt());
    BOOST_CHECK(asserter::assert_file(e, a));
}

BOOST_AUTO_TEST_CASE(write_file_content_overwrites_file_correctly) {
    SETUP_TEST_LOG_SOURCE("write_file_content_overwrites_file_correctly");
    const auto a(filesystem_tests::actual_file_to_overwrite_txt());
    BOOST_LOG_SEV(lg, info) << "actual path: " << a.string();

    write_file_content(a, expected_content);

    const auto e(filesystem_tests::expected_file_to_overwrite_txt());
    BOOST_CHECK(asserter::assert_file(e, a));
}

BOOST_AUTO_TEST_CASE(find_files_returns_expected_files_when_recursing) {
    SETUP_TEST_LOG_SOURCE("find_files_returns_expected_files_when_recursing");
    const auto dir(filesystem_tests::data_set());
    const auto files(dogen::utility::filesystem::find_files(dir));
    BOOST_LOG_SEV(lg, info) << "Files found: " << files;

    BOOST_CHECK(files.size() == 6);

    for (const auto& f : files) {
        BOOST_CHECK(
            compare_filenames(f, filesystem_tests::expected_some_file_txt()) ||
            compare_filenames(
                f, filesystem_tests::expected_file_to_overwrite_txt()) ||
            compare_filenames(
                f, filesystem_tests::input_non_empty_file_txt()) ||
            compare_filenames(f, filesystem_tests::input_empty_file_txt()));
    }
}

BOOST_AUTO_TEST_CASE(find_files_returns_expected_files_when_not_recursing) {
    SETUP_TEST_LOG_SOURCE("find_files_returns_expected_files_when_not_recursing");
    const auto dir(filesystem_tests::expected());
    const auto files(dogen::utility::filesystem::find_files(dir));
    BOOST_LOG_SEV(lg, info) << "Files found: " << files;

    BOOST_CHECK(files.size() == 2);
    for (const auto& f : files) {
        BOOST_CHECK(
            compare_filenames(f, filesystem_tests::expected_some_file_txt()) ||
            compare_filenames(
                f, filesystem_tests::expected_file_to_overwrite_txt()));
    }
}

BOOST_AUTO_TEST_CASE(find_files_returns_expected_files_with_multiple_directories) {
    SETUP_TEST_LOG_SOURCE("find_files_returns_expected_files_with_multiple_directories");
    const auto dirs = std::vector<boost::filesystem::path> {
        filesystem_tests::input(),
        filesystem_tests::expected(),
        filesystem_tests::actual(),
    };
    const auto files(dogen::utility::filesystem::find_files(dirs));
    BOOST_LOG_SEV(lg, info) << "Files found: " << files;

    BOOST_CHECK(files.size() == 6);

    for (const auto& f : files) {
        BOOST_CHECK(
            compare_filenames(f, filesystem_tests::expected_some_file_txt()) ||
            compare_filenames(
                f, filesystem_tests::expected_file_to_overwrite_txt()) ||
            compare_filenames(
                f, filesystem_tests::input_non_empty_file_txt()) ||
            compare_filenames(f, filesystem_tests::input_empty_file_txt()));
    }
}

BOOST_AUTO_TEST_CASE(find_files_throws_when_argument_is_a_file) {
    SETUP_TEST_LOG_SOURCE("find_files_throws_when_argument_is_a_file");
    const auto dir(filesystem_tests::expected_some_file_txt());
    contains_checker<file_not_found> c(not_a_dir_message);
    BOOST_CHECK_EXCEPTION(find_files(dir), file_not_found, c);
}

BOOST_AUTO_TEST_CASE(find_files_throws_when_directory_does_not_exist) {
    SETUP_TEST_LOG_SOURCE("find_files_throws_when_directory_does_not_exist");
    contains_checker<file_not_found> c(dir_not_found_message);
    BOOST_CHECK_EXCEPTION(find_files(invalid_dir), file_not_found, c);
}

BOOST_AUTO_TEST_SUITE_END()
