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
#include "dogen/dynamic/schema/io/value_io.hpp"
#include "dogen/dynamic/schema/types/text.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace dynamic {
namespace schema {

text::text(const std::string& content)
    : dogen::dynamic::schema::value(),
      content_(content) { }

void text::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::dynamic::schema::text\"" << ", "
      << "\"__parent_0__\": ";
    value::to_stream(s);
    s << ", "
      << "\"content\": " << "\"" << tidy_up_string(content_) << "\""
      << " }";
}

void text::swap(text& other) noexcept {
    value::swap(other);

    using std::swap;
    swap(content_, other.content_);
}

bool text::equals(const dogen::dynamic::schema::value& other) const {
    const text* const p(dynamic_cast<const text* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool text::operator==(const text& rhs) const {
    return value::compare(rhs) &&
        content_ == rhs.content_;
}

text& text::operator=(text other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& text::content() const {
    return content_;
}

std::string& text::content() {
    return content_;
}

void text::content(const std::string& v) {
    content_ = v;
}

void text::content(const std::string&& v) {
    content_ = std::move(v);
}

} } }