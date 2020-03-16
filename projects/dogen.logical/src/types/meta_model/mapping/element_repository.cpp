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
#include "dogen.logical/types/meta_model/mapping/fixed_mappable.hpp"
#include "dogen.logical/types/meta_model/mapping/element_repository.hpp"
#include "dogen.logical/types/meta_model/mapping/extensible_mappable.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::meta_model::mapping::extensible_mappable>& lhs,
const boost::shared_ptr<dogen::logical::meta_model::mapping::extensible_mappable>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::meta_model::mapping::fixed_mappable>& lhs,
const boost::shared_ptr<dogen::logical::meta_model::mapping::fixed_mappable>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::meta_model::mapping {

element_repository::element_repository(
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::extensible_mappable> >& extensible_mappables,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::fixed_mappable> >& fixed_mappables)
    : extensible_mappables_(extensible_mappables),
      fixed_mappables_(fixed_mappables) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(extensible_mappables_, other.extensible_mappables_);
    swap(fixed_mappables_, other.fixed_mappables_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return extensible_mappables_ == rhs.extensible_mappables_ &&
        fixed_mappables_ == rhs.fixed_mappables_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::extensible_mappable> >& element_repository::extensible_mappables() const {
    return extensible_mappables_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::extensible_mappable> >& element_repository::extensible_mappables() {
    return extensible_mappables_;
}

void element_repository::extensible_mappables(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::extensible_mappable> >& v) {
    extensible_mappables_ = v;
}

void element_repository::extensible_mappables(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::extensible_mappable> >&& v) {
    extensible_mappables_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::fixed_mappable> >& element_repository::fixed_mappables() const {
    return fixed_mappables_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::fixed_mappable> >& element_repository::fixed_mappables() {
    return fixed_mappables_;
}

void element_repository::fixed_mappables(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::fixed_mappable> >& v) {
    fixed_mappables_ = v;
}

void element_repository::fixed_mappables(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::mapping::fixed_mappable> >&& v) {
    fixed_mappables_ = std::move(v);
}

}
