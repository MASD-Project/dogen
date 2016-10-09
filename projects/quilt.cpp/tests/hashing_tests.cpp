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
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/quilt.cpp/types/all.hpp"
#include "dogen/quilt.cpp/io/all_io.hpp"
#include "dogen/quilt.cpp/hash/all_hash.hpp"
#include "dogen/quilt.cpp/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("quilt.cpp");
const std::string test_suite("hashing_tests");

}

using namespace dogen::quilt::cpp;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(hashing_tests)

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");

    test_hashing<formattables::model_generator>();
    test_hashing<formattables::formattable_generator>();
    test_hashing<formattables::opaque_configuration_generator>();
    test_hashing<formattables::element_configuration_generator>();
    test_hashing<formattables::global_enablement_configuration_generator>();
    test_hashing<formattables::formatter_configuration_generator>();
    test_hashing<formattables::facet_configuration_generator>();
    test_hashing<formattables::helper_configuration_generator>();
    test_hashing<formattables::aspect_configuration_generator>();
    test_hashing<formattables::helper_descriptor_generator>();
    test_hashing<formattables::decoration_profile_generator>();
    test_hashing<formattables::facet_profile_generator>();
    test_hashing<formattables::formatter_profile_generator>();
    test_hashing<formattables::profile_types_generator>();
    test_hashing<formattables::streaming_configuration_generator>();
    test_hashing<annotations::path_annotations_generator>();
    test_hashing<annotations::aspect_annotations_generator>();
    test_hashing<annotations::inclusion_directive_annotations_generator>();
        test_hashing<fabric::registrar_generator>();
    test_hashing<fabric::cmakelists_generator>();
    test_hashing<fabric::odb_options_generator>();
    test_hashing<fabric::master_header_generator>();
    test_hashing<fabric::forward_declarations_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
