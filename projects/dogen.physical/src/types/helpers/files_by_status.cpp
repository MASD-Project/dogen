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
#include "dogen.physical/types/helpers/files_by_status.hpp"

namespace dogen::physical::helpers {

files_by_status::files_by_status(
    const std::list<boost::filesystem::path>& unexpected,
    const std::list<boost::filesystem::path>& ignored)
    : unexpected_(unexpected),
      ignored_(ignored) { }

void files_by_status::swap(files_by_status& other) noexcept {
    using std::swap;
    swap(unexpected_, other.unexpected_);
    swap(ignored_, other.ignored_);
}

bool files_by_status::operator==(const files_by_status& rhs) const {
    return unexpected_ == rhs.unexpected_ &&
        ignored_ == rhs.ignored_;
}

files_by_status& files_by_status::operator=(files_by_status other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<boost::filesystem::path>& files_by_status::unexpected() const {
    return unexpected_;
}

std::list<boost::filesystem::path>& files_by_status::unexpected() {
    return unexpected_;
}

void files_by_status::unexpected(const std::list<boost::filesystem::path>& v) {
    unexpected_ = v;
}

void files_by_status::unexpected(const std::list<boost::filesystem::path>&& v) {
    unexpected_ = std::move(v);
}

const std::list<boost::filesystem::path>& files_by_status::ignored() const {
    return ignored_;
}

std::list<boost::filesystem::path>& files_by_status::ignored() {
    return ignored_;
}

void files_by_status::ignored(const std::list<boost::filesystem::path>& v) {
    ignored_ = v;
}

void files_by_status::ignored(const std::list<boost::filesystem::path>&& v) {
    ignored_ = std::move(v);
}

}
