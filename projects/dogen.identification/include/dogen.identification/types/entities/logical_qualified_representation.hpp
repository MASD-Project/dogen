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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_QUALIFIED_REPRESENTATION_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_QUALIFIED_REPRESENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/logical_id.hpp"

namespace dogen::identification::entities {

/**
 * @brief Fully qualified representation for a logical identifier.
 */
class logical_qualified_representation final {
public:
    logical_qualified_representation() = default;
    logical_qualified_representation(const logical_qualified_representation&) = default;
    logical_qualified_representation(logical_qualified_representation&&) = default;
    ~logical_qualified_representation() = default;

public:
    logical_qualified_representation(
        const std::string& dot,
        const std::string& colon,
        const std::string& identifiable,
        const dogen::identification::entities::logical_id& id);

public:
    /**
     * @brief Qualified identifier using "." as the separator.
     */
    /**@{*/
    const std::string& dot() const;
    std::string& dot();
    void dot(const std::string& v);
    void dot(const std::string&& v);
    /**@}*/

    /**
     * @brief Qualified identifier using "::" as the separator.
     */
    /**@{*/
    const std::string& colon() const;
    std::string& colon();
    void colon(const std::string& v);
    void colon(const std::string&& v);
    /**@}*/

    /**
     * @brief Representation of the identifier that can usable as an identifier on all of the
     * supported technical spaces, using the entire name structure.
     */
    /**@{*/
    const std::string& identifiable() const;
    std::string& identifiable();
    void identifiable(const std::string& v);
    void identifiable(const std::string&& v);
    /**@}*/

    /**
     * @brief identifier for this element in the logical dimension.
     */
    /**@{*/
    const dogen::identification::entities::logical_id& id() const;
    dogen::identification::entities::logical_id& id();
    void id(const dogen::identification::entities::logical_id& v);
    void id(const dogen::identification::entities::logical_id&& v);
    /**@}*/

public:
    bool operator==(const logical_qualified_representation& rhs) const;
    bool operator!=(const logical_qualified_representation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_qualified_representation& other) noexcept;
    logical_qualified_representation& operator=(logical_qualified_representation other);

private:
    std::string dot_;
    std::string colon_;
    std::string identifiable_;
    dogen::identification::entities::logical_id id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::logical_qualified_representation& lhs,
    dogen::identification::entities::logical_qualified_representation& rhs) {
    lhs.swap(rhs);
}

}

#endif
