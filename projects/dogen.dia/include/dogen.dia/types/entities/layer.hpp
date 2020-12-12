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
#ifndef DOGEN_DIA_TYPES_ENTITIES_LAYER_HPP
#define DOGEN_DIA_TYPES_ENTITIES_LAYER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include "dogen.dia/types/entities/object.hpp"

namespace dogen::dia::entities {

/**
 * @brief Represents a layer in a Dia diagram.
 */
class layer final {
public:
    layer(const layer&) = default;
    layer(layer&&) = default;
    ~layer() = default;

public:
    layer();

public:
    layer(
        const std::string& name,
        const bool visible,
        const bool active,
        const std::vector<dogen::dia::entities::object>& objects);

public:
    /**
     * @brief Name of the layer.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Whether the layer is visible on screen or not.
     */
    /**@{*/
    bool visible() const;
    void visible(const bool v);
    /**@}*/

    /**
     * @brief Whether the layer is active or not.
     */
    /**@{*/
    bool active() const;
    void active(const bool v);
    /**@}*/

    /**
     * @brief Dia objects contained in layer.
     */
    /**@{*/
    const std::vector<dogen::dia::entities::object>& objects() const;
    std::vector<dogen::dia::entities::object>& objects();
    void objects(const std::vector<dogen::dia::entities::object>& v);
    void objects(const std::vector<dogen::dia::entities::object>&& v);
    /**@}*/

public:
    bool operator==(const layer& rhs) const;
    bool operator!=(const layer& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(layer& other) noexcept;
    layer& operator=(layer other);

private:
    std::string name_;
    bool visible_;
    bool active_;
    std::vector<dogen::dia::entities::object> objects_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::layer& lhs,
    dogen::dia::entities::layer& rhs) {
    lhs.swap(rhs);
}

}

#endif
