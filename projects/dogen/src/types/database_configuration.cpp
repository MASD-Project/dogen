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
#include "dogen/types/database_configuration.hpp"

namespace dogen {

database_configuration::database_configuration()
    : port_(static_cast<unsigned int>(0)),
      engine_(static_cast<dogen::database_engine>(0)),
      generate_schema_(static_cast<bool>(0)) { }

database_configuration::database_configuration(
    const std::string& host,
    const unsigned int port,
    const std::string& name,
    const std::string& user,
    const std::string& password,
    const dogen::database_engine engine,
    const bool generate_schema)
    : host_(host),
      port_(port),
      name_(name),
      user_(user),
      password_(password),
      engine_(engine),
      generate_schema_(generate_schema) { }

void database_configuration::swap(database_configuration& other) noexcept {
    using std::swap;
    swap(host_, other.host_);
    swap(port_, other.port_);
    swap(name_, other.name_);
    swap(user_, other.user_);
    swap(password_, other.password_);
    swap(engine_, other.engine_);
    swap(generate_schema_, other.generate_schema_);
}

bool database_configuration::operator==(const database_configuration& rhs) const {
    return host_ == rhs.host_ &&
        port_ == rhs.port_ &&
        name_ == rhs.name_ &&
        user_ == rhs.user_ &&
        password_ == rhs.password_ &&
        engine_ == rhs.engine_ &&
        generate_schema_ == rhs.generate_schema_;
}

database_configuration& database_configuration::operator=(database_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& database_configuration::host() const {
    return host_;
}

std::string& database_configuration::host() {
    return host_;
}

void database_configuration::host(const std::string& v) {
    host_ = v;
}

void database_configuration::host(const std::string&& v) {
    host_ = std::move(v);
}

unsigned int database_configuration::port() const {
    return port_;
}

void database_configuration::port(const unsigned int v) {
    port_ = v;
}

const std::string& database_configuration::name() const {
    return name_;
}

std::string& database_configuration::name() {
    return name_;
}

void database_configuration::name(const std::string& v) {
    name_ = v;
}

void database_configuration::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& database_configuration::user() const {
    return user_;
}

std::string& database_configuration::user() {
    return user_;
}

void database_configuration::user(const std::string& v) {
    user_ = v;
}

void database_configuration::user(const std::string&& v) {
    user_ = std::move(v);
}

const std::string& database_configuration::password() const {
    return password_;
}

std::string& database_configuration::password() {
    return password_;
}

void database_configuration::password(const std::string& v) {
    password_ = v;
}

void database_configuration::password(const std::string&& v) {
    password_ = std::move(v);
}

dogen::database_engine database_configuration::engine() const {
    return engine_;
}

void database_configuration::engine(const dogen::database_engine v) {
    engine_ = v;
}

bool database_configuration::generate_schema() const {
    return generate_schema_;
}

void database_configuration::generate_schema(const bool v) {
    generate_schema_ = v;
}

}
