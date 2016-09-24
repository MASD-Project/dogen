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
#include "dogen/quilt.cpp/serialization/fabric/odb_options_ser.hpp"
#include "dogen/quilt.cpp/serialization/fabric/master_header_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formattable_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/odb_annotations_ser.hpp"
#include "dogen/quilt.cpp/serialization/fabric/forward_declarations_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/path_annotations_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/path_derivatives_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/aspect_annotations_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/helper_annotations_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/opaque_annotations_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_descriptor_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/element_annotations_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/streaming_annotations_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/aspect_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/element_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/enablement_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formatters/inclusion_support_types_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formatter_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/directory_names_annotations_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/path_derivatives_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/aspect_annotations_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/helper_annotations_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/aspect_properties_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/global_enablement_properties_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_properties_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/element_annotations_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/element_properties_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/inclusion_directive_annotations_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/local_enablement_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/annotations/streaming_annotations_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formatter_properties_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/global_enablement_configuration_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/inclusion_directives_repository_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/inclusion_dependencies_repository_ser.hpp"

#endif
