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
#include "dogen/cpp/io/abilities_io.hpp"
#include "dogen/cpp/io/aspect_types_io.hpp"
#include "dogen/cpp/io/class_aspects_io.hpp"
#include "dogen/cpp/io/class_info_io.hpp"
#include "dogen/cpp/io/class_types_io.hpp"
#include "dogen/cpp/io/cmakelists_info_io.hpp"
#include "dogen/cpp/io/concept_info_io.hpp"
#include "dogen/cpp/io/content_descriptor_io.hpp"
#include "dogen/cpp/io/content_types_io.hpp"
#include "dogen/cpp/io/cpp_settings_io.hpp"
#include "dogen/cpp/io/entity_io.hpp"
#include "dogen/cpp/io/enum_info_io.hpp"
#include "dogen/cpp/io/enumerator_info_io.hpp"
#include "dogen/cpp/io/exception_info_io.hpp"
#include "dogen/cpp/io/facet_settings_io.hpp"
#include "dogen/cpp/io/file_info_io.hpp"
#include "dogen/cpp/io/file_settings_io.hpp"
#include "dogen/cpp/io/file_types_io.hpp"
#include "dogen/cpp/io/formatter_settings_io.hpp"
#include "dogen/cpp/io/formatters/formatter_types_io.hpp"
#include "dogen/cpp/io/formatters/odb/settings_io.hpp"
#include "dogen/cpp/io/formatters/serialization/settings_io.hpp"
#include "dogen/cpp/io/global_settings_io.hpp"
#include "dogen/cpp/io/includes_io.hpp"
#include "dogen/cpp/io/inheritance_io.hpp"
#include "dogen/cpp/io/namespace_info_io.hpp"
#include "dogen/cpp/io/nested_type_info_io.hpp"
#include "dogen/cpp/io/new_class_info_io.hpp"
#include "dogen/cpp/io/odb_options_info_io.hpp"
#include "dogen/cpp/io/parent_info_io.hpp"
#include "dogen/cpp/io/primitive_info_io.hpp"
#include "dogen/cpp/io/project_io.hpp"
#include "dogen/cpp/io/property_info_io.hpp"
#include "dogen/cpp/io/registrar_info_io.hpp"
#include "dogen/cpp/io/state_io.hpp"
#include "dogen/cpp/io/visitor_info_io.hpp"
