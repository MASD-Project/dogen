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
#include "dogen/cpp/serialization/access_specifier_types_ser.hpp"
#include "dogen/cpp/serialization/aspect_types_ser.hpp"
#include "dogen/cpp/serialization/base_specifier_ser.hpp"
#include "dogen/cpp/serialization/class_head_ser.hpp"
#include "dogen/cpp/serialization/class_info_ser.hpp"
#include "dogen/cpp/serialization/class_key_types_ser.hpp"
#include "dogen/cpp/serialization/class_specifier_ser.hpp"
#include "dogen/cpp/serialization/class_types_ser.hpp"
#include "dogen/cpp/serialization/cmakelists_info_ser.hpp"
#include "dogen/cpp/serialization/content_descriptor_ser.hpp"
#include "dogen/cpp/serialization/content_types_ser.hpp"
#include "dogen/cpp/serialization/cv_qualifier_types_ser.hpp"
#include "dogen/cpp/serialization/decl_specifier_ser.hpp"
#include "dogen/cpp/serialization/declarator_ser.hpp"
#include "dogen/cpp/serialization/entity_ser.hpp"
#include "dogen/cpp/serialization/enum_info_ser.hpp"
#include "dogen/cpp/serialization/enumerator_info_ser.hpp"
#include "dogen/cpp/serialization/exception_info_ser.hpp"
#include "dogen/cpp/serialization/file_types_ser.hpp"
#include "dogen/cpp/serialization/function_specifier_types_ser.hpp"
#include "dogen/cpp/serialization/function_types_ser.hpp"
#include "dogen/cpp/serialization/fundamental_types_ser.hpp"
#include "dogen/cpp/serialization/member_declaration_ser.hpp"
#include "dogen/cpp/serialization/member_specification_ser.hpp"
#include "dogen/cpp/serialization/namespace_info_ser.hpp"
#include "dogen/cpp/serialization/nested_type_info_ser.hpp"
#include "dogen/cpp/serialization/odb_options_info_ser.hpp"
#include "dogen/cpp/serialization/parameter_declaration_ser.hpp"
#include "dogen/cpp/serialization/parent_info_ser.hpp"
#include "dogen/cpp/serialization/pointer_types_ser.hpp"
#include "dogen/cpp/serialization/project_ser.hpp"
#include "dogen/cpp/serialization/property_info_ser.hpp"
#include "dogen/cpp/serialization/qualified_id_ser.hpp"
#include "dogen/cpp/serialization/registrar_info_ser.hpp"
#include "dogen/cpp/serialization/registrar_ser.hpp"
#include "dogen/cpp/serialization/scope_ser.hpp"
#include "dogen/cpp/serialization/scope_types_ser.hpp"
#include "dogen/cpp/serialization/source_file_ser.hpp"
#include "dogen/cpp/serialization/storage_class_types_ser.hpp"
#include "dogen/cpp/serialization/template_argument_ser.hpp"
#include "dogen/cpp/serialization/template_id_ser.hpp"
#include "dogen/cpp/serialization/type_specifier_ser.hpp"
#include "dogen/cpp/serialization/visitor_info_ser.hpp"
