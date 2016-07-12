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
#include <boost/algorithm/string.hpp>
#include "dogen/yarn/io/generation_types_io.hpp"
#include "dogen/quilt.cpp/io/properties/entity_io.hpp"
#include "dogen/quilt.cpp/types/properties/class_info.hpp"
#include "dogen/quilt.cpp/io/properties/parent_info_io.hpp"
#include "dogen/quilt.cpp/io/properties/property_info_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::quilt::cpp::properties::property_info>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::quilt::cpp::properties::parent_info>& v) {
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
namespace quilt {
namespace cpp {
namespace properties {

class_info::class_info()
    : requires_stream_manipulators_(static_cast<bool>(0)),
      requires_manual_move_constructor_(static_cast<bool>(0)),
      requires_manual_default_constructor_(static_cast<bool>(0)),
      is_parent_(static_cast<bool>(0)),
      is_visitable_(static_cast<bool>(0)),
      is_immutable_(static_cast<bool>(0)),
      is_root_parent_visitable_(static_cast<bool>(0)),
      generation_type_(static_cast<dogen::yarn::generation_types>(0)),
      is_final_(static_cast<bool>(0)),
      in_inheritance_relationship_(static_cast<bool>(0)) { }

class_info::class_info(
    const std::string& identity,
    const dogen::quilt::cpp::properties::origin_types origin_type,
    const std::string& id,
    const std::string& name,
    const std::string& qualified_name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const std::list<dogen::quilt::cpp::properties::property_info>& properties,
    const std::list<dogen::quilt::cpp::properties::property_info>& all_properties,
    const bool requires_stream_manipulators,
    const bool requires_manual_move_constructor,
    const bool requires_manual_default_constructor,
    const std::list<dogen::quilt::cpp::properties::parent_info>& parents,
    const bool is_parent,
    const std::string& root_parent_name,
    const std::string& root_parent_name_qualified,
    const std::list<std::string>& leaves,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_root_parent_visitable,
    const dogen::yarn::generation_types generation_type,
    const bool is_final,
    const bool in_inheritance_relationship)
    : dogen::quilt::cpp::properties::entity(
      identity,
      origin_type,
      id,
      name,
      qualified_name,
      documentation,
      namespaces),
      properties_(properties),
      all_properties_(all_properties),
      requires_stream_manipulators_(requires_stream_manipulators),
      requires_manual_move_constructor_(requires_manual_move_constructor),
      requires_manual_default_constructor_(requires_manual_default_constructor),
      parents_(parents),
      is_parent_(is_parent),
      root_parent_name_(root_parent_name),
      root_parent_name_qualified_(root_parent_name_qualified),
      leaves_(leaves),
      is_visitable_(is_visitable),
      is_immutable_(is_immutable),
      is_root_parent_visitable_(is_root_parent_visitable),
      generation_type_(generation_type),
      is_final_(is_final),
      in_inheritance_relationship_(in_inheritance_relationship) { }

void class_info::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::properties::class_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << ", "
      << "\"properties\": " << properties_ << ", "
      << "\"all_properties\": " << all_properties_ << ", "
      << "\"requires_stream_manipulators\": " << requires_stream_manipulators_ << ", "
      << "\"requires_manual_move_constructor\": " << requires_manual_move_constructor_ << ", "
      << "\"requires_manual_default_constructor\": " << requires_manual_default_constructor_ << ", "
      << "\"parents\": " << parents_ << ", "
      << "\"is_parent\": " << is_parent_ << ", "
      << "\"root_parent_name\": " << "\"" << tidy_up_string(root_parent_name_) << "\"" << ", "
      << "\"root_parent_name_qualified\": " << "\"" << tidy_up_string(root_parent_name_qualified_) << "\"" << ", "
      << "\"leaves\": " << leaves_ << ", "
      << "\"is_visitable\": " << is_visitable_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_root_parent_visitable\": " << is_root_parent_visitable_ << ", "
      << "\"generation_type\": " << generation_type_ << ", "
      << "\"is_final\": " << is_final_ << ", "
      << "\"in_inheritance_relationship\": " << in_inheritance_relationship_
      << " }";
}

void class_info::swap(class_info& other) noexcept {
    entity::swap(other);

    using std::swap;
    swap(properties_, other.properties_);
    swap(all_properties_, other.all_properties_);
    swap(requires_stream_manipulators_, other.requires_stream_manipulators_);
    swap(requires_manual_move_constructor_, other.requires_manual_move_constructor_);
    swap(requires_manual_default_constructor_, other.requires_manual_default_constructor_);
    swap(parents_, other.parents_);
    swap(is_parent_, other.is_parent_);
    swap(root_parent_name_, other.root_parent_name_);
    swap(root_parent_name_qualified_, other.root_parent_name_qualified_);
    swap(leaves_, other.leaves_);
    swap(is_visitable_, other.is_visitable_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_root_parent_visitable_, other.is_root_parent_visitable_);
    swap(generation_type_, other.generation_type_);
    swap(is_final_, other.is_final_);
    swap(in_inheritance_relationship_, other.in_inheritance_relationship_);
}

bool class_info::equals(const dogen::quilt::cpp::properties::formattable& other) const {
    const class_info* const p(dynamic_cast<const class_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool class_info::operator==(const class_info& rhs) const {
    return entity::compare(rhs) &&
        properties_ == rhs.properties_ &&
        all_properties_ == rhs.all_properties_ &&
        requires_stream_manipulators_ == rhs.requires_stream_manipulators_ &&
        requires_manual_move_constructor_ == rhs.requires_manual_move_constructor_ &&
        requires_manual_default_constructor_ == rhs.requires_manual_default_constructor_ &&
        parents_ == rhs.parents_ &&
        is_parent_ == rhs.is_parent_ &&
        root_parent_name_ == rhs.root_parent_name_ &&
        root_parent_name_qualified_ == rhs.root_parent_name_qualified_ &&
        leaves_ == rhs.leaves_ &&
        is_visitable_ == rhs.is_visitable_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_root_parent_visitable_ == rhs.is_root_parent_visitable_ &&
        generation_type_ == rhs.generation_type_ &&
        is_final_ == rhs.is_final_ &&
        in_inheritance_relationship_ == rhs.in_inheritance_relationship_;
}

class_info& class_info::operator=(class_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::quilt::cpp::properties::property_info>& class_info::properties() const {
    return properties_;
}

std::list<dogen::quilt::cpp::properties::property_info>& class_info::properties() {
    return properties_;
}

void class_info::properties(const std::list<dogen::quilt::cpp::properties::property_info>& v) {
    properties_ = v;
}

void class_info::properties(const std::list<dogen::quilt::cpp::properties::property_info>&& v) {
    properties_ = std::move(v);
}

const std::list<dogen::quilt::cpp::properties::property_info>& class_info::all_properties() const {
    return all_properties_;
}

std::list<dogen::quilt::cpp::properties::property_info>& class_info::all_properties() {
    return all_properties_;
}

void class_info::all_properties(const std::list<dogen::quilt::cpp::properties::property_info>& v) {
    all_properties_ = v;
}

void class_info::all_properties(const std::list<dogen::quilt::cpp::properties::property_info>&& v) {
    all_properties_ = std::move(v);
}

bool class_info::requires_stream_manipulators() const {
    return requires_stream_manipulators_;
}

void class_info::requires_stream_manipulators(const bool v) {
    requires_stream_manipulators_ = v;
}

bool class_info::requires_manual_move_constructor() const {
    return requires_manual_move_constructor_;
}

void class_info::requires_manual_move_constructor(const bool v) {
    requires_manual_move_constructor_ = v;
}

bool class_info::requires_manual_default_constructor() const {
    return requires_manual_default_constructor_;
}

void class_info::requires_manual_default_constructor(const bool v) {
    requires_manual_default_constructor_ = v;
}

const std::list<dogen::quilt::cpp::properties::parent_info>& class_info::parents() const {
    return parents_;
}

std::list<dogen::quilt::cpp::properties::parent_info>& class_info::parents() {
    return parents_;
}

void class_info::parents(const std::list<dogen::quilt::cpp::properties::parent_info>& v) {
    parents_ = v;
}

void class_info::parents(const std::list<dogen::quilt::cpp::properties::parent_info>&& v) {
    parents_ = std::move(v);
}

bool class_info::is_parent() const {
    return is_parent_;
}

void class_info::is_parent(const bool v) {
    is_parent_ = v;
}

const std::string& class_info::root_parent_name() const {
    return root_parent_name_;
}

std::string& class_info::root_parent_name() {
    return root_parent_name_;
}

void class_info::root_parent_name(const std::string& v) {
    root_parent_name_ = v;
}

void class_info::root_parent_name(const std::string&& v) {
    root_parent_name_ = std::move(v);
}

const std::string& class_info::root_parent_name_qualified() const {
    return root_parent_name_qualified_;
}

std::string& class_info::root_parent_name_qualified() {
    return root_parent_name_qualified_;
}

void class_info::root_parent_name_qualified(const std::string& v) {
    root_parent_name_qualified_ = v;
}

void class_info::root_parent_name_qualified(const std::string&& v) {
    root_parent_name_qualified_ = std::move(v);
}

const std::list<std::string>& class_info::leaves() const {
    return leaves_;
}

std::list<std::string>& class_info::leaves() {
    return leaves_;
}

void class_info::leaves(const std::list<std::string>& v) {
    leaves_ = v;
}

void class_info::leaves(const std::list<std::string>&& v) {
    leaves_ = std::move(v);
}

bool class_info::is_visitable() const {
    return is_visitable_;
}

void class_info::is_visitable(const bool v) {
    is_visitable_ = v;
}

bool class_info::is_immutable() const {
    return is_immutable_;
}

void class_info::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool class_info::is_root_parent_visitable() const {
    return is_root_parent_visitable_;
}

void class_info::is_root_parent_visitable(const bool v) {
    is_root_parent_visitable_ = v;
}

dogen::yarn::generation_types class_info::generation_type() const {
    return generation_type_;
}

void class_info::generation_type(const dogen::yarn::generation_types v) {
    generation_type_ = v;
}

bool class_info::is_final() const {
    return is_final_;
}

void class_info::is_final(const bool v) {
    is_final_ = v;
}

bool class_info::in_inheritance_relationship() const {
    return in_inheritance_relationship_;
}

void class_info::in_inheritance_relationship(const bool v) {
    in_inheritance_relationship_ = v;
}

} } } }
