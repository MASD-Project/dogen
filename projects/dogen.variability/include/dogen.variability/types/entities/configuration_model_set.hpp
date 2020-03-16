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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_MODEL_SET_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_MODEL_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.variability/types/entities/configuration_model.hpp"

namespace dogen::variability::entities {

class configuration_model_set final {
public:
    configuration_model_set() = default;
    configuration_model_set(const configuration_model_set&) = default;
    configuration_model_set(configuration_model_set&&) = default;
    ~configuration_model_set() = default;

public:
    explicit configuration_model_set(const std::list<dogen::variability::entities::configuration_model>& models);

public:
    const std::list<dogen::variability::entities::configuration_model>& models() const;
    std::list<dogen::variability::entities::configuration_model>& models();
    void models(const std::list<dogen::variability::entities::configuration_model>& v);
    void models(const std::list<dogen::variability::entities::configuration_model>&& v);

public:
    bool operator==(const configuration_model_set& rhs) const;
    bool operator!=(const configuration_model_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(configuration_model_set& other) noexcept;
    configuration_model_set& operator=(configuration_model_set other);

private:
    std::list<dogen::variability::entities::configuration_model> models_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::configuration_model_set& lhs,
    dogen::variability::entities::configuration_model_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
