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
#include "dogen.physical/types/entities/element_model.hpp"

namespace dogen::physical::entities {

element_model::element_model(const std::unordered_map<std::string, dogen::physical::entities::element>& elements)
    : elements_(elements) { }

void element_model::swap(element_model& other) noexcept {
    using std::swap;
    swap(elements_, other.elements_);
}

bool element_model::operator==(const element_model& rhs) const {
    return elements_ == rhs.elements_;
}

element_model& element_model::operator=(element_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::physical::entities::element>& element_model::elements() const {
    return elements_;
}

std::unordered_map<std::string, dogen::physical::entities::element>& element_model::elements() {
    return elements_;
}

void element_model::elements(const std::unordered_map<std::string, dogen::physical::entities::element>& v) {
    elements_ = v;
}

void element_model::elements(const std::unordered_map<std::string, dogen::physical::entities::element>&& v) {
    elements_ = std::move(v);
}

}
