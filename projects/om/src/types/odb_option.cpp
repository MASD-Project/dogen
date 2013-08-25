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
#include "dogen/om/types/odb_option.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace om {

odb_option::odb_option(const std::string& comment)
    : comment_(comment) { }

void odb_option::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::odb_option\"" << ", "
      << "\"comment\": " << "\"" << tidy_up_string(comment_) << "\""
      << " }";
}

void odb_option::swap(odb_option& other) noexcept {
    using std::swap;
    swap(comment_, other.comment_);
}

bool odb_option::compare(const odb_option& rhs) const {
    return comment_ == rhs.comment_;
}

const std::string& odb_option::comment() const {
    return comment_;
}

std::string& odb_option::comment() {
    return comment_;
}

void odb_option::comment(const std::string& v) {
    comment_ = v;
}

void odb_option::comment(const std::string&& v) {
    comment_ = std::move(v);
}

} }