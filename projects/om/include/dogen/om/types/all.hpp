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
#include "dogen/om/types/cmake_add_library.hpp"
#include "dogen/om/types/cmake_feature.hpp"
#include "dogen/om/types/cmake_file.hpp"
#include "dogen/om/types/cmake_install.hpp"
#include "dogen/om/types/cmake_set_target_properties.hpp"
#include "dogen/om/types/code_generation_marker.hpp"
#include "dogen/om/types/code_generation_marker_factory.hpp"
#include "dogen/om/types/cpp_abstract_function.hpp"
#include "dogen/om/types/cpp_abstract_instance.hpp"
#include "dogen/om/types/cpp_access_specifier_types.hpp"
#include "dogen/om/types/cpp_argument.hpp"
#include "dogen/om/types/cpp_base.hpp"
#include "dogen/om/types/cpp_class.hpp"
#include "dogen/om/types/cpp_class_types.hpp"
#include "dogen/om/types/cpp_enumeration.hpp"
#include "dogen/om/types/cpp_enumerator.hpp"
#include "dogen/om/types/cpp_feature.hpp"
#include "dogen/om/types/cpp_feature_visitor.hpp"
#include "dogen/om/types/cpp_file.hpp"
#include "dogen/om/types/cpp_function.hpp"
#include "dogen/om/types/cpp_fundamental_types.hpp"
#include "dogen/om/types/cpp_header_guard.hpp"
#include "dogen/om/types/cpp_ifdef.hpp"
#include "dogen/om/types/cpp_include_directive.hpp"
#include "dogen/om/types/cpp_include_types.hpp"
#include "dogen/om/types/cpp_instance_typeref.hpp"
#include "dogen/om/types/cpp_member_function.hpp"
#include "dogen/om/types/cpp_member_function_types.hpp"
#include "dogen/om/types/cpp_member_group.hpp"
#include "dogen/om/types/cpp_member_variable.hpp"
#include "dogen/om/types/cpp_memory_types.hpp"
#include "dogen/om/types/cpp_namespace.hpp"
#include "dogen/om/types/cpp_pragma.hpp"
#include "dogen/om/types/cpp_project.hpp"
#include "dogen/om/types/cpp_representation_types.hpp"
#include "dogen/om/types/cpp_typedef.hpp"
#include "dogen/om/types/cpp_typeref.hpp"
#include "dogen/om/types/cpp_variable.hpp"
#include "dogen/om/types/doxygen_command.hpp"
#include "dogen/om/types/doxygen_command_types.hpp"
#include "dogen/om/types/hydration_error.hpp"
#include "dogen/om/types/licence.hpp"
#include "dogen/om/types/licence_hydrator.hpp"
#include "dogen/om/types/odb_database_option.hpp"
#include "dogen/om/types/odb_guard_prefix_option.hpp"
#include "dogen/om/types/odb_include_regex_option.hpp"
#include "dogen/om/types/odb_option.hpp"
#include "dogen/om/types/odb_options_file.hpp"
#include "dogen/om/types/om.hpp"
#include "dogen/om/types/preamble.hpp"
#include "dogen/om/types/preamble_field.hpp"
#include "dogen/om/types/preamble_scheme.hpp"
#include "dogen/om/types/preamble_scheme_hydrator.hpp"
#include "dogen/om/types/text_file.hpp"
