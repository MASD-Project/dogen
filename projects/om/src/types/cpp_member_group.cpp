/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/om/types/cpp_feature.hpp"
#include "dogen/om/types/cpp_member_group.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::om::cpp_feature>& lhs,
const boost::shared_ptr<dogen::om::cpp_feature>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace om {

cpp_member_group::cpp_member_group()
    : type_(static_cast<dogen::om::cpp_access_specifier_types>(0)) { }

cpp_member_group::cpp_member_group(
    const dogen::om::cpp_access_specifier_types& type,
    const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features)
    : type_(type),
      features_(features) { }

void cpp_member_group::swap(cpp_member_group& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(features_, other.features_);
}

bool cpp_member_group::operator==(const cpp_member_group& rhs) const {
    return type_ == rhs.type_ &&
        features_ == rhs.features_;
}

cpp_member_group& cpp_member_group::operator=(cpp_member_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::om::cpp_access_specifier_types cpp_member_group::type() const {
    return type_;
}

void cpp_member_group::type(const dogen::om::cpp_access_specifier_types& v) {
    type_ = v;
}

const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& cpp_member_group::features() const {
    return features_;
}

std::list<boost::shared_ptr<dogen::om::cpp_feature> >& cpp_member_group::features() {
    return features_;
}

void cpp_member_group::features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& v) {
    features_ = v;
}

void cpp_member_group::features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >&& v) {
    features_ = std::move(v);
}

} }