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
#include "dogen/cpp/types/formattables/file_properties.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

file_properties::file_properties(file_properties&& rhs)
    : file_path_(std::move(rhs.file_path_)),
      inclusion_(std::move(rhs.inclusion_)) { }

file_properties::file_properties(
    const boost::filesystem::path& file_path,
    const boost::optional<dogen::cpp::formattables::inclusion>& inclusion)
    : file_path_(file_path),
      inclusion_(inclusion) { }

void file_properties::swap(file_properties& other) noexcept {
    using std::swap;
    swap(file_path_, other.file_path_);
    swap(inclusion_, other.inclusion_);
}

bool file_properties::operator==(const file_properties& rhs) const {
    return file_path_ == rhs.file_path_ &&
        inclusion_ == rhs.inclusion_;
}

file_properties& file_properties::operator=(file_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& file_properties::file_path() const {
    return file_path_;
}

boost::filesystem::path& file_properties::file_path() {
    return file_path_;
}

void file_properties::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void file_properties::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const boost::optional<dogen::cpp::formattables::inclusion>& file_properties::inclusion() const {
    return inclusion_;
}

boost::optional<dogen::cpp::formattables::inclusion>& file_properties::inclusion() {
    return inclusion_;
}

void file_properties::inclusion(const boost::optional<dogen::cpp::formattables::inclusion>& v) {
    inclusion_ = v;
}

void file_properties::inclusion(const boost::optional<dogen::cpp::formattables::inclusion>&& v) {
    inclusion_ = std::move(v);
}

} } }