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
#include "dogen/cpp/types/class_head.hpp"

namespace dogen {
namespace cpp {

class_head::class_head()
    : key_(static_cast<dogen::cpp::class_key_types>(0)),
      is_final_(static_cast<bool>(0)) { }

class_head::class_head(
    const dogen::cpp::class_key_types& key,
    const dogen::cpp::qualified_id& name,
    const std::list<dogen::cpp::base_specifier>& base_specifier_list,
    const bool is_final)
    : key_(key),
      name_(name),
      base_specifier_list_(base_specifier_list),
      is_final_(is_final) { }

void class_head::swap(class_head& other) noexcept {
    using std::swap;
    swap(key_, other.key_);
    swap(name_, other.name_);
    swap(base_specifier_list_, other.base_specifier_list_);
    swap(is_final_, other.is_final_);
}

bool class_head::operator==(const class_head& rhs) const {
    return key_ == rhs.key_ &&
        name_ == rhs.name_ &&
        base_specifier_list_ == rhs.base_specifier_list_ &&
        is_final_ == rhs.is_final_;
}

class_head& class_head::operator=(class_head other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::cpp::class_key_types class_head::key() const {
    return key_;
}

void class_head::key(const dogen::cpp::class_key_types& v) {
    key_ = v;
}

const dogen::cpp::qualified_id& class_head::name() const {
    return name_;
}

dogen::cpp::qualified_id& class_head::name() {
    return name_;
}

void class_head::name(const dogen::cpp::qualified_id& v) {
    name_ = v;
}

void class_head::name(const dogen::cpp::qualified_id&& v) {
    name_ = std::move(v);
}

const std::list<dogen::cpp::base_specifier>& class_head::base_specifier_list() const {
    return base_specifier_list_;
}

std::list<dogen::cpp::base_specifier>& class_head::base_specifier_list() {
    return base_specifier_list_;
}

void class_head::base_specifier_list(const std::list<dogen::cpp::base_specifier>& v) {
    base_specifier_list_ = v;
}

void class_head::base_specifier_list(const std::list<dogen::cpp::base_specifier>&& v) {
    base_specifier_list_ = std::move(v);
}

bool class_head::is_final() const {
    return is_final_;
}

void class_head::is_final(const bool v) {
    is_final_ = v;
}

} }