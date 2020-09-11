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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_PART_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_PART_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/physical_meta_name.hpp"

namespace dogen::physical::entities {

/**
 * @brief Properties related to the part.
 */
class part_properties final {
public:
    part_properties() = default;
    part_properties(const part_properties&) = default;
    part_properties(part_properties&&) = default;
    ~part_properties() = default;

public:
    part_properties(
        const dogen::identification::entities::physical_meta_name& meta_name,
        const std::string& directory);

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

    /**
     * @brief Name of the directory to use for the part.
     */
    /**@{*/
    const std::string& directory() const;
    std::string& directory();
    void directory(const std::string& v);
    void directory(const std::string&& v);
    /**@}*/

public:
    bool operator==(const part_properties& rhs) const;
    bool operator!=(const part_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(part_properties& other) noexcept;
    part_properties& operator=(part_properties other);

private:
    dogen::identification::entities::physical_meta_name meta_name_;
    std::string directory_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::part_properties& lhs,
    dogen::physical::entities::part_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
