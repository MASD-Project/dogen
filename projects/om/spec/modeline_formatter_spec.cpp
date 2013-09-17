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
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/om/types/modeline.hpp"
#include "dogen/om/types/all.hpp"
#include "dogen/om/io/all_io.hpp"
#include "dogen/om/test_data/all_td.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string empty;
const std::string test_module("om");
const std::string test_suite("modeline_formatter_spec");

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

dogen::om::modeline_field
make_field(const std::string& name, const std::string& value) {
    dogen::om::modeline_field r;
    r.name(name);
    r.value(value);
    return r;
}

std::list<dogen::om::modeline_field> mock_emacs_fields() {
    std::list<dogen::om::modeline_field> r;

    r.push_back(make_field("mode", "c++"));
    r.push_back(make_field("tab-width", "4"));
    r.push_back(make_field("indent-tabs-mode", "nil"));
    r.push_back(make_field("c-basic-offset", "4"));

    return r;
}

dogen::om::modeline mock_emacs_modeline(const dogen::om::modeline_locations l) {
    dogen::om::modeline r;
    r.editor(dogen::om::editors::emacs);
    r.location(l);
    r.fields(mock_emacs_fields());
    return r;
}

std::list<dogen::om::modeline_field> mock_vim_fields() {
    std::list<dogen::om::modeline_field> r;

    r.push_back(make_field("ft", "cpp"));
    r.push_back(make_field("ts", "4"));
    r.push_back(make_field("sw", "4"));
    r.push_back(make_field("sts", "4"));
    r.push_back(make_field("nowrap:", ""));
    r.push_back(make_field("cindent:", ""));

    return r;
}

dogen::om::modeline mock_vim_modeline(const dogen::om::modeline_locations l) {
    dogen::om::modeline r;
    r.editor(dogen::om::editors::vim);
    r.location(l);
    r.fields(mock_vim_fields());
    return r;
}

}

using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(modeline_formatter)

BOOST_AUTO_TEST_CASE(emacs_top_modeline_results_in_expected_modeline) {
    SETUP_TEST_LOG_SOURCE("emacs_top_modeline_results_in_expected_modeline");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_emacs_modeline(dogen::om::modeline_locations::top));
    dogen::om::modeline_formatter f;
    const auto r(f.format(m));
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << emacs_top_modeline;
    BOOST_CHECK(r == emacs_top_modeline);
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(emacs_bottom_modeline_results_in_expected_modeline) {
    SETUP_TEST_LOG_SOURCE("emacs_bottom_modeline_results_in_expected_modeline");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m(mock_emacs_modeline(dogen::om::modeline_locations::bottom));
    dogen::om::modeline_formatter f;
    const auto r(f.format(m));
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << emacs_bottom_modeline;
    BOOST_CHECK(r == emacs_bottom_modeline);
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(vim_top_modeline_results_in_expected_modeline) {
    SETUP_TEST_LOG_SOURCE("vim_top_modeline_results_in_expected_modeline");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto m0(mock_vim_modeline(dogen::om::modeline_locations::top));
    dogen::om::modeline_formatter f;
    const auto r0(f.format(m0));
    BOOST_LOG_SEV(lg, debug) << "actual: " << r0;
    BOOST_LOG_SEV(lg, debug) << "expected: " << vim_modeline;
    BOOST_CHECK(r0 == vim_modeline);

    const auto m1(mock_vim_modeline(dogen::om::modeline_locations::bottom));
    const auto r1(f.format(m1));
    BOOST_LOG_SEV(lg, debug) << "actual: " << r1;
    BOOST_LOG_SEV(lg, debug) << "expected: " << vim_modeline;
    BOOST_CHECK(r1 == vim_modeline);

    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(modeline_with_unsupported_editor_throws) {
    SETUP_TEST_LOG_SOURCE("modeline_with_unsupported_editor_throws");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    auto m(mock_emacs_modeline(dogen::om::modeline_locations::bottom));
    m.editor(dogen::om::editors::invalid);

    using dogen::om::formatting_error;
    contains_checker<formatting_error> c(unsupported_editor_message);

    dogen::om::modeline_formatter f;
    BOOST_CHECK_EXCEPTION(f.format(m), formatting_error, c);
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_SUITE_END()
