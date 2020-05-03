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
#ifndef DOGEN_TEXT_TYPES_ENTITIES_ELEMENT_ARTEFACTS_HPP
#define DOGEN_TEXT_TYPES_ENTITIES_ELEMENT_ARTEFACTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/element_fwd.hpp"
#include "dogen.physical/types/entities/artefact_fwd.hpp"

namespace dogen::text::entities {

/**
 * @brief Maps logical elements with the physical artefacts that will be produced from them.
 */
class element_artefacts final {
public:
    element_artefacts() = default;
    element_artefacts(const element_artefacts&) = default;
    element_artefacts(element_artefacts&&) = default;
    ~element_artefacts() = default;

public:
    element_artefacts(
        const boost::shared_ptr<dogen::logical::entities::element>& element,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts);

public:
    /**
     * @brief Logical element that gives rise to the artefact.
     */
    /**@{*/
    const boost::shared_ptr<dogen::logical::entities::element>& element() const;
    boost::shared_ptr<dogen::logical::entities::element>& element();
    void element(const boost::shared_ptr<dogen::logical::entities::element>& v);
    void element(const boost::shared_ptr<dogen::logical::entities::element>&& v);
    /**@}*/

    /**
     * @brief Physical artefact that will be produced from the logical element.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts();
    void artefacts(const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& v);
    void artefacts(const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >&& v);
    /**@}*/

public:
    bool operator==(const element_artefacts& rhs) const;
    bool operator!=(const element_artefacts& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_artefacts& other) noexcept;
    element_artefacts& operator=(element_artefacts other);

private:
    boost::shared_ptr<dogen::logical::entities::element> element_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> > artefacts_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::entities::element_artefacts& lhs,
    dogen::text::entities::element_artefacts& rhs) {
    lhs.swap(rhs);
}

}

#endif
