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
#include "dogen.text/types/transforms/repository.hpp"
#include "dogen.text/types/transforms/helper_transform.hpp"

namespace std {

inline bool operator==(const std::shared_ptr<dogen::text::transforms::helper_transform>& lhs,
const std::shared_ptr<dogen::text::transforms::helper_transform>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::text::transforms {

repository::repository(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& helper_transforms)
    : helper_transforms_(helper_transforms) { }

void repository::swap(repository& other) noexcept {
    using std::swap;
    swap(helper_transforms_, other.helper_transforms_);
}

bool repository::operator==(const repository& rhs) const {
    return helper_transforms_ == rhs.helper_transforms_;
}

repository& repository::operator=(repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& repository::helper_transforms() const {
    return helper_transforms_;
}

std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& repository::helper_transforms() {
    return helper_transforms_;
}

void repository::helper_transforms(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& v) {
    helper_transforms_ = v;
}

void repository::helper_transforms(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >&& v) {
    helper_transforms_ = std::move(v);
}

}
