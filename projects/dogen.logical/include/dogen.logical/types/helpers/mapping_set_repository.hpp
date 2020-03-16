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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_SET_REPOSITORY_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_SET_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.logical/types/helpers/mapping_set.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Stores all available mapping sets.
 */
class mapping_set_repository final {
public:
    mapping_set_repository() = default;
    mapping_set_repository(const mapping_set_repository&) = default;
    mapping_set_repository(mapping_set_repository&&) = default;
    ~mapping_set_repository() = default;

public:
    mapping_set_repository(
        const dogen::logical::helpers::mapping_set& default_mapping_set,
        const std::unordered_map<std::string, dogen::logical::helpers::mapping_set>& by_name);

public:
    const dogen::logical::helpers::mapping_set& default_mapping_set() const;
    dogen::logical::helpers::mapping_set& default_mapping_set();
    void default_mapping_set(const dogen::logical::helpers::mapping_set& v);
    void default_mapping_set(const dogen::logical::helpers::mapping_set&& v);

    const std::unordered_map<std::string, dogen::logical::helpers::mapping_set>& by_name() const;
    std::unordered_map<std::string, dogen::logical::helpers::mapping_set>& by_name();
    void by_name(const std::unordered_map<std::string, dogen::logical::helpers::mapping_set>& v);
    void by_name(const std::unordered_map<std::string, dogen::logical::helpers::mapping_set>&& v);

public:
    bool operator==(const mapping_set_repository& rhs) const;
    bool operator!=(const mapping_set_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(mapping_set_repository& other) noexcept;
    mapping_set_repository& operator=(mapping_set_repository other);

private:
    dogen::logical::helpers::mapping_set default_mapping_set_;
    std::unordered_map<std::string, dogen::logical::helpers::mapping_set> by_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::helpers::mapping_set_repository& lhs,
    dogen::logical::helpers::mapping_set_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
