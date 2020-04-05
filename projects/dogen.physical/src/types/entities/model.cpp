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

model::model(
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::string& origin_sha1_hash,
    const dogen::physical::entities::logical_name& logical_name,
    const dogen::physical::entities::meta_name& physical_meta_name,
    const dogen::physical::entities::name& name,
    const std::string& technical_space,
    const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts,
    const std::list<boost::filesystem::path>& managed_directories,
    const dogen::physical::entities::outputting_properties& outputting_properties)
    : configuration_(configuration),
      origin_sha1_hash_(origin_sha1_hash),
      logical_name_(logical_name),
      physical_meta_name_(physical_meta_name),
      name_(name),
      technical_space_(technical_space),
      artefacts_(artefacts),
      managed_directories_(managed_directories),
      outputting_properties_(outputting_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(configuration_, other.configuration_);
    swap(origin_sha1_hash_, other.origin_sha1_hash_);
    swap(logical_name_, other.logical_name_);
    swap(physical_meta_name_, other.physical_meta_name_);
    swap(name_, other.name_);
    swap(technical_space_, other.technical_space_);
    swap(artefacts_, other.artefacts_);
    swap(managed_directories_, other.managed_directories_);
    swap(outputting_properties_, other.outputting_properties_);
}

bool model::operator==(const model& rhs) const {
    return configuration_ == rhs.configuration_ &&
        origin_sha1_hash_ == rhs.origin_sha1_hash_ &&
        logical_name_ == rhs.logical_name_ &&
        physical_meta_name_ == rhs.physical_meta_name_ &&
        name_ == rhs.name_ &&
        technical_space_ == rhs.technical_space_ &&
        artefacts_ == rhs.artefacts_ &&
        managed_directories_ == rhs.managed_directories_ &&
        outputting_properties_ == rhs.outputting_properties_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
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

const std::string& model::origin_sha1_hash() const {
    return origin_sha1_hash_;
}

std::string& model::origin_sha1_hash() {
    return origin_sha1_hash_;
}

void model::origin_sha1_hash(const std::string& v) {
    origin_sha1_hash_ = v;
}

void model::origin_sha1_hash(const std::string&& v) {
    origin_sha1_hash_ = std::move(v);
}

const dogen::physical::entities::logical_name& model::logical_name() const {
    return logical_name_;
}

dogen::physical::entities::logical_name& model::logical_name() {
    return logical_name_;
}

void model::logical_name(const dogen::physical::entities::logical_name& v) {
    logical_name_ = v;
}

void model::logical_name(const dogen::physical::entities::logical_name&& v) {
    logical_name_ = std::move(v);
}

const dogen::physical::entities::meta_name& model::physical_meta_name() const {
    return physical_meta_name_;
}

dogen::physical::entities::meta_name& model::physical_meta_name() {
    return physical_meta_name_;
}

void model::physical_meta_name(const dogen::physical::entities::meta_name& v) {
    physical_meta_name_ = v;
}

void model::physical_meta_name(const dogen::physical::entities::meta_name&& v) {
    physical_meta_name_ = std::move(v);
}

const dogen::physical::entities::name& model::name() const {
    return name_;
}

dogen::physical::entities::name& model::name() {
    return name_;
}

void model::name(const dogen::physical::entities::name& v) {
    name_ = v;
}

void model::name(const dogen::physical::entities::name&& v) {
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

const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& model::artefacts() const {
    return artefacts_;
}

std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& model::artefacts() {
    return artefacts_;
}

void model::artefacts(const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& v) {
    artefacts_ = v;
}

void model::artefacts(const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >&& v) {
    artefacts_ = std::move(v);
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

}
