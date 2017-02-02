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
#include "dogen/quilt.cpp/types/formattables/inclusion_directive_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

inclusion_directive_configuration::inclusion_directive_configuration()
    : inclusion_required_(static_cast<bool>(0)) { }

inclusion_directive_configuration::inclusion_directive_configuration(
    const bool inclusion_required,
    const std::string& primary_directive,
    const std::list<std::string>& secondary_directives)
    : inclusion_required_(inclusion_required),
      primary_directive_(primary_directive),
      secondary_directives_(secondary_directives) { }

void inclusion_directive_configuration::swap(inclusion_directive_configuration& other) noexcept {
    using std::swap;
    swap(inclusion_required_, other.inclusion_required_);
    swap(primary_directive_, other.primary_directive_);
    swap(secondary_directives_, other.secondary_directives_);
}

bool inclusion_directive_configuration::operator==(const inclusion_directive_configuration& rhs) const {
    return inclusion_required_ == rhs.inclusion_required_ &&
        primary_directive_ == rhs.primary_directive_ &&
        secondary_directives_ == rhs.secondary_directives_;
}

inclusion_directive_configuration& inclusion_directive_configuration::operator=(inclusion_directive_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool inclusion_directive_configuration::inclusion_required() const {
    return inclusion_required_;
}

void inclusion_directive_configuration::inclusion_required(const bool v) {
    inclusion_required_ = v;
}

const std::string& inclusion_directive_configuration::primary_directive() const {
    return primary_directive_;
}

std::string& inclusion_directive_configuration::primary_directive() {
    return primary_directive_;
}

void inclusion_directive_configuration::primary_directive(const std::string& v) {
    primary_directive_ = v;
}

void inclusion_directive_configuration::primary_directive(const std::string&& v) {
    primary_directive_ = std::move(v);
}

const std::list<std::string>& inclusion_directive_configuration::secondary_directives() const {
    return secondary_directives_;
}

std::list<std::string>& inclusion_directive_configuration::secondary_directives() {
    return secondary_directives_;
}

void inclusion_directive_configuration::secondary_directives(const std::list<std::string>& v) {
    secondary_directives_ = v;
}

void inclusion_directive_configuration::secondary_directives(const std::list<std::string>&& v) {
    secondary_directives_ = std::move(v);
}

} } } }
