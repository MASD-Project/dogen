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
#include "dogen.stitch/types/properties.hpp"

namespace dogen {
namespace stitch {

properties::properties(properties&& rhs)
    : decoration_properties_(std::move(rhs.decoration_properties_)),
      stitching_properties_(std::move(rhs.stitching_properties_)) { }

properties::properties(
    const boost::optional<dogen::formatting::decoration_properties>& decoration_properties,
    const dogen::stitch::stitching_properties& stitching_properties)
    : decoration_properties_(decoration_properties),
      stitching_properties_(stitching_properties) { }

void properties::swap(properties& other) noexcept {
    using std::swap;
    swap(decoration_properties_, other.decoration_properties_);
    swap(stitching_properties_, other.stitching_properties_);
}

bool properties::operator==(const properties& rhs) const {
    return decoration_properties_ == rhs.decoration_properties_ &&
        stitching_properties_ == rhs.stitching_properties_;
}

properties& properties::operator=(properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatting::decoration_properties>& properties::decoration_properties() const {
    return decoration_properties_;
}

boost::optional<dogen::formatting::decoration_properties>& properties::decoration_properties() {
    return decoration_properties_;
}

void properties::decoration_properties(const boost::optional<dogen::formatting::decoration_properties>& v) {
    decoration_properties_ = v;
}

void properties::decoration_properties(const boost::optional<dogen::formatting::decoration_properties>&& v) {
    decoration_properties_ = std::move(v);
}

const dogen::stitch::stitching_properties& properties::stitching_properties() const {
    return stitching_properties_;
}

dogen::stitch::stitching_properties& properties::stitching_properties() {
    return stitching_properties_;
}

void properties::stitching_properties(const dogen::stitch::stitching_properties& v) {
    stitching_properties_ = v;
}

void properties::stitching_properties(const dogen::stitch::stitching_properties&& v) {
    stitching_properties_ = std::move(v);
}

} }
