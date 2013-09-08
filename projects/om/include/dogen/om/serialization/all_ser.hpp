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
#include "dogen/om/serialization/cmake_add_library_ser.hpp"
#include "dogen/om/serialization/cmake_feature_ser.hpp"
#include "dogen/om/serialization/cmake_file_ser.hpp"
#include "dogen/om/serialization/cmake_install_ser.hpp"
#include "dogen/om/serialization/cmake_set_target_properties_ser.hpp"
#include "dogen/om/serialization/code_generation_marker_ser.hpp"
#include "dogen/om/serialization/cpp_abstract_function_ser.hpp"
#include "dogen/om/serialization/cpp_abstract_instance_ser.hpp"
#include "dogen/om/serialization/cpp_access_specifier_types_ser.hpp"
#include "dogen/om/serialization/cpp_argument_ser.hpp"
#include "dogen/om/serialization/cpp_base_ser.hpp"
#include "dogen/om/serialization/cpp_class_ser.hpp"
#include "dogen/om/serialization/cpp_class_types_ser.hpp"
#include "dogen/om/serialization/cpp_enumeration_ser.hpp"
#include "dogen/om/serialization/cpp_enumerator_ser.hpp"
#include "dogen/om/serialization/cpp_feature_ser.hpp"
#include "dogen/om/serialization/cpp_file_ser.hpp"
#include "dogen/om/serialization/cpp_function_ser.hpp"
#include "dogen/om/serialization/cpp_fundamental_types_ser.hpp"
#include "dogen/om/serialization/cpp_header_guard_ser.hpp"
#include "dogen/om/serialization/cpp_ifdef_ser.hpp"
#include "dogen/om/serialization/cpp_include_directive_ser.hpp"
#include "dogen/om/serialization/cpp_include_types_ser.hpp"
#include "dogen/om/serialization/cpp_instance_typeref_ser.hpp"
#include "dogen/om/serialization/cpp_member_function_ser.hpp"
#include "dogen/om/serialization/cpp_member_function_types_ser.hpp"
#include "dogen/om/serialization/cpp_member_group_ser.hpp"
#include "dogen/om/serialization/cpp_member_variable_ser.hpp"
#include "dogen/om/serialization/cpp_memory_types_ser.hpp"
#include "dogen/om/serialization/cpp_namespace_ser.hpp"
#include "dogen/om/serialization/cpp_pragma_ser.hpp"
#include "dogen/om/serialization/cpp_project_ser.hpp"
#include "dogen/om/serialization/cpp_representation_types_ser.hpp"
#include "dogen/om/serialization/cpp_typedef_ser.hpp"
#include "dogen/om/serialization/cpp_typeref_ser.hpp"
#include "dogen/om/serialization/cpp_variable_ser.hpp"
#include "dogen/om/serialization/doxygen_command_ser.hpp"
#include "dogen/om/serialization/doxygen_command_types_ser.hpp"
#include "dogen/om/serialization/editors_ser.hpp"
#include "dogen/om/serialization/licence_ser.hpp"
#include "dogen/om/serialization/modeline_field_ser.hpp"
#include "dogen/om/serialization/modeline_group_ser.hpp"
#include "dogen/om/serialization/modeline_locations_ser.hpp"
#include "dogen/om/serialization/modeline_ser.hpp"
#include "dogen/om/serialization/odb_database_option_ser.hpp"
#include "dogen/om/serialization/odb_guard_prefix_option_ser.hpp"
#include "dogen/om/serialization/odb_include_regex_option_ser.hpp"
#include "dogen/om/serialization/odb_option_ser.hpp"
#include "dogen/om/serialization/odb_options_file_ser.hpp"
#include "dogen/om/serialization/registrar_ser.hpp"
#include "dogen/om/serialization/text_file_ser.hpp"
