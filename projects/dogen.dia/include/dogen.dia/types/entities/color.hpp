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
#ifndef DOGEN_DIA_TYPES_ENTITIES_COLOR_HPP
#define DOGEN_DIA_TYPES_ENTITIES_COLOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::dia::entities {

/**
 * @brief Represents a color in a diagram.
 */
class color final {
public:
    color() = default;
    color(const color&) = default;
    color(color&&) = default;
    ~color() = default;

public:
    explicit color(const std::string& value);

public:
    /**
     * @brief Text representation of an RGB value in hex.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const color& rhs) const;
    bool operator!=(const color& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(color& other) noexcept;
    color& operator=(color other);

private:
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::color& lhs,
    dogen::dia::entities::color& rhs) {
    lhs.swap(rhs);
}

}

#endif
