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
#include "dogen.physical/types/entities/backend_properties.hpp"

namespace dogen::physical::entities {

backend_properties::backend_properties()
    : enabled_(static_cast<bool>(0)),
      enable_backend_directories_(static_cast<bool>(0)) { }

backend_properties::backend_properties(
    const dogen::identification::entities::physical_meta_name& meta_name,
    const bool enabled,
    const std::string& technical_space_version,
    const std::string& directory,
    const bool enable_backend_directories)
    : meta_name_(meta_name),
      enabled_(enabled),
      technical_space_version_(technical_space_version),
      directory_(directory),
      enable_backend_directories_(enable_backend_directories) { }

void backend_properties::swap(backend_properties& other) noexcept {
    using std::swap;
    swap(meta_name_, other.meta_name_);
    swap(enabled_, other.enabled_);
    swap(technical_space_version_, other.technical_space_version_);
    swap(directory_, other.directory_);
    swap(enable_backend_directories_, other.enable_backend_directories_);
}

bool backend_properties::operator==(const backend_properties& rhs) const {
    return meta_name_ == rhs.meta_name_ &&
        enabled_ == rhs.enabled_ &&
        technical_space_version_ == rhs.technical_space_version_ &&
        directory_ == rhs.directory_ &&
        enable_backend_directories_ == rhs.enable_backend_directories_;
}

backend_properties& backend_properties::operator=(backend_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::physical_meta_name& backend_properties::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::physical_meta_name& backend_properties::meta_name() {
    return meta_name_;
}

void backend_properties::meta_name(const dogen::identification::entities::physical_meta_name& v) {
    meta_name_ = v;
}

void backend_properties::meta_name(const dogen::identification::entities::physical_meta_name&& v) {
    meta_name_ = std::move(v);
}

bool backend_properties::enabled() const {
    return enabled_;
}

void backend_properties::enabled(const bool v) {
    enabled_ = v;
}

const std::string& backend_properties::technical_space_version() const {
    return technical_space_version_;
}

std::string& backend_properties::technical_space_version() {
    return technical_space_version_;
}

void backend_properties::technical_space_version(const std::string& v) {
    technical_space_version_ = v;
}

void backend_properties::technical_space_version(const std::string&& v) {
    technical_space_version_ = std::move(v);
}

const std::string& backend_properties::directory() const {
    return directory_;
}

std::string& backend_properties::directory() {
    return directory_;
}

void backend_properties::directory(const std::string& v) {
    directory_ = v;
}

void backend_properties::directory(const std::string&& v) {
    directory_ = std::move(v);
}

bool backend_properties::enable_backend_directories() const {
    return enable_backend_directories_;
}

void backend_properties::enable_backend_directories(const bool v) {
    enable_backend_directories_ = v;
}

}
