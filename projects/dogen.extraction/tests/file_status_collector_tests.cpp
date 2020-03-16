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
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/test_data/validating_resolver.hpp"
#include "dogen.utility/types/test_data/tds_test_good.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.extraction/types/helpers/file_status_collector.hpp"

namespace  {

const std::string test_suite("file_status_collector_tests");
const std::string test_module("dogen.extraction.tests");
const std::string fl_tds_expected("file_status_collector/expected");
const std::string fl_tds_actual_f1("file_status_collector/actual/file_1.txt");
const std::string fl_tds_actual_f2("file_status_collector/actual/file_2.txt");
const std::string fl_tds_actual("file_status_collector/actual");

const std::vector<std::string> ignored_files;

const std::list<boost::filesystem::path> managed_directories() {
    std::list<boost::filesystem::path> r;
    r.push_back(dogen::utility::test_data::tds_test_good::expected());
    return r;
}

const dogen::extraction::entities::artefact
to_artefact(const boost::filesystem::path& p) {
    dogen::extraction::entities::artefact r;
    r.path(p);
    return r;
}

const dogen::extraction::entities::model
create_model(const std::list<boost::filesystem::path>& files,
    const std::vector<std::string>& ignored_files) {
    dogen::extraction::entities::model r;
    r.outputting_properties().ignore_files_matching_regex(ignored_files);
    r.managed_directories(managed_directories());
    for(const auto& f : files)
        r.artefacts().push_back(to_artefact(f));

    return r;
}

}

BOOST_AUTO_TEST_SUITE(file_status_collector_tests)

BOOST_AUTO_TEST_CASE(when_all_files_are_present_file_status_collector_does_not_find_extra_files) {
    SETUP_TEST_LOG("when_all_files_are_present_file_status_collector_does_not_find_extra_files");
    using dogen::utility::test_data::tds_test_good;
    const std::list<boost::filesystem::path> files = {
        tds_test_good::expected_file_1_txt(),
        tds_test_good::expected_file_2_txt(),
        tds_test_good::expected_test_serializer_xmltst(),
        tds_test_good::expected_test_serializer_2_xmltst(),
        tds_test_good::expected_empty_file_txt()
    };
    const auto tm(create_model(files, ignored_files));
    using dogen::extraction::helpers::file_status_collector;
    const auto r(file_status_collector::collect(tm));
    BOOST_CHECK(r.unexpected().empty());
}

BOOST_AUTO_TEST_CASE(when_extra_files_are_present_file_status_collector_finds_the_extra_files) {
    SETUP_TEST_LOG("when_extra_files_are_present_file_status_collector_finds_the_extra_files");
    using dogen::utility::test_data::tds_test_good;
    const std::list<boost::filesystem::path> files = {
        tds_test_good::expected_test_serializer_xmltst(),
        tds_test_good::expected_test_serializer_2_xmltst(),
        tds_test_good::expected_empty_file_txt()
    };
    const auto tm(create_model(files, ignored_files));
    using dogen::extraction::helpers::file_status_collector;
    const auto r(file_status_collector::collect(tm));

    BOOST_REQUIRE(r.unexpected().size() == 2);
    BOOST_CHECK(
        (r.unexpected().front() == tds_test_good::expected_file_1_txt() &&
            r.unexpected().back() == tds_test_good::expected_file_2_txt()) ||
        (r.unexpected().back() == tds_test_good::expected_file_1_txt() &&
            r.unexpected().front() == tds_test_good::expected_file_2_txt()));
}

BOOST_AUTO_TEST_CASE(ignored_files_are_not_deleted) {
    SETUP_TEST_LOG("ignored_files_are_not_deleted");
    using dogen::utility::test_data::tds_test_good;
    const std::list<boost::filesystem::path> files = {
        tds_test_good::expected_test_serializer_xmltst(),
        tds_test_good::expected_test_serializer_2_xmltst(),
        tds_test_good::expected_empty_file_txt()
    };

    const std::vector<std::string> ignores({".*/file_1.*"});
    const auto tm(create_model(files, ignores));
    using dogen::extraction::helpers::file_status_collector;
    const auto r(file_status_collector::collect(tm));

    BOOST_CHECK([&]{
            for (const auto& f : r.unexpected())
                if (f == tds_test_good::expected_file_1_txt())
                    return false;
            return true;
        }());
}

BOOST_AUTO_TEST_SUITE_END()
