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
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/repository.hpp"
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
#include "dogen/sml/io/entity_io.hpp"
#include "dogen/sml/io/service_io.hpp"
#include "dogen/sml/io/module_io.hpp"
#include "dogen/sml/io/repository_io.hpp"
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
#include "dogen/sml/test_data/entity_td.hpp"
#include "dogen/sml/test_data/service_td.hpp"
#include "dogen/sml/test_data/module_td.hpp"
#include "dogen/sml/test_data/repository_td.hpp"
#include "dogen/sml/test_data/object_td.hpp"
#include "dogen/sml/test_data/concept_td.hpp"
#include "dogen/sml/test_data/model_td.hpp"
#include "dogen/sml/serialization/generation_types_ser.hpp"
#include "dogen/sml/serialization/nested_qname_ser.hpp"
#include "dogen/sml/serialization/property_ser.hpp"
#include "dogen/sml/serialization/operation_ser.hpp"
#include "dogen/sml/serialization/qname_ser.hpp"
#include "dogen/sml/serialization/primitive_ser.hpp"
#include "dogen/sml/serialization/enumerator_ser.hpp"
#include "dogen/sml/serialization/enumeration_ser.hpp"
#include "dogen/sml/serialization/value_object_ser.hpp"
#include "dogen/sml/serialization/entity_ser.hpp"
#include "dogen/sml/serialization/service_ser.hpp"
#include "dogen/sml/serialization/module_ser.hpp"
#include "dogen/sml/serialization/repository_ser.hpp"
#include "dogen/sml/serialization/object_ser.hpp"
#include "dogen/sml/serialization/concept_ser.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/sml/serialization/registrar_ser.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::sml::register_types<Archive>(ar);
}

namespace {

const std::string empty;
const std::string test_module("sml");
const std::string test_suite("serialization_spec");

}

using namespace dogen::sml;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(serialization)

BOOST_AUTO_TEST_CASE(validate_serialization) {
    SETUP_TEST_LOG("validate_serialization");

    rountrip_type<generation_types_generator>();
    rountrip_type<nested_qname_generator>();
    rountrip_type<property_generator>();
    rountrip_type<operation_generator>();
    rountrip_type<qname_generator>();
    rountrip_type<primitive_generator>();
    rountrip_type<enumerator_generator>();
    rountrip_type<enumeration_generator>();
    rountrip_type<value_object_generator>();
    rountrip_type<entity_generator>();
    rountrip_type<service_generator>();
    rountrip_type<module_generator>();
    rountrip_type<repository_generator>();
    rountrip_type<object_generator>();
    rountrip_type<concept_generator>();
    rountrip_type<model_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
