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
#include "dogen/quilt.cpp/types/annotations/opaque_annotations.hpp"
#include "dogen/quilt.cpp/types/annotations/element_annotations.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& lhs,
const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

element_annotations::element_annotations(
    const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& opaque_annotations,
    const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >& opaque_annotations_for_property)
    : opaque_annotations_(opaque_annotations),
      opaque_annotations_for_property_(opaque_annotations_for_property) { }

void element_annotations::swap(element_annotations& other) noexcept {
    using std::swap;
    swap(opaque_annotations_, other.opaque_annotations_);
    swap(opaque_annotations_for_property_, other.opaque_annotations_for_property_);
}

bool element_annotations::operator==(const element_annotations& rhs) const {
    return opaque_annotations_ == rhs.opaque_annotations_ &&
        opaque_annotations_for_property_ == rhs.opaque_annotations_for_property_;
}

element_annotations& element_annotations::operator=(element_annotations other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& element_annotations::opaque_annotations() const {
    return opaque_annotations_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& element_annotations::opaque_annotations() {
    return opaque_annotations_;
}

void element_annotations::opaque_annotations(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& v) {
    opaque_annotations_ = v;
}

void element_annotations::opaque_annotations(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >&& v) {
    opaque_annotations_ = std::move(v);
}

const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >& element_annotations::opaque_annotations_for_property() const {
    return opaque_annotations_for_property_;
}

std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >& element_annotations::opaque_annotations_for_property() {
    return opaque_annotations_for_property_;
}

void element_annotations::opaque_annotations_for_property(const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >& v) {
    opaque_annotations_for_property_ = v;
}

void element_annotations::opaque_annotations_for_property(const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >&& v) {
    opaque_annotations_for_property_ = std::move(v);
}

} } } }
