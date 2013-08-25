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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/om/io/cpp_argument_io.hpp"
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/io/cpp_instance_typeref_io.hpp"
#include "dogen/om/io/cpp_representation_types_io.hpp"
#include "dogen/om/io/doxygen_command_io.hpp"
#include "dogen/om/types/cpp_abstract_function.hpp"

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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::om::cpp_argument>& v) {
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
namespace om {

cpp_abstract_function::cpp_abstract_function()
    : representation_type_(static_cast<dogen::om::cpp_representation_types>(0)),
      is_inline_(static_cast<bool>(0)),
      is_friend_(static_cast<bool>(0)) { }

cpp_abstract_function::cpp_abstract_function(
    const std::string& name,
    const std::list<dogen::om::doxygen_command>& commands,
    const dogen::om::cpp_representation_types& representation_type,
    const bool is_inline,
    const dogen::om::cpp_instance_typeref& return_type,
    const std::list<dogen::om::cpp_argument>& arguments,
    const bool is_friend)
    : dogen::om::cpp_feature(name),
      commands_(commands),
      representation_type_(representation_type),
      is_inline_(is_inline),
      return_type_(return_type),
      arguments_(arguments),
      is_friend_(is_friend) { }

void cpp_abstract_function::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_abstract_function\"" << ", "
      << "\"__parent_0__\": ";
    cpp_feature::to_stream(s);
    s << ", "
      << "\"commands\": " << commands_ << ", "
      << "\"representation_type\": " << representation_type_ << ", "
      << "\"is_inline\": " << is_inline_ << ", "
      << "\"return_type\": " << return_type_ << ", "
      << "\"arguments\": " << arguments_ << ", "
      << "\"is_friend\": " << is_friend_
      << " }";
}

void cpp_abstract_function::swap(cpp_abstract_function& other) noexcept {
    cpp_feature::swap(other);

    using std::swap;
    swap(commands_, other.commands_);
    swap(representation_type_, other.representation_type_);
    swap(is_inline_, other.is_inline_);
    swap(return_type_, other.return_type_);
    swap(arguments_, other.arguments_);
    swap(is_friend_, other.is_friend_);
}

bool cpp_abstract_function::compare(const cpp_abstract_function& rhs) const {
    return cpp_feature::compare(rhs) &&
        commands_ == rhs.commands_ &&
        representation_type_ == rhs.representation_type_ &&
        is_inline_ == rhs.is_inline_ &&
        return_type_ == rhs.return_type_ &&
        arguments_ == rhs.arguments_ &&
        is_friend_ == rhs.is_friend_;
}

const std::list<dogen::om::doxygen_command>& cpp_abstract_function::commands() const {
    return commands_;
}

std::list<dogen::om::doxygen_command>& cpp_abstract_function::commands() {
    return commands_;
}

void cpp_abstract_function::commands(const std::list<dogen::om::doxygen_command>& v) {
    commands_ = v;
}

void cpp_abstract_function::commands(const std::list<dogen::om::doxygen_command>&& v) {
    commands_ = std::move(v);
}

dogen::om::cpp_representation_types cpp_abstract_function::representation_type() const {
    return representation_type_;
}

void cpp_abstract_function::representation_type(const dogen::om::cpp_representation_types& v) {
    representation_type_ = v;
}

bool cpp_abstract_function::is_inline() const {
    return is_inline_;
}

void cpp_abstract_function::is_inline(const bool v) {
    is_inline_ = v;
}

const dogen::om::cpp_instance_typeref& cpp_abstract_function::return_type() const {
    return return_type_;
}

dogen::om::cpp_instance_typeref& cpp_abstract_function::return_type() {
    return return_type_;
}

void cpp_abstract_function::return_type(const dogen::om::cpp_instance_typeref& v) {
    return_type_ = v;
}

void cpp_abstract_function::return_type(const dogen::om::cpp_instance_typeref&& v) {
    return_type_ = std::move(v);
}

const std::list<dogen::om::cpp_argument>& cpp_abstract_function::arguments() const {
    return arguments_;
}

std::list<dogen::om::cpp_argument>& cpp_abstract_function::arguments() {
    return arguments_;
}

void cpp_abstract_function::arguments(const std::list<dogen::om::cpp_argument>& v) {
    arguments_ = v;
}

void cpp_abstract_function::arguments(const std::list<dogen::om::cpp_argument>&& v) {
    arguments_ = std::move(v);
}

bool cpp_abstract_function::is_friend() const {
    return is_friend_;
}

void cpp_abstract_function::is_friend(const bool v) {
    is_friend_ = v;
}

} }