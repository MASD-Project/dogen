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
#include "dogen.logical/types/entities/physical/hard_coded_relation.hpp"

namespace dogen::logical::entities::physical {

hard_coded_relation::hard_coded_relation(const std::string& value)
    : value_(value) { }

void hard_coded_relation::swap(hard_coded_relation& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

bool hard_coded_relation::operator==(const hard_coded_relation& rhs) const {
    return value_ == rhs.value_;
}

hard_coded_relation& hard_coded_relation::operator=(hard_coded_relation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& hard_coded_relation::value() const {
    return value_;
}

std::string& hard_coded_relation::value() {
    return value_;
}

void hard_coded_relation::value(const std::string& v) {
    value_ = v;
}

void hard_coded_relation::value(const std::string&& v) {
    value_ = std::move(v);
}

}
