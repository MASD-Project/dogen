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
#ifndef MASD_DOGEN_CODING_TYPES_ALL_HPP
#define MASD_DOGEN_CODING_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.coding/types/coding.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/helpers/node.hpp"
#include "masd.dogen.coding/types/helpers/mapper.hpp"
#include "masd.dogen.coding/types/helpers/indexer.hpp"
#include "masd.dogen.coding/types/helpers/indices.hpp"
#include "masd.dogen.coding/types/helpers/mapping.hpp"
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/types/helpers/resolver.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/editor.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/helpers/decomposer.hpp"
#include "masd.dogen.coding/types/helpers/separators.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/licence.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set.hpp"
#include "masd.dogen.coding/types/meta_model/location.hpp"
#include "masd.dogen.coding/types/meta_model/modeline.hpp"
#include "masd.dogen.coding/types/helpers/name_builder.hpp"
#include "masd.dogen.coding/types/helpers/name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/attribute.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/model_set.hpp"
#include "masd.dogen.coding/types/meta_model/name_tree.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/helpers/mapping_error.hpp"
#include "masd.dogen.coding/types/helpers/mapping_value.hpp"
#include "masd.dogen.coding/types/helpers/parsing_error.hpp"
#include "masd.dogen.coding/types/meta_model/decoration.hpp"
#include "masd.dogen.coding/types/meta_model/enumerator.hpp"
#include "masd.dogen.coding/types/transforms/transforms.hpp"
#include "masd.dogen.coding/types/helpers/building_error.hpp"
#include "masd.dogen.coding/types/helpers/indexing_error.hpp"
#include "masd.dogen.coding/types/helpers/name_flattener.hpp"
#include "masd.dogen.coding/types/helpers/pretty_printer.hpp"
#include "masd.dogen.coding/types/helpers/printing_error.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/helpers/hydration_error.hpp"
#include "masd.dogen.coding/types/helpers/mapping_actions.hpp"
#include "masd.dogen.coding/types/helpers/mapping_context.hpp"
#include "masd.dogen.coding/types/meta_model/letter_cases.hpp"
#include "masd.dogen.coding/types/meta_model/origin_types.hpp"
#include "masd.dogen.coding/types/helpers/location_builder.hpp"
#include "masd.dogen.coding/types/helpers/resolution_error.hpp"
#include "masd.dogen.coding/types/helpers/string_processor.hpp"
#include "masd.dogen.coding/types/helpers/validation_error.hpp"
#include "masd.dogen.coding/types/meta_model/configuration.hpp"
#include "masd.dogen.coding/types/transforms/orm_transform.hpp"
#include "masd.dogen.coding/types/helpers/mappings_hydrator.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/helpers/name_tree_builder.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_field.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_group.hpp"
#include "masd.dogen.coding/types/transforms/assembly_chain.hpp"
#include "masd.dogen.coding/types/helpers/mappings_validator.hpp"
#include "masd.dogen.coding/types/meta_model/element_visitor.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/types/meta_model/technical_space.hpp"
#include "masd.dogen.coding/types/meta_model/type_parameters.hpp"
#include "masd.dogen.coding/types/transforms/merge_transform.hpp"
#include "masd.dogen.coding/types/transforms/origin_transform.hpp"
#include "masd.dogen.coding/types/helpers/decomposition_result.hpp"
#include "masd.dogen.coding/types/helpers/new_name_tree_parser.hpp"
#include "masd.dogen.coding/types/meta_model/formatting_styles.hpp"
#include "masd.dogen.coding/types/meta_model/generation_marker.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_location.hpp"
#include "masd.dogen.coding/types/transforms/mapping_transform.hpp"
#include "masd.dogen.coding/types/transforms/modules_transform.hpp"
#include "masd.dogen.coding/types/transforms/parsing_transform.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.coding/types/meta_model/static_stereotypes.hpp"
#include "masd.dogen.coding/types/transforms/pre_assembly_chain.hpp"
#include "masd.dogen.coding/types/transforms/resolver_transform.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set_repository.hpp"
#include "masd.dogen.coding/types/helpers/pre_assembly_validator.hpp"
#include "masd.dogen.coding/types/meta_model/artefact_properties.hpp"
#include "masd.dogen.coding/types/transforms/modelines_transform.hpp"
#include "masd.dogen.coding/types/transforms/post_assembly_chain.hpp"
#include "masd.dogen.coding/types/helpers/legacy_name_tree_parser.hpp"
#include "masd.dogen.coding/types/helpers/post_assembly_validator.hpp"
#include "masd.dogen.coding/types/meta_model/orm_database_systems.hpp"
#include "masd.dogen.coding/types/meta_model/orm_model_properties.hpp"
#include "masd.dogen.coding/types/transforms/attributes_transform.hpp"
#include "masd.dogen.coding/types/transforms/primitives_transform.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/meta_model/extraction_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_module_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_object_properties.hpp"
#include "masd.dogen.coding/types/transforms/containment_transform.hpp"
#include "masd.dogen.coding/types/transforms/meta_naming_transform.hpp"
#include "masd.dogen.coding/types/transforms/stereotypes_transform.hpp"
#include "masd.dogen.coding/types/transforms/type_params_transform.hpp"
#include "masd.dogen.coding/types/transforms/associations_transform.hpp"
#include "masd.dogen.coding/types/transforms/enumerations_transform.hpp"
#include "masd.dogen.coding/types/transforms/model_production_chain.hpp"
#include "masd.dogen.coding/types/transforms/configuration_transform.hpp"
#include "masd.dogen.coding/types/transforms/global_module_transform.hpp"
#include "masd.dogen.coding/types/meta_model/orm_attribute_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_primitive_properties.hpp"
#include "masd.dogen.coding/types/transforms/generalization_transform.hpp"
#include "masd.dogen.coding/types/transforms/technical_space_transform.hpp"
#include "masd.dogen.coding/types/transforms/object_templates_transform.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set_repository_factory.hpp"
#include "masd.dogen.coding/types/meta_model/fully_qualified_representation.hpp"
#include "masd.dogen.coding/types/transforms/annotation_expansion_transform.hpp"
#include "masd.dogen.coding/types/transforms/extraction_properties_transform.hpp"
#include "masd.dogen.coding/types/helpers/fully_qualified_representation_builder.hpp"
#include "masd.dogen.coding/types/meta_model/local_archetype_location_properties.hpp"

#endif
