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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_META_NAME_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_META_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.physical/types/entities/location.hpp"

namespace dogen::physical::entities {

/**
 * @brief Name of an element in physical space.
 *
 * A name represents a point or a region in physical space. It can only be used by one
 * physical element. Names can be uniquely identified by their qualified ID.
 *
 * Name has the following properties: a) two different points or regionsin physical
 * space cannot have the same name and b) the same point or region in physical space
 * can only have one and only one name.
 */
class meta_name final {
public:
    meta_name() = default;
    meta_name(const meta_name&) = default;
    meta_name(meta_name&&) = default;
    ~meta_name() = default;

public:
    meta_name(
        const std::string& simple,
        const std::string& qualified,
        const dogen::physical::entities::location& location);

public:
    /**
     * @brief Simple (non-qualified) name of the physical element at this address.
     *
     * The simple name must be unique for a given location.
     */
    /**@{*/
    const std::string& simple() const;
    std::string& simple();
    void simple(const std::string& v);
    void simple(const std::string&& v);
    /**@}*/

    /**
     * @brief Qualified name for a physical element.
     */
    /**@{*/
    const std::string& qualified() const;
    std::string& qualified();
    void qualified(const std::string& v);
    void qualified(const std::string&& v);
    /**@}*/

    /**
     * @brief Location for a name in physical space.
     */
    /**@{*/
    const dogen::physical::entities::location& location() const;
    dogen::physical::entities::location& location();
    void location(const dogen::physical::entities::location& v);
    void location(const dogen::physical::entities::location&& v);
    /**@}*/

public:
    bool operator==(const meta_name& rhs) const;
    bool operator!=(const meta_name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(meta_name& other) noexcept;
    meta_name& operator=(meta_name other);

private:
    std::string simple_;
    std::string qualified_;
    dogen::physical::entities::location location_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::meta_name& lhs,
    dogen::physical::entities::meta_name& rhs) {
    lhs.swap(rhs);
}

}

#endif
