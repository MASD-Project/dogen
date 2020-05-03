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
#ifndef DOGEN_TEXT_CSHARP_TYPES_FORMATTABLES_AUXILIARY_FUNCTION_PROPERTIES_HPP
#define DOGEN_TEXT_CSHARP_TYPES_FORMATTABLES_AUXILIARY_FUNCTION_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.text.csharp/types/formattables/auxiliary_function_types.hpp"

namespace dogen::text::csharp::formattables {

class auxiliary_function_properties final {
public:
    auxiliary_function_properties(const auxiliary_function_properties&) = default;
    auxiliary_function_properties(auxiliary_function_properties&&) = default;
    ~auxiliary_function_properties() = default;

public:
    auxiliary_function_properties();

public:
    auxiliary_function_properties(
        const dogen::text::csharp::formattables::auxiliary_function_types type,
        const std::string& name);

public:
    dogen::text::csharp::formattables::auxiliary_function_types type() const;
    void type(const dogen::text::csharp::formattables::auxiliary_function_types v);

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

public:
    bool operator==(const auxiliary_function_properties& rhs) const;
    bool operator!=(const auxiliary_function_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(auxiliary_function_properties& other) noexcept;
    auxiliary_function_properties& operator=(auxiliary_function_properties other);

private:
    dogen::text::csharp::formattables::auxiliary_function_types type_;
    std::string name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::csharp::formattables::auxiliary_function_properties& lhs,
    dogen::text::csharp::formattables::auxiliary_function_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
