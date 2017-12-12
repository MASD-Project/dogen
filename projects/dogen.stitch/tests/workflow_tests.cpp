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
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/seam.hpp"
#include "dogen/utility/test_data/stitch.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/stitch/io/text_template_io.hpp"
#include "dogen/stitch/types/instantiation_error.hpp"
#include "dogen/stitch/types/workflow.hpp"

namespace {

const std::string empty;
const std::string test_module("stitch");
const std::string test_suite("workflow_tests");

const std::string empty_template("Template has no content");
const bool compatibility_mode(false);

}

using dogen::utility::test::contains_checker;
using dogen::utility::test::asserter;
using dogen::stitch::instantiation_error;

BOOST_AUTO_TEST_SUITE(workflow_tests)

BOOST_AUTO_TEST_CASE(simple_template_results_in_expected_output) {
    SETUP_TEST_LOG_SOURCE("simple_template_results_in_expected_output");

    dogen::stitch::workflow w(compatibility_mode);
    using namespace dogen::utility::test_data;
    w.execute(stitch::input_simple_template_stitch());

    BOOST_CHECK(asserter::assert_file(
            seam::expected_simple_template_stitch_cpp(),
            seam::actual_simple_template_stitch_cpp()));
}

BOOST_AUTO_TEST_CASE(complex_template_results_in_expected_output) {
    SETUP_TEST_LOG_SOURCE("complex_template_results_in_expected_output");

    dogen::stitch::workflow w(compatibility_mode);
    using namespace dogen::utility::test_data;
    w.execute(stitch::input_complex_template_stitch());

    BOOST_CHECK(asserter::assert_file(
            seam::expected_complex_template_stitch_cpp(),
            seam::actual_complex_template_stitch_cpp()));
}

BOOST_AUTO_TEST_CASE(empty_template_throws) {
    SETUP_TEST_LOG_SOURCE("empty_template_throws");

    dogen::stitch::workflow w(compatibility_mode);
    using namespace dogen::utility::test_data;
    contains_checker<dogen::stitch::instantiation_error> c(empty_template);
    BOOST_CHECK_EXCEPTION(w.execute(stitch::input_empty_template_stitch());,
        instantiation_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
