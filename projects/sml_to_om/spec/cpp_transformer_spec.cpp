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
#include "dogen/sml_to_om/types/all.hpp"
#include "dogen/sml_to_om/io/all_io.hpp"
#include "dogen/sml_to_om/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("sml_to_om");
const std::string test_suite("cpp_transformer_spec");

}

using namespace dogen::sml_to_om;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(cpp_transformer)

BOOST_AUTO_TEST_CASE(transforming_empty_model_results_in_expected_cpp_project) {
    SETUP_TEST_LOG("transforming_empty_model_results_in_expected_cpp_project");

}

BOOST_AUTO_TEST_SUITE_END()
