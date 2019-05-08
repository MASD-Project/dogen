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
#include "masd.dogen.coding/types/meta_model/element_visitor.hpp"
#include "masd.dogen.coding/io/meta_model/variability/feature_template_group_io.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group_registrar.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<masd::dogen::coding::meta_model::variability::feature_template_group>& v) {
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

feature_template_group_registrar::feature_template_group_registrar(
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
    const std::list<masd::dogen::coding::meta_model::variability::feature_template_group>& template_groups)
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
      template_groups_(template_groups) { }

void feature_template_group_registrar::accept(const element_visitor& v) const {
    v.visit(*this);
}

void feature_template_group_registrar::accept(element_visitor& v) const {
    v.visit(*this);
    }

void feature_template_group_registrar::accept(const element_visitor& v) {
    v.visit(*this);
}

void feature_template_group_registrar::accept(element_visitor& v) {
    v.visit(*this);
}

void feature_template_group_registrar::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::coding::meta_model::variability::feature_template_group_registrar\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"template_groups\": " << template_groups_
      << " }";
}

void feature_template_group_registrar::swap(feature_template_group_registrar& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(template_groups_, other.template_groups_);
}

bool feature_template_group_registrar::equals(const masd::dogen::coding::meta_model::element& other) const {
    const feature_template_group_registrar* const p(dynamic_cast<const feature_template_group_registrar* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool feature_template_group_registrar::operator==(const feature_template_group_registrar& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        template_groups_ == rhs.template_groups_;
}

feature_template_group_registrar& feature_template_group_registrar::operator=(feature_template_group_registrar other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<masd::dogen::coding::meta_model::variability::feature_template_group>& feature_template_group_registrar::template_groups() const {
    return template_groups_;
}

std::list<masd::dogen::coding::meta_model::variability::feature_template_group>& feature_template_group_registrar::template_groups() {
    return template_groups_;
}

void feature_template_group_registrar::template_groups(const std::list<masd::dogen::coding::meta_model::variability::feature_template_group>& v) {
    template_groups_ = v;
}

void feature_template_group_registrar::template_groups(const std::list<masd::dogen::coding::meta_model::variability::feature_template_group>&& v) {
    template_groups_ = std::move(v);
}

}
