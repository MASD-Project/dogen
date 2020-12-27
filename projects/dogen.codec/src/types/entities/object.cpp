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
#include "dogen.codec/types/entities/object.hpp"

namespace dogen::codec::entities {

object::object()
    : is_package_(static_cast<bool>(0)) { }

object::object(object&& rhs)
    : comment_(std::move(rhs.comment_)),
      id_(std::move(rhs.id_)),
      name_(std::move(rhs.name_)),
      object_type_(std::move(rhs.object_type_)),
      stereotypes_(std::move(rhs.stereotypes_)),
      container_id_(std::move(rhs.container_id_)),
      connection_(std::move(rhs.connection_)),
      attributes_(std::move(rhs.attributes_)),
      is_package_(std::move(rhs.is_package_)) { }

object::object(
    const dogen::codec::entities::comment& comment,
    const std::string& id,
    const std::string& name,
    const std::string& object_type,
    const std::string& stereotypes,
    const std::string& container_id,
    const boost::optional<std::pair<std::string, std::string> >& connection,
    const std::list<dogen::codec::entities::attribute>& attributes,
    const bool is_package)
    : comment_(comment),
      id_(id),
      name_(name),
      object_type_(object_type),
      stereotypes_(stereotypes),
      container_id_(container_id),
      connection_(connection),
      attributes_(attributes),
      is_package_(is_package) { }

void object::swap(object& other) noexcept {
    using std::swap;
    swap(comment_, other.comment_);
    swap(id_, other.id_);
    swap(name_, other.name_);
    swap(object_type_, other.object_type_);
    swap(stereotypes_, other.stereotypes_);
    swap(container_id_, other.container_id_);
    swap(connection_, other.connection_);
    swap(attributes_, other.attributes_);
    swap(is_package_, other.is_package_);
}

bool object::operator==(const object& rhs) const {
    return comment_ == rhs.comment_ &&
        id_ == rhs.id_ &&
        name_ == rhs.name_ &&
        object_type_ == rhs.object_type_ &&
        stereotypes_ == rhs.stereotypes_ &&
        container_id_ == rhs.container_id_ &&
        connection_ == rhs.connection_ &&
        attributes_ == rhs.attributes_ &&
        is_package_ == rhs.is_package_;
}

object& object::operator=(object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::codec::entities::comment& object::comment() const {
    return comment_;
}

dogen::codec::entities::comment& object::comment() {
    return comment_;
}

void object::comment(const dogen::codec::entities::comment& v) {
    comment_ = v;
}

void object::comment(const dogen::codec::entities::comment&& v) {
    comment_ = std::move(v);
}

const std::string& object::id() const {
    return id_;
}

std::string& object::id() {
    return id_;
}

void object::id(const std::string& v) {
    id_ = v;
}

void object::id(const std::string&& v) {
    id_ = std::move(v);
}

const std::string& object::name() const {
    return name_;
}

std::string& object::name() {
    return name_;
}

void object::name(const std::string& v) {
    name_ = v;
}

void object::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& object::object_type() const {
    return object_type_;
}

std::string& object::object_type() {
    return object_type_;
}

void object::object_type(const std::string& v) {
    object_type_ = v;
}

void object::object_type(const std::string&& v) {
    object_type_ = std::move(v);
}

const std::string& object::stereotypes() const {
    return stereotypes_;
}

std::string& object::stereotypes() {
    return stereotypes_;
}

void object::stereotypes(const std::string& v) {
    stereotypes_ = v;
}

void object::stereotypes(const std::string&& v) {
    stereotypes_ = std::move(v);
}

const std::string& object::container_id() const {
    return container_id_;
}

std::string& object::container_id() {
    return container_id_;
}

void object::container_id(const std::string& v) {
    container_id_ = v;
}

void object::container_id(const std::string&& v) {
    container_id_ = std::move(v);
}

const boost::optional<std::pair<std::string, std::string> >& object::connection() const {
    return connection_;
}

boost::optional<std::pair<std::string, std::string> >& object::connection() {
    return connection_;
}

void object::connection(const boost::optional<std::pair<std::string, std::string> >& v) {
    connection_ = v;
}

void object::connection(const boost::optional<std::pair<std::string, std::string> >&& v) {
    connection_ = std::move(v);
}

const std::list<dogen::codec::entities::attribute>& object::attributes() const {
    return attributes_;
}

std::list<dogen::codec::entities::attribute>& object::attributes() {
    return attributes_;
}

void object::attributes(const std::list<dogen::codec::entities::attribute>& v) {
    attributes_ = v;
}

void object::attributes(const std::list<dogen::codec::entities::attribute>&& v) {
    attributes_ = std::move(v);
}

bool object::is_package() const {
    return is_package_;
}

void object::is_package(const bool v) {
    is_package_ = v;
}

}
