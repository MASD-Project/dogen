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
#ifndef DOGEN_M2T_TYPES_ENTITIES_LOGICAL_PHYSICAL_PAIR_HPP
#define DOGEN_M2T_TYPES_ENTITIES_LOGICAL_PHYSICAL_PAIR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/element_fwd.hpp"
#include "dogen.physical/types/entities/artefact_fwd.hpp"

namespace dogen::m2t::entities {

/**
 * @brief Pairs up logical elements with the physical artefacts that will be produced from them.
 */
class logical_physical_pair final {
public:
    logical_physical_pair() = default;
    logical_physical_pair(const logical_physical_pair&) = default;
    logical_physical_pair(logical_physical_pair&&) = default;
    ~logical_physical_pair() = default;

public:
    logical_physical_pair(
        const boost::shared_ptr<dogen::logical::entities::element>& logical_element,
        const boost::shared_ptr<dogen::physical::entities::artefact>& physical_artefact);

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
     * @brief Physical artefact that will be produced from the logical element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::physical::entities::artefact>& physical_artefact() const;
    boost::shared_ptr<dogen::physical::entities::artefact>& physical_artefact();
    void physical_artefact(const boost::shared_ptr<dogen::physical::entities::artefact>& v);
    void physical_artefact(const boost::shared_ptr<dogen::physical::entities::artefact>&& v);
    /**@}*/

public:
    bool operator==(const logical_physical_pair& rhs) const;
    bool operator!=(const logical_physical_pair& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_physical_pair& other) noexcept;
    logical_physical_pair& operator=(logical_physical_pair other);

private:
    boost::shared_ptr<dogen::logical::entities::element> logical_element_;
    boost::shared_ptr<dogen::physical::entities::artefact> physical_artefact_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::entities::logical_physical_pair& lhs,
    dogen::m2t::entities::logical_physical_pair& rhs) {
    lhs.swap(rhs);
}

}

#endif
