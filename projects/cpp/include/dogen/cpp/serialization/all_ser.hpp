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
#include "dogen/cpp/serialization/expansion/expansion_inputs_ser.hpp"
#include "dogen/cpp/serialization/expansion/path_derivatives_ser.hpp"
#include "dogen/cpp/serialization/formattables/abilities_ser.hpp"
#include "dogen/cpp/serialization/formattables/aspect_types_ser.hpp"
#include "dogen/cpp/serialization/formattables/class_aspects_ser.hpp"
#include "dogen/cpp/serialization/formattables/class_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/class_types_ser.hpp"
#include "dogen/cpp/serialization/formattables/cmakelists_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/concept_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/content_descriptor_ser.hpp"
#include "dogen/cpp/serialization/formattables/content_types_ser.hpp"
#include "dogen/cpp/serialization/formattables/entity_ser.hpp"
#include "dogen/cpp/serialization/formattables/enum_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/enumerator_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/exception_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/family_types_ser.hpp"
#include "dogen/cpp/serialization/formattables/file_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/file_types_ser.hpp"
#include "dogen/cpp/serialization/formattables/formattable_ser.hpp"
#include "dogen/cpp/serialization/formattables/includes_ser.hpp"
#include "dogen/cpp/serialization/formattables/inheritance_ser.hpp"
#include "dogen/cpp/serialization/formattables/namespace_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/nested_type_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/new_class_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/odb_options_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/parent_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/primitive_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/project_ser.hpp"
#include "dogen/cpp/serialization/formattables/property_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/registrar_info_ser.hpp"
#include "dogen/cpp/serialization/formattables/state_ser.hpp"
#include "dogen/cpp/serialization/formattables/visitor_info_ser.hpp"
#include "dogen/cpp/serialization/formatters/file_types_ser.hpp"
#include "dogen/cpp/serialization/formatters/formatter_types_ser.hpp"
#include "dogen/cpp/serialization/formatters/serialization/settings_ser.hpp"
#include "dogen/cpp/serialization/registrar_ser.hpp"
#include "dogen/cpp/serialization/settings/bundle_ser.hpp"
#include "dogen/cpp/serialization/settings/formatter_settings_ser.hpp"
#include "dogen/cpp/serialization/settings/odb_settings_ser.hpp"
#include "dogen/cpp/serialization/settings/opaque_settings_ser.hpp"
#include "dogen/cpp/serialization/settings/path_settings_ser.hpp"
#include "dogen/cpp/serialization/settings/type_settings_ser.hpp"
