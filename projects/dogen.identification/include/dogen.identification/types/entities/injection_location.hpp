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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_INJECTION_LOCATION_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_INJECTION_LOCATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.identification/types/entities/uri.hpp"

namespace dogen::identification::entities {

/**
 * @brief Location of a modeling element in the injection dimension.
 */
class injection_location final {
public:
    injection_location(const injection_location&) = default;
    injection_location(injection_location&&) = default;
    ~injection_location() = default;

public:
    injection_location();

public:
    injection_location(
        const dogen::identification::entities::uri& uri,
        const long line,
        const long column);

public:
    /**
     * @brief URI to the model that contained this element.
     */
    /**@{*/
    const dogen::identification::entities::uri& uri() const;
    dogen::identification::entities::uri& uri();
    void uri(const dogen::identification::entities::uri& v);
    void uri(const dogen::identification::entities::uri&& v);
    /**@}*/

    /**
     * @brief Line number where the element was defined.
     */
    /**@{*/
    long line() const;
    void line(const long v);
    /**@}*/

    /**
     * @brief Column number where the element was defined.
     */
    /**@{*/
    long column() const;
    void column(const long v);
    /**@}*/

public:
    bool operator==(const injection_location& rhs) const;
    bool operator!=(const injection_location& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(injection_location& other) noexcept;
    injection_location& operator=(injection_location other);

private:
    dogen::identification::entities::uri uri_;
    long line_;
    long column_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::injection_location& lhs,
    dogen::identification::entities::injection_location& rhs) {
    lhs.swap(rhs);
}

}

#endif
