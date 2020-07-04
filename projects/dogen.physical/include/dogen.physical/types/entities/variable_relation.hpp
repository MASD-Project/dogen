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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_VARIABLE_RELATION_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_VARIABLE_RELATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.physical/types/entities/variable_relation_type.hpp"

namespace dogen::physical::entities {

class variable_relation final {
public:
    variable_relation(const variable_relation&) = default;
    variable_relation(variable_relation&&) = default;
    ~variable_relation() = default;

public:
    variable_relation();

public:
    variable_relation(
        const std::string& original_urn,
        const std::string& resolved_urn,
        const dogen::physical::entities::variable_relation_type type);

public:
    /**
     * @brief URN which may or may not be an archetype URN.
     *
     *  It must have the form "archetype:" if pointing to an archetype, or  "label:" if
     * pointing to a label, and then is followed by "KEY:VALUE". The label must resolve
     * to a unique archetype.
     */
    /**@{*/
    const std::string& original_urn() const;
    std::string& original_urn();
    void original_urn(const std::string& v);
    void original_urn(const std::string&& v);
    /**@}*/

    /**
     * @brief URN pointing to the archetype.
     *
     *  It must have the form "archetype:".
     */
    /**@{*/
    const std::string& resolved_urn() const;
    std::string& resolved_urn();
    void resolved_urn(const std::string& v);
    void resolved_urn(const std::string&& v);
    /**@}*/

    /**
     * @brief How these archetypes are related.
     */
    /**@{*/
    dogen::physical::entities::variable_relation_type type() const;
    void type(const dogen::physical::entities::variable_relation_type v);
    /**@}*/

public:
    bool operator==(const variable_relation& rhs) const;
    bool operator!=(const variable_relation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(variable_relation& other) noexcept;
    variable_relation& operator=(variable_relation other);

private:
    std::string original_urn_;
    std::string resolved_urn_;
    dogen::physical::entities::variable_relation_type type_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::variable_relation& lhs,
    dogen::physical::entities::variable_relation& rhs) {
    lhs.swap(rhs);
}

}

#endif
