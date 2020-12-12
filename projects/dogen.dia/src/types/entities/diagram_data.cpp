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
#include "dogen.dia/types/entities/diagram_data.hpp"

namespace dogen::dia::entities {

diagram_data::diagram_data(const std::vector<dogen::dia::entities::attribute>& attributes)
    : attributes_(attributes) { }

void diagram_data::swap(diagram_data& other) noexcept {
    using std::swap;
    swap(attributes_, other.attributes_);
}

bool diagram_data::operator==(const diagram_data& rhs) const {
    return attributes_ == rhs.attributes_;
}

diagram_data& diagram_data::operator=(diagram_data other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<dogen::dia::entities::attribute>& diagram_data::attributes() const {
    return attributes_;
}

std::vector<dogen::dia::entities::attribute>& diagram_data::attributes() {
    return attributes_;
}

void diagram_data::attributes(const std::vector<dogen::dia::entities::attribute>& v) {
    attributes_ = v;
}

void diagram_data::attributes(const std::vector<dogen::dia::entities::attribute>&& v) {
    attributes_ = std::move(v);
}

}
