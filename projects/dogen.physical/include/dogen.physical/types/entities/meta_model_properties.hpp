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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_META_MODEL_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_META_MODEL_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/filesystem/path.hpp>
#include "dogen.physical/types/entities/part_properties.hpp"
#include "dogen.physical/types/entities/facet_properties.hpp"
#include "dogen.physical/types/entities/backend_properties.hpp"
#include "dogen.physical/types/entities/archetype_properties.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.physical/types/entities/project_path_properties.hpp"
#include "dogen.physical/types/entities/archetype_kind_properties.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.identification/hash/entities/logical_meta_physical_id_hash.hpp"

namespace dogen::physical::entities {

/**
 * @brief Meta-model configuration supplied by this model.
 *
 * The meta-model properties represent a set of variability overrides supplied on top
 * of the existing physical meta-model. In addition, the properties also contain
 * computed values on the back of physical transforms.
 */
class meta_model_properties final {
public:
    meta_model_properties() = default;
    meta_model_properties(const meta_model_properties&) = default;
    ~meta_model_properties() = default;

public:
    meta_model_properties(meta_model_properties&& rhs);

public:
    meta_model_properties(
        const boost::filesystem::path& output_directory_path,
        const boost::filesystem::path& file_path,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>& backend_properties,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& facet_properties,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>& archetype_properties,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>& archetype_kind_properties,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>& part_properties,
        const std::unordered_set<dogen::identification::entities::physical_meta_id>& enabled_backends,
        const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element,
        const dogen::physical::entities::project_path_properties& project_path_properties);

public:
    /**
     * @brief Full path to the output directory chosen by the user.
     */
    /**@{*/
    const boost::filesystem::path& output_directory_path() const;
    boost::filesystem::path& output_directory_path();
    void output_directory_path(const boost::filesystem::path& v);
    void output_directory_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Full path to the component.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>& backend_properties() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>& backend_properties();
    void backend_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>& v);
    void backend_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties>&& v);

    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& facet_properties() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& facet_properties();
    void facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& v);
    void facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>&& v);

    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>& archetype_properties() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>& archetype_properties();
    void archetype_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>& v);
    void archetype_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties>&& v);

    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>& archetype_kind_properties() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>& archetype_kind_properties();
    void archetype_kind_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>& v);
    void archetype_kind_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties>&& v);

    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>& part_properties() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>& part_properties();
    void part_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>& v);
    void part_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties>&& v);

    /**
     * @brief Contains the IDs of all of the backends which are enabled.
     */
    /**@{*/
    const std::unordered_set<dogen::identification::entities::physical_meta_id>& enabled_backends() const;
    std::unordered_set<dogen::identification::entities::physical_meta_id>& enabled_backends();
    void enabled_backends(const std::unordered_set<dogen::identification::entities::physical_meta_id>& v);
    void enabled_backends(const std::unordered_set<dogen::identification::entities::physical_meta_id>&& v);
    /**@}*/

    const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element() const;
    std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element();
    void enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& v);
    void enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>&& v);

    const dogen::physical::entities::project_path_properties& project_path_properties() const;
    dogen::physical::entities::project_path_properties& project_path_properties();
    void project_path_properties(const dogen::physical::entities::project_path_properties& v);
    void project_path_properties(const dogen::physical::entities::project_path_properties&& v);

public:
    bool operator==(const meta_model_properties& rhs) const;
    bool operator!=(const meta_model_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(meta_model_properties& other) noexcept;
    meta_model_properties& operator=(meta_model_properties other);

private:
    boost::filesystem::path output_directory_path_;
    boost::filesystem::path file_path_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::backend_properties> backend_properties_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties> facet_properties_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_properties> archetype_properties_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype_kind_properties> archetype_kind_properties_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::part_properties> part_properties_;
    std::unordered_set<dogen::identification::entities::physical_meta_id> enabled_backends_;
    std::unordered_set<dogen::identification::entities::logical_meta_physical_id> enabled_archetype_for_element_;
    dogen::physical::entities::project_path_properties project_path_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::meta_model_properties& lhs,
    dogen::physical::entities::meta_model_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
