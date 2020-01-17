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
#include "dogen.extraction/types/meta_model/artefact.hpp"

namespace dogen::extraction::meta_model {

artefact::artefact()
    : overwrite_(static_cast<bool>(0)) { }

artefact::artefact(artefact&& rhs)
    : origin_sha1_hash_(std::move(rhs.origin_sha1_hash_)),
      origin_element_id_(std::move(rhs.origin_element_id_)),
      path_(std::move(rhs.path_)),
      content_(std::move(rhs.content_)),
      overwrite_(std::move(rhs.overwrite_)),
      dependencies_(std::move(rhs.dependencies_)),
      unified_diff_(std::move(rhs.unified_diff_)),
      operation_(std::move(rhs.operation_)) { }

artefact::artefact(
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const boost::filesystem::path& path,
    const std::string& content,
    const bool overwrite,
    const std::vector<boost::filesystem::path>& dependencies,
    const std::string& unified_diff,
    const dogen::extraction::meta_model::operation& operation)
    : origin_sha1_hash_(origin_sha1_hash),
      origin_element_id_(origin_element_id),
      path_(path),
      content_(content),
      overwrite_(overwrite),
      dependencies_(dependencies),
      unified_diff_(unified_diff),
      operation_(operation) { }

void artefact::swap(artefact& other) noexcept {
    using std::swap;
    swap(origin_sha1_hash_, other.origin_sha1_hash_);
    swap(origin_element_id_, other.origin_element_id_);
    swap(path_, other.path_);
    swap(content_, other.content_);
    swap(overwrite_, other.overwrite_);
    swap(dependencies_, other.dependencies_);
    swap(unified_diff_, other.unified_diff_);
    swap(operation_, other.operation_);
}

bool artefact::operator==(const artefact& rhs) const {
    return origin_sha1_hash_ == rhs.origin_sha1_hash_ &&
        origin_element_id_ == rhs.origin_element_id_ &&
        path_ == rhs.path_ &&
        content_ == rhs.content_ &&
        overwrite_ == rhs.overwrite_ &&
        dependencies_ == rhs.dependencies_ &&
        unified_diff_ == rhs.unified_diff_ &&
        operation_ == rhs.operation_;
}

artefact& artefact::operator=(artefact other) {
    using std::swap;
    swap(*this, other);
    return *this;
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

const std::string& artefact::origin_element_id() const {
    return origin_element_id_;
}

std::string& artefact::origin_element_id() {
    return origin_element_id_;
}

void artefact::origin_element_id(const std::string& v) {
    origin_element_id_ = v;
}

void artefact::origin_element_id(const std::string&& v) {
    origin_element_id_ = std::move(v);
}

const boost::filesystem::path& artefact::path() const {
    return path_;
}

boost::filesystem::path& artefact::path() {
    return path_;
}

void artefact::path(const boost::filesystem::path& v) {
    path_ = v;
}

void artefact::path(const boost::filesystem::path&& v) {
    path_ = std::move(v);
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

const dogen::extraction::meta_model::operation& artefact::operation() const {
    return operation_;
}

dogen::extraction::meta_model::operation& artefact::operation() {
    return operation_;
}

void artefact::operation(const dogen::extraction::meta_model::operation& v) {
    operation_ = v;
}

void artefact::operation(const dogen::extraction::meta_model::operation&& v) {
    operation_ = std::move(v);
}

}
