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
#include "dogen/quilt.csharp/types/formatters/context.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

context::context(const dogen::quilt::csharp::formattables::element_properties& element_properties)
    : element_properties_(element_properties) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(element_properties_, other.element_properties_);
}

bool context::operator==(const context& rhs) const {
    return element_properties_ == rhs.element_properties_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::quilt::csharp::formattables::element_properties& context::element_properties() const {
    return element_properties_;
}

dogen::quilt::csharp::formattables::element_properties& context::element_properties() {
    return element_properties_;
}

void context::element_properties(const dogen::quilt::csharp::formattables::element_properties& v) {
    element_properties_ = v;
}

void context::element_properties(const dogen::quilt::csharp::formattables::element_properties&& v) {
    element_properties_ = std::move(v);
}

} } } }
