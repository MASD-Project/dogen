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
#ifndef DOGEN_OM_TYPES_OM_HPP
#define DOGEN_OM_TYPES_OM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {

/**
 * @brief OM is the Output Model.
 *
 * @section om_0 Objective
 *
 * OM was designed to model the contents of the files to output with only the
 * required level of flexibility needed by Dogen. Thus it does not aim to model
 * the language at the specification level - e.g. like an AST - nor is it as
 * abstract as SML. Getting the modeling at the right level of granularity took
 * quite a few attempts and we do not claim to have perfected it just yet;
 * however, we did take into account all of the existing use cases revealed by
 * Dogen thus far and made sure they were all handled in a clean (or clean-ish)
 * manner.
 *
 * The objective of this model is to provide all of the data structures that a
 * "file renderer" would need to create valid source code. It is presumed that
 * the "file renderer" is processing the data structures in the model in a
 * sequential fashion, and as such, each data structure should provide all of
 * the information required for it to be rendered without any further lookups.
 *
 * @section om_1 Future Directions
 *
 * OM only supports C++ at present, but it is designed to be extended in the
 * future with other languages such as Java, C# etc.
 *
 *
 */
namespace om {
} }

#endif
