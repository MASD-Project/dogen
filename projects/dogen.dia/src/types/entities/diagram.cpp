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
#include "dogen.dia/types/entities/diagram.hpp"

namespace dogen::dia::entities {

diagram::diagram(
    const dogen::dia::entities::diagram_data& diagram_data,
    const std::vector<dogen::dia::entities::layer>& layers)
    : diagram_data_(diagram_data),
      layers_(layers) { }

void diagram::swap(diagram& other) noexcept {
    using std::swap;
    swap(diagram_data_, other.diagram_data_);
    swap(layers_, other.layers_);
}

bool diagram::operator==(const diagram& rhs) const {
    return diagram_data_ == rhs.diagram_data_ &&
        layers_ == rhs.layers_;
}

diagram& diagram::operator=(diagram other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::dia::entities::diagram_data& diagram::diagram_data() const {
    return diagram_data_;
}

dogen::dia::entities::diagram_data& diagram::diagram_data() {
    return diagram_data_;
}

void diagram::diagram_data(const dogen::dia::entities::diagram_data& v) {
    diagram_data_ = v;
}

void diagram::diagram_data(const dogen::dia::entities::diagram_data&& v) {
    diagram_data_ = std::move(v);
}

const std::vector<dogen::dia::entities::layer>& diagram::layers() const {
    return layers_;
}

std::vector<dogen::dia::entities::layer>& diagram::layers() {
    return layers_;
}

void diagram::layers(const std::vector<dogen::dia::entities::layer>& v) {
    layers_ = v;
}

void diagram::layers(const std::vector<dogen::dia::entities::layer>&& v) {
    layers_ = std::move(v);
}

}
