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
#include "dogen/cpp/types/settings/directory_names_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

directory_names_settings::directory_names_settings(
    const std::string& source_directory_name,
    const std::string& include_directory_name)
    : source_directory_name_(source_directory_name),
      include_directory_name_(include_directory_name) { }

void directory_names_settings::swap(directory_names_settings& other) noexcept {
    using std::swap;
    swap(source_directory_name_, other.source_directory_name_);
    swap(include_directory_name_, other.include_directory_name_);
}

bool directory_names_settings::operator==(const directory_names_settings& rhs) const {
    return source_directory_name_ == rhs.source_directory_name_ &&
        include_directory_name_ == rhs.include_directory_name_;
}

directory_names_settings& directory_names_settings::operator=(directory_names_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& directory_names_settings::source_directory_name() const {
    return source_directory_name_;
}

std::string& directory_names_settings::source_directory_name() {
    return source_directory_name_;
}

void directory_names_settings::source_directory_name(const std::string& v) {
    source_directory_name_ = v;
}

void directory_names_settings::source_directory_name(const std::string&& v) {
    source_directory_name_ = std::move(v);
}

const std::string& directory_names_settings::include_directory_name() const {
    return include_directory_name_;
}

std::string& directory_names_settings::include_directory_name() {
    return include_directory_name_;
}

void directory_names_settings::include_directory_name(const std::string& v) {
    include_directory_name_ = v;
}

void directory_names_settings::include_directory_name(const std::string&& v) {
    include_directory_name_ = std::move(v);
}

} } }
