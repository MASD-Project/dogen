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
#include "dogen/cpp/io/formattables/file_properties_io.hpp"
#include "dogen/cpp/types/formattables/formattable.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::cpp::formattables::file_properties>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

formattable::formattable(
    const std::string& identity,
    const std::unordered_map<std::string, dogen::cpp::formattables::file_properties>& file_properties_by_formatter_name)
    : identity_(identity),
      file_properties_by_formatter_name_(file_properties_by_formatter_name) { }

void formattable::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::formattable\"" << ", "
      << "\"identity\": " << "\"" << tidy_up_string(identity_) << "\"" << ", "
      << "\"file_properties_by_formatter_name\": " << file_properties_by_formatter_name_
      << " }";
}

void formattable::swap(formattable& other) noexcept {
    using std::swap;
    swap(identity_, other.identity_);
    swap(file_properties_by_formatter_name_, other.file_properties_by_formatter_name_);
}

bool formattable::compare(const formattable& rhs) const {
    return identity_ == rhs.identity_ &&
        file_properties_by_formatter_name_ == rhs.file_properties_by_formatter_name_;
}

const std::string& formattable::identity() const {
    return identity_;
}

std::string& formattable::identity() {
    return identity_;
}

void formattable::identity(const std::string& v) {
    identity_ = v;
}

void formattable::identity(const std::string&& v) {
    identity_ = std::move(v);
}

const std::unordered_map<std::string, dogen::cpp::formattables::file_properties>& formattable::file_properties_by_formatter_name() const {
    return file_properties_by_formatter_name_;
}

std::unordered_map<std::string, dogen::cpp::formattables::file_properties>& formattable::file_properties_by_formatter_name() {
    return file_properties_by_formatter_name_;
}

void formattable::file_properties_by_formatter_name(const std::unordered_map<std::string, dogen::cpp::formattables::file_properties>& v) {
    file_properties_by_formatter_name_ = v;
}

void formattable::file_properties_by_formatter_name(const std::unordered_map<std::string, dogen::cpp::formattables::file_properties>&& v) {
    file_properties_by_formatter_name_ = std::move(v);
}

} } }