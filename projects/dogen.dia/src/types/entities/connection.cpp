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
#include "dogen.dia/types/entities/connection.hpp"

namespace dogen::dia::entities {

connection::connection(
    const std::string& handle,
    const std::string& to,
    const std::string& connection_slot)
    : handle_(handle),
      to_(to),
      connection_slot_(connection_slot) { }

void connection::swap(connection& other) noexcept {
    using std::swap;
    swap(handle_, other.handle_);
    swap(to_, other.to_);
    swap(connection_slot_, other.connection_slot_);
}

bool connection::operator==(const connection& rhs) const {
    return handle_ == rhs.handle_ &&
        to_ == rhs.to_ &&
        connection_slot_ == rhs.connection_slot_;
}

connection& connection::operator=(connection other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& connection::handle() const {
    return handle_;
}

std::string& connection::handle() {
    return handle_;
}

void connection::handle(const std::string& v) {
    handle_ = v;
}

void connection::handle(const std::string&& v) {
    handle_ = std::move(v);
}

const std::string& connection::to() const {
    return to_;
}

std::string& connection::to() {
    return to_;
}

void connection::to(const std::string& v) {
    to_ = v;
}

void connection::to(const std::string&& v) {
    to_ = std::move(v);
}

const std::string& connection::connection_slot() const {
    return connection_slot_;
}

std::string& connection::connection_slot() {
    return connection_slot_;
}

void connection::connection_slot(const std::string& v) {
    connection_slot_ = v;
}

void connection::connection_slot(const std::string&& v) {
    connection_slot_ = std::move(v);
}

}
