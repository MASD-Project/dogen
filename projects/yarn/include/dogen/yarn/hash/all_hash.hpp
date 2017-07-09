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
#ifndef DOGEN_YARN_HASH_ALL_HASH_HPP
#define DOGEN_YARN_HASH_ALL_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/hash/node_hash.hpp"
#include "dogen/yarn/hash/model_hash.hpp"
#include "dogen/yarn/hash/module_hash.hpp"
#include "dogen/yarn/hash/object_hash.hpp"
#include "dogen/yarn/hash/builtin_hash.hpp"
#include "dogen/yarn/hash/concept_hash.hpp"
#include "dogen/yarn/hash/element_hash.hpp"
#include "dogen/yarn/hash/mapping_hash.hpp"
#include "dogen/yarn/hash/visitor_hash.hpp"
#include "dogen/yarn/hash/location_hash.hpp"
#include "dogen/yarn/hash/attribute_hash.hpp"
#include "dogen/yarn/hash/exception_hash.hpp"
#include "dogen/yarn/hash/languages_hash.hpp"
#include "dogen/yarn/hash/name_tree_hash.hpp"
#include "dogen/yarn/hash/primitive_hash.hpp"
#include "dogen/yarn/hash/enumerator_hash.hpp"
#include "dogen/yarn/hash/separators_hash.hpp"
#include "dogen/yarn/hash/enumeration_hash.hpp"
#include "dogen/yarn/hash/mapping_set_hash.hpp"
#include "dogen/yarn/hash/letter_cases_hash.hpp"
#include "dogen/yarn/hash/object_types_hash.hpp"
#include "dogen/yarn/hash/origin_types_hash.hpp"
#include "dogen/yarn/hash/mapping_value_hash.hpp"
#include "dogen/yarn/hash/helpers/indices_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_hash.hpp"
#include "dogen/yarn/hash/mapping_actions_hash.hpp"
#include "dogen/yarn/hash/mapping_context_hash.hpp"
#include "dogen/yarn/hash/type_parameters_hash.hpp"
#include "dogen/yarn/hash/formatting_styles_hash.hpp"
#include "dogen/yarn/hash/element_properties_hash.hpp"
#include "dogen/yarn/hash/intermediate_model_hash.hpp"
#include "dogen/yarn/hash/artefact_properties_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_set_hash.hpp"
#include "dogen/yarn/hash/orm_database_systems_hash.hpp"
#include "dogen/yarn/hash/orm_model_properties_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_value_hash.hpp"
#include "dogen/yarn/hash/orm_module_properties_hash.hpp"
#include "dogen/yarn/hash/orm_object_properties_hash.hpp"
#include "dogen/yarn/hash/mapping_set_repository_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_actions_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_context_hash.hpp"
#include "dogen/yarn/hash/orm_attribute_properties_hash.hpp"
#include "dogen/yarn/hash/orm_primitive_properties_hash.hpp"
#include "dogen/yarn/hash/helpers/decomposition_result_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_set_repository_hash.hpp"
#include "dogen/yarn/hash/transforms/code_generation_output_hash.hpp"
#include "dogen/yarn/hash/transforms/exogenous_transform_types_hash.hpp"

#endif
