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
#ifndef DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_ASPECT_PROPERTIES_HPP
#define DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_ASPECT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen::generation::csharp::formattables {

class aspect_properties final {
public:
    aspect_properties(const aspect_properties&) = default;
    aspect_properties(aspect_properties&&) = default;
    ~aspect_properties() = default;

public:
    aspect_properties();

public:
    aspect_properties(
        const bool is_floating_point,
        const bool requires_static_reference_equals);

public:
    bool is_floating_point() const;
    void is_floating_point(const bool v);

    bool requires_static_reference_equals() const;
    void requires_static_reference_equals(const bool v);

public:
    bool operator==(const aspect_properties& rhs) const;
    bool operator!=(const aspect_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(aspect_properties& other) noexcept;
    aspect_properties& operator=(aspect_properties other);

private:
    bool is_floating_point_;
    bool requires_static_reference_equals_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::csharp::formattables::aspect_properties& lhs,
    dogen::generation::csharp::formattables::aspect_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
