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
#include "dogen/cpp/types/member_specification.hpp"

namespace dogen {
namespace cpp {

member_specification::member_specification()
    : access_(static_cast<dogen::cpp::access_specifier_types>(0)) { }

member_specification::member_specification(
    const dogen::cpp::access_specifier_types& access,
    const std::list<dogen::cpp::member_declaration>& member_declaration_list)
    : access_(access),
      member_declaration_list_(member_declaration_list) { }

void member_specification::swap(member_specification& other) noexcept {
    using std::swap;
    swap(access_, other.access_);
    swap(member_declaration_list_, other.member_declaration_list_);
}

bool member_specification::operator==(const member_specification& rhs) const {
    return access_ == rhs.access_ &&
        member_declaration_list_ == rhs.member_declaration_list_;
}

member_specification& member_specification::operator=(member_specification other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::cpp::access_specifier_types member_specification::access() const {
    return access_;
}

void member_specification::access(const dogen::cpp::access_specifier_types& v) {
    access_ = v;
}

const std::list<dogen::cpp::member_declaration>& member_specification::member_declaration_list() const {
    return member_declaration_list_;
}

std::list<dogen::cpp::member_declaration>& member_specification::member_declaration_list() {
    return member_declaration_list_;
}

void member_specification::member_declaration_list(const std::list<dogen::cpp::member_declaration>& v) {
    member_declaration_list_ = v;
}

void member_specification::member_declaration_list(const std::list<dogen::cpp::member_declaration>&& v) {
    member_declaration_list_ = std::move(v);
}

} }