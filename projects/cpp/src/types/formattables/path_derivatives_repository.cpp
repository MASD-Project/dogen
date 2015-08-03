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
#include "dogen/cpp/types/formattables/path_derivatives_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

path_derivatives_repository::path_derivatives_repository(const std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >& path_derivatives_by_qname)
    : path_derivatives_by_qname_(path_derivatives_by_qname) { }

void path_derivatives_repository::swap(path_derivatives_repository& other) noexcept {
    using std::swap;
    swap(path_derivatives_by_qname_, other.path_derivatives_by_qname_);
}

bool path_derivatives_repository::operator==(const path_derivatives_repository& rhs) const {
    return path_derivatives_by_qname_ == rhs.path_derivatives_by_qname_;
}

path_derivatives_repository& path_derivatives_repository::operator=(path_derivatives_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >& path_derivatives_repository::path_derivatives_by_qname() const {
    return path_derivatives_by_qname_;
}

std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >& path_derivatives_repository::path_derivatives_by_qname() {
    return path_derivatives_by_qname_;
}

void path_derivatives_repository::path_derivatives_by_qname(const std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >& v) {
    path_derivatives_by_qname_ = v;
}

void path_derivatives_repository::path_derivatives_by_qname(const std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >&& v) {
    path_derivatives_by_qname_ = std::move(v);
}

} } }
