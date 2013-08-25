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
#include "dogen/om/io/cpp_enumerator_io.hpp"
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/io/cpp_fundamental_types_io.hpp"
#include "dogen/om/io/cpp_representation_types_io.hpp"
#include "dogen/om/io/doxygen_command_io.hpp"
#include "dogen/om/types/cpp_enumeration.hpp"

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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::om::cpp_enumerator>& v) {
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

cpp_enumeration::cpp_enumeration()
    : representation_type_(static_cast<dogen::om::cpp_representation_types>(0)),
      type_(static_cast<dogen::om::cpp_fundamental_types>(0)),
      is_class_(static_cast<bool>(0)) { }

cpp_enumeration::cpp_enumeration(
    const std::string& name,
    const std::list<dogen::om::doxygen_command>& commands,
    const dogen::om::cpp_representation_types& representation_type,
    const dogen::om::cpp_fundamental_types& type,
    const std::list<dogen::om::cpp_enumerator>& enumerators,
    const bool is_class)
    : dogen::om::cpp_feature(name),
      commands_(commands),
      representation_type_(representation_type),
      type_(type),
      enumerators_(enumerators),
      is_class_(is_class) { }

void cpp_enumeration::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_enumeration\"" << ", "
      << "\"__parent_0__\": ";
    cpp_feature::to_stream(s);
    s << ", "
      << "\"commands\": " << commands_ << ", "
      << "\"representation_type\": " << representation_type_ << ", "
      << "\"type\": " << type_ << ", "
      << "\"enumerators\": " << enumerators_ << ", "
      << "\"is_class\": " << is_class_
      << " }";
}

void cpp_enumeration::swap(cpp_enumeration& other) noexcept {
    cpp_feature::swap(other);

    using std::swap;
    swap(commands_, other.commands_);
    swap(representation_type_, other.representation_type_);
    swap(type_, other.type_);
    swap(enumerators_, other.enumerators_);
    swap(is_class_, other.is_class_);
}

bool cpp_enumeration::equals(const dogen::om::cpp_feature& other) const {
    const cpp_enumeration* const p(dynamic_cast<const cpp_enumeration* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_enumeration::operator==(const cpp_enumeration& rhs) const {
    return cpp_feature::compare(rhs) &&
        commands_ == rhs.commands_ &&
        representation_type_ == rhs.representation_type_ &&
        type_ == rhs.type_ &&
        enumerators_ == rhs.enumerators_ &&
        is_class_ == rhs.is_class_;
}

cpp_enumeration& cpp_enumeration::operator=(cpp_enumeration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::om::doxygen_command>& cpp_enumeration::commands() const {
    return commands_;
}

std::list<dogen::om::doxygen_command>& cpp_enumeration::commands() {
    return commands_;
}

void cpp_enumeration::commands(const std::list<dogen::om::doxygen_command>& v) {
    commands_ = v;
}

void cpp_enumeration::commands(const std::list<dogen::om::doxygen_command>&& v) {
    commands_ = std::move(v);
}

dogen::om::cpp_representation_types cpp_enumeration::representation_type() const {
    return representation_type_;
}

void cpp_enumeration::representation_type(const dogen::om::cpp_representation_types& v) {
    representation_type_ = v;
}

dogen::om::cpp_fundamental_types cpp_enumeration::type() const {
    return type_;
}

void cpp_enumeration::type(const dogen::om::cpp_fundamental_types& v) {
    type_ = v;
}

const std::list<dogen::om::cpp_enumerator>& cpp_enumeration::enumerators() const {
    return enumerators_;
}

std::list<dogen::om::cpp_enumerator>& cpp_enumeration::enumerators() {
    return enumerators_;
}

void cpp_enumeration::enumerators(const std::list<dogen::om::cpp_enumerator>& v) {
    enumerators_ = v;
}

void cpp_enumeration::enumerators(const std::list<dogen::om::cpp_enumerator>&& v) {
    enumerators_ = std::move(v);
}

bool cpp_enumeration::is_class() const {
    return is_class_;
}

void cpp_enumeration::is_class(const bool v) {
    is_class_ = v;
}

} }