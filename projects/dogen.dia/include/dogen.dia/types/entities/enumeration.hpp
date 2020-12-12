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
#ifndef DOGEN_DIA_TYPES_ENTITIES_ENUMERATION_HPP
#define DOGEN_DIA_TYPES_ENTITIES_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::dia::entities {

/**
 * @brief Represents a enumeration in a diagram.
 */
class enumeration final {
public:
    enumeration() = default;
    enumeration(const enumeration&) = default;
    enumeration(enumeration&&) = default;
    ~enumeration() = default;

public:
    explicit enumeration(const std::string& value);

public:
    /**
     * @brief Text representation of a enumeration.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const enumeration& rhs) const;
    bool operator!=(const enumeration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(enumeration& other) noexcept;
    enumeration& operator=(enumeration other);

private:
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::enumeration& lhs,
    dogen::dia::entities::enumeration& rhs) {
    lhs.swap(rhs);
}

}

#endif
