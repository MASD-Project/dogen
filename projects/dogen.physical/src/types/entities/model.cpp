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
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.variability/types/entities/configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::configuration>& lhs,
const boost::shared_ptr<dogen::variability::entities::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::physical::entities::artefact>& lhs,
const boost::shared_ptr<dogen::physical::entities::artefact>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::physical::entities {

model::model()
    : has_generatable_artefacts_(static_cast<bool>(0)) { }

model::model(
    const dogen::identification::entities::physical_meta_name& meta_name,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const dogen::identification::entities::logical_provenance& provenance,
    const dogen::identification::entities::physical_name& name,
    const std::string& technical_space,
    const std::list<boost::filesystem::path>& managed_directories,
    const dogen::physical::entities::outputting_properties& outputting_properties,
    const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& orphan_artefacts,
    const dogen::physical::entities::meta_model_properties& meta_model_properties,
    const bool has_generatable_artefacts,
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::region>& regions_by_logical_id)
    : meta_name_(meta_name),
      configuration_(configuration),
      provenance_(provenance),
      name_(name),
      technical_space_(technical_space),
      managed_directories_(managed_directories),
      outputting_properties_(outputting_properties),
      orphan_artefacts_(orphan_artefacts),
      meta_model_properties_(meta_model_properties),
      has_generatable_artefacts_(has_generatable_artefacts),
      regions_by_logical_id_(regions_by_logical_id) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(meta_name_, other.meta_name_);
    swap(configuration_, other.configuration_);
    swap(provenance_, other.provenance_);
    swap(name_, other.name_);
    swap(technical_space_, other.technical_space_);
    swap(managed_directories_, other.managed_directories_);
    swap(outputting_properties_, other.outputting_properties_);
    swap(orphan_artefacts_, other.orphan_artefacts_);
    swap(meta_model_properties_, other.meta_model_properties_);
    swap(has_generatable_artefacts_, other.has_generatable_artefacts_);
    swap(regions_by_logical_id_, other.regions_by_logical_id_);
}

bool model::operator==(const model& rhs) const {
    return meta_name_ == rhs.meta_name_ &&
        configuration_ == rhs.configuration_ &&
        provenance_ == rhs.provenance_ &&
        name_ == rhs.name_ &&
        technical_space_ == rhs.technical_space_ &&
        managed_directories_ == rhs.managed_directories_ &&
        outputting_properties_ == rhs.outputting_properties_ &&
        orphan_artefacts_ == rhs.orphan_artefacts_ &&
        meta_model_properties_ == rhs.meta_model_properties_ &&
        has_generatable_artefacts_ == rhs.has_generatable_artefacts_ &&
        regions_by_logical_id_ == rhs.regions_by_logical_id_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::physical_meta_name& model::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::physical_meta_name& model::meta_name() {
    return meta_name_;
}

void model::meta_name(const dogen::identification::entities::physical_meta_name& v) {
    meta_name_ = v;
}

void model::meta_name(const dogen::identification::entities::physical_meta_name&& v) {
    meta_name_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::entities::configuration>& model::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::entities::configuration>& model::configuration() {
    return configuration_;
}

void model::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    configuration_ = v;
}

void model::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::identification::entities::logical_provenance& model::provenance() const {
    return provenance_;
}

dogen::identification::entities::logical_provenance& model::provenance() {
    return provenance_;
}

void model::provenance(const dogen::identification::entities::logical_provenance& v) {
    provenance_ = v;
}

void model::provenance(const dogen::identification::entities::logical_provenance&& v) {
    provenance_ = std::move(v);
}

const dogen::identification::entities::physical_name& model::name() const {
    return name_;
}

dogen::identification::entities::physical_name& model::name() {
    return name_;
}

void model::name(const dogen::identification::entities::physical_name& v) {
    name_ = v;
}

void model::name(const dogen::identification::entities::physical_name&& v) {
    name_ = std::move(v);
}

const std::string& model::technical_space() const {
    return technical_space_;
}

std::string& model::technical_space() {
    return technical_space_;
}

void model::technical_space(const std::string& v) {
    technical_space_ = v;
}

void model::technical_space(const std::string&& v) {
    technical_space_ = std::move(v);
}

const std::list<boost::filesystem::path>& model::managed_directories() const {
    return managed_directories_;
}

std::list<boost::filesystem::path>& model::managed_directories() {
    return managed_directories_;
}

void model::managed_directories(const std::list<boost::filesystem::path>& v) {
    managed_directories_ = v;
}

void model::managed_directories(const std::list<boost::filesystem::path>&& v) {
    managed_directories_ = std::move(v);
}

const dogen::physical::entities::outputting_properties& model::outputting_properties() const {
    return outputting_properties_;
}

dogen::physical::entities::outputting_properties& model::outputting_properties() {
    return outputting_properties_;
}

void model::outputting_properties(const dogen::physical::entities::outputting_properties& v) {
    outputting_properties_ = v;
}

void model::outputting_properties(const dogen::physical::entities::outputting_properties&& v) {
    outputting_properties_ = std::move(v);
}

const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& model::orphan_artefacts() const {
    return orphan_artefacts_;
}

std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& model::orphan_artefacts() {
    return orphan_artefacts_;
}

void model::orphan_artefacts(const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& v) {
    orphan_artefacts_ = v;
}

void model::orphan_artefacts(const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >&& v) {
    orphan_artefacts_ = std::move(v);
}

const dogen::physical::entities::meta_model_properties& model::meta_model_properties() const {
    return meta_model_properties_;
}

dogen::physical::entities::meta_model_properties& model::meta_model_properties() {
    return meta_model_properties_;
}

void model::meta_model_properties(const dogen::physical::entities::meta_model_properties& v) {
    meta_model_properties_ = v;
}

void model::meta_model_properties(const dogen::physical::entities::meta_model_properties&& v) {
    meta_model_properties_ = std::move(v);
}

bool model::has_generatable_artefacts() const {
    return has_generatable_artefacts_;
}

void model::has_generatable_artefacts(const bool v) {
    has_generatable_artefacts_ = v;
}

const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::region>& model::regions_by_logical_id() const {
    return regions_by_logical_id_;
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::region>& model::regions_by_logical_id() {
    return regions_by_logical_id_;
}

void model::regions_by_logical_id(const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::region>& v) {
    regions_by_logical_id_ = v;
}

void model::regions_by_logical_id(const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::region>&& v) {
    regions_by_logical_id_ = std::move(v);
}

}
