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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_SET_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.identification/hash/entities/technical_space_hash.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Consistent unit of mapping that can be used to translate a model from one technical
 * space to another.
 */
class mapping_set final {
public:
    mapping_set() = default;
    mapping_set(const mapping_set&) = default;
    mapping_set(mapping_set&&) = default;
    ~mapping_set() = default;

public:
    mapping_set(
        const std::string& name,
        const std::unordered_map<dogen::identification::entities::technical_space, std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name> >& by_agnostic_id,
        const std::unordered_map<dogen::identification::entities::technical_space, std::unordered_set<dogen::identification::entities::logical_id> >& erasures_by_technical_space);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::unordered_map<dogen::identification::entities::technical_space, std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name> >& by_agnostic_id() const;
    std::unordered_map<dogen::identification::entities::technical_space, std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name> >& by_agnostic_id();
    void by_agnostic_id(const std::unordered_map<dogen::identification::entities::technical_space, std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name> >& v);
    void by_agnostic_id(const std::unordered_map<dogen::identification::entities::technical_space, std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name> >&& v);

    const std::unordered_map<dogen::identification::entities::technical_space, std::unordered_set<dogen::identification::entities::logical_id> >& erasures_by_technical_space() const;
    std::unordered_map<dogen::identification::entities::technical_space, std::unordered_set<dogen::identification::entities::logical_id> >& erasures_by_technical_space();
    void erasures_by_technical_space(const std::unordered_map<dogen::identification::entities::technical_space, std::unordered_set<dogen::identification::entities::logical_id> >& v);
    void erasures_by_technical_space(const std::unordered_map<dogen::identification::entities::technical_space, std::unordered_set<dogen::identification::entities::logical_id> >&& v);

public:
    bool operator==(const mapping_set& rhs) const;
    bool operator!=(const mapping_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(mapping_set& other) noexcept;
    mapping_set& operator=(mapping_set other);

private:
    std::string name_;
    std::unordered_map<dogen::identification::entities::technical_space, std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name> > by_agnostic_id_;
    std::unordered_map<dogen::identification::entities::technical_space, std::unordered_set<dogen::identification::entities::logical_id> > erasures_by_technical_space_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::helpers::mapping_set& lhs,
    dogen::logical::helpers::mapping_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
