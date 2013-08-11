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
#include "dogen/cpp/types/type_specifier.hpp"

namespace dogen {
namespace cpp {

type_specifier::type_specifier()
    : cv_qualifier_(static_cast<dogen::cpp::cv_qualifier_types>(0)),
      pointer_type_(static_cast<dogen::cpp::pointer_types>(0)),
      class_key_(static_cast<dogen::cpp::class_key_types>(0)) { }

type_specifier::type_specifier(
    const dogen::cpp::cv_qualifier_types& cv_qualifier,
    const dogen::cpp::pointer_types& pointer_type,
    const dogen::cpp::qualified_id& qualified_id,
    const dogen::cpp::class_key_types& class_key,
    const dogen::cpp::template_id& template_id)
    : cv_qualifier_(cv_qualifier),
      pointer_type_(pointer_type),
      qualified_id_(qualified_id),
      class_key_(class_key),
      template_id_(template_id) { }

void type_specifier::swap(type_specifier& other) noexcept {
    using std::swap;
    swap(cv_qualifier_, other.cv_qualifier_);
    swap(pointer_type_, other.pointer_type_);
    swap(qualified_id_, other.qualified_id_);
    swap(class_key_, other.class_key_);
    swap(template_id_, other.template_id_);
}

bool type_specifier::operator==(const type_specifier& rhs) const {
    return cv_qualifier_ == rhs.cv_qualifier_ &&
        pointer_type_ == rhs.pointer_type_ &&
        qualified_id_ == rhs.qualified_id_ &&
        class_key_ == rhs.class_key_ &&
        template_id_ == rhs.template_id_;
}

type_specifier& type_specifier::operator=(type_specifier other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::cpp::cv_qualifier_types type_specifier::cv_qualifier() const {
    return cv_qualifier_;
}

void type_specifier::cv_qualifier(const dogen::cpp::cv_qualifier_types& v) {
    cv_qualifier_ = v;
}

dogen::cpp::pointer_types type_specifier::pointer_type() const {
    return pointer_type_;
}

void type_specifier::pointer_type(const dogen::cpp::pointer_types& v) {
    pointer_type_ = v;
}

const dogen::cpp::qualified_id& type_specifier::qualified_id() const {
    return qualified_id_;
}

dogen::cpp::qualified_id& type_specifier::qualified_id() {
    return qualified_id_;
}

void type_specifier::qualified_id(const dogen::cpp::qualified_id& v) {
    qualified_id_ = v;
}

void type_specifier::qualified_id(const dogen::cpp::qualified_id&& v) {
    qualified_id_ = std::move(v);
}

dogen::cpp::class_key_types type_specifier::class_key() const {
    return class_key_;
}

void type_specifier::class_key(const dogen::cpp::class_key_types& v) {
    class_key_ = v;
}

const dogen::cpp::template_id& type_specifier::template_id() const {
    return template_id_;
}

dogen::cpp::template_id& type_specifier::template_id() {
    return template_id_;
}

void type_specifier::template_id(const dogen::cpp::template_id& v) {
    template_id_ = v;
}

void type_specifier::template_id(const dogen::cpp::template_id&& v) {
    template_id_ = std::move(v);
}

} }