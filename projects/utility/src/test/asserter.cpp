/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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

#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/io/set_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen/utility/test/bytewise_file_asserter.hpp"

using boost::filesystem::path;

namespace {

const std::string empty;
const std::string contains("assert contains");
const std::string starts_with("assert starts with");
const std::string directory("assert directory");
const std::string file("assert file");

std::set<path> items_in_directory(path top_dir) {
    std::set<path> r;

    using boost::filesystem::recursive_directory_iterator;
    for (recursive_directory_iterator end, dir(top_dir); dir != end; ++dir) {
        const path p(*dir);
        if (boost::filesystem::is_regular_file(p))
            r.insert(p);
    }
    return r;
}

std::set<std::string> normalise(path base, std::set<path> paths) {
    std::set<std::string> r;
    boost::copy(paths | boost::adaptors::transformed([&](path p) {
                using boost::replace_first_copy;
                return replace_first_copy(p.string(), base.string(), empty);
            }),
        std::inserter(r, r.end()));
    return r;
}

bool compare_paths(
    boost::tuple<path, std::set<path> > expected_tuple,
    boost::tuple<path, std::set<path> > actual_tuple) {

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

namespace dogen {
namespace utility {
namespace test {

dogen::utility::log::logger asserter::lg_(
    dogen::utility::log::logger_factory("asserter"));

bool asserter::handle_assert(const bool result, const std::string assertion) {
    using namespace dogen::utility::log;
    if (!result)
        BOOST_LOG_SEV(lg_, error) << assertion << " failed.";
    else
        BOOST_LOG_SEV(lg_, debug) << assertion << " succeeded.";
    return result;
}

bool asserter::assert_file(boost::filesystem::path expected_path,
    boost::filesystem::path actual_path, file_asserter& fa) {
    return handle_assert(fa.assert_file(expected_path, actual_path), file);
}

bool asserter::assert_file(boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {
    bytewise_file_asserter bfa;
    return assert_file(expected_path, actual_path, bfa);
}

bool asserter::assert_directory(boost::filesystem::path expected_path,
    boost::filesystem::path actual_path,
    std::vector<file_asserter::shared_ptr> file_asserters) {

    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg_, debug) << "expected directory: " << expected_path;
    BOOST_LOG_SEV(lg_, debug) << "actual directory: " << actual_path;

    auto lambda([](path d){
            return boost::make_tuple(d, items_in_directory(d));
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
            for (const auto fa : file_asserters) {
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

bool asserter::assert_directory(boost::filesystem::path expected_path,
    boost::filesystem::path actual_path) {
    std::vector<file_asserter::shared_ptr> v;
    return assert_directory(expected_path, actual_path, v);
}

bool asserter::
assert_starts_with(const std::string expected, const std::string actual) {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg_, debug) << "expected: " << expected;
    BOOST_LOG_SEV(lg_, debug) << "actual: " << actual;
    return handle_assert(boost::starts_with(actual, expected), starts_with);
}

bool asserter::
assert_contains(const std::string expected, const std::string actual) {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg_, debug) << "expected: " << expected;
    BOOST_LOG_SEV(lg_, debug) << "actual: " << actual;
    return handle_assert(boost::contains(actual, expected), contains);
}

} } }
