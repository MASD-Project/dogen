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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/sml/io/generation_types_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/type_io.hpp"
#include "dogen/sml/types/abstract_object.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::property>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::sml::qname>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::qname>& v) {
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
namespace sml {

abstract_object::abstract_object()
    : is_parent_(static_cast<bool>(0)),
      number_of_type_arguments_(static_cast<unsigned int>(0)),
      is_visitable_(static_cast<bool>(0)),
      is_immutable_(static_cast<bool>(0)),
      is_versioned_(static_cast<bool>(0)),
      is_comparable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)) { }

abstract_object::abstract_object(abstract_object&& rhs)
    : dogen::sml::type(
        std::forward<dogen::sml::type>(rhs)),
      properties_(std::move(rhs.properties_)),
      parent_name_(std::move(rhs.parent_name_)),
      original_parent_name_(std::move(rhs.original_parent_name_)),
      leaves_(std::move(rhs.leaves_)),
      is_parent_(std::move(rhs.is_parent_)),
      number_of_type_arguments_(std::move(rhs.number_of_type_arguments_)),
      is_visitable_(std::move(rhs.is_visitable_)),
      is_immutable_(std::move(rhs.is_immutable_)),
      is_versioned_(std::move(rhs.is_versioned_)),
      is_comparable_(std::move(rhs.is_comparable_)),
      is_fluent_(std::move(rhs.is_fluent_)),
      modeled_concepts_(std::move(rhs.modeled_concepts_)) { }

abstract_object::abstract_object(
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const std::list<dogen::sml::property>& properties,
    const boost::optional<dogen::sml::qname>& parent_name,
    const boost::optional<dogen::sml::qname>& original_parent_name,
    const std::list<dogen::sml::qname>& leaves,
    const bool is_parent,
    const unsigned int number_of_type_arguments,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_versioned,
    const bool is_comparable,
    const bool is_fluent,
    const std::list<dogen::sml::qname>& modeled_concepts)
    : dogen::sml::type(documentation,
      implementation_specific_parameters,
      name,
      generation_type),
      properties_(properties),
      parent_name_(parent_name),
      original_parent_name_(original_parent_name),
      leaves_(leaves),
      is_parent_(is_parent),
      number_of_type_arguments_(number_of_type_arguments),
      is_visitable_(is_visitable),
      is_immutable_(is_immutable),
      is_versioned_(is_versioned),
      is_comparable_(is_comparable),
      is_fluent_(is_fluent),
      modeled_concepts_(modeled_concepts) { }

void abstract_object::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::sml::abstract_object\"" << ", "
      << "\"__parent_0__\": ";
    type::to_stream(s);
    s << ", "
      << "\"properties\": " << properties_ << ", "
      << "\"parent_name\": " << parent_name_ << ", "
      << "\"original_parent_name\": " << original_parent_name_ << ", "
      << "\"leaves\": " << leaves_ << ", "
      << "\"is_parent\": " << is_parent_ << ", "
      << "\"number_of_type_arguments\": " << number_of_type_arguments_ << ", "
      << "\"is_visitable\": " << is_visitable_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_versioned\": " << is_versioned_ << ", "
      << "\"is_comparable\": " << is_comparable_ << ", "
      << "\"is_fluent\": " << is_fluent_ << ", "
      << "\"modeled_concepts\": " << modeled_concepts_
      << " }";
}

void abstract_object::swap(abstract_object& other) noexcept {
    type::swap(other);

    using std::swap;
    swap(properties_, other.properties_);
    swap(parent_name_, other.parent_name_);
    swap(original_parent_name_, other.original_parent_name_);
    swap(leaves_, other.leaves_);
    swap(is_parent_, other.is_parent_);
    swap(number_of_type_arguments_, other.number_of_type_arguments_);
    swap(is_visitable_, other.is_visitable_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_versioned_, other.is_versioned_);
    swap(is_comparable_, other.is_comparable_);
    swap(is_fluent_, other.is_fluent_);
    swap(modeled_concepts_, other.modeled_concepts_);
}

bool abstract_object::compare(const abstract_object& rhs) const {
    return type::compare(rhs) &&
        properties_ == rhs.properties_ &&
        parent_name_ == rhs.parent_name_ &&
        original_parent_name_ == rhs.original_parent_name_ &&
        leaves_ == rhs.leaves_ &&
        is_parent_ == rhs.is_parent_ &&
        number_of_type_arguments_ == rhs.number_of_type_arguments_ &&
        is_visitable_ == rhs.is_visitable_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_versioned_ == rhs.is_versioned_ &&
        is_comparable_ == rhs.is_comparable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        modeled_concepts_ == rhs.modeled_concepts_;
}

const std::list<dogen::sml::property>& abstract_object::properties() const {
    return properties_;
}

std::list<dogen::sml::property>& abstract_object::properties() {
    return properties_;
}

void abstract_object::properties(const std::list<dogen::sml::property>& v) {
    properties_ = v;
}

void abstract_object::properties(const std::list<dogen::sml::property>&& v) {
    properties_ = std::move(v);
}

const boost::optional<dogen::sml::qname>& abstract_object::parent_name() const {
    return parent_name_;
}

boost::optional<dogen::sml::qname>& abstract_object::parent_name() {
    return parent_name_;
}

void abstract_object::parent_name(const boost::optional<dogen::sml::qname>& v) {
    parent_name_ = v;
}

void abstract_object::parent_name(const boost::optional<dogen::sml::qname>&& v) {
    parent_name_ = std::move(v);
}

const boost::optional<dogen::sml::qname>& abstract_object::original_parent_name() const {
    return original_parent_name_;
}

boost::optional<dogen::sml::qname>& abstract_object::original_parent_name() {
    return original_parent_name_;
}

void abstract_object::original_parent_name(const boost::optional<dogen::sml::qname>& v) {
    original_parent_name_ = v;
}

void abstract_object::original_parent_name(const boost::optional<dogen::sml::qname>&& v) {
    original_parent_name_ = std::move(v);
}

const std::list<dogen::sml::qname>& abstract_object::leaves() const {
    return leaves_;
}

std::list<dogen::sml::qname>& abstract_object::leaves() {
    return leaves_;
}

void abstract_object::leaves(const std::list<dogen::sml::qname>& v) {
    leaves_ = v;
}

void abstract_object::leaves(const std::list<dogen::sml::qname>&& v) {
    leaves_ = std::move(v);
}

bool abstract_object::is_parent() const {
    return is_parent_;
}

void abstract_object::is_parent(const bool v) {
    is_parent_ = v;
}

unsigned int abstract_object::number_of_type_arguments() const {
    return number_of_type_arguments_;
}

void abstract_object::number_of_type_arguments(const unsigned int v) {
    number_of_type_arguments_ = v;
}

bool abstract_object::is_visitable() const {
    return is_visitable_;
}

void abstract_object::is_visitable(const bool v) {
    is_visitable_ = v;
}

bool abstract_object::is_immutable() const {
    return is_immutable_;
}

void abstract_object::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool abstract_object::is_versioned() const {
    return is_versioned_;
}

void abstract_object::is_versioned(const bool v) {
    is_versioned_ = v;
}

bool abstract_object::is_comparable() const {
    return is_comparable_;
}

void abstract_object::is_comparable(const bool v) {
    is_comparable_ = v;
}

bool abstract_object::is_fluent() const {
    return is_fluent_;
}

void abstract_object::is_fluent(const bool v) {
    is_fluent_ = v;
}

const std::list<dogen::sml::qname>& abstract_object::modeled_concepts() const {
    return modeled_concepts_;
}

std::list<dogen::sml::qname>& abstract_object::modeled_concepts() {
    return modeled_concepts_;
}

void abstract_object::modeled_concepts(const std::list<dogen::sml::qname>& v) {
    modeled_concepts_ = v;
}

void abstract_object::modeled_concepts(const std::list<dogen::sml::qname>&& v) {
    modeled_concepts_ = std::move(v);
}

} }