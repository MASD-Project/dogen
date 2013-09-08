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
#include "dogen/om/io/cmake_add_library_io.hpp"
#include "dogen/om/io/cmake_feature_io.hpp"
#include "dogen/om/io/cmake_file_io.hpp"
#include "dogen/om/io/cmake_install_io.hpp"
#include "dogen/om/io/cmake_set_target_properties_io.hpp"
#include "dogen/om/io/code_generation_marker_io.hpp"
#include "dogen/om/io/cpp_abstract_function_io.hpp"
#include "dogen/om/io/cpp_abstract_instance_io.hpp"
#include "dogen/om/io/cpp_access_specifier_types_io.hpp"
#include "dogen/om/io/cpp_argument_io.hpp"
#include "dogen/om/io/cpp_base_io.hpp"
#include "dogen/om/io/cpp_class_io.hpp"
#include "dogen/om/io/cpp_class_types_io.hpp"
#include "dogen/om/io/cpp_enumeration_io.hpp"
#include "dogen/om/io/cpp_enumerator_io.hpp"
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/io/cpp_file_io.hpp"
#include "dogen/om/io/cpp_function_io.hpp"
#include "dogen/om/io/cpp_fundamental_types_io.hpp"
#include "dogen/om/io/cpp_header_guard_io.hpp"
#include "dogen/om/io/cpp_ifdef_io.hpp"
#include "dogen/om/io/cpp_include_directive_io.hpp"
#include "dogen/om/io/cpp_include_types_io.hpp"
#include "dogen/om/io/cpp_instance_typeref_io.hpp"
#include "dogen/om/io/cpp_member_function_io.hpp"
#include "dogen/om/io/cpp_member_function_types_io.hpp"
#include "dogen/om/io/cpp_member_group_io.hpp"
#include "dogen/om/io/cpp_member_variable_io.hpp"
#include "dogen/om/io/cpp_memory_types_io.hpp"
#include "dogen/om/io/cpp_namespace_io.hpp"
#include "dogen/om/io/cpp_pragma_io.hpp"
#include "dogen/om/io/cpp_project_io.hpp"
#include "dogen/om/io/cpp_representation_types_io.hpp"
#include "dogen/om/io/cpp_typedef_io.hpp"
#include "dogen/om/io/cpp_typeref_io.hpp"
#include "dogen/om/io/cpp_variable_io.hpp"
#include "dogen/om/io/doxygen_command_io.hpp"
#include "dogen/om/io/doxygen_command_types_io.hpp"
#include "dogen/om/io/editors_io.hpp"
#include "dogen/om/io/licence_io.hpp"
#include "dogen/om/io/modeline_field_io.hpp"
#include "dogen/om/io/modeline_group_io.hpp"
#include "dogen/om/io/modeline_io.hpp"
#include "dogen/om/io/modeline_locations_io.hpp"
#include "dogen/om/io/odb_database_option_io.hpp"
#include "dogen/om/io/odb_guard_prefix_option_io.hpp"
#include "dogen/om/io/odb_include_regex_option_io.hpp"
#include "dogen/om/io/odb_option_io.hpp"
#include "dogen/om/io/odb_options_file_io.hpp"
#include "dogen/om/io/text_file_io.hpp"
