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
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/io/entities/attribute_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::attribute>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::logical::entities::name, std::list<dogen::logical::entities::attribute> >& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::structural {

object_template::object_template()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)),
      is_child_(static_cast<bool>(0)) { }

object_template::object_template(
    const dogen::logical::entities::name& name,
    const std::string& documentation,
    const dogen::logical::entities::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::entities::name& meta_name,
    const dogen::logical::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::entities::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::list<dogen::logical::entities::attribute>& all_attributes,
    const std::list<dogen::logical::entities::attribute>& local_attributes,
    const std::unordered_map<dogen::logical::entities::name, std::list<dogen::logical::entities::attribute> >& inherited_attributes,
    const bool is_immutable,
    const bool is_fluent,
    const std::list<dogen::logical::entities::name>& parents,
    const bool is_child)
    : dogen::logical::entities::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      artefact_properties,
      archetype_location_properties,
      decoration),
      all_attributes_(all_attributes),
      local_attributes_(local_attributes),
      inherited_attributes_(inherited_attributes),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      parents_(parents),
      is_child_(is_child) { }

void object_template::accept(const element_visitor& v) const {
    v.visit(*this);
}

void object_template::accept(element_visitor& v) const {
    v.visit(*this);
    }

void object_template::accept(const element_visitor& v) {
    v.visit(*this);
}

void object_template::accept(element_visitor& v) {
    v.visit(*this);
}

void object_template::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::structural::object_template\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"all_attributes\": " << all_attributes_ << ", "
      << "\"local_attributes\": " << local_attributes_ << ", "
      << "\"inherited_attributes\": " << inherited_attributes_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_fluent\": " << is_fluent_ << ", "
      << "\"parents\": " << parents_ << ", "
      << "\"is_child\": " << is_child_
      << " }";
}

void object_template::swap(object_template& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(all_attributes_, other.all_attributes_);
    swap(local_attributes_, other.local_attributes_);
    swap(inherited_attributes_, other.inherited_attributes_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(parents_, other.parents_);
    swap(is_child_, other.is_child_);
}

bool object_template::equals(const dogen::logical::entities::element& other) const {
    const object_template* const p(dynamic_cast<const object_template* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool object_template::operator==(const object_template& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        all_attributes_ == rhs.all_attributes_ &&
        local_attributes_ == rhs.local_attributes_ &&
        inherited_attributes_ == rhs.inherited_attributes_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        parents_ == rhs.parents_ &&
        is_child_ == rhs.is_child_;
}

object_template& object_template::operator=(object_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::logical::entities::attribute>& object_template::all_attributes() const {
    return all_attributes_;
}

std::list<dogen::logical::entities::attribute>& object_template::all_attributes() {
    return all_attributes_;
}

void object_template::all_attributes(const std::list<dogen::logical::entities::attribute>& v) {
    all_attributes_ = v;
}

void object_template::all_attributes(const std::list<dogen::logical::entities::attribute>&& v) {
    all_attributes_ = std::move(v);
}

const std::list<dogen::logical::entities::attribute>& object_template::local_attributes() const {
    return local_attributes_;
}

std::list<dogen::logical::entities::attribute>& object_template::local_attributes() {
    return local_attributes_;
}

void object_template::local_attributes(const std::list<dogen::logical::entities::attribute>& v) {
    local_attributes_ = v;
}

void object_template::local_attributes(const std::list<dogen::logical::entities::attribute>&& v) {
    local_attributes_ = std::move(v);
}

const std::unordered_map<dogen::logical::entities::name, std::list<dogen::logical::entities::attribute> >& object_template::inherited_attributes() const {
    return inherited_attributes_;
}

std::unordered_map<dogen::logical::entities::name, std::list<dogen::logical::entities::attribute> >& object_template::inherited_attributes() {
    return inherited_attributes_;
}

void object_template::inherited_attributes(const std::unordered_map<dogen::logical::entities::name, std::list<dogen::logical::entities::attribute> >& v) {
    inherited_attributes_ = v;
}

void object_template::inherited_attributes(const std::unordered_map<dogen::logical::entities::name, std::list<dogen::logical::entities::attribute> >&& v) {
    inherited_attributes_ = std::move(v);
}

bool object_template::is_immutable() const {
    return is_immutable_;
}

void object_template::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool object_template::is_fluent() const {
    return is_fluent_;
}

void object_template::is_fluent(const bool v) {
    is_fluent_ = v;
}

const std::list<dogen::logical::entities::name>& object_template::parents() const {
    return parents_;
}

std::list<dogen::logical::entities::name>& object_template::parents() {
    return parents_;
}

void object_template::parents(const std::list<dogen::logical::entities::name>& v) {
    parents_ = v;
}

void object_template::parents(const std::list<dogen::logical::entities::name>&& v) {
    parents_ = std::move(v);
}

bool object_template::is_child() const {
    return is_child_;
}

void object_template::is_child(const bool v) {
    is_child_ = v;
}

}
