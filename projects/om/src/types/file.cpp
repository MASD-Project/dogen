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

file::file()
    : overwrite_(static_cast<bool>(0)) { }

file::file(file&& rhs)
    : relative_path_(std::move(rhs.relative_path_)),
      absolute_path_(std::move(rhs.absolute_path_)),
      contents_(std::move(rhs.contents_)),
      overwrite_(std::move(rhs.overwrite_)) { }

file::file(
    const boost::filesystem::path& relative_path,
    const boost::filesystem::path& absolute_path,
    const std::string& contents,
    const bool overwrite)
    : relative_path_(relative_path),
      absolute_path_(absolute_path),
      contents_(contents),
      overwrite_(overwrite) { }

void file::swap(file& other) noexcept {
    using std::swap;
    swap(relative_path_, other.relative_path_);
    swap(absolute_path_, other.absolute_path_);
    swap(contents_, other.contents_);
    swap(overwrite_, other.overwrite_);
}

bool file::operator==(const file& rhs) const {
    return relative_path_ == rhs.relative_path_ &&
        absolute_path_ == rhs.absolute_path_ &&
        contents_ == rhs.contents_ &&
        overwrite_ == rhs.overwrite_;
}

file& file::operator=(file other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& file::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& file::relative_path() {
    return relative_path_;
}

void file::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void file::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

const boost::filesystem::path& file::absolute_path() const {
    return absolute_path_;
}

boost::filesystem::path& file::absolute_path() {
    return absolute_path_;
}

void file::absolute_path(const boost::filesystem::path& v) {
    absolute_path_ = v;
}

void file::absolute_path(const boost::filesystem::path&& v) {
    absolute_path_ = std::move(v);
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

bool file::overwrite() const {
    return overwrite_;
}

void file::overwrite(const bool v) {
    overwrite_ = v;
}

} }