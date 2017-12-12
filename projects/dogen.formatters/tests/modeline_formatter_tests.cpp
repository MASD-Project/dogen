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
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/formatters/types/modeline.hpp"
#include "dogen/formatters/types/modeline_formatter.hpp"
#include "dogen/formatters/types/formatting_error.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string empty;
const std::string test_module("formatters");
const std::string test_suite("modeline_formatter_tests");

const std::string unsupported_editor_message("Modeline is not supported");
const std::string emacs_top_modeline(
    "-*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-");
const std::string emacs_bottom_modeline(R"(Local variables:
mode: c++
tab-width: 4
indent-tabs-mode: nil
c-basic-offset: 4
End:
)");

const std::string vim_modeline(
    "vim: set ft=cpp ts=4 sw=4 sts=4 nowrap: cindent:");

dogen::formatters::modeline_field
make_field(const std::string& name, const std::string& value) {
    dogen::formatters::modeline_field r;
    r.name(name);
    r.value(value);
    return r;
}

std::list<dogen::formatters::modeline_field> mock_emacs_fields() {
    std::list<dogen::formatters::modeline_field> r;

    r.push_back(make_field("mode", "c++"));
    r.push_back(make_field("tab-width", "4"));
    r.push_back(make_field("indent-tabs-mode", "nil"));
    r.push_back(make_field("c-basic-offset", "4"));

    return r;
}

dogen::formatters::modeline mock_emacs_modeline(const dogen::formatters::modeline_locations l) {
    dogen::formatters::modeline r;
    r.editor(dogen::formatters::editors::emacs);
    r.location(l);
    r.fields(mock_emacs_fields());
    return r;
}

std::list<dogen::formatters::modeline_field> mock_vim_fields() {
    std::list<dogen::formatters::modeline_field> r;

    r.push_back(make_field("ft", "cpp"));
    r.push_back(make_field("ts", "4"));
    r.push_back(make_field("sw", "4"));
    r.push_back(make_field("sts", "4"));
    r.push_back(make_field("nowrap:", ""));
    r.push_back(make_field("cindent:", ""));

    return r;
}

dogen::formatters::modeline mock_vim_modeline(const dogen::formatters::modeline_locations l) {
    dogen::formatters::modeline r;
    r.editor(dogen::formatters::editors::vim);
    r.location(l);
    r.fields(mock_vim_fields());
    return r;
}

std::string
format(const dogen::formatters::modeline_formatter& f, const dogen::formatters::modeline& m) {
    std::ostringstream s;
    f.format(s, m);
    return s.str();
}

}

using namespace dogen::utility::test;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(modeline_formatter_tests)

BOOST_AUTO_TEST_CASE(emacs_top_modeline_results_in_expected_modeline) {
    SETUP_TEST_LOG_SOURCE("emacs_top_modeline_results_in_expected_modeline");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_emacs_modeline(dogen::formatters::modeline_locations::top));
    dogen::formatters::modeline_formatter f;
    const auto r(format(f, m));
    BOOST_CHECK(asserter::assert_equals_marker(emacs_top_modeline, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(emacs_bottom_modeline_results_in_expected_modeline) {
    SETUP_TEST_LOG_SOURCE("emacs_bottom_modeline_results_in_expected_modeline");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_emacs_modeline(dogen::formatters::modeline_locations::bottom));
    dogen::formatters::modeline_formatter f;
    const auto r(format(f, m));
    BOOST_CHECK(asserter::assert_equals_marker(emacs_bottom_modeline, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(vim_top_modeline_results_in_expected_modeline) {
    SETUP_TEST_LOG_SOURCE("vim_top_modeline_results_in_expected_modeline");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m0(mock_vim_modeline(dogen::formatters::modeline_locations::top));
    dogen::formatters::modeline_formatter f;
    const auto r0(format(f, m0));
    BOOST_CHECK(asserter::assert_equals_marker(vim_modeline, r0));

    const auto m1(mock_vim_modeline(dogen::formatters::modeline_locations::bottom));
    const auto r1(format(f, m1));
    BOOST_CHECK(asserter::assert_equals_marker(vim_modeline, r1));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(modeline_with_unsupported_editor_throws) {
    SETUP_TEST_LOG_SOURCE("modeline_with_unsupported_editor_throws");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    auto m(mock_emacs_modeline(dogen::formatters::modeline_locations::bottom));
    m.editor(dogen::formatters::editors::invalid);

    using dogen::formatters::formatting_error;
    contains_checker<formatting_error> c(unsupported_editor_message);

    dogen::formatters::modeline_formatter f;
    BOOST_CHECK_EXCEPTION(format(f, m), formatting_error, c);
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_SUITE_END()
