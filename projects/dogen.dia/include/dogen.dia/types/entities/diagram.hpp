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
#ifndef DOGEN_DIA_TYPES_ENTITIES_DIAGRAM_HPP
#define DOGEN_DIA_TYPES_ENTITIES_DIAGRAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include "dogen.dia/types/entities/layer.hpp"
#include "dogen.dia/types/entities/diagram_data.hpp"

namespace dogen::dia::entities {

/**
 * @brief Represents a diagram in Dia.
 */
class diagram final {
public:
    diagram() = default;
    diagram(const diagram&) = default;
    diagram(diagram&&) = default;
    ~diagram() = default;

public:
    diagram(
        const dogen::dia::entities::diagram_data& diagram_data,
        const std::vector<dogen::dia::entities::layer>& layers);

public:
    /**
     * @brief Basic diagram definitions.
     */
    /**@{*/
    const dogen::dia::entities::diagram_data& diagram_data() const;
    dogen::dia::entities::diagram_data& diagram_data();
    void diagram_data(const dogen::dia::entities::diagram_data& v);
    void diagram_data(const dogen::dia::entities::diagram_data&& v);
    /**@}*/

    /**
     * @brief Visual layers on the diagram.
     */
    /**@{*/
    const std::vector<dogen::dia::entities::layer>& layers() const;
    std::vector<dogen::dia::entities::layer>& layers();
    void layers(const std::vector<dogen::dia::entities::layer>& v);
    void layers(const std::vector<dogen::dia::entities::layer>&& v);
    /**@}*/

public:
    bool operator==(const diagram& rhs) const;
    bool operator!=(const diagram& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(diagram& other) noexcept;
    diagram& operator=(diagram other);

private:
    dogen::dia::entities::diagram_data diagram_data_;
    std::vector<dogen::dia::entities::layer> layers_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::diagram& lhs,
    dogen::dia::entities::diagram& rhs) {
    lhs.swap(rhs);
}

}

#endif
