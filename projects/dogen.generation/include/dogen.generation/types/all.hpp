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
#ifndef DOGEN_GENERATION_TYPES_ALL_HPP
#define DOGEN_GENERATION_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.generation/types/traits.hpp"
#include "dogen.generation/types/meta_model/model.hpp"
#include "dogen.generation/types/transforms/context.hpp"
#include "dogen.generation/types/meta_model/artefact.hpp"
#include "dogen.generation/types/helpers/stream_writer.hpp"
#include "dogen.generation/types/helpers/writing_error.hpp"
#include "dogen.generation/types/meta_model/text_model.hpp"
#include "dogen.generation/types/transforms/configuration.hpp"
#include "dogen.generation/types/helpers/filesystem_writer.hpp"
#include "dogen.generation/types/meta_model/facet_properties.hpp"
#include "dogen.generation/types/meta_model/element_archetype.hpp"
#include "dogen.generation/types/meta_model/formatting_styles.hpp"
#include "dogen.generation/types/meta_model/backend_properties.hpp"
#include "dogen.generation/types/meta_model/locator_properties.hpp"
#include "dogen.generation/types/meta_model/artefact_properties.hpp"
#include "dogen.generation/types/meta_model/generatable_element.hpp"
#include "dogen.generation/types/meta_model/archetype_properties.hpp"
#include "dogen.generation/types/transforms/enablement_transform.hpp"
#include "dogen.generation/types/transforms/formatting_transform.hpp"
#include "dogen.generation/types/transforms/transformation_error.hpp"
#include "dogen.generation/types/helpers/artefact_writer_interface.hpp"
#include "dogen.generation/types/transforms/generability_transform.hpp"
#include "dogen.generation/types/transforms/model_generation_chain.hpp"
#include "dogen.generation/types/meta_model/path_contribution_types.hpp"
#include "dogen.generation/types/meta_model/model_segment_properties.hpp"
#include "dogen.generation/types/transforms/dynamic_transforms_chain.hpp"
#include "dogen.generation/types/transforms/formatting_configuration.hpp"
#include "dogen.generation/types/transforms/model_to_text_model_chain.hpp"
#include "dogen.generation/types/meta_model/directory_structure_styles.hpp"
#include "dogen.generation/types/meta_model/archetype_family_properties.hpp"
#include "dogen.generation/types/transforms/dynamic_transform_interface.hpp"
#include "dogen.generation/types/transforms/dynamic_transform_registrar.hpp"
#include "dogen.generation/types/transforms/model_post_processing_chain.hpp"
#include "dogen.generation/types/transforms/text_model_generation_chain.hpp"
#include "dogen.generation/types/transforms/locator_properties_transform.hpp"
#include "dogen.generation/types/transforms/artefact_properties_transform.hpp"
#include "dogen.generation/types/meta_model/intra_backend_segment_properties.hpp"
#include "dogen.generation/types/meta_model/denormalised_archetype_properties.hpp"
#include "dogen.generation/types/meta_model/local_archetype_location_properties.hpp"
#include "dogen.generation/types/meta_model/global_archetype_location_properties.hpp"
#include "dogen.generation/types/transforms/archetype_location_properties_transform.hpp"
#include "dogen.generation/types/transforms/model_to_text_model_transform_interface.hpp"
#include "dogen.generation/types/transforms/model_to_text_model_transform_registrar.hpp"
#include "dogen.generation/types/transforms/modeling_model_to_generation_model_transform.hpp"

#endif
