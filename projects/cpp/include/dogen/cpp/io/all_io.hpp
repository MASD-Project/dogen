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
#include "dogen/cpp/io/formattables/abilities_io.hpp"
#include "dogen/cpp/io/formattables/aspect_types_io.hpp"
#include "dogen/cpp/io/formattables/class_aspects_io.hpp"
#include "dogen/cpp/io/formattables/class_info_io.hpp"
#include "dogen/cpp/io/formattables/class_types_io.hpp"
#include "dogen/cpp/io/formattables/cmakelists_info_io.hpp"
#include "dogen/cpp/io/formattables/concept_info_io.hpp"
#include "dogen/cpp/io/formattables/content_descriptor_io.hpp"
#include "dogen/cpp/io/formattables/content_types_io.hpp"
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/io/formattables/enum_info_io.hpp"
#include "dogen/cpp/io/formattables/enumerator_info_io.hpp"
#include "dogen/cpp/io/formattables/exception_info_io.hpp"
#include "dogen/cpp/io/formattables/family_types_io.hpp"
#include "dogen/cpp/io/formattables/file_info_io.hpp"
#include "dogen/cpp/io/formattables/file_types_io.hpp"
#include "dogen/cpp/io/formattables/formattable_io.hpp"
#include "dogen/cpp/io/formattables/includes_io.hpp"
#include "dogen/cpp/io/formattables/inheritance_io.hpp"
#include "dogen/cpp/io/formattables/namespace_info_io.hpp"
#include "dogen/cpp/io/formattables/nested_type_info_io.hpp"
#include "dogen/cpp/io/formattables/new_class_info_io.hpp"
#include "dogen/cpp/io/formattables/odb_options_info_io.hpp"
#include "dogen/cpp/io/formattables/parent_info_io.hpp"
#include "dogen/cpp/io/formattables/primitive_info_io.hpp"
#include "dogen/cpp/io/formattables/project_io.hpp"
#include "dogen/cpp/io/formattables/property_info_io.hpp"
#include "dogen/cpp/io/formattables/registrar_info_io.hpp"
#include "dogen/cpp/io/formattables/state_io.hpp"
#include "dogen/cpp/io/formattables/visitor_info_io.hpp"
#include "dogen/cpp/io/formatters/file_types_io.hpp"
#include "dogen/cpp/io/formatters/formatter_types_io.hpp"
#include "dogen/cpp/io/formatters/serialization/settings_io.hpp"
#include "dogen/cpp/io/settings/bundle_io.hpp"
#include "dogen/cpp/io/settings/formatter_settings_io.hpp"
#include "dogen/cpp/io/settings/global_path_settings_io.hpp"
#include "dogen/cpp/io/settings/inclusion_delimiter_types_io.hpp"
#include "dogen/cpp/io/settings/inclusion_io.hpp"
#include "dogen/cpp/io/settings/local_path_settings_io.hpp"
#include "dogen/cpp/io/settings/odb_settings_io.hpp"
#include "dogen/cpp/io/settings/opaque_settings_io.hpp"
#include "dogen/cpp/io/settings/type_settings_io.hpp"
