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
#include "dogen/cpp/types/entity.hpp"
#include "dogen/cpp/types/scope.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::entity>& lhs,
const boost::shared_ptr<dogen::cpp::entity>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace cpp {

scope::scope()
    : type_(static_cast<dogen::cpp::scope_types>(0)) { }

scope::scope(
    const dogen::cpp::scope_types& type,
    const std::list<dogen::cpp::scope>& inner_scopes,
    const std::list<boost::shared_ptr<dogen::cpp::entity> >& entities)
    : type_(type),
      inner_scopes_(inner_scopes),
      entities_(entities) { }

void scope::swap(scope& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(inner_scopes_, other.inner_scopes_);
    swap(entities_, other.entities_);
}

bool scope::operator==(const scope& rhs) const {
    return type_ == rhs.type_ &&
        inner_scopes_ == rhs.inner_scopes_ &&
        entities_ == rhs.entities_;
}

scope& scope::operator=(scope other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::cpp::scope_types scope::type() const {
    return type_;
}

void scope::type(const dogen::cpp::scope_types& v) {
    type_ = v;
}

const std::list<dogen::cpp::scope>& scope::inner_scopes() const {
    return inner_scopes_;
}

std::list<dogen::cpp::scope>& scope::inner_scopes() {
    return inner_scopes_;
}

void scope::inner_scopes(const std::list<dogen::cpp::scope>& v) {
    inner_scopes_ = v;
}

void scope::inner_scopes(const std::list<dogen::cpp::scope>&& v) {
    inner_scopes_ = std::move(v);
}

const std::list<boost::shared_ptr<dogen::cpp::entity> >& scope::entities() const {
    return entities_;
}

std::list<boost::shared_ptr<dogen::cpp::entity> >& scope::entities() {
    return entities_;
}

void scope::entities(const std::list<boost::shared_ptr<dogen::cpp::entity> >& v) {
    entities_ = v;
}

void scope::entities(const std::list<boost::shared_ptr<dogen::cpp::entity> >&& v) {
    entities_ = std::move(v);
}

} }