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
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.logical/types/entities/variability/initializer.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::logical_name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::variability {

initializer::initializer(
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
    const std::list<dogen::identification::entities::logical_name>& feature_template_bundles,
    const std::list<dogen::identification::entities::logical_name>& feature_bundles)
    : dogen::logical::entities::element(
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
      helper_properties),
      feature_template_bundles_(feature_template_bundles),
      feature_bundles_(feature_bundles) { }

void initializer::accept(const element_visitor& v) const {
    v.visit(*this);
}

void initializer::accept(element_visitor& v) const {
    v.visit(*this);
    }

void initializer::accept(const element_visitor& v) {
    v.visit(*this);
}

void initializer::accept(element_visitor& v) {
    v.visit(*this);
}

void initializer::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::variability::initializer\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"feature_template_bundles\": " << feature_template_bundles_ << ", "
      << "\"feature_bundles\": " << feature_bundles_
      << " }";
}

void initializer::swap(initializer& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(feature_template_bundles_, other.feature_template_bundles_);
    swap(feature_bundles_, other.feature_bundles_);
}

bool initializer::equals(const dogen::logical::entities::element& other) const {
    const initializer* const p(dynamic_cast<const initializer* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool initializer::operator==(const initializer& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        feature_template_bundles_ == rhs.feature_template_bundles_ &&
        feature_bundles_ == rhs.feature_bundles_;
}

initializer& initializer::operator=(initializer other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::identification::entities::logical_name>& initializer::feature_template_bundles() const {
    return feature_template_bundles_;
}

std::list<dogen::identification::entities::logical_name>& initializer::feature_template_bundles() {
    return feature_template_bundles_;
}

void initializer::feature_template_bundles(const std::list<dogen::identification::entities::logical_name>& v) {
    feature_template_bundles_ = v;
}

void initializer::feature_template_bundles(const std::list<dogen::identification::entities::logical_name>&& v) {
    feature_template_bundles_ = std::move(v);
}

const std::list<dogen::identification::entities::logical_name>& initializer::feature_bundles() const {
    return feature_bundles_;
}

std::list<dogen::identification::entities::logical_name>& initializer::feature_bundles() {
    return feature_bundles_;
}

void initializer::feature_bundles(const std::list<dogen::identification::entities::logical_name>& v) {
    feature_bundles_ = v;
}

void initializer::feature_bundles(const std::list<dogen::identification::entities::logical_name>&& v) {
    feature_bundles_ = std::move(v);
}

}
