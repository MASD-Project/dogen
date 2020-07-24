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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_META_NAME_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_META_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/logical_meta_id.hpp"

namespace dogen::identification::entities {

class logical_meta_name final {
public:
    logical_meta_name() = default;
    logical_meta_name(const logical_meta_name&) = default;
    logical_meta_name(logical_meta_name&&) = default;
    ~logical_meta_name() = default;

public:
    logical_meta_name(
        const std::string& simple,
        const dogen::identification::entities::logical_meta_id& id);

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
     * @brief Identifier for this logical meta-element.
     */
    /**@{*/
    const dogen::identification::entities::logical_meta_id& id() const;
    dogen::identification::entities::logical_meta_id& id();
    void id(const dogen::identification::entities::logical_meta_id& v);
    void id(const dogen::identification::entities::logical_meta_id&& v);
    /**@}*/

public:
    bool operator==(const logical_meta_name& rhs) const;
    bool operator!=(const logical_meta_name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_meta_name& other) noexcept;
    logical_meta_name& operator=(logical_meta_name other);

private:
    std::string simple_;
    dogen::identification::entities::logical_meta_id id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::logical_meta_name& lhs,
    dogen::identification::entities::logical_meta_name& rhs) {
    lhs.swap(rhs);
}

}

#endif
