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
#define BOOST_RESULT_OF_USE_DECLTYPE
#include <set>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/string/differ.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/io/set_io.hpp"
#include "dogen.utility/types/io/vector_io.hpp"
#include "dogen.utility/types/serialization/xml_helper.hpp"
#include "dogen.utility/types/test/bytewise_file_asserter.hpp"
#include "dogen.utility/types/test/asserter.hpp"

using boost::filesystem::path;

namespace {

const std::string empty;
const std::string empty_marker("<empty_string>");
const std::string contains("assert contains");
const std::string starts_with("assert starts with");
const std::string directory("assert directory");
const std::string file("assert file");

std::set<std::string> normalise(const path& base, const std::set<path>& paths) {
    std::set<std::string> r;
    boost::copy(paths |
        boost::adaptors::transformed([&](path p) -> std::string {
                using boost::replace_first_copy;
                return replace_first_copy(p.string(), base.string(), empty);
            }),
        std::inserter(r, r.end()));
    return r;
}

bool compare_paths(
    const boost::tuple<path, std::set<path> >& expected_tuple,
    const boost::tuple<path, std::set<path> >& actual_tuple) {

    const auto a(normalise(actual_tuple.get<0>(), actual_tuple.get<1>()));
    const auto e(normalise(expected_tuple.get<0>(), expected_tuple.get<1>()));

    using namespace dogen::utility::log;
    auto lg(dogen::utility::test::asserter::logger());
    BOOST_LOG_SEV(lg, debug) << "actual paths: " << a;
    BOOST_LOG_SEV(lg, debug) << "expected paths: " << e;
    if (a != e) {
        std::vector<std::string> delta;
        boost::set_difference(a, e, std::back_inserter(delta));
        BOOST_LOG_SEV(lg, debug) << "extra files: " << delta;

        delta.clear();
        boost::set_difference(e, a, std::back_inserter(delta));
        BOOST_LOG_SEV(lg, debug) << "missing files: " << delta;

        return false;
    }

    BOOST_LOG_SEV(lg, debug) << "Actual and expected paths are the same.";
    return true;
}

}

namespace dogen::utility::test {

/*
 * Note: Log defined visibly by design. We are using this log on the
 * header file in order to support template based methods that need to
 * log.
 */
using namespace dogen::utility::log;
logger asserter::lg_(logger_factory("utility.test.asserter"));

bool asserter::handle_assert(const bool result, const std::string& assertion) {
    if (!result)
        BOOST_LOG_SEV(lg_, error) << assertion << " failed.";
    else
        BOOST_LOG_SEV(lg_, debug) << assertion << " succeeded.";
    return result;
}

void asserter::
log_strings(const std::string& expected, const std::string& actual) {
    BOOST_LOG_SEV(lg_, debug) << "expected: <start>"
                              << (expected.empty() ? empty_marker : expected)
                              << "<end>";
    BOOST_LOG_SEV(lg_, debug) << "actual: <start>"
                              << (actual.empty() ? empty_marker : actual)
                              << "<end>";
}

bool asserter::assert_file(const boost::filesystem::path& expected_path,
    const boost::filesystem::path& actual_path, file_asserter& fa) {
    return handle_assert(fa.assert_file(expected_path, actual_path), file);
}

bool asserter::assert_file(const boost::filesystem::path& expected_path,
    const boost::filesystem::path& actual_path) {
    bytewise_file_asserter bfa;
    return assert_file(expected_path, actual_path, bfa);
}

bool asserter::assert_directory(const boost::filesystem::path& expected_path,
    const boost::filesystem::path& actual_path,
    const std::vector<file_asserter::shared_ptr>& file_asserters) {

    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg_, debug) << "expected directory: " << expected_path;
    BOOST_LOG_SEV(lg_, debug) << "actual directory: " << actual_path;

    auto lambda([](path d){
            return boost::make_tuple(d, filesystem::find_files(d));
        });

    const auto expected(lambda(expected_path));
    const auto actual(lambda(actual_path));
    if (!compare_paths(expected, actual))
        return handle_assert(false, directory);

    bool r(true);
    auto cf([&](boost::tuple<path, path> tuple) {
            path e, a;
            boost::tie(e, a) = tuple;
            BOOST_LOG_SEV(lg_, debug) << "expected:" << e;
            BOOST_LOG_SEV(lg_, debug) << "actual:" << a;

            bool asserter_found(false);
            for (const auto& fa : file_asserters) {
                if (fa->is_assertable(e) && fa->is_assertable(a)) {
                    asserter_found = true;
                    if (!assert_file(e, a, *fa)) {
                        r = false;
                        break;
                    }
                }
            }

            if (!asserter_found) {
                if (!assert_file(e, a))
                    r = false;
            }
        });

    boost::for_each(boost::combine(expected.get<1>(), actual.get<1>()), cf);
    return handle_assert(r, directory);
}

bool asserter::assert_directory(const boost::filesystem::path& expected_path,
    const boost::filesystem::path& actual_path) {
    std::vector<file_asserter::shared_ptr> v;
    return assert_directory(expected_path, actual_path, v);
}

bool asserter::assert_equals_string(const std::string& expected,
    const std::string& actual) {
    /*
     * No need to log actual and expected as the differ will do that
     * for us.
     */
    BOOST_LOG_SEV(lg_, debug) << "diffing expected (a) against actual (b): ";
    string::differ::diff(expected, actual);
    return handle_assert(expected == actual, "assert equals");
}

bool asserter::
assert_starts_with(const std::string& expected, const std::string& actual) {
    log_strings(expected, actual);
    if (actual.empty() && !expected.empty())
        return handle_assert(false, contains);

    return handle_assert(boost::starts_with(actual, expected), starts_with);
}

bool asserter::
assert_contains(const std::string& expected, const std::string& actual) {
    log_strings(expected, actual);
    if (actual.empty() && !expected.empty())
        return handle_assert(false, contains);

    return handle_assert(boost::contains(actual, expected), contains);
}

}
