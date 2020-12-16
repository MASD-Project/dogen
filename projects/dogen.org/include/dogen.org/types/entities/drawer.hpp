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
#ifndef DOGEN_ORG_TYPES_ENTITIES_DRAWER_HPP
#define DOGEN_ORG_TYPES_ENTITIES_DRAWER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.org/types/entities/drawer_type.hpp"
#include "dogen.org/types/entities/drawer_content.hpp"

namespace dogen::org::entities {

class drawer final {
public:
    drawer(const drawer&) = default;
    drawer(drawer&&) = default;
    ~drawer() = default;

public:
    drawer();

public:
    drawer(
        const dogen::org::entities::drawer_type type,
        const std::list<dogen::org::entities::drawer_content>& contents);

public:
    dogen::org::entities::drawer_type type() const;
    void type(const dogen::org::entities::drawer_type v);

    const std::list<dogen::org::entities::drawer_content>& contents() const;
    std::list<dogen::org::entities::drawer_content>& contents();
    void contents(const std::list<dogen::org::entities::drawer_content>& v);
    void contents(const std::list<dogen::org::entities::drawer_content>&& v);

public:
    bool operator==(const drawer& rhs) const;
    bool operator!=(const drawer& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(drawer& other) noexcept;
    drawer& operator=(drawer other);

private:
    dogen::org::entities::drawer_type type_;
    std::list<dogen::org::entities::drawer_content> contents_;
};

}

namespace std {

template<>
inline void swap(
    dogen::org::entities::drawer& lhs,
    dogen::org::entities::drawer& rhs) {
    lhs.swap(rhs);
}

}

#endif
