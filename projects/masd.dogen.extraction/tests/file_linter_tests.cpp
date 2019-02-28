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
#include <boost/test/unit_test.hpp>
#include "masd.dogen.utility/types/test/asserter.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/test_data/validating_resolver.hpp"
#include "masd.dogen.utility/types/test_data/tds_test_good.hpp"
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.extraction/types/helpers/file_linter.hpp"

namespace  {

const std::string test_suite("file_linter_tests");
const std::string test_module("masd.dogen.extraction.tests");
const std::string fl_tds_expected("file_linter/expected");
const std::string fl_tds_actual_f1("file_linter/actual/file_1.txt");
const std::string fl_tds_actual_f2("file_linter/actual/file_2.txt");
const std::string fl_tds_actual("file_linter/actual");

const std::vector<std::string> ignored_files;

const std::list<boost::filesystem::path> managed_directories() {
    std::list<boost::filesystem::path> r;
    r.push_front(masd::dogen::utility::test_data::tds_test_good::expected());
    return r;
}

const masd::dogen::extraction::meta_model::artefact
to_artefact(const boost::filesystem::path& p) {
    masd::dogen::extraction::meta_model::artefact r;
    r.path(p);
    return r;
}

const masd::dogen::extraction::meta_model::model
create_model(const std::list<boost::filesystem::path>& files,
    const std::vector<std::string>& ignored_files) {
    masd::dogen::extraction::meta_model::model r;
    r.ignore_files_matching_regex(ignored_files);
    r.managed_directories(managed_directories());
    for(const auto& f : files)
        r.artefacts().push_back(to_artefact(f));

    return r;
}

}

BOOST_AUTO_TEST_SUITE(file_linter_tests)

BOOST_AUTO_TEST_CASE(when_all_files_are_present_file_linter_does_not_find_extra_files) {
    SETUP_TEST_LOG("when_all_files_are_present_file_linter_does_not_find_extra_files");
    using masd::dogen::utility::test_data::tds_test_good;
    const std::list<boost::filesystem::path> files = {
        tds_test_good::expected_file_1_txt(),
        tds_test_good::expected_file_2_txt(),
        tds_test_good::expected_test_serializer_xmltst(),
        tds_test_good::expected_test_serializer_2_xmltst(),
        tds_test_good::expected_empty_file_txt()
    };
    const auto tm(create_model(files, ignored_files));
    using masd::dogen::extraction::helpers::file_linter;
    const auto result(file_linter::lint(tm));
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(when_extra_files_are_present_file_linter_finds_the_extra_files) {
    SETUP_TEST_LOG("when_extra_files_are_present_file_linter_finds_the_extra_files");
    using masd::dogen::utility::test_data::tds_test_good;
    const std::list<boost::filesystem::path> files = {
        tds_test_good::expected_test_serializer_xmltst(),
        tds_test_good::expected_test_serializer_2_xmltst(),
        tds_test_good::expected_empty_file_txt()
    };
    const auto tm(create_model(files, ignored_files));
    using masd::dogen::extraction::helpers::file_linter;
    const auto result(file_linter::lint(tm));

    BOOST_REQUIRE(result.size() == 2);
    BOOST_CHECK(
        (result.front() == tds_test_good::expected_file_1_txt() &&
            result.back() == tds_test_good::expected_file_2_txt()) ||
        (result.back() == tds_test_good::expected_file_1_txt() &&
            result.front() == tds_test_good::expected_file_2_txt()));
}

BOOST_AUTO_TEST_CASE(ignored_files_are_not_deleted) {
    SETUP_TEST_LOG("ignored_files_are_not_deleted");
    using masd::dogen::utility::test_data::tds_test_good;
    const std::list<boost::filesystem::path> files = {
        tds_test_good::expected_test_serializer_xmltst(),
        tds_test_good::expected_test_serializer_2_xmltst(),
        tds_test_good::expected_empty_file_txt()
    };

    const std::vector<std::string> ignores({".*/file_1.*"});
    const auto tm(create_model(files, ignores));
    using masd::dogen::extraction::helpers::file_linter;
    const auto result(file_linter::lint(tm));

    BOOST_CHECK([&]{
            for (const auto& f : result)
                if (f == tds_test_good::expected_file_1_txt())
                    return false;
            return true;
        }());
}

BOOST_AUTO_TEST_SUITE_END()
