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

#include "dogen/yarn/hash/helpers/node_hash.hpp"
#include "dogen/yarn/hash/helpers/indices_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_hash.hpp"
#include "dogen/yarn/hash/meta_model/name_hash.hpp"
#include "dogen/yarn/hash/meta_model/model_hash.hpp"
#include "dogen/yarn/hash/meta_model/module_hash.hpp"
#include "dogen/yarn/hash/meta_model/object_hash.hpp"
#include "dogen/yarn/hash/helpers/separators_hash.hpp"
#include "dogen/yarn/hash/meta_model/builtin_hash.hpp"
#include "dogen/yarn/hash/meta_model/element_hash.hpp"
#include "dogen/yarn/hash/meta_model/visitor_hash.hpp"
#include "dogen/yarn/hash/transforms/options_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_set_hash.hpp"
#include "dogen/yarn/hash/meta_model/artefact_hash.hpp"
#include "dogen/yarn/hash/meta_model/exomodel_hash.hpp"
#include "dogen/yarn/hash/meta_model/location_hash.hpp"
#include "dogen/yarn/hash/meta_model/attribute_hash.hpp"
#include "dogen/yarn/hash/meta_model/endomodel_hash.hpp"
#include "dogen/yarn/hash/meta_model/exception_hash.hpp"
#include "dogen/yarn/hash/meta_model/languages_hash.hpp"
#include "dogen/yarn/hash/meta_model/name_tree_hash.hpp"
#include "dogen/yarn/hash/meta_model/primitive_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_value_hash.hpp"
#include "dogen/yarn/hash/meta_model/enumerator_hash.hpp"
#include "dogen/yarn/hash/meta_model/text_model_hash.hpp"
#include "dogen/yarn/hash/meta_model/enumeration_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_actions_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_context_hash.hpp"
#include "dogen/yarn/hash/meta_model/letter_cases_hash.hpp"
#include "dogen/yarn/hash/meta_model/origin_types_hash.hpp"
#include "dogen/yarn/hash/transforms/configuration_hash.hpp"
#include "dogen/yarn/hash/helpers/transform_metrics_hash.hpp"
#include "dogen/yarn/hash/meta_model/object_template_hash.hpp"
#include "dogen/yarn/hash/meta_model/type_parameters_hash.hpp"
#include "dogen/yarn/hash/meta_model/facet_properties_hash.hpp"
#include "dogen/yarn/hash/helpers/decomposition_result_hash.hpp"
#include "dogen/yarn/hash/meta_model/element_archetype_hash.hpp"
#include "dogen/yarn/hash/meta_model/formatting_styles_hash.hpp"
#include "dogen/yarn/hash/meta_model/backend_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/locator_properties_hash.hpp"
#include "dogen/yarn/hash/helpers/mapping_set_repository_hash.hpp"
#include "dogen/yarn/hash/meta_model/artefact_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/archetype_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/orm_database_systems_hash.hpp"
#include "dogen/yarn/hash/meta_model/orm_model_properties_hash.hpp"
#include "dogen/yarn/hash/transforms/naming_configuration_hash.hpp"
#include "dogen/yarn/hash/meta_model/orm_module_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/orm_object_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/path_contribution_types_hash.hpp"
#include "dogen/yarn/hash/meta_model/model_segment_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/orm_attribute_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/orm_primitive_properties_hash.hpp"
#include "dogen/yarn/hash/transforms/exomodel_transform_types_hash.hpp"
#include "dogen/yarn/hash/transforms/formatting_configuration_hash.hpp"
#include "dogen/yarn/hash/meta_model/directory_structure_styles_hash.hpp"
#include "dogen/yarn/hash/meta_model/archetype_family_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/intra_backend_segment_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/denormalised_archetype_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/local_archetype_location_properties_hash.hpp"
#include "dogen/yarn/hash/meta_model/global_archetype_location_properties_hash.hpp"

#endif
