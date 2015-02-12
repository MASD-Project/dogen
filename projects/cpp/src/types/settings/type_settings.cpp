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
#include "dogen/cpp/types/settings/type_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

type_settings::type_settings()
    : family_type_(static_cast<dogen::cpp::formattables::family_types>(0)),
      requires_manual_default_constructor_(static_cast<bool>(0)),
      requires_manual_move_constructor_(static_cast<bool>(0)),
      inclusion_required_(static_cast<bool>(0)) { }

type_settings::type_settings(
    const dogen::cpp::formattables::family_types& family_type,
    const bool requires_manual_default_constructor,
    const bool requires_manual_move_constructor,
    const bool inclusion_required)
    : family_type_(family_type),
      requires_manual_default_constructor_(requires_manual_default_constructor),
      requires_manual_move_constructor_(requires_manual_move_constructor),
      inclusion_required_(inclusion_required) { }

void type_settings::swap(type_settings& other) noexcept {
    using std::swap;
    swap(family_type_, other.family_type_);
    swap(requires_manual_default_constructor_, other.requires_manual_default_constructor_);
    swap(requires_manual_move_constructor_, other.requires_manual_move_constructor_);
    swap(inclusion_required_, other.inclusion_required_);
}

bool type_settings::operator==(const type_settings& rhs) const {
    return family_type_ == rhs.family_type_ &&
        requires_manual_default_constructor_ == rhs.requires_manual_default_constructor_ &&
        requires_manual_move_constructor_ == rhs.requires_manual_move_constructor_ &&
        inclusion_required_ == rhs.inclusion_required_;
}

type_settings& type_settings::operator=(type_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::cpp::formattables::family_types type_settings::family_type() const {
    return family_type_;
}

void type_settings::family_type(const dogen::cpp::formattables::family_types& v) {
    family_type_ = v;
}

bool type_settings::requires_manual_default_constructor() const {
    return requires_manual_default_constructor_;
}

void type_settings::requires_manual_default_constructor(const bool v) {
    requires_manual_default_constructor_ = v;
}

bool type_settings::requires_manual_move_constructor() const {
    return requires_manual_move_constructor_;
}

void type_settings::requires_manual_move_constructor(const bool v) {
    requires_manual_move_constructor_ = v;
}

bool type_settings::inclusion_required() const {
    return inclusion_required_;
}

void type_settings::inclusion_required(const bool v) {
    inclusion_required_ = v;
}

} } }