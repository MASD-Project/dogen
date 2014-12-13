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
#include <ostream>
#include "dogen/dynamic/io/boolean_io.hpp"
#include "dogen/dynamic/io/value_io.hpp"
#include "dogen/dynamic/types/boolean_collection.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::dynamic::boolean>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace dynamic {

boolean_collection::boolean_collection(
    const dogen::dynamic::value_types& type,
    const std::list<dogen::dynamic::boolean>& content)
    : dogen::dynamic::value(type),
      content_(content) { }

void boolean_collection::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::dynamic::boolean_collection\"" << ", "
      << "\"__parent_0__\": ";
    value::to_stream(s);
    s << ", "
      << "\"content\": " << content_
      << " }";
}

void boolean_collection::swap(boolean_collection& other) noexcept {
    value::swap(other);

    using std::swap;
    swap(content_, other.content_);
}

bool boolean_collection::equals(const dogen::dynamic::value& other) const {
    const boolean_collection* const p(dynamic_cast<const boolean_collection* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool boolean_collection::operator==(const boolean_collection& rhs) const {
    return value::compare(rhs) &&
        content_ == rhs.content_;
}

boolean_collection& boolean_collection::operator=(boolean_collection other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::dynamic::boolean>& boolean_collection::content() const {
    return content_;
}

std::list<dogen::dynamic::boolean>& boolean_collection::content() {
    return content_;
}

void boolean_collection::content(const std::list<dogen::dynamic::boolean>& v) {
    content_ = v;
}

void boolean_collection::content(const std::list<dogen::dynamic::boolean>&& v) {
    content_ = std::move(v);
}

} }