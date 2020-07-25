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
#include "dogen.physical/types/entities/facet.hpp"

namespace dogen::physical::entities {

facet::facet(
    const std::string& default_directory_name,
    const std::string& override_directory_name,
    const std::string& description,
    const dogen::physical::entities::meta_name& meta_name,
    const std::list<dogen::identification::entities::label>& labels,
    const std::string& default_postfix,
    const std::string& override_postfix,
    const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes,
    const std::unordered_map<std::string, dogen::physical::entities::archetype>& default_archetype_for_logical_meta_model_id)
    : default_directory_name_(default_directory_name),
      override_directory_name_(override_directory_name),
      description_(description),
      meta_name_(meta_name),
      labels_(labels),
      default_postfix_(default_postfix),
      override_postfix_(override_postfix),
      archetypes_(archetypes),
      default_archetype_for_logical_meta_model_id_(default_archetype_for_logical_meta_model_id) { }

void facet::swap(facet& other) noexcept {
    using std::swap;
    swap(default_directory_name_, other.default_directory_name_);
    swap(override_directory_name_, other.override_directory_name_);
    swap(description_, other.description_);
    swap(meta_name_, other.meta_name_);
    swap(labels_, other.labels_);
    swap(default_postfix_, other.default_postfix_);
    swap(override_postfix_, other.override_postfix_);
    swap(archetypes_, other.archetypes_);
    swap(default_archetype_for_logical_meta_model_id_, other.default_archetype_for_logical_meta_model_id_);
}

bool facet::operator==(const facet& rhs) const {
    return default_directory_name_ == rhs.default_directory_name_ &&
        override_directory_name_ == rhs.override_directory_name_ &&
        description_ == rhs.description_ &&
        meta_name_ == rhs.meta_name_ &&
        labels_ == rhs.labels_ &&
        default_postfix_ == rhs.default_postfix_ &&
        override_postfix_ == rhs.override_postfix_ &&
        archetypes_ == rhs.archetypes_ &&
        default_archetype_for_logical_meta_model_id_ == rhs.default_archetype_for_logical_meta_model_id_;
}

facet& facet::operator=(facet other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& facet::default_directory_name() const {
    return default_directory_name_;
}

std::string& facet::default_directory_name() {
    return default_directory_name_;
}

void facet::default_directory_name(const std::string& v) {
    default_directory_name_ = v;
}

void facet::default_directory_name(const std::string&& v) {
    default_directory_name_ = std::move(v);
}

const std::string& facet::override_directory_name() const {
    return override_directory_name_;
}

std::string& facet::override_directory_name() {
    return override_directory_name_;
}

void facet::override_directory_name(const std::string& v) {
    override_directory_name_ = v;
}

void facet::override_directory_name(const std::string&& v) {
    override_directory_name_ = std::move(v);
}

const std::string& facet::description() const {
    return description_;
}

std::string& facet::description() {
    return description_;
}

void facet::description(const std::string& v) {
    description_ = v;
}

void facet::description(const std::string&& v) {
    description_ = std::move(v);
}

const dogen::physical::entities::meta_name& facet::meta_name() const {
    return meta_name_;
}

dogen::physical::entities::meta_name& facet::meta_name() {
    return meta_name_;
}

void facet::meta_name(const dogen::physical::entities::meta_name& v) {
    meta_name_ = v;
}

void facet::meta_name(const dogen::physical::entities::meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::list<dogen::identification::entities::label>& facet::labels() const {
    return labels_;
}

std::list<dogen::identification::entities::label>& facet::labels() {
    return labels_;
}

void facet::labels(const std::list<dogen::identification::entities::label>& v) {
    labels_ = v;
}

void facet::labels(const std::list<dogen::identification::entities::label>&& v) {
    labels_ = std::move(v);
}

const std::string& facet::default_postfix() const {
    return default_postfix_;
}

std::string& facet::default_postfix() {
    return default_postfix_;
}

void facet::default_postfix(const std::string& v) {
    default_postfix_ = v;
}

void facet::default_postfix(const std::string&& v) {
    default_postfix_ = std::move(v);
}

const std::string& facet::override_postfix() const {
    return override_postfix_;
}

std::string& facet::override_postfix() {
    return override_postfix_;
}

void facet::override_postfix(const std::string& v) {
    override_postfix_ = v;
}

void facet::override_postfix(const std::string&& v) {
    override_postfix_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::archetype>& facet::archetypes() const {
    return archetypes_;
}

std::unordered_map<std::string, dogen::physical::entities::archetype>& facet::archetypes() {
    return archetypes_;
}

void facet::archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v) {
    archetypes_ = v;
}

void facet::archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v) {
    archetypes_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::archetype>& facet::default_archetype_for_logical_meta_model_id() const {
    return default_archetype_for_logical_meta_model_id_;
}

std::unordered_map<std::string, dogen::physical::entities::archetype>& facet::default_archetype_for_logical_meta_model_id() {
    return default_archetype_for_logical_meta_model_id_;
}

void facet::default_archetype_for_logical_meta_model_id(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v) {
    default_archetype_for_logical_meta_model_id_ = v;
}

void facet::default_archetype_for_logical_meta_model_id(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v) {
    default_archetype_for_logical_meta_model_id_ = std::move(v);
}

}
