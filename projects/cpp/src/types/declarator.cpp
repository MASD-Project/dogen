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
#include "dogen/cpp/types/declarator.hpp"

namespace dogen {
namespace cpp {

declarator::declarator()
    : cv_qualifier_(static_cast<dogen::cpp::cv_qualifier_types>(0)),
      pointer_type_(static_cast<dogen::cpp::pointer_types>(0)),
      pointer_cv_qualifier_(static_cast<dogen::cpp::cv_qualifier_types>(0)) { }

declarator::declarator(
    const dogen::cpp::cv_qualifier_types& cv_qualifier,
    const dogen::cpp::pointer_types& pointer_type,
    const dogen::cpp::cv_qualifier_types& pointer_cv_qualifier,
    const dogen::cpp::qualified_id& declarator_id,
    const std::list<dogen::cpp::qualified_id>& exception_specification,
    const std::list<dogen::cpp::parameter_declaration>& parameter_declaration_list)
    : cv_qualifier_(cv_qualifier),
      pointer_type_(pointer_type),
      pointer_cv_qualifier_(pointer_cv_qualifier),
      declarator_id_(declarator_id),
      exception_specification_(exception_specification),
      parameter_declaration_list_(parameter_declaration_list) { }

void declarator::swap(declarator& other) noexcept {
    using std::swap;
    swap(cv_qualifier_, other.cv_qualifier_);
    swap(pointer_type_, other.pointer_type_);
    swap(pointer_cv_qualifier_, other.pointer_cv_qualifier_);
    swap(declarator_id_, other.declarator_id_);
    swap(exception_specification_, other.exception_specification_);
    swap(parameter_declaration_list_, other.parameter_declaration_list_);
}

bool declarator::operator==(const declarator& rhs) const {
    return cv_qualifier_ == rhs.cv_qualifier_ &&
        pointer_type_ == rhs.pointer_type_ &&
        pointer_cv_qualifier_ == rhs.pointer_cv_qualifier_ &&
        declarator_id_ == rhs.declarator_id_ &&
        exception_specification_ == rhs.exception_specification_ &&
        parameter_declaration_list_ == rhs.parameter_declaration_list_;
}

declarator& declarator::operator=(declarator other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::cpp::cv_qualifier_types declarator::cv_qualifier() const {
    return cv_qualifier_;
}

void declarator::cv_qualifier(const dogen::cpp::cv_qualifier_types& v) {
    cv_qualifier_ = v;
}

dogen::cpp::pointer_types declarator::pointer_type() const {
    return pointer_type_;
}

void declarator::pointer_type(const dogen::cpp::pointer_types& v) {
    pointer_type_ = v;
}

dogen::cpp::cv_qualifier_types declarator::pointer_cv_qualifier() const {
    return pointer_cv_qualifier_;
}

void declarator::pointer_cv_qualifier(const dogen::cpp::cv_qualifier_types& v) {
    pointer_cv_qualifier_ = v;
}

const dogen::cpp::qualified_id& declarator::declarator_id() const {
    return declarator_id_;
}

dogen::cpp::qualified_id& declarator::declarator_id() {
    return declarator_id_;
}

void declarator::declarator_id(const dogen::cpp::qualified_id& v) {
    declarator_id_ = v;
}

void declarator::declarator_id(const dogen::cpp::qualified_id&& v) {
    declarator_id_ = std::move(v);
}

const std::list<dogen::cpp::qualified_id>& declarator::exception_specification() const {
    return exception_specification_;
}

std::list<dogen::cpp::qualified_id>& declarator::exception_specification() {
    return exception_specification_;
}

void declarator::exception_specification(const std::list<dogen::cpp::qualified_id>& v) {
    exception_specification_ = v;
}

void declarator::exception_specification(const std::list<dogen::cpp::qualified_id>&& v) {
    exception_specification_ = std::move(v);
}

const std::list<dogen::cpp::parameter_declaration>& declarator::parameter_declaration_list() const {
    return parameter_declaration_list_;
}

std::list<dogen::cpp::parameter_declaration>& declarator::parameter_declaration_list() {
    return parameter_declaration_list_;
}

void declarator::parameter_declaration_list(const std::list<dogen::cpp::parameter_declaration>& v) {
    parameter_declaration_list_ = v;
}

void declarator::parameter_declaration_list(const std::list<dogen::cpp::parameter_declaration>&& v) {
    parameter_declaration_list_ = std::move(v);
}

} }