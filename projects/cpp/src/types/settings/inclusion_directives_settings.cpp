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
    : requires_inclusion_directives_(static_cast<bool>(0)) { }

inclusion_directives_settings::inclusion_directives_settings(
    const std::unordered_map<std::string, std::string>& inclusion_directives,
    const bool requires_inclusion_directives)
    : inclusion_directives_(inclusion_directives),
      requires_inclusion_directives_(requires_inclusion_directives) { }

void inclusion_directives_settings::swap(inclusion_directives_settings& other) noexcept {
    using std::swap;
    swap(inclusion_directives_, other.inclusion_directives_);
    swap(requires_inclusion_directives_, other.requires_inclusion_directives_);
}

bool inclusion_directives_settings::operator==(const inclusion_directives_settings& rhs) const {
    return inclusion_directives_ == rhs.inclusion_directives_ &&
        requires_inclusion_directives_ == rhs.requires_inclusion_directives_;
}

inclusion_directives_settings& inclusion_directives_settings::operator=(inclusion_directives_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::string>& inclusion_directives_settings::inclusion_directives() const {
    return inclusion_directives_;
}

std::unordered_map<std::string, std::string>& inclusion_directives_settings::inclusion_directives() {
    return inclusion_directives_;
}

void inclusion_directives_settings::inclusion_directives(const std::unordered_map<std::string, std::string>& v) {
    inclusion_directives_ = v;
}

void inclusion_directives_settings::inclusion_directives(const std::unordered_map<std::string, std::string>&& v) {
    inclusion_directives_ = std::move(v);
}

bool inclusion_directives_settings::requires_inclusion_directives() const {
    return requires_inclusion_directives_;
}

void inclusion_directives_settings::requires_inclusion_directives(const bool v) {
    requires_inclusion_directives_ = v;
}

} } }