/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

model::model()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)),
      origin_type_(static_cast<dogen::sml::origin_types>(0)),
      is_target_(static_cast<bool>(0)),
      has_generatable_types_(static_cast<bool>(0)) { }

model::model(model&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      extensions_(std::move(rhs.extensions_)),
      name_(std::move(rhs.name_)),
      generation_type_(std::move(rhs.generation_type_)),
      origin_type_(std::move(rhs.origin_type_)),
      containing_module_(std::move(rhs.containing_module_)),
      references_(std::move(rhs.references_)),
      leaves_(std::move(rhs.leaves_)),
      modules_(std::move(rhs.modules_)),
      concepts_(std::move(rhs.concepts_)),
      primitives_(std::move(rhs.primitives_)),
      enumerations_(std::move(rhs.enumerations_)),
      objects_(std::move(rhs.objects_)),
      is_target_(std::move(rhs.is_target_)),
      has_generatable_types_(std::move(rhs.has_generatable_types_)) { }

model::model(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const dogen::sml::origin_types& origin_type,
    const boost::optional<dogen::sml::qname>& containing_module,
    const std::unordered_map<dogen::sml::qname, dogen::sml::origin_types>& references,
    const std::unordered_set<dogen::sml::qname>& leaves,
    const std::unordered_map<dogen::sml::qname, dogen::sml::module>& modules,
    const std::unordered_map<dogen::sml::qname, dogen::sml::concept>& concepts,
    const std::unordered_map<dogen::sml::qname, dogen::sml::primitive>& primitives,
    const std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>& enumerations,
    const std::unordered_map<dogen::sml::qname, dogen::sml::object>& objects,
    const bool is_target,
    const bool has_generatable_types)
    : documentation_(documentation),
      extensions_(extensions),
      name_(name),
      generation_type_(generation_type),
      origin_type_(origin_type),
      containing_module_(containing_module),
      references_(references),
      leaves_(leaves),
      modules_(modules),
      concepts_(concepts),
      primitives_(primitives),
      enumerations_(enumerations),
      objects_(objects),
      is_target_(is_target),
      has_generatable_types_(has_generatable_types) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(extensions_, other.extensions_);
    swap(name_, other.name_);
    swap(generation_type_, other.generation_type_);
    swap(origin_type_, other.origin_type_);
    swap(containing_module_, other.containing_module_);
    swap(references_, other.references_);
    swap(leaves_, other.leaves_);
    swap(modules_, other.modules_);
    swap(concepts_, other.concepts_);
    swap(primitives_, other.primitives_);
    swap(enumerations_, other.enumerations_);
    swap(objects_, other.objects_);
    swap(is_target_, other.is_target_);
    swap(has_generatable_types_, other.has_generatable_types_);
}

bool model::operator==(const model& rhs) const {
    return documentation_ == rhs.documentation_ &&
        extensions_ == rhs.extensions_ &&
        name_ == rhs.name_ &&
        generation_type_ == rhs.generation_type_ &&
        origin_type_ == rhs.origin_type_ &&
        containing_module_ == rhs.containing_module_ &&
        references_ == rhs.references_ &&
        leaves_ == rhs.leaves_ &&
        modules_ == rhs.modules_ &&
        concepts_ == rhs.concepts_ &&
        primitives_ == rhs.primitives_ &&
        enumerations_ == rhs.enumerations_ &&
        objects_ == rhs.objects_ &&
        is_target_ == rhs.is_target_ &&
        has_generatable_types_ == rhs.has_generatable_types_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
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

const dogen::dynamic::object& model::extensions() const {
    return extensions_;
}

dogen::dynamic::object& model::extensions() {
    return extensions_;
}

void model::extensions(const dogen::dynamic::object& v) {
    extensions_ = v;
}

void model::extensions(const dogen::dynamic::object&& v) {
    extensions_ = std::move(v);
}

const dogen::sml::qname& model::name() const {
    return name_;
}

dogen::sml::qname& model::name() {
    return name_;
}

void model::name(const dogen::sml::qname& v) {
    name_ = v;
}

void model::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

dogen::sml::generation_types model::generation_type() const {
    return generation_type_;
}

void model::generation_type(const dogen::sml::generation_types& v) {
    generation_type_ = v;
}

dogen::sml::origin_types model::origin_type() const {
    return origin_type_;
}

void model::origin_type(const dogen::sml::origin_types& v) {
    origin_type_ = v;
}

const boost::optional<dogen::sml::qname>& model::containing_module() const {
    return containing_module_;
}

boost::optional<dogen::sml::qname>& model::containing_module() {
    return containing_module_;
}

void model::containing_module(const boost::optional<dogen::sml::qname>& v) {
    containing_module_ = v;
}

void model::containing_module(const boost::optional<dogen::sml::qname>&& v) {
    containing_module_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::origin_types>& model::references() const {
    return references_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::origin_types>& model::references() {
    return references_;
}

void model::references(const std::unordered_map<dogen::sml::qname, dogen::sml::origin_types>& v) {
    references_ = v;
}

void model::references(const std::unordered_map<dogen::sml::qname, dogen::sml::origin_types>&& v) {
    references_ = std::move(v);
}

const std::unordered_set<dogen::sml::qname>& model::leaves() const {
    return leaves_;
}

std::unordered_set<dogen::sml::qname>& model::leaves() {
    return leaves_;
}

void model::leaves(const std::unordered_set<dogen::sml::qname>& v) {
    leaves_ = v;
}

void model::leaves(const std::unordered_set<dogen::sml::qname>&& v) {
    leaves_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::module>& model::modules() const {
    return modules_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::module>& model::modules() {
    return modules_;
}

void model::modules(const std::unordered_map<dogen::sml::qname, dogen::sml::module>& v) {
    modules_ = v;
}

void model::modules(const std::unordered_map<dogen::sml::qname, dogen::sml::module>&& v) {
    modules_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::concept>& model::concepts() const {
    return concepts_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::concept>& model::concepts() {
    return concepts_;
}

void model::concepts(const std::unordered_map<dogen::sml::qname, dogen::sml::concept>& v) {
    concepts_ = v;
}

void model::concepts(const std::unordered_map<dogen::sml::qname, dogen::sml::concept>&& v) {
    concepts_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::primitive>& model::primitives() const {
    return primitives_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::primitive>& model::primitives() {
    return primitives_;
}

void model::primitives(const std::unordered_map<dogen::sml::qname, dogen::sml::primitive>& v) {
    primitives_ = v;
}

void model::primitives(const std::unordered_map<dogen::sml::qname, dogen::sml::primitive>&& v) {
    primitives_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>& model::enumerations() const {
    return enumerations_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>& model::enumerations() {
    return enumerations_;
}

void model::enumerations(const std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>& v) {
    enumerations_ = v;
}

void model::enumerations(const std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>&& v) {
    enumerations_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::object>& model::objects() const {
    return objects_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::object>& model::objects() {
    return objects_;
}

void model::objects(const std::unordered_map<dogen::sml::qname, dogen::sml::object>& v) {
    objects_ = v;
}

void model::objects(const std::unordered_map<dogen::sml::qname, dogen::sml::object>&& v) {
    objects_ = std::move(v);
}

bool model::is_target() const {
    return is_target_;
}

void model::is_target(const bool v) {
    is_target_ = v;
}

bool model::has_generatable_types() const {
    return has_generatable_types_;
}

void model::has_generatable_types(const bool v) {
    has_generatable_types_ = v;
}

} }
