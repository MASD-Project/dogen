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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_NAME_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.assets/types/meta_model/location.hpp"
#include "dogen.assets/types/meta_model/fully_qualified_representation.hpp"

namespace dogen::assets::meta_model {

/**
 * @brief Name of an element in asset space.
 *
 * A name represents a point in asset space, and this point can only be
 * used by one asset element. Names can be uniquely identified by their
 * qualified ID.
 *
 * Name has the following properties: a) two different points in element space
 * cannot have the same name and b) the same point in element space can only
 * have one and only one name.
 *
 * Names are required in addition to just using the qualfied ID representation
 * because we use them to infer all sorts of properties for an element (namespaces,
 * naming files, etc).
 */
class name final {
public:
    name() = default;
    name(const name&) = default;
    name(name&&) = default;
    ~name() = default;

public:
    name(
        const dogen::assets::meta_model::fully_qualified_representation& qualified,
        const std::string& simple,
        const dogen::assets::meta_model::location& location);

public:
    const dogen::assets::meta_model::fully_qualified_representation& qualified() const;
    dogen::assets::meta_model::fully_qualified_representation& qualified();
    void qualified(const dogen::assets::meta_model::fully_qualified_representation& v);
    void qualified(const dogen::assets::meta_model::fully_qualified_representation&& v);

    /**
     * @brief Simple (non-qualified) name of the assets element at this address.
     *
     * The simple name must be unique for a given location.
     */
    /**@{*/
    const std::string& simple() const;
    std::string& simple();
    void simple(const std::string& v);
    void simple(const std::string&& v);
    /**@}*/

    /**
     * @brief Where the name is located in element space.
     */
    /**@{*/
    const dogen::assets::meta_model::location& location() const;
    dogen::assets::meta_model::location& location();
    void location(const dogen::assets::meta_model::location& v);
    void location(const dogen::assets::meta_model::location&& v);
    /**@}*/

public:
    bool operator==(const name& rhs) const;
    bool operator!=(const name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(name& other) noexcept;
    name& operator=(name other);

private:
    dogen::assets::meta_model::fully_qualified_representation qualified_;
    std::string simple_;
    dogen::assets::meta_model::location location_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::name& lhs,
    dogen::assets::meta_model::name& rhs) {
    lhs.swap(rhs);
}

}

#endif
