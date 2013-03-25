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
#include "dogen/cpp/types/boost_model_helper.hpp"
#include "dogen/cpp/types/boost_types.hpp"
#include "dogen/cpp/types/cpp_aspect_types.hpp"
#include "dogen/cpp/types/cpp_backend.hpp"
#include "dogen/cpp/types/cpp_inclusion_manager.hpp"
#include "dogen/cpp/types/cpp_location_manager.hpp"
#include "dogen/cpp/types/cpp_location_request.hpp"
#include "dogen/cpp/types/dependency_details.hpp"
#include "dogen/cpp/types/dependency_extractor.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/cpp/types/formatters/cpp_class_declaration.hpp"
#include "dogen/cpp/types/formatters/cpp_class_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_domain_class_declaration.hpp"
#include "dogen/cpp/types/formatters/cpp_domain_class_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_domain_header.hpp"
#include "dogen/cpp/types/formatters/cpp_domain_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_doxygen_comments.hpp"
#include "dogen/cpp/types/formatters/cpp_enumeration_declaration.hpp"
#include "dogen/cpp/types/formatters/cpp_exception_declaration.hpp"
#include "dogen/cpp/types/formatters/cpp_facet_includer.hpp"
#include "dogen/cpp/types/formatters/cpp_forward_declarations_header.hpp"
#include "dogen/cpp/types/formatters/cpp_generator_header.hpp"
#include "dogen/cpp/types/formatters/cpp_generator_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_hash_header.hpp"
#include "dogen/cpp/types/formatters/cpp_hash_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_header_guards.hpp"
#include "dogen/cpp/types/formatters/cpp_include_cmakelists.hpp"
#include "dogen/cpp/types/formatters/cpp_includes.hpp"
#include "dogen/cpp/types/formatters/cpp_indenter.hpp"
#include "dogen/cpp/types/formatters/cpp_inserter_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_io_header.hpp"
#include "dogen/cpp/types/formatters/cpp_io_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_key_class_declaration.hpp"
#include "dogen/cpp/types/formatters/cpp_key_class_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_licence.hpp"
#include "dogen/cpp/types/formatters/cpp_namespace.hpp"
#include "dogen/cpp/types/formatters/cpp_namespace_helper.hpp"
#include "dogen/cpp/types/formatters/cpp_null_formatter.hpp"
#include "dogen/cpp/types/formatters/cpp_odb_header.hpp"
#include "dogen/cpp/types/formatters/cpp_qualified_name.hpp"
#include "dogen/cpp/types/formatters/cpp_registrar_header.hpp"
#include "dogen/cpp/types/formatters/cpp_registrar_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_serialization_header.hpp"
#include "dogen/cpp/types/formatters/cpp_serialization_implementation.hpp"
#include "dogen/cpp/types/formatters/cpp_src_cmakelists.hpp"
#include "dogen/cpp/types/formatters/cpp_utility.hpp"
#include "dogen/cpp/types/formatters/factory.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"
#include "dogen/cpp/types/formatters/production_failure.hpp"
#include "dogen/cpp/types/generation_failure.hpp"
#include "dogen/cpp/types/std_model_helper.hpp"
#include "dogen/cpp/types/std_types.hpp"
#include "dogen/cpp/types/view_models/class_view_model.hpp"
#include "dogen/cpp/types/view_models/cmakelists_view_model.hpp"
#include "dogen/cpp/types/view_models/enumeration_view_model.hpp"
#include "dogen/cpp/types/view_models/enumerator_view_model.hpp"
#include "dogen/cpp/types/view_models/exception_view_model.hpp"
#include "dogen/cpp/types/view_models/file_view_model.hpp"
#include "dogen/cpp/types/view_models/nested_type_view_model.hpp"
#include "dogen/cpp/types/view_models/parent_view_model.hpp"
#include "dogen/cpp/types/view_models/property_view_model.hpp"
#include "dogen/cpp/types/view_models/registrar_view_model.hpp"
#include "dogen/cpp/types/view_models/sml_to_cpp_view_model.hpp"
#include "dogen/cpp/types/view_models/transformation_error.hpp"
