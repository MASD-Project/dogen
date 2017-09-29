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
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/tds_test_good.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/yarn/types/helpers/file_linter.hpp"

namespace  {

const std::string test_suite("file_linter_tests");
const std::string test_module("yarn");
const std::string fl_tds_expected("file_linter/expected");
const std::string fl_tds_actual_f1("file_linter/actual/file_1.txt");
const std::string fl_tds_actual_f2("file_linter/actual/file_2.txt");
const std::string fl_tds_actual("file_linter/actual");

const std::vector<std::string> ignored_files;

const std::list<boost::filesystem::path> managed_directories() {
    std::list<boost::filesystem::path> r;
    r.push_front(dogen::utility::test_data::tds_test_good::expected());
    return r;
}

const dogen::formatters::artefact
to_artefact(const boost::filesystem::path& p) {
    dogen::formatters::artefact r;
    r.path(p);
    return r;
}

const dogen::yarn::meta_model::text_model
create_model(const std::list<boost::filesystem::path> files) {
    dogen::yarn::meta_model::text_model r;
    r.managed_directories(managed_directories());
    for(const auto& f : files)
        r.artefacts().push_back(to_artefact(f));

    return r;
}

}

BOOST_AUTO_TEST_SUITE(file_linter_tests)

BOOST_AUTO_TEST_CASE(when_all_files_are_present_file_linter_does_not_find_extra_files) {
    SETUP_TEST_LOG("when_all_files_are_present_file_linter_does_not_find_extra_files");
    using dogen::utility::test_data::tds_test_good;
    const std::list<boost::filesystem::path> files = {
        tds_test_good::expected_file_1_txt(),
        tds_test_good::expected_file_2_txt(),
        tds_test_good::expected_test_serializer_xmltst(),
        tds_test_good::expected_test_serializer_2_xmltst(),
        tds_test_good::expected_empty_file_txt()
    };
    const auto tm(create_model(files));

    using dogen::yarn::helpers::file_linter;
    const auto result(file_linter::lint(ignored_files, tm));
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(when_extra_files_are_present_file_linter_finds_the_extra_files) {
    SETUP_TEST_LOG("when_extra_files_are_present_file_linter_finds_the_extra_files");
    using dogen::utility::test_data::tds_test_good;
    const std::list<boost::filesystem::path> files = {
        tds_test_good::expected_test_serializer_xmltst(),
        tds_test_good::expected_test_serializer_2_xmltst(),
        tds_test_good::expected_empty_file_txt()
    };
    const auto tm(create_model(files));

    using dogen::yarn::helpers::file_linter;
    const auto result(file_linter::lint(ignored_files, tm));

    BOOST_CHECK(result.size() == 2);
    BOOST_CHECK(
        (result.front() == tds_test_good::expected_file_1_txt() &&
            result.back() == tds_test_good::expected_file_2_txt()) ||
        (result.back() == tds_test_good::expected_file_1_txt() &&
            result.front() == tds_test_good::expected_file_2_txt()));
}

BOOST_AUTO_TEST_CASE(ignored_files_are_not_deleted) {
    SETUP_TEST_LOG("ignored_files_are_not_deleted");
    using dogen::utility::test_data::tds_test_good;
    const std::list<boost::filesystem::path> files = {
        tds_test_good::expected_test_serializer_xmltst(),
        tds_test_good::expected_test_serializer_2_xmltst(),
        tds_test_good::expected_empty_file_txt()
    };
    const auto tm(create_model(files));

    const std::vector<std::string> ignores({".*/file_1.*"});
    using dogen::yarn::helpers::file_linter;
    const auto result(file_linter::lint(ignores, tm));

    BOOST_CHECK([&]{
            for (const auto& f : result)
                if (f == tds_test_good::expected_file_1_txt())
                    return false;
            return true;
        }());
}

BOOST_AUTO_TEST_SUITE_END()
