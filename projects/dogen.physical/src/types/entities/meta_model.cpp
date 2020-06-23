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
#include "dogen.physical/types/entities/meta_model.hpp"

namespace dogen::physical::entities {

meta_model::meta_model(
    const std::string& default_directory_name,
    const std::string& override_directory_name,
    const std::string& description,
    const dogen::physical::entities::meta_name& meta_name,
    const std::list<dogen::physical::entities::label>& labels,
    const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& enablement_flags,
    const std::unordered_map<std::string, std::vector<std::string> >& template_instantiation_domains,
    const std::list<dogen::physical::entities::backend>& backends,
    const dogen::physical::entities::meta_name_indices& indexed_names)
    : default_directory_name_(default_directory_name),
      override_directory_name_(override_directory_name),
      description_(description),
      meta_name_(meta_name),
      labels_(labels),
      enablement_flags_(enablement_flags),
      template_instantiation_domains_(template_instantiation_domains),
      backends_(backends),
      indexed_names_(indexed_names) { }

void meta_model::swap(meta_model& other) noexcept {
    using std::swap;
    swap(default_directory_name_, other.default_directory_name_);
    swap(override_directory_name_, other.override_directory_name_);
    swap(description_, other.description_);
    swap(meta_name_, other.meta_name_);
    swap(labels_, other.labels_);
    swap(enablement_flags_, other.enablement_flags_);
    swap(template_instantiation_domains_, other.template_instantiation_domains_);
    swap(backends_, other.backends_);
    swap(indexed_names_, other.indexed_names_);
}

bool meta_model::operator==(const meta_model& rhs) const {
    return default_directory_name_ == rhs.default_directory_name_ &&
        override_directory_name_ == rhs.override_directory_name_ &&
        description_ == rhs.description_ &&
        meta_name_ == rhs.meta_name_ &&
        labels_ == rhs.labels_ &&
        enablement_flags_ == rhs.enablement_flags_ &&
        template_instantiation_domains_ == rhs.template_instantiation_domains_ &&
        backends_ == rhs.backends_ &&
        indexed_names_ == rhs.indexed_names_;
}

meta_model& meta_model::operator=(meta_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& meta_model::default_directory_name() const {
    return default_directory_name_;
}

std::string& meta_model::default_directory_name() {
    return default_directory_name_;
}

void meta_model::default_directory_name(const std::string& v) {
    default_directory_name_ = v;
}

void meta_model::default_directory_name(const std::string&& v) {
    default_directory_name_ = std::move(v);
}

const std::string& meta_model::override_directory_name() const {
    return override_directory_name_;
}

std::string& meta_model::override_directory_name() {
    return override_directory_name_;
}

void meta_model::override_directory_name(const std::string& v) {
    override_directory_name_ = v;
}

void meta_model::override_directory_name(const std::string&& v) {
    override_directory_name_ = std::move(v);
}

const std::string& meta_model::description() const {
    return description_;
}

std::string& meta_model::description() {
    return description_;
}

void meta_model::description(const std::string& v) {
    description_ = v;
}

void meta_model::description(const std::string&& v) {
    description_ = std::move(v);
}

const dogen::physical::entities::meta_name& meta_model::meta_name() const {
    return meta_name_;
}

dogen::physical::entities::meta_name& meta_model::meta_name() {
    return meta_name_;
}

void meta_model::meta_name(const dogen::physical::entities::meta_name& v) {
    meta_name_ = v;
}

void meta_model::meta_name(const dogen::physical::entities::meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::list<dogen::physical::entities::label>& meta_model::labels() const {
    return labels_;
}

std::list<dogen::physical::entities::label>& meta_model::labels() {
    return labels_;
}

void meta_model::labels(const std::list<dogen::physical::entities::label>& v) {
    labels_ = v;
}

void meta_model::labels(const std::list<dogen::physical::entities::label>&& v) {
    labels_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& meta_model::enablement_flags() const {
    return enablement_flags_;
}

std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& meta_model::enablement_flags() {
    return enablement_flags_;
}

void meta_model::enablement_flags(const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& v) {
    enablement_flags_ = v;
}

void meta_model::enablement_flags(const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>&& v) {
    enablement_flags_ = std::move(v);
}

const std::unordered_map<std::string, std::vector<std::string> >& meta_model::template_instantiation_domains() const {
    return template_instantiation_domains_;
}

std::unordered_map<std::string, std::vector<std::string> >& meta_model::template_instantiation_domains() {
    return template_instantiation_domains_;
}

void meta_model::template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >& v) {
    template_instantiation_domains_ = v;
}

void meta_model::template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >&& v) {
    template_instantiation_domains_ = std::move(v);
}

const std::list<dogen::physical::entities::backend>& meta_model::backends() const {
    return backends_;
}

std::list<dogen::physical::entities::backend>& meta_model::backends() {
    return backends_;
}

void meta_model::backends(const std::list<dogen::physical::entities::backend>& v) {
    backends_ = v;
}

void meta_model::backends(const std::list<dogen::physical::entities::backend>&& v) {
    backends_ = std::move(v);
}

const dogen::physical::entities::meta_name_indices& meta_model::indexed_names() const {
    return indexed_names_;
}

dogen::physical::entities::meta_name_indices& meta_model::indexed_names() {
    return indexed_names_;
}

void meta_model::indexed_names(const dogen::physical::entities::meta_name_indices& v) {
    indexed_names_ = v;
}

void meta_model::indexed_names(const dogen::physical::entities::meta_name_indices&& v) {
    indexed_names_ = std::move(v);
}

}
