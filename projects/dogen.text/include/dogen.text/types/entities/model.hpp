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
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.text/types/entities/element_artefacts.hpp"
#include "dogen.identification/types/entities/logical_provenance.hpp"

namespace dogen::text::entities {

/**
 * @brief Represents the combined logical-physical space.
 */
class model final {
public:
    model() = default;
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model(
        const dogen::identification::entities::logical_provenance& provenance,
        const dogen::logical::entities::model& logical,
        const dogen::physical::entities::model& physical,
        const std::list<dogen::text::entities::element_artefacts>& elements);

public:
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
     * @brief The logical model representation in the logical-physical space.
     */
    /**@{*/
    const dogen::logical::entities::model& logical() const;
    dogen::logical::entities::model& logical();
    void logical(const dogen::logical::entities::model& v);
    void logical(const dogen::logical::entities::model&& v);
    /**@}*/

    /**
     * @brief The physical model representation in the logical-physical space.
     */
    /**@{*/
    const dogen::physical::entities::model& physical() const;
    dogen::physical::entities::model& physical();
    void physical(const dogen::physical::entities::model& v);
    void physical(const dogen::physical::entities::model&& v);
    /**@}*/

    const std::list<dogen::text::entities::element_artefacts>& elements() const;
    std::list<dogen::text::entities::element_artefacts>& elements();
    void elements(const std::list<dogen::text::entities::element_artefacts>& v);
    void elements(const std::list<dogen::text::entities::element_artefacts>&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::identification::entities::logical_provenance provenance_;
    dogen::logical::entities::model logical_;
    dogen::physical::entities::model physical_;
    std::list<dogen::text::entities::element_artefacts> elements_;
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
