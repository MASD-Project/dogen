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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ARTEFACT_REPOSITORY_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ARTEFACT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/filesystem/path.hpp>
#include "dogen.physical/types/entities/artefact_set.hpp"
#include "dogen.physical/types/entities/element_archetype.hpp"
#include "dogen.physical/hash/entities/element_archetype_hash.hpp"
#include "dogen.physical/types/entities/extraction_properties.hpp"
#include "dogen.physical/types/entities/global_enablement_properties.hpp"

namespace dogen::physical::entities {

class artefact_repository final {
public:
    artefact_repository() = default;
    artefact_repository(const artefact_repository&) = default;
    artefact_repository(artefact_repository&&) = default;
    ~artefact_repository() = default;

public:
    artefact_repository(
        const std::unordered_map<std::string, dogen::physical::entities::artefact_set>& artefact_sets_by_logical_id,
        const std::string& identifier,
        const dogen::physical::entities::extraction_properties& extraction_properties,
        const dogen::physical::entities::global_enablement_properties& global_enablement_properties,
        const std::unordered_set<dogen::physical::entities::element_archetype>& enabled_archetype_for_element,
        const std::list<boost::filesystem::path>& managed_directories);

public:
    /**
     * @brief All atefact sets in this model, by logical ID.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::physical::entities::artefact_set>& artefact_sets_by_logical_id() const;
    std::unordered_map<std::string, dogen::physical::entities::artefact_set>& artefact_sets_by_logical_id();
    void artefact_sets_by_logical_id(const std::unordered_map<std::string, dogen::physical::entities::artefact_set>& v);
    void artefact_sets_by_logical_id(const std::unordered_map<std::string, dogen::physical::entities::artefact_set>&& v);
    /**@}*/

    /**
     * @brief Identifier for this repository. Used for logging and tracing only.
     */
    /**@{*/
    const std::string& identifier() const;
    std::string& identifier();
    void identifier(const std::string& v);
    void identifier(const std::string&& v);
    /**@}*/

    const dogen::physical::entities::extraction_properties& extraction_properties() const;
    dogen::physical::entities::extraction_properties& extraction_properties();
    void extraction_properties(const dogen::physical::entities::extraction_properties& v);
    void extraction_properties(const dogen::physical::entities::extraction_properties&& v);

    const dogen::physical::entities::global_enablement_properties& global_enablement_properties() const;
    dogen::physical::entities::global_enablement_properties& global_enablement_properties();
    void global_enablement_properties(const dogen::physical::entities::global_enablement_properties& v);
    void global_enablement_properties(const dogen::physical::entities::global_enablement_properties&& v);

    const std::unordered_set<dogen::physical::entities::element_archetype>& enabled_archetype_for_element() const;
    std::unordered_set<dogen::physical::entities::element_archetype>& enabled_archetype_for_element();
    void enabled_archetype_for_element(const std::unordered_set<dogen::physical::entities::element_archetype>& v);
    void enabled_archetype_for_element(const std::unordered_set<dogen::physical::entities::element_archetype>&& v);

    const std::list<boost::filesystem::path>& managed_directories() const;
    std::list<boost::filesystem::path>& managed_directories();
    void managed_directories(const std::list<boost::filesystem::path>& v);
    void managed_directories(const std::list<boost::filesystem::path>&& v);

public:
    bool operator==(const artefact_repository& rhs) const;
    bool operator!=(const artefact_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact_repository& other) noexcept;
    artefact_repository& operator=(artefact_repository other);

private:
    std::unordered_map<std::string, dogen::physical::entities::artefact_set> artefact_sets_by_logical_id_;
    std::string identifier_;
    dogen::physical::entities::extraction_properties extraction_properties_;
    dogen::physical::entities::global_enablement_properties global_enablement_properties_;
    std::unordered_set<dogen::physical::entities::element_archetype> enabled_archetype_for_element_;
    std::list<boost::filesystem::path> managed_directories_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::artefact_repository& lhs,
    dogen::physical::entities::artefact_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
