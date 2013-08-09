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
#include "dogen/cpp/io/element_info_io.hpp"
#include "dogen/cpp/types/exception_info.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
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

namespace dogen {
namespace cpp {

exception_info::exception_info(
    const std::string& documentation,
    const std::string& name,
    const std::list<std::string>& namespaces)
    : dogen::cpp::element_info(documentation),
      name_(name),
      namespaces_(namespaces) { }

void exception_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::exception_info\"" << ", "
      << "\"__parent_0__\": ";
    element_info::to_stream(s);
    s << ", "
      << "\"name\": " << "\"" << tidy_up_string(name_) << "\"" << ", "
      << "\"namespaces\": " << namespaces_
      << " }";
}

void exception_info::swap(exception_info& other) noexcept {
    element_info::swap(other);

    using std::swap;
    swap(name_, other.name_);
    swap(namespaces_, other.namespaces_);
}

bool exception_info::equals(const dogen::cpp::element_info& other) const {
    const exception_info* const p(dynamic_cast<const exception_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool exception_info::operator==(const exception_info& rhs) const {
    return element_info::compare(rhs) &&
        name_ == rhs.name_ &&
        namespaces_ == rhs.namespaces_;
}

exception_info& exception_info::operator=(exception_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& exception_info::name() const {
    return name_;
}

std::string& exception_info::name() {
    return name_;
}

void exception_info::name(const std::string& v) {
    name_ = v;
}

void exception_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<std::string>& exception_info::namespaces() const {
    return namespaces_;
}

std::list<std::string>& exception_info::namespaces() {
    return namespaces_;
}

void exception_info::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void exception_info::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

} }