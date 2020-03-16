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
#include "dogen.physical/types/entities/paths.hpp"

namespace dogen::physical::entities {

paths::paths(paths&& rhs)
    : absolute_(std::move(rhs.absolute_)),
      relative_(std::move(rhs.relative_)) { }

paths::paths(
    const boost::filesystem::path& absolute,
    const boost::filesystem::path& relative)
    : absolute_(absolute),
      relative_(relative) { }

void paths::swap(paths& other) noexcept {
    using std::swap;
    swap(absolute_, other.absolute_);
    swap(relative_, other.relative_);
}

bool paths::operator==(const paths& rhs) const {
    return absolute_ == rhs.absolute_ &&
        relative_ == rhs.relative_;
}

paths& paths::operator=(paths other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& paths::absolute() const {
    return absolute_;
}

boost::filesystem::path& paths::absolute() {
    return absolute_;
}

void paths::absolute(const boost::filesystem::path& v) {
    absolute_ = v;
}

void paths::absolute(const boost::filesystem::path&& v) {
    absolute_ = std::move(v);
}

const boost::filesystem::path& paths::relative() const {
    return relative_;
}

boost::filesystem::path& paths::relative() {
    return relative_;
}

void paths::relative(const boost::filesystem::path& v) {
    relative_ = v;
}

void paths::relative(const boost::filesystem::path&& v) {
    relative_ = std::move(v);
}

}
