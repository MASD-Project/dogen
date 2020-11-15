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
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::module>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::module>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::entities {

model::model()
    : input_technical_space_(static_cast<dogen::identification::entities::technical_space>(0)),
      technical_space_version_(static_cast<dogen::identification::entities::technical_space_version>(0)) { }

model::model(model&& rhs)
    : name_(std::move(rhs.name_)),
      meta_name_(std::move(rhs.meta_name_)),
      provenance_(std::move(rhs.provenance_)),
      references_(std::move(rhs.references_)),
      leaves_(std::move(rhs.leaves_)),
      root_module_(std::move(rhs.root_module_)),
      input_technical_space_(std::move(rhs.input_technical_space_)),
      output_technical_spaces_(std::move(rhs.output_technical_spaces_)),
      all_technical_spaces_(std::move(rhs.all_technical_spaces_)),
      orm_properties_(std::move(rhs.orm_properties_)),
      structural_elements_(std::move(rhs.structural_elements_)),
      decoration_elements_(std::move(rhs.decoration_elements_)),
      variability_elements_(std::move(rhs.variability_elements_)),
      mapping_elements_(std::move(rhs.mapping_elements_)),
      templating_elements_(std::move(rhs.templating_elements_)),
      serialization_elements_(std::move(rhs.serialization_elements_)),
      visual_studio_elements_(std::move(rhs.visual_studio_elements_)),
      orm_elements_(std::move(rhs.orm_elements_)),
      build_elements_(std::move(rhs.build_elements_)),
      physical_elements_(std::move(rhs.physical_elements_)),
      meta_names_(std::move(rhs.meta_names_)),
      streaming_properties_(std::move(rhs.streaming_properties_)),
      technical_space_version_(std::move(rhs.technical_space_version_)),
      aspect_properties_(std::move(rhs.aspect_properties_)),
      assistant_properties_(std::move(rhs.assistant_properties_)) { }

model::model(
    const dogen::identification::entities::logical_name& name,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::codec_provenance& provenance,
    const std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>& references,
    const std::unordered_set<dogen::identification::entities::logical_name>& leaves,
    const boost::shared_ptr<dogen::logical::entities::structural::module>& root_module,
    const dogen::identification::entities::technical_space input_technical_space,
    const std::list<dogen::identification::entities::technical_space>& output_technical_spaces,
    const std::unordered_set<dogen::identification::entities::technical_space>& all_technical_spaces,
    const boost::optional<dogen::logical::entities::orm::model_properties>& orm_properties,
    const dogen::logical::entities::structural::element_repository& structural_elements,
    const dogen::logical::entities::decoration::element_repository& decoration_elements,
    const dogen::logical::entities::variability::element_repository& variability_elements,
    const dogen::logical::entities::mapping::element_repository& mapping_elements,
    const dogen::logical::entities::templating::element_repository& templating_elements,
    const dogen::logical::entities::serialization::element_repository& serialization_elements,
    const dogen::logical::entities::visual_studio::element_repository& visual_studio_elements,
    const dogen::logical::entities::orm::element_repository& orm_elements,
    const dogen::logical::entities::build::element_repository& build_elements,
    const dogen::logical::entities::physical::element_repository& physical_elements,
    const std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>& meta_names,
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>& streaming_properties,
    const dogen::identification::entities::technical_space_version technical_space_version,
    const std::unordered_map<std::string, dogen::logical::entities::aspect_properties>& aspect_properties,
    const std::unordered_map<std::string, dogen::logical::entities::assistant_properties>& assistant_properties)
    : name_(name),
      meta_name_(meta_name),
      provenance_(provenance),
      references_(references),
      leaves_(leaves),
      root_module_(root_module),
      input_technical_space_(input_technical_space),
      output_technical_spaces_(output_technical_spaces),
      all_technical_spaces_(all_technical_spaces),
      orm_properties_(orm_properties),
      structural_elements_(structural_elements),
      decoration_elements_(decoration_elements),
      variability_elements_(variability_elements),
      mapping_elements_(mapping_elements),
      templating_elements_(templating_elements),
      serialization_elements_(serialization_elements),
      visual_studio_elements_(visual_studio_elements),
      orm_elements_(orm_elements),
      build_elements_(build_elements),
      physical_elements_(physical_elements),
      meta_names_(meta_names),
      streaming_properties_(streaming_properties),
      technical_space_version_(technical_space_version),
      aspect_properties_(aspect_properties),
      assistant_properties_(assistant_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(meta_name_, other.meta_name_);
    swap(provenance_, other.provenance_);
    swap(references_, other.references_);
    swap(leaves_, other.leaves_);
    swap(root_module_, other.root_module_);
    swap(input_technical_space_, other.input_technical_space_);
    swap(output_technical_spaces_, other.output_technical_spaces_);
    swap(all_technical_spaces_, other.all_technical_spaces_);
    swap(orm_properties_, other.orm_properties_);
    swap(structural_elements_, other.structural_elements_);
    swap(decoration_elements_, other.decoration_elements_);
    swap(variability_elements_, other.variability_elements_);
    swap(mapping_elements_, other.mapping_elements_);
    swap(templating_elements_, other.templating_elements_);
    swap(serialization_elements_, other.serialization_elements_);
    swap(visual_studio_elements_, other.visual_studio_elements_);
    swap(orm_elements_, other.orm_elements_);
    swap(build_elements_, other.build_elements_);
    swap(physical_elements_, other.physical_elements_);
    swap(meta_names_, other.meta_names_);
    swap(streaming_properties_, other.streaming_properties_);
    swap(technical_space_version_, other.technical_space_version_);
    swap(aspect_properties_, other.aspect_properties_);
    swap(assistant_properties_, other.assistant_properties_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        meta_name_ == rhs.meta_name_ &&
        provenance_ == rhs.provenance_ &&
        references_ == rhs.references_ &&
        leaves_ == rhs.leaves_ &&
        root_module_ == rhs.root_module_ &&
        input_technical_space_ == rhs.input_technical_space_ &&
        output_technical_spaces_ == rhs.output_technical_spaces_ &&
        all_technical_spaces_ == rhs.all_technical_spaces_ &&
        orm_properties_ == rhs.orm_properties_ &&
        structural_elements_ == rhs.structural_elements_ &&
        decoration_elements_ == rhs.decoration_elements_ &&
        variability_elements_ == rhs.variability_elements_ &&
        mapping_elements_ == rhs.mapping_elements_ &&
        templating_elements_ == rhs.templating_elements_ &&
        serialization_elements_ == rhs.serialization_elements_ &&
        visual_studio_elements_ == rhs.visual_studio_elements_ &&
        orm_elements_ == rhs.orm_elements_ &&
        build_elements_ == rhs.build_elements_ &&
        physical_elements_ == rhs.physical_elements_ &&
        meta_names_ == rhs.meta_names_ &&
        streaming_properties_ == rhs.streaming_properties_ &&
        technical_space_version_ == rhs.technical_space_version_ &&
        aspect_properties_ == rhs.aspect_properties_ &&
        assistant_properties_ == rhs.assistant_properties_;
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

const dogen::identification::entities::codec_provenance& model::provenance() const {
    return provenance_;
}

dogen::identification::entities::codec_provenance& model::provenance() {
    return provenance_;
}

void model::provenance(const dogen::identification::entities::codec_provenance& v) {
    provenance_ = v;
}

void model::provenance(const dogen::identification::entities::codec_provenance&& v) {
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

dogen::identification::entities::technical_space model::input_technical_space() const {
    return input_technical_space_;
}

void model::input_technical_space(const dogen::identification::entities::technical_space v) {
    input_technical_space_ = v;
}

const std::list<dogen::identification::entities::technical_space>& model::output_technical_spaces() const {
    return output_technical_spaces_;
}

std::list<dogen::identification::entities::technical_space>& model::output_technical_spaces() {
    return output_technical_spaces_;
}

void model::output_technical_spaces(const std::list<dogen::identification::entities::technical_space>& v) {
    output_technical_spaces_ = v;
}

void model::output_technical_spaces(const std::list<dogen::identification::entities::technical_space>&& v) {
    output_technical_spaces_ = std::move(v);
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

const dogen::logical::entities::structural::element_repository& model::structural_elements() const {
    return structural_elements_;
}

dogen::logical::entities::structural::element_repository& model::structural_elements() {
    return structural_elements_;
}

void model::structural_elements(const dogen::logical::entities::structural::element_repository& v) {
    structural_elements_ = v;
}

void model::structural_elements(const dogen::logical::entities::structural::element_repository&& v) {
    structural_elements_ = std::move(v);
}

const dogen::logical::entities::decoration::element_repository& model::decoration_elements() const {
    return decoration_elements_;
}

dogen::logical::entities::decoration::element_repository& model::decoration_elements() {
    return decoration_elements_;
}

void model::decoration_elements(const dogen::logical::entities::decoration::element_repository& v) {
    decoration_elements_ = v;
}

void model::decoration_elements(const dogen::logical::entities::decoration::element_repository&& v) {
    decoration_elements_ = std::move(v);
}

const dogen::logical::entities::variability::element_repository& model::variability_elements() const {
    return variability_elements_;
}

dogen::logical::entities::variability::element_repository& model::variability_elements() {
    return variability_elements_;
}

void model::variability_elements(const dogen::logical::entities::variability::element_repository& v) {
    variability_elements_ = v;
}

void model::variability_elements(const dogen::logical::entities::variability::element_repository&& v) {
    variability_elements_ = std::move(v);
}

const dogen::logical::entities::mapping::element_repository& model::mapping_elements() const {
    return mapping_elements_;
}

dogen::logical::entities::mapping::element_repository& model::mapping_elements() {
    return mapping_elements_;
}

void model::mapping_elements(const dogen::logical::entities::mapping::element_repository& v) {
    mapping_elements_ = v;
}

void model::mapping_elements(const dogen::logical::entities::mapping::element_repository&& v) {
    mapping_elements_ = std::move(v);
}

const dogen::logical::entities::templating::element_repository& model::templating_elements() const {
    return templating_elements_;
}

dogen::logical::entities::templating::element_repository& model::templating_elements() {
    return templating_elements_;
}

void model::templating_elements(const dogen::logical::entities::templating::element_repository& v) {
    templating_elements_ = v;
}

void model::templating_elements(const dogen::logical::entities::templating::element_repository&& v) {
    templating_elements_ = std::move(v);
}

const dogen::logical::entities::serialization::element_repository& model::serialization_elements() const {
    return serialization_elements_;
}

dogen::logical::entities::serialization::element_repository& model::serialization_elements() {
    return serialization_elements_;
}

void model::serialization_elements(const dogen::logical::entities::serialization::element_repository& v) {
    serialization_elements_ = v;
}

void model::serialization_elements(const dogen::logical::entities::serialization::element_repository&& v) {
    serialization_elements_ = std::move(v);
}

const dogen::logical::entities::visual_studio::element_repository& model::visual_studio_elements() const {
    return visual_studio_elements_;
}

dogen::logical::entities::visual_studio::element_repository& model::visual_studio_elements() {
    return visual_studio_elements_;
}

void model::visual_studio_elements(const dogen::logical::entities::visual_studio::element_repository& v) {
    visual_studio_elements_ = v;
}

void model::visual_studio_elements(const dogen::logical::entities::visual_studio::element_repository&& v) {
    visual_studio_elements_ = std::move(v);
}

const dogen::logical::entities::orm::element_repository& model::orm_elements() const {
    return orm_elements_;
}

dogen::logical::entities::orm::element_repository& model::orm_elements() {
    return orm_elements_;
}

void model::orm_elements(const dogen::logical::entities::orm::element_repository& v) {
    orm_elements_ = v;
}

void model::orm_elements(const dogen::logical::entities::orm::element_repository&& v) {
    orm_elements_ = std::move(v);
}

const dogen::logical::entities::build::element_repository& model::build_elements() const {
    return build_elements_;
}

dogen::logical::entities::build::element_repository& model::build_elements() {
    return build_elements_;
}

void model::build_elements(const dogen::logical::entities::build::element_repository& v) {
    build_elements_ = v;
}

void model::build_elements(const dogen::logical::entities::build::element_repository&& v) {
    build_elements_ = std::move(v);
}

const dogen::logical::entities::physical::element_repository& model::physical_elements() const {
    return physical_elements_;
}

dogen::logical::entities::physical::element_repository& model::physical_elements() {
    return physical_elements_;
}

void model::physical_elements(const dogen::logical::entities::physical::element_repository& v) {
    physical_elements_ = v;
}

void model::physical_elements(const dogen::logical::entities::physical::element_repository&& v) {
    physical_elements_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>& model::meta_names() const {
    return meta_names_;
}

std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>& model::meta_names() {
    return meta_names_;
}

void model::meta_names(const std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>& v) {
    meta_names_ = v;
}

void model::meta_names(const std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>&& v) {
    meta_names_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>& model::streaming_properties() const {
    return streaming_properties_;
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>& model::streaming_properties() {
    return streaming_properties_;
}

void model::streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>& v) {
    streaming_properties_ = v;
}

void model::streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>&& v) {
    streaming_properties_ = std::move(v);
}

dogen::identification::entities::technical_space_version model::technical_space_version() const {
    return technical_space_version_;
}

void model::technical_space_version(const dogen::identification::entities::technical_space_version v) {
    technical_space_version_ = v;
}

const std::unordered_map<std::string, dogen::logical::entities::aspect_properties>& model::aspect_properties() const {
    return aspect_properties_;
}

std::unordered_map<std::string, dogen::logical::entities::aspect_properties>& model::aspect_properties() {
    return aspect_properties_;
}

void model::aspect_properties(const std::unordered_map<std::string, dogen::logical::entities::aspect_properties>& v) {
    aspect_properties_ = v;
}

void model::aspect_properties(const std::unordered_map<std::string, dogen::logical::entities::aspect_properties>&& v) {
    aspect_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::logical::entities::assistant_properties>& model::assistant_properties() const {
    return assistant_properties_;
}

std::unordered_map<std::string, dogen::logical::entities::assistant_properties>& model::assistant_properties() {
    return assistant_properties_;
}

void model::assistant_properties(const std::unordered_map<std::string, dogen::logical::entities::assistant_properties>& v) {
    assistant_properties_ = v;
}

void model::assistant_properties(const std::unordered_map<std::string, dogen::logical::entities::assistant_properties>&& v) {
    assistant_properties_ = std::move(v);
}

}
