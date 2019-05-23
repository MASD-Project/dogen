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
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.assets/types/meta_model/element_visitor.hpp"
#include "dogen.assets/types/meta_model/variability/feature_bundle.hpp"
#include "dogen.assets/io/meta_model/variability/feature_template_io.hpp"

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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::assets::meta_model::variability::feature_template>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::assets::meta_model::variability {

feature_bundle::feature_bundle(
    const dogen::assets::meta_model::name& name,
    const std::string& documentation,
    const dogen::assets::meta_model::origin_types origin_type,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::assets::meta_model::name& meta_name,
    const dogen::assets::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const bool is_element_extension,
    const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
    const std::list<dogen::assets::meta_model::name>& transparent_associations,
    const std::list<dogen::assets::meta_model::name>& opaque_associations,
    const std::list<dogen::assets::meta_model::name>& associative_container_keys,
    const std::list<dogen::assets::meta_model::variability::feature_template>& feature_templates)
    : dogen::assets::meta_model::element(
      name,
      documentation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      is_element_extension,
      artefact_properties,
      archetype_location_properties,
      decoration),
      transparent_associations_(transparent_associations),
      opaque_associations_(opaque_associations),
      associative_container_keys_(associative_container_keys),
      feature_templates_(feature_templates) { }

void feature_bundle::accept(const element_visitor& v) const {
    v.visit(*this);
}

void feature_bundle::accept(element_visitor& v) const {
    v.visit(*this);
    }

void feature_bundle::accept(const element_visitor& v) {
    v.visit(*this);
}

void feature_bundle::accept(element_visitor& v) {
    v.visit(*this);
}

void feature_bundle::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::feature_bundle\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"transparent_associations\": " << transparent_associations_ << ", "
      << "\"opaque_associations\": " << opaque_associations_ << ", "
      << "\"associative_container_keys\": " << associative_container_keys_ << ", "
      << "\"feature_templates\": " << feature_templates_
      << " }";
}

void feature_bundle::swap(feature_bundle& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(transparent_associations_, other.transparent_associations_);
    swap(opaque_associations_, other.opaque_associations_);
    swap(associative_container_keys_, other.associative_container_keys_);
    swap(feature_templates_, other.feature_templates_);
}

bool feature_bundle::equals(const dogen::assets::meta_model::element& other) const {
    const feature_bundle* const p(dynamic_cast<const feature_bundle* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool feature_bundle::operator==(const feature_bundle& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        transparent_associations_ == rhs.transparent_associations_ &&
        opaque_associations_ == rhs.opaque_associations_ &&
        associative_container_keys_ == rhs.associative_container_keys_ &&
        feature_templates_ == rhs.feature_templates_;
}

feature_bundle& feature_bundle::operator=(feature_bundle other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::assets::meta_model::name>& feature_bundle::transparent_associations() const {
    return transparent_associations_;
}

std::list<dogen::assets::meta_model::name>& feature_bundle::transparent_associations() {
    return transparent_associations_;
}

void feature_bundle::transparent_associations(const std::list<dogen::assets::meta_model::name>& v) {
    transparent_associations_ = v;
}

void feature_bundle::transparent_associations(const std::list<dogen::assets::meta_model::name>&& v) {
    transparent_associations_ = std::move(v);
}

const std::list<dogen::assets::meta_model::name>& feature_bundle::opaque_associations() const {
    return opaque_associations_;
}

std::list<dogen::assets::meta_model::name>& feature_bundle::opaque_associations() {
    return opaque_associations_;
}

void feature_bundle::opaque_associations(const std::list<dogen::assets::meta_model::name>& v) {
    opaque_associations_ = v;
}

void feature_bundle::opaque_associations(const std::list<dogen::assets::meta_model::name>&& v) {
    opaque_associations_ = std::move(v);
}

const std::list<dogen::assets::meta_model::name>& feature_bundle::associative_container_keys() const {
    return associative_container_keys_;
}

std::list<dogen::assets::meta_model::name>& feature_bundle::associative_container_keys() {
    return associative_container_keys_;
}

void feature_bundle::associative_container_keys(const std::list<dogen::assets::meta_model::name>& v) {
    associative_container_keys_ = v;
}

void feature_bundle::associative_container_keys(const std::list<dogen::assets::meta_model::name>&& v) {
    associative_container_keys_ = std::move(v);
}

const std::list<dogen::assets::meta_model::variability::feature_template>& feature_bundle::feature_templates() const {
    return feature_templates_;
}

std::list<dogen::assets::meta_model::variability::feature_template>& feature_bundle::feature_templates() {
    return feature_templates_;
}

void feature_bundle::feature_templates(const std::list<dogen::assets::meta_model::variability::feature_template>& v) {
    feature_templates_ = v;
}

void feature_bundle::feature_templates(const std::list<dogen::assets::meta_model::variability::feature_template>&& v) {
    feature_templates_ = std::move(v);
}

}
