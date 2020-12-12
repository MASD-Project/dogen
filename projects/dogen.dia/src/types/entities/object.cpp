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
#include "dogen.dia/types/entities/object.hpp"

namespace dogen::dia::entities {

object::object()
    : version_(static_cast<int>(0)) { }

object::object(object&& rhs)
    : id_(std::move(rhs.id_)),
      type_(std::move(rhs.type_)),
      version_(std::move(rhs.version_)),
      connections_(std::move(rhs.connections_)),
      child_node_(std::move(rhs.child_node_)),
      attributes_(std::move(rhs.attributes_)) { }

object::object(
    const std::string& id,
    const std::string& type,
    const int version,
    const std::vector<dogen::dia::entities::connection>& connections,
    const boost::optional<dogen::dia::entities::child_node>& child_node,
    const std::vector<dogen::dia::entities::attribute>& attributes)
    : id_(id),
      type_(type),
      version_(version),
      connections_(connections),
      child_node_(child_node),
      attributes_(attributes) { }

void object::swap(object& other) noexcept {
    using std::swap;
    swap(id_, other.id_);
    swap(type_, other.type_);
    swap(version_, other.version_);
    swap(connections_, other.connections_);
    swap(child_node_, other.child_node_);
    swap(attributes_, other.attributes_);
}

bool object::operator==(const object& rhs) const {
    return id_ == rhs.id_ &&
        type_ == rhs.type_ &&
        version_ == rhs.version_ &&
        connections_ == rhs.connections_ &&
        child_node_ == rhs.child_node_ &&
        attributes_ == rhs.attributes_;
}

object& object::operator=(object other) {
    using std::swap;
    swap(*this, other);
    return *this;
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

const std::string& object::type() const {
    return type_;
}

std::string& object::type() {
    return type_;
}

void object::type(const std::string& v) {
    type_ = v;
}

void object::type(const std::string&& v) {
    type_ = std::move(v);
}

int object::version() const {
    return version_;
}

void object::version(const int v) {
    version_ = v;
}

const std::vector<dogen::dia::entities::connection>& object::connections() const {
    return connections_;
}

std::vector<dogen::dia::entities::connection>& object::connections() {
    return connections_;
}

void object::connections(const std::vector<dogen::dia::entities::connection>& v) {
    connections_ = v;
}

void object::connections(const std::vector<dogen::dia::entities::connection>&& v) {
    connections_ = std::move(v);
}

const boost::optional<dogen::dia::entities::child_node>& object::child_node() const {
    return child_node_;
}

boost::optional<dogen::dia::entities::child_node>& object::child_node() {
    return child_node_;
}

void object::child_node(const boost::optional<dogen::dia::entities::child_node>& v) {
    child_node_ = v;
}

void object::child_node(const boost::optional<dogen::dia::entities::child_node>&& v) {
    child_node_ = std::move(v);
}

const std::vector<dogen::dia::entities::attribute>& object::attributes() const {
    return attributes_;
}

std::vector<dogen::dia::entities::attribute>& object::attributes() {
    return attributes_;
}

void object::attributes(const std::vector<dogen::dia::entities::attribute>& v) {
    attributes_ = v;
}

void object::attributes(const std::vector<dogen::dia::entities::attribute>&& v) {
    attributes_ = std::move(v);
}

}
