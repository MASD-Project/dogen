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
#include "dogen/yarn/types/meta_model/exoelement.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

exoelement::exoelement()
    : can_be_primitive_underlier_(static_cast<bool>(0)),
      in_global_module_(static_cast<bool>(0)),
      can_be_enumeration_underlier_(static_cast<bool>(0)),
      is_default_enumeration_type_(static_cast<bool>(0)),
      is_associative_container_(static_cast<bool>(0)),
      is_floating_point_(static_cast<bool>(0)) { }

exoelement::exoelement(
    const std::string& documentation,
    const std::list<std::pair<std::string, std::string> >& tagged_values,
    const std::string& name,
    const std::list<std::string>& parents,
    const std::list<dogen::yarn::meta_model::exoattribute>& attributes,
    const bool can_be_primitive_underlier,
    const bool in_global_module,
    const bool can_be_enumeration_underlier,
    const bool is_default_enumeration_type,
    const bool is_associative_container,
    const bool is_floating_point,
    const std::list<std::string>& stereotypes,
    const std::string& fallback_element_type)
    : documentation_(documentation),
      tagged_values_(tagged_values),
      name_(name),
      parents_(parents),
      attributes_(attributes),
      can_be_primitive_underlier_(can_be_primitive_underlier),
      in_global_module_(in_global_module),
      can_be_enumeration_underlier_(can_be_enumeration_underlier),
      is_default_enumeration_type_(is_default_enumeration_type),
      is_associative_container_(is_associative_container),
      is_floating_point_(is_floating_point),
      stereotypes_(stereotypes),
      fallback_element_type_(fallback_element_type) { }

void exoelement::swap(exoelement& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(tagged_values_, other.tagged_values_);
    swap(name_, other.name_);
    swap(parents_, other.parents_);
    swap(attributes_, other.attributes_);
    swap(can_be_primitive_underlier_, other.can_be_primitive_underlier_);
    swap(in_global_module_, other.in_global_module_);
    swap(can_be_enumeration_underlier_, other.can_be_enumeration_underlier_);
    swap(is_default_enumeration_type_, other.is_default_enumeration_type_);
    swap(is_associative_container_, other.is_associative_container_);
    swap(is_floating_point_, other.is_floating_point_);
    swap(stereotypes_, other.stereotypes_);
    swap(fallback_element_type_, other.fallback_element_type_);
}

bool exoelement::operator==(const exoelement& rhs) const {
    return documentation_ == rhs.documentation_ &&
        tagged_values_ == rhs.tagged_values_ &&
        name_ == rhs.name_ &&
        parents_ == rhs.parents_ &&
        attributes_ == rhs.attributes_ &&
        can_be_primitive_underlier_ == rhs.can_be_primitive_underlier_ &&
        in_global_module_ == rhs.in_global_module_ &&
        can_be_enumeration_underlier_ == rhs.can_be_enumeration_underlier_ &&
        is_default_enumeration_type_ == rhs.is_default_enumeration_type_ &&
        is_associative_container_ == rhs.is_associative_container_ &&
        is_floating_point_ == rhs.is_floating_point_ &&
        stereotypes_ == rhs.stereotypes_ &&
        fallback_element_type_ == rhs.fallback_element_type_;
}

exoelement& exoelement::operator=(exoelement other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& exoelement::documentation() const {
    return documentation_;
}

std::string& exoelement::documentation() {
    return documentation_;
}

void exoelement::documentation(const std::string& v) {
    documentation_ = v;
}

void exoelement::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::list<std::pair<std::string, std::string> >& exoelement::tagged_values() const {
    return tagged_values_;
}

std::list<std::pair<std::string, std::string> >& exoelement::tagged_values() {
    return tagged_values_;
}

void exoelement::tagged_values(const std::list<std::pair<std::string, std::string> >& v) {
    tagged_values_ = v;
}

void exoelement::tagged_values(const std::list<std::pair<std::string, std::string> >&& v) {
    tagged_values_ = std::move(v);
}

const std::string& exoelement::name() const {
    return name_;
}

std::string& exoelement::name() {
    return name_;
}

void exoelement::name(const std::string& v) {
    name_ = v;
}

void exoelement::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& exoelement::parents() const {
    return parents_;
}

std::list<std::string>& exoelement::parents() {
    return parents_;
}

void exoelement::parents(const std::list<std::string>& v) {
    parents_ = v;
}

void exoelement::parents(const std::list<std::string>&& v) {
    parents_ = std::move(v);
}

const std::list<dogen::yarn::meta_model::exoattribute>& exoelement::attributes() const {
    return attributes_;
}

std::list<dogen::yarn::meta_model::exoattribute>& exoelement::attributes() {
    return attributes_;
}

void exoelement::attributes(const std::list<dogen::yarn::meta_model::exoattribute>& v) {
    attributes_ = v;
}

void exoelement::attributes(const std::list<dogen::yarn::meta_model::exoattribute>&& v) {
    attributes_ = std::move(v);
}

bool exoelement::can_be_primitive_underlier() const {
    return can_be_primitive_underlier_;
}

void exoelement::can_be_primitive_underlier(const bool v) {
    can_be_primitive_underlier_ = v;
}

bool exoelement::in_global_module() const {
    return in_global_module_;
}

void exoelement::in_global_module(const bool v) {
    in_global_module_ = v;
}

bool exoelement::can_be_enumeration_underlier() const {
    return can_be_enumeration_underlier_;
}

void exoelement::can_be_enumeration_underlier(const bool v) {
    can_be_enumeration_underlier_ = v;
}

bool exoelement::is_default_enumeration_type() const {
    return is_default_enumeration_type_;
}

void exoelement::is_default_enumeration_type(const bool v) {
    is_default_enumeration_type_ = v;
}

bool exoelement::is_associative_container() const {
    return is_associative_container_;
}

void exoelement::is_associative_container(const bool v) {
    is_associative_container_ = v;
}

bool exoelement::is_floating_point() const {
    return is_floating_point_;
}

void exoelement::is_floating_point(const bool v) {
    is_floating_point_ = v;
}

const std::list<std::string>& exoelement::stereotypes() const {
    return stereotypes_;
}

std::list<std::string>& exoelement::stereotypes() {
    return stereotypes_;
}

void exoelement::stereotypes(const std::list<std::string>& v) {
    stereotypes_ = v;
}

void exoelement::stereotypes(const std::list<std::string>&& v) {
    stereotypes_ = std::move(v);
}

const std::string& exoelement::fallback_element_type() const {
    return fallback_element_type_;
}

std::string& exoelement::fallback_element_type() {
    return fallback_element_type_;
}

void exoelement::fallback_element_type(const std::string& v) {
    fallback_element_type_ = v;
}

void exoelement::fallback_element_type(const std::string&& v) {
    fallback_element_type_ = std::move(v);
}

} } }
