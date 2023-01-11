/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_RELATIONS_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_RELATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/physical/constant_relation.hpp"
#include "dogen.logical/types/entities/physical/variable_relation.hpp"
#include "dogen.logical/types/entities/physical/hard_coded_relation.hpp"
#include "dogen.logical/serialization/entities/physical/relations_fwd_ser.hpp"

namespace dogen::logical::entities::physical {

class relations final {
public:
    relations() = default;
    relations(const relations&) = default;
    relations(relations&&) = default;
    ~relations() = default;

public:
    relations(
        const std::string& status,
        const std::list<dogen::logical::entities::physical::constant_relation>& constant,
        const std::list<dogen::logical::entities::physical::variable_relation>& variable,
        const std::list<dogen::logical::entities::physical::hard_coded_relation>& hard_coded);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::logical::entities::physical::relations& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::logical::entities::physical::relations& v, unsigned int version);

public:
    /**
     * @brief Status of this archetype with regards to relations.
     */
    /**@{*/
    const std::string& status() const;
    std::string& status();
    void status(const std::string& v);
    void status(const std::string&& v);
    /**@}*/

    /**
     * @brief All archetypes this archetype is related to,  over a fixed logical meta-model
     * element.
     */
    /**@{*/
    const std::list<dogen::logical::entities::physical::constant_relation>& constant() const;
    std::list<dogen::logical::entities::physical::constant_relation>& constant();
    void constant(const std::list<dogen::logical::entities::physical::constant_relation>& v);
    void constant(const std::list<dogen::logical::entities::physical::constant_relation>&& v);
    /**@}*/

    const std::list<dogen::logical::entities::physical::variable_relation>& variable() const;
    std::list<dogen::logical::entities::physical::variable_relation>& variable();
    void variable(const std::list<dogen::logical::entities::physical::variable_relation>& v);
    void variable(const std::list<dogen::logical::entities::physical::variable_relation>&& v);

    const std::list<dogen::logical::entities::physical::hard_coded_relation>& hard_coded() const;
    std::list<dogen::logical::entities::physical::hard_coded_relation>& hard_coded();
    void hard_coded(const std::list<dogen::logical::entities::physical::hard_coded_relation>& v);
    void hard_coded(const std::list<dogen::logical::entities::physical::hard_coded_relation>&& v);

public:
    bool operator==(const relations& rhs) const;
    bool operator!=(const relations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(relations& other) noexcept;
    relations& operator=(relations other);

private:
    std::string status_;
    std::list<dogen::logical::entities::physical::constant_relation> constant_;
    std::list<dogen::logical::entities::physical::variable_relation> variable_;
    std::list<dogen::logical::entities::physical::hard_coded_relation> hard_coded_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::relations& lhs,
    dogen::logical::entities::physical::relations& rhs) {
    lhs.swap(rhs);
}

}

#endif
