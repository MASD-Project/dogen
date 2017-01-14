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
#include "dogen/upsilon/types/type_information.hpp"

namespace dogen {
namespace upsilon {

type_information::type_information(type_information&& rhs)
    : entries_(std::move(rhs.entries_)),
      file_path_(std::move(rhs.file_path_)) { }

type_information::type_information(
    const std::vector<dogen::upsilon::type_information_entry>& entries,
    const boost::filesystem::path& file_path)
    : entries_(entries),
      file_path_(file_path) { }

void type_information::swap(type_information& other) noexcept {
    using std::swap;
    swap(entries_, other.entries_);
    swap(file_path_, other.file_path_);
}

bool type_information::operator==(const type_information& rhs) const {
    return entries_ == rhs.entries_ &&
        file_path_ == rhs.file_path_;
}

type_information& type_information::operator=(type_information other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<dogen::upsilon::type_information_entry>& type_information::entries() const {
    return entries_;
}

std::vector<dogen::upsilon::type_information_entry>& type_information::entries() {
    return entries_;
}

void type_information::entries(const std::vector<dogen::upsilon::type_information_entry>& v) {
    entries_ = v;
}

void type_information::entries(const std::vector<dogen::upsilon::type_information_entry>&& v) {
    entries_ = std::move(v);
}

const boost::filesystem::path& type_information::file_path() const {
    return file_path_;
}

boost::filesystem::path& type_information::file_path() {
    return file_path_;
}

void type_information::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void type_information::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

} }
