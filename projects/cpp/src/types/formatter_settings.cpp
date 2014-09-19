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
#include "dogen/cpp/types/formatter_settings.hpp"

namespace dogen {
namespace cpp {

formatter_settings::formatter_settings(
    const std::unordered_map<std::string, bool>& enabled_facets,
    const dogen::cpp::includes& includes,
    const std::string& relative_path)
    : enabled_facets_(enabled_facets),
      includes_(includes),
      relative_path_(relative_path) { }

void formatter_settings::swap(formatter_settings& other) noexcept {
    using std::swap;
    swap(enabled_facets_, other.enabled_facets_);
    swap(includes_, other.includes_);
    swap(relative_path_, other.relative_path_);
}

bool formatter_settings::operator==(const formatter_settings& rhs) const {
    return enabled_facets_ == rhs.enabled_facets_ &&
        includes_ == rhs.includes_ &&
        relative_path_ == rhs.relative_path_;
}

formatter_settings& formatter_settings::operator=(formatter_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, bool>& formatter_settings::enabled_facets() const {
    return enabled_facets_;
}

std::unordered_map<std::string, bool>& formatter_settings::enabled_facets() {
    return enabled_facets_;
}

void formatter_settings::enabled_facets(const std::unordered_map<std::string, bool>& v) {
    enabled_facets_ = v;
}

void formatter_settings::enabled_facets(const std::unordered_map<std::string, bool>&& v) {
    enabled_facets_ = std::move(v);
}

const dogen::cpp::includes& formatter_settings::includes() const {
    return includes_;
}

dogen::cpp::includes& formatter_settings::includes() {
    return includes_;
}

void formatter_settings::includes(const dogen::cpp::includes& v) {
    includes_ = v;
}

void formatter_settings::includes(const dogen::cpp::includes&& v) {
    includes_ = std::move(v);
}

const std::string& formatter_settings::relative_path() const {
    return relative_path_;
}

std::string& formatter_settings::relative_path() {
    return relative_path_;
}

void formatter_settings::relative_path(const std::string& v) {
    relative_path_ = v;
}

void formatter_settings::relative_path(const std::string&& v) {
    relative_path_ = std::move(v);
}

} }