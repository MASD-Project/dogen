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
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/io/cpp_typeref_io.hpp"
#include "dogen/om/io/doxygen_command_io.hpp"
#include "dogen/om/types/cpp_typedef.hpp"

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

namespace dogen {
namespace om {

cpp_typedef::cpp_typedef(
    const std::string& name,
    const std::list<dogen::om::doxygen_command>& commands,
    const dogen::om::cpp_typeref& type)
    : dogen::om::cpp_feature(name),
      commands_(commands),
      type_(type) { }

void cpp_typedef::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_typedef\"" << ", "
      << "\"__parent_0__\": ";
    cpp_feature::to_stream(s);
    s << ", "
      << "\"commands\": " << commands_ << ", "
      << "\"type\": " << type_
      << " }";
}

void cpp_typedef::swap(cpp_typedef& other) noexcept {
    cpp_feature::swap(other);

    using std::swap;
    swap(commands_, other.commands_);
    swap(type_, other.type_);
}

bool cpp_typedef::equals(const dogen::om::cpp_feature& other) const {
    const cpp_typedef* const p(dynamic_cast<const cpp_typedef* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_typedef::operator==(const cpp_typedef& rhs) const {
    return cpp_feature::compare(rhs) &&
        commands_ == rhs.commands_ &&
        type_ == rhs.type_;
}

cpp_typedef& cpp_typedef::operator=(cpp_typedef other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::om::doxygen_command>& cpp_typedef::commands() const {
    return commands_;
}

std::list<dogen::om::doxygen_command>& cpp_typedef::commands() {
    return commands_;
}

void cpp_typedef::commands(const std::list<dogen::om::doxygen_command>& v) {
    commands_ = v;
}

void cpp_typedef::commands(const std::list<dogen::om::doxygen_command>&& v) {
    commands_ = std::move(v);
}

const dogen::om::cpp_typeref& cpp_typedef::type() const {
    return type_;
}

dogen::om::cpp_typeref& cpp_typedef::type() {
    return type_;
}

void cpp_typedef::type(const dogen::om::cpp_typeref& v) {
    type_ = v;
}

void cpp_typedef::type(const dogen::om::cpp_typeref&& v) {
    type_ = std::move(v);
}

} }