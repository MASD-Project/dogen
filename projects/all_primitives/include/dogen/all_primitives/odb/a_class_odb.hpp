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
#ifndef DOGEN_ALL_PRIMITIVES_ODB_A_CLASS_ODB_HPP
#define DOGEN_ALL_PRIMITIVES_ODB_A_CLASS_ODB_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/all_primitives/types/a_class.hpp"

namespace dogen {
namespace all_primitives {

#ifdef ODB_COMPILER

#pragma db object(a_class)

#pragma db member(a_class::bool_property_) bool_property
#pragma db member(a_class::char_property_) char_property
#pragma db member(a_class::uchar_property_) uchar_property
#pragma db member(a_class::int_property_) int_property
#pragma db member(a_class::uint_property_) uint_property
#pragma db member(a_class::long_property_) long_property
#pragma db member(a_class::ulong_property_) ulong_property
#pragma db member(a_class::long_long_property_) long_long_property
#pragma db member(a_class::ulong_long_property_) ulong_long_property
#pragma db member(a_class::short_property_) short_property
#pragma db member(a_class::ushort_property_) ushort_property
#pragma db member(a_class::double_property_) double_property
#pragma db member(a_class::float_property_) float_property
#pragma db member(a_class::versioned_key_) versioned_key

#endif

} }

#endif
