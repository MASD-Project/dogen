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
#include "dogen/upsilon/io/type_io.hpp"
#include "dogen/upsilon/types/collection.hpp"
#include "dogen/upsilon/types/type_visitor.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace upsilon {

collection::collection(
    const std::string& name,
    const std::string& extends,
    const std::string& comment,
    const std::list<std::string>& tag_refs,
    const std::string& pof_id,
    const std::string& type_name)
    : dogen::upsilon::type(
      name,
      extends,
      comment,
      tag_refs,
      pof_id),
      type_name_(type_name) { }

void collection::accept(const type_visitor& v) const {
    v.visit(*this);
}

void collection::accept(type_visitor& v) const {
    v.visit(*this);
    }

void collection::accept(const type_visitor& v) {
    v.visit(*this);
}

void collection::accept(type_visitor& v) {
    v.visit(*this);
}

void collection::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::upsilon::collection\"" << ", "
      << "\"__parent_0__\": ";
    dogen::upsilon::type::to_stream(s);
    s << ", "
      << "\"type_name\": " << "\"" << tidy_up_string(type_name_) << "\""
      << " }";
}

void collection::swap(collection& other) noexcept {
    dogen::upsilon::type::swap(other);

    using std::swap;
    swap(type_name_, other.type_name_);
}

bool collection::equals(const dogen::upsilon::type& other) const {
    const collection* const p(dynamic_cast<const collection* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool collection::operator==(const collection& rhs) const {
    return dogen::upsilon::type::compare(rhs) &&
        type_name_ == rhs.type_name_;
}

collection& collection::operator=(collection other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& collection::type_name() const {
    return type_name_;
}

std::string& collection::type_name() {
    return type_name_;
}

void collection::type_name(const std::string& v) {
    type_name_ = v;
}

void collection::type_name(const std::string&& v) {
    type_name_ = std::move(v);
}

} }
