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
#include "dogen/dia_to_sml/types/object_profile.hpp"

namespace dogen {
namespace dia_to_sml {

object_profile::object_profile()
    : is_uml_large_package_(static_cast<bool>(0)),
      is_uml_class_(static_cast<bool>(0)),
      is_uml_generalization_(static_cast<bool>(0)),
      is_uml_association_(static_cast<bool>(0)),
      is_uml_note_(static_cast<bool>(0)),
      is_uml_message_(static_cast<bool>(0)),
      is_uml_realization_(static_cast<bool>(0)),
      is_enumeration_(static_cast<bool>(0)),
      is_exception_(static_cast<bool>(0)),
      is_entity_(static_cast<bool>(0)),
      is_value_(static_cast<bool>(0)),
      is_service_(static_cast<bool>(0)),
      is_non_generatable_(static_cast<bool>(0)),
      is_versioned_(static_cast<bool>(0)),
      is_keyed_(static_cast<bool>(0)) { }

object_profile::object_profile(
    const bool is_uml_large_package,
    const bool is_uml_class,
    const bool is_uml_generalization,
    const bool is_uml_association,
    const bool is_uml_note,
    const bool is_uml_message,
    const bool is_uml_realization,
    const bool is_enumeration,
    const bool is_exception,
    const bool is_entity,
    const bool is_value,
    const bool is_service,
    const bool is_non_generatable,
    const bool is_versioned,
    const bool is_keyed)
    : is_uml_large_package_(is_uml_large_package),
      is_uml_class_(is_uml_class),
      is_uml_generalization_(is_uml_generalization),
      is_uml_association_(is_uml_association),
      is_uml_note_(is_uml_note),
      is_uml_message_(is_uml_message),
      is_uml_realization_(is_uml_realization),
      is_enumeration_(is_enumeration),
      is_exception_(is_exception),
      is_entity_(is_entity),
      is_value_(is_value),
      is_service_(is_service),
      is_non_generatable_(is_non_generatable),
      is_versioned_(is_versioned),
      is_keyed_(is_keyed) { }

void object_profile::swap(object_profile& other) noexcept {
    using std::swap;
    swap(is_uml_large_package_, other.is_uml_large_package_);
    swap(is_uml_class_, other.is_uml_class_);
    swap(is_uml_generalization_, other.is_uml_generalization_);
    swap(is_uml_association_, other.is_uml_association_);
    swap(is_uml_note_, other.is_uml_note_);
    swap(is_uml_message_, other.is_uml_message_);
    swap(is_uml_realization_, other.is_uml_realization_);
    swap(is_enumeration_, other.is_enumeration_);
    swap(is_exception_, other.is_exception_);
    swap(is_entity_, other.is_entity_);
    swap(is_value_, other.is_value_);
    swap(is_service_, other.is_service_);
    swap(is_non_generatable_, other.is_non_generatable_);
    swap(is_versioned_, other.is_versioned_);
    swap(is_keyed_, other.is_keyed_);
}

bool object_profile::operator==(const object_profile& rhs) const {
    return is_uml_large_package_ == rhs.is_uml_large_package_ &&
        is_uml_class_ == rhs.is_uml_class_ &&
        is_uml_generalization_ == rhs.is_uml_generalization_ &&
        is_uml_association_ == rhs.is_uml_association_ &&
        is_uml_note_ == rhs.is_uml_note_ &&
        is_uml_message_ == rhs.is_uml_message_ &&
        is_uml_realization_ == rhs.is_uml_realization_ &&
        is_enumeration_ == rhs.is_enumeration_ &&
        is_exception_ == rhs.is_exception_ &&
        is_entity_ == rhs.is_entity_ &&
        is_value_ == rhs.is_value_ &&
        is_service_ == rhs.is_service_ &&
        is_non_generatable_ == rhs.is_non_generatable_ &&
        is_versioned_ == rhs.is_versioned_ &&
        is_keyed_ == rhs.is_keyed_;
}

object_profile& object_profile::operator=(object_profile other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool object_profile::is_uml_large_package() const {
    return is_uml_large_package_;
}

void object_profile::is_uml_large_package(const bool v) {
    is_uml_large_package_ = v;
}

bool object_profile::is_uml_class() const {
    return is_uml_class_;
}

void object_profile::is_uml_class(const bool v) {
    is_uml_class_ = v;
}

bool object_profile::is_uml_generalization() const {
    return is_uml_generalization_;
}

void object_profile::is_uml_generalization(const bool v) {
    is_uml_generalization_ = v;
}

bool object_profile::is_uml_association() const {
    return is_uml_association_;
}

void object_profile::is_uml_association(const bool v) {
    is_uml_association_ = v;
}

bool object_profile::is_uml_note() const {
    return is_uml_note_;
}

void object_profile::is_uml_note(const bool v) {
    is_uml_note_ = v;
}

bool object_profile::is_uml_message() const {
    return is_uml_message_;
}

void object_profile::is_uml_message(const bool v) {
    is_uml_message_ = v;
}

bool object_profile::is_uml_realization() const {
    return is_uml_realization_;
}

void object_profile::is_uml_realization(const bool v) {
    is_uml_realization_ = v;
}

bool object_profile::is_enumeration() const {
    return is_enumeration_;
}

void object_profile::is_enumeration(const bool v) {
    is_enumeration_ = v;
}

bool object_profile::is_exception() const {
    return is_exception_;
}

void object_profile::is_exception(const bool v) {
    is_exception_ = v;
}

bool object_profile::is_entity() const {
    return is_entity_;
}

void object_profile::is_entity(const bool v) {
    is_entity_ = v;
}

bool object_profile::is_value() const {
    return is_value_;
}

void object_profile::is_value(const bool v) {
    is_value_ = v;
}

bool object_profile::is_service() const {
    return is_service_;
}

void object_profile::is_service(const bool v) {
    is_service_ = v;
}

bool object_profile::is_non_generatable() const {
    return is_non_generatable_;
}

void object_profile::is_non_generatable(const bool v) {
    is_non_generatable_ = v;
}

bool object_profile::is_versioned() const {
    return is_versioned_;
}

void object_profile::is_versioned(const bool v) {
    is_versioned_ = v;
}

bool object_profile::is_keyed() const {
    return is_keyed_;
}

void object_profile::is_keyed(const bool v) {
    is_keyed_ = v;
}

} }