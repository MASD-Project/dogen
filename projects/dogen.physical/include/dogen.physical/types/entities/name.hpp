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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_NAME_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace dogen::physical::entities {

class name final {
public:
    name() = default;
    name(const name&) = default;
    ~name() = default;

public:
    name(name&& rhs);

public:
    name(
        const std::string& simple,
        const boost::filesystem::path& qualified);

public:
    /**
     * @brief File or directory simple name.
     */
    /**@{*/
    const std::string& simple() const;
    std::string& simple();
    void simple(const std::string& v);
    void simple(const std::string&& v);
    /**@}*/

    /**
     * @brief Absolute path to the file or directory.
     *
     * The qualified name indicates the location in the filesystem where it will be
     * written or where it was sourced from.
     */
    /**@{*/
    const boost::filesystem::path& qualified() const;
    boost::filesystem::path& qualified();
    void qualified(const boost::filesystem::path& v);
    void qualified(const boost::filesystem::path&& v);
    /**@}*/

public:
    bool operator==(const name& rhs) const;
    bool operator!=(const name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(name& other) noexcept;
    name& operator=(name other);

private:
    std::string simple_;
    boost::filesystem::path qualified_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::name& lhs,
    dogen::physical::entities::name& rhs) {
    lhs.swap(rhs);
}

}

#endif
