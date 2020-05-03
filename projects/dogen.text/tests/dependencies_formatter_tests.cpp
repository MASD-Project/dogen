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
#include "dogen.text/types/formatters/dependencies_formatter.hpp"
#include "dogen.text/types/formatters/indent_filter.hpp"
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include <boost/test/unit_test.hpp>
#include <sstream>

namespace {

const std::string test_module("dogen.text.tests");
const std::string test_suite("dependencies_formatter_tests");
const std::string empty;

const std::string csharp_usings(
    R"(using System
using System.Linq
using ICSharpCode.NRefactory.Editor
)");

const std::string cpp_includes_with_top_modeline(
    R"(#include "user_inc_1"
#include "user_inc_2"
#include <unix/system_inc_2>
#include <win32/system_inc_1>
)");

using dogen::logical::entities::technical_space;
using dogen::text::formatters::dependencies_formatter;
using dogen::text::formatters::indent_filter;
std::string format(const technical_space ts,
                   const std::list<std::string> &deps) {
  dependencies_formatter f;
  std::ostringstream s;

  boost::iostreams::filtering_ostream fo;
  indent_filter::push(fo, 4);
  fo.push(s);

  f.format(fo, ts, deps);
  return s.str();
}

}

using namespace dogen::utility::test;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(dependencies_formatter_tests)

BOOST_AUTO_TEST_CASE(csharp_non_empty_dependencies_are_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_non_empty_dependencies_are_formatted_correctly");

    const std::list<std::string> deps {
        "System", "System.Linq",
        "ICSharpCode.NRefactory.Editor"
    };

    const auto &e(csharp_usings);
    const auto a(format(technical_space::csharp, deps));
    BOOST_CHECK(asserter::assert_equals_string(e, a));
}

BOOST_AUTO_TEST_CASE(cpp_non_empty_dependencies_are_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_non_empty_dependencies_are_formatted_correctly");

    const std::list<std::string> deps {
        "\"user_inc_1\"",
        "\"user_inc_2\"",
        "<unix/system_inc_2>",
        "<win32/system_inc_1>"
    };

    const auto& e(cpp_includes_with_top_modeline);
    const auto a(format(technical_space::cpp, deps));
    BOOST_CHECK(asserter::assert_equals_string(e, a));
}

BOOST_AUTO_TEST_CASE(empty_dependencies_produce_no_output) {
    SETUP_TEST_LOG_SOURCE("empty_dependencies_produce_no_output");

    const std::list<std::string> deps;
    const std::string e;
    const auto cpp_a(format(technical_space::cpp, deps));
    BOOST_CHECK(asserter::assert_equals_string(e, cpp_a));

    const auto csharp_a(format(technical_space::csharp, deps));
    BOOST_CHECK(asserter::assert_equals_string(e, csharp_a));
}

BOOST_AUTO_TEST_SUITE_END()
