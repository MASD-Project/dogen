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
#ifndef DOGEN_BOOST_MODEL_ODB_CLASS_B_ODB_HPP
#define DOGEN_BOOST_MODEL_ODB_CLASS_B_ODB_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/boost_model/types/class_b.hpp"

namespace dogen {
namespace boost_model {

#ifdef ODB_COMPILER

#pragma db object(class_b)

#pragma db member(class_b::prop_0_) prop_0
#pragma db member(class_b::prop_1_) prop_1
#pragma db member(class_b::prop_2_) prop_2
#pragma db member(class_b::prop_3_) prop_3
#pragma db member(class_b::prop_4_) prop_4
#pragma db member(class_b::prop_5_) prop_5
#pragma db member(class_b::prop_6_) prop_6

#endif

} }

#endif
