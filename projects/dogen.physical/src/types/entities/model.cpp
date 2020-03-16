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
#include "dogen.physical/types/entities/model.hpp"

namespace dogen::physical::entities {

model::model(const std::unordered_map<std::string, dogen::physical::entities::kernel>& kernels)
    : kernels_(kernels) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(kernels_, other.kernels_);
}

bool model::operator==(const model& rhs) const {
    return kernels_ == rhs.kernels_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::physical::entities::kernel>& model::kernels() const {
    return kernels_;
}

std::unordered_map<std::string, dogen::physical::entities::kernel>& model::kernels() {
    return kernels_;
}

void model::kernels(const std::unordered_map<std::string, dogen::physical::entities::kernel>& v) {
    kernels_ = v;
}

void model::kernels(const std::unordered_map<std::string, dogen::physical::entities::kernel>&& v) {
    kernels_ = std::move(v);
}

}
