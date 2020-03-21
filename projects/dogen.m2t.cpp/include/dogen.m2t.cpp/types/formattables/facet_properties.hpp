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
#ifndef DOGEN_M2T_CPP_TYPES_FORMATTABLES_FACET_PROPERTIES_HPP
#define DOGEN_M2T_CPP_TYPES_FORMATTABLES_FACET_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::m2t::cpp::formattables {

class facet_properties final {
public:
    facet_properties(const facet_properties&) = default;
    facet_properties(facet_properties&&) = default;
    ~facet_properties() = default;

public:
    facet_properties();

public:
    facet_properties(
        const std::string& directory,
        const bool enabled);

public:
    const std::string& directory() const;
    std::string& directory();
    void directory(const std::string& v);
    void directory(const std::string&& v);

    bool enabled() const;
    void enabled(const bool v);

public:
    bool operator==(const facet_properties& rhs) const;
    bool operator!=(const facet_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(facet_properties& other) noexcept;
    facet_properties& operator=(facet_properties other);

private:
    std::string directory_;
    bool enabled_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::cpp::formattables::facet_properties& lhs,
    dogen::m2t::cpp::formattables::facet_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
