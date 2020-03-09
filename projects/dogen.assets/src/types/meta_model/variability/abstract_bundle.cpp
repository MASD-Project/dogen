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
#include "dogen.archetypes/io/location_io.hpp"
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.variability/io/meta_model/binding_point_io.hpp"
#include "dogen.assets/types/meta_model/variability/abstract_bundle.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::assets::meta_model::name>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::variability::meta_model::binding_point>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::assets::meta_model::variability {

abstract_bundle::abstract_bundle()
    : generate_static_configuration_(static_cast<bool>(0)),
      requires_manual_default_constructor_(static_cast<bool>(0)) { }

abstract_bundle::abstract_bundle(abstract_bundle&& rhs)
    : dogen::assets::meta_model::element(
        std::forward<dogen::assets::meta_model::element>(rhs)),
      transparent_associations_(std::move(rhs.transparent_associations_)),
      opaque_associations_(std::move(rhs.opaque_associations_)),
      associative_container_keys_(std::move(rhs.associative_container_keys_)),
      generate_static_configuration_(std::move(rhs.generate_static_configuration_)),
      requires_manual_default_constructor_(std::move(rhs.requires_manual_default_constructor_)),
      location_(std::move(rhs.location_)),
      default_binding_point_(std::move(rhs.default_binding_point_)) { }

abstract_bundle::abstract_bundle(
    const dogen::assets::meta_model::name& name,
    const std::string& documentation,
    const dogen::assets::meta_model::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::assets::meta_model::name& meta_name,
    const dogen::assets::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<dogen::assets::meta_model::technical_space, boost::optional<dogen::assets::meta_model::decoration::element_properties> >& decoration,
    const std::list<dogen::assets::meta_model::name>& transparent_associations,
    const std::list<dogen::assets::meta_model::name>& opaque_associations,
    const std::list<dogen::assets::meta_model::name>& associative_container_keys,
    const bool generate_static_configuration,
    const bool requires_manual_default_constructor,
    const dogen::archetypes::location& location,
    const boost::optional<dogen::variability::meta_model::binding_point>& default_binding_point)
    : dogen::assets::meta_model::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      origin_element_id,
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
      generate_static_configuration_(generate_static_configuration),
      requires_manual_default_constructor_(requires_manual_default_constructor),
      location_(location),
      default_binding_point_(default_binding_point) { }

void abstract_bundle::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::abstract_bundle\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"transparent_associations\": " << transparent_associations_ << ", "
      << "\"opaque_associations\": " << opaque_associations_ << ", "
      << "\"associative_container_keys\": " << associative_container_keys_ << ", "
      << "\"generate_static_configuration\": " << generate_static_configuration_ << ", "
      << "\"requires_manual_default_constructor\": " << requires_manual_default_constructor_ << ", "
      << "\"location\": " << location_ << ", "
      << "\"default_binding_point\": " << default_binding_point_
      << " }";
}

void abstract_bundle::swap(abstract_bundle& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(transparent_associations_, other.transparent_associations_);
    swap(opaque_associations_, other.opaque_associations_);
    swap(associative_container_keys_, other.associative_container_keys_);
    swap(generate_static_configuration_, other.generate_static_configuration_);
    swap(requires_manual_default_constructor_, other.requires_manual_default_constructor_);
    swap(location_, other.location_);
    swap(default_binding_point_, other.default_binding_point_);
}

bool abstract_bundle::compare(const abstract_bundle& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        transparent_associations_ == rhs.transparent_associations_ &&
        opaque_associations_ == rhs.opaque_associations_ &&
        associative_container_keys_ == rhs.associative_container_keys_ &&
        generate_static_configuration_ == rhs.generate_static_configuration_ &&
        requires_manual_default_constructor_ == rhs.requires_manual_default_constructor_ &&
        location_ == rhs.location_ &&
        default_binding_point_ == rhs.default_binding_point_;
}

const std::list<dogen::assets::meta_model::name>& abstract_bundle::transparent_associations() const {
    return transparent_associations_;
}

std::list<dogen::assets::meta_model::name>& abstract_bundle::transparent_associations() {
    return transparent_associations_;
}

void abstract_bundle::transparent_associations(const std::list<dogen::assets::meta_model::name>& v) {
    transparent_associations_ = v;
}

void abstract_bundle::transparent_associations(const std::list<dogen::assets::meta_model::name>&& v) {
    transparent_associations_ = std::move(v);
}

const std::list<dogen::assets::meta_model::name>& abstract_bundle::opaque_associations() const {
    return opaque_associations_;
}

std::list<dogen::assets::meta_model::name>& abstract_bundle::opaque_associations() {
    return opaque_associations_;
}

void abstract_bundle::opaque_associations(const std::list<dogen::assets::meta_model::name>& v) {
    opaque_associations_ = v;
}

void abstract_bundle::opaque_associations(const std::list<dogen::assets::meta_model::name>&& v) {
    opaque_associations_ = std::move(v);
}

const std::list<dogen::assets::meta_model::name>& abstract_bundle::associative_container_keys() const {
    return associative_container_keys_;
}

std::list<dogen::assets::meta_model::name>& abstract_bundle::associative_container_keys() {
    return associative_container_keys_;
}

void abstract_bundle::associative_container_keys(const std::list<dogen::assets::meta_model::name>& v) {
    associative_container_keys_ = v;
}

void abstract_bundle::associative_container_keys(const std::list<dogen::assets::meta_model::name>&& v) {
    associative_container_keys_ = std::move(v);
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

const dogen::archetypes::location& abstract_bundle::location() const {
    return location_;
}

dogen::archetypes::location& abstract_bundle::location() {
    return location_;
}

void abstract_bundle::location(const dogen::archetypes::location& v) {
    location_ = v;
}

void abstract_bundle::location(const dogen::archetypes::location&& v) {
    location_ = std::move(v);
}

const boost::optional<dogen::variability::meta_model::binding_point>& abstract_bundle::default_binding_point() const {
    return default_binding_point_;
}

boost::optional<dogen::variability::meta_model::binding_point>& abstract_bundle::default_binding_point() {
    return default_binding_point_;
}

void abstract_bundle::default_binding_point(const boost::optional<dogen::variability::meta_model::binding_point>& v) {
    default_binding_point_ = v;
}

void abstract_bundle::default_binding_point(const boost::optional<dogen::variability::meta_model::binding_point>&& v) {
    default_binding_point_ = std::move(v);
}

}