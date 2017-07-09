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
#ifndef DOGEN_YARN_IO_ALL_IO_HPP
#define DOGEN_YARN_IO_ALL_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/io/node_io.hpp"
#include "dogen/yarn/io/model_io.hpp"
#include "dogen/yarn/io/module_io.hpp"
#include "dogen/yarn/io/object_io.hpp"
#include "dogen/yarn/io/builtin_io.hpp"
#include "dogen/yarn/io/concept_io.hpp"
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/yarn/io/mapping_io.hpp"
#include "dogen/yarn/io/visitor_io.hpp"
#include "dogen/yarn/io/location_io.hpp"
#include "dogen/yarn/io/attribute_io.hpp"
#include "dogen/yarn/io/exception_io.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/io/name_tree_io.hpp"
#include "dogen/yarn/io/primitive_io.hpp"
#include "dogen/yarn/io/enumerator_io.hpp"
#include "dogen/yarn/io/separators_io.hpp"
#include "dogen/yarn/io/enumeration_io.hpp"
#include "dogen/yarn/io/mapping_set_io.hpp"
#include "dogen/yarn/io/letter_cases_io.hpp"
#include "dogen/yarn/io/object_types_io.hpp"
#include "dogen/yarn/io/origin_types_io.hpp"
#include "dogen/yarn/io/mapping_value_io.hpp"
#include "dogen/yarn/io/helpers/indices_io.hpp"
#include "dogen/yarn/io/helpers/mapping_io.hpp"
#include "dogen/yarn/io/mapping_actions_io.hpp"
#include "dogen/yarn/io/mapping_context_io.hpp"
#include "dogen/yarn/io/type_parameters_io.hpp"
#include "dogen/yarn/io/formatting_styles_io.hpp"
#include "dogen/yarn/io/element_properties_io.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/io/artefact_properties_io.hpp"
#include "dogen/yarn/io/helpers/mapping_set_io.hpp"
#include "dogen/yarn/io/orm_database_systems_io.hpp"
#include "dogen/yarn/io/orm_model_properties_io.hpp"
#include "dogen/yarn/io/helpers/mapping_value_io.hpp"
#include "dogen/yarn/io/orm_module_properties_io.hpp"
#include "dogen/yarn/io/orm_object_properties_io.hpp"
#include "dogen/yarn/io/mapping_set_repository_io.hpp"
#include "dogen/yarn/io/helpers/mapping_actions_io.hpp"
#include "dogen/yarn/io/helpers/mapping_context_io.hpp"
#include "dogen/yarn/io/orm_attribute_properties_io.hpp"
#include "dogen/yarn/io/orm_primitive_properties_io.hpp"
#include "dogen/yarn/io/helpers/decomposition_result_io.hpp"
#include "dogen/yarn/io/helpers/mapping_set_repository_io.hpp"
#include "dogen/yarn/io/transforms/code_generation_output_io.hpp"
#include "dogen/yarn/io/transforms/exogenous_transform_types_io.hpp"

#endif
