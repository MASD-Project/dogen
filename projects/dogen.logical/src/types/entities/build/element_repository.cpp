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
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.logical/types/entities/build/element_repository.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::build::cmakelists>& lhs,
const boost::shared_ptr<dogen::logical::entities::build::cmakelists>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::entities::build {

element_repository::element_repository(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::build::cmakelists> >& cmakelists)
    : cmakelists_(cmakelists) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(cmakelists_, other.cmakelists_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return cmakelists_ == rhs.cmakelists_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::build::cmakelists> >& element_repository::cmakelists() const {
    return cmakelists_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::build::cmakelists> >& element_repository::cmakelists() {
    return cmakelists_;
}

void element_repository::cmakelists(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::build::cmakelists> >& v) {
    cmakelists_ = v;
}

void element_repository::cmakelists(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::build::cmakelists> >&& v) {
    cmakelists_ = std::move(v);
}

}
