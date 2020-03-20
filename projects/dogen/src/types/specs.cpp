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

specs::specs(const std::list<dogen::spec_category>& categories)
    : categories_(categories) { }

void specs::swap(specs& other) noexcept {
    using std::swap;
    swap(categories_, other.categories_);
}

bool specs::operator==(const specs& rhs) const {
    return categories_ == rhs.categories_;
}

specs& specs::operator=(specs other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::spec_category>& specs::categories() const {
    return categories_;
}

std::list<dogen::spec_category>& specs::categories() {
    return categories_;
}

void specs::categories(const std::list<dogen::spec_category>& v) {
    categories_ = v;
}

void specs::categories(const std::list<dogen::spec_category>&& v) {
    categories_ = std::move(v);
}

}
