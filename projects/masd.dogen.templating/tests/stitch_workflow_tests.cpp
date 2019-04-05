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
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/test/asserter.hpp"
#include "masd.dogen.utility/types/test_data/stitch.hpp"
#include "masd.dogen.utility/types/test/exception_checkers.hpp"
#include "masd.dogen.templating/io/stitch/text_template_io.hpp"
#include "masd.dogen.templating/types/stitch/instantiation_error.hpp"
#include "masd.dogen.templating/types/stitch/workflow.hpp"

namespace {

const std::string empty;
const std::string test_module("masd.dogen.templating.tests");
const std::string test_suite("stitch_workflow_tests");

const std::string empty_template("Template has no content");
const bool compatibility_mode(true);

const std::string decoration_preamble_key(
    "masd.generation.decoration.preamble");
const std::string decoration_postamble_key(
    "masd.generation.decoration.postamble");
const auto kvps = std::unordered_map<std::string, std::string> {
    { decoration_preamble_key, empty },
    { decoration_postamble_key, empty }
};

const std::string decoration_preamble(
    R"(/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
)");

}

using masd::dogen::utility::test::contains_checker;
using masd::dogen::utility::test::asserter;
using masd::dogen::templating::stitch::instantiation_error;

BOOST_AUTO_TEST_SUITE(stitch_workflow_tests)

BOOST_AUTO_TEST_CASE(simple_template_results_in_expected_output) {
    SETUP_TEST_LOG_SOURCE("simple_template_results_in_expected_output");

    masd::dogen::templating::stitch::workflow w(compatibility_mode);
    using namespace masd::dogen::utility::test_data;
    w.execute(stitch::input_simple_template_stitch(), kvps);

    BOOST_CHECK(asserter::assert_file(
            stitch::expected_simple_template_stitch_cpp(),
            stitch::actual_simple_template_stitch_cpp()));
}

BOOST_AUTO_TEST_CASE(complex_template_results_in_expected_output) {
    SETUP_TEST_LOG_SOURCE("complex_template_results_in_expected_output");

    masd::dogen::templating::stitch::workflow w(compatibility_mode);
    using namespace masd::dogen::utility::test_data;

    const auto kvps = std::unordered_map<std::string, std::string> {
        { decoration_preamble_key, decoration_preamble },
        { decoration_postamble_key, empty }
    };
    w.execute(stitch::input_complex_template_stitch(), kvps);

    BOOST_CHECK(asserter::assert_file(
            stitch::expected_complex_template_stitch_cpp(),
            stitch::actual_complex_template_stitch_cpp()));
}

BOOST_AUTO_TEST_CASE(empty_template_throws) {
    SETUP_TEST_LOG_SOURCE("empty_template_throws");

    masd::dogen::templating::stitch::workflow w(compatibility_mode);
    using namespace masd::dogen::utility::test_data;
    contains_checker<masd::dogen::templating::stitch::instantiation_error>
        c(empty_template);
    BOOST_CHECK_EXCEPTION(w.execute(stitch::input_empty_template_stitch(), kvps),
        instantiation_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
