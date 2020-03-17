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
#include "dogen.physical/types/entities/operation.hpp"

namespace dogen::physical::entities {

operation::operation()
    : type_(static_cast<dogen::physical::entities::operation_type>(0)),
      reason_(static_cast<dogen::physical::entities::operation_reason>(0)) { }

operation::operation(
    const dogen::physical::entities::operation_type type,
    const dogen::physical::entities::operation_reason reason)
    : type_(type),
      reason_(reason) { }

void operation::swap(operation& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(reason_, other.reason_);
}

bool operation::operator==(const operation& rhs) const {
    return type_ == rhs.type_ &&
        reason_ == rhs.reason_;
}

operation& operation::operator=(operation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::physical::entities::operation_type operation::type() const {
    return type_;
}

void operation::type(const dogen::physical::entities::operation_type v) {
    type_ = v;
}

dogen::physical::entities::operation_reason operation::reason() const {
    return reason_;
}

void operation::reason(const dogen::physical::entities::operation_reason v) {
    reason_ = v;
}

}
