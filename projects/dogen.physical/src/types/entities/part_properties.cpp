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
#include "dogen.physical/types/entities/part_properties.hpp"

namespace dogen::physical::entities {

part_properties::part_properties(part_properties&& rhs)
    : meta_name_(std::move(rhs.meta_name_)),
      file_path_(std::move(rhs.file_path_)),
      relative_path_(std::move(rhs.relative_path_)),
      directory_name_(std::move(rhs.directory_name_)),
      computed_directory_name_(std::move(rhs.computed_directory_name_)) { }

part_properties::part_properties(
    const dogen::identification::entities::physical_meta_name& meta_name,
    const boost::filesystem::path& file_path,
    const boost::filesystem::path& relative_path,
    const std::string& directory_name,
    const std::string& computed_directory_name)
    : meta_name_(meta_name),
      file_path_(file_path),
      relative_path_(relative_path),
      directory_name_(directory_name),
      computed_directory_name_(computed_directory_name) { }

void part_properties::swap(part_properties& other) noexcept {
    using std::swap;
    swap(meta_name_, other.meta_name_);
    swap(file_path_, other.file_path_);
    swap(relative_path_, other.relative_path_);
    swap(directory_name_, other.directory_name_);
    swap(computed_directory_name_, other.computed_directory_name_);
}

bool part_properties::operator==(const part_properties& rhs) const {
    return meta_name_ == rhs.meta_name_ &&
        file_path_ == rhs.file_path_ &&
        relative_path_ == rhs.relative_path_ &&
        directory_name_ == rhs.directory_name_ &&
        computed_directory_name_ == rhs.computed_directory_name_;
}

part_properties& part_properties::operator=(part_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::physical_meta_name& part_properties::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::physical_meta_name& part_properties::meta_name() {
    return meta_name_;
}

void part_properties::meta_name(const dogen::identification::entities::physical_meta_name& v) {
    meta_name_ = v;
}

void part_properties::meta_name(const dogen::identification::entities::physical_meta_name&& v) {
    meta_name_ = std::move(v);
}

const boost::filesystem::path& part_properties::file_path() const {
    return file_path_;
}

boost::filesystem::path& part_properties::file_path() {
    return file_path_;
}

void part_properties::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void part_properties::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const boost::filesystem::path& part_properties::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& part_properties::relative_path() {
    return relative_path_;
}

void part_properties::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void part_properties::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

const std::string& part_properties::directory_name() const {
    return directory_name_;
}

std::string& part_properties::directory_name() {
    return directory_name_;
}

void part_properties::directory_name(const std::string& v) {
    directory_name_ = v;
}

void part_properties::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

const std::string& part_properties::computed_directory_name() const {
    return computed_directory_name_;
}

std::string& part_properties::computed_directory_name() {
    return computed_directory_name_;
}

void part_properties::computed_directory_name(const std::string& v) {
    computed_directory_name_ = v;
}

void part_properties::computed_directory_name(const std::string&& v) {
    computed_directory_name_ = std::move(v);
}

}
