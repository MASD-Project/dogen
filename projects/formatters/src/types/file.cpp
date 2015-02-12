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
#include "dogen/formatters/types/file.hpp"

namespace dogen {
namespace formatters {

file::file()
    : overwrite_(static_cast<bool>(0)) { }

file::file(file&& rhs)
    : path_(std::move(rhs.path_)),
      content_(std::move(rhs.content_)),
      overwrite_(std::move(rhs.overwrite_)) { }

file::file(
    const boost::filesystem::path& path,
    const std::string& content,
    const bool overwrite)
    : path_(path),
      content_(content),
      overwrite_(overwrite) { }

void file::swap(file& other) noexcept {
    using std::swap;
    swap(path_, other.path_);
    swap(content_, other.content_);
    swap(overwrite_, other.overwrite_);
}

bool file::operator==(const file& rhs) const {
    return path_ == rhs.path_ &&
        content_ == rhs.content_ &&
        overwrite_ == rhs.overwrite_;
}

file& file::operator=(file other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& file::path() const {
    return path_;
}

boost::filesystem::path& file::path() {
    return path_;
}

void file::path(const boost::filesystem::path& v) {
    path_ = v;
}

void file::path(const boost::filesystem::path&& v) {
    path_ = std::move(v);
}

const std::string& file::content() const {
    return content_;
}

std::string& file::content() {
    return content_;
}

void file::content(const std::string& v) {
    content_ = v;
}

void file::content(const std::string&& v) {
    content_ = std::move(v);
}

bool file::overwrite() const {
    return overwrite_;
}

void file::overwrite(const bool v) {
    overwrite_ = v;
}

} }