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
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.text/types/entities/element_artefacts.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::element>& lhs,
const boost::shared_ptr<dogen::logical::entities::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::text::entities {

element_artefacts::element_artefacts(
    const boost::shared_ptr<dogen::logical::entities::element>& element,
    const dogen::physical::entities::artefact_set& artefacts)
    : element_(element),
      artefacts_(artefacts) { }

void element_artefacts::swap(element_artefacts& other) noexcept {
    using std::swap;
    swap(element_, other.element_);
    swap(artefacts_, other.artefacts_);
}

bool element_artefacts::operator==(const element_artefacts& rhs) const {
    return element_ == rhs.element_ &&
        artefacts_ == rhs.artefacts_;
}

element_artefacts& element_artefacts::operator=(element_artefacts other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::logical::entities::element>& element_artefacts::element() const {
    return element_;
}

boost::shared_ptr<dogen::logical::entities::element>& element_artefacts::element() {
    return element_;
}

void element_artefacts::element(const boost::shared_ptr<dogen::logical::entities::element>& v) {
    element_ = v;
}

void element_artefacts::element(const boost::shared_ptr<dogen::logical::entities::element>&& v) {
    element_ = std::move(v);
}

const dogen::physical::entities::artefact_set& element_artefacts::artefacts() const {
    return artefacts_;
}

dogen::physical::entities::artefact_set& element_artefacts::artefacts() {
    return artefacts_;
}

void element_artefacts::artefacts(const dogen::physical::entities::artefact_set& v) {
    artefacts_ = v;
}

void element_artefacts::artefacts(const dogen::physical::entities::artefact_set&& v) {
    artefacts_ = std::move(v);
}

}
