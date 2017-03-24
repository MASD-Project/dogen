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

#include "dogen/quilt.cpp/serialization/fabric/registrar_ser.hpp"
#include "dogen/quilt.cpp/serialization/fabric/cmakelists_ser.hpp"
#include "dogen/quilt.cpp/serialization/fabric/odb_target_ser.hpp"
#include "dogen/quilt.cpp/serialization/fabric/odb_targets_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/model_ser.hpp"
#include "dogen/quilt.cpp/serialization/fabric/master_header_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formattable_ser.hpp"
#include "dogen/quilt.cpp/serialization/fabric/common_odb_options_ser.hpp"
#include "dogen/quilt.cpp/serialization/fabric/object_odb_options_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/cpp_standards_ser.hpp"
#include "dogen/quilt.cpp/serialization/fabric/forward_declarations_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/odb_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/directive_group_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/facet_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/aspect_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formatting_styles_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_descriptor_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/element_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/artefact_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/streaming_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/locator_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formatters/inclusion_support_types_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formatting_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/directive_group_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/locator_facet_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/local_enablement_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/global_enablement_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/locator_archetype_configuration_ser.hpp"

#endif
