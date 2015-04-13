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
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/formatters/io/file_io.hpp"
#include "dogen/stitch/io/text_template_io.hpp"
#include "dogen/stitch/types/formatting_error.hpp"
#include "dogen/stitch/types/formatter.hpp"

namespace {

const std::string empty;
const std::string single_line_text_only("This is a template");

const std::string test_module("stitch");
const std::string test_suite("formatter_spec");

dogen::formatters::file format(const dogen::stitch::text_template& tt) {
    dogen::stitch::formatter f;
    return f.format(tt);
}

}

using dogen::utility::test::contains_checker;
using dogen::stitch::formatting_error;

BOOST_AUTO_TEST_SUITE(formatter)

BOOST_AUTO_TEST_CASE(empty_text_template_results_in_empty_file) {
    SETUP_TEST_LOG_SOURCE("empty_text_template_results_in_empty_file");

    dogen::stitch::text_template tt;
    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    BOOST_CHECK(r.content().empty());
}

BOOST_AUTO_TEST_SUITE_END()
