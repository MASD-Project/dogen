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
#include "dogen/dia_to_sml/types/profile.hpp"

namespace dogen {
namespace dia_to_sml {

profile::profile()
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
      is_value_object_(static_cast<bool>(0)),
      is_service_(static_cast<bool>(0)),
      is_non_generatable_(static_cast<bool>(0)),
      is_versioned_(static_cast<bool>(0)),
      is_keyed_entity_(static_cast<bool>(0)),
      is_visitable_(static_cast<bool>(0)),
      is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)),
      is_aggregate_root_(static_cast<bool>(0)),
      is_concept_(static_cast<bool>(0)),
      is_repository_(static_cast<bool>(0)),
      is_factory_(static_cast<bool>(0)) { }

profile::profile(
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
    const bool is_value_object,
    const bool is_service,
    const bool is_non_generatable,
    const bool is_versioned,
    const bool is_keyed_entity,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_fluent,
    const bool is_aggregate_root,
    const bool is_concept,
    const std::list<std::string>& unknown_stereotypes,
    const bool is_repository,
    const bool is_factory)
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
      is_value_object_(is_value_object),
      is_service_(is_service),
      is_non_generatable_(is_non_generatable),
      is_versioned_(is_versioned),
      is_keyed_entity_(is_keyed_entity),
      is_visitable_(is_visitable),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      is_aggregate_root_(is_aggregate_root),
      is_concept_(is_concept),
      unknown_stereotypes_(unknown_stereotypes),
      is_repository_(is_repository),
      is_factory_(is_factory) { }

void profile::swap(profile& other) noexcept {
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
    swap(is_value_object_, other.is_value_object_);
    swap(is_service_, other.is_service_);
    swap(is_non_generatable_, other.is_non_generatable_);
    swap(is_versioned_, other.is_versioned_);
    swap(is_keyed_entity_, other.is_keyed_entity_);
    swap(is_visitable_, other.is_visitable_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(is_aggregate_root_, other.is_aggregate_root_);
    swap(is_concept_, other.is_concept_);
    swap(unknown_stereotypes_, other.unknown_stereotypes_);
    swap(is_repository_, other.is_repository_);
    swap(is_factory_, other.is_factory_);
}

bool profile::operator==(const profile& rhs) const {
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
        is_value_object_ == rhs.is_value_object_ &&
        is_service_ == rhs.is_service_ &&
        is_non_generatable_ == rhs.is_non_generatable_ &&
        is_versioned_ == rhs.is_versioned_ &&
        is_keyed_entity_ == rhs.is_keyed_entity_ &&
        is_visitable_ == rhs.is_visitable_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        is_aggregate_root_ == rhs.is_aggregate_root_ &&
        is_concept_ == rhs.is_concept_ &&
        unknown_stereotypes_ == rhs.unknown_stereotypes_ &&
        is_repository_ == rhs.is_repository_ &&
        is_factory_ == rhs.is_factory_;
}

profile& profile::operator=(profile other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool profile::is_uml_large_package() const {
    return is_uml_large_package_;
}

void profile::is_uml_large_package(const bool v) {
    is_uml_large_package_ = v;
}

bool profile::is_uml_class() const {
    return is_uml_class_;
}

void profile::is_uml_class(const bool v) {
    is_uml_class_ = v;
}

bool profile::is_uml_generalization() const {
    return is_uml_generalization_;
}

void profile::is_uml_generalization(const bool v) {
    is_uml_generalization_ = v;
}

bool profile::is_uml_association() const {
    return is_uml_association_;
}

void profile::is_uml_association(const bool v) {
    is_uml_association_ = v;
}

bool profile::is_uml_note() const {
    return is_uml_note_;
}

void profile::is_uml_note(const bool v) {
    is_uml_note_ = v;
}

bool profile::is_uml_message() const {
    return is_uml_message_;
}

void profile::is_uml_message(const bool v) {
    is_uml_message_ = v;
}

bool profile::is_uml_realization() const {
    return is_uml_realization_;
}

void profile::is_uml_realization(const bool v) {
    is_uml_realization_ = v;
}

bool profile::is_enumeration() const {
    return is_enumeration_;
}

void profile::is_enumeration(const bool v) {
    is_enumeration_ = v;
}

bool profile::is_exception() const {
    return is_exception_;
}

void profile::is_exception(const bool v) {
    is_exception_ = v;
}

bool profile::is_entity() const {
    return is_entity_;
}

void profile::is_entity(const bool v) {
    is_entity_ = v;
}

bool profile::is_value_object() const {
    return is_value_object_;
}

void profile::is_value_object(const bool v) {
    is_value_object_ = v;
}

bool profile::is_service() const {
    return is_service_;
}

void profile::is_service(const bool v) {
    is_service_ = v;
}

bool profile::is_non_generatable() const {
    return is_non_generatable_;
}

void profile::is_non_generatable(const bool v) {
    is_non_generatable_ = v;
}

bool profile::is_versioned() const {
    return is_versioned_;
}

void profile::is_versioned(const bool v) {
    is_versioned_ = v;
}

bool profile::is_keyed_entity() const {
    return is_keyed_entity_;
}

void profile::is_keyed_entity(const bool v) {
    is_keyed_entity_ = v;
}

bool profile::is_visitable() const {
    return is_visitable_;
}

void profile::is_visitable(const bool v) {
    is_visitable_ = v;
}

bool profile::is_immutable() const {
    return is_immutable_;
}

void profile::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool profile::is_fluent() const {
    return is_fluent_;
}

void profile::is_fluent(const bool v) {
    is_fluent_ = v;
}

bool profile::is_aggregate_root() const {
    return is_aggregate_root_;
}

void profile::is_aggregate_root(const bool v) {
    is_aggregate_root_ = v;
}

bool profile::is_concept() const {
    return is_concept_;
}

void profile::is_concept(const bool v) {
    is_concept_ = v;
}

const std::list<std::string>& profile::unknown_stereotypes() const {
    return unknown_stereotypes_;
}

std::list<std::string>& profile::unknown_stereotypes() {
    return unknown_stereotypes_;
}

void profile::unknown_stereotypes(const std::list<std::string>& v) {
    unknown_stereotypes_ = v;
}

void profile::unknown_stereotypes(const std::list<std::string>&& v) {
    unknown_stereotypes_ = std::move(v);
}

bool profile::is_repository() const {
    return is_repository_;
}

void profile::is_repository(const bool v) {
    is_repository_ = v;
}

bool profile::is_factory() const {
    return is_factory_;
}

void profile::is_factory(const bool v) {
    is_factory_ = v;
}

} }