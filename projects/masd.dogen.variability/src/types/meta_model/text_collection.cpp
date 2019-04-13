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
#include "masd.dogen.variability/io/meta_model/value_io.hpp"
#include "masd.dogen.variability/types/meta_model/value_visitor.hpp"
#include "masd.dogen.variability/types/meta_model/text_collection.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace masd::dogen::variability::meta_model {

text_collection::text_collection(const std::list<std::string>& content)
    : masd::dogen::variability::meta_model::value(),
      content_(content) { }

void text_collection::accept(const value_visitor& v) const {
    v.visit(*this);
}

void text_collection::accept(value_visitor& v) const {
    v.visit(*this);
    }

void text_collection::accept(const value_visitor& v) {
    v.visit(*this);
}

void text_collection::accept(value_visitor& v) {
    v.visit(*this);
}

void text_collection::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::variability::meta_model::text_collection\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::variability::meta_model::value::to_stream(s);
    s << ", "
      << "\"content\": " << content_
      << " }";
}

void text_collection::swap(text_collection& other) noexcept {
    masd::dogen::variability::meta_model::value::swap(other);

    using std::swap;
    swap(content_, other.content_);
}

bool text_collection::equals(const masd::dogen::variability::meta_model::value& other) const {
    const text_collection* const p(dynamic_cast<const text_collection* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool text_collection::operator==(const text_collection& rhs) const {
    return masd::dogen::variability::meta_model::value::compare(rhs) &&
        content_ == rhs.content_;
}

text_collection& text_collection::operator=(text_collection other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& text_collection::content() const {
    return content_;
}

std::list<std::string>& text_collection::content() {
    return content_;
}

void text_collection::content(const std::list<std::string>& v) {
    content_ = v;
}

void text_collection::content(const std::list<std::string>&& v) {
    content_ = std::move(v);
}

}
