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
#include "dogen/cpp/types/cpp.hpp"
#include "dogen/cpp/types/formattables/abilities.hpp"
#include "dogen/cpp/types/formattables/aspect_types.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/class_aspects.hpp"
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp/types/formattables/class_types.hpp"
#include "dogen/cpp/types/formattables/cmakelists_info.hpp"
#include "dogen/cpp/types/formattables/concept_info.hpp"
#include "dogen/cpp/types/formattables/content_descriptor.hpp"
#include "dogen/cpp/types/formattables/content_descriptor_factory.hpp"
#include "dogen/cpp/types/formattables/content_types.hpp"
#include "dogen/cpp/types/formattables/entity.hpp"
#include "dogen/cpp/types/formattables/enum_info.hpp"
#include "dogen/cpp/types/formattables/enumerator_info.hpp"
#include "dogen/cpp/types/formattables/exception_info.hpp"
#include "dogen/cpp/types/formattables/family_types.hpp"
#include "dogen/cpp/types/formattables/file_info.hpp"
#include "dogen/cpp/types/formattables/file_types.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"
#include "dogen/cpp/types/formattables/formattable_visitor.hpp"
#include "dogen/cpp/types/formattables/formattables.hpp"
#include "dogen/cpp/types/formattables/forward_declarations_info.hpp"
#include "dogen/cpp/types/formattables/includers_info.hpp"
#include "dogen/cpp/types/formattables/includes.hpp"
#include "dogen/cpp/types/formattables/inheritance.hpp"
#include "dogen/cpp/types/formattables/name_builder.hpp"
#include "dogen/cpp/types/formattables/namespace_info.hpp"
#include "dogen/cpp/types/formattables/nested_type_info.hpp"
#include "dogen/cpp/types/formattables/new_class_info.hpp"
#include "dogen/cpp/types/formattables/odb_options_info.hpp"
#include "dogen/cpp/types/formattables/parent_info.hpp"
#include "dogen/cpp/types/formattables/primitive_info.hpp"
#include "dogen/cpp/types/formattables/project.hpp"
#include "dogen/cpp/types/formattables/property_info.hpp"
#include "dogen/cpp/types/formattables/registrar_info.hpp"
#include "dogen/cpp/types/formattables/state.hpp"
#include "dogen/cpp/types/formattables/transformation_error.hpp"
#include "dogen/cpp/types/formattables/transformer.hpp"
#include "dogen/cpp/types/formattables/visitor_info.hpp"
#include "dogen/cpp/types/formattables/workflow.hpp"
#include "dogen/cpp/types/formatters/boilerplate_formatter.hpp"
#include "dogen/cpp/types/formatters/class_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/cmakelists_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formatters/enum_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/exception_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"
#include "dogen/cpp/types/formatters/formatter_interface.hpp"
#include "dogen/cpp/types/formatters/formatter_types.hpp"
#include "dogen/cpp/types/formatters/formatters.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/forward_declarations_formatter.hpp"
#include "dogen/cpp/types/formatters/forward_declarations_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/hash/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/enricher.hpp"
#include "dogen/cpp/types/formatters/hash/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/field_definitions.hpp"
#include "dogen/cpp/types/formatters/hash/hash.hpp"
#include "dogen/cpp/types/formatters/hash/initializer.hpp"
#include "dogen/cpp/types/formatters/hash/traits.hpp"
#include "dogen/cpp/types/formatters/header_guard_formatter.hpp"
#include "dogen/cpp/types/formatters/include_cmakelists_formatter.hpp"
#include "dogen/cpp/types/formatters/include_formatter.hpp"
#include "dogen/cpp/types/formatters/includers_formatter.hpp"
#include "dogen/cpp/types/formatters/includers_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/initializer.hpp"
#include "dogen/cpp/types/formatters/io/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/io/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/io/enricher.hpp"
#include "dogen/cpp/types/formatters/io/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/io/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/io/field_definitions.hpp"
#include "dogen/cpp/types/formatters/io/initializer.hpp"
#include "dogen/cpp/types/formatters/io/io.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/odb/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/odb/enricher.hpp"
#include "dogen/cpp/types/formatters/odb/field_definitions.hpp"
#include "dogen/cpp/types/formatters/odb/initializer.hpp"
#include "dogen/cpp/types/formatters/odb/odb.hpp"
#include "dogen/cpp/types/formatters/odb/odb_options_formatter.hpp"
#include "dogen/cpp/types/formatters/odb/settings.hpp"
#include "dogen/cpp/types/formatters/odb/settings_factory.hpp"
#include "dogen/cpp/types/formatters/odb/traits.hpp"
#include "dogen/cpp/types/formatters/odb_options_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/qname_formatter.hpp"
#include "dogen/cpp/types/formatters/registrar.hpp"
#include "dogen/cpp/types/formatters/registrar_error.hpp"
#include "dogen/cpp/types/formatters/registrar_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/serialization/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/enricher.hpp"
#include "dogen/cpp/types/formatters/serialization/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/field_definitions.hpp"
#include "dogen/cpp/types/formatters/serialization/initializer.hpp"
#include "dogen/cpp/types/formatters/serialization/serialization.hpp"
#include "dogen/cpp/types/formatters/serialization/settings.hpp"
#include "dogen/cpp/types/formatters/serialization/settings_factory.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/source_cmakelists_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/enricher.hpp"
#include "dogen/cpp/types/formatters/test_data/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/field_definitions.hpp"
#include "dogen/cpp/types/formatters/test_data/initializer.hpp"
#include "dogen/cpp/types/formatters/test_data/test_data.hpp"
#include "dogen/cpp/types/formatters/test_data/traits.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/types/enricher.hpp"
#include "dogen/cpp/types/formatters/types/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/types/exception_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/exception_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/types/field_definitions.hpp"
#include "dogen/cpp/types/formatters/types/initializer.hpp"
#include "dogen/cpp/types/formatters/types/namespace_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/types/types.hpp"
#include "dogen/cpp/types/formatters/types/visitor_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/visitor_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/visitor_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/initializer.hpp"
#include "dogen/cpp/types/settings/building_error.hpp"
#include "dogen/cpp/types/settings/bundle.hpp"
#include "dogen/cpp/types/settings/bundle_factory.hpp"
#include "dogen/cpp/types/settings/common_formatter_settings.hpp"
#include "dogen/cpp/types/settings/common_formatter_settings_factory.hpp"
#include "dogen/cpp/types/settings/field_definitions.hpp"
#include "dogen/cpp/types/settings/inclusion.hpp"
#include "dogen/cpp/types/settings/inclusion_delimiter_types.hpp"
#include "dogen/cpp/types/settings/initializer.hpp"
#include "dogen/cpp/types/settings/path_settings.hpp"
#include "dogen/cpp/types/settings/path_settings_factory.hpp"
#include "dogen/cpp/types/settings/registrar.hpp"
#include "dogen/cpp/types/settings/registrar_error.hpp"
#include "dogen/cpp/types/settings/sample_settings.hpp"
#include "dogen/cpp/types/settings/settings.hpp"
#include "dogen/cpp/types/settings/special_formatter_settings.hpp"
#include "dogen/cpp/types/settings/special_formatter_settings_factory_interface.hpp"
#include "dogen/cpp/types/settings/type_settings.hpp"
#include "dogen/cpp/types/settings/type_settings_factory.hpp"
#include "dogen/cpp/types/settings/workflow.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/workflow.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
