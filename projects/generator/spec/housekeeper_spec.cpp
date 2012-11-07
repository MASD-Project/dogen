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
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/tds_test_good.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/generator/housekeeper.hpp"

namespace  {

const std::string test_suite("housekeeper_spec");
const std::string test_module("generator");
const std::string hk_tds_expected("housekeeper/expected");
const std::string hk_tds_actual_f1("housekeeper/actual/file_1.txt");
const std::string hk_tds_actual_f2("housekeeper/actual/file_2.txt");
const std::string hk_tds_actual("housekeeper/actual");

const std::vector<std::string> ignored_files;

}

BOOST_AUTO_TEST_SUITE(housekeeper)

BOOST_AUTO_TEST_CASE(when_all_files_are_present_housekeeper_does_not_find_extra_files) {
    SETUP_TEST_LOG("when_all_files_are_present_housekeeper_does_not_find_extra_files");
    std::set<boost::filesystem::path> e;

    using dogen::utility::test_data::tds_test_good;
    e.insert(tds_test_good::expected_file_1_txt());
    e.insert(tds_test_good::expected_file_2_txt());
    e.insert(tds_test_good::expected_test_serializer_xmltst());
    e.insert(tds_test_good::expected_test_serializer_2_xmltst());
    e.insert(tds_test_good::expected_empty_file_txt());

    const std::vector<boost::filesystem::path> v({tds_test_good::expected()});
    const bool verbose(true);
    bool called(false);
    const auto lambda([&](std::list<boost::filesystem::path>) {called = true;});

    using dogen::generator::housekeeper;
    housekeeper hk(ignored_files, v, e, verbose, lambda);
    hk.tidy_up();
    BOOST_CHECK(!called);
}

BOOST_AUTO_TEST_CASE(when_extra_files_are_present_housekeeper_finds_the_extra_files) {
    SETUP_TEST_LOG("when_extra_files_are_present_housekeeper_finds_the_extra_files");
    std::set<boost::filesystem::path> e;

    using dogen::utility::test_data::tds_test_good;
    e.insert(tds_test_good::expected_test_serializer_xmltst());
    e.insert(tds_test_good::expected_test_serializer_2_xmltst());
    e.insert(tds_test_good::expected_empty_file_txt());

    const std::vector<boost::filesystem::path> v({tds_test_good::expected()});
    const bool verbose(true);
    bool called(false);
    const auto lambda([&](std::list<boost::filesystem::path> p) {
            BOOST_CHECK(p.size() == 2);
            BOOST_CHECK(
                (p.front() == tds_test_good::expected_file_1_txt() &&
                    p.back() == tds_test_good::expected_file_2_txt()) ||
                (p.back() == tds_test_good::expected_file_1_txt() &&
                    p.front() == tds_test_good::expected_file_2_txt()));
            called = true;
        });

    using dogen::generator::housekeeper;
    housekeeper hk(ignored_files, v, e, verbose, lambda);
    hk.tidy_up();
    BOOST_CHECK(called);
}

BOOST_AUTO_TEST_CASE(housekeeper_deletes_extra_files_and_only_extra_files) {
    SETUP_TEST_LOG("housekeeper_deletes_extra_files_and_only_extra_files");
    using dogen::utility::test_data::validating_resolver;
    const auto a(validating_resolver::resolve(hk_tds_actual));
    const std::vector<boost::filesystem::path> v({a});

    std::set<boost::filesystem::path> f;
    f.insert(validating_resolver::resolve(hk_tds_actual_f1));
    f.insert(validating_resolver::resolve(hk_tds_actual_f2));

    const bool verbose(true);

    using dogen::generator::housekeeper;
    housekeeper hk(ignored_files, v, f, verbose);
    hk.tidy_up();

    using dogen::utility::test::asserter;
    const auto e(validating_resolver::resolve(hk_tds_expected));
    BOOST_CHECK(asserter::assert_directory(e, a));
}


BOOST_AUTO_TEST_CASE(ignored_files_are_not_deleted) {
    SETUP_TEST_LOG("ignored_files_are_not_deleted");
    std::set<boost::filesystem::path> e;

    using dogen::utility::test_data::tds_test_good;
    e.insert(tds_test_good::expected_test_serializer_xmltst());
    e.insert(tds_test_good::expected_test_serializer_2_xmltst());
    e.insert(tds_test_good::expected_empty_file_txt());

    std::vector<std::string> ignores({".*/file_1.*"});

    const std::vector<boost::filesystem::path> v({tds_test_good::expected()});
    const bool verbose(true);
    bool called(false);
    const auto lambda([&](std::list<boost::filesystem::path> l) {
            for (const auto a : l)
                if (a == tds_test_good::expected_file_1_txt())
                    called = true;
        });

    using dogen::generator::housekeeper;
    housekeeper hk(ignores, v, e, verbose, lambda);
    hk.tidy_up();
    BOOST_CHECK(!called);
}


BOOST_AUTO_TEST_SUITE_END()
