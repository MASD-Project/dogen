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
#ifndef DOGEN_QUILT_CPP_HASH_ALL_HASH_HPP
#define DOGEN_QUILT_CPP_HASH_ALL_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/quilt.cpp/hash/fabric/registrar_hash.hpp"
#include "dogen/quilt.cpp/hash/fabric/cmakelists_hash.hpp"
#include "dogen/quilt.cpp/hash/fabric/odb_options_hash.hpp"
#include "dogen/quilt.cpp/hash/fabric/master_header_hash.hpp"
#include "dogen/quilt.cpp/hash/formatters/file_types_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/odb_annotations_hash.hpp"
#include "dogen/quilt.cpp/hash/fabric/forward_declarations_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/path_annotations_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/path_derivatives_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/aspect_annotations_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/helper_annotations_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/opaque_annotations_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/aspect_properties_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/helper_descriptor_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/helper_properties_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/element_annotations_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/element_properties_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/streaming_annotations_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/formatter_properties_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/enablement_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/formatters/inclusion_support_types_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/inclusion_path_support_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/directory_names_annotations_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/path_derivatives_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/aspect_annotations_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/helper_annotations_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/aspect_properties_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/global_enablement_properties_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/helper_properties_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/element_annotations_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/element_properties_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/inclusion_directive_annotations_hash.hpp"
#include "dogen/quilt.cpp/hash/annotations/streaming_annotations_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/formatter_properties_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/inclusion_directives_repository_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/inclusion_dependencies_repository_hash.hpp"

#endif
