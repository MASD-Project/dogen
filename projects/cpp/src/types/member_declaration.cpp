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
#include "dogen/cpp/types/member_declaration.hpp"

namespace dogen {
namespace cpp {

member_declaration::member_declaration()
    : function_type_(static_cast<dogen::cpp::function_types>(0)),
      is_pure_(static_cast<bool>(0)),
      is_override_(static_cast<bool>(0)),
      is_default_(static_cast<bool>(0)) { }

member_declaration::member_declaration(
    const std::list<dogen::cpp::decl_specifier>& decl_specifier_seq,
    const dogen::cpp::declarator& declarator,
    const std::string& constant_initialiser,
    const dogen::cpp::function_types& function_type,
    const bool is_pure,
    const bool is_override,
    const bool is_default)
    : decl_specifier_seq_(decl_specifier_seq),
      declarator_(declarator),
      constant_initialiser_(constant_initialiser),
      function_type_(function_type),
      is_pure_(is_pure),
      is_override_(is_override),
      is_default_(is_default) { }

void member_declaration::swap(member_declaration& other) noexcept {
    using std::swap;
    swap(decl_specifier_seq_, other.decl_specifier_seq_);
    swap(declarator_, other.declarator_);
    swap(constant_initialiser_, other.constant_initialiser_);
    swap(function_type_, other.function_type_);
    swap(is_pure_, other.is_pure_);
    swap(is_override_, other.is_override_);
    swap(is_default_, other.is_default_);
}

bool member_declaration::operator==(const member_declaration& rhs) const {
    return decl_specifier_seq_ == rhs.decl_specifier_seq_ &&
        declarator_ == rhs.declarator_ &&
        constant_initialiser_ == rhs.constant_initialiser_ &&
        function_type_ == rhs.function_type_ &&
        is_pure_ == rhs.is_pure_ &&
        is_override_ == rhs.is_override_ &&
        is_default_ == rhs.is_default_;
}

member_declaration& member_declaration::operator=(member_declaration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::cpp::decl_specifier>& member_declaration::decl_specifier_seq() const {
    return decl_specifier_seq_;
}

std::list<dogen::cpp::decl_specifier>& member_declaration::decl_specifier_seq() {
    return decl_specifier_seq_;
}

void member_declaration::decl_specifier_seq(const std::list<dogen::cpp::decl_specifier>& v) {
    decl_specifier_seq_ = v;
}

void member_declaration::decl_specifier_seq(const std::list<dogen::cpp::decl_specifier>&& v) {
    decl_specifier_seq_ = std::move(v);
}

const dogen::cpp::declarator& member_declaration::declarator() const {
    return declarator_;
}

dogen::cpp::declarator& member_declaration::declarator() {
    return declarator_;
}

void member_declaration::declarator(const dogen::cpp::declarator& v) {
    declarator_ = v;
}

void member_declaration::declarator(const dogen::cpp::declarator&& v) {
    declarator_ = std::move(v);
}

const std::string& member_declaration::constant_initialiser() const {
    return constant_initialiser_;
}

std::string& member_declaration::constant_initialiser() {
    return constant_initialiser_;
}

void member_declaration::constant_initialiser(const std::string& v) {
    constant_initialiser_ = v;
}

void member_declaration::constant_initialiser(const std::string&& v) {
    constant_initialiser_ = std::move(v);
}

dogen::cpp::function_types member_declaration::function_type() const {
    return function_type_;
}

void member_declaration::function_type(const dogen::cpp::function_types& v) {
    function_type_ = v;
}

bool member_declaration::is_pure() const {
    return is_pure_;
}

void member_declaration::is_pure(const bool v) {
    is_pure_ = v;
}

bool member_declaration::is_override() const {
    return is_override_;
}

void member_declaration::is_override(const bool v) {
    is_override_ = v;
}

bool member_declaration::is_default() const {
    return is_default_;
}

void member_declaration::is_default(const bool v) {
    is_default_ = v;
}

} }