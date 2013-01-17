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
#ifndef DOGEN_ENUMERATION_ODB_A_CLASS_ODB_HPP
#define DOGEN_ENUMERATION_ODB_A_CLASS_ODB_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/enumeration/types/a_class.hpp"

namespace dogen {
namespace enumeration {

#ifdef ODB_COMPILER

#pragma db object(a_class)

#pragma db member(a_class::colour_type_) colour_type
#pragma db member(a_class::book_type_) book_type
#pragma db member(a_class::shape_type_) shape_type

#endif

} }

#endif
