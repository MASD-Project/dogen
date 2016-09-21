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
#include "dogen/stitch/types/properties.hpp"

namespace dogen {
namespace stitch {

properties::properties(properties&& rhs)
    : decoration_configuration_(std::move(rhs.decoration_configuration_)),
      stitching_settings_(std::move(rhs.stitching_settings_)) { }

properties::properties(
    const boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration,
    const dogen::stitch::stitching_settings& stitching_settings)
    : decoration_configuration_(decoration_configuration),
      stitching_settings_(stitching_settings) { }

void properties::swap(properties& other) noexcept {
    using std::swap;
    swap(decoration_configuration_, other.decoration_configuration_);
    swap(stitching_settings_, other.stitching_settings_);
}

bool properties::operator==(const properties& rhs) const {
    return decoration_configuration_ == rhs.decoration_configuration_ &&
        stitching_settings_ == rhs.stitching_settings_;
}

properties& properties::operator=(properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::decoration_configuration>& properties::decoration_configuration() const {
    return decoration_configuration_;
}

boost::optional<dogen::formatters::decoration_configuration>& properties::decoration_configuration() {
    return decoration_configuration_;
}

void properties::decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>& v) {
    decoration_configuration_ = v;
}

void properties::decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>&& v) {
    decoration_configuration_ = std::move(v);
}

const dogen::stitch::stitching_settings& properties::stitching_settings() const {
    return stitching_settings_;
}

dogen::stitch::stitching_settings& properties::stitching_settings() {
    return stitching_settings_;
}

void properties::stitching_settings(const dogen::stitch::stitching_settings& v) {
    stitching_settings_ = v;
}

void properties::stitching_settings(const dogen::stitch::stitching_settings&& v) {
    stitching_settings_ = std::move(v);
}

} }
