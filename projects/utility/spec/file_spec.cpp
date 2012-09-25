/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <string>
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/filesystem/file_not_found.hpp"
#include "dogen/utility/test_data/filesystem_tests.hpp"

namespace {

const std::string test_module("utility");
const std::string test_suite("kuito_spec");

const std::string expected_content("some contentent\nmore than one line\nend\n");
const std::string non_existent_file("non_existent_file.dia");
const std::string file_not_found("File not found: ");

}

BOOST_AUTO_TEST_SUITE(file)

BOOST_AUTO_TEST_CASE(read_file_content_reads_existing_non_empty_file_correctly) {
    SETUP_TEST_LOG_SOURCE("read_file_content_reads_existing_non_empty_file_correctly");
    using dogen::utility::test_data::filesystem_tests;
    const auto i(filesystem_tests::input_non_empty_file_txt());
    BOOST_LOG_SEV(lg, info) << "input path: " << i.string();

    using dogen::utility::filesystem::read_file_content;
    const auto actual(read_file_content(i));

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_object(expected_content, actual));
}

BOOST_AUTO_TEST_CASE(read_file_content_reads_empty_file_correctly) {
    SETUP_TEST_LOG_SOURCE("read_file_content_reads_existing_non_empty_file_correctly");
    using dogen::utility::test_data::filesystem_tests;
    const auto i(filesystem_tests::input_empty_file_txt());
    BOOST_LOG_SEV(lg, info) << "input path: " << i.string();

    using dogen::utility::filesystem::read_file_content;
    const auto actual(read_file_content(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << actual;
    BOOST_CHECK(actual.empty());
}

BOOST_AUTO_TEST_CASE(read_file_content_throws_when_reading_non_existent_file) {
    SETUP_TEST_LOG_SOURCE("read_file_content_throws_when_reading_non_existent_file");
    using dogen::utility::test_data::filesystem_tests;
    const auto i(filesystem_tests::non_existent_file());
    BOOST_LOG_SEV(lg, info) << "input path: " << i.string();

    using dogen::utility::filesystem::file_not_found;
    auto pred([](const file_not_found& e) {
            const std::string msg(e.what());
            return boost::starts_with(msg, ::file_not_found) &&
                boost::contains(msg, ::non_existent_file);
        });

    using dogen::utility::filesystem::read_file_content;
    BOOST_CHECK_EXCEPTION(read_file_content(i), file_not_found, pred);
}

BOOST_AUTO_TEST_CASE(write_file_content_writes_file_correctly) {
    SETUP_TEST_LOG_SOURCE("write_file_content_writes_file_correctly");
    using dogen::utility::test_data::filesystem_tests;
    const auto a(filesystem_tests::actual_some_file_txt());
    BOOST_LOG_SEV(lg, info) << "actual path: " << a.string();

    using dogen::utility::filesystem::write_file_content;
    write_file_content(a, expected_content);

    const auto e(filesystem_tests::expected_some_file_txt());
    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_file(e, a));
}

BOOST_AUTO_TEST_CASE(write_file_content_overwrites_file_correctly) {
    SETUP_TEST_LOG_SOURCE("write_file_content_overwrites_file_correctly");
    using dogen::utility::test_data::filesystem_tests;
    const auto a(filesystem_tests::actual_file_to_overwrite_txt());
    BOOST_LOG_SEV(lg, info) << "actual path: " << a.string();

    using dogen::utility::filesystem::write_file_content;
    write_file_content(a, expected_content);

    const auto e(filesystem_tests::expected_file_to_overwrite_txt());
    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_file(e, a));
}

BOOST_AUTO_TEST_SUITE_END()
