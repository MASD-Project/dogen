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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_INJECTION_PROVENANCE_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_INJECTION_PROVENANCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.identification/types/entities/model_id.hpp"
#include "dogen.identification/types/entities/sha1_hash.hpp"
#include "dogen.identification/types/entities/model_type.hpp"
#include "dogen.identification/types/entities/injection_id.hpp"
#include "dogen.identification/types/entities/injection_location.hpp"

namespace dogen::identification::entities {

/**
 * @brief Source of a model element in the injection dimension.
 */
class injection_provenance final {
public:
    injection_provenance(const injection_provenance&) = default;
    injection_provenance(injection_provenance&&) = default;
    ~injection_provenance() = default;

public:
    injection_provenance();

public:
    injection_provenance(
        const dogen::identification::entities::model_id& model_id,
        const dogen::identification::entities::model_type model_type,
        const dogen::identification::entities::sha1_hash& model_sha1_hash,
        const dogen::identification::entities::injection_id& injection_id,
        const dogen::identification::entities::injection_location& location);

public:
    /**
     * @brief ID for a model.
     */
    /**@{*/
    const dogen::identification::entities::model_id& model_id() const;
    dogen::identification::entities::model_id& model_id();
    void model_id(const dogen::identification::entities::model_id& v);
    void model_id(const dogen::identification::entities::model_id&& v);
    /**@}*/

    /**
     * @brief Type of the model where this element originates from.
     */
    /**@{*/
    dogen::identification::entities::model_type model_type() const;
    void model_type(const dogen::identification::entities::model_type v);
    /**@}*/

    /**
     * @brief SHA1 key of the original injection model.
     */
    /**@{*/
    const dogen::identification::entities::sha1_hash& model_sha1_hash() const;
    dogen::identification::entities::sha1_hash& model_sha1_hash();
    void model_sha1_hash(const dogen::identification::entities::sha1_hash& v);
    void model_sha1_hash(const dogen::identification::entities::sha1_hash&& v);
    /**@}*/

    /**
     * @brief Identifier for the modeling element in the injection dimension.
     */
    /**@{*/
    const dogen::identification::entities::injection_id& injection_id() const;
    dogen::identification::entities::injection_id& injection_id();
    void injection_id(const dogen::identification::entities::injection_id& v);
    void injection_id(const dogen::identification::entities::injection_id&& v);
    /**@}*/

    /**
     * @brief Where the element was located in the original source.
     */
    /**@{*/
    const dogen::identification::entities::injection_location& location() const;
    dogen::identification::entities::injection_location& location();
    void location(const dogen::identification::entities::injection_location& v);
    void location(const dogen::identification::entities::injection_location&& v);
    /**@}*/

public:
    bool operator==(const injection_provenance& rhs) const;
    bool operator!=(const injection_provenance& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(injection_provenance& other) noexcept;
    injection_provenance& operator=(injection_provenance other);

private:
    dogen::identification::entities::model_id model_id_;
    dogen::identification::entities::model_type model_type_;
    dogen::identification::entities::sha1_hash model_sha1_hash_;
    dogen::identification::entities::injection_id injection_id_;
    dogen::identification::entities::injection_location location_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::injection_provenance& lhs,
    dogen::identification::entities::injection_provenance& rhs) {
    lhs.swap(rhs);
}

}

#endif
