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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_KIND_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_KIND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::physical::entities {

class archetype_kind final {
public:
    archetype_kind() = default;
    archetype_kind(const archetype_kind&) = default;
    archetype_kind(archetype_kind&&) = default;
    ~archetype_kind() = default;

public:
    archetype_kind(
        const std::string& description,
        const std::string& id,
        const std::string& file_extension);

public:
    /**
     * @brief Human readable description of the entity.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);

    const std::string& file_extension() const;
    std::string& file_extension();
    void file_extension(const std::string& v);
    void file_extension(const std::string&& v);

public:
    bool operator==(const archetype_kind& rhs) const;
    bool operator!=(const archetype_kind& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_kind& other) noexcept;
    archetype_kind& operator=(archetype_kind other);

private:
    std::string description_;
    std::string id_;
    std::string file_extension_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::archetype_kind& lhs,
    dogen::physical::entities::archetype_kind& rhs) {
    lhs.swap(rhs);
}

}

#endif
