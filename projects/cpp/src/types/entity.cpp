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
#include <boost/algorithm/string.hpp>
#include <ostream>
#include "dogen/cpp/types/entity.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace cpp {

entity::entity(const std::string& documentation)
    : documentation_(documentation) { }

void entity::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::entity\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\""
      << " }";
}

void entity::swap(entity& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
}

bool entity::compare(const entity& rhs) const {
    return documentation_ == rhs.documentation_;
}

const std::string& entity::documentation() const {
    return documentation_;
}

std::string& entity::documentation() {
    return documentation_;
}

void entity::documentation(const std::string& v) {
    documentation_ = v;
}

void entity::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

} }