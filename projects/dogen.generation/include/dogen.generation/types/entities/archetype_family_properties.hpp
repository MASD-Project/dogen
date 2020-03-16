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
#ifndef DOGEN_GENERATION_TYPES_ENTITIES_ARCHETYPE_FAMILY_PROPERTIES_HPP
#define DOGEN_GENERATION_TYPES_ENTITIES_ARCHETYPE_FAMILY_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::generation::entities {

/**
 * @brief Properties pertaining to families of archetypes, related to the path computation.
 */
class archetype_family_properties final {
public:
    archetype_family_properties() = default;
    archetype_family_properties(const archetype_family_properties&) = default;
    archetype_family_properties(archetype_family_properties&&) = default;
    ~archetype_family_properties() = default;

public:
    explicit archetype_family_properties(const std::string& extension);

public:
    /**
     * @brief Extension to use for files of this group. Includes the leading dot.
     */
    /**@{*/
    const std::string& extension() const;
    std::string& extension();
    void extension(const std::string& v);
    void extension(const std::string&& v);
    /**@}*/

public:
    bool operator==(const archetype_family_properties& rhs) const;
    bool operator!=(const archetype_family_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_family_properties& other) noexcept;
    archetype_family_properties& operator=(archetype_family_properties other);

private:
    std::string extension_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::entities::archetype_family_properties& lhs,
    dogen::generation::entities::archetype_family_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
