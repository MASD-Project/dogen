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
#ifndef DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_ATTRIBUTE_PROPERTIES_HPP
#define DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_ATTRIBUTE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.m2t.csharp/types/formattables/auxiliary_function_properties.hpp"

namespace dogen::m2t::csharp::formattables {

class attribute_properties final {
public:
    attribute_properties() = default;
    attribute_properties(const attribute_properties&) = default;
    attribute_properties(attribute_properties&&) = default;
    ~attribute_properties() = default;

public:
    explicit attribute_properties(const std::unordered_map<std::string, dogen::m2t::csharp::formattables::auxiliary_function_properties>& auxiliary_function_properties);

public:
    const std::unordered_map<std::string, dogen::m2t::csharp::formattables::auxiliary_function_properties>& auxiliary_function_properties() const;
    std::unordered_map<std::string, dogen::m2t::csharp::formattables::auxiliary_function_properties>& auxiliary_function_properties();
    void auxiliary_function_properties(const std::unordered_map<std::string, dogen::m2t::csharp::formattables::auxiliary_function_properties>& v);
    void auxiliary_function_properties(const std::unordered_map<std::string, dogen::m2t::csharp::formattables::auxiliary_function_properties>&& v);

public:
    bool operator==(const attribute_properties& rhs) const;
    bool operator!=(const attribute_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(attribute_properties& other) noexcept;
    attribute_properties& operator=(attribute_properties other);

private:
    std::unordered_map<std::string, dogen::m2t::csharp::formattables::auxiliary_function_properties> auxiliary_function_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::csharp::formattables::attribute_properties& lhs,
    dogen::m2t::csharp::formattables::attribute_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
