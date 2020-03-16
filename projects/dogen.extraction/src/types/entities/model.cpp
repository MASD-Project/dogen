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
#include "dogen.extraction/types/entities/model.hpp"
#include "dogen.variability/types/entities/configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::configuration>& lhs,
const boost::shared_ptr<dogen::variability::entities::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::extraction::entities {

model::model(
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& name,
    const std::string& technical_space,
    const std::list<dogen::extraction::entities::artefact>& artefacts,
    const std::list<boost::filesystem::path>& managed_directories,
    const dogen::extraction::entities::outputting_properties& outputting_properties)
    : configuration_(configuration),
      origin_sha1_hash_(origin_sha1_hash),
      origin_element_id_(origin_element_id),
      name_(name),
      technical_space_(technical_space),
      artefacts_(artefacts),
      managed_directories_(managed_directories),
      outputting_properties_(outputting_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(configuration_, other.configuration_);
    swap(origin_sha1_hash_, other.origin_sha1_hash_);
    swap(origin_element_id_, other.origin_element_id_);
    swap(name_, other.name_);
    swap(technical_space_, other.technical_space_);
    swap(artefacts_, other.artefacts_);
    swap(managed_directories_, other.managed_directories_);
    swap(outputting_properties_, other.outputting_properties_);
}

bool model::operator==(const model& rhs) const {
    return configuration_ == rhs.configuration_ &&
        origin_sha1_hash_ == rhs.origin_sha1_hash_ &&
        origin_element_id_ == rhs.origin_element_id_ &&
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

const std::string& model::origin_element_id() const {
    return origin_element_id_;
}

std::string& model::origin_element_id() {
    return origin_element_id_;
}

void model::origin_element_id(const std::string& v) {
    origin_element_id_ = v;
}

void model::origin_element_id(const std::string&& v) {
    origin_element_id_ = std::move(v);
}

const std::string& model::name() const {
    return name_;
}

std::string& model::name() {
    return name_;
}

void model::name(const std::string& v) {
    name_ = v;
}

void model::name(const std::string&& v) {
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

const std::list<dogen::extraction::entities::artefact>& model::artefacts() const {
    return artefacts_;
}

std::list<dogen::extraction::entities::artefact>& model::artefacts() {
    return artefacts_;
}

void model::artefacts(const std::list<dogen::extraction::entities::artefact>& v) {
    artefacts_ = v;
}

void model::artefacts(const std::list<dogen::extraction::entities::artefact>&& v) {
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

const dogen::extraction::entities::outputting_properties& model::outputting_properties() const {
    return outputting_properties_;
}

dogen::extraction::entities::outputting_properties& model::outputting_properties() {
    return outputting_properties_;
}

void model::outputting_properties(const dogen::extraction::entities::outputting_properties& v) {
    outputting_properties_ = v;
}

void model::outputting_properties(const dogen::extraction::entities::outputting_properties&& v) {
    outputting_properties_ = std::move(v);
}

}
