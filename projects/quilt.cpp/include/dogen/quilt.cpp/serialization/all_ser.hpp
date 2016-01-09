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
#ifndef DOGEN_QUILT_CPP_SERIALIZATION_ALL_SER_HPP
#define DOGEN_QUILT_CPP_SERIALIZATION_ALL_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/quilt.cpp/serialization/registrar_ser.hpp"
#include "dogen/quilt.cpp/serialization/settings/bundle_ser.hpp"
#include "dogen/quilt.cpp/serialization/formatters/context_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/entity_ser.hpp"
#include "dogen/quilt.cpp/serialization/formatters/file_types_ser.hpp"
#include "dogen/quilt.cpp/serialization/settings/odb_settings_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/enum_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/settings/path_settings_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/class_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formattable_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/parent_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/settings/aspect_settings_ser.hpp"
#include "dogen/quilt.cpp/serialization/settings/opaque_settings_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/concept_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/origin_types_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/visitor_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/property_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/settings/bundle_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/exception_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/includers_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/namespace_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/primitive_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/registrar_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/cmakelists_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/enumerator_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/nested_type_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/odb_options_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/path_derivatives_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/visited_type_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formatter_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/settings/directory_names_settings_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/enablement_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/settings/inclusion_directive_settings_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/forward_declarations_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/settings/inclusion_directives_settings_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/path_derivatives_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/global_enablement_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/integrated_facets_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formatter_properties_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/inclusion_directives_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/inclusion_dependencies_repository_ser.hpp"

#endif
