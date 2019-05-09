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
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/structural/module.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace masd::dogen::coding::meta_model {

model::model()
    : origin_type_(static_cast<masd::dogen::coding::meta_model::origin_types>(0)),
      input_technical_space_(static_cast<masd::dogen::coding::meta_model::technical_space>(0)) { }

model::model(model&& rhs)
    : name_(std::move(rhs.name_)),
      meta_name_(std::move(rhs.meta_name_)),
      origin_type_(std::move(rhs.origin_type_)),
      references_(std::move(rhs.references_)),
      leaves_(std::move(rhs.leaves_)),
      root_module_(std::move(rhs.root_module_)),
      input_technical_space_(std::move(rhs.input_technical_space_)),
      output_technical_spaces_(std::move(rhs.output_technical_spaces_)),
      orm_properties_(std::move(rhs.orm_properties_)),
      extraction_properties_(std::move(rhs.extraction_properties_)),
      structural_elements_(std::move(rhs.structural_elements_)),
      decoration_elements_(std::move(rhs.decoration_elements_)),
      variability_elements_(std::move(rhs.variability_elements_)) { }

model::model(
    const masd::dogen::coding::meta_model::name& name,
    const masd::dogen::coding::meta_model::name& meta_name,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references,
    const std::unordered_set<masd::dogen::coding::meta_model::name>& leaves,
    const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& root_module,
    const masd::dogen::coding::meta_model::technical_space input_technical_space,
    const std::list<masd::dogen::coding::meta_model::technical_space>& output_technical_spaces,
    const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& orm_properties,
    const masd::dogen::coding::meta_model::extraction_properties& extraction_properties,
    const masd::dogen::coding::meta_model::structural::element_repository& structural_elements,
    const masd::dogen::coding::meta_model::decoration::element_repository& decoration_elements,
    const masd::dogen::coding::meta_model::variability::element_repository& variability_elements)
    : name_(name),
      meta_name_(meta_name),
      origin_type_(origin_type),
      references_(references),
      leaves_(leaves),
      root_module_(root_module),
      input_technical_space_(input_technical_space),
      output_technical_spaces_(output_technical_spaces),
      orm_properties_(orm_properties),
      extraction_properties_(extraction_properties),
      structural_elements_(structural_elements),
      decoration_elements_(decoration_elements),
      variability_elements_(variability_elements) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(meta_name_, other.meta_name_);
    swap(origin_type_, other.origin_type_);
    swap(references_, other.references_);
    swap(leaves_, other.leaves_);
    swap(root_module_, other.root_module_);
    swap(input_technical_space_, other.input_technical_space_);
    swap(output_technical_spaces_, other.output_technical_spaces_);
    swap(orm_properties_, other.orm_properties_);
    swap(extraction_properties_, other.extraction_properties_);
    swap(structural_elements_, other.structural_elements_);
    swap(decoration_elements_, other.decoration_elements_);
    swap(variability_elements_, other.variability_elements_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        meta_name_ == rhs.meta_name_ &&
        origin_type_ == rhs.origin_type_ &&
        references_ == rhs.references_ &&
        leaves_ == rhs.leaves_ &&
        root_module_ == rhs.root_module_ &&
        input_technical_space_ == rhs.input_technical_space_ &&
        output_technical_spaces_ == rhs.output_technical_spaces_ &&
        orm_properties_ == rhs.orm_properties_ &&
        extraction_properties_ == rhs.extraction_properties_ &&
        structural_elements_ == rhs.structural_elements_ &&
        decoration_elements_ == rhs.decoration_elements_ &&
        variability_elements_ == rhs.variability_elements_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::coding::meta_model::name& model::name() const {
    return name_;
}

masd::dogen::coding::meta_model::name& model::name() {
    return name_;
}

void model::name(const masd::dogen::coding::meta_model::name& v) {
    name_ = v;
}

void model::name(const masd::dogen::coding::meta_model::name&& v) {
    name_ = std::move(v);
}

const masd::dogen::coding::meta_model::name& model::meta_name() const {
    return meta_name_;
}

masd::dogen::coding::meta_model::name& model::meta_name() {
    return meta_name_;
}

void model::meta_name(const masd::dogen::coding::meta_model::name& v) {
    meta_name_ = v;
}

void model::meta_name(const masd::dogen::coding::meta_model::name&& v) {
    meta_name_ = std::move(v);
}

masd::dogen::coding::meta_model::origin_types model::origin_type() const {
    return origin_type_;
}

void model::origin_type(const masd::dogen::coding::meta_model::origin_types v) {
    origin_type_ = v;
}

const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& model::references() const {
    return references_;
}

std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& model::references() {
    return references_;
}

void model::references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& v) {
    references_ = v;
}

void model::references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>&& v) {
    references_ = std::move(v);
}

const std::unordered_set<masd::dogen::coding::meta_model::name>& model::leaves() const {
    return leaves_;
}

std::unordered_set<masd::dogen::coding::meta_model::name>& model::leaves() {
    return leaves_;
}

void model::leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>& v) {
    leaves_ = v;
}

void model::leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>&& v) {
    leaves_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& model::root_module() const {
    return root_module_;
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& model::root_module() {
    return root_module_;
}

void model::root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& v) {
    root_module_ = v;
}

void model::root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>&& v) {
    root_module_ = std::move(v);
}

masd::dogen::coding::meta_model::technical_space model::input_technical_space() const {
    return input_technical_space_;
}

void model::input_technical_space(const masd::dogen::coding::meta_model::technical_space v) {
    input_technical_space_ = v;
}

const std::list<masd::dogen::coding::meta_model::technical_space>& model::output_technical_spaces() const {
    return output_technical_spaces_;
}

std::list<masd::dogen::coding::meta_model::technical_space>& model::output_technical_spaces() {
    return output_technical_spaces_;
}

void model::output_technical_spaces(const std::list<masd::dogen::coding::meta_model::technical_space>& v) {
    output_technical_spaces_ = v;
}

void model::output_technical_spaces(const std::list<masd::dogen::coding::meta_model::technical_space>&& v) {
    output_technical_spaces_ = std::move(v);
}

const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& model::orm_properties() const {
    return orm_properties_;
}

boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& model::orm_properties() {
    return orm_properties_;
}

void model::orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& v) {
    orm_properties_ = v;
}

void model::orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>&& v) {
    orm_properties_ = std::move(v);
}

const masd::dogen::coding::meta_model::extraction_properties& model::extraction_properties() const {
    return extraction_properties_;
}

masd::dogen::coding::meta_model::extraction_properties& model::extraction_properties() {
    return extraction_properties_;
}

void model::extraction_properties(const masd::dogen::coding::meta_model::extraction_properties& v) {
    extraction_properties_ = v;
}

void model::extraction_properties(const masd::dogen::coding::meta_model::extraction_properties&& v) {
    extraction_properties_ = std::move(v);
}

const masd::dogen::coding::meta_model::structural::element_repository& model::structural_elements() const {
    return structural_elements_;
}

masd::dogen::coding::meta_model::structural::element_repository& model::structural_elements() {
    return structural_elements_;
}

void model::structural_elements(const masd::dogen::coding::meta_model::structural::element_repository& v) {
    structural_elements_ = v;
}

void model::structural_elements(const masd::dogen::coding::meta_model::structural::element_repository&& v) {
    structural_elements_ = std::move(v);
}

const masd::dogen::coding::meta_model::decoration::element_repository& model::decoration_elements() const {
    return decoration_elements_;
}

masd::dogen::coding::meta_model::decoration::element_repository& model::decoration_elements() {
    return decoration_elements_;
}

void model::decoration_elements(const masd::dogen::coding::meta_model::decoration::element_repository& v) {
    decoration_elements_ = v;
}

void model::decoration_elements(const masd::dogen::coding::meta_model::decoration::element_repository&& v) {
    decoration_elements_ = std::move(v);
}

const masd::dogen::coding::meta_model::variability::element_repository& model::variability_elements() const {
    return variability_elements_;
}

masd::dogen::coding::meta_model::variability::element_repository& model::variability_elements() {
    return variability_elements_;
}

void model::variability_elements(const masd::dogen::coding::meta_model::variability::element_repository& v) {
    variability_elements_ = v;
}

void model::variability_elements(const masd::dogen::coding::meta_model::variability::element_repository&& v) {
    variability_elements_ = std::move(v);
}

}
