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
#include "dogen/om/io/odb_option_io.hpp"
#include "dogen/om/types/odb_guard_prefix_option.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace om {

odb_guard_prefix_option::odb_guard_prefix_option(
    const std::string& comment,
    const std::string& guard_prefix)
    : dogen::om::odb_option(comment),
      guard_prefix_(guard_prefix) { }

void odb_guard_prefix_option::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::odb_guard_prefix_option\"" << ", "
      << "\"__parent_0__\": ";
    odb_option::to_stream(s);
    s << ", "
      << "\"guard_prefix\": " << "\"" << tidy_up_string(guard_prefix_) << "\""
      << " }";
}

void odb_guard_prefix_option::swap(odb_guard_prefix_option& other) noexcept {
    odb_option::swap(other);

    using std::swap;
    swap(guard_prefix_, other.guard_prefix_);
}

bool odb_guard_prefix_option::equals(const dogen::om::odb_option& other) const {
    const odb_guard_prefix_option* const p(dynamic_cast<const odb_guard_prefix_option* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool odb_guard_prefix_option::operator==(const odb_guard_prefix_option& rhs) const {
    return odb_option::compare(rhs) &&
        guard_prefix_ == rhs.guard_prefix_;
}

odb_guard_prefix_option& odb_guard_prefix_option::operator=(odb_guard_prefix_option other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& odb_guard_prefix_option::guard_prefix() const {
    return guard_prefix_;
}

std::string& odb_guard_prefix_option::guard_prefix() {
    return guard_prefix_;
}

void odb_guard_prefix_option::guard_prefix(const std::string& v) {
    guard_prefix_ = v;
}

void odb_guard_prefix_option::guard_prefix(const std::string&& v) {
    guard_prefix_ = std::move(v);
}

} }