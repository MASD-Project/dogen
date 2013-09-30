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
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/repository.hpp"
#include "dogen/sml/types/factory.hpp"
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
#include "dogen/sml/io/entity_io.hpp"
#include "dogen/sml/io/keyed_entity_io.hpp"
#include "dogen/sml/io/service_io.hpp"
#include "dogen/sml/io/module_io.hpp"
#include "dogen/sml/io/repository_io.hpp"
#include "dogen/sml/io/factory_io.hpp"
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
#include "dogen/sml/test_data/entity_td.hpp"
#include "dogen/sml/test_data/keyed_entity_td.hpp"
#include "dogen/sml/test_data/service_td.hpp"
#include "dogen/sml/test_data/module_td.hpp"
#include "dogen/sml/test_data/repository_td.hpp"
#include "dogen/sml/test_data/factory_td.hpp"
#include "dogen/sml/test_data/concept_td.hpp"
#include "dogen/sml/test_data/model_td.hpp"
#include "dogen/sml/hash/generation_types_hash.hpp"
#include "dogen/sml/hash/nested_qname_hash.hpp"
#include "dogen/sml/hash/property_hash.hpp"
#include "dogen/sml/hash/operation_hash.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/hash/primitive_hash.hpp"
#include "dogen/sml/hash/enumerator_hash.hpp"
#include "dogen/sml/hash/enumeration_hash.hpp"
#include "dogen/sml/hash/value_object_hash.hpp"
#include "dogen/sml/hash/entity_hash.hpp"
#include "dogen/sml/hash/keyed_entity_hash.hpp"
#include "dogen/sml/hash/service_hash.hpp"
#include "dogen/sml/hash/module_hash.hpp"
#include "dogen/sml/hash/repository_hash.hpp"
#include "dogen/sml/hash/factory_hash.hpp"
#include "dogen/sml/hash/concept_hash.hpp"
#include "dogen/sml/hash/model_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("sml");
const std::string test_suite("hashing_spec");

}

using namespace dogen::sml;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(hashing)

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");

    test_hashing<generation_types_generator>();
    // FIXME: bug in composition?
    // test_hashing<nested_qname_generator>();
    test_hashing<property_generator>();
    test_hashing<operation_generator>();
    test_hashing<qname_generator>();
    test_hashing<primitive_generator>();
    test_hashing<enumerator_generator>();
    test_hashing<enumeration_generator>();
    test_hashing<value_object_generator>();
    test_hashing<entity_generator>();
    test_hashing<keyed_entity_generator>();
    test_hashing<service_generator>();
    test_hashing<module_generator>();
    test_hashing<repository_generator>();
    test_hashing<factory_generator>();
    test_hashing<concept_generator>();
    test_hashing<model_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
