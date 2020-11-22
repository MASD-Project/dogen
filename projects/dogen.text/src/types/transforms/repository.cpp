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

repository::repository(const std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& helpers_by_family)
    : helpers_by_family_(helpers_by_family) { }

void repository::swap(repository& other) noexcept {
    using std::swap;
    swap(helpers_by_family_, other.helpers_by_family_);
}

bool repository::operator==(const repository& rhs) const {
    return helpers_by_family_ == rhs.helpers_by_family_;
}

repository& repository::operator=(repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& repository::helpers_by_family() const {
    return helpers_by_family_;
}

std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& repository::helpers_by_family() {
    return helpers_by_family_;
}

void repository::helpers_by_family(const std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >& v) {
    helpers_by_family_ = v;
}

void repository::helpers_by_family(const std::unordered_map<std::string, std::unordered_map<dogen::identification::entities::physical_meta_id, std::list<std::shared_ptr<dogen::text::transforms::helper_transform> > > >&& v) {
    helpers_by_family_ = std::move(v);
}

}
