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
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/om/types/all.hpp"
#include "dogen/om/io/all_io.hpp"
#include "dogen/om/test_data/all_td.hpp"

namespace {

const std::string test_module("om");
const std::string test_suite("cpp_include_formatter_spec");
const dogen::om::cpp_includes empty_includes = dogen::om::cpp_includes();

const std::string with_includes(R"(#include <win32/system_inc_1>
#include <unix/system_inc_2>
#include "user_inc_1"
#include "user_inc_2"
)");

}

using namespace dogen::om;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(cpp_include_formatter)

BOOST_AUTO_TEST_CASE(non_empty_includes_produces_expected_preprocessor_includes) {
    SETUP_TEST_LOG_SOURCE("non_empty_includes_produces_expected_preprocessor_includes");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    dogen::om::cpp_includes i;
    i.system().push_back("win32/system_inc_1"); // FIXME
    i.system().push_back("unix/system_inc_2");
    i.user().push_back("user_inc_1");
    i.user().push_back("user_inc_2");

    std::ostringstream s;
    dogen::om::cpp_include_formatter f;
    f.format(s, i);
    const auto r(s.str());
    BOOST_CHECK(r == with_includes);
    BOOST_LOG_SEV(lg, debug) << "expected: " << with_includes;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(empty_includes_produces_no_preprocessor_includes) {
    SETUP_TEST_LOG_SOURCE("empty_includes_produces_no_preprocessor_includes");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    std::ostringstream s;
    dogen::om::cpp_include_formatter f;
    f.format(s, empty_includes);
    const auto r(s.str());
    BOOST_CHECK(r.empty());
    BOOST_LOG_SEV(lg, debug) << "expected: <empty>";
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_SUITE_END()
