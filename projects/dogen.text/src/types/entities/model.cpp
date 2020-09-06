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
#include "dogen.text/types/entities/model.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::module>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::module>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::text::entities {

model::model()
    : has_generatable_types_(static_cast<bool>(0)),
      input_technical_space_(static_cast<dogen::identification::entities::technical_space>(0)),
      output_technical_space_(static_cast<dogen::identification::entities::technical_space>(0)) { }

model::model(model&& rhs)
    : name_(std::move(rhs.name_)),
      meta_name_(std::move(rhs.meta_name_)),
      provenance_(std::move(rhs.provenance_)),
      references_(std::move(rhs.references_)),
      leaves_(std::move(rhs.leaves_)),
      elements_(std::move(rhs.elements_)),
      root_module_(std::move(rhs.root_module_)),
      has_generatable_types_(std::move(rhs.has_generatable_types_)),
      input_technical_space_(std::move(rhs.input_technical_space_)),
      output_technical_space_(std::move(rhs.output_technical_space_)),
      all_technical_spaces_(std::move(rhs.all_technical_spaces_)),
      orm_properties_(std::move(rhs.orm_properties_)),
      enabled_archetype_for_element_(std::move(rhs.enabled_archetype_for_element_)),
      extraction_properties_(std::move(rhs.extraction_properties_)),
      managed_directories_(std::move(rhs.managed_directories_)),
      facet_properties_(std::move(rhs.facet_properties_)) { }

model::model(
    const dogen::identification::entities::logical_name& name,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::injection_provenance& provenance,
    const std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>& references,
    const std::unordered_set<dogen::identification::entities::logical_name>& leaves,
    const std::list<dogen::text::entities::element_artefacts>& elements,
    const boost::shared_ptr<dogen::logical::entities::structural::module>& root_module,
    const bool has_generatable_types,
    const dogen::identification::entities::technical_space input_technical_space,
    const dogen::identification::entities::technical_space output_technical_space,
    const std::unordered_set<dogen::identification::entities::technical_space>& all_technical_spaces,
    const boost::optional<dogen::logical::entities::orm::model_properties>& orm_properties,
    const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& enabled_archetype_for_element,
    const dogen::physical::entities::extraction_properties& extraction_properties,
    const std::list<boost::filesystem::path>& managed_directories,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& facet_properties)
    : name_(name),
      meta_name_(meta_name),
      provenance_(provenance),
      references_(references),
      leaves_(leaves),
      elements_(elements),
      root_module_(root_module),
      has_generatable_types_(has_generatable_types),
      input_technical_space_(input_technical_space),
      output_technical_space_(output_technical_space),
      all_technical_spaces_(all_technical_spaces),
      orm_properties_(orm_properties),
      enabled_archetype_for_element_(enabled_archetype_for_element),
      extraction_properties_(extraction_properties),
      managed_directories_(managed_directories),
      facet_properties_(facet_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(meta_name_, other.meta_name_);
    swap(provenance_, other.provenance_);
    swap(references_, other.references_);
    swap(leaves_, other.leaves_);
    swap(elements_, other.elements_);
    swap(root_module_, other.root_module_);
    swap(has_generatable_types_, other.has_generatable_types_);
    swap(input_technical_space_, other.input_technical_space_);
    swap(output_technical_space_, other.output_technical_space_);
    swap(all_technical_spaces_, other.all_technical_spaces_);
    swap(orm_properties_, other.orm_properties_);
    swap(enabled_archetype_for_element_, other.enabled_archetype_for_element_);
    swap(extraction_properties_, other.extraction_properties_);
    swap(managed_directories_, other.managed_directories_);
    swap(facet_properties_, other.facet_properties_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        meta_name_ == rhs.meta_name_ &&
        provenance_ == rhs.provenance_ &&
        references_ == rhs.references_ &&
        leaves_ == rhs.leaves_ &&
        elements_ == rhs.elements_ &&
        root_module_ == rhs.root_module_ &&
        has_generatable_types_ == rhs.has_generatable_types_ &&
        input_technical_space_ == rhs.input_technical_space_ &&
        output_technical_space_ == rhs.output_technical_space_ &&
        all_technical_spaces_ == rhs.all_technical_spaces_ &&
        orm_properties_ == rhs.orm_properties_ &&
        enabled_archetype_for_element_ == rhs.enabled_archetype_for_element_ &&
        extraction_properties_ == rhs.extraction_properties_ &&
        managed_directories_ == rhs.managed_directories_ &&
        facet_properties_ == rhs.facet_properties_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::logical_name& model::name() const {
    return name_;
}

dogen::identification::entities::logical_name& model::name() {
    return name_;
}

void model::name(const dogen::identification::entities::logical_name& v) {
    name_ = v;
}

void model::name(const dogen::identification::entities::logical_name&& v) {
    name_ = std::move(v);
}

const dogen::identification::entities::logical_meta_name& model::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::logical_meta_name& model::meta_name() {
    return meta_name_;
}

void model::meta_name(const dogen::identification::entities::logical_meta_name& v) {
    meta_name_ = v;
}

void model::meta_name(const dogen::identification::entities::logical_meta_name&& v) {
    meta_name_ = std::move(v);
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

const std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>& model::references() const {
    return references_;
}

std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>& model::references() {
    return references_;
}

void model::references(const std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>& v) {
    references_ = v;
}

void model::references(const std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>&& v) {
    references_ = std::move(v);
}

const std::unordered_set<dogen::identification::entities::logical_name>& model::leaves() const {
    return leaves_;
}

std::unordered_set<dogen::identification::entities::logical_name>& model::leaves() {
    return leaves_;
}

void model::leaves(const std::unordered_set<dogen::identification::entities::logical_name>& v) {
    leaves_ = v;
}

void model::leaves(const std::unordered_set<dogen::identification::entities::logical_name>&& v) {
    leaves_ = std::move(v);
}

const std::list<dogen::text::entities::element_artefacts>& model::elements() const {
    return elements_;
}

std::list<dogen::text::entities::element_artefacts>& model::elements() {
    return elements_;
}

void model::elements(const std::list<dogen::text::entities::element_artefacts>& v) {
    elements_ = v;
}

void model::elements(const std::list<dogen::text::entities::element_artefacts>&& v) {
    elements_ = std::move(v);
}

const boost::shared_ptr<dogen::logical::entities::structural::module>& model::root_module() const {
    return root_module_;
}

boost::shared_ptr<dogen::logical::entities::structural::module>& model::root_module() {
    return root_module_;
}

void model::root_module(const boost::shared_ptr<dogen::logical::entities::structural::module>& v) {
    root_module_ = v;
}

void model::root_module(const boost::shared_ptr<dogen::logical::entities::structural::module>&& v) {
    root_module_ = std::move(v);
}

bool model::has_generatable_types() const {
    return has_generatable_types_;
}

void model::has_generatable_types(const bool v) {
    has_generatable_types_ = v;
}

dogen::identification::entities::technical_space model::input_technical_space() const {
    return input_technical_space_;
}

void model::input_technical_space(const dogen::identification::entities::technical_space v) {
    input_technical_space_ = v;
}

dogen::identification::entities::technical_space model::output_technical_space() const {
    return output_technical_space_;
}

void model::output_technical_space(const dogen::identification::entities::technical_space v) {
    output_technical_space_ = v;
}

const std::unordered_set<dogen::identification::entities::technical_space>& model::all_technical_spaces() const {
    return all_technical_spaces_;
}

std::unordered_set<dogen::identification::entities::technical_space>& model::all_technical_spaces() {
    return all_technical_spaces_;
}

void model::all_technical_spaces(const std::unordered_set<dogen::identification::entities::technical_space>& v) {
    all_technical_spaces_ = v;
}

void model::all_technical_spaces(const std::unordered_set<dogen::identification::entities::technical_space>&& v) {
    all_technical_spaces_ = std::move(v);
}

const boost::optional<dogen::logical::entities::orm::model_properties>& model::orm_properties() const {
    return orm_properties_;
}

boost::optional<dogen::logical::entities::orm::model_properties>& model::orm_properties() {
    return orm_properties_;
}

void model::orm_properties(const boost::optional<dogen::logical::entities::orm::model_properties>& v) {
    orm_properties_ = v;
}

void model::orm_properties(const boost::optional<dogen::logical::entities::orm::model_properties>&& v) {
    orm_properties_ = std::move(v);
}

const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& model::enabled_archetype_for_element() const {
    return enabled_archetype_for_element_;
}

std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& model::enabled_archetype_for_element() {
    return enabled_archetype_for_element_;
}

void model::enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& v) {
    enabled_archetype_for_element_ = v;
}

void model::enabled_archetype_for_element(const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>&& v) {
    enabled_archetype_for_element_ = std::move(v);
}

const dogen::physical::entities::extraction_properties& model::extraction_properties() const {
    return extraction_properties_;
}

dogen::physical::entities::extraction_properties& model::extraction_properties() {
    return extraction_properties_;
}

void model::extraction_properties(const dogen::physical::entities::extraction_properties& v) {
    extraction_properties_ = v;
}

void model::extraction_properties(const dogen::physical::entities::extraction_properties&& v) {
    extraction_properties_ = std::move(v);
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

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& model::facet_properties() const {
    return facet_properties_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& model::facet_properties() {
    return facet_properties_;
}

void model::facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>& v) {
    facet_properties_ = v;
}

void model::facet_properties(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet_properties>&& v) {
    facet_properties_ = std::move(v);
}

}
