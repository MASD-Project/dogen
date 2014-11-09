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
#include "dogen/cpp/types/path_spec_details.hpp"

namespace dogen {
namespace cpp {

path_spec_details::path_spec_details(path_spec_details&& rhs)
    : relative_path_(std::move(rhs.relative_path_)),
      includes_(std::move(rhs.includes_)) { }

path_spec_details::path_spec_details(
    const boost::filesystem::path& relative_path,
    const dogen::cpp::includes& includes)
    : relative_path_(relative_path),
      includes_(includes) { }

void path_spec_details::swap(path_spec_details& other) noexcept {
    using std::swap;
    swap(relative_path_, other.relative_path_);
    swap(includes_, other.includes_);
}

bool path_spec_details::operator==(const path_spec_details& rhs) const {
    return relative_path_ == rhs.relative_path_ &&
        includes_ == rhs.includes_;
}

path_spec_details& path_spec_details::operator=(path_spec_details other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& path_spec_details::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& path_spec_details::relative_path() {
    return relative_path_;
}

void path_spec_details::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void path_spec_details::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

const dogen::cpp::includes& path_spec_details::includes() const {
    return includes_;
}

dogen::cpp::includes& path_spec_details::includes() {
    return includes_;
}

void path_spec_details::includes(const dogen::cpp::includes& v) {
    includes_ = v;
}

void path_spec_details::includes(const dogen::cpp::includes&& v) {
    includes_ = std::move(v);
}

} }