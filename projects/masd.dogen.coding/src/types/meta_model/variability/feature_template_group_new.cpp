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
#include "masd.dogen.coding/io/meta_model/element_io.hpp"
#include "masd.dogen.coding/types/meta_model/variability/element_visitor.hpp"
#include "masd.dogen.coding/io/meta_model/variability/feature_template_new_io.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group_new.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<masd::dogen::coding::meta_model::variability::feature_template_new>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace masd::dogen::coding::meta_model::variability {

feature_template_group_new::feature_template_group_new(
    const masd::dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const masd::dogen::coding::meta_model::name& meta_name,
    const masd::dogen::coding::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration,
    const bool is_element_extension,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<masd::dogen::coding::meta_model::decoration::element_properties>& decoration,
    const std::list<masd::dogen::coding::meta_model::variability::feature_template_new>& feature_templates)
    : masd::dogen::coding::meta_model::element(
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
      feature_templates_(feature_templates) { }

void feature_template_group_new::accept(const masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void feature_template_group_new::accept(masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void feature_template_group_new::accept(const masd::dogen::coding::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void feature_template_group_new::accept(masd::dogen::coding::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void feature_template_group_new::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::coding::meta_model::variability::feature_template_group_new\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"feature_templates\": " << feature_templates_
      << " }";
}

void feature_template_group_new::swap(feature_template_group_new& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(feature_templates_, other.feature_templates_);
}

bool feature_template_group_new::equals(const masd::dogen::coding::meta_model::element& other) const {
    const feature_template_group_new* const p(dynamic_cast<const feature_template_group_new* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool feature_template_group_new::operator==(const feature_template_group_new& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        feature_templates_ == rhs.feature_templates_;
}

feature_template_group_new& feature_template_group_new::operator=(feature_template_group_new other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<masd::dogen::coding::meta_model::variability::feature_template_new>& feature_template_group_new::feature_templates() const {
    return feature_templates_;
}

std::list<masd::dogen::coding::meta_model::variability::feature_template_new>& feature_template_group_new::feature_templates() {
    return feature_templates_;
}

void feature_template_group_new::feature_templates(const std::list<masd::dogen::coding::meta_model::variability::feature_template_new>& v) {
    feature_templates_ = v;
}

void feature_template_group_new::feature_templates(const std::list<masd::dogen::coding::meta_model::variability::feature_template_new>&& v) {
    feature_templates_ = std::move(v);
}

}
