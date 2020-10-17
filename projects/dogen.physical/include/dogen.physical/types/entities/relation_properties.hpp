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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_RELATION_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_RELATION_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.physical/types/entities/relation_status.hpp"

namespace dogen::physical::entities {

class relation_properties final {
public:
    relation_properties(const relation_properties&) = default;
    relation_properties(relation_properties&&) = default;
    ~relation_properties() = default;

public:
    relation_properties();

public:
    relation_properties(
        const std::list<std::string>& relations,
        const dogen::physical::entities::relation_status relation_status);

public:
    /**
     * @brief Artefacts that this artefact depends on.
     *
     * The format used is dependent on the technical space the artefact belongs to.
     */
    /**@{*/
    const std::list<std::string>& relations() const;
    std::list<std::string>& relations();
    void relations(const std::list<std::string>& v);
    void relations(const std::list<std::string>&& v);
    /**@}*/

    dogen::physical::entities::relation_status relation_status() const;
    void relation_status(const dogen::physical::entities::relation_status v);

public:
    bool operator==(const relation_properties& rhs) const;
    bool operator!=(const relation_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(relation_properties& other) noexcept;
    relation_properties& operator=(relation_properties other);

private:
    std::list<std::string> relations_;
    dogen::physical::entities::relation_status relation_status_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::relation_properties& lhs,
    dogen::physical::entities::relation_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
