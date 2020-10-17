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
#include "dogen.physical/types/entities/path_properties.hpp"

namespace dogen::physical::entities {

path_properties::path_properties(path_properties&& rhs)
    : file_path_(std::move(rhs.file_path_)) { }

path_properties::path_properties(const boost::filesystem::path& file_path)
    : file_path_(file_path) { }

void path_properties::swap(path_properties& other) noexcept {
    using std::swap;
    swap(file_path_, other.file_path_);
}

bool path_properties::operator==(const path_properties& rhs) const {
    return file_path_ == rhs.file_path_;
}

path_properties& path_properties::operator=(path_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& path_properties::file_path() const {
    return file_path_;
}

boost::filesystem::path& path_properties::file_path() {
    return file_path_;
}

void path_properties::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void path_properties::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

}
