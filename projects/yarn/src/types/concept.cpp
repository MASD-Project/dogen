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
#include <boost/io/ios_state.hpp>
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/io/property_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::yarn::property>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::yarn::name>& v) {
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
namespace yarn {

concept::concept()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)),
      is_parent_(static_cast<bool>(0)),
      is_child_(static_cast<bool>(0)) { }

concept::concept(
    const bool in_global_module,
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::yarn::name& name,
    const dogen::yarn::generation_types generation_type,
    const dogen::yarn::origin_types origin_type,
    const std::string& original_model_name,
    const boost::optional<dogen::yarn::name>& containing_module,
    const std::list<dogen::yarn::property>& all_properties,
    const std::list<dogen::yarn::property>& local_properties,
    const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& inherited_properties,
    const bool is_immutable,
    const bool is_fluent,
    const std::list<dogen::yarn::name>& refines,
    const bool is_parent,
    const bool is_child)
    : dogen::yarn::element(
      in_global_module,
      documentation,
      extensions,
      name,
      generation_type,
      origin_type,
      original_model_name,
      containing_module),
      all_properties_(all_properties),
      local_properties_(local_properties),
      inherited_properties_(inherited_properties),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      refines_(refines),
      is_parent_(is_parent),
      is_child_(is_child) { }

void concept::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::concept\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << ", "
      << "\"all_properties\": " << all_properties_ << ", "
      << "\"local_properties\": " << local_properties_ << ", "
      << "\"inherited_properties\": " << inherited_properties_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_fluent\": " << is_fluent_ << ", "
      << "\"refines\": " << refines_ << ", "
      << "\"is_parent\": " << is_parent_ << ", "
      << "\"is_child\": " << is_child_
      << " }";
}

void concept::swap(concept& other) noexcept {
    element::swap(other);

    using std::swap;
    swap(all_properties_, other.all_properties_);
    swap(local_properties_, other.local_properties_);
    swap(inherited_properties_, other.inherited_properties_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(refines_, other.refines_);
    swap(is_parent_, other.is_parent_);
    swap(is_child_, other.is_child_);
}

bool concept::equals(const dogen::yarn::element& other) const {
    const concept* const p(dynamic_cast<const concept* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool concept::operator==(const concept& rhs) const {
    return element::compare(rhs) &&
        all_properties_ == rhs.all_properties_ &&
        local_properties_ == rhs.local_properties_ &&
        inherited_properties_ == rhs.inherited_properties_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        refines_ == rhs.refines_ &&
        is_parent_ == rhs.is_parent_ &&
        is_child_ == rhs.is_child_;
}

concept& concept::operator=(concept other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::yarn::property>& concept::all_properties() const {
    return all_properties_;
}

std::list<dogen::yarn::property>& concept::all_properties() {
    return all_properties_;
}

void concept::all_properties(const std::list<dogen::yarn::property>& v) {
    all_properties_ = v;
}

void concept::all_properties(const std::list<dogen::yarn::property>&& v) {
    all_properties_ = std::move(v);
}

const std::list<dogen::yarn::property>& concept::local_properties() const {
    return local_properties_;
}

std::list<dogen::yarn::property>& concept::local_properties() {
    return local_properties_;
}

void concept::local_properties(const std::list<dogen::yarn::property>& v) {
    local_properties_ = v;
}

void concept::local_properties(const std::list<dogen::yarn::property>&& v) {
    local_properties_ = std::move(v);
}

const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& concept::inherited_properties() const {
    return inherited_properties_;
}

std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& concept::inherited_properties() {
    return inherited_properties_;
}

void concept::inherited_properties(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& v) {
    inherited_properties_ = v;
}

void concept::inherited_properties(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >&& v) {
    inherited_properties_ = std::move(v);
}

bool concept::is_immutable() const {
    return is_immutable_;
}

void concept::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool concept::is_fluent() const {
    return is_fluent_;
}

void concept::is_fluent(const bool v) {
    is_fluent_ = v;
}

const std::list<dogen::yarn::name>& concept::refines() const {
    return refines_;
}

std::list<dogen::yarn::name>& concept::refines() {
    return refines_;
}

void concept::refines(const std::list<dogen::yarn::name>& v) {
    refines_ = v;
}

void concept::refines(const std::list<dogen::yarn::name>&& v) {
    refines_ = std::move(v);
}

bool concept::is_parent() const {
    return is_parent_;
}

void concept::is_parent(const bool v) {
    is_parent_ = v;
}

bool concept::is_child() const {
    return is_child_;
}

void concept::is_child(const bool v) {
    is_child_ = v;
}

} }
