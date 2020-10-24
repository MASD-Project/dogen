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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_BACKEND_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/part.hpp"
#include "dogen.physical/types/entities/facet.hpp"
#include "dogen.physical/types/entities/archetype.hpp"
#include "dogen.identification/types/entities/label.hpp"
#include "dogen.physical/types/entities/archetype_kind.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"

namespace dogen::physical::entities {

/**
 * @brief Represents a meta-region in physical space with archetypes for a primary technical
 * space, and associated secondary technical spaces.
 */
class backend final {
public:
    backend(const backend&) = default;
    backend(backend&&) = default;
    ~backend() = default;

public:
    backend();

public:
    backend(
        const std::string& directory_name,
        const std::string& description,
        const dogen::identification::entities::physical_meta_name& meta_name,
        const std::list<dogen::identification::entities::label>& labels,
        const dogen::identification::entities::technical_space technical_space,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>& parts,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& facets,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& archetypes,
        const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& archetype_kinds);

public:
    /**
     * @brief Default name to use for the directory in the file-system representing this element.
     */
    /**@{*/
    const std::string& directory_name() const;
    std::string& directory_name();
    void directory_name(const std::string& v);
    void directory_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Human readable description of the entity.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

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
     * @brief All labels associated with this element.
     */
    /**@{*/
    const std::list<dogen::identification::entities::label>& labels() const;
    std::list<dogen::identification::entities::label>& labels();
    void labels(const std::list<dogen::identification::entities::label>& v);
    void labels(const std::list<dogen::identification::entities::label>&& v);
    /**@}*/

    /**
     * @brief Technical space to which this physical element belongs to.
     */
    /**@{*/
    dogen::identification::entities::technical_space technical_space() const;
    void technical_space(const dogen::identification::entities::technical_space v);
    /**@}*/

    /**
     * @brief Parts by part ID.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>& parts() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>& parts();
    void parts(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>& v);
    void parts(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part>&& v);
    /**@}*/

    /**
     * @brief Facets by facet ID.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& facets() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& facets();
    void facets(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>& v);
    void facets(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet>&& v);
    /**@}*/

    /**
     * @brief Archetypes by archetype ID.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& archetypes() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& archetypes();
    void archetypes(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>& v);
    void archetypes(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype>&& v);
    /**@}*/

    /**
     * @brief Archetype kinds by ID.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& archetype_kinds() const;
    std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& archetype_kinds();
    void archetype_kinds(const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>& v);
    void archetype_kinds(const std::unordered_map<std::string, dogen::physical::entities::archetype_kind>&& v);
    /**@}*/

public:
    bool operator==(const backend& rhs) const;
    bool operator!=(const backend& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(backend& other) noexcept;
    backend& operator=(backend other);

private:
    std::string directory_name_;
    std::string description_;
    dogen::identification::entities::physical_meta_name meta_name_;
    std::list<dogen::identification::entities::label> labels_;
    dogen::identification::entities::technical_space technical_space_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part> parts_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet> facets_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype> archetypes_;
    std::unordered_map<std::string, dogen::physical::entities::archetype_kind> archetype_kinds_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::backend& lhs,
    dogen::physical::entities::backend& rhs) {
    lhs.swap(rhs);
}

}

#endif
