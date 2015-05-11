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
#include "dogen/cpp/types/settings/inclusion_directives_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

inclusion_directives_settings::inclusion_directives_settings()
    : inclusion_required_(static_cast<bool>(0)) { }

inclusion_directives_settings::inclusion_directives_settings(
    const bool inclusion_required,
    const std::unordered_map<std::string, dogen::cpp::settings::inclusion_directive_settings>& inclusion_directive_settings)
    : inclusion_required_(inclusion_required),
      inclusion_directive_settings_(inclusion_directive_settings) { }

void inclusion_directives_settings::swap(inclusion_directives_settings& other) noexcept {
    using std::swap;
    swap(inclusion_required_, other.inclusion_required_);
    swap(inclusion_directive_settings_, other.inclusion_directive_settings_);
}

bool inclusion_directives_settings::operator==(const inclusion_directives_settings& rhs) const {
    return inclusion_required_ == rhs.inclusion_required_ &&
        inclusion_directive_settings_ == rhs.inclusion_directive_settings_;
}

inclusion_directives_settings& inclusion_directives_settings::operator=(inclusion_directives_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool inclusion_directives_settings::inclusion_required() const {
    return inclusion_required_;
}

void inclusion_directives_settings::inclusion_required(const bool v) {
    inclusion_required_ = v;
}

const std::unordered_map<std::string, dogen::cpp::settings::inclusion_directive_settings>& inclusion_directives_settings::inclusion_directive_settings() const {
    return inclusion_directive_settings_;
}

std::unordered_map<std::string, dogen::cpp::settings::inclusion_directive_settings>& inclusion_directives_settings::inclusion_directive_settings() {
    return inclusion_directive_settings_;
}

void inclusion_directives_settings::inclusion_directive_settings(const std::unordered_map<std::string, dogen::cpp::settings::inclusion_directive_settings>& v) {
    inclusion_directive_settings_ = v;
}

void inclusion_directives_settings::inclusion_directive_settings(const std::unordered_map<std::string, dogen::cpp::settings::inclusion_directive_settings>&& v) {
    inclusion_directive_settings_ = std::move(v);
}

} } }