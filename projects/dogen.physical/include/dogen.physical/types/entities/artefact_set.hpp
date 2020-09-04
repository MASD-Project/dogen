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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ARTEFACT_SET_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ARTEFACT_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.physical/types/entities/artefact_fwd.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/logical_provenance.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"

namespace dogen::physical::entities {

/**
 * @brief Represents a slice of logical-physical space fixed at one logical point.
 */
class artefact_set final {
public:
    artefact_set(const artefact_set&) = default;
    artefact_set(artefact_set&&) = default;
    ~artefact_set() = default;

public:
    artefact_set();

public:
    artefact_set(
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::logical_provenance& provenance,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts_by_archetype,
        const std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>& archetype_for_role,
        const bool is_generatable);

public:
    /**
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration() const;
    boost::shared_ptr<dogen::variability::entities::configuration>& configuration();
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v);
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v);
    /**@}*/

    /**
     * @brief Details of the provenance of this model element.
     */
    /**@{*/
    const dogen::identification::entities::logical_provenance& provenance() const;
    dogen::identification::entities::logical_provenance& provenance();
    void provenance(const dogen::identification::entities::logical_provenance& v);
    void provenance(const dogen::identification::entities::logical_provenance&& v);
    /**@}*/

    /**
     * @brief All artefacts that are contained within this set, organised by archetype.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts_by_archetype() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts_by_archetype();
    void artefacts_by_archetype(const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >& v);
    void artefacts_by_archetype(const std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> >&& v);
    /**@}*/

    /**
     * @brief Resolves a role into a concrete archetype, in the context of this logical element.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>& archetype_for_role() const;
    std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>& archetype_for_role();
    void archetype_for_role(const std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>& v);
    void archetype_for_role(const std::unordered_map<std::string, dogen::identification::entities::physical_meta_id>&& v);
    /**@}*/

    /**
     * @brief If false, the entire artefact set is not generatable.
     */
    /**@{*/
    bool is_generatable() const;
    void is_generatable(const bool v);
    /**@}*/

public:
    bool operator==(const artefact_set& rhs) const;
    bool operator!=(const artefact_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact_set& other) noexcept;
    artefact_set& operator=(artefact_set other);

private:
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    dogen::identification::entities::logical_provenance provenance_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, boost::shared_ptr<dogen::physical::entities::artefact> > artefacts_by_archetype_;
    std::unordered_map<std::string, dogen::identification::entities::physical_meta_id> archetype_for_role_;
    bool is_generatable_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::artefact_set& lhs,
    dogen::physical::entities::artefact_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
