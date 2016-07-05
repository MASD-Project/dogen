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
#include "dogen/stitch/types/settings_bundle.hpp"

namespace dogen {
namespace stitch {

settings_bundle::settings_bundle(settings_bundle&& rhs)
    : file_properties_(std::move(rhs.file_properties_)),
      stitching_settings_(std::move(rhs.stitching_settings_)) { }

settings_bundle::settings_bundle(
    const boost::optional<dogen::formatters::file_properties>& file_properties,
    const dogen::stitch::stitching_settings& stitching_settings)
    : file_properties_(file_properties),
      stitching_settings_(stitching_settings) { }

void settings_bundle::swap(settings_bundle& other) noexcept {
    using std::swap;
    swap(file_properties_, other.file_properties_);
    swap(stitching_settings_, other.stitching_settings_);
}

bool settings_bundle::operator==(const settings_bundle& rhs) const {
    return file_properties_ == rhs.file_properties_ &&
        stitching_settings_ == rhs.stitching_settings_;
}

settings_bundle& settings_bundle::operator=(settings_bundle other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::file_properties>& settings_bundle::file_properties() const {
    return file_properties_;
}

boost::optional<dogen::formatters::file_properties>& settings_bundle::file_properties() {
    return file_properties_;
}

void settings_bundle::file_properties(const boost::optional<dogen::formatters::file_properties>& v) {
    file_properties_ = v;
}

void settings_bundle::file_properties(const boost::optional<dogen::formatters::file_properties>&& v) {
    file_properties_ = std::move(v);
}

const dogen::stitch::stitching_settings& settings_bundle::stitching_settings() const {
    return stitching_settings_;
}

dogen::stitch::stitching_settings& settings_bundle::stitching_settings() {
    return stitching_settings_;
}

void settings_bundle::stitching_settings(const dogen::stitch::stitching_settings& v) {
    stitching_settings_ = v;
}

void settings_bundle::stitching_settings(const dogen::stitch::stitching_settings&& v) {
    stitching_settings_ = std::move(v);
}

} }
