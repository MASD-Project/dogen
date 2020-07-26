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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_PHYSICAL_META_NAME_INDICES_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_PHYSICAL_META_NAME_INDICES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/archetype_name_set.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"

namespace dogen::identification::entities {

/**
 * @brief Containing physical meta-names, indexed as required by use cases.
 */
class physical_meta_name_indices final {
public:
    physical_meta_name_indices() = default;
    physical_meta_name_indices(const physical_meta_name_indices&) = default;
    physical_meta_name_indices(physical_meta_name_indices&&) = default;
    ~physical_meta_name_indices() = default;

public:
    physical_meta_name_indices(
        const std::list<dogen::identification::entities::physical_meta_name>& all,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >& facet_names_by_backend_name,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>& archetype_names_by_logical_meta_name,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >& archetype_names_by_backend_by_facet);

public:
    /**
     * @brief All meta-names.
     */
    /**@{*/
    const std::list<dogen::identification::entities::physical_meta_name>& all() const;
    std::list<dogen::identification::entities::physical_meta_name>& all();
    void all(const std::list<dogen::identification::entities::physical_meta_name>& v);
    void all(const std::list<dogen::identification::entities::physical_meta_name>&& v);
    /**@}*/

    /**
     * @brief Qualified names of facets by qualified names of backends.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >& facet_names_by_backend_name() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >& facet_names_by_backend_name();
    void facet_names_by_backend_name(const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >& v);
    void facet_names_by_backend_name(const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> >&& v);
    /**@}*/

    /**
     * @brief Physical meta-names by logical meta-names.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>& archetype_names_by_logical_meta_name() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>& archetype_names_by_logical_meta_name();
    void archetype_names_by_logical_meta_name(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>& v);
    void archetype_names_by_logical_meta_name(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set>&& v);
    /**@}*/

    /**
     * @brief Archetype names by qualified backend and facet names
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >& archetype_names_by_backend_by_facet() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >& archetype_names_by_backend_by_facet();
    void archetype_names_by_backend_by_facet(const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >& v);
    void archetype_names_by_backend_by_facet(const std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > >&& v);
    /**@}*/

public:
    bool operator==(const physical_meta_name_indices& rhs) const;
    bool operator!=(const physical_meta_name_indices& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(physical_meta_name_indices& other) noexcept;
    physical_meta_name_indices& operator=(physical_meta_name_indices other);

private:
    std::list<dogen::identification::entities::physical_meta_name> all_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_set<dogen::identification::entities::physical_meta_id> > facet_names_by_backend_name_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::archetype_name_set> archetype_names_by_logical_meta_name_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<dogen::identification::entities::physical_meta_id> > > archetype_names_by_backend_by_facet_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::physical_meta_name_indices& lhs,
    dogen::identification::entities::physical_meta_name_indices& rhs) {
    lhs.swap(rhs);
}

}

#endif
