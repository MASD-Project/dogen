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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_CONTEXT_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_MAPPING_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"

namespace dogen::logical::helpers {

class mapping_context final {
public:
    mapping_context() = default;
    mapping_context(const mapping_context&) = default;
    mapping_context(mapping_context&&) = default;
    ~mapping_context() = default;

public:
    mapping_context(
        const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& translations,
        const std::unordered_set<dogen::identification::entities::logical_id>& erasures,
        const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& injections);

public:
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& translations() const;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& translations();
    void translations(const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& v);
    void translations(const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>&& v);

    const std::unordered_set<dogen::identification::entities::logical_id>& erasures() const;
    std::unordered_set<dogen::identification::entities::logical_id>& erasures();
    void erasures(const std::unordered_set<dogen::identification::entities::logical_id>& v);
    void erasures(const std::unordered_set<dogen::identification::entities::logical_id>&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& injections() const;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& injections();
    void injections(const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& v);
    void injections(const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>&& v);

public:
    bool operator==(const mapping_context& rhs) const;
    bool operator!=(const mapping_context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(mapping_context& other) noexcept;
    mapping_context& operator=(mapping_context other);

private:
    std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name> translations_;
    std::unordered_set<dogen::identification::entities::logical_id> erasures_;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name> injections_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::helpers::mapping_context& lhs,
    dogen::logical::helpers::mapping_context& rhs) {
    lhs.swap(rhs);
}

}

#endif
