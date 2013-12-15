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
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/operation.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/enumerator.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/concept.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/io/generation_types_io.hpp"
#include "dogen/sml/io/nested_qname_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/operation_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/primitive_io.hpp"
#include "dogen/sml/io/enumerator_io.hpp"
#include "dogen/sml/io/enumeration_io.hpp"
#include "dogen/sml/io/value_object_io.hpp"
#include "dogen/sml/io/service_io.hpp"
#include "dogen/sml/io/module_io.hpp"
#include "dogen/sml/io/object_io.hpp"
#include "dogen/sml/io/concept_io.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/test_data/generation_types_td.hpp"
#include "dogen/sml/test_data/nested_qname_td.hpp"
#include "dogen/sml/test_data/property_td.hpp"
#include "dogen/sml/test_data/operation_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/primitive_td.hpp"
#include "dogen/sml/test_data/enumerator_td.hpp"
#include "dogen/sml/test_data/enumeration_td.hpp"
#include "dogen/sml/test_data/value_object_td.hpp"
#include "dogen/sml/test_data/service_td.hpp"
#include "dogen/sml/test_data/module_td.hpp"
#include "dogen/sml/test_data/object_td.hpp"
#include "dogen/sml/test_data/concept_td.hpp"
#include "dogen/sml/test_data/model_td.hpp"

namespace {

const std::string empty;
const std::string test_module("sml");
const std::string test_suite("move_copy_assignment_spec");

}

using namespace dogen::sml;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(move_assignment_copy)

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");

    test_move_assignment_copy<generation_types_generator>();
    test_move_assignment_copy<nested_qname_generator>();
    test_move_assignment_copy<property_generator>();
    test_move_assignment_copy<operation_generator>();
    test_move_assignment_copy<qname_generator>();
    test_move_assignment_copy<primitive_generator>();
    test_move_assignment_copy<enumerator_generator>();
    test_move_assignment_copy<enumeration_generator>();
    test_move_assignment_copy<value_object_generator>();
    test_move_assignment_copy<service_generator>();
    test_move_assignment_copy<module_generator>();
    test_move_assignment_copy<object_generator>();
    test_move_assignment_copy<concept_generator>();
    test_move_assignment_copy<model_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
