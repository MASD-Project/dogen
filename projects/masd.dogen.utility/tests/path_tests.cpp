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
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/test/asserter.hpp"
#include "dogen.utility/filesystem/path.hpp"
#include "dogen.utility/filesystem/file_not_found.hpp"

namespace {

const std::string test_module("utility");
const std::string test_suite("path_tests");

}

BOOST_AUTO_TEST_SUITE(path_tests)

BOOST_AUTO_TEST_CASE(path_to_executable_returns_expected_results) {
    SETUP_TEST_LOG_SOURCE("path_to_executable_returns_expected_results");

    const auto p(dogen::utility::filesystem::executable_directory());
    BOOST_LOG_SEV(lg, info) << "input path: " << p.string();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(path_to_data_directory_returns_expected_results) {
    SETUP_TEST_LOG_SOURCE("path_to_data_directory_returns_expected_results");

    const auto p(dogen::utility::filesystem::data_files_directory());
    BOOST_LOG_SEV(lg, info) << "input path: " << p.string();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
