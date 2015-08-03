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
#include "dogen/cpp/types/formattables/formatter_properties_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

formatter_properties_repository::formatter_properties_repository(const std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties> >& formatter_properties_by_qname)
    : formatter_properties_by_qname_(formatter_properties_by_qname) { }

void formatter_properties_repository::swap(formatter_properties_repository& other) noexcept {
    using std::swap;
    swap(formatter_properties_by_qname_, other.formatter_properties_by_qname_);
}

bool formatter_properties_repository::operator==(const formatter_properties_repository& rhs) const {
    return formatter_properties_by_qname_ == rhs.formatter_properties_by_qname_;
}

formatter_properties_repository& formatter_properties_repository::operator=(formatter_properties_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties> >& formatter_properties_repository::formatter_properties_by_qname() const {
    return formatter_properties_by_qname_;
}

std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties> >& formatter_properties_repository::formatter_properties_by_qname() {
    return formatter_properties_by_qname_;
}

void formatter_properties_repository::formatter_properties_by_qname(const std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties> >& v) {
    formatter_properties_by_qname_ = v;
}

void formatter_properties_repository::formatter_properties_by_qname(const std::unordered_map<dogen::tack::qname, std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties> >&& v) {
    formatter_properties_by_qname_ = std::move(v);
}

} } }
