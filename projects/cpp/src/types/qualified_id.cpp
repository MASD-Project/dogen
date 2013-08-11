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
#include "dogen/cpp/types/qualified_id.hpp"

namespace dogen {
namespace cpp {

qualified_id::qualified_id()
    : start_at_global_scope_(static_cast<bool>(0)) { }

qualified_id::qualified_id(
    const std::string& unqualified_id,
    const std::list<std::string>& nested_name_specifier,
    const bool start_at_global_scope)
    : unqualified_id_(unqualified_id),
      nested_name_specifier_(nested_name_specifier),
      start_at_global_scope_(start_at_global_scope) { }

void qualified_id::swap(qualified_id& other) noexcept {
    using std::swap;
    swap(unqualified_id_, other.unqualified_id_);
    swap(nested_name_specifier_, other.nested_name_specifier_);
    swap(start_at_global_scope_, other.start_at_global_scope_);
}

bool qualified_id::operator==(const qualified_id& rhs) const {
    return unqualified_id_ == rhs.unqualified_id_ &&
        nested_name_specifier_ == rhs.nested_name_specifier_ &&
        start_at_global_scope_ == rhs.start_at_global_scope_;
}

qualified_id& qualified_id::operator=(qualified_id other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& qualified_id::unqualified_id() const {
    return unqualified_id_;
}

std::string& qualified_id::unqualified_id() {
    return unqualified_id_;
}

void qualified_id::unqualified_id(const std::string& v) {
    unqualified_id_ = v;
}

void qualified_id::unqualified_id(const std::string&& v) {
    unqualified_id_ = std::move(v);
}

const std::list<std::string>& qualified_id::nested_name_specifier() const {
    return nested_name_specifier_;
}

std::list<std::string>& qualified_id::nested_name_specifier() {
    return nested_name_specifier_;
}

void qualified_id::nested_name_specifier(const std::list<std::string>& v) {
    nested_name_specifier_ = v;
}

void qualified_id::nested_name_specifier(const std::list<std::string>&& v) {
    nested_name_specifier_ = std::move(v);
}

bool qualified_id::start_at_global_scope() const {
    return start_at_global_scope_;
}

void qualified_id::start_at_global_scope(const bool v) {
    start_at_global_scope_ = v;
}

} }