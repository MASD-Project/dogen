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
#ifndef DOGEN_ANNOTATIONS_SERIALIZATION_ALL_SER_HPP
#define DOGEN_ANNOTATIONS_SERIALIZATION_ALL_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/annotations/serialization/name_ser.hpp"
#include "dogen/annotations/serialization/text_ser.hpp"
#include "dogen/annotations/serialization/type_ser.hpp"
#include "dogen/annotations/serialization/value_ser.hpp"
#include "dogen/annotations/serialization/number_ser.hpp"
#include "dogen/annotations/serialization/boolean_ser.hpp"
#include "dogen/annotations/serialization/profile_ser.hpp"
#include "dogen/annotations/serialization/scribble_ser.hpp"
#include "dogen/annotations/serialization/annotation_ser.hpp"
#include "dogen/annotations/serialization/scope_types_ser.hpp"
#include "dogen/annotations/serialization/value_types_ser.hpp"
#include "dogen/annotations/serialization/type_template_ser.hpp"
#include "dogen/annotations/serialization/entry_template_ser.hpp"
#include "dogen/annotations/serialization/scribble_group_ser.hpp"
#include "dogen/annotations/serialization/template_kinds_ser.hpp"
#include "dogen/annotations/serialization/text_collection_ser.hpp"
#include "dogen/annotations/serialization/type_repository_ser.hpp"
#include "dogen/annotations/serialization/annotation_group_ser.hpp"
#include "dogen/annotations/serialization/archetype_location_ser.hpp"
#include "dogen/annotations/serialization/profile_repository_ser.hpp"
#include "dogen/annotations/serialization/profiler_configuration_ser.hpp"
#include "dogen/annotations/serialization/archetype_location_repository_ser.hpp"

#endif
