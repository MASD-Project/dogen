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
#include "dogen/yarn/types/all.hpp"
#include "dogen/yarn/io/all_io.hpp"
#include "dogen/yarn/test_data/all_td.hpp"
#include "dogen/yarn/serialization/all_ser.hpp"
#include "dogen/yarn/serialization/registrar_ser.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::yarn::register_types<Archive>(ar);
}

namespace {

const std::string empty;
const std::string test_module("yarn");
const std::string test_suite("serialization_tests");

}

using namespace dogen::yarn::helpers;
using namespace dogen::yarn::meta_model;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(serialization_tests)

BOOST_AUTO_TEST_CASE(validate_serialization) {
    SETUP_TEST_LOG("validate_serialization");

    roundtrip_type<object_generator>();
    roundtrip_type<origin_types_generator>();
    roundtrip_type<name_tree_generator>();
    roundtrip_type<node_generator>();
    roundtrip_type<attribute_generator>();
    roundtrip_type<name_generator>();
    roundtrip_type<builtin_generator>();
    roundtrip_type<enumerator_generator>();
    roundtrip_type<enumeration_generator>();
    roundtrip_type<module_generator>();
    roundtrip_type<object_generator>();
    roundtrip_type<object_template_generator>();
    roundtrip_type<endomodel_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
