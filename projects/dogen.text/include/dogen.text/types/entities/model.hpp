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
#ifndef DOGEN_TEXT_TYPES_ENTITIES_MODEL_HPP
#define DOGEN_TEXT_TYPES_ENTITIES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/filesystem/path.hpp>
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.text/types/entities/element_artefacts.hpp"
#include "dogen.physical/types/entities/facet_properties.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.physical/types/entities/extraction_properties.hpp"
#include "dogen.identification/types/entities/codec_provenance.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/logical_meta_name.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.identification/hash/entities/logical_meta_physical_id_hash.hpp"

namespace dogen::text::entities {

/**
 * @brief Represents the combined logical-physical space.
 */
class model final {
public:
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model();

public:
    model(
        const dogen::identification::entities::logical_name& name,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::codec_provenance& provenance,
        const std::list<dogen::text::entities::element_artefacts>& elements,
        const bool has_generatable_types,
        const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element,
        const dogen::physical::entities::extraction_properties& extraction_properties,
        const std::list<boost::filesystem::path>& managed_directories,
        const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& facet_properties,
        const dogen::logical::entities::model& logical);

public:
    const dogen::identification::entities::logical_name& name() const;
    dogen::identification::entities::logical_name& name();
    void name(const dogen::identification::entities::logical_name& v);
    void name(const dogen::identification::entities::logical_name&& v);

    const dogen::identification::entities::logical_meta_name& meta_name() const;
    dogen::identification::entities::logical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::logical_meta_name& v);
    void meta_name(const dogen::identification::entities::logical_meta_name&& v);

    /**
     * @brief Details of the provenance of this model element.
     */
    /**@{*/
    const dogen::identification::entities::codec_provenance& provenance() const;
    dogen::identification::entities::codec_provenance& provenance();
    void provenance(const dogen::identification::entities::codec_provenance& v);
    void provenance(const dogen::identification::entities::codec_provenance&& v);
    /**@}*/

    const std::list<dogen::text::entities::element_artefacts>& elements() const;
    std::list<dogen::text::entities::element_artefacts>& elements();
    void elements(const std::list<dogen::text::entities::element_artefacts>& v);
    void elements(const std::list<dogen::text::entities::element_artefacts>&& v);

    /**
     * @brief If true the intermediate model has at least one generable type, false otherwise.
     */
    /**@{*/
    bool has_generatable_types() const;
    void has_generatable_types(const bool v);
    /**@}*/

    const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element() const;
    std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element();
    void enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& v);
    void enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>&& v);

    const dogen::physical::entities::extraction_properties& extraction_properties() const;
    dogen::physical::entities::extraction_properties& extraction_properties();
    void extraction_properties(const dogen::physical::entities::extraction_properties& v);
    void extraction_properties(const dogen::physical::entities::extraction_properties&& v);

    const std::list<boost::filesystem::path>& managed_directories() const;
    std::list<boost::filesystem::path>& managed_directories();
    void managed_directories(const std::list<boost::filesystem::path>& v);
    void managed_directories(const std::list<boost::filesystem::path>&& v);

    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& facet_properties() const;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& facet_properties();
    void facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& v);
    void facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>&& v);

    /**
     * @brief The logical model representation in the logical-physical space.
     */
    /**@{*/
    const dogen::logical::entities::model& logical() const;
    dogen::logical::entities::model& logical();
    void logical(const dogen::logical::entities::model& v);
    void logical(const dogen::logical::entities::model&& v);
    /**@}*/

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::identification::entities::logical_name name_;
    dogen::identification::entities::logical_meta_name meta_name_;
    dogen::identification::entities::codec_provenance provenance_;
    std::list<dogen::text::entities::element_artefacts> elements_;
    bool has_generatable_types_;
    std::unordered_set<dogen::identification::entities::logical_meta_physical_id> enabled_archetype_for_element_;
    dogen::physical::entities::extraction_properties extraction_properties_;
    std::list<boost::filesystem::path> managed_directories_;
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties> facet_properties_;
    dogen::logical::entities::model logical_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::entities::model& lhs,
    dogen::text::entities::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
