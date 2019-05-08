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
#ifndef MASD_DOGEN_GENERATION_CSHARP_TYPES_ALL_HPP
#define MASD_DOGEN_GENERATION_CSHARP_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.generation.csharp/types/csharp.hpp"
#include "masd.dogen.generation.csharp/types/traits.hpp"
#include "masd.dogen.generation.csharp/types/initializer.hpp"
#include "masd.dogen.generation.csharp/types/fabric/traits.hpp"
#include "masd.dogen.generation.csharp/types/workflow_error.hpp"
#include "masd.dogen.generation.csharp/types/element_visitor.hpp"
#include "masd.dogen.generation.csharp/types/fabric/injector.hpp"
#include "masd.dogen.generation.csharp/types/fabric/assistant.hpp"
#include "masd.dogen.generation.csharp/types/formatters/traits.hpp"
#include "masd.dogen.generation.csharp/types/fabric/initializer.hpp"
#include "masd.dogen.generation.csharp/types/formattables/model.hpp"
#include "masd.dogen.generation.csharp/types/formatters/context.hpp"
#include "masd.dogen.generation.csharp/types/formatters/workflow.hpp"
#include "masd.dogen.generation.csharp/types/fabric/assembly_info.hpp"
#include "masd.dogen.generation.csharp/types/formattables/adapter.hpp"
#include "masd.dogen.generation.csharp/types/formattables/locator.hpp"
#include "masd.dogen.generation.csharp/types/formattables/reducer.hpp"
#include "masd.dogen.generation.csharp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/traits.hpp"
#include "masd.dogen.generation.csharp/types/formatters/registrar.hpp"
#include "masd.dogen.generation.csharp/types/formattables/workflow.hpp"
#include "masd.dogen.generation.csharp/types/formatters/repository.hpp"
#include "masd.dogen.generation.csharp/types/formatters/initializer.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.csharp/types/fabric/assistant_factory.hpp"
#include "masd.dogen.generation.csharp/types/fabric/dynamic_transform.hpp"
#include "masd.dogen.generation.csharp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.csharp/types/formattables/formattable.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/initializer.hpp"
#include "masd.dogen.generation.csharp/types/formatters/registrar_error.hpp"
#include "masd.dogen.generation.csharp/types/formattables/location_error.hpp"
#include "masd.dogen.generation.csharp/types/formattables/model_expander.hpp"
#include "masd.dogen.generation.csharp/types/formattables/using_expander.hpp"
#include "masd.dogen.generation.csharp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.csharp/types/formatters/test_data/traits.hpp"
#include "masd.dogen.generation.csharp/types/fabric/assembly_info_factory.hpp"
#include "masd.dogen.generation.csharp/types/fabric/visual_studio_factory.hpp"
#include "masd.dogen.generation.csharp/types/fabric/visual_studio_project.hpp"
#include "masd.dogen.generation.csharp/types/formattables/aspect_expander.hpp"
#include "masd.dogen.generation.csharp/types/formattables/expansion_error.hpp"
#include "masd.dogen.generation.csharp/types/formattables/helper_expander.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/enum_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/initializer.hpp"
#include "masd.dogen.generation.csharp/types/fabric/visual_studio_solution.hpp"
#include "masd.dogen.generation.csharp/types/formattables/adaptation_error.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/class_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formattables/aspect_properties.hpp"
#include "masd.dogen.generation.csharp/types/formattables/helper_descriptor.hpp"
#include "masd.dogen.generation.csharp/types/formattables/helper_properties.hpp"
#include "masd.dogen.generation.csharp/types/formattables/assistant_expander.hpp"
#include "masd.dogen.generation.csharp/types/formattables/element_properties.hpp"
#include "masd.dogen.generation.csharp/types/formattables/file_path_expander.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/builtin_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/enumerable_helper.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/enum_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formattables/artefact_properties.hpp"
#include "masd.dogen.generation.csharp/types/formatters/test_data/initializer.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/class_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formattables/assistant_properties.hpp"
#include "masd.dogen.generation.csharp/types/formattables/attribute_properties.hpp"
#include "masd.dogen.generation.csharp/types/formattables/helper_configuration.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/assistant_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/primitive_formatter.hpp"
#include "masd.dogen.generation.csharp/types/fabric/visual_studio_configuration.hpp"
#include "masd.dogen.generation.csharp/types/formattables/locator_configuration.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/builtin_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/visitor_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formattables/project_items_expander.hpp"
#include "masd.dogen.generation.csharp/types/formatters/test_data/enum_formatter.hpp"
#include "masd.dogen.generation.csharp/types/model_to_extraction_model_transform.hpp"
#include "masd.dogen.generation.csharp/types/formatters/test_data/class_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/exception_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/namespace_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/primitive_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formattables/auxiliary_function_types.hpp"
#include "masd.dogen.generation.csharp/types/formatters/helper_formatter_interface.hpp"
#include "masd.dogen.generation.csharp/types/formatters/test_data/builtin_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/artefact_formatter_interface.hpp"
#include "masd.dogen.generation.csharp/types/formattables/locator_facet_configuration.hpp"
#include "masd.dogen.generation.csharp/types/formatters/test_data/assistant_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/test_data/primitive_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formattables/auxiliary_function_properties.hpp"
#include "masd.dogen.generation.csharp/types/formatters/visual_studio_project_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/visual_studio_solution_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formattables/locator_archetype_configuration.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/floating_point_number_helper.hpp"

#endif
