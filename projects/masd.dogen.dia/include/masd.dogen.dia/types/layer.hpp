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
#ifndef MASD_DOGEN_DIA_TYPES_LAYER_HPP
#define MASD_DOGEN_DIA_TYPES_LAYER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include "masd.dogen.dia/types/object.hpp"
#include "masd.dogen.dia/serialization/layer_fwd_ser.hpp"

namespace masd::dogen::dia {

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
        const std::vector<masd::dogen::dia::object>& objects);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const masd::dogen::dia::layer& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, masd::dogen::dia::layer& v, unsigned int version);

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
    const std::vector<masd::dogen::dia::object>& objects() const;
    std::vector<masd::dogen::dia::object>& objects();
    void objects(const std::vector<masd::dogen::dia::object>& v);
    void objects(const std::vector<masd::dogen::dia::object>&& v);
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
    std::vector<masd::dogen::dia::object> objects_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::dia::layer& lhs,
    masd::dogen::dia::layer& rhs) {
    lhs.swap(rhs);
}

}

#endif
