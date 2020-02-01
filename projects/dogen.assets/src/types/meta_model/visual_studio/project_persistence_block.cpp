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
#include "dogen.assets/types/meta_model/visual_studio/project_persistence_block.hpp"

namespace dogen::assets::meta_model::visual_studio {

project_persistence_block::project_persistence_block(project_persistence_block&& rhs)
    : guid_(std::move(rhs.guid_)),
      name_(std::move(rhs.name_)),
      relative_path_(std::move(rhs.relative_path_)) { }

project_persistence_block::project_persistence_block(
    const std::string& guid,
    const std::string& name,
    const boost::filesystem::path& relative_path)
    : guid_(guid),
      name_(name),
      relative_path_(relative_path) { }

void project_persistence_block::swap(project_persistence_block& other) noexcept {
    using std::swap;
    swap(guid_, other.guid_);
    swap(name_, other.name_);
    swap(relative_path_, other.relative_path_);
}

bool project_persistence_block::operator==(const project_persistence_block& rhs) const {
    return guid_ == rhs.guid_ &&
        name_ == rhs.name_ &&
        relative_path_ == rhs.relative_path_;
}

project_persistence_block& project_persistence_block::operator=(project_persistence_block other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& project_persistence_block::guid() const {
    return guid_;
}

std::string& project_persistence_block::guid() {
    return guid_;
}

void project_persistence_block::guid(const std::string& v) {
    guid_ = v;
}

void project_persistence_block::guid(const std::string&& v) {
    guid_ = std::move(v);
}

const std::string& project_persistence_block::name() const {
    return name_;
}

std::string& project_persistence_block::name() {
    return name_;
}

void project_persistence_block::name(const std::string& v) {
    name_ = v;
}

void project_persistence_block::name(const std::string&& v) {
    name_ = std::move(v);
}

const boost::filesystem::path& project_persistence_block::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& project_persistence_block::relative_path() {
    return relative_path_;
}

void project_persistence_block::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void project_persistence_block::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

}
