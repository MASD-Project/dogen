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
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.physical/types/entities/extraction_properties.hpp"
#include "dogen.physical/types/entities/meta_model_properties.hpp"
#include "dogen.physical/types/entities/global_enablement_properties.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.identification/hash/entities/logical_meta_physical_id_hash.hpp"

namespace dogen::physical::entities {

class artefact_repository final {
public:
    artefact_repository(const artefact_repository&) = default;
    artefact_repository(artefact_repository&&) = default;
    ~artefact_repository() = default;

public:
    artefact_repository();

public:
    artefact_repository(
        const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& artefact_sets_by_logical_id,
        const std::string& identifier,
        const dogen::identification::entities::logical_id& root_module_logical_id,
        const dogen::physical::entities::extraction_properties& extraction_properties,
        const dogen::physical::entities::global_enablement_properties& global_enablement_properties,
        const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element,
        const std::list<boost::filesystem::path>& managed_directories,
        const bool has_generatable_artefacts,
        const dogen::physical::entities::meta_model_properties& meta_model_properties);

public:
    /**
     * @brief All atefact sets in this model, by logical ID.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& artefact_sets_by_logical_id() const;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& artefact_sets_by_logical_id();
    void artefact_sets_by_logical_id(const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& v);
    void artefact_sets_by_logical_id(const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>&& v);
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

    /**
     * @brief Identifier of the artefact set containing the root module.
     */
    /**@{*/
    const dogen::identification::entities::logical_id& root_module_logical_id() const;
    dogen::identification::entities::logical_id& root_module_logical_id();
    void root_module_logical_id(const dogen::identification::entities::logical_id& v);
    void root_module_logical_id(const dogen::identification::entities::logical_id&& v);
    /**@}*/

    const dogen::physical::entities::extraction_properties& extraction_properties() const;
    dogen::physical::entities::extraction_properties& extraction_properties();
    void extraction_properties(const dogen::physical::entities::extraction_properties& v);
    void extraction_properties(const dogen::physical::entities::extraction_properties&& v);

    const dogen::physical::entities::global_enablement_properties& global_enablement_properties() const;
    dogen::physical::entities::global_enablement_properties& global_enablement_properties();
    void global_enablement_properties(const dogen::physical::entities::global_enablement_properties& v);
    void global_enablement_properties(const dogen::physical::entities::global_enablement_properties&& v);

    const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element() const;
    std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element();
    void enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& v);
    void enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>&& v);

    const std::list<boost::filesystem::path>& managed_directories() const;
    std::list<boost::filesystem::path>& managed_directories();
    void managed_directories(const std::list<boost::filesystem::path>& v);
    void managed_directories(const std::list<boost::filesystem::path>&& v);

    /**
     * @brief If true the repository has at least one generable artefact, false otherwise.
     */
    /**@{*/
    bool has_generatable_artefacts() const;
    void has_generatable_artefacts(const bool v);
    /**@}*/

    /**
     * @brief Meta-model configuration supplied by this model.
     */
    /**@{*/
    const dogen::physical::entities::meta_model_properties& meta_model_properties() const;
    dogen::physical::entities::meta_model_properties& meta_model_properties();
    void meta_model_properties(const dogen::physical::entities::meta_model_properties& v);
    void meta_model_properties(const dogen::physical::entities::meta_model_properties&& v);
    /**@}*/

public:
    bool operator==(const artefact_repository& rhs) const;
    bool operator!=(const artefact_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact_repository& other) noexcept;
    artefact_repository& operator=(artefact_repository other);

private:
    std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set> artefact_sets_by_logical_id_;
    std::string identifier_;
    dogen::identification::entities::logical_id root_module_logical_id_;
    dogen::physical::entities::extraction_properties extraction_properties_;
    dogen::physical::entities::global_enablement_properties global_enablement_properties_;
    std::unordered_set<dogen::identification::entities::logical_meta_physical_id> enabled_archetype_for_element_;
    std::list<boost::filesystem::path> managed_directories_;
    bool has_generatable_artefacts_;
    dogen::physical::entities::meta_model_properties meta_model_properties_;
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
