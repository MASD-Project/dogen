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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_OUTPUT_MODEL_SET_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_OUTPUT_MODEL_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"

namespace dogen::logical::entities {

/**
 * @brief Represents a set of related logical models produced as ouput of the logical model chains.
 */
class output_model_set final {
public:
    output_model_set() = default;
    output_model_set(const output_model_set&) = default;
    output_model_set(output_model_set&&) = default;
    ~output_model_set() = default;

public:
    output_model_set(
        const dogen::identification::entities::logical_name& name,
        const std::list<dogen::logical::entities::model>& models);

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::identification::entities::logical_name& name() const;
    dogen::identification::entities::logical_name& name();
    void name(const dogen::identification::entities::logical_name& v);
    void name(const dogen::identification::entities::logical_name&& v);
    /**@}*/

    /**
     * @brief All models in this model set.
     */
    /**@{*/
    const std::list<dogen::logical::entities::model>& models() const;
    std::list<dogen::logical::entities::model>& models();
    void models(const std::list<dogen::logical::entities::model>& v);
    void models(const std::list<dogen::logical::entities::model>&& v);
    /**@}*/

public:
    bool operator==(const output_model_set& rhs) const;
    bool operator!=(const output_model_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(output_model_set& other) noexcept;
    output_model_set& operator=(output_model_set other);

private:
    dogen::identification::entities::logical_name name_;
    std::list<dogen::logical::entities::model> models_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::output_model_set& lhs,
    dogen::logical::entities::output_model_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
