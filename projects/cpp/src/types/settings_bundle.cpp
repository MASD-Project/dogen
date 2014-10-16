/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/settings_bundle.hpp"

namespace dogen {
namespace cpp {

settings_bundle::settings_bundle(
    const dogen::cpp::facet_settings& facet_settings,
    const dogen::cpp::cpp_settings& cpp_settings)
    : facet_settings_(facet_settings),
      cpp_settings_(cpp_settings) { }

void settings_bundle::swap(settings_bundle& other) noexcept {
    using std::swap;
    swap(facet_settings_, other.facet_settings_);
    swap(cpp_settings_, other.cpp_settings_);
}

bool settings_bundle::operator==(const settings_bundle& rhs) const {
    return facet_settings_ == rhs.facet_settings_ &&
        cpp_settings_ == rhs.cpp_settings_;
}

settings_bundle& settings_bundle::operator=(settings_bundle other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::cpp::facet_settings& settings_bundle::facet_settings() const {
    return facet_settings_;
}

dogen::cpp::facet_settings& settings_bundle::facet_settings() {
    return facet_settings_;
}

void settings_bundle::facet_settings(const dogen::cpp::facet_settings& v) {
    facet_settings_ = v;
}

void settings_bundle::facet_settings(const dogen::cpp::facet_settings&& v) {
    facet_settings_ = std::move(v);
}

const dogen::cpp::cpp_settings& settings_bundle::cpp_settings() const {
    return cpp_settings_;
}

dogen::cpp::cpp_settings& settings_bundle::cpp_settings() {
    return cpp_settings_;
}

void settings_bundle::cpp_settings(const dogen::cpp::cpp_settings& v) {
    cpp_settings_ = v;
}

void settings_bundle::cpp_settings(const dogen::cpp::cpp_settings&& v) {
    cpp_settings_ = std::move(v);
}

} }