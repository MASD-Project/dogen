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
#include "dogen/om/hash/cmake_add_library_hash.hpp"
#include "dogen/om/hash/cmake_feature_hash.hpp"
#include "dogen/om/hash/cmake_file_hash.hpp"
#include "dogen/om/hash/cmake_install_hash.hpp"
#include "dogen/om/hash/cmake_set_target_properties_hash.hpp"
#include "dogen/om/hash/code_generation_marker_hash.hpp"
#include "dogen/om/hash/cpp_abstract_function_hash.hpp"
#include "dogen/om/hash/cpp_abstract_instance_hash.hpp"
#include "dogen/om/hash/cpp_access_specifier_types_hash.hpp"
#include "dogen/om/hash/cpp_argument_hash.hpp"
#include "dogen/om/hash/cpp_base_hash.hpp"
#include "dogen/om/hash/cpp_class_hash.hpp"
#include "dogen/om/hash/cpp_class_types_hash.hpp"
#include "dogen/om/hash/cpp_enumeration_hash.hpp"
#include "dogen/om/hash/cpp_enumerator_hash.hpp"
#include "dogen/om/hash/cpp_feature_hash.hpp"
#include "dogen/om/hash/cpp_file_hash.hpp"
#include "dogen/om/hash/cpp_function_hash.hpp"
#include "dogen/om/hash/cpp_fundamental_types_hash.hpp"
#include "dogen/om/hash/cpp_header_guard_hash.hpp"
#include "dogen/om/hash/cpp_ifdef_hash.hpp"
#include "dogen/om/hash/cpp_include_directive_hash.hpp"
#include "dogen/om/hash/cpp_include_types_hash.hpp"
#include "dogen/om/hash/cpp_instance_typeref_hash.hpp"
#include "dogen/om/hash/cpp_member_function_hash.hpp"
#include "dogen/om/hash/cpp_member_function_types_hash.hpp"
#include "dogen/om/hash/cpp_member_group_hash.hpp"
#include "dogen/om/hash/cpp_member_variable_hash.hpp"
#include "dogen/om/hash/cpp_memory_types_hash.hpp"
#include "dogen/om/hash/cpp_namespace_hash.hpp"
#include "dogen/om/hash/cpp_pragma_hash.hpp"
#include "dogen/om/hash/cpp_project_hash.hpp"
#include "dogen/om/hash/cpp_representation_types_hash.hpp"
#include "dogen/om/hash/cpp_typedef_hash.hpp"
#include "dogen/om/hash/cpp_typeref_hash.hpp"
#include "dogen/om/hash/cpp_variable_hash.hpp"
#include "dogen/om/hash/doxygen_command_hash.hpp"
#include "dogen/om/hash/doxygen_command_types_hash.hpp"
#include "dogen/om/hash/licence_hash.hpp"
#include "dogen/om/hash/odb_database_option_hash.hpp"
#include "dogen/om/hash/odb_guard_prefix_option_hash.hpp"
#include "dogen/om/hash/odb_include_regex_option_hash.hpp"
#include "dogen/om/hash/odb_option_hash.hpp"
#include "dogen/om/hash/odb_options_file_hash.hpp"
#include "dogen/om/hash/preamble_hash.hpp"
#include "dogen/om/hash/preamble_types_hash.hpp"
#include "dogen/om/hash/text_file_hash.hpp"
