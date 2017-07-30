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
#include "dogen/yarn/types/helpers/location_builder.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

location_builder::location_builder(const dogen::yarn::meta_model::location& location_)
    : location__(location_) { }

void location_builder::swap(location_builder& other) noexcept {
    using std::swap;
    swap(location__, other.location__);
}

bool location_builder::operator==(const location_builder& rhs) const {
    return location__ == rhs.location__;
}

location_builder& location_builder::operator=(location_builder other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::meta_model::location& location_builder::location_() const {
    return location__;
}

dogen::yarn::meta_model::location& location_builder::location_() {
    return location__;
}

void location_builder::location_(const dogen::yarn::meta_model::location& v) {
    location__ = v;
}

void location_builder::location_(const dogen::yarn::meta_model::location&& v) {
    location__ = std::move(v);
}

} } }
