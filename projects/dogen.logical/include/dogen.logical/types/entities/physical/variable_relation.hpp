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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_VARIABLE_RELATION_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_VARIABLE_RELATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::logical::entities::physical {

class variable_relation final {
public:
    variable_relation() = default;
    variable_relation(const variable_relation&) = default;
    variable_relation(variable_relation&&) = default;
    ~variable_relation() = default;

public:
    variable_relation(
        const std::string& original_urn,
        const std::string& type);

public:
    /**
     * @brief URN pointing to an archetype or a label, as it was originally created by the user.
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
     * @brief Type of the variable relation.
     */
    /**@{*/
    const std::string& type() const;
    std::string& type();
    void type(const std::string& v);
    void type(const std::string&& v);
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
    std::string type_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::variable_relation& lhs,
    dogen::logical::entities::physical::variable_relation& rhs) {
    lhs.swap(rhs);
}

}

#endif
