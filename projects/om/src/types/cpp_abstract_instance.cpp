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
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/io/cpp_typeref_io.hpp"
#include "dogen/om/io/doxygen_command_io.hpp"
#include "dogen/om/types/cpp_abstract_instance.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::om::doxygen_command>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace om {

cpp_abstract_instance::cpp_abstract_instance(
    const std::string& name,
    const std::list<dogen::om::doxygen_command>& commands,
    const dogen::om::cpp_typeref& type,
    const std::string& default_value)
    : dogen::om::cpp_feature(name),
      commands_(commands),
      type_(type),
      default_value_(default_value) { }

void cpp_abstract_instance::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_abstract_instance\"" << ", "
      << "\"__parent_0__\": ";
    cpp_feature::to_stream(s);
    s << ", "
      << "\"commands\": " << commands_ << ", "
      << "\"type\": " << type_ << ", "
      << "\"default_value\": " << "\"" << tidy_up_string(default_value_) << "\""
      << " }";
}

void cpp_abstract_instance::swap(cpp_abstract_instance& other) noexcept {
    cpp_feature::swap(other);

    using std::swap;
    swap(commands_, other.commands_);
    swap(type_, other.type_);
    swap(default_value_, other.default_value_);
}

bool cpp_abstract_instance::compare(const cpp_abstract_instance& rhs) const {
    return cpp_feature::compare(rhs) &&
        commands_ == rhs.commands_ &&
        type_ == rhs.type_ &&
        default_value_ == rhs.default_value_;
}

const std::list<dogen::om::doxygen_command>& cpp_abstract_instance::commands() const {
    return commands_;
}

std::list<dogen::om::doxygen_command>& cpp_abstract_instance::commands() {
    return commands_;
}

void cpp_abstract_instance::commands(const std::list<dogen::om::doxygen_command>& v) {
    commands_ = v;
}

void cpp_abstract_instance::commands(const std::list<dogen::om::doxygen_command>&& v) {
    commands_ = std::move(v);
}

const dogen::om::cpp_typeref& cpp_abstract_instance::type() const {
    return type_;
}

dogen::om::cpp_typeref& cpp_abstract_instance::type() {
    return type_;
}

void cpp_abstract_instance::type(const dogen::om::cpp_typeref& v) {
    type_ = v;
}

void cpp_abstract_instance::type(const dogen::om::cpp_typeref&& v) {
    type_ = std::move(v);
}

const std::string& cpp_abstract_instance::default_value() const {
    return default_value_;
}

std::string& cpp_abstract_instance::default_value() {
    return default_value_;
}

void cpp_abstract_instance::default_value(const std::string& v) {
    default_value_ = v;
}

void cpp_abstract_instance::default_value(const std::string&& v) {
    default_value_ = std::move(v);
}

} }