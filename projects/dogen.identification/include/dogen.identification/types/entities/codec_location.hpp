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
#include <boost/filesystem/path.hpp>

namespace dogen::identification::entities {

/**
 * @brief Location of a modeling element in the codec dimension.
 */
class codec_location final {
public:
    codec_location(const codec_location&) = default;
    ~codec_location() = default;

public:
    codec_location();

public:
    codec_location(codec_location&& rhs);

public:
    codec_location(
        const boost::filesystem::path& full_path,
        const long line);

public:
    /**
     * @brief Full path to the file that was read, if any.
     */
    /**@{*/
    const boost::filesystem::path& full_path() const;
    boost::filesystem::path& full_path();
    void full_path(const boost::filesystem::path& v);
    void full_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Line number where the element was defined.
     */
    /**@{*/
    long line() const;
    void line(const long v);
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
    boost::filesystem::path full_path_;
    long line_;
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
