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
#ifndef DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_MODEL_SET_PRAGMAS_HPP
#define DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_MODEL_SET_PRAGMAS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.relational/odb/tracing/io_type_pragmas.hpp"
#include "dogen.relational/odb/tracing/model_set_id_pragmas.hpp"
#include "dogen.relational/odb/tracing/transform_id_pragmas.hpp"
#include "dogen.relational/types/tracing/transform_model_set.hpp"

namespace dogen::relational::tracing {

#ifdef ODB_COMPILER

#pragma db object(transform_model_set) schema("DOGEN")
#pragma db object(transform_model_set) no_id

#endif

}

#endif
