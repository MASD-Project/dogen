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
#include "dogen/quilt.cpp/types/formattables/inclusion_directive_group.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

inclusion_directive_group::inclusion_directive_group(
    const std::string& primary_directive,
    const std::list<std::string>& secondary_directives)
    : primary_directive_(primary_directive),
      secondary_directives_(secondary_directives) { }

void inclusion_directive_group::swap(inclusion_directive_group& other) noexcept {
    using std::swap;
    swap(primary_directive_, other.primary_directive_);
    swap(secondary_directives_, other.secondary_directives_);
}

bool inclusion_directive_group::operator==(const inclusion_directive_group& rhs) const {
    return primary_directive_ == rhs.primary_directive_ &&
        secondary_directives_ == rhs.secondary_directives_;
}

inclusion_directive_group& inclusion_directive_group::operator=(inclusion_directive_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& inclusion_directive_group::primary_directive() const {
    return primary_directive_;
}

std::string& inclusion_directive_group::primary_directive() {
    return primary_directive_;
}

void inclusion_directive_group::primary_directive(const std::string& v) {
    primary_directive_ = v;
}

void inclusion_directive_group::primary_directive(const std::string&& v) {
    primary_directive_ = std::move(v);
}

const std::list<std::string>& inclusion_directive_group::secondary_directives() const {
    return secondary_directives_;
}

std::list<std::string>& inclusion_directive_group::secondary_directives() {
    return secondary_directives_;
}

void inclusion_directive_group::secondary_directives(const std::list<std::string>& v) {
    secondary_directives_ = v;
}

void inclusion_directive_group::secondary_directives(const std::list<std::string>&& v) {
    secondary_directives_ = std::move(v);
}

} } } }
