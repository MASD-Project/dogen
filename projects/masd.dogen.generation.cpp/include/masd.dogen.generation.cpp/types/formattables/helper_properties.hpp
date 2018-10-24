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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_HELPER_PROPERTIES_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_HELPER_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "masd.dogen.generation.cpp/types/formattables/helper_descriptor.hpp"

namespace masd::dogen::generation::cpp::formattables {

class helper_properties final {
public:
    helper_properties(const helper_properties&) = default;
    helper_properties(helper_properties&&) = default;
    ~helper_properties() = default;

public:
    helper_properties();

public:
    helper_properties(
        const masd::dogen::generation::cpp::formattables::helper_descriptor& current,
        const std::list<masd::dogen::generation::cpp::formattables::helper_descriptor>& direct_descendants,
        const bool in_inheritance_relationship);

public:
    const masd::dogen::generation::cpp::formattables::helper_descriptor& current() const;
    masd::dogen::generation::cpp::formattables::helper_descriptor& current();
    void current(const masd::dogen::generation::cpp::formattables::helper_descriptor& v);
    void current(const masd::dogen::generation::cpp::formattables::helper_descriptor&& v);

    const std::list<masd::dogen::generation::cpp::formattables::helper_descriptor>& direct_descendants() const;
    std::list<masd::dogen::generation::cpp::formattables::helper_descriptor>& direct_descendants();
    void direct_descendants(const std::list<masd::dogen::generation::cpp::formattables::helper_descriptor>& v);
    void direct_descendants(const std::list<masd::dogen::generation::cpp::formattables::helper_descriptor>&& v);

    bool in_inheritance_relationship() const;
    void in_inheritance_relationship(const bool v);

public:
    bool operator==(const helper_properties& rhs) const;
    bool operator!=(const helper_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_properties& other) noexcept;
    helper_properties& operator=(helper_properties other);

private:
    masd::dogen::generation::cpp::formattables::helper_descriptor current_;
    std::list<masd::dogen::generation::cpp::formattables::helper_descriptor> direct_descendants_;
    bool in_inheritance_relationship_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::cpp::formattables::helper_properties& lhs,
    masd::dogen::generation::cpp::formattables::helper_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
