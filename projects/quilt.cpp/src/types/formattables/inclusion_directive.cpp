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
#include "dogen/quilt.cpp/types/formattables/inclusion_directive.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

inclusion_directive::inclusion_directive(
    const std::string& principal,
    const std::list<std::string>& auxiliary)
    : principal_(principal),
      auxiliary_(auxiliary) { }

void inclusion_directive::swap(inclusion_directive& other) noexcept {
    using std::swap;
    swap(principal_, other.principal_);
    swap(auxiliary_, other.auxiliary_);
}

bool inclusion_directive::operator==(const inclusion_directive& rhs) const {
    return principal_ == rhs.principal_ &&
        auxiliary_ == rhs.auxiliary_;
}

inclusion_directive& inclusion_directive::operator=(inclusion_directive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& inclusion_directive::principal() const {
    return principal_;
}

std::string& inclusion_directive::principal() {
    return principal_;
}

void inclusion_directive::principal(const std::string& v) {
    principal_ = v;
}

void inclusion_directive::principal(const std::string&& v) {
    principal_ = std::move(v);
}

const std::list<std::string>& inclusion_directive::auxiliary() const {
    return auxiliary_;
}

std::list<std::string>& inclusion_directive::auxiliary() {
    return auxiliary_;
}

void inclusion_directive::auxiliary(const std::list<std::string>& v) {
    auxiliary_ = v;
}

void inclusion_directive::auxiliary(const std::list<std::string>&& v) {
    auxiliary_ = std::move(v);
}

} } } }
