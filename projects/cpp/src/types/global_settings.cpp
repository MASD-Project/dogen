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
#include "dogen/cpp/types/global_settings.hpp"

namespace dogen {
namespace cpp {

global_settings::global_settings(
    const dogen::cpp::facet_settings& facet_settings,
    const dogen::cpp::cpp_settings& cpp_settings,
    const dogen::formatters::general_settings& general_settings)
    : facet_settings_(facet_settings),
      cpp_settings_(cpp_settings),
      general_settings_(general_settings) { }

void global_settings::swap(global_settings& other) noexcept {
    using std::swap;
    swap(facet_settings_, other.facet_settings_);
    swap(cpp_settings_, other.cpp_settings_);
    swap(general_settings_, other.general_settings_);
}

bool global_settings::operator==(const global_settings& rhs) const {
    return facet_settings_ == rhs.facet_settings_ &&
        cpp_settings_ == rhs.cpp_settings_ &&
        general_settings_ == rhs.general_settings_;
}

global_settings& global_settings::operator=(global_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::cpp::facet_settings& global_settings::facet_settings() const {
    return facet_settings_;
}

dogen::cpp::facet_settings& global_settings::facet_settings() {
    return facet_settings_;
}

void global_settings::facet_settings(const dogen::cpp::facet_settings& v) {
    facet_settings_ = v;
}

void global_settings::facet_settings(const dogen::cpp::facet_settings&& v) {
    facet_settings_ = std::move(v);
}

const dogen::cpp::cpp_settings& global_settings::cpp_settings() const {
    return cpp_settings_;
}

dogen::cpp::cpp_settings& global_settings::cpp_settings() {
    return cpp_settings_;
}

void global_settings::cpp_settings(const dogen::cpp::cpp_settings& v) {
    cpp_settings_ = v;
}

void global_settings::cpp_settings(const dogen::cpp::cpp_settings&& v) {
    cpp_settings_ = std::move(v);
}

const dogen::formatters::general_settings& global_settings::general_settings() const {
    return general_settings_;
}

dogen::formatters::general_settings& global_settings::general_settings() {
    return general_settings_;
}

void global_settings::general_settings(const dogen::formatters::general_settings& v) {
    general_settings_ = v;
}

void global_settings::general_settings(const dogen::formatters::general_settings&& v) {
    general_settings_ = std::move(v);
}

} }