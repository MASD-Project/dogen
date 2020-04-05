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
      overwrite_(static_cast<bool>(0)),
      formatting_style_(static_cast<dogen::physical::entities::formatting_styles>(0)) { }

artefact::artefact(
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::string& origin_sha1_hash,
    const dogen::physical::entities::logical_name& logical_name,
    const dogen::physical::entities::meta_name& physical_meta_name,
    const dogen::physical::entities::name& name,
    const std::string& content,
    const bool enabled,
    const bool overwrite,
    const std::unordered_map<std::string, boost::filesystem::path>& relative_paths,
    const std::vector<boost::filesystem::path>& dependencies,
    const std::string& unified_diff,
    const dogen::physical::entities::operation& operation,
    const dogen::physical::entities::enablement_flags& enablement_flags,
    const dogen::physical::entities::formatting_styles formatting_style,
    const std::string& formatting_input)
    : configuration_(configuration),
      origin_sha1_hash_(origin_sha1_hash),
      logical_name_(logical_name),
      physical_meta_name_(physical_meta_name),
      name_(name),
      content_(content),
      enabled_(enabled),
      overwrite_(overwrite),
      relative_paths_(relative_paths),
      dependencies_(dependencies),
      unified_diff_(unified_diff),
      operation_(operation),
      enablement_flags_(enablement_flags),
      formatting_style_(formatting_style),
      formatting_input_(formatting_input) { }

void artefact::swap(artefact& other) noexcept {
    using std::swap;
    swap(configuration_, other.configuration_);
    swap(origin_sha1_hash_, other.origin_sha1_hash_);
    swap(logical_name_, other.logical_name_);
    swap(physical_meta_name_, other.physical_meta_name_);
    swap(name_, other.name_);
    swap(content_, other.content_);
    swap(enabled_, other.enabled_);
    swap(overwrite_, other.overwrite_);
    swap(relative_paths_, other.relative_paths_);
    swap(dependencies_, other.dependencies_);
    swap(unified_diff_, other.unified_diff_);
    swap(operation_, other.operation_);
    swap(enablement_flags_, other.enablement_flags_);
    swap(formatting_style_, other.formatting_style_);
    swap(formatting_input_, other.formatting_input_);
}

bool artefact::operator==(const artefact& rhs) const {
    return configuration_ == rhs.configuration_ &&
        origin_sha1_hash_ == rhs.origin_sha1_hash_ &&
        logical_name_ == rhs.logical_name_ &&
        physical_meta_name_ == rhs.physical_meta_name_ &&
        name_ == rhs.name_ &&
        content_ == rhs.content_ &&
        enabled_ == rhs.enabled_ &&
        overwrite_ == rhs.overwrite_ &&
        relative_paths_ == rhs.relative_paths_ &&
        dependencies_ == rhs.dependencies_ &&
        unified_diff_ == rhs.unified_diff_ &&
        operation_ == rhs.operation_ &&
        enablement_flags_ == rhs.enablement_flags_ &&
        formatting_style_ == rhs.formatting_style_ &&
        formatting_input_ == rhs.formatting_input_;
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

const dogen::physical::entities::logical_name& artefact::logical_name() const {
    return logical_name_;
}

dogen::physical::entities::logical_name& artefact::logical_name() {
    return logical_name_;
}

void artefact::logical_name(const dogen::physical::entities::logical_name& v) {
    logical_name_ = v;
}

void artefact::logical_name(const dogen::physical::entities::logical_name&& v) {
    logical_name_ = std::move(v);
}

const dogen::physical::entities::meta_name& artefact::physical_meta_name() const {
    return physical_meta_name_;
}

dogen::physical::entities::meta_name& artefact::physical_meta_name() {
    return physical_meta_name_;
}

void artefact::physical_meta_name(const dogen::physical::entities::meta_name& v) {
    physical_meta_name_ = v;
}

void artefact::physical_meta_name(const dogen::physical::entities::meta_name&& v) {
    physical_meta_name_ = std::move(v);
}

const dogen::physical::entities::name& artefact::name() const {
    return name_;
}

dogen::physical::entities::name& artefact::name() {
    return name_;
}

void artefact::name(const dogen::physical::entities::name& v) {
    name_ = v;
}

void artefact::name(const dogen::physical::entities::name&& v) {
    name_ = std::move(v);
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

const std::unordered_map<std::string, boost::filesystem::path>& artefact::relative_paths() const {
    return relative_paths_;
}

std::unordered_map<std::string, boost::filesystem::path>& artefact::relative_paths() {
    return relative_paths_;
}

void artefact::relative_paths(const std::unordered_map<std::string, boost::filesystem::path>& v) {
    relative_paths_ = v;
}

void artefact::relative_paths(const std::unordered_map<std::string, boost::filesystem::path>&& v) {
    relative_paths_ = std::move(v);
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

dogen::physical::entities::formatting_styles artefact::formatting_style() const {
    return formatting_style_;
}

void artefact::formatting_style(const dogen::physical::entities::formatting_styles v) {
    formatting_style_ = v;
}

const std::string& artefact::formatting_input() const {
    return formatting_input_;
}

std::string& artefact::formatting_input() {
    return formatting_input_;
}

void artefact::formatting_input(const std::string& v) {
    formatting_input_ = v;
}

void artefact::formatting_input(const std::string&& v) {
    formatting_input_ = std::move(v);
}

}
