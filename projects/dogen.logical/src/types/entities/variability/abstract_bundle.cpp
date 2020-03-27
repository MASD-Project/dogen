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
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.variability/io/entities/binding_point_io.hpp"
#include "dogen.logical/types/entities/variability/abstract_bundle.hpp"

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

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::variability::entities::binding_point>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::logical::entities::variability {

abstract_bundle::abstract_bundle()
    : generate_registration_(static_cast<bool>(0)),
      generate_static_configuration_(static_cast<bool>(0)),
      requires_manual_default_constructor_(static_cast<bool>(0)) { }

abstract_bundle::abstract_bundle(abstract_bundle&& rhs)
    : dogen::logical::entities::element(
        std::forward<dogen::logical::entities::element>(rhs)),
      transparent_associations_(std::move(rhs.transparent_associations_)),
      opaque_associations_(std::move(rhs.opaque_associations_)),
      associative_container_keys_(std::move(rhs.associative_container_keys_)),
      key_prefix_(std::move(rhs.key_prefix_)),
      generate_registration_(std::move(rhs.generate_registration_)),
      generate_static_configuration_(std::move(rhs.generate_static_configuration_)),
      requires_manual_default_constructor_(std::move(rhs.requires_manual_default_constructor_)),
      default_binding_point_(std::move(rhs.default_binding_point_)) { }

abstract_bundle::abstract_bundle(
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
    const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& archetype_location_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::list<dogen::logical::entities::name>& transparent_associations,
    const std::list<dogen::logical::entities::name>& opaque_associations,
    const std::list<dogen::logical::entities::name>& associative_container_keys,
    const std::string& key_prefix,
    const bool generate_registration,
    const bool generate_static_configuration,
    const bool requires_manual_default_constructor,
    const boost::optional<dogen::variability::entities::binding_point>& default_binding_point)
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
      transparent_associations_(transparent_associations),
      opaque_associations_(opaque_associations),
      associative_container_keys_(associative_container_keys),
      key_prefix_(key_prefix),
      generate_registration_(generate_registration),
      generate_static_configuration_(generate_static_configuration),
      requires_manual_default_constructor_(requires_manual_default_constructor),
      default_binding_point_(default_binding_point) { }

void abstract_bundle::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::variability::abstract_bundle\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"transparent_associations\": " << transparent_associations_ << ", "
      << "\"opaque_associations\": " << opaque_associations_ << ", "
      << "\"associative_container_keys\": " << associative_container_keys_ << ", "
      << "\"key_prefix\": " << "\"" << tidy_up_string(key_prefix_) << "\"" << ", "
      << "\"generate_registration\": " << generate_registration_ << ", "
      << "\"generate_static_configuration\": " << generate_static_configuration_ << ", "
      << "\"requires_manual_default_constructor\": " << requires_manual_default_constructor_ << ", "
      << "\"default_binding_point\": " << default_binding_point_
      << " }";
}

void abstract_bundle::swap(abstract_bundle& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(transparent_associations_, other.transparent_associations_);
    swap(opaque_associations_, other.opaque_associations_);
    swap(associative_container_keys_, other.associative_container_keys_);
    swap(key_prefix_, other.key_prefix_);
    swap(generate_registration_, other.generate_registration_);
    swap(generate_static_configuration_, other.generate_static_configuration_);
    swap(requires_manual_default_constructor_, other.requires_manual_default_constructor_);
    swap(default_binding_point_, other.default_binding_point_);
}

bool abstract_bundle::compare(const abstract_bundle& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        transparent_associations_ == rhs.transparent_associations_ &&
        opaque_associations_ == rhs.opaque_associations_ &&
        associative_container_keys_ == rhs.associative_container_keys_ &&
        key_prefix_ == rhs.key_prefix_ &&
        generate_registration_ == rhs.generate_registration_ &&
        generate_static_configuration_ == rhs.generate_static_configuration_ &&
        requires_manual_default_constructor_ == rhs.requires_manual_default_constructor_ &&
        default_binding_point_ == rhs.default_binding_point_;
}

const std::list<dogen::logical::entities::name>& abstract_bundle::transparent_associations() const {
    return transparent_associations_;
}

std::list<dogen::logical::entities::name>& abstract_bundle::transparent_associations() {
    return transparent_associations_;
}

void abstract_bundle::transparent_associations(const std::list<dogen::logical::entities::name>& v) {
    transparent_associations_ = v;
}

void abstract_bundle::transparent_associations(const std::list<dogen::logical::entities::name>&& v) {
    transparent_associations_ = std::move(v);
}

const std::list<dogen::logical::entities::name>& abstract_bundle::opaque_associations() const {
    return opaque_associations_;
}

std::list<dogen::logical::entities::name>& abstract_bundle::opaque_associations() {
    return opaque_associations_;
}

void abstract_bundle::opaque_associations(const std::list<dogen::logical::entities::name>& v) {
    opaque_associations_ = v;
}

void abstract_bundle::opaque_associations(const std::list<dogen::logical::entities::name>&& v) {
    opaque_associations_ = std::move(v);
}

const std::list<dogen::logical::entities::name>& abstract_bundle::associative_container_keys() const {
    return associative_container_keys_;
}

std::list<dogen::logical::entities::name>& abstract_bundle::associative_container_keys() {
    return associative_container_keys_;
}

void abstract_bundle::associative_container_keys(const std::list<dogen::logical::entities::name>& v) {
    associative_container_keys_ = v;
}

void abstract_bundle::associative_container_keys(const std::list<dogen::logical::entities::name>&& v) {
    associative_container_keys_ = std::move(v);
}

const std::string& abstract_bundle::key_prefix() const {
    return key_prefix_;
}

std::string& abstract_bundle::key_prefix() {
    return key_prefix_;
}

void abstract_bundle::key_prefix(const std::string& v) {
    key_prefix_ = v;
}

void abstract_bundle::key_prefix(const std::string&& v) {
    key_prefix_ = std::move(v);
}

bool abstract_bundle::generate_registration() const {
    return generate_registration_;
}

void abstract_bundle::generate_registration(const bool v) {
    generate_registration_ = v;
}

bool abstract_bundle::generate_static_configuration() const {
    return generate_static_configuration_;
}

void abstract_bundle::generate_static_configuration(const bool v) {
    generate_static_configuration_ = v;
}

bool abstract_bundle::requires_manual_default_constructor() const {
    return requires_manual_default_constructor_;
}

void abstract_bundle::requires_manual_default_constructor(const bool v) {
    requires_manual_default_constructor_ = v;
}

const boost::optional<dogen::variability::entities::binding_point>& abstract_bundle::default_binding_point() const {
    return default_binding_point_;
}

boost::optional<dogen::variability::entities::binding_point>& abstract_bundle::default_binding_point() {
    return default_binding_point_;
}

void abstract_bundle::default_binding_point(const boost::optional<dogen::variability::entities::binding_point>& v) {
    default_binding_point_ = v;
}

void abstract_bundle::default_binding_point(const boost::optional<dogen::variability::entities::binding_point>&& v) {
    default_binding_point_ = std::move(v);
}

}
