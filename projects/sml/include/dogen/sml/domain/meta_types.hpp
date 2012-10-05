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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_SML_DOMAIN_META_TYPES_HPP
#define DOGEN_SML_DOMAIN_META_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml {

/**
 * @brief Set of all available types of types in SML.
 */
enum class meta_types : unsigned int {
    invalid = 0, ///< we don't yet know the type's type
    enumeration = 1, ///< Type is an enumeration
    pod = 2, ///< Type is Plain Old Data
    attribute = 3, ///< Type is an attribute
    package = 4, ///< Type is a package
    primitive = 5 ///< Type is a package
};

} }

#endif
