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
#include "dogen.codec.dia/types/processed_object.hpp"

namespace dogen::codec::dia {

processed_object::processed_object()
    : dia_object_type_(static_cast<dogen::codec::dia::dia_object_types>(0)) { }

processed_object::processed_object(processed_object&& rhs)
    : id_(std::move(rhs.id_)),
      name_(std::move(rhs.name_)),
      dia_object_type_(std::move(rhs.dia_object_type_)),
      stereotypes_(std::move(rhs.stereotypes_)),
      comment_(std::move(rhs.comment_)),
      child_node_id_(std::move(rhs.child_node_id_)),
      connection_(std::move(rhs.connection_)),
      attributes_(std::move(rhs.attributes_)) { }

processed_object::processed_object(
    const std::string& id,
    const std::string& name,
    const dogen::codec::dia::dia_object_types dia_object_type,
    const std::string& stereotypes,
    const dogen::codec::dia::processed_comment& comment,
    const std::string& child_node_id,
    const boost::optional<std::pair<std::string, std::string> >& connection,
    const std::list<dogen::codec::dia::processed_attribute>& attributes)
    : id_(id),
      name_(name),
      dia_object_type_(dia_object_type),
      stereotypes_(stereotypes),
      comment_(comment),
      child_node_id_(child_node_id),
      connection_(connection),
      attributes_(attributes) { }

void processed_object::swap(processed_object& other) noexcept {
    using std::swap;
    swap(id_, other.id_);
    swap(name_, other.name_);
    swap(dia_object_type_, other.dia_object_type_);
    swap(stereotypes_, other.stereotypes_);
    swap(comment_, other.comment_);
    swap(child_node_id_, other.child_node_id_);
    swap(connection_, other.connection_);
    swap(attributes_, other.attributes_);
}

bool processed_object::operator==(const processed_object& rhs) const {
    return id_ == rhs.id_ &&
        name_ == rhs.name_ &&
        dia_object_type_ == rhs.dia_object_type_ &&
        stereotypes_ == rhs.stereotypes_ &&
        comment_ == rhs.comment_ &&
        child_node_id_ == rhs.child_node_id_ &&
        connection_ == rhs.connection_ &&
        attributes_ == rhs.attributes_;
}

processed_object& processed_object::operator=(processed_object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& processed_object::id() const {
    return id_;
}

std::string& processed_object::id() {
    return id_;
}

void processed_object::id(const std::string& v) {
    id_ = v;
}

void processed_object::id(const std::string&& v) {
    id_ = std::move(v);
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

dogen::codec::dia::dia_object_types processed_object::dia_object_type() const {
    return dia_object_type_;
}

void processed_object::dia_object_type(const dogen::codec::dia::dia_object_types v) {
    dia_object_type_ = v;
}

const std::string& processed_object::stereotypes() const {
    return stereotypes_;
}

std::string& processed_object::stereotypes() {
    return stereotypes_;
}

void processed_object::stereotypes(const std::string& v) {
    stereotypes_ = v;
}

void processed_object::stereotypes(const std::string&& v) {
    stereotypes_ = std::move(v);
}

const dogen::codec::dia::processed_comment& processed_object::comment() const {
    return comment_;
}

dogen::codec::dia::processed_comment& processed_object::comment() {
    return comment_;
}

void processed_object::comment(const dogen::codec::dia::processed_comment& v) {
    comment_ = v;
}

void processed_object::comment(const dogen::codec::dia::processed_comment&& v) {
    comment_ = std::move(v);
}

const std::string& processed_object::child_node_id() const {
    return child_node_id_;
}

std::string& processed_object::child_node_id() {
    return child_node_id_;
}

void processed_object::child_node_id(const std::string& v) {
    child_node_id_ = v;
}

void processed_object::child_node_id(const std::string&& v) {
    child_node_id_ = std::move(v);
}

const boost::optional<std::pair<std::string, std::string> >& processed_object::connection() const {
    return connection_;
}

boost::optional<std::pair<std::string, std::string> >& processed_object::connection() {
    return connection_;
}

void processed_object::connection(const boost::optional<std::pair<std::string, std::string> >& v) {
    connection_ = v;
}

void processed_object::connection(const boost::optional<std::pair<std::string, std::string> >&& v) {
    connection_ = std::move(v);
}

const std::list<dogen::codec::dia::processed_attribute>& processed_object::attributes() const {
    return attributes_;
}

std::list<dogen::codec::dia::processed_attribute>& processed_object::attributes() {
    return attributes_;
}

void processed_object::attributes(const std::list<dogen::codec::dia::processed_attribute>& v) {
    attributes_ = v;
}

void processed_object::attributes(const std::list<dogen::codec::dia::processed_attribute>&& v) {
    attributes_ = std::move(v);
}

}
