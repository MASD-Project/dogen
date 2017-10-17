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

#include "dogen/yarn/serialization/helpers/node_ser.hpp"
#include "dogen/yarn/serialization/helpers/indices_ser.hpp"
#include "dogen/yarn/serialization/helpers/mapping_ser.hpp"
#include "dogen/yarn/serialization/meta_model/name_ser.hpp"
#include "dogen/yarn/serialization/meta_model/model_ser.hpp"
#include "dogen/yarn/serialization/meta_model/module_ser.hpp"
#include "dogen/yarn/serialization/meta_model/object_ser.hpp"
#include "dogen/yarn/serialization/helpers/separators_ser.hpp"
#include "dogen/yarn/serialization/meta_model/builtin_ser.hpp"
#include "dogen/yarn/serialization/meta_model/element_ser.hpp"
#include "dogen/yarn/serialization/meta_model/visitor_ser.hpp"
#include "dogen/yarn/serialization/transforms/options_ser.hpp"
#include "dogen/yarn/serialization/helpers/mapping_set_ser.hpp"
#include "dogen/yarn/serialization/meta_model/exomodel_ser.hpp"
#include "dogen/yarn/serialization/meta_model/location_ser.hpp"
#include "dogen/yarn/serialization/meta_model/attribute_ser.hpp"
#include "dogen/yarn/serialization/meta_model/endomodel_ser.hpp"
#include "dogen/yarn/serialization/meta_model/exception_ser.hpp"
#include "dogen/yarn/serialization/meta_model/languages_ser.hpp"
#include "dogen/yarn/serialization/meta_model/name_tree_ser.hpp"
#include "dogen/yarn/serialization/meta_model/primitive_ser.hpp"
#include "dogen/yarn/serialization/helpers/mapping_value_ser.hpp"
#include "dogen/yarn/serialization/meta_model/enumerator_ser.hpp"
#include "dogen/yarn/serialization/meta_model/text_model_ser.hpp"
#include "dogen/yarn/serialization/meta_model/enumeration_ser.hpp"
#include "dogen/yarn/serialization/helpers/mapping_actions_ser.hpp"
#include "dogen/yarn/serialization/helpers/mapping_context_ser.hpp"
#include "dogen/yarn/serialization/meta_model/letter_cases_ser.hpp"
#include "dogen/yarn/serialization/meta_model/origin_types_ser.hpp"
#include "dogen/yarn/serialization/transforms/configuration_ser.hpp"
#include "dogen/yarn/serialization/helpers/transform_metrics_ser.hpp"
#include "dogen/yarn/serialization/meta_model/object_template_ser.hpp"
#include "dogen/yarn/serialization/meta_model/type_parameters_ser.hpp"
#include "dogen/yarn/serialization/meta_model/facet_properties_ser.hpp"
#include "dogen/yarn/serialization/helpers/decomposition_result_ser.hpp"
#include "dogen/yarn/serialization/meta_model/element_archetype_ser.hpp"
#include "dogen/yarn/serialization/meta_model/formatting_styles_ser.hpp"
#include "dogen/yarn/serialization/meta_model/backend_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/locator_properties_ser.hpp"
#include "dogen/yarn/serialization/helpers/mapping_set_repository_ser.hpp"
#include "dogen/yarn/serialization/meta_model/artefact_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/archetype_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/orm_database_systems_ser.hpp"
#include "dogen/yarn/serialization/meta_model/orm_model_properties_ser.hpp"
#include "dogen/yarn/serialization/transforms/naming_configuration_ser.hpp"
#include "dogen/yarn/serialization/meta_model/orm_module_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/orm_object_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/path_contribution_types_ser.hpp"
#include "dogen/yarn/serialization/meta_model/model_segment_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/orm_attribute_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/orm_primitive_properties_ser.hpp"
#include "dogen/yarn/serialization/transforms/exomodel_transform_types_ser.hpp"
#include "dogen/yarn/serialization/transforms/formatting_configuration_ser.hpp"
#include "dogen/yarn/serialization/meta_model/directory_structure_styles_ser.hpp"
#include "dogen/yarn/serialization/meta_model/archetype_family_properties_ser.hpp"
#include "dogen/yarn/serialization/transforms/local_enablement_configuration_ser.hpp"
#include "dogen/yarn/serialization/transforms/global_enablement_configuration_ser.hpp"
#include "dogen/yarn/serialization/meta_model/intra_backend_segment_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/denormalised_archetype_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/local_archetype_location_properties_ser.hpp"
#include "dogen/yarn/serialization/meta_model/global_archetype_location_properties_ser.hpp"

#endif
