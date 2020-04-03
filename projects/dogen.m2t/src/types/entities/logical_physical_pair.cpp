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
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.m2t/types/entities/logical_physical_pair.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::element>& lhs,
const boost::shared_ptr<dogen::logical::entities::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::physical::entities::artefact>& lhs,
const boost::shared_ptr<dogen::physical::entities::artefact>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::m2t::entities {

logical_physical_pair::logical_physical_pair(
    const boost::shared_ptr<dogen::logical::entities::element>& logical_element,
    const boost::shared_ptr<dogen::physical::entities::artefact>& physical_artefact)
    : logical_element_(logical_element),
      physical_artefact_(physical_artefact) { }

void logical_physical_pair::swap(logical_physical_pair& other) noexcept {
    using std::swap;
    swap(logical_element_, other.logical_element_);
    swap(physical_artefact_, other.physical_artefact_);
}

bool logical_physical_pair::operator==(const logical_physical_pair& rhs) const {
    return logical_element_ == rhs.logical_element_ &&
        physical_artefact_ == rhs.physical_artefact_;
}

logical_physical_pair& logical_physical_pair::operator=(logical_physical_pair other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::logical::entities::element>& logical_physical_pair::logical_element() const {
    return logical_element_;
}

boost::shared_ptr<dogen::logical::entities::element>& logical_physical_pair::logical_element() {
    return logical_element_;
}

void logical_physical_pair::logical_element(const boost::shared_ptr<dogen::logical::entities::element>& v) {
    logical_element_ = v;
}

void logical_physical_pair::logical_element(const boost::shared_ptr<dogen::logical::entities::element>&& v) {
    logical_element_ = std::move(v);
}

const boost::shared_ptr<dogen::physical::entities::artefact>& logical_physical_pair::physical_artefact() const {
    return physical_artefact_;
}

boost::shared_ptr<dogen::physical::entities::artefact>& logical_physical_pair::physical_artefact() {
    return physical_artefact_;
}

void logical_physical_pair::physical_artefact(const boost::shared_ptr<dogen::physical::entities::artefact>& v) {
    physical_artefact_ = v;
}

void logical_physical_pair::physical_artefact(const boost::shared_ptr<dogen::physical::entities::artefact>&& v) {
    physical_artefact_ = std::move(v);
}

}
