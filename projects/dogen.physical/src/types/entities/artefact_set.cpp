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
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/artefact_set.hpp"
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

artefact_set::artefact_set(
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::string& logical_meta_element_id,
    const std::string& logical_element_id,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts_by_archetype,
    const std::unordered_map<std::string, std::string>& archetype_for_role)
    : configuration_(configuration),
      logical_meta_element_id_(logical_meta_element_id),
      logical_element_id_(logical_element_id),
      artefacts_by_archetype_(artefacts_by_archetype),
      archetype_for_role_(archetype_for_role) { }

void artefact_set::swap(artefact_set& other) noexcept {
    using std::swap;
    swap(configuration_, other.configuration_);
    swap(logical_meta_element_id_, other.logical_meta_element_id_);
    swap(logical_element_id_, other.logical_element_id_);
    swap(artefacts_by_archetype_, other.artefacts_by_archetype_);
    swap(archetype_for_role_, other.archetype_for_role_);
}

bool artefact_set::operator==(const artefact_set& rhs) const {
    return configuration_ == rhs.configuration_ &&
        logical_meta_element_id_ == rhs.logical_meta_element_id_ &&
        logical_element_id_ == rhs.logical_element_id_ &&
        artefacts_by_archetype_ == rhs.artefacts_by_archetype_ &&
        archetype_for_role_ == rhs.archetype_for_role_;
}

artefact_set& artefact_set::operator=(artefact_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::variability::entities::configuration>& artefact_set::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::entities::configuration>& artefact_set::configuration() {
    return configuration_;
}

void artefact_set::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    configuration_ = v;
}

void artefact_set::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v) {
    configuration_ = std::move(v);
}

const std::string& artefact_set::logical_meta_element_id() const {
    return logical_meta_element_id_;
}

std::string& artefact_set::logical_meta_element_id() {
    return logical_meta_element_id_;
}

void artefact_set::logical_meta_element_id(const std::string& v) {
    logical_meta_element_id_ = v;
}

void artefact_set::logical_meta_element_id(const std::string&& v) {
    logical_meta_element_id_ = std::move(v);
}

const std::string& artefact_set::logical_element_id() const {
    return logical_element_id_;
}

std::string& artefact_set::logical_element_id() {
    return logical_element_id_;
}

void artefact_set::logical_element_id(const std::string& v) {
    logical_element_id_ = v;
}

void artefact_set::logical_element_id(const std::string&& v) {
    logical_element_id_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& artefact_set::artefacts_by_archetype() const {
    return artefacts_by_archetype_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& artefact_set::artefacts_by_archetype() {
    return artefacts_by_archetype_;
}

void artefact_set::artefacts_by_archetype(const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& v) {
    artefacts_by_archetype_ = v;
}

void artefact_set::artefacts_by_archetype(const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >&& v) {
    artefacts_by_archetype_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& artefact_set::archetype_for_role() const {
    return archetype_for_role_;
}

std::unordered_map<std::string, std::string>& artefact_set::archetype_for_role() {
    return archetype_for_role_;
}

void artefact_set::archetype_for_role(const std::unordered_map<std::string, std::string>& v) {
    archetype_for_role_ = v;
}

void artefact_set::archetype_for_role(const std::unordered_map<std::string, std::string>&& v) {
    archetype_for_role_ = std::move(v);
}

}
