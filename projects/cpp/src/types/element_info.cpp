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
#include "dogen/cpp/types/element_info.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace cpp {

element_info::element_info(const std::string& documentation)
    : documentation_(documentation) { }

void element_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::element_info\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\""
      << " }";
}

void element_info::swap(element_info& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
}

bool element_info::compare(const element_info& rhs) const {
    return documentation_ == rhs.documentation_;
}

const std::string& element_info::documentation() const {
    return documentation_;
}

std::string& element_info::documentation() {
    return documentation_;
}

void element_info::documentation(const std::string& v) {
    documentation_ = v;
}

void element_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

} }