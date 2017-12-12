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
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/wale/types/workflow.hpp"

namespace {

const std::string test_module("wale");
const std::string test_suite("workflow_tests");

}

BOOST_AUTO_TEST_SUITE(workflow_tests)

BOOST_AUTO_TEST_CASE(wale_templates_in_data_produce_expected_instantiation) {
    SETUP_TEST_LOG_SOURCE("wale_templates_in_data_produce_expected_instantiation");

    const auto kvps = std::unordered_map<std::string, std::string> {
        {"class.simple_name", "some_class"}
    };

    dogen::wale::workflow w;
    w.execute("cpp_artefact_formatter_header.wale", kvps);
    BOOST_TEST_CHECKPOINT("Instantiated template.");
}

BOOST_AUTO_TEST_SUITE_END()
