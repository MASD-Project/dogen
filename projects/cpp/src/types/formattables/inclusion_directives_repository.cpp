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
#include "dogen/cpp/types/formattables/inclusion_directives_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

inclusion_directives_repository::inclusion_directives_repository(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::string> >& inclusion_directives_by_name)
    : inclusion_directives_by_name_(inclusion_directives_by_name) { }

void inclusion_directives_repository::swap(inclusion_directives_repository& other) noexcept {
    using std::swap;
    swap(inclusion_directives_by_name_, other.inclusion_directives_by_name_);
}

bool inclusion_directives_repository::operator==(const inclusion_directives_repository& rhs) const {
    return inclusion_directives_by_name_ == rhs.inclusion_directives_by_name_;
}

inclusion_directives_repository& inclusion_directives_repository::operator=(inclusion_directives_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::string> >& inclusion_directives_repository::inclusion_directives_by_name() const {
    return inclusion_directives_by_name_;
}

std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::string> >& inclusion_directives_repository::inclusion_directives_by_name() {
    return inclusion_directives_by_name_;
}

void inclusion_directives_repository::inclusion_directives_by_name(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::string> >& v) {
    inclusion_directives_by_name_ = v;
}

void inclusion_directives_repository::inclusion_directives_by_name(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::string> >&& v) {
    inclusion_directives_by_name_ = std::move(v);
}

} } }
