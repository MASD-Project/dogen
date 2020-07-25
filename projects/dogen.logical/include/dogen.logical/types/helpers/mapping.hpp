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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.logical/types/helpers/mapping_value.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.identification/hash/entities/technical_space_hash.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Stores the mapping of a key (the element id) to its values, organised by technical
 * space.
 */
class mapping final {
public:
    mapping() = default;
    mapping(const mapping&) = default;
    mapping(mapping&&) = default;
    ~mapping() = default;

public:
    mapping(
        const std::string& agnostic_id,
        const std::unordered_map<dogen::identification::entities::technical_space, dogen::logical::helpers::mapping_value>& by_technical_space);

public:
    /**
     * @brief Technical space agnostic ID of the element we're mapping from.
     */
    /**@{*/
    const std::string& agnostic_id() const;
    std::string& agnostic_id();
    void agnostic_id(const std::string& v);
    void agnostic_id(const std::string&& v);
    /**@}*/

    /**
     * @brief Values of the mapping, by technical space.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::technical_space, dogen::logical::helpers::mapping_value>& by_technical_space() const;
    std::unordered_map<dogen::identification::entities::technical_space, dogen::logical::helpers::mapping_value>& by_technical_space();
    void by_technical_space(const std::unordered_map<dogen::identification::entities::technical_space, dogen::logical::helpers::mapping_value>& v);
    void by_technical_space(const std::unordered_map<dogen::identification::entities::technical_space, dogen::logical::helpers::mapping_value>&& v);
    /**@}*/

public:
    bool operator==(const mapping& rhs) const;
    bool operator!=(const mapping& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(mapping& other) noexcept;
    mapping& operator=(mapping other);

private:
    std::string agnostic_id_;
    std::unordered_map<dogen::identification::entities::technical_space, dogen::logical::helpers::mapping_value> by_technical_space_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::helpers::mapping& lhs,
    dogen::logical::helpers::mapping& rhs) {
    lhs.swap(rhs);
}

}

#endif
