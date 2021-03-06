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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_KIND_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_KIND_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/physical_meta_name.hpp"

namespace dogen::physical::entities {

class archetype_kind_properties final {
public:
    archetype_kind_properties() = default;
    archetype_kind_properties(const archetype_kind_properties&) = default;
    archetype_kind_properties(archetype_kind_properties&&) = default;
    ~archetype_kind_properties() = default;

public:
    archetype_kind_properties(
        const dogen::identification::entities::physical_meta_name& meta_name,
        const std::string& file_extension);

public:
    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::identification::entities::physical_meta_name& meta_name() const;
    dogen::identification::entities::physical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::physical_meta_name& v);
    void meta_name(const dogen::identification::entities::physical_meta_name&& v);
    /**@}*/

    const std::string& file_extension() const;
    std::string& file_extension();
    void file_extension(const std::string& v);
    void file_extension(const std::string&& v);

public:
    bool operator==(const archetype_kind_properties& rhs) const;
    bool operator!=(const archetype_kind_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_kind_properties& other) noexcept;
    archetype_kind_properties& operator=(archetype_kind_properties other);

private:
    dogen::identification::entities::physical_meta_name meta_name_;
    std::string file_extension_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::archetype_kind_properties& lhs,
    dogen::physical::entities::archetype_kind_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
