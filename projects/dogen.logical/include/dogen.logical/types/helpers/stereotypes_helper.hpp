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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_STEREOTYPES_HELPER_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_STEREOTYPES_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include "dogen.identification/types/entities/stereotype.hpp"
#include "dogen.logical/types/entities/stereotypes.hpp"
#include "dogen.logical/types/entities/static_stereotypes.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Converts well-known stereotypes from and to strings.
 */
class stereotypes_helper final {
public:
    /**
     * @brief Converts a single well-known stereotype into its enum.
     *
     * @note The stereotype primitive must not have any leading or
     * trailing spaces or other artefacts and must match exactly the
     * definition of a well-known logical stereotype,
     * e.g. 'logical::object', etc.
     */
    entities::static_stereotypes
    from_primitive(const identification::entities::stereotype& st) const;

public:
    /**
     * @brief Given a list of stereotypes, returns the set of
     * well-known stereotypes as well as those it does not know of.
     */
    entities::stereotypes
    from_primitives(const std::list<identification::entities::stereotype>&
        stereotypes) const;

    /**
     * @brief Converts a well-known stereotype to its primitive
     * representation.
     */
    identification::entities::stereotype
    to_primitive(const entities::static_stereotypes ss) const;

public:
    /**
     * @brief Returns true if the well-known stereotype denotes a logical
     * element type, false otherwise.
     */
    bool
    is_element_type(const entities::static_stereotypes ss) const;

    /**
     * @brief Given a list of well-known stereotypes, extracts those
     * which are element types.
     */
    std::list<entities::static_stereotypes> extract_element_types(
        const std::list<entities::static_stereotypes>& ss) const;

    /**
     * @brief Given a list of well-known stereotypes, extracts those
     * which are not element types.
     */
    std::list<entities::static_stereotypes>
    extract_non_element_types(
        const std::list<entities::static_stereotypes>& ss) const;
};

}

#endif
