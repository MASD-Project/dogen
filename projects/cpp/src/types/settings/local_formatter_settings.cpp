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
#include "dogen/cpp/types/settings/local_formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

local_formatter_settings::local_formatter_settings()
    : enabled_(static_cast<bool>(0)),
      supported_(static_cast<bool>(0)),
      inclusion_delimiter_type_(static_cast<dogen::cpp::formattables::inclusion_delimiter_types>(0)) { }

local_formatter_settings::local_formatter_settings(local_formatter_settings&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      supported_(std::move(rhs.supported_)),
      inclusion_path_(std::move(rhs.inclusion_path_)),
      inclusion_delimiter_type_(std::move(rhs.inclusion_delimiter_type_)) { }

local_formatter_settings::local_formatter_settings(
    const bool enabled,
    const bool supported,
    const boost::filesystem::path& inclusion_path,
    const dogen::cpp::formattables::inclusion_delimiter_types& inclusion_delimiter_type)
    : enabled_(enabled),
      supported_(supported),
      inclusion_path_(inclusion_path),
      inclusion_delimiter_type_(inclusion_delimiter_type) { }

void local_formatter_settings::swap(local_formatter_settings& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(supported_, other.supported_);
    swap(inclusion_path_, other.inclusion_path_);
    swap(inclusion_delimiter_type_, other.inclusion_delimiter_type_);
}

bool local_formatter_settings::operator==(const local_formatter_settings& rhs) const {
    return enabled_ == rhs.enabled_ &&
        supported_ == rhs.supported_ &&
        inclusion_path_ == rhs.inclusion_path_ &&
        inclusion_delimiter_type_ == rhs.inclusion_delimiter_type_;
}

local_formatter_settings& local_formatter_settings::operator=(local_formatter_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool local_formatter_settings::enabled() const {
    return enabled_;
}

void local_formatter_settings::enabled(const bool v) {
    enabled_ = v;
}

bool local_formatter_settings::supported() const {
    return supported_;
}

void local_formatter_settings::supported(const bool v) {
    supported_ = v;
}

const boost::filesystem::path& local_formatter_settings::inclusion_path() const {
    return inclusion_path_;
}

boost::filesystem::path& local_formatter_settings::inclusion_path() {
    return inclusion_path_;
}

void local_formatter_settings::inclusion_path(const boost::filesystem::path& v) {
    inclusion_path_ = v;
}

void local_formatter_settings::inclusion_path(const boost::filesystem::path&& v) {
    inclusion_path_ = std::move(v);
}

dogen::cpp::formattables::inclusion_delimiter_types local_formatter_settings::inclusion_delimiter_type() const {
    return inclusion_delimiter_type_;
}

void local_formatter_settings::inclusion_delimiter_type(const dogen::cpp::formattables::inclusion_delimiter_types& v) {
    inclusion_delimiter_type_ = v;
}

} } }