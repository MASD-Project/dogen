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
#ifndef DOGEN_UTILITY_TEST_ASSERTER_HPP
#define DOGEN_UTILITY_TEST_ASSERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/test/xml_serialization_helper.hpp"
#include "dogen/utility/test/file_asserter.hpp"

namespace dogen {
namespace utility {
namespace test {

class asserter {
public:
    asserter() = delete;
    asserter(const asserter&) = delete;
    ~asserter() = delete;
    asserter(asserter&&) = delete;
    asserter& operator=(const asserter&) = delete;

private:
    static dogen::utility::log::logger lg_;

public:
    static dogen::utility::log::logger logger() { return lg_; }

private:
    static bool handle_assert(const bool result, const std::string assertion);

public:
    /**
     * @brief Returns true if two objects are equal, false otherwise.
     */
    template<typename Entity>
    static bool assert_object(Entity expected, Entity actual) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) <<"expected: " << expected;
        BOOST_LOG_SEV(lg_, debug) <<"actual: " << actual;
        return handle_assert(expected == actual, "assert object");
    }

    /**
     * @brief Outputs the actual object and compares it to its serialised form.
     *
     * @param actual_path File name where to place the actual object
     * @param actual Actual object
     * @param expected_path Baseline for the object.
     */
    template<typename Entity>
    static bool assert_object(
        boost::filesystem::path expected_path,
        boost::filesystem::path actual_path,
        Entity actual) {

        using dogen::utility::test::xml_serialize;
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "writing actual: " << actual_path.string();
        xml_serialize(actual_path, actual);

        using dogen::utility::test::xml_deserialize;
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "reading expected: "
                                  << expected_path.string();

        const auto expected(xml_deserialize<Entity>(expected_path));
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "diff -u " << expected_path.string()
                                  << " " << actual_path.string();

        return assert_object(expected, actual);
    }

    /**
     * @brief Asserts that expected matches actual according to the
     * file asserter passed in.
     *
     * @param expected_path path to the expected file
     * @param actual_path path to the actual file
     * @param fa file asserter to use
     *
     * @pre Assumes that fa.is_assertable for both actual and expected
     * paths.
     */
    static bool assert_file(boost::filesystem::path expected_path,
        boost::filesystem::path actual_path, file_asserter& fa);

    /**
     * @brief Asserts that expected matches actual according to the
     * default file asserter.
     *
     * The default asserter is the byte-wise file asserter, which
     * performs a byte-wise comparison between the contents of the
     * files.
     *
     * @param expected_path path to the expected file
     * @param actual_path path to the actual file
     */
    static bool assert_file(boost::filesystem::path expected_path,
        boost::filesystem::path actual_path);

    /**
     * @brief Asserts that expected matches actual by ensuring they
     * have the same files and the files have the same contents.
     *
     * It uses the byte-wise file asserter to compare contents.
     */
    static bool assert_directory(boost::filesystem::path expected_path,
        boost::filesystem::path actual_path);

    /**
     * @brief Asserts that expected matches actual by ensuring they
     * have the same files and the files have the same contents.
     *
     * File assertions are done by trying each file asserter passed in
     * in turn. If none are assertable, the byte-wise file asserter is
     * used. If more than one are assertable, they are all used in the
     * order present in the vector until the first one fails.
     */
    static bool assert_directory(boost::filesystem::path expected_path,
        boost::filesystem::path actual_path,
        std::vector<file_asserter::shared_ptr> file_asserters);

    /**
     * @brief Returns true if expected matches equal via the equality
     * operator.
     *
     * The entity concept requires both the equality operator and the
     * inserter operator.
     *
     * @param expected object with the expected state
     * @param actual object that was actually generated
     */
    template<typename Entity>
    static bool assert_equals(const Entity& expected, const Entity& actual) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "expected: " << expected;
        BOOST_LOG_SEV(lg_, debug) << "actual: " << actual;
        return handle_assert(expected == actual, "assert equals");
    }

    /**
     * @brief Returns true if the actual string starts with the
     * content supplied by the expected string.
     */
    static bool assert_starts_with(const std::string expected,
        const std::string actual);

    /**
     * @brief Returns true if the actual string contains the expected
     * string.
     */
    static bool assert_contains(const std::string expected,
        const std::string actual);
};

} } }

#endif
