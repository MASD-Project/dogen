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
#ifndef DOGEN_QUILT_CPP_IO_ALL_IO_HPP
#define DOGEN_QUILT_CPP_IO_ALL_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/quilt.cpp/io/fabric/registrar_io.hpp"
#include "dogen/quilt.cpp/io/fabric/cmakelists_io.hpp"
#include "dogen/quilt.cpp/io/fabric/odb_options_io.hpp"
#include "dogen/quilt.cpp/io/formattables/model_io.hpp"
#include "dogen/quilt.cpp/io/fabric/master_header_io.hpp"
#include "dogen/quilt.cpp/io/formattables/formattable_io.hpp"
#include "dogen/quilt.cpp/io/formattables/facet_profile_io.hpp"
#include "dogen/quilt.cpp/io/formattables/profile_group_io.hpp"
#include "dogen/quilt.cpp/io/formattables/profile_types_io.hpp"
#include "dogen/quilt.cpp/io/annotations/odb_annotations_io.hpp"
#include "dogen/quilt.cpp/io/fabric/forward_declarations_io.hpp"
#include "dogen/quilt.cpp/io/annotations/path_annotations_io.hpp"
#include "dogen/quilt.cpp/io/annotations/opaque_annotations_io.hpp"
#include "dogen/quilt.cpp/io/formattables/formatter_profile_io.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_descriptor_io.hpp"
#include "dogen/quilt.cpp/io/formattables/decoration_profile_io.hpp"
#include "dogen/quilt.cpp/io/formattables/facet_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/aspect_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/opaque_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/element_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formatters/inclusion_support_types_io.hpp"
#include "dogen/quilt.cpp/io/formattables/formatter_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/streaming_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/local_enablement_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/global_enablement_configuration_io.hpp"
#include "dogen/quilt.cpp/io/formattables/inclusion_directive_configuration_io.hpp"

#endif
