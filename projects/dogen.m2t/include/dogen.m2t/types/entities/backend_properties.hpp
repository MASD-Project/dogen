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
#ifndef DOGEN_M2T_TYPES_ENTITIES_BACKEND_PROPERTIES_HPP
#define DOGEN_M2T_TYPES_ENTITIES_BACKEND_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen::m2t::entities {

/**
 * @brief Properties related to the backend.
 */
class backend_properties final {
public:
    backend_properties(const backend_properties&) = default;
    backend_properties(backend_properties&&) = default;
    ~backend_properties() = default;

public:
    backend_properties();

public:
    explicit backend_properties(const bool enabled);

public:
    /**
     * @brief If true, this backend is enabled.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

public:
    bool operator==(const backend_properties& rhs) const;
    bool operator!=(const backend_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(backend_properties& other) noexcept;
    backend_properties& operator=(backend_properties other);

private:
    bool enabled_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::entities::backend_properties& lhs,
    dogen::m2t::entities::backend_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
