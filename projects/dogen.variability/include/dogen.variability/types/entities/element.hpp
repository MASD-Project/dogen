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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_ELEMENT_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/name.hpp"

namespace dogen::variability::entities {

/**
 * @brief Represents an element modeling some aspect of variability.
 */
class element {
public:
    element() = default;
    element(const element&) = default;
    element(element&&) = default;

    virtual ~element() noexcept = 0;

public:
    element(
        const dogen::identification::entities::name& name,
        const std::string& description);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Name of this variability element.
     */
    /**@{*/
    const dogen::identification::entities::name& name() const;
    dogen::identification::entities::name& name();
    void name(const dogen::identification::entities::name& v);
    void name(const dogen::identification::entities::name&& v);
    /**@}*/

    /**
     * @brief Human readable description of the feature, used for documentation.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

protected:
    bool compare(const element& rhs) const;
public:
    virtual bool equals(const element& other) const = 0;

protected:
    void swap(element& other) noexcept;

private:
    dogen::identification::entities::name name_;
    std::string description_;
};

inline element::~element() noexcept { }

inline bool operator==(const element& lhs, const element& rhs) {
    return lhs.equals(rhs);
}

}

#endif
