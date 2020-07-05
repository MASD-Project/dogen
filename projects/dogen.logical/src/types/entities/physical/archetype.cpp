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
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/io/entities/physical/relations_io.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/io/entities/physical/archetype_generator_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::logical::entities::physical {

archetype::archetype()
    : major_technical_space_(static_cast<dogen::logical::entities::technical_space>(0)) { }

archetype::archetype(
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
    const std::list<dogen::logical::entities::label>& labels,
    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::string& id,
    const dogen::logical::entities::technical_space major_technical_space,
    const std::string& meta_model_name,
    const std::string& backend_name,
    const std::string& facet_name,
    const std::string& part_id,
    const std::string& logical_meta_element_id,
    const dogen::logical::entities::physical::relations& relations,
    const dogen::logical::entities::physical::archetype_generator& generator)
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
      labels,
      artefact_properties,
      enablement_properties,
      decoration),
      id_(id),
      major_technical_space_(major_technical_space),
      meta_model_name_(meta_model_name),
      backend_name_(backend_name),
      facet_name_(facet_name),
      part_id_(part_id),
      logical_meta_element_id_(logical_meta_element_id),
      relations_(relations),
      generator_(generator) { }

void archetype::accept(const element_visitor& v) const {
    v.visit(*this);
}

void archetype::accept(element_visitor& v) const {
    v.visit(*this);
    }

void archetype::accept(const element_visitor& v) {
    v.visit(*this);
}

void archetype::accept(element_visitor& v) {
    v.visit(*this);
}

void archetype::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::physical::archetype\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"id\": " << "\"" << tidy_up_string(id_) << "\"" << ", "
      << "\"major_technical_space\": " << major_technical_space_ << ", "
      << "\"meta_model_name\": " << "\"" << tidy_up_string(meta_model_name_) << "\"" << ", "
      << "\"backend_name\": " << "\"" << tidy_up_string(backend_name_) << "\"" << ", "
      << "\"facet_name\": " << "\"" << tidy_up_string(facet_name_) << "\"" << ", "
      << "\"part_id\": " << "\"" << tidy_up_string(part_id_) << "\"" << ", "
      << "\"logical_meta_element_id\": " << "\"" << tidy_up_string(logical_meta_element_id_) << "\"" << ", "
      << "\"relations\": " << relations_ << ", "
      << "\"generator\": " << generator_
      << " }";
}

void archetype::swap(archetype& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(id_, other.id_);
    swap(major_technical_space_, other.major_technical_space_);
    swap(meta_model_name_, other.meta_model_name_);
    swap(backend_name_, other.backend_name_);
    swap(facet_name_, other.facet_name_);
    swap(part_id_, other.part_id_);
    swap(logical_meta_element_id_, other.logical_meta_element_id_);
    swap(relations_, other.relations_);
    swap(generator_, other.generator_);
}

bool archetype::equals(const dogen::logical::entities::element& other) const {
    const archetype* const p(dynamic_cast<const archetype* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool archetype::operator==(const archetype& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        id_ == rhs.id_ &&
        major_technical_space_ == rhs.major_technical_space_ &&
        meta_model_name_ == rhs.meta_model_name_ &&
        backend_name_ == rhs.backend_name_ &&
        facet_name_ == rhs.facet_name_ &&
        part_id_ == rhs.part_id_ &&
        logical_meta_element_id_ == rhs.logical_meta_element_id_ &&
        relations_ == rhs.relations_ &&
        generator_ == rhs.generator_;
}

archetype& archetype::operator=(archetype other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& archetype::id() const {
    return id_;
}

std::string& archetype::id() {
    return id_;
}

void archetype::id(const std::string& v) {
    id_ = v;
}

void archetype::id(const std::string&& v) {
    id_ = std::move(v);
}

dogen::logical::entities::technical_space archetype::major_technical_space() const {
    return major_technical_space_;
}

void archetype::major_technical_space(const dogen::logical::entities::technical_space v) {
    major_technical_space_ = v;
}

const std::string& archetype::meta_model_name() const {
    return meta_model_name_;
}

std::string& archetype::meta_model_name() {
    return meta_model_name_;
}

void archetype::meta_model_name(const std::string& v) {
    meta_model_name_ = v;
}

void archetype::meta_model_name(const std::string&& v) {
    meta_model_name_ = std::move(v);
}

const std::string& archetype::backend_name() const {
    return backend_name_;
}

std::string& archetype::backend_name() {
    return backend_name_;
}

void archetype::backend_name(const std::string& v) {
    backend_name_ = v;
}

void archetype::backend_name(const std::string&& v) {
    backend_name_ = std::move(v);
}

const std::string& archetype::facet_name() const {
    return facet_name_;
}

std::string& archetype::facet_name() {
    return facet_name_;
}

void archetype::facet_name(const std::string& v) {
    facet_name_ = v;
}

void archetype::facet_name(const std::string&& v) {
    facet_name_ = std::move(v);
}

const std::string& archetype::part_id() const {
    return part_id_;
}

std::string& archetype::part_id() {
    return part_id_;
}

void archetype::part_id(const std::string& v) {
    part_id_ = v;
}

void archetype::part_id(const std::string&& v) {
    part_id_ = std::move(v);
}

const std::string& archetype::logical_meta_element_id() const {
    return logical_meta_element_id_;
}

std::string& archetype::logical_meta_element_id() {
    return logical_meta_element_id_;
}

void archetype::logical_meta_element_id(const std::string& v) {
    logical_meta_element_id_ = v;
}

void archetype::logical_meta_element_id(const std::string&& v) {
    logical_meta_element_id_ = std::move(v);
}

const dogen::logical::entities::physical::relations& archetype::relations() const {
    return relations_;
}

dogen::logical::entities::physical::relations& archetype::relations() {
    return relations_;
}

void archetype::relations(const dogen::logical::entities::physical::relations& v) {
    relations_ = v;
}

void archetype::relations(const dogen::logical::entities::physical::relations&& v) {
    relations_ = std::move(v);
}

const dogen::logical::entities::physical::archetype_generator& archetype::generator() const {
    return generator_;
}

dogen::logical::entities::physical::archetype_generator& archetype::generator() {
    return generator_;
}

void archetype::generator(const dogen::logical::entities::physical::archetype_generator& v) {
    generator_ = v;
}

void archetype::generator(const dogen::logical::entities::physical::archetype_generator&& v) {
    generator_ = std::move(v);
}

}
