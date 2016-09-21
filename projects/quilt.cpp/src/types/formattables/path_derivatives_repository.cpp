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
#include "dogen/quilt.cpp/types/formattables/path_derivatives_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

path_derivatives_repository::path_derivatives_repository(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::quilt::cpp::formattables::path_derivatives> >& by_name)
    : by_name_(by_name) { }

void path_derivatives_repository::swap(path_derivatives_repository& other) noexcept {
    using std::swap;
    swap(by_name_, other.by_name_);
}

bool path_derivatives_repository::operator==(const path_derivatives_repository& rhs) const {
    return by_name_ == rhs.by_name_;
}

path_derivatives_repository& path_derivatives_repository::operator=(path_derivatives_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::quilt::cpp::formattables::path_derivatives> >& path_derivatives_repository::by_name() const {
    return by_name_;
}

std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::quilt::cpp::formattables::path_derivatives> >& path_derivatives_repository::by_name() {
    return by_name_;
}

void path_derivatives_repository::by_name(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::quilt::cpp::formattables::path_derivatives> >& v) {
    by_name_ = v;
}

void path_derivatives_repository::by_name(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::quilt::cpp::formattables::path_derivatives> >&& v) {
    by_name_ = std::move(v);
}

} } } }
