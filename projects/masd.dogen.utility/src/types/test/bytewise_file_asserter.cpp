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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.utility/types/test/bytewise_file_asserter.hpp"

namespace masd::dogen::utility::test {

bool bytewise_file_asserter::is_assertable(boost::filesystem::path) const {
    return true;
}

bool bytewise_file_asserter::
assert_file(boost::filesystem::path expected,
    boost::filesystem::path actual) const {
    using dogen::utility::filesystem::read_file_content;
    const std::string expected_content(read_file_content(expected));
    const std::string actual_content(read_file_content(actual));

    using namespace masd::dogen::utility::log;
    logger lg(logger_factory("utility.test.bytewise_file_asserter"));


    if (expected_content == actual_content) {
        BOOST_LOG_SEV(lg, debug)
            << "Byte-wise file asserter: contents are equal.";
        return true;
    }

    BOOST_LOG_SEV(lg, debug) << "Byte-wise file asserter: contents differ.";
    BOOST_LOG_SEV(lg, debug) << "expected content: " << expected_content;
    BOOST_LOG_SEV(lg, debug) << "actual content: " << actual_content;
    BOOST_LOG_SEV(lg, debug) << "diff -u " << expected.string() << " "
                             << actual.string();
    return false;
}

}
