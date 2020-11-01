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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_TECHNICAL_SPACE_PROPERTIES_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_TECHNICAL_SPACE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen::logical::entities::structural {

class technical_space_properties final {
public:
    technical_space_properties(const technical_space_properties&) = default;
    technical_space_properties(technical_space_properties&&) = default;
    ~technical_space_properties() = default;

public:
    technical_space_properties();

public:
    technical_space_properties(
        const bool requires_manual_default_constructor,
        const bool requires_manual_move_constructor,
        const bool requires_stream_manipulators,
        const bool is_floating_point,
        const bool requires_static_reference_equals);

public:
    bool requires_manual_default_constructor() const;
    void requires_manual_default_constructor(const bool v);

    bool requires_manual_move_constructor() const;
    void requires_manual_move_constructor(const bool v);

    bool requires_stream_manipulators() const;
    void requires_stream_manipulators(const bool v);

    bool is_floating_point() const;
    void is_floating_point(const bool v);

    bool requires_static_reference_equals() const;
    void requires_static_reference_equals(const bool v);

public:
    bool operator==(const technical_space_properties& rhs) const;
    bool operator!=(const technical_space_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(technical_space_properties& other) noexcept;
    technical_space_properties& operator=(technical_space_properties other);

private:
    bool requires_manual_default_constructor_;
    bool requires_manual_move_constructor_;
    bool requires_stream_manipulators_;
    bool is_floating_point_;
    bool requires_static_reference_equals_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::structural::technical_space_properties& lhs,
    dogen::logical::entities::structural::technical_space_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
