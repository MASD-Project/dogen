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
#include "dogen.text/types/transforms/registrar.hpp"

namespace dogen::text::transforms {

registrar::registrar(const dogen::text::transforms::repository& repository_)
    : repository__(repository_) { }

void registrar::swap(registrar& other) noexcept {
    using std::swap;
    swap(repository__, other.repository__);
}

bool registrar::operator==(const registrar& rhs) const {
    return repository__ == rhs.repository__;
}

registrar& registrar::operator=(registrar other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::text::transforms::repository& registrar::repository_() const {
    return repository__;
}

dogen::text::transforms::repository& registrar::repository_() {
    return repository__;
}

void registrar::repository_(const dogen::text::transforms::repository& v) {
    repository__ = v;
}

void registrar::repository_(const dogen::text::transforms::repository&& v) {
    repository__ = std::move(v);
}

}
