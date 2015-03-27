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
#include "dogen/cpp/hash/formattables/abilities_hash.hpp"
#include "dogen/cpp/hash/formattables/aspect_types_hash.hpp"
#include "dogen/cpp/hash/formattables/class_aspects_hash.hpp"
#include "dogen/cpp/hash/formattables/class_info_hash.hpp"
#include "dogen/cpp/hash/formattables/class_types_hash.hpp"
#include "dogen/cpp/hash/formattables/cmakelists_info_hash.hpp"
#include "dogen/cpp/hash/formattables/concept_info_hash.hpp"
#include "dogen/cpp/hash/formattables/content_descriptor_hash.hpp"
#include "dogen/cpp/hash/formattables/content_types_hash.hpp"
#include "dogen/cpp/hash/formattables/entity_hash.hpp"
#include "dogen/cpp/hash/formattables/enum_info_hash.hpp"
#include "dogen/cpp/hash/formattables/enumerator_info_hash.hpp"
#include "dogen/cpp/hash/formattables/exception_info_hash.hpp"
#include "dogen/cpp/hash/formattables/family_types_hash.hpp"
#include "dogen/cpp/hash/formattables/file_info_hash.hpp"
#include "dogen/cpp/hash/formattables/file_types_hash.hpp"
#include "dogen/cpp/hash/formattables/formattable_hash.hpp"
#include "dogen/cpp/hash/formattables/includes_hash.hpp"
#include "dogen/cpp/hash/formattables/inheritance_hash.hpp"
#include "dogen/cpp/hash/formattables/namespace_info_hash.hpp"
#include "dogen/cpp/hash/formattables/nested_type_info_hash.hpp"
#include "dogen/cpp/hash/formattables/new_class_info_hash.hpp"
#include "dogen/cpp/hash/formattables/odb_options_info_hash.hpp"
#include "dogen/cpp/hash/formattables/parent_info_hash.hpp"
#include "dogen/cpp/hash/formattables/primitive_info_hash.hpp"
#include "dogen/cpp/hash/formattables/project_hash.hpp"
#include "dogen/cpp/hash/formattables/property_info_hash.hpp"
#include "dogen/cpp/hash/formattables/registrar_info_hash.hpp"
#include "dogen/cpp/hash/formattables/state_hash.hpp"
#include "dogen/cpp/hash/formattables/visitor_info_hash.hpp"
#include "dogen/cpp/hash/formatters/file_types_hash.hpp"
#include "dogen/cpp/hash/formatters/formatter_types_hash.hpp"
#include "dogen/cpp/hash/formatters/serialization/settings_hash.hpp"
#include "dogen/cpp/hash/settings/bundle_hash.hpp"
#include "dogen/cpp/hash/settings/formatter_settings_hash.hpp"
#include "dogen/cpp/hash/settings/odb_settings_hash.hpp"
#include "dogen/cpp/hash/settings/opaque_settings_hash.hpp"
#include "dogen/cpp/hash/settings/path_settings_hash.hpp"
#include "dogen/cpp/hash/settings/type_settings_hash.hpp"
