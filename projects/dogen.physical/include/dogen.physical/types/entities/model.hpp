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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_MODEL_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.physical/types/entities/artefact_fwd.hpp"
#include "dogen.physical/types/entities/artefact_set.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/physical_name.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.physical/types/entities/outputting_properties.hpp"
#include "dogen.identification/types/entities/logical_provenance.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"

namespace dogen::physical::entities {

/**
 * @brief Collection of entities representing objects in physical space.
 */
class model final {
public:
    model() = default;
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model(
        const dogen::identification::entities::physical_meta_name& meta_name,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::logical_provenance& provenance,
        const dogen::identification::entities::physical_name& name,
        const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& artefact_sets_by_logical_id,
        const std::string& technical_space,
        const std::list<boost::filesystem::path>& managed_directories,
        const dogen::physical::entities::outputting_properties& outputting_properties,
        const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& orphan_artefacts);

public:
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
     * @brief Name of the physical element.
     */
    /**@{*/
    const dogen::identification::entities::physical_name& name() const;
    dogen::identification::entities::physical_name& name();
    void name(const dogen::identification::entities::physical_name& v);
    void name(const dogen::identification::entities::physical_name&& v);
    /**@}*/

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
     * @brief Primary technical space that this model belongs to.
     */
    /**@{*/
    const std::string& technical_space() const;
    std::string& technical_space();
    void technical_space(const std::string& v);
    void technical_space(const std::string&& v);
    /**@}*/

    const std::list<boost::filesystem::path>& managed_directories() const;
    std::list<boost::filesystem::path>& managed_directories();
    void managed_directories(const std::list<boost::filesystem::path>& v);
    void managed_directories(const std::list<boost::filesystem::path>&& v);

    const dogen::physical::entities::outputting_properties& outputting_properties() const;
    dogen::physical::entities::outputting_properties& outputting_properties();
    void outputting_properties(const dogen::physical::entities::outputting_properties& v);
    void outputting_properties(const dogen::physical::entities::outputting_properties&& v);

    /**
     * @brief Artefacts that exist in the physical dimension only.
     */
    /**@{*/
    const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& orphan_artefacts() const;
    std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& orphan_artefacts();
    void orphan_artefacts(const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& v);
    void orphan_artefacts(const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >&& v);
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
    dogen::identification::entities::physical_meta_name meta_name_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    dogen::identification::entities::logical_provenance provenance_;
    dogen::identification::entities::physical_name name_;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set> artefact_sets_by_logical_id_;
    std::string technical_space_;
    std::list<boost::filesystem::path> managed_directories_;
    dogen::physical::entities::outputting_properties outputting_properties_;
    std::list<boost::shared_ptr<dogen::physical::entities::artefact> > orphan_artefacts_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::model& lhs,
    dogen::physical::entities::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
