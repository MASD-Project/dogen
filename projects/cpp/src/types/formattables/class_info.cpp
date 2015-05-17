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
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/sml/io/generation_types_io.hpp"
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp/io/formattables/class_types_io.hpp"
#include "dogen/cpp/io/formattables/parent_info_io.hpp"
#include "dogen/cpp/io/formattables/property_info_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::formattables::property_info>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::formattables::parent_info>& v) {
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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<std::string, std::string>& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << "\"" << tidy_up_string(v.first) << "\"" << ", ";
    s << "\"second\": " << "\"" << tidy_up_string(v.second) << "\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<std::string, std::string> >& v) {
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
namespace cpp {
namespace formattables {

class_info::class_info()
    : requires_stream_manipulators_(static_cast<bool>(0)),
      requires_manual_move_constructor_(static_cast<bool>(0)),
      requires_manual_default_constructor_(static_cast<bool>(0)),
      is_parent_(static_cast<bool>(0)),
      is_comparable_(static_cast<bool>(0)),
      is_visitable_(static_cast<bool>(0)),
      is_immutable_(static_cast<bool>(0)),
      is_original_parent_visitable_(static_cast<bool>(0)),
      class_type_(static_cast<dogen::cpp::formattables::class_types>(0)),
      generation_type_(static_cast<dogen::sml::generation_types>(0)),
      is_final_(static_cast<bool>(0)) { }

class_info::class_info(
    const std::string& identity,
    const std::string& name,
    const std::string& qualified_name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const dogen::cpp::settings::bundle& settings,
    const std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties>& formatter_properties,
    const std::list<dogen::cpp::formattables::property_info>& properties,
    const std::list<dogen::cpp::formattables::property_info>& all_properties,
    const bool requires_stream_manipulators,
    const bool requires_manual_move_constructor,
    const bool requires_manual_default_constructor,
    const std::list<dogen::cpp::formattables::parent_info>& parents,
    const bool is_parent,
    const std::string& original_parent_name,
    const std::string& original_parent_name_qualified,
    const std::list<std::string>& leaves,
    const std::list<std::pair<std::string, std::string> >& opaque_parameters,
    const bool is_comparable,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_original_parent_visitable,
    const dogen::cpp::formattables::class_types& class_type,
    const dogen::sml::generation_types& generation_type,
    const bool is_final)
    : dogen::cpp::formattables::entity(identity,
      name,
      qualified_name,
      documentation,
      namespaces,
      settings,
      formatter_properties),
      properties_(properties),
      all_properties_(all_properties),
      requires_stream_manipulators_(requires_stream_manipulators),
      requires_manual_move_constructor_(requires_manual_move_constructor),
      requires_manual_default_constructor_(requires_manual_default_constructor),
      parents_(parents),
      is_parent_(is_parent),
      original_parent_name_(original_parent_name),
      original_parent_name_qualified_(original_parent_name_qualified),
      leaves_(leaves),
      opaque_parameters_(opaque_parameters),
      is_comparable_(is_comparable),
      is_visitable_(is_visitable),
      is_immutable_(is_immutable),
      is_original_parent_visitable_(is_original_parent_visitable),
      class_type_(class_type),
      generation_type_(generation_type),
      is_final_(is_final) { }

void class_info::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::class_info\"" << ", "
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
      << "\"original_parent_name\": " << "\"" << tidy_up_string(original_parent_name_) << "\"" << ", "
      << "\"original_parent_name_qualified\": " << "\"" << tidy_up_string(original_parent_name_qualified_) << "\"" << ", "
      << "\"leaves\": " << leaves_ << ", "
      << "\"opaque_parameters\": " << opaque_parameters_ << ", "
      << "\"is_comparable\": " << is_comparable_ << ", "
      << "\"is_visitable\": " << is_visitable_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_original_parent_visitable\": " << is_original_parent_visitable_ << ", "
      << "\"class_type\": " << class_type_ << ", "
      << "\"generation_type\": " << generation_type_ << ", "
      << "\"is_final\": " << is_final_
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
    swap(original_parent_name_, other.original_parent_name_);
    swap(original_parent_name_qualified_, other.original_parent_name_qualified_);
    swap(leaves_, other.leaves_);
    swap(opaque_parameters_, other.opaque_parameters_);
    swap(is_comparable_, other.is_comparable_);
    swap(is_visitable_, other.is_visitable_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_original_parent_visitable_, other.is_original_parent_visitable_);
    swap(class_type_, other.class_type_);
    swap(generation_type_, other.generation_type_);
    swap(is_final_, other.is_final_);
}

bool class_info::equals(const dogen::cpp::formattables::formattable& other) const {
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
        original_parent_name_ == rhs.original_parent_name_ &&
        original_parent_name_qualified_ == rhs.original_parent_name_qualified_ &&
        leaves_ == rhs.leaves_ &&
        opaque_parameters_ == rhs.opaque_parameters_ &&
        is_comparable_ == rhs.is_comparable_ &&
        is_visitable_ == rhs.is_visitable_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_original_parent_visitable_ == rhs.is_original_parent_visitable_ &&
        class_type_ == rhs.class_type_ &&
        generation_type_ == rhs.generation_type_ &&
        is_final_ == rhs.is_final_;
}

class_info& class_info::operator=(class_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::cpp::formattables::property_info>& class_info::properties() const {
    return properties_;
}

std::list<dogen::cpp::formattables::property_info>& class_info::properties() {
    return properties_;
}

void class_info::properties(const std::list<dogen::cpp::formattables::property_info>& v) {
    properties_ = v;
}

void class_info::properties(const std::list<dogen::cpp::formattables::property_info>&& v) {
    properties_ = std::move(v);
}

const std::list<dogen::cpp::formattables::property_info>& class_info::all_properties() const {
    return all_properties_;
}

std::list<dogen::cpp::formattables::property_info>& class_info::all_properties() {
    return all_properties_;
}

void class_info::all_properties(const std::list<dogen::cpp::formattables::property_info>& v) {
    all_properties_ = v;
}

void class_info::all_properties(const std::list<dogen::cpp::formattables::property_info>&& v) {
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

const std::list<dogen::cpp::formattables::parent_info>& class_info::parents() const {
    return parents_;
}

std::list<dogen::cpp::formattables::parent_info>& class_info::parents() {
    return parents_;
}

void class_info::parents(const std::list<dogen::cpp::formattables::parent_info>& v) {
    parents_ = v;
}

void class_info::parents(const std::list<dogen::cpp::formattables::parent_info>&& v) {
    parents_ = std::move(v);
}

bool class_info::is_parent() const {
    return is_parent_;
}

void class_info::is_parent(const bool v) {
    is_parent_ = v;
}

const std::string& class_info::original_parent_name() const {
    return original_parent_name_;
}

std::string& class_info::original_parent_name() {
    return original_parent_name_;
}

void class_info::original_parent_name(const std::string& v) {
    original_parent_name_ = v;
}

void class_info::original_parent_name(const std::string&& v) {
    original_parent_name_ = std::move(v);
}

const std::string& class_info::original_parent_name_qualified() const {
    return original_parent_name_qualified_;
}

std::string& class_info::original_parent_name_qualified() {
    return original_parent_name_qualified_;
}

void class_info::original_parent_name_qualified(const std::string& v) {
    original_parent_name_qualified_ = v;
}

void class_info::original_parent_name_qualified(const std::string&& v) {
    original_parent_name_qualified_ = std::move(v);
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

const std::list<std::pair<std::string, std::string> >& class_info::opaque_parameters() const {
    return opaque_parameters_;
}

std::list<std::pair<std::string, std::string> >& class_info::opaque_parameters() {
    return opaque_parameters_;
}

void class_info::opaque_parameters(const std::list<std::pair<std::string, std::string> >& v) {
    opaque_parameters_ = v;
}

void class_info::opaque_parameters(const std::list<std::pair<std::string, std::string> >&& v) {
    opaque_parameters_ = std::move(v);
}

bool class_info::is_comparable() const {
    return is_comparable_;
}

void class_info::is_comparable(const bool v) {
    is_comparable_ = v;
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

bool class_info::is_original_parent_visitable() const {
    return is_original_parent_visitable_;
}

void class_info::is_original_parent_visitable(const bool v) {
    is_original_parent_visitable_ = v;
}

dogen::cpp::formattables::class_types class_info::class_type() const {
    return class_type_;
}

void class_info::class_type(const dogen::cpp::formattables::class_types& v) {
    class_type_ = v;
}

dogen::sml::generation_types class_info::generation_type() const {
    return generation_type_;
}

void class_info::generation_type(const dogen::sml::generation_types& v) {
    generation_type_ = v;
}

bool class_info::is_final() const {
    return is_final_;
}

void class_info::is_final(const bool v) {
    is_final_ = v;
}

} } }