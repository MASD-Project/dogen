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
#include "dogen/om/types/file.hpp"

namespace dogen {
namespace om {

file::file(file&& rhs)
    : full_path_(std::move(rhs.full_path_)),
      contents_(std::move(rhs.contents_)) { }

file::file(
    const boost::filesystem::path& full_path,
    const std::string& contents)
    : full_path_(full_path),
      contents_(contents) { }

void file::swap(file& other) noexcept {
    using std::swap;
    swap(full_path_, other.full_path_);
    swap(contents_, other.contents_);
}

bool file::operator==(const file& rhs) const {
    return full_path_ == rhs.full_path_ &&
        contents_ == rhs.contents_;
}

file& file::operator=(file other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& file::full_path() const {
    return full_path_;
}

boost::filesystem::path& file::full_path() {
    return full_path_;
}

void file::full_path(const boost::filesystem::path& v) {
    full_path_ = v;
}

void file::full_path(const boost::filesystem::path&& v) {
    full_path_ = std::move(v);
}

const std::string& file::contents() const {
    return contents_;
}

std::string& file::contents() {
    return contents_;
}

void file::contents(const std::string& v) {
    contents_ = v;
}

void file::contents(const std::string&& v) {
    contents_ = std::move(v);
}

} }