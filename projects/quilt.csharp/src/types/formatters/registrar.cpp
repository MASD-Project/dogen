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
#include "dogen/quilt.csharp/types/formatters/registrar.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

registrar::registrar(const dogen::quilt::csharp::formatters::repository& formatter_repository_)
    : formatter_repository__(formatter_repository_) { }

void registrar::swap(registrar& other) noexcept {
    using std::swap;
    swap(formatter_repository__, other.formatter_repository__);
}

bool registrar::operator==(const registrar& rhs) const {
    return formatter_repository__ == rhs.formatter_repository__;
}

registrar& registrar::operator=(registrar other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::quilt::csharp::formatters::repository& registrar::formatter_repository_() const {
    return formatter_repository__;
}

dogen::quilt::csharp::formatters::repository& registrar::formatter_repository_() {
    return formatter_repository__;
}

void registrar::formatter_repository_(const dogen::quilt::csharp::formatters::repository& v) {
    formatter_repository__ = v;
}

void registrar::formatter_repository_(const dogen::quilt::csharp::formatters::repository&& v) {
    formatter_repository__ = std::move(v);
}

} } } }
