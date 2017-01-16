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
#include "dogen/upsilon/types/primitive.hpp"
#include "dogen/upsilon/types/type_visitor.hpp"
#include "dogen/upsilon/io/intrinsic_types_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace upsilon {

primitive::primitive()
    : intrinsic_(static_cast<dogen::upsilon::intrinsic_types>(0)) { }

primitive::primitive(
    const dogen::upsilon::name& name,
    const dogen::upsilon::name& extends,
    const std::string& comment,
    const std::vector<std::string>& tag_refs,
    const std::string& pof_id,
    const dogen::upsilon::intrinsic_types intrinsic,
    const std::string& default_value)
    : dogen::upsilon::type(
      name,
      extends,
      comment,
      tag_refs,
      pof_id),
      intrinsic_(intrinsic),
      default_value_(default_value) { }

void primitive::accept(const type_visitor& v) const {
    v.visit(*this);
}

void primitive::accept(type_visitor& v) const {
    v.visit(*this);
    }

void primitive::accept(const type_visitor& v) {
    v.visit(*this);
}

void primitive::accept(type_visitor& v) {
    v.visit(*this);
}

void primitive::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::upsilon::primitive\"" << ", "
      << "\"__parent_0__\": ";
    dogen::upsilon::type::to_stream(s);
    s << ", "
      << "\"intrinsic\": " << intrinsic_ << ", "
      << "\"default_value\": " << "\"" << tidy_up_string(default_value_) << "\""
      << " }";
}

void primitive::swap(primitive& other) noexcept {
    dogen::upsilon::type::swap(other);

    using std::swap;
    swap(intrinsic_, other.intrinsic_);
    swap(default_value_, other.default_value_);
}

bool primitive::equals(const dogen::upsilon::type& other) const {
    const primitive* const p(dynamic_cast<const primitive* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool primitive::operator==(const primitive& rhs) const {
    return dogen::upsilon::type::compare(rhs) &&
        intrinsic_ == rhs.intrinsic_ &&
        default_value_ == rhs.default_value_;
}

primitive& primitive::operator=(primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::upsilon::intrinsic_types primitive::intrinsic() const {
    return intrinsic_;
}

void primitive::intrinsic(const dogen::upsilon::intrinsic_types v) {
    intrinsic_ = v;
}

const std::string& primitive::default_value() const {
    return default_value_;
}

std::string& primitive::default_value() {
    return default_value_;
}

void primitive::default_value(const std::string& v) {
    default_value_ = v;
}

void primitive::default_value(const std::string&& v) {
    default_value_ = std::move(v);
}

} }
