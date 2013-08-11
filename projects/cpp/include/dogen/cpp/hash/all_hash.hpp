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
#include "dogen/cpp/hash/access_specifier_types_hash.hpp"
#include "dogen/cpp/hash/aspect_types_hash.hpp"
#include "dogen/cpp/hash/base_specifier_hash.hpp"
#include "dogen/cpp/hash/class_head_hash.hpp"
#include "dogen/cpp/hash/class_info_hash.hpp"
#include "dogen/cpp/hash/class_key_types_hash.hpp"
#include "dogen/cpp/hash/class_specifier_hash.hpp"
#include "dogen/cpp/hash/class_types_hash.hpp"
#include "dogen/cpp/hash/cmakelists_info_hash.hpp"
#include "dogen/cpp/hash/content_descriptor_hash.hpp"
#include "dogen/cpp/hash/content_types_hash.hpp"
#include "dogen/cpp/hash/cv_qualifier_types_hash.hpp"
#include "dogen/cpp/hash/decl_specifier_hash.hpp"
#include "dogen/cpp/hash/declarator_hash.hpp"
#include "dogen/cpp/hash/entity_hash.hpp"
#include "dogen/cpp/hash/enum_info_hash.hpp"
#include "dogen/cpp/hash/enumerator_info_hash.hpp"
#include "dogen/cpp/hash/exception_info_hash.hpp"
#include "dogen/cpp/hash/file_types_hash.hpp"
#include "dogen/cpp/hash/function_specifier_types_hash.hpp"
#include "dogen/cpp/hash/function_types_hash.hpp"
#include "dogen/cpp/hash/fundamental_types_hash.hpp"
#include "dogen/cpp/hash/member_declaration_hash.hpp"
#include "dogen/cpp/hash/member_specification_hash.hpp"
#include "dogen/cpp/hash/namespace_info_hash.hpp"
#include "dogen/cpp/hash/nested_type_info_hash.hpp"
#include "dogen/cpp/hash/odb_options_info_hash.hpp"
#include "dogen/cpp/hash/parameter_declaration_hash.hpp"
#include "dogen/cpp/hash/parent_info_hash.hpp"
#include "dogen/cpp/hash/pointer_types_hash.hpp"
#include "dogen/cpp/hash/project_hash.hpp"
#include "dogen/cpp/hash/property_info_hash.hpp"
#include "dogen/cpp/hash/qualified_id_hash.hpp"
#include "dogen/cpp/hash/registrar_info_hash.hpp"
#include "dogen/cpp/hash/scope_hash.hpp"
#include "dogen/cpp/hash/scope_types_hash.hpp"
#include "dogen/cpp/hash/source_file_hash.hpp"
#include "dogen/cpp/hash/storage_class_types_hash.hpp"
#include "dogen/cpp/hash/template_argument_hash.hpp"
#include "dogen/cpp/hash/template_id_hash.hpp"
#include "dogen/cpp/hash/type_specifier_hash.hpp"
#include "dogen/cpp/hash/visitor_info_hash.hpp"
