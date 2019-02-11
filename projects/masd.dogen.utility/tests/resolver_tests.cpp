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
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/test/asserter.hpp"
#include "masd.dogen.utility/types/test_data/resolver.hpp"
#include "masd.dogen.utility/types/test_data/validating_resolver.hpp"
#include "masd.dogen.utility/types/test_data/tds_test_good.hpp"
#include "masd.dogen.utility/types/filesystem/file_not_found.hpp"

namespace {

const std::string test_module("masd.dogen.utility.tests");
const std::string test_suite("resolver_tests");

const std::string non_existent_file("non_existent_file.dia");
const std::string test_data_dir("test_data");
const std::string good_dataset("tds_test_good");
const std::string file_not_found("File not found: ");

}

BOOST_AUTO_TEST_SUITE(resolver_tests)

BOOST_AUTO_TEST_CASE(resolver_returns_test_data_directory_for_empty_paths) {
    SETUP_TEST_LOG_SOURCE("resolver_returns_test_data_directory_for_empty_paths");
    using masd::dogen::utility::test_data::resolver;
    const auto r(resolver::resolve(boost::filesystem::path()));

    BOOST_LOG_SEV(lg, info) << "path: " << r.string();
    BOOST_CHECK(boost::filesystem::exists(r));
    BOOST_CHECK(boost::ends_with(r.string(), test_data_dir));
}

BOOST_AUTO_TEST_CASE(resolver_returns_absolute_path_for_relative_path) {
    SETUP_TEST_LOG_SOURCE("resolver_returns_absolute_path_for_relative_path");
    using masd::dogen::utility::test_data::resolver;
    const auto r(resolver::resolve(good_dataset));

    BOOST_LOG_SEV(lg, info) << "path: " << r.string();
    BOOST_CHECK(boost::filesystem::exists(r));
    BOOST_CHECK(boost::ends_with(r.string(), good_dataset));
}

BOOST_AUTO_TEST_CASE(resolver_does_not_throw_for_non_existent_paths) {
    SETUP_TEST_LOG_SOURCE("resolver_does_not_throw_for_non_existent_paths");
    using masd::dogen::utility::test_data::resolver;
    using masd::dogen::utility::test_data::tds_test_good;
    const auto r(resolver::resolve(tds_test_good::non_existent_file()));

    BOOST_LOG_SEV(lg, info) << "path: " << r.string();
    BOOST_CHECK(!boost::filesystem::exists(r));
    BOOST_CHECK(boost::ends_with(r.string(), non_existent_file));
}

BOOST_AUTO_TEST_CASE(validating_resolver_returns_test_data_directory_for_empty_paths) {
    SETUP_TEST_LOG_SOURCE("validating_resolver_returns_test_data_directory_for_empty_paths");
    using masd::dogen::utility::test_data::validating_resolver;
    const auto r(validating_resolver::resolve(boost::filesystem::path()));

    BOOST_LOG_SEV(lg, info) << "path: " << r.string();
    BOOST_CHECK(boost::filesystem::exists(r));
    BOOST_CHECK(boost::ends_with(r.string(), test_data_dir));
}

BOOST_AUTO_TEST_CASE(validating_resolver_returns_absolute_path_for_relative_path) {
    SETUP_TEST_LOG_SOURCE("validating_resolver_returns_absolute_path_for_relative_path");
    using masd::dogen::utility::test_data::validating_resolver;
    const auto r(validating_resolver::resolve(good_dataset));

    BOOST_LOG_SEV(lg, info) << "path: " << r.string();
    BOOST_CHECK(boost::filesystem::exists(r));
    BOOST_CHECK(boost::ends_with(r.string(), good_dataset));
}

BOOST_AUTO_TEST_CASE(validating_resolver_throws_for_non_existent_paths) {
    SETUP_TEST_LOG_SOURCE("validating_resolver_throws_for_non_existent_paths");
    using masd::dogen::utility::test_data::tds_test_good;
    const auto i(tds_test_good::non_existent_file());
    BOOST_LOG_SEV(lg, info) << "input path: " << i.string();

    using masd::dogen::utility::test_data::validating_resolver;
    using masd::dogen::utility::filesystem::file_not_found;

    BOOST_CHECK_EXCEPTION(
        validating_resolver::resolve(i),
        file_not_found,
        [](const file_not_found& e) -> bool {
            const std::string msg(e.what());
            return boost::starts_with(msg, ::file_not_found) &&
                boost::contains(msg, non_existent_file);
        });
}

BOOST_AUTO_TEST_SUITE_END()
