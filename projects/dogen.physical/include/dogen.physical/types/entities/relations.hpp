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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_RELATIONS_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_RELATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.physical/types/entities/relation_status.hpp"
#include "dogen.physical/types/entities/constant_relation.hpp"
#include "dogen.physical/types/entities/variable_relation.hpp"
#include "dogen.physical/types/entities/hard_coded_relation.hpp"

namespace dogen::physical::entities {

/**
 * @brief Models relationships between archetypes.
 */
class relations final {
public:
    relations(const relations&) = default;
    relations(relations&&) = default;
    ~relations() = default;

public:
    relations();

public:
    relations(
        const dogen::physical::entities::relation_status status,
        const std::list<dogen::physical::entities::constant_relation>& constant,
        const std::list<dogen::physical::entities::variable_relation>& variable,
        const std::list<dogen::physical::entities::hard_coded_relation>& hard_coded);

public:
    /**
     * @brief Status of this archetype with regards to being related to archetypes.
     */
    /**@{*/
    dogen::physical::entities::relation_status status() const;
    void status(const dogen::physical::entities::relation_status v);
    /**@}*/

    /**
     * @brief All archetypes this archetype is related to,  over a fixed logical meta-model
     * element.
     */
    /**@{*/
    const std::list<dogen::physical::entities::constant_relation>& constant() const;
    std::list<dogen::physical::entities::constant_relation>& constant();
    void constant(const std::list<dogen::physical::entities::constant_relation>& v);
    void constant(const std::list<dogen::physical::entities::constant_relation>&& v);
    /**@}*/

    /**
     * @brief All archetypes this archetype is related to,  over a variable logical meta-model
     * element.
     */
    /**@{*/
    const std::list<dogen::physical::entities::variable_relation>& variable() const;
    std::list<dogen::physical::entities::variable_relation>& variable();
    void variable(const std::list<dogen::physical::entities::variable_relation>& v);
    void variable(const std::list<dogen::physical::entities::variable_relation>&& v);
    /**@}*/

    const std::list<dogen::physical::entities::hard_coded_relation>& hard_coded() const;
    std::list<dogen::physical::entities::hard_coded_relation>& hard_coded();
    void hard_coded(const std::list<dogen::physical::entities::hard_coded_relation>& v);
    void hard_coded(const std::list<dogen::physical::entities::hard_coded_relation>&& v);

public:
    bool operator==(const relations& rhs) const;
    bool operator!=(const relations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(relations& other) noexcept;
    relations& operator=(relations other);

private:
    dogen::physical::entities::relation_status status_;
    std::list<dogen::physical::entities::constant_relation> constant_;
    std::list<dogen::physical::entities::variable_relation> variable_;
    std::list<dogen::physical::entities::hard_coded_relation> hard_coded_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::relations& lhs,
    dogen::physical::entities::relations& rhs) {
    lhs.swap(rhs);
}

}

#endif
