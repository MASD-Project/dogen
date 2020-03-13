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
#include "dogen/types/specs.hpp"

namespace dogen {

specs::specs(const std::list<dogen::spec_group>& groups)
    : groups_(groups) { }

void specs::swap(specs& other) noexcept {
    using std::swap;
    swap(groups_, other.groups_);
}

bool specs::operator==(const specs& rhs) const {
    return groups_ == rhs.groups_;
}

specs& specs::operator=(specs other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::spec_group>& specs::groups() const {
    return groups_;
}

std::list<dogen::spec_group>& specs::groups() {
    return groups_;
}

void specs::groups(const std::list<dogen::spec_group>& v) {
    groups_ = v;
}

void specs::groups(const std::list<dogen::spec_group>&& v) {
    groups_ = std::move(v);
}

}
