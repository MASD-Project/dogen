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
#include "dogen/cpp/types/settings/local_path_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

local_path_settings::local_path_settings()
    : inclusion_required_(static_cast<bool>(0)),
      inclusion_delimiter_type_(static_cast<dogen::cpp::settings::inclusion_delimiter_types>(0)) { }

local_path_settings::local_path_settings(local_path_settings&& rhs)
    : inclusion_required_(std::move(rhs.inclusion_required_)),
      inclusion_path_(std::move(rhs.inclusion_path_)),
      inclusion_delimiter_type_(std::move(rhs.inclusion_delimiter_type_)) { }

local_path_settings::local_path_settings(
    const bool inclusion_required,
    const boost::filesystem::path& inclusion_path,
    const dogen::cpp::settings::inclusion_delimiter_types& inclusion_delimiter_type)
    : inclusion_required_(inclusion_required),
      inclusion_path_(inclusion_path),
      inclusion_delimiter_type_(inclusion_delimiter_type) { }

void local_path_settings::swap(local_path_settings& other) noexcept {
    using std::swap;
    swap(inclusion_required_, other.inclusion_required_);
    swap(inclusion_path_, other.inclusion_path_);
    swap(inclusion_delimiter_type_, other.inclusion_delimiter_type_);
}

bool local_path_settings::operator==(const local_path_settings& rhs) const {
    return inclusion_required_ == rhs.inclusion_required_ &&
        inclusion_path_ == rhs.inclusion_path_ &&
        inclusion_delimiter_type_ == rhs.inclusion_delimiter_type_;
}

local_path_settings& local_path_settings::operator=(local_path_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool local_path_settings::inclusion_required() const {
    return inclusion_required_;
}

void local_path_settings::inclusion_required(const bool v) {
    inclusion_required_ = v;
}

const boost::filesystem::path& local_path_settings::inclusion_path() const {
    return inclusion_path_;
}

boost::filesystem::path& local_path_settings::inclusion_path() {
    return inclusion_path_;
}

void local_path_settings::inclusion_path(const boost::filesystem::path& v) {
    inclusion_path_ = v;
}

void local_path_settings::inclusion_path(const boost::filesystem::path&& v) {
    inclusion_path_ = std::move(v);
}

dogen::cpp::settings::inclusion_delimiter_types local_path_settings::inclusion_delimiter_type() const {
    return inclusion_delimiter_type_;
}

void local_path_settings::inclusion_delimiter_type(const dogen::cpp::settings::inclusion_delimiter_types& v) {
    inclusion_delimiter_type_ = v;
}

} } }