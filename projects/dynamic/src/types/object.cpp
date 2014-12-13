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
#include "dogen/dynamic/types/object.hpp"

namespace dogen {
namespace dynamic {

object::object(const std::list<dogen::dynamic::field>& fields)
    : fields_(fields) { }

void object::swap(object& other) noexcept {
    using std::swap;
    swap(fields_, other.fields_);
}

bool object::operator==(const object& rhs) const {
    return fields_ == rhs.fields_;
}

object& object::operator=(object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::dynamic::field>& object::fields() const {
    return fields_;
}

std::list<dogen::dynamic::field>& object::fields() {
    return fields_;
}

void object::fields(const std::list<dogen::dynamic::field>& v) {
    fields_ = v;
}

void object::fields(const std::list<dogen::dynamic::field>&& v) {
    fields_ = std::move(v);
}

} }