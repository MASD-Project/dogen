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
#include "dogen.text/types/entities/logical_physical_region.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::element>& lhs,
const boost::shared_ptr<dogen::logical::entities::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::text::entities {

logical_physical_region::logical_physical_region(
    const boost::shared_ptr<dogen::logical::entities::element>& logical_element,
    const dogen::physical::entities::region& physical_region)
    : logical_element_(logical_element),
      physical_region_(physical_region) { }

void logical_physical_region::swap(logical_physical_region& other) noexcept {
    using std::swap;
    swap(logical_element_, other.logical_element_);
    swap(physical_region_, other.physical_region_);
}

bool logical_physical_region::operator==(const logical_physical_region& rhs) const {
    return logical_element_ == rhs.logical_element_ &&
        physical_region_ == rhs.physical_region_;
}

logical_physical_region& logical_physical_region::operator=(logical_physical_region other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::logical::entities::element>& logical_physical_region::logical_element() const {
    return logical_element_;
}

boost::shared_ptr<dogen::logical::entities::element>& logical_physical_region::logical_element() {
    return logical_element_;
}

void logical_physical_region::logical_element(const boost::shared_ptr<dogen::logical::entities::element>& v) {
    logical_element_ = v;
}

void logical_physical_region::logical_element(const boost::shared_ptr<dogen::logical::entities::element>&& v) {
    logical_element_ = std::move(v);
}

const dogen::physical::entities::region& logical_physical_region::physical_region() const {
    return physical_region_;
}

dogen::physical::entities::region& logical_physical_region::physical_region() {
    return physical_region_;
}

void logical_physical_region::physical_region(const dogen::physical::entities::region& v) {
    physical_region_ = v;
}

void logical_physical_region::physical_region(const dogen::physical::entities::region&& v) {
    physical_region_ = std::move(v);
}

}
