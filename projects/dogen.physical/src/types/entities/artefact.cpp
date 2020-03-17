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
#include "dogen.variability/types/entities/configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::configuration>& lhs,
const boost::shared_ptr<dogen::variability::entities::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::physical::entities {

artefact::artefact()
    : enabled_(static_cast<bool>(0)),
      overwrite_(static_cast<bool>(0)) { }

artefact::artefact(
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::string& origin_sha1_hash,
    const dogen::physical::entities::logical_location& logical_location,
    const std::unordered_map<std::string, dogen::physical::entities::paths>& paths,
    const std::string& content,
    const bool enabled,
    const bool overwrite,
    const std::vector<boost::filesystem::path>& dependencies,
    const std::string& unified_diff,
    const dogen::physical::entities::operation& operation,
    const dogen::physical::entities::enablement_flags& enablement_flags)
    : configuration_(configuration),
      origin_sha1_hash_(origin_sha1_hash),
      logical_location_(logical_location),
      paths_(paths),
      content_(content),
      enabled_(enabled),
      overwrite_(overwrite),
      dependencies_(dependencies),
      unified_diff_(unified_diff),
      operation_(operation),
      enablement_flags_(enablement_flags) { }

void artefact::swap(artefact& other) noexcept {
    using std::swap;
    swap(configuration_, other.configuration_);
    swap(origin_sha1_hash_, other.origin_sha1_hash_);
    swap(logical_location_, other.logical_location_);
    swap(paths_, other.paths_);
    swap(content_, other.content_);
    swap(enabled_, other.enabled_);
    swap(overwrite_, other.overwrite_);
    swap(dependencies_, other.dependencies_);
    swap(unified_diff_, other.unified_diff_);
    swap(operation_, other.operation_);
    swap(enablement_flags_, other.enablement_flags_);
}

bool artefact::operator==(const artefact& rhs) const {
    return configuration_ == rhs.configuration_ &&
        origin_sha1_hash_ == rhs.origin_sha1_hash_ &&
        logical_location_ == rhs.logical_location_ &&
        paths_ == rhs.paths_ &&
        content_ == rhs.content_ &&
        enabled_ == rhs.enabled_ &&
        overwrite_ == rhs.overwrite_ &&
        dependencies_ == rhs.dependencies_ &&
        unified_diff_ == rhs.unified_diff_ &&
        operation_ == rhs.operation_ &&
        enablement_flags_ == rhs.enablement_flags_;
}

artefact& artefact::operator=(artefact other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::variability::entities::configuration>& artefact::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::entities::configuration>& artefact::configuration() {
    return configuration_;
}

void artefact::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    configuration_ = v;
}

void artefact::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v) {
    configuration_ = std::move(v);
}

const std::string& artefact::origin_sha1_hash() const {
    return origin_sha1_hash_;
}

std::string& artefact::origin_sha1_hash() {
    return origin_sha1_hash_;
}

void artefact::origin_sha1_hash(const std::string& v) {
    origin_sha1_hash_ = v;
}

void artefact::origin_sha1_hash(const std::string&& v) {
    origin_sha1_hash_ = std::move(v);
}

const dogen::physical::entities::logical_location& artefact::logical_location() const {
    return logical_location_;
}

dogen::physical::entities::logical_location& artefact::logical_location() {
    return logical_location_;
}

void artefact::logical_location(const dogen::physical::entities::logical_location& v) {
    logical_location_ = v;
}

void artefact::logical_location(const dogen::physical::entities::logical_location&& v) {
    logical_location_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::paths>& artefact::paths() const {
    return paths_;
}

std::unordered_map<std::string, dogen::physical::entities::paths>& artefact::paths() {
    return paths_;
}

void artefact::paths(const std::unordered_map<std::string, dogen::physical::entities::paths>& v) {
    paths_ = v;
}

void artefact::paths(const std::unordered_map<std::string, dogen::physical::entities::paths>&& v) {
    paths_ = std::move(v);
}

const std::string& artefact::content() const {
    return content_;
}

std::string& artefact::content() {
    return content_;
}

void artefact::content(const std::string& v) {
    content_ = v;
}

void artefact::content(const std::string&& v) {
    content_ = std::move(v);
}

bool artefact::enabled() const {
    return enabled_;
}

void artefact::enabled(const bool v) {
    enabled_ = v;
}

bool artefact::overwrite() const {
    return overwrite_;
}

void artefact::overwrite(const bool v) {
    overwrite_ = v;
}

const std::vector<boost::filesystem::path>& artefact::dependencies() const {
    return dependencies_;
}

std::vector<boost::filesystem::path>& artefact::dependencies() {
    return dependencies_;
}

void artefact::dependencies(const std::vector<boost::filesystem::path>& v) {
    dependencies_ = v;
}

void artefact::dependencies(const std::vector<boost::filesystem::path>&& v) {
    dependencies_ = std::move(v);
}

const std::string& artefact::unified_diff() const {
    return unified_diff_;
}

std::string& artefact::unified_diff() {
    return unified_diff_;
}

void artefact::unified_diff(const std::string& v) {
    unified_diff_ = v;
}

void artefact::unified_diff(const std::string&& v) {
    unified_diff_ = std::move(v);
}

const dogen::physical::entities::operation& artefact::operation() const {
    return operation_;
}

dogen::physical::entities::operation& artefact::operation() {
    return operation_;
}

void artefact::operation(const dogen::physical::entities::operation& v) {
    operation_ = v;
}

void artefact::operation(const dogen::physical::entities::operation&& v) {
    operation_ = std::move(v);
}

const dogen::physical::entities::enablement_flags& artefact::enablement_flags() const {
    return enablement_flags_;
}

dogen::physical::entities::enablement_flags& artefact::enablement_flags() {
    return enablement_flags_;
}

void artefact::enablement_flags(const dogen::physical::entities::enablement_flags& v) {
    enablement_flags_ = v;
}

void artefact::enablement_flags(const dogen::physical::entities::enablement_flags&& v) {
    enablement_flags_ = std::move(v);
}

}
