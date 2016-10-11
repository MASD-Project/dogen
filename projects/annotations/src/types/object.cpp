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
#include "dogen/annotations/types/object.hpp"

namespace dogen {
namespace annotations {

annotation::annotation(const std::unordered_map<std::string, dogen::annotations::field_instance>& fields)
    : fields_(fields) { }

void annotation::swap(annotation& other) noexcept {
    using std::swap;
    swap(fields_, other.fields_);
}

bool annotation::operator==(const annotation& rhs) const {
    return fields_ == rhs.fields_;
}

annotation& annotation::operator=(annotation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::annotations::field_instance>& annotation::fields() const {
    return fields_;
}

std::unordered_map<std::string, dogen::annotations::field_instance>& annotation::fields() {
    return fields_;
}

void annotation::fields(const std::unordered_map<std::string, dogen::annotations::field_instance>& v) {
    fields_ = v;
}

void annotation::fields(const std::unordered_map<std::string, dogen::annotations::field_instance>&& v) {
    fields_ = std::move(v);
}

} }
