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
#include "dogen.text.csharp/types/formattables/formattable.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::element>& lhs,
const boost::shared_ptr<dogen::logical::entities::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::text::csharp::formattables {

formattable::formattable(
    const boost::shared_ptr<dogen::logical::entities::element>& element,
    const dogen::physical::entities::region& artefacts)
    : element_(element),
      artefacts_(artefacts) { }

void formattable::swap(formattable& other) noexcept {
    using std::swap;
    swap(element_, other.element_);
    swap(artefacts_, other.artefacts_);
}

bool formattable::operator==(const formattable& rhs) const {
    return element_ == rhs.element_ &&
        artefacts_ == rhs.artefacts_;
}

formattable& formattable::operator=(formattable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::logical::entities::element>& formattable::element() const {
    return element_;
}

boost::shared_ptr<dogen::logical::entities::element>& formattable::element() {
    return element_;
}

void formattable::element(const boost::shared_ptr<dogen::logical::entities::element>& v) {
    element_ = v;
}

void formattable::element(const boost::shared_ptr<dogen::logical::entities::element>&& v) {
    element_ = std::move(v);
}

const dogen::physical::entities::region& formattable::artefacts() const {
    return artefacts_;
}

dogen::physical::entities::region& formattable::artefacts() {
    return artefacts_;
}

void formattable::artefacts(const dogen::physical::entities::region& v) {
    artefacts_ = v;
}

void formattable::artefacts(const dogen::physical::entities::region&& v) {
    artefacts_ = std::move(v);
}

}
