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
#ifndef DOGEN_PHYSICAL_TYPES_HELPERS_QUALIFIED_NAME_BUILDER_HPP
#define DOGEN_PHYSICAL_TYPES_HELPERS_QUALIFIED_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.physical/types/entities/location.hpp"

namespace dogen::physical::helpers {

/**
 * @brief Builds qualified names according to the geometry of physical
 * space.
 *
 * If the names and locations are not valid for the requests in
 * question, we throw.
 */
class qualified_name_builder final {
public:
    /**
     * @brief Builds a qualified name for the kernel region in
     * physical space.
     */
    /**@{*/
    static std::string build_kernel(const entities::location& l);
    static std::string build_kernel(const entities::meta_name& mn);
    /**@}*/

    /**
     * @brief Builds a qualified name for the backend region in
     * physical space.
     */
    /**@{*/
    static std::string build_backend(const entities::location& l);
    static std::string build_backend(const entities::meta_name& n);
    /**@}*/

    /**
     * @brief Builds a qualified name for the facet region in physical
     * space.
     */
    /**@{*/
    static std::string build_facet(const entities::location& l,
        const bool add_canonical = false);
    static std::string build_facet(const entities::meta_name& n,
        const bool add_canonical = false);
    /**@}*/

    /**
     * @brief Builds a qualified name for the complete archetype.
     */
    /**@{*/
    static std::string build_archetype(const entities::location& l);
    static std::string build_archetype(const entities::meta_name& n);
    /**@}*/
};

}

#endif
