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
#include "dogen.utility/types/test_data/validating_resolver.hpp"
#include "dogen.utility/types/io/set_io.hpp"
#include "dogen.utility/types/io/vector_io.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/filesystem/file_not_found.hpp"
#include "dogen.utility/types/test_data/tds_test_good.hpp"

template<typename Archive> void register_types(Archive&) {
}

namespace {

const std::string test_module("dogen.utility.tests");
const std::string test_suite("asserter_tests");

const std::string non_existent_file("non_existent_file.dia");

const std::string bad_dataset("tds_test_bad");
const std::string bad_dataset_actual("tds_test_bad/actual");
const std::string bad_dataset_expected("tds_test_bad/expected");
const std::string ugly_dataset_actual("tds_test_ugly/actual");
const std::string ugly_dataset_expected("tds_test_ugly/expected");

const std::string file_not_found("File not found: ");

/*
 * Set to true to rebase. Note that you still need to run the
 * appropriate rebase target afterwards to copy the files across.
 */
const bool rm(false);

struct test_serialization {
    test_serialization() : i_(0) {}
    test_serialization(int i) : i_(i) { }
    bool operator==(const test_serialization& rhs) const {
        return i_ == rhs.i_;
    }
    int i_;
};

std::ostream& operator<<(std::ostream& stream, const test_serialization& v) {
    return stream << "\"test_serialization\": {"
                  << "\"i\": " << v.i_
                  << "}";
}

}

namespace boost::serialization {

template<class Archive>
inline void
serialize(Archive & archive,  test_serialization& v, const unsigned int) {
    archive & make_nvp("i", v.i_);
}

}

BOOST_AUTO_TEST_SUITE(asserter_tests)

BOOST_AUTO_TEST_CASE(assert_file_returns_true_for_files_with_equal_contents) {
    SETUP_TEST_LOG("assert_file_returns_true_for_files_with_equal_contents");
    using dogen::utility::test_data::tds_test_good;
    const auto e(tds_test_good::expected_file_1_txt());
    const auto a(tds_test_good::actual_file_1_txt());

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_file(e, a));
}

BOOST_AUTO_TEST_CASE(assert_file_returns_true_for_empty_files) {
    SETUP_TEST_LOG("assert_file_returns_true_for_empty_files");
    using dogen::utility::test_data::tds_test_good;
    const auto e(tds_test_good::expected_empty_file_txt());
    const auto a(tds_test_good::actual_empty_file_txt());

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_file(e, a));
}

BOOST_AUTO_TEST_CASE(assert_file_returns_false_for_files_with_different_content) {
    SETUP_TEST_LOG("assert_file_returns_false_for_files_with_different_content");
    using dogen::utility::test_data::tds_test_good;
    const auto e(tds_test_good::expected_file_1_txt());
    const auto a(tds_test_good::actual_file_2_txt());

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_file(e, a));
}

BOOST_AUTO_TEST_CASE(assert_file_throws_for_non_existent_files) {
    SETUP_TEST_LOG_SOURCE("assert_file_throws_for_non_existent_files");
    using dogen::utility::test_data::tds_test_good;
    const auto g(tds_test_good::expected_file_1_txt());
    const auto b(tds_test_good::non_existent_file());
    BOOST_LOG_SEV(lg, info) << "g: " << g.string();
    BOOST_LOG_SEV(lg, info) << "b: " << b.string();

    using dogen::utility::filesystem::file_not_found;
    auto f([](const file_not_found& e) -> bool {
            const std::string msg(e.what());
            return boost::starts_with(msg, ::file_not_found) &&
                boost::contains(msg, ::non_existent_file);
        });

    using dogen::utility::test::asserter;
    BOOST_CHECK_EXCEPTION(asserter::assert_file(g, b), file_not_found, f);
    BOOST_CHECK_EXCEPTION(asserter::assert_file(b, g), file_not_found, f);
    BOOST_CHECK_EXCEPTION(asserter::assert_file(b, b), file_not_found, f);
}

BOOST_AUTO_TEST_CASE(assert_directory_good_data_set_returns_true) {
    SETUP_TEST_LOG("assert_directory_good_data_set_returns_true");
    using dogen::utility::test_data::tds_test_good;
    const auto a(tds_test_good::actual());
    const auto e(tds_test_good::expected());

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_directory(e, a));
}

BOOST_AUTO_TEST_CASE(assert_directory_bad_data_set_returns_false) {
    SETUP_TEST_LOG("assert_directory_bad_data_set_returns_false");
    using dogen::utility::test_data::validating_resolver;
    const auto a(validating_resolver::resolve(bad_dataset_actual));
    const auto e(validating_resolver::resolve(bad_dataset_expected));

    using dogen::utility::test::asserter;
    BOOST_CHECK(!asserter::assert_directory(e, a));
}

BOOST_AUTO_TEST_CASE(assert_directory_ugly_data_set_returns_false) {
    SETUP_TEST_LOG("assert_directory_ugly_data_set_returns_false");
    using dogen::utility::test_data::validating_resolver;
    const auto a(validating_resolver::resolve(ugly_dataset_actual));
    const auto e(validating_resolver::resolve(ugly_dataset_expected));

    using dogen::utility::test::asserter;
    BOOST_CHECK(!asserter::assert_directory(e, a));
}

BOOST_AUTO_TEST_CASE(assert_object_serialize_and_compare_returns_true_if_items_are_equal) {
    SETUP_TEST_LOG("assert_object_serialize_and_compare_returns_true_if_items_are_equal");
    using dogen::utility::test_data::tds_test_good;
    const auto a(tds_test_good::actual_test_serializer_xmltst());
    const auto e(tds_test_good::expected_test_serializer_xmltst());

    test_serialization ts(5);
    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_object(rm, e, a, ts));
}

BOOST_AUTO_TEST_CASE(assert_object_serialize_and_compare_returns_false_if_items_are_different) {
    SETUP_TEST_LOG("assert_object_serialize_and_compare_returns_false_if_items_are_different");
    using dogen::utility::test_data::tds_test_good;
    const auto a(tds_test_good::actual_test_serializer_2_xmltst());
    const auto e(tds_test_good::expected_test_serializer_xmltst());

    test_serialization ts(10);
    using dogen::utility::test::asserter;
    BOOST_CHECK(!asserter::assert_object(rm, e, a, ts));
}

BOOST_AUTO_TEST_CASE(assert_equals_returns_false_if_items_are_different) {
    SETUP_TEST_LOG("assert_equals_returns_false_if_items_are_different");

    std::string e_str("some string");
    std::string a_str("another string");

    using dogen::utility::test::asserter;
    BOOST_CHECK(!asserter::assert_equals(e_str, a_str));

    int e_int(0);
    int a_int(1);
    BOOST_CHECK(!asserter::assert_equals(e_int, a_int));
}

BOOST_AUTO_TEST_CASE(assert_equals_returns_true_if_items_are_equal) {
    SETUP_TEST_LOG("assert_equals_returns_true_if_items_are_equal");

    std::string e_str("some string");
    std::string a_str("some string");

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_equals(e_str, a_str));
    BOOST_CHECK(asserter::assert_equals(e_str, e_str));

    int e_int(0);
    int a_int(0);
    BOOST_CHECK(asserter::assert_equals(e_int, a_int));
    BOOST_CHECK(asserter::assert_equals(e_int, e_int));
}

BOOST_AUTO_TEST_CASE(assert_starts_with_returns_false_if_strings_start_differently) {
    SETUP_TEST_LOG("assert_starts_with_returns_false_if_strings_start_differently");

    std::string e_str("some");
    std::string a_str("asome string");

    using dogen::utility::test::asserter;
    BOOST_CHECK(!asserter::assert_starts_with(e_str, a_str));
}

BOOST_AUTO_TEST_CASE(assert_starts_with_returns_true_if_strings_start_the_same_way) {
    SETUP_TEST_LOG("assert_starts_with_returns_true_if_strings_start_the_same_way");

    std::string e_str("some");
    std::string a_str("some string");

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_starts_with(e_str, a_str));
    BOOST_CHECK(asserter::assert_starts_with(e_str, e_str));
}

BOOST_AUTO_TEST_CASE(assert_contains_returns_false_if_strings_are_not_related) {
    SETUP_TEST_LOG("assert_contains_returns_false_if_strings_are_not_related");

    std::string e_str("some");
    std::string a_str("unrelated string");

    using dogen::utility::test::asserter;
    BOOST_CHECK(!asserter::assert_contains(e_str, a_str));
}

BOOST_AUTO_TEST_CASE(assert_contains_returns_true_if_expected_is_a_subset_of_actual) {
    SETUP_TEST_LOG("assert_contains_returns_true_if_expected_is_a_subset_of_actual");

    std::string e_str("str");
    std::string a_str("some string");

    using dogen::utility::test::asserter;
    BOOST_CHECK(asserter::assert_contains(e_str, a_str));
    BOOST_CHECK(asserter::assert_contains(e_str, e_str));
}

BOOST_AUTO_TEST_SUITE_END()
