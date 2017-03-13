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
#ifndef DOGEN_YARN_SERIALIZATION_ALL_SER_HPP
#define DOGEN_YARN_SERIALIZATION_ALL_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/serialization/name_ser.hpp"
#include "dogen/yarn/serialization/node_ser.hpp"
#include "dogen/yarn/serialization/model_ser.hpp"
#include "dogen/yarn/serialization/module_ser.hpp"
#include "dogen/yarn/serialization/object_ser.hpp"
#include "dogen/yarn/serialization/builtin_ser.hpp"
#include "dogen/yarn/serialization/concept_ser.hpp"
#include "dogen/yarn/serialization/element_ser.hpp"
#include "dogen/yarn/serialization/indices_ser.hpp"
#include "dogen/yarn/serialization/mapping_ser.hpp"
#include "dogen/yarn/serialization/visitor_ser.hpp"
#include "dogen/yarn/serialization/location_ser.hpp"
#include "dogen/yarn/serialization/attribute_ser.hpp"
#include "dogen/yarn/serialization/exception_ser.hpp"
#include "dogen/yarn/serialization/languages_ser.hpp"
#include "dogen/yarn/serialization/name_tree_ser.hpp"
#include "dogen/yarn/serialization/primitive_ser.hpp"
#include "dogen/yarn/serialization/descriptor_ser.hpp"
#include "dogen/yarn/serialization/enumerator_ser.hpp"
#include "dogen/yarn/serialization/separators_ser.hpp"
#include "dogen/yarn/serialization/enumeration_ser.hpp"
#include "dogen/yarn/serialization/mapping_set_ser.hpp"
#include "dogen/yarn/serialization/letter_cases_ser.hpp"
#include "dogen/yarn/serialization/object_types_ser.hpp"
#include "dogen/yarn/serialization/origin_types_ser.hpp"
#include "dogen/yarn/serialization/mapping_value_ser.hpp"
#include "dogen/yarn/serialization/mapping_actions_ser.hpp"
#include "dogen/yarn/serialization/mapping_context_ser.hpp"
#include "dogen/yarn/serialization/type_parameters_ser.hpp"
#include "dogen/yarn/serialization/intermediate_model_ser.hpp"
#include "dogen/yarn/serialization/decomposition_result_ser.hpp"
#include "dogen/yarn/serialization/orm_database_systems_ser.hpp"
#include "dogen/yarn/serialization/mapping_set_repository_ser.hpp"
#include "dogen/yarn/serialization/orm_model_configuration_ser.hpp"
#include "dogen/yarn/serialization/orm_module_configuration_ser.hpp"
#include "dogen/yarn/serialization/orm_object_configuration_ser.hpp"
#include "dogen/yarn/serialization/orm_attribute_configuration_ser.hpp"
#include "dogen/yarn/serialization/orm_primitive_configuration_ser.hpp"
#include "dogen/yarn/serialization/intermediate_model_repository_ser.hpp"

#endif
