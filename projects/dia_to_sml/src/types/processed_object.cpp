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
#include "dogen/dia_to_sml/types/processed_object.hpp"

namespace dogen {
namespace dia_to_sml {

processed_object::processed_object()
    : object_type_(static_cast<dogen::dia_to_sml::object_types>(0)),
      stereotype_(static_cast<dogen::dia_to_sml::stereotypes>(0)) { }

processed_object::processed_object(
    const std::string& name,
    const dogen::dia_to_sml::object_types& object_type,
    const dogen::dia_to_sml::stereotypes& stereotype,
    const std::string& comment,
    const std::vector<dogen::dia::composite>& uml_attributes,
    const std::string& parent_id)
    : name_(name),
      object_type_(object_type),
      stereotype_(stereotype),
      comment_(comment),
      uml_attributes_(uml_attributes),
      parent_id_(parent_id) { }

void processed_object::swap(processed_object& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(object_type_, other.object_type_);
    swap(stereotype_, other.stereotype_);
    swap(comment_, other.comment_);
    swap(uml_attributes_, other.uml_attributes_);
    swap(parent_id_, other.parent_id_);
}

bool processed_object::operator==(const processed_object& rhs) const {
    return name_ == rhs.name_ &&
        object_type_ == rhs.object_type_ &&
        stereotype_ == rhs.stereotype_ &&
        comment_ == rhs.comment_ &&
        uml_attributes_ == rhs.uml_attributes_ &&
        parent_id_ == rhs.parent_id_;
}

processed_object& processed_object::operator=(processed_object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& processed_object::name() const {
    return name_;
}

std::string& processed_object::name() {
    return name_;
}

void processed_object::name(const std::string& v) {
    name_ = v;
}

void processed_object::name(const std::string&& v) {
    name_ = std::move(v);
}

dogen::dia_to_sml::object_types processed_object::object_type() const {
    return object_type_;
}

void processed_object::object_type(const dogen::dia_to_sml::object_types& v) {
    object_type_ = v;
}

dogen::dia_to_sml::stereotypes processed_object::stereotype() const {
    return stereotype_;
}

void processed_object::stereotype(const dogen::dia_to_sml::stereotypes& v) {
    stereotype_ = v;
}

const std::string& processed_object::comment() const {
    return comment_;
}

std::string& processed_object::comment() {
    return comment_;
}

void processed_object::comment(const std::string& v) {
    comment_ = v;
}

void processed_object::comment(const std::string&& v) {
    comment_ = std::move(v);
}

const std::vector<dogen::dia::composite>& processed_object::uml_attributes() const {
    return uml_attributes_;
}

std::vector<dogen::dia::composite>& processed_object::uml_attributes() {
    return uml_attributes_;
}

void processed_object::uml_attributes(const std::vector<dogen::dia::composite>& v) {
    uml_attributes_ = v;
}

void processed_object::uml_attributes(const std::vector<dogen::dia::composite>&& v) {
    uml_attributes_ = std::move(v);
}

const std::string& processed_object::parent_id() const {
    return parent_id_;
}

std::string& processed_object::parent_id() {
    return parent_id_;
}

void processed_object::parent_id(const std::string& v) {
    parent_id_ = v;
}

void processed_object::parent_id(const std::string&& v) {
    parent_id_ = std::move(v);
}

} }