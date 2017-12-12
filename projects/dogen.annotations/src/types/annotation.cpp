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
#include "dogen.annotations/types/value.hpp"
#include "dogen.annotations/types/annotation.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::annotations::value>& lhs,
const boost::shared_ptr<dogen::annotations::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace annotations {

annotation::annotation()
    : scope_(static_cast<dogen::annotations::scope_types>(0)) { }

annotation::annotation(
    const std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >& tagged_values,
    const dogen::annotations::scope_types scope)
    : tagged_values_(tagged_values),
      scope_(scope) { }

void annotation::swap(annotation& other) noexcept {
    using std::swap;
    swap(tagged_values_, other.tagged_values_);
    swap(scope_, other.scope_);
}

bool annotation::operator==(const annotation& rhs) const {
    return tagged_values_ == rhs.tagged_values_ &&
        scope_ == rhs.scope_;
}

annotation& annotation::operator=(annotation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >& annotation::tagged_values() const {
    return tagged_values_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >& annotation::tagged_values() {
    return tagged_values_;
}

void annotation::tagged_values(const std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >& v) {
    tagged_values_ = v;
}

void annotation::tagged_values(const std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >&& v) {
    tagged_values_ = std::move(v);
}

dogen::annotations::scope_types annotation::scope() const {
    return scope_;
}

void annotation::scope(const dogen::annotations::scope_types v) {
    scope_ = v;
}

} }
