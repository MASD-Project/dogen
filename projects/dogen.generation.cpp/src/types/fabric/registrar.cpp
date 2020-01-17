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
#include "dogen.generation.cpp/types/element_visitor.hpp"
#include "dogen.generation.cpp/types/fabric/registrar.hpp"

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

namespace dogen::generation::cpp::fabric {

registrar::registrar(
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
    const bool is_element_extension,
    const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
    const std::list<dogen::assets::meta_model::name>& leaves,
    const std::list<dogen::assets::meta_model::name>& model_dependencies,
    const std::list<dogen::assets::meta_model::name>& registrar_dependencies)
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
      is_element_extension,
      artefact_properties,
      archetype_location_properties,
      decoration),
      leaves_(leaves),
      model_dependencies_(model_dependencies),
      registrar_dependencies_(registrar_dependencies) { }

void registrar::accept(const dogen::assets::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void registrar::accept(dogen::assets::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void registrar::accept(const dogen::assets::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void registrar::accept(dogen::assets::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void registrar::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::generation::cpp::fabric::registrar\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"leaves\": " << leaves_ << ", "
      << "\"model_dependencies\": " << model_dependencies_ << ", "
      << "\"registrar_dependencies\": " << registrar_dependencies_
      << " }";
}

void registrar::swap(registrar& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(leaves_, other.leaves_);
    swap(model_dependencies_, other.model_dependencies_);
    swap(registrar_dependencies_, other.registrar_dependencies_);
}

bool registrar::equals(const dogen::assets::meta_model::element& other) const {
    const registrar* const p(dynamic_cast<const registrar* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool registrar::operator==(const registrar& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        leaves_ == rhs.leaves_ &&
        model_dependencies_ == rhs.model_dependencies_ &&
        registrar_dependencies_ == rhs.registrar_dependencies_;
}

registrar& registrar::operator=(registrar other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::assets::meta_model::name>& registrar::leaves() const {
    return leaves_;
}

std::list<dogen::assets::meta_model::name>& registrar::leaves() {
    return leaves_;
}

void registrar::leaves(const std::list<dogen::assets::meta_model::name>& v) {
    leaves_ = v;
}

void registrar::leaves(const std::list<dogen::assets::meta_model::name>&& v) {
    leaves_ = std::move(v);
}

const std::list<dogen::assets::meta_model::name>& registrar::model_dependencies() const {
    return model_dependencies_;
}

std::list<dogen::assets::meta_model::name>& registrar::model_dependencies() {
    return model_dependencies_;
}

void registrar::model_dependencies(const std::list<dogen::assets::meta_model::name>& v) {
    model_dependencies_ = v;
}

void registrar::model_dependencies(const std::list<dogen::assets::meta_model::name>&& v) {
    model_dependencies_ = std::move(v);
}

const std::list<dogen::assets::meta_model::name>& registrar::registrar_dependencies() const {
    return registrar_dependencies_;
}

std::list<dogen::assets::meta_model::name>& registrar::registrar_dependencies() {
    return registrar_dependencies_;
}

void registrar::registrar_dependencies(const std::list<dogen::assets::meta_model::name>& v) {
    registrar_dependencies_ = v;
}

void registrar::registrar_dependencies(const std::list<dogen::assets::meta_model::name>&& v) {
    registrar_dependencies_ = std::move(v);
}

}
