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
#include "dogen/quilt.cpp/types/properties/nested_type_info.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

nested_type_info::nested_type_info()
    : is_primitive_(static_cast<bool>(0)),
      is_enumeration_(static_cast<bool>(0)),
      is_string_like_(static_cast<bool>(0)),
      is_char_like_(static_cast<bool>(0)),
      is_int_like_(static_cast<bool>(0)),
      is_sequence_container_(static_cast<bool>(0)),
      is_associative_container_(static_cast<bool>(0)),
      is_smart_pointer_(static_cast<bool>(0)),
      is_optional_like_(static_cast<bool>(0)),
      is_variant_like_(static_cast<bool>(0)),
      is_filesystem_path_(static_cast<bool>(0)),
      is_date_(static_cast<bool>(0)),
      is_ptime_(static_cast<bool>(0)),
      is_time_duration_(static_cast<bool>(0)),
      is_pair_(static_cast<bool>(0)),
      is_ptree_(static_cast<bool>(0)) { }

nested_type_info::nested_type_info(
    const std::string& name,
    const std::string& qualified_name,
    const std::string& identifiable_name,
    const std::string& complete_name,
    const std::string& complete_identifiable_name,
    const bool is_primitive,
    const bool is_enumeration,
    const bool is_string_like,
    const bool is_char_like,
    const bool is_int_like,
    const bool is_sequence_container,
    const bool is_associative_container,
    const bool is_smart_pointer,
    const bool is_optional_like,
    const bool is_variant_like,
    const std::list<dogen::quilt::cpp::properties::nested_type_info>& children,
    const std::list<std::string>& namespaces,
    const bool is_filesystem_path,
    const bool is_date,
    const bool is_ptime,
    const bool is_time_duration,
    const bool is_pair,
    const bool is_ptree)
    : name_(name),
      qualified_name_(qualified_name),
      identifiable_name_(identifiable_name),
      complete_name_(complete_name),
      complete_identifiable_name_(complete_identifiable_name),
      is_primitive_(is_primitive),
      is_enumeration_(is_enumeration),
      is_string_like_(is_string_like),
      is_char_like_(is_char_like),
      is_int_like_(is_int_like),
      is_sequence_container_(is_sequence_container),
      is_associative_container_(is_associative_container),
      is_smart_pointer_(is_smart_pointer),
      is_optional_like_(is_optional_like),
      is_variant_like_(is_variant_like),
      children_(children),
      namespaces_(namespaces),
      is_filesystem_path_(is_filesystem_path),
      is_date_(is_date),
      is_ptime_(is_ptime),
      is_time_duration_(is_time_duration),
      is_pair_(is_pair),
      is_ptree_(is_ptree) { }

void nested_type_info::swap(nested_type_info& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(qualified_name_, other.qualified_name_);
    swap(identifiable_name_, other.identifiable_name_);
    swap(complete_name_, other.complete_name_);
    swap(complete_identifiable_name_, other.complete_identifiable_name_);
    swap(is_primitive_, other.is_primitive_);
    swap(is_enumeration_, other.is_enumeration_);
    swap(is_string_like_, other.is_string_like_);
    swap(is_char_like_, other.is_char_like_);
    swap(is_int_like_, other.is_int_like_);
    swap(is_sequence_container_, other.is_sequence_container_);
    swap(is_associative_container_, other.is_associative_container_);
    swap(is_smart_pointer_, other.is_smart_pointer_);
    swap(is_optional_like_, other.is_optional_like_);
    swap(is_variant_like_, other.is_variant_like_);
    swap(children_, other.children_);
    swap(namespaces_, other.namespaces_);
    swap(is_filesystem_path_, other.is_filesystem_path_);
    swap(is_date_, other.is_date_);
    swap(is_ptime_, other.is_ptime_);
    swap(is_time_duration_, other.is_time_duration_);
    swap(is_pair_, other.is_pair_);
    swap(is_ptree_, other.is_ptree_);
}

bool nested_type_info::operator==(const nested_type_info& rhs) const {
    return name_ == rhs.name_ &&
        qualified_name_ == rhs.qualified_name_ &&
        identifiable_name_ == rhs.identifiable_name_ &&
        complete_name_ == rhs.complete_name_ &&
        complete_identifiable_name_ == rhs.complete_identifiable_name_ &&
        is_primitive_ == rhs.is_primitive_ &&
        is_enumeration_ == rhs.is_enumeration_ &&
        is_string_like_ == rhs.is_string_like_ &&
        is_char_like_ == rhs.is_char_like_ &&
        is_int_like_ == rhs.is_int_like_ &&
        is_sequence_container_ == rhs.is_sequence_container_ &&
        is_associative_container_ == rhs.is_associative_container_ &&
        is_smart_pointer_ == rhs.is_smart_pointer_ &&
        is_optional_like_ == rhs.is_optional_like_ &&
        is_variant_like_ == rhs.is_variant_like_ &&
        children_ == rhs.children_ &&
        namespaces_ == rhs.namespaces_ &&
        is_filesystem_path_ == rhs.is_filesystem_path_ &&
        is_date_ == rhs.is_date_ &&
        is_ptime_ == rhs.is_ptime_ &&
        is_time_duration_ == rhs.is_time_duration_ &&
        is_pair_ == rhs.is_pair_ &&
        is_ptree_ == rhs.is_ptree_;
}

nested_type_info& nested_type_info::operator=(nested_type_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& nested_type_info::name() const {
    return name_;
}

std::string& nested_type_info::name() {
    return name_;
}

void nested_type_info::name(const std::string& v) {
    name_ = v;
}

void nested_type_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& nested_type_info::qualified_name() const {
    return qualified_name_;
}

std::string& nested_type_info::qualified_name() {
    return qualified_name_;
}

void nested_type_info::qualified_name(const std::string& v) {
    qualified_name_ = v;
}

void nested_type_info::qualified_name(const std::string&& v) {
    qualified_name_ = std::move(v);
}

const std::string& nested_type_info::identifiable_name() const {
    return identifiable_name_;
}

std::string& nested_type_info::identifiable_name() {
    return identifiable_name_;
}

void nested_type_info::identifiable_name(const std::string& v) {
    identifiable_name_ = v;
}

void nested_type_info::identifiable_name(const std::string&& v) {
    identifiable_name_ = std::move(v);
}

const std::string& nested_type_info::complete_name() const {
    return complete_name_;
}

std::string& nested_type_info::complete_name() {
    return complete_name_;
}

void nested_type_info::complete_name(const std::string& v) {
    complete_name_ = v;
}

void nested_type_info::complete_name(const std::string&& v) {
    complete_name_ = std::move(v);
}

const std::string& nested_type_info::complete_identifiable_name() const {
    return complete_identifiable_name_;
}

std::string& nested_type_info::complete_identifiable_name() {
    return complete_identifiable_name_;
}

void nested_type_info::complete_identifiable_name(const std::string& v) {
    complete_identifiable_name_ = v;
}

void nested_type_info::complete_identifiable_name(const std::string&& v) {
    complete_identifiable_name_ = std::move(v);
}

bool nested_type_info::is_primitive() const {
    return is_primitive_;
}

void nested_type_info::is_primitive(const bool v) {
    is_primitive_ = v;
}

bool nested_type_info::is_enumeration() const {
    return is_enumeration_;
}

void nested_type_info::is_enumeration(const bool v) {
    is_enumeration_ = v;
}

bool nested_type_info::is_string_like() const {
    return is_string_like_;
}

void nested_type_info::is_string_like(const bool v) {
    is_string_like_ = v;
}

bool nested_type_info::is_char_like() const {
    return is_char_like_;
}

void nested_type_info::is_char_like(const bool v) {
    is_char_like_ = v;
}

bool nested_type_info::is_int_like() const {
    return is_int_like_;
}

void nested_type_info::is_int_like(const bool v) {
    is_int_like_ = v;
}

bool nested_type_info::is_sequence_container() const {
    return is_sequence_container_;
}

void nested_type_info::is_sequence_container(const bool v) {
    is_sequence_container_ = v;
}

bool nested_type_info::is_associative_container() const {
    return is_associative_container_;
}

void nested_type_info::is_associative_container(const bool v) {
    is_associative_container_ = v;
}

bool nested_type_info::is_smart_pointer() const {
    return is_smart_pointer_;
}

void nested_type_info::is_smart_pointer(const bool v) {
    is_smart_pointer_ = v;
}

bool nested_type_info::is_optional_like() const {
    return is_optional_like_;
}

void nested_type_info::is_optional_like(const bool v) {
    is_optional_like_ = v;
}

bool nested_type_info::is_variant_like() const {
    return is_variant_like_;
}

void nested_type_info::is_variant_like(const bool v) {
    is_variant_like_ = v;
}

const std::list<dogen::quilt::cpp::properties::nested_type_info>& nested_type_info::children() const {
    return children_;
}

std::list<dogen::quilt::cpp::properties::nested_type_info>& nested_type_info::children() {
    return children_;
}

void nested_type_info::children(const std::list<dogen::quilt::cpp::properties::nested_type_info>& v) {
    children_ = v;
}

void nested_type_info::children(const std::list<dogen::quilt::cpp::properties::nested_type_info>&& v) {
    children_ = std::move(v);
}

const std::list<std::string>& nested_type_info::namespaces() const {
    return namespaces_;
}

std::list<std::string>& nested_type_info::namespaces() {
    return namespaces_;
}

void nested_type_info::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void nested_type_info::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

bool nested_type_info::is_filesystem_path() const {
    return is_filesystem_path_;
}

void nested_type_info::is_filesystem_path(const bool v) {
    is_filesystem_path_ = v;
}

bool nested_type_info::is_date() const {
    return is_date_;
}

void nested_type_info::is_date(const bool v) {
    is_date_ = v;
}

bool nested_type_info::is_ptime() const {
    return is_ptime_;
}

void nested_type_info::is_ptime(const bool v) {
    is_ptime_ = v;
}

bool nested_type_info::is_time_duration() const {
    return is_time_duration_;
}

void nested_type_info::is_time_duration(const bool v) {
    is_time_duration_ = v;
}

bool nested_type_info::is_pair() const {
    return is_pair_;
}

void nested_type_info::is_pair(const bool v) {
    is_pair_ = v;
}

bool nested_type_info::is_ptree() const {
    return is_ptree_;
}

void nested_type_info::is_ptree(const bool v) {
    is_ptree_ = v;
}

} } } }
