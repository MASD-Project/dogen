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
#ifndef DOGEN_TEXT_TYPES_ENTITIES_LOGICAL_PHYSICAL_REGION_HPP
#define DOGEN_TEXT_TYPES_ENTITIES_LOGICAL_PHYSICAL_REGION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.physical/types/entities/region.hpp"
#include "dogen.logical/types/entities/element_fwd.hpp"

namespace dogen::text::entities {

/**
 * @brief Represents a region of logical-physical space with a single logical element and
 * its associated physical elements.
 */
class logical_physical_region final {
public:
    logical_physical_region() = default;
    logical_physical_region(const logical_physical_region&) = default;
    logical_physical_region(logical_physical_region&&) = default;
    ~logical_physical_region() = default;

public:
    logical_physical_region(
        const boost::shared_ptr<dogen::logical::entities::element>& logical_element,
        const dogen::physical::entities::region& physical_region);

public:
    /**
     * @brief Logical element that gives rise to the artefact.
     */
    /**@{*/
    const boost::shared_ptr<dogen::logical::entities::element>& logical_element() const;
    boost::shared_ptr<dogen::logical::entities::element>& logical_element();
    void logical_element(const boost::shared_ptr<dogen::logical::entities::element>& v);
    void logical_element(const boost::shared_ptr<dogen::logical::entities::element>&& v);
    /**@}*/

    /**
     * @brief Physical artefacts that will be produced from the logical element.
     */
    /**@{*/
    const dogen::physical::entities::region& physical_region() const;
    dogen::physical::entities::region& physical_region();
    void physical_region(const dogen::physical::entities::region& v);
    void physical_region(const dogen::physical::entities::region&& v);
    /**@}*/

public:
    bool operator==(const logical_physical_region& rhs) const;
    bool operator!=(const logical_physical_region& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_physical_region& other) noexcept;
    logical_physical_region& operator=(logical_physical_region other);

private:
    boost::shared_ptr<dogen::logical::entities::element> logical_element_;
    dogen::physical::entities::region physical_region_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::entities::logical_physical_region& lhs,
    dogen::text::entities::logical_physical_region& rhs) {
    lhs.swap(rhs);
}

}

#endif
