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
#include <boost/algorithm/string.hpp>
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/io/entities/variability/abstract_bundle_io.hpp"
#include "dogen.logical/io/entities/variability/feature_template_io.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::variability::feature_template>& v) {
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

namespace dogen::logical::entities::variability {

feature_template_bundle::feature_template_bundle(
    const dogen::identification::entities::logical_name& name,
    const std::string& documentation,
    const dogen::identification::entities::codec_provenance& provenance,
    const dogen::identification::entities::logical_id& contained_by,
    const bool in_global_module,
    const dogen::logical::entities::stereotypes& stereotypes,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::identification::entities::label>& labels,
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::list<dogen::logical::entities::helper_properties>& helper_properties,
    const std::list<dogen::identification::entities::logical_name>& transparent_associations,
    const std::list<dogen::identification::entities::logical_name>& opaque_associations,
    const std::list<dogen::identification::entities::logical_name>& associative_container_keys,
    const std::string& key_prefix,
    const bool generate_registration,
    const bool generate_static_configuration,
    const bool requires_manual_default_constructor,
    const boost::optional<dogen::variability::entities::binding_point>& default_binding_point,
    const std::list<dogen::logical::entities::variability::feature_template>& feature_templates,
    const std::string& instantiation_domain_name)
    : dogen::logical::entities::variability::abstract_bundle(
      name,
      documentation,
      provenance,
      contained_by,
      in_global_module,
      stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      generability_status,
      decoration,
      helper_properties,
      transparent_associations,
      opaque_associations,
      associative_container_keys,
      key_prefix,
      generate_registration,
      generate_static_configuration,
      requires_manual_default_constructor,
      default_binding_point),
      feature_templates_(feature_templates),
      instantiation_domain_name_(instantiation_domain_name) { }

void feature_template_bundle::accept(const element_visitor& v) const {
    v.visit(*this);
}

void feature_template_bundle::accept(element_visitor& v) const {
    v.visit(*this);
    }

void feature_template_bundle::accept(const element_visitor& v) {
    v.visit(*this);
}

void feature_template_bundle::accept(element_visitor& v) {
    v.visit(*this);
}

void feature_template_bundle::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::variability::feature_template_bundle\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::variability::abstract_bundle::to_stream(s);
    s << ", "
      << "\"feature_templates\": " << feature_templates_ << ", "
      << "\"instantiation_domain_name\": " << "\"" << tidy_up_string(instantiation_domain_name_) << "\""
      << " }";
}

void feature_template_bundle::swap(feature_template_bundle& other) noexcept {
    dogen::logical::entities::variability::abstract_bundle::swap(other);

    using std::swap;
    swap(feature_templates_, other.feature_templates_);
    swap(instantiation_domain_name_, other.instantiation_domain_name_);
}

bool feature_template_bundle::equals(const dogen::logical::entities::element& other) const {
    const feature_template_bundle* const p(dynamic_cast<const feature_template_bundle* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool feature_template_bundle::operator==(const feature_template_bundle& rhs) const {
    return dogen::logical::entities::variability::abstract_bundle::compare(rhs) &&
        feature_templates_ == rhs.feature_templates_ &&
        instantiation_domain_name_ == rhs.instantiation_domain_name_;
}

feature_template_bundle& feature_template_bundle::operator=(feature_template_bundle other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::logical::entities::variability::feature_template>& feature_template_bundle::feature_templates() const {
    return feature_templates_;
}

std::list<dogen::logical::entities::variability::feature_template>& feature_template_bundle::feature_templates() {
    return feature_templates_;
}

void feature_template_bundle::feature_templates(const std::list<dogen::logical::entities::variability::feature_template>& v) {
    feature_templates_ = v;
}

void feature_template_bundle::feature_templates(const std::list<dogen::logical::entities::variability::feature_template>&& v) {
    feature_templates_ = std::move(v);
}

const std::string& feature_template_bundle::instantiation_domain_name() const {
    return instantiation_domain_name_;
}

std::string& feature_template_bundle::instantiation_domain_name() {
    return instantiation_domain_name_;
}

void feature_template_bundle::instantiation_domain_name(const std::string& v) {
    instantiation_domain_name_ = v;
}

void feature_template_bundle::instantiation_domain_name(const std::string&& v) {
    instantiation_domain_name_ = std::move(v);
}

}
