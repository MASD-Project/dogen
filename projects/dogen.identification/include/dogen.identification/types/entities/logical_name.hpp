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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_NAME_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/logical_location.hpp"
#include "dogen.identification/types/entities/qualified_name_representations.hpp"

namespace dogen::identification::entities {

/**
 * @brief Name of an element in logical space.
 *
 * A name represents a point or a region in logical space, and this point or region can
 * only be used by one element. Names can be uniquely identified by their qualified ID.
 *
 * Name has the following properties: a) two different points or regions in logical
 * space cannot have the same name and b) the same point in logical space can only
 * have one and only one name.
 *
 * Names are required in addition to just using the qualfied ID representation
 * because we use them to infer all sorts of properties for an element (namespaces,
 * naming files, etc).
 */
class logical_name final {
public:
    logical_name(const logical_name&) = default;
    logical_name(logical_name&&) = default;
    ~logical_name() = default;

public:
    logical_name();

public:
    logical_name(
        const std::string& simple,
        const dogen::identification::entities::qualified_name_representations& qualified,
        const dogen::identification::entities::logical_id& id,
        const dogen::identification::entities::logical_location& location,
        const bool is_container);

public:
    /**
     * @brief Simple name for a modeling element.
     */
    /**@{*/
    const std::string& simple() const;
    std::string& simple();
    void simple(const std::string& v);
    void simple(const std::string&& v);
    /**@}*/

    /**
     * @brief Contains the name according to different representations.
     */
    /**@{*/
    const dogen::identification::entities::qualified_name_representations& qualified() const;
    dogen::identification::entities::qualified_name_representations& qualified();
    void qualified(const dogen::identification::entities::qualified_name_representations& v);
    void qualified(const dogen::identification::entities::qualified_name_representations&& v);
    /**@}*/

    /**
     * @brief Identifier for this logical element.
     */
    /**@{*/
    const dogen::identification::entities::logical_id& id() const;
    dogen::identification::entities::logical_id& id();
    void id(const dogen::identification::entities::logical_id& v);
    void id(const dogen::identification::entities::logical_id&& v);
    /**@}*/

    /**
     * @brief Where the name is located in element space.
     */
    /**@{*/
    const dogen::identification::entities::logical_location& location() const;
    dogen::identification::entities::logical_location& location();
    void location(const dogen::identification::entities::logical_location& v);
    void location(const dogen::identification::entities::logical_location&& v);
    /**@}*/

    /**
     * @brief If true, the name indicates an element that can contain other elements.
     */
    /**@{*/
    bool is_container() const;
    void is_container(const bool v);
    /**@}*/

public:
    bool operator==(const logical_name& rhs) const;
    bool operator!=(const logical_name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_name& other) noexcept;
    logical_name& operator=(logical_name other);

private:
    std::string simple_;
    dogen::identification::entities::qualified_name_representations qualified_;
    dogen::identification::entities::logical_id id_;
    dogen::identification::entities::logical_location location_;
    bool is_container_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::logical_name& lhs,
    dogen::identification::entities::logical_name& rhs) {
    lhs.swap(rhs);
}

}

#endif
