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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_FIXED_RELATION_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_FIXED_RELATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::physical::entities {

/**
 * @brief Represents a relation between archetypes, fixed to a logical model element.
 */
class fixed_relation final {
public:
    fixed_relation() = default;
    fixed_relation(const fixed_relation&) = default;
    fixed_relation(fixed_relation&&) = default;
    ~fixed_relation() = default;

public:
    fixed_relation(
        const std::string& archetype_urn,
        const std::string& logical_model_element_id);

public:
    /**
     * @brief URN pointing to the archetype.
     *
     *  It must have the form "archetype:" if pointing to an archetype, or  "label:" if
     * pointing to a label, and then is followed by "KEY:VALUE". The label must resolve
     * to a unique archetype.
     */
    /**@{*/
    const std::string& archetype_urn() const;
    std::string& archetype_urn();
    void archetype_urn(const std::string& v);
    void archetype_urn(const std::string&& v);
    /**@}*/

    /**
     * @brief ID of the logical model element that the relation is fixed against.
     *
     * Element must exist in the current loaded models.
     */
    /**@{*/
    const std::string& logical_model_element_id() const;
    std::string& logical_model_element_id();
    void logical_model_element_id(const std::string& v);
    void logical_model_element_id(const std::string&& v);
    /**@}*/

public:
    bool operator==(const fixed_relation& rhs) const;
    bool operator!=(const fixed_relation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(fixed_relation& other) noexcept;
    fixed_relation& operator=(fixed_relation other);

private:
    std::string archetype_urn_;
    std::string logical_model_element_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::fixed_relation& lhs,
    dogen::physical::entities::fixed_relation& rhs) {
    lhs.swap(rhs);
}

}

#endif
