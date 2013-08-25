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
#include "dogen/om/io/cpp_base_io.hpp"
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/io/cpp_member_group_io.hpp"
#include "dogen/om/io/cpp_representation_types_io.hpp"
#include "dogen/om/io/doxygen_command_io.hpp"
#include "dogen/om/types/cpp_class.hpp"

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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::om::cpp_base>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::om::cpp_member_group>& v) {
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

cpp_class::cpp_class()
    : representation_type_(static_cast<dogen::om::cpp_representation_types>(0)),
      is_final_(static_cast<bool>(0)),
      is_friend_(static_cast<bool>(0)) { }

cpp_class::cpp_class(
    const std::string& name,
    const std::list<dogen::om::doxygen_command>& commands,
    const dogen::om::cpp_representation_types& representation_type,
    const std::list<dogen::om::cpp_base>& bases,
    const std::list<dogen::om::cpp_member_group>& members,
    const bool is_final,
    const bool is_friend)
    : dogen::om::cpp_feature(name),
      commands_(commands),
      representation_type_(representation_type),
      bases_(bases),
      members_(members),
      is_final_(is_final),
      is_friend_(is_friend) { }

void cpp_class::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_class\"" << ", "
      << "\"__parent_0__\": ";
    cpp_feature::to_stream(s);
    s << ", "
      << "\"commands\": " << commands_ << ", "
      << "\"representation_type\": " << representation_type_ << ", "
      << "\"bases\": " << bases_ << ", "
      << "\"members\": " << members_ << ", "
      << "\"is_final\": " << is_final_ << ", "
      << "\"is_friend\": " << is_friend_
      << " }";
}

void cpp_class::swap(cpp_class& other) noexcept {
    cpp_feature::swap(other);

    using std::swap;
    swap(commands_, other.commands_);
    swap(representation_type_, other.representation_type_);
    swap(bases_, other.bases_);
    swap(members_, other.members_);
    swap(is_final_, other.is_final_);
    swap(is_friend_, other.is_friend_);
}

bool cpp_class::equals(const dogen::om::cpp_feature& other) const {
    const cpp_class* const p(dynamic_cast<const cpp_class* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_class::operator==(const cpp_class& rhs) const {
    return cpp_feature::compare(rhs) &&
        commands_ == rhs.commands_ &&
        representation_type_ == rhs.representation_type_ &&
        bases_ == rhs.bases_ &&
        members_ == rhs.members_ &&
        is_final_ == rhs.is_final_ &&
        is_friend_ == rhs.is_friend_;
}

cpp_class& cpp_class::operator=(cpp_class other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::om::doxygen_command>& cpp_class::commands() const {
    return commands_;
}

std::list<dogen::om::doxygen_command>& cpp_class::commands() {
    return commands_;
}

void cpp_class::commands(const std::list<dogen::om::doxygen_command>& v) {
    commands_ = v;
}

void cpp_class::commands(const std::list<dogen::om::doxygen_command>&& v) {
    commands_ = std::move(v);
}

dogen::om::cpp_representation_types cpp_class::representation_type() const {
    return representation_type_;
}

void cpp_class::representation_type(const dogen::om::cpp_representation_types& v) {
    representation_type_ = v;
}

const std::list<dogen::om::cpp_base>& cpp_class::bases() const {
    return bases_;
}

std::list<dogen::om::cpp_base>& cpp_class::bases() {
    return bases_;
}

void cpp_class::bases(const std::list<dogen::om::cpp_base>& v) {
    bases_ = v;
}

void cpp_class::bases(const std::list<dogen::om::cpp_base>&& v) {
    bases_ = std::move(v);
}

const std::list<dogen::om::cpp_member_group>& cpp_class::members() const {
    return members_;
}

std::list<dogen::om::cpp_member_group>& cpp_class::members() {
    return members_;
}

void cpp_class::members(const std::list<dogen::om::cpp_member_group>& v) {
    members_ = v;
}

void cpp_class::members(const std::list<dogen::om::cpp_member_group>&& v) {
    members_ = std::move(v);
}

bool cpp_class::is_final() const {
    return is_final_;
}

void cpp_class::is_final(const bool v) {
    is_final_ = v;
}

bool cpp_class::is_friend() const {
    return is_friend_;
}

void cpp_class::is_friend(const bool v) {
    is_friend_ = v;
}

} }