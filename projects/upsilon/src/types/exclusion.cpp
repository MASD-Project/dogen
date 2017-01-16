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
#include "dogen/upsilon/types/exclusion.hpp"

namespace dogen {
namespace upsilon {

exclusion::exclusion(const std::string& type_name)
    : type_name_(type_name) { }

void exclusion::swap(exclusion& other) noexcept {
    using std::swap;
    swap(type_name_, other.type_name_);
}

bool exclusion::operator==(const exclusion& rhs) const {
    return type_name_ == rhs.type_name_;
}

exclusion& exclusion::operator=(exclusion other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& exclusion::type_name() const {
    return type_name_;
}

std::string& exclusion::type_name() {
    return type_name_;
}

void exclusion::type_name(const std::string& v) {
    type_name_ = v;
}

void exclusion::type_name(const std::string&& v) {
    type_name_ = std::move(v);
}

} }
