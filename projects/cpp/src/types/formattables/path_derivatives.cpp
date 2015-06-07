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
#include "dogen/cpp/types/formattables/path_derivatives.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

path_derivatives::path_derivatives(path_derivatives&& rhs)
    : file_path_(std::move(rhs.file_path_)),
      header_guard_(std::move(rhs.header_guard_)),
      inclusion_directive_(std::move(rhs.inclusion_directive_)) { }

path_derivatives::path_derivatives(
    const boost::filesystem::path& file_path,
    const boost::optional<std::string>& header_guard,
    const boost::optional<std::string>& inclusion_directive)
    : file_path_(file_path),
      header_guard_(header_guard),
      inclusion_directive_(inclusion_directive) { }

void path_derivatives::swap(path_derivatives& other) noexcept {
    using std::swap;
    swap(file_path_, other.file_path_);
    swap(header_guard_, other.header_guard_);
    swap(inclusion_directive_, other.inclusion_directive_);
}

bool path_derivatives::operator==(const path_derivatives& rhs) const {
    return file_path_ == rhs.file_path_ &&
        header_guard_ == rhs.header_guard_ &&
        inclusion_directive_ == rhs.inclusion_directive_;
}

path_derivatives& path_derivatives::operator=(path_derivatives other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& path_derivatives::file_path() const {
    return file_path_;
}

boost::filesystem::path& path_derivatives::file_path() {
    return file_path_;
}

void path_derivatives::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void path_derivatives::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const boost::optional<std::string>& path_derivatives::header_guard() const {
    return header_guard_;
}

boost::optional<std::string>& path_derivatives::header_guard() {
    return header_guard_;
}

void path_derivatives::header_guard(const boost::optional<std::string>& v) {
    header_guard_ = v;
}

void path_derivatives::header_guard(const boost::optional<std::string>&& v) {
    header_guard_ = std::move(v);
}

const boost::optional<std::string>& path_derivatives::inclusion_directive() const {
    return inclusion_directive_;
}

boost::optional<std::string>& path_derivatives::inclusion_directive() {
    return inclusion_directive_;
}

void path_derivatives::inclusion_directive(const boost::optional<std::string>& v) {
    inclusion_directive_ = v;
}

void path_derivatives::inclusion_directive(const boost::optional<std::string>&& v) {
    inclusion_directive_ = std::move(v);
}

} } }
