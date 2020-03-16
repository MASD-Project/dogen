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
#ifndef DOGEN_INJECTION_TYPES_ENTITIES_MODEL_SET_HPP
#define DOGEN_INJECTION_TYPES_ENTITIES_MODEL_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.injection/types/entities/model.hpp"
#include "dogen.injection/types/entities/reference_graph_data.hpp"

namespace dogen::injection::entities {

class model_set final {
public:
    model_set() = default;
    model_set(const model_set&) = default;
    model_set(model_set&&) = default;
    ~model_set() = default;

public:
    model_set(
        const dogen::injection::entities::model& target,
        const std::list<dogen::injection::entities::model>& references,
        const dogen::injection::entities::reference_graph_data& reference_graph_data);

public:
    const dogen::injection::entities::model& target() const;
    dogen::injection::entities::model& target();
    void target(const dogen::injection::entities::model& v);
    void target(const dogen::injection::entities::model&& v);

    const std::list<dogen::injection::entities::model>& references() const;
    std::list<dogen::injection::entities::model>& references();
    void references(const std::list<dogen::injection::entities::model>& v);
    void references(const std::list<dogen::injection::entities::model>&& v);

    /**
     * @brief Stores the data required to build a graph of references for a model set.
     */
    /**@{*/
    const dogen::injection::entities::reference_graph_data& reference_graph_data() const;
    dogen::injection::entities::reference_graph_data& reference_graph_data();
    void reference_graph_data(const dogen::injection::entities::reference_graph_data& v);
    void reference_graph_data(const dogen::injection::entities::reference_graph_data&& v);
    /**@}*/

public:
    bool operator==(const model_set& rhs) const;
    bool operator!=(const model_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model_set& other) noexcept;
    model_set& operator=(model_set other);

private:
    dogen::injection::entities::model target_;
    std::list<dogen::injection::entities::model> references_;
    dogen::injection::entities::reference_graph_data reference_graph_data_;
};

}

namespace std {

template<>
inline void swap(
    dogen::injection::entities::model_set& lhs,
    dogen::injection::entities::model_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
