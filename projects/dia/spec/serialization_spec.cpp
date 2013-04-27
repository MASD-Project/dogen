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
#include "dogen/dia/types/all.hpp"
#include "dogen/dia/io/all_io.hpp"
#include "dogen/dia/test_data/all_td.hpp"
#include "dogen/dia/serialization/all_ser.hpp"
#include "dogen/dia/serialization/registrar_ser.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::dia::register_types<Archive>(ar);
}

namespace {

const std::string empty;
const std::string test_module("dia");
const std::string test_suite("serialization_spec");

}

using namespace dogen::dia;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(serialization)

BOOST_AUTO_TEST_CASE(validate_serialization) {
    SETUP_TEST_LOG("validate_serialization");

    rountrip_type<attribute_generator>();
    rountrip_type<boolean_generator>();
    rountrip_type<child_node_generator>();
    rountrip_type<color_generator>();
    rountrip_type<composite_generator>();
    rountrip_type<connection_generator>();
    rountrip_type<diagram_data_generator>();
    rountrip_type<diagram_generator>();
    rountrip_type<enumeration_generator>();
    rountrip_type<font_generator>();
    rountrip_type<integer_generator>();
    rountrip_type<layer_generator>();
    rountrip_type<object_generator>();
    rountrip_type<point_generator>();
    rountrip_type<real_generator>();
    rountrip_type<rectangle_generator>();
    rountrip_type<string_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
