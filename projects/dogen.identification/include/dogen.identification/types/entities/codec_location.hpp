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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_CODEC_LOCATION_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_CODEC_LOCATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen::identification::entities {

/**
 * @brief Location of a modeling element in the codec dimension.
 */
class codec_location final {
public:
    codec_location(const codec_location&) = default;
    codec_location(codec_location&&) = default;
    ~codec_location() = default;

public:
    codec_location();

public:
    codec_location(
        const long line,
        const long column);

public:
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
    bool operator==(const codec_location& rhs) const;
    bool operator!=(const codec_location& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(codec_location& other) noexcept;
    codec_location& operator=(codec_location other);

private:
    long line_;
    long column_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::codec_location& lhs,
    dogen::identification::entities::codec_location& rhs) {
    lhs.swap(rhs);
}

}

#endif
