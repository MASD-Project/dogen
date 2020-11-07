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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_ELEMENT_PROPERTIES_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_ELEMENT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.logical/types/entities/helper_properties.hpp"

namespace dogen::text::cpp::formattables {

/**
 * @brief All of the properties associated with an element.
 */
class element_properties final {
public:
    element_properties() = default;
    element_properties(const element_properties&) = default;
    element_properties(element_properties&&) = default;
    ~element_properties() = default;

public:
    explicit element_properties(const std::list<dogen::logical::entities::helper_properties>& helper_properties);

public:
    const std::list<dogen::logical::entities::helper_properties>& helper_properties() const;
    std::list<dogen::logical::entities::helper_properties>& helper_properties();
    void helper_properties(const std::list<dogen::logical::entities::helper_properties>& v);
    void helper_properties(const std::list<dogen::logical::entities::helper_properties>&& v);

public:
    bool operator==(const element_properties& rhs) const;
    bool operator!=(const element_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_properties& other) noexcept;
    element_properties& operator=(element_properties other);

private:
    std::list<dogen::logical::entities::helper_properties> helper_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::cpp::formattables::element_properties& lhs,
    dogen::text::cpp::formattables::element_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
