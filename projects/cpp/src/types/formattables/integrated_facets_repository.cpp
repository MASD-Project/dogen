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
#include "dogen/cpp/types/formattables/integrated_facets_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

integrated_facets_repository::integrated_facets_repository(const std::unordered_map<std::string, std::unordered_set<std::string> >& integrated_facets_by_formatter_name)
    : integrated_facets_by_formatter_name_(integrated_facets_by_formatter_name) { }

void integrated_facets_repository::swap(integrated_facets_repository& other) noexcept {
    using std::swap;
    swap(integrated_facets_by_formatter_name_, other.integrated_facets_by_formatter_name_);
}

bool integrated_facets_repository::operator==(const integrated_facets_repository& rhs) const {
    return integrated_facets_by_formatter_name_ == rhs.integrated_facets_by_formatter_name_;
}

integrated_facets_repository& integrated_facets_repository::operator=(integrated_facets_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::unordered_set<std::string> >& integrated_facets_repository::integrated_facets_by_formatter_name() const {
    return integrated_facets_by_formatter_name_;
}

std::unordered_map<std::string, std::unordered_set<std::string> >& integrated_facets_repository::integrated_facets_by_formatter_name() {
    return integrated_facets_by_formatter_name_;
}

void integrated_facets_repository::integrated_facets_by_formatter_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v) {
    integrated_facets_by_formatter_name_ = v;
}

void integrated_facets_repository::integrated_facets_by_formatter_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v) {
    integrated_facets_by_formatter_name_ = std::move(v);
}

} } }