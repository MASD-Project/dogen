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
#include "dogen.injection/types/entities/model.hpp"
#include "dogen.variability/types/entities/configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::configuration>& lhs,
const boost::shared_ptr<dogen::variability::entities::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::injection::entities {

model::model(
    const std::list<dogen::identification::entities::tagged_value>& tagged_values,
    const std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides,
    const std::list<dogen::identification::entities::stereotype>& stereotypes,
    const std::string& documentation,
    const dogen::identification::entities::name& name,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const dogen::identification::entities::injection_provenance& provenance,
    const std::list<dogen::injection::entities::element>& elements,
    const std::string& input_technical_space,
    const std::list<std::string>& references,
    const std::unordered_set<std::string>& processed_variability_overrides)
    : tagged_values_(tagged_values),
      tagged_values_overrides_(tagged_values_overrides),
      stereotypes_(stereotypes),
      documentation_(documentation),
      name_(name),
      configuration_(configuration),
      provenance_(provenance),
      elements_(elements),
      input_technical_space_(input_technical_space),
      references_(references),
      processed_variability_overrides_(processed_variability_overrides) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(tagged_values_, other.tagged_values_);
    swap(tagged_values_overrides_, other.tagged_values_overrides_);
    swap(stereotypes_, other.stereotypes_);
    swap(documentation_, other.documentation_);
    swap(name_, other.name_);
    swap(configuration_, other.configuration_);
    swap(provenance_, other.provenance_);
    swap(elements_, other.elements_);
    swap(input_technical_space_, other.input_technical_space_);
    swap(references_, other.references_);
    swap(processed_variability_overrides_, other.processed_variability_overrides_);
}

bool model::operator==(const model& rhs) const {
    return tagged_values_ == rhs.tagged_values_ &&
        tagged_values_overrides_ == rhs.tagged_values_overrides_ &&
        stereotypes_ == rhs.stereotypes_ &&
        documentation_ == rhs.documentation_ &&
        name_ == rhs.name_ &&
        configuration_ == rhs.configuration_ &&
        provenance_ == rhs.provenance_ &&
        elements_ == rhs.elements_ &&
        input_technical_space_ == rhs.input_technical_space_ &&
        references_ == rhs.references_ &&
        processed_variability_overrides_ == rhs.processed_variability_overrides_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::identification::entities::tagged_value>& model::tagged_values() const {
    return tagged_values_;
}

std::list<dogen::identification::entities::tagged_value>& model::tagged_values() {
    return tagged_values_;
}

void model::tagged_values(const std::list<dogen::identification::entities::tagged_value>& v) {
    tagged_values_ = v;
}

void model::tagged_values(const std::list<dogen::identification::entities::tagged_value>&& v) {
    tagged_values_ = std::move(v);
}

const std::list<dogen::identification::entities::tagged_value>& model::tagged_values_overrides() const {
    return tagged_values_overrides_;
}

std::list<dogen::identification::entities::tagged_value>& model::tagged_values_overrides() {
    return tagged_values_overrides_;
}

void model::tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>& v) {
    tagged_values_overrides_ = v;
}

void model::tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>&& v) {
    tagged_values_overrides_ = std::move(v);
}

const std::list<dogen::identification::entities::stereotype>& model::stereotypes() const {
    return stereotypes_;
}

std::list<dogen::identification::entities::stereotype>& model::stereotypes() {
    return stereotypes_;
}

void model::stereotypes(const std::list<dogen::identification::entities::stereotype>& v) {
    stereotypes_ = v;
}

void model::stereotypes(const std::list<dogen::identification::entities::stereotype>&& v) {
    stereotypes_ = std::move(v);
}

const std::string& model::documentation() const {
    return documentation_;
}

std::string& model::documentation() {
    return documentation_;
}

void model::documentation(const std::string& v) {
    documentation_ = v;
}

void model::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const dogen::identification::entities::name& model::name() const {
    return name_;
}

dogen::identification::entities::name& model::name() {
    return name_;
}

void model::name(const dogen::identification::entities::name& v) {
    name_ = v;
}

void model::name(const dogen::identification::entities::name&& v) {
    name_ = std::move(v);
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

const dogen::identification::entities::injection_provenance& model::provenance() const {
    return provenance_;
}

dogen::identification::entities::injection_provenance& model::provenance() {
    return provenance_;
}

void model::provenance(const dogen::identification::entities::injection_provenance& v) {
    provenance_ = v;
}

void model::provenance(const dogen::identification::entities::injection_provenance&& v) {
    provenance_ = std::move(v);
}

const std::list<dogen::injection::entities::element>& model::elements() const {
    return elements_;
}

std::list<dogen::injection::entities::element>& model::elements() {
    return elements_;
}

void model::elements(const std::list<dogen::injection::entities::element>& v) {
    elements_ = v;
}

void model::elements(const std::list<dogen::injection::entities::element>&& v) {
    elements_ = std::move(v);
}

const std::string& model::input_technical_space() const {
    return input_technical_space_;
}

std::string& model::input_technical_space() {
    return input_technical_space_;
}

void model::input_technical_space(const std::string& v) {
    input_technical_space_ = v;
}

void model::input_technical_space(const std::string&& v) {
    input_technical_space_ = std::move(v);
}

const std::list<std::string>& model::references() const {
    return references_;
}

std::list<std::string>& model::references() {
    return references_;
}

void model::references(const std::list<std::string>& v) {
    references_ = v;
}

void model::references(const std::list<std::string>&& v) {
    references_ = std::move(v);
}

const std::unordered_set<std::string>& model::processed_variability_overrides() const {
    return processed_variability_overrides_;
}

std::unordered_set<std::string>& model::processed_variability_overrides() {
    return processed_variability_overrides_;
}

void model::processed_variability_overrides(const std::unordered_set<std::string>& v) {
    processed_variability_overrides_ = v;
}

void model::processed_variability_overrides(const std::unordered_set<std::string>&& v) {
    processed_variability_overrides_ = std::move(v);
}

}
