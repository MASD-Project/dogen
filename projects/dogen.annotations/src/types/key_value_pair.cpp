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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen/annotations/io/value_io.hpp"
#include "dogen/annotations/types/value_visitor.hpp"
#include "dogen/annotations/types/key_value_pair.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, std::string>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->second) << "\"";
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace dogen {
namespace annotations {

key_value_pair::key_value_pair(const std::unordered_map<std::string, std::string>& content)
    : dogen::annotations::value(),
      content_(content) { }

void key_value_pair::accept(const value_visitor& v) const {
    v.visit(*this);
}

void key_value_pair::accept(value_visitor& v) const {
    v.visit(*this);
    }

void key_value_pair::accept(const value_visitor& v) {
    v.visit(*this);
}

void key_value_pair::accept(value_visitor& v) {
    v.visit(*this);
}

void key_value_pair::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::annotations::key_value_pair\"" << ", "
      << "\"__parent_0__\": ";
    dogen::annotations::value::to_stream(s);
    s << ", "
      << "\"content\": " << content_
      << " }";
}

void key_value_pair::swap(key_value_pair& other) noexcept {
    dogen::annotations::value::swap(other);

    using std::swap;
    swap(content_, other.content_);
}

bool key_value_pair::equals(const dogen::annotations::value& other) const {
    const key_value_pair* const p(dynamic_cast<const key_value_pair* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool key_value_pair::operator==(const key_value_pair& rhs) const {
    return dogen::annotations::value::compare(rhs) &&
        content_ == rhs.content_;
}

key_value_pair& key_value_pair::operator=(key_value_pair other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::string>& key_value_pair::content() const {
    return content_;
}

std::unordered_map<std::string, std::string>& key_value_pair::content() {
    return content_;
}

void key_value_pair::content(const std::unordered_map<std::string, std::string>& v) {
    content_ = v;
}

void key_value_pair::content(const std::unordered_map<std::string, std::string>&& v) {
    content_ = std::move(v);
}

} }
