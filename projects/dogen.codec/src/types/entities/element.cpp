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
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.variability/types/entities/configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::configuration>& lhs,
const boost::shared_ptr<dogen::variability::entities::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::codec::entities {

element::element()
    : can_be_primitive_underlier_(static_cast<bool>(0)),
      in_global_module_(static_cast<bool>(0)),
      can_be_enumeration_underlier_(static_cast<bool>(0)),
      is_default_enumeration_type_(static_cast<bool>(0)),
      is_associative_container_(static_cast<bool>(0)),
      is_floating_point_(static_cast<bool>(0)) { }

element::element(
    const std::list<dogen::identification::entities::tagged_value>& tagged_values,
    const std::list<dogen::identification::entities::stereotype>& stereotypes,
    const std::list<dogen::identification::entities::stereotype>& templates,
    const std::list<dogen::identification::entities::stereotype>& configurations,
    const dogen::identification::entities::name& name,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const dogen::identification::entities::codec_provenance& provenance,
    const std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides,
    const dogen::codec::entities::comment& comment,
    const std::list<std::string>& parents,
    const std::list<dogen::codec::entities::attribute>& attributes,
    const std::string& fallback_element_type,
    const bool can_be_primitive_underlier,
    const bool in_global_module,
    const bool can_be_enumeration_underlier,
    const bool is_default_enumeration_type,
    const bool is_associative_container,
    const bool is_floating_point,
    const dogen::identification::entities::codec_id& containing_element_id,
    const std::list<std::string>& plantuml)
    : tagged_values_(tagged_values),
      stereotypes_(stereotypes),
      templates_(templates),
      configurations_(configurations),
      name_(name),
      configuration_(configuration),
      provenance_(provenance),
      tagged_values_overrides_(tagged_values_overrides),
      comment_(comment),
      parents_(parents),
      attributes_(attributes),
      fallback_element_type_(fallback_element_type),
      can_be_primitive_underlier_(can_be_primitive_underlier),
      in_global_module_(in_global_module),
      can_be_enumeration_underlier_(can_be_enumeration_underlier),
      is_default_enumeration_type_(is_default_enumeration_type),
      is_associative_container_(is_associative_container),
      is_floating_point_(is_floating_point),
      containing_element_id_(containing_element_id),
      plantuml_(plantuml) { }

void element::swap(element& other) noexcept {
    using std::swap;
    swap(tagged_values_, other.tagged_values_);
    swap(stereotypes_, other.stereotypes_);
    swap(templates_, other.templates_);
    swap(configurations_, other.configurations_);
    swap(name_, other.name_);
    swap(configuration_, other.configuration_);
    swap(provenance_, other.provenance_);
    swap(tagged_values_overrides_, other.tagged_values_overrides_);
    swap(comment_, other.comment_);
    swap(parents_, other.parents_);
    swap(attributes_, other.attributes_);
    swap(fallback_element_type_, other.fallback_element_type_);
    swap(can_be_primitive_underlier_, other.can_be_primitive_underlier_);
    swap(in_global_module_, other.in_global_module_);
    swap(can_be_enumeration_underlier_, other.can_be_enumeration_underlier_);
    swap(is_default_enumeration_type_, other.is_default_enumeration_type_);
    swap(is_associative_container_, other.is_associative_container_);
    swap(is_floating_point_, other.is_floating_point_);
    swap(containing_element_id_, other.containing_element_id_);
    swap(plantuml_, other.plantuml_);
}

bool element::operator==(const element& rhs) const {
    return tagged_values_ == rhs.tagged_values_ &&
        stereotypes_ == rhs.stereotypes_ &&
        templates_ == rhs.templates_ &&
        configurations_ == rhs.configurations_ &&
        name_ == rhs.name_ &&
        configuration_ == rhs.configuration_ &&
        provenance_ == rhs.provenance_ &&
        tagged_values_overrides_ == rhs.tagged_values_overrides_ &&
        comment_ == rhs.comment_ &&
        parents_ == rhs.parents_ &&
        attributes_ == rhs.attributes_ &&
        fallback_element_type_ == rhs.fallback_element_type_ &&
        can_be_primitive_underlier_ == rhs.can_be_primitive_underlier_ &&
        in_global_module_ == rhs.in_global_module_ &&
        can_be_enumeration_underlier_ == rhs.can_be_enumeration_underlier_ &&
        is_default_enumeration_type_ == rhs.is_default_enumeration_type_ &&
        is_associative_container_ == rhs.is_associative_container_ &&
        is_floating_point_ == rhs.is_floating_point_ &&
        containing_element_id_ == rhs.containing_element_id_ &&
        plantuml_ == rhs.plantuml_;
}

element& element::operator=(element other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::identification::entities::tagged_value>& element::tagged_values() const {
    return tagged_values_;
}

std::list<dogen::identification::entities::tagged_value>& element::tagged_values() {
    return tagged_values_;
}

void element::tagged_values(const std::list<dogen::identification::entities::tagged_value>& v) {
    tagged_values_ = v;
}

void element::tagged_values(const std::list<dogen::identification::entities::tagged_value>&& v) {
    tagged_values_ = std::move(v);
}

const std::list<dogen::identification::entities::stereotype>& element::stereotypes() const {
    return stereotypes_;
}

std::list<dogen::identification::entities::stereotype>& element::stereotypes() {
    return stereotypes_;
}

void element::stereotypes(const std::list<dogen::identification::entities::stereotype>& v) {
    stereotypes_ = v;
}

void element::stereotypes(const std::list<dogen::identification::entities::stereotype>&& v) {
    stereotypes_ = std::move(v);
}

const std::list<dogen::identification::entities::stereotype>& element::templates() const {
    return templates_;
}

std::list<dogen::identification::entities::stereotype>& element::templates() {
    return templates_;
}

void element::templates(const std::list<dogen::identification::entities::stereotype>& v) {
    templates_ = v;
}

void element::templates(const std::list<dogen::identification::entities::stereotype>&& v) {
    templates_ = std::move(v);
}

const std::list<dogen::identification::entities::stereotype>& element::configurations() const {
    return configurations_;
}

std::list<dogen::identification::entities::stereotype>& element::configurations() {
    return configurations_;
}

void element::configurations(const std::list<dogen::identification::entities::stereotype>& v) {
    configurations_ = v;
}

void element::configurations(const std::list<dogen::identification::entities::stereotype>&& v) {
    configurations_ = std::move(v);
}

const dogen::identification::entities::name& element::name() const {
    return name_;
}

dogen::identification::entities::name& element::name() {
    return name_;
}

void element::name(const dogen::identification::entities::name& v) {
    name_ = v;
}

void element::name(const dogen::identification::entities::name&& v) {
    name_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::entities::configuration>& element::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::entities::configuration>& element::configuration() {
    return configuration_;
}

void element::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    configuration_ = v;
}

void element::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::identification::entities::codec_provenance& element::provenance() const {
    return provenance_;
}

dogen::identification::entities::codec_provenance& element::provenance() {
    return provenance_;
}

void element::provenance(const dogen::identification::entities::codec_provenance& v) {
    provenance_ = v;
}

void element::provenance(const dogen::identification::entities::codec_provenance&& v) {
    provenance_ = std::move(v);
}

const std::list<dogen::identification::entities::tagged_value>& element::tagged_values_overrides() const {
    return tagged_values_overrides_;
}

std::list<dogen::identification::entities::tagged_value>& element::tagged_values_overrides() {
    return tagged_values_overrides_;
}

void element::tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>& v) {
    tagged_values_overrides_ = v;
}

void element::tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>&& v) {
    tagged_values_overrides_ = std::move(v);
}

const dogen::codec::entities::comment& element::comment() const {
    return comment_;
}

dogen::codec::entities::comment& element::comment() {
    return comment_;
}

void element::comment(const dogen::codec::entities::comment& v) {
    comment_ = v;
}

void element::comment(const dogen::codec::entities::comment&& v) {
    comment_ = std::move(v);
}

const std::list<std::string>& element::parents() const {
    return parents_;
}

std::list<std::string>& element::parents() {
    return parents_;
}

void element::parents(const std::list<std::string>& v) {
    parents_ = v;
}

void element::parents(const std::list<std::string>&& v) {
    parents_ = std::move(v);
}

const std::list<dogen::codec::entities::attribute>& element::attributes() const {
    return attributes_;
}

std::list<dogen::codec::entities::attribute>& element::attributes() {
    return attributes_;
}

void element::attributes(const std::list<dogen::codec::entities::attribute>& v) {
    attributes_ = v;
}

void element::attributes(const std::list<dogen::codec::entities::attribute>&& v) {
    attributes_ = std::move(v);
}

const std::string& element::fallback_element_type() const {
    return fallback_element_type_;
}

std::string& element::fallback_element_type() {
    return fallback_element_type_;
}

void element::fallback_element_type(const std::string& v) {
    fallback_element_type_ = v;
}

void element::fallback_element_type(const std::string&& v) {
    fallback_element_type_ = std::move(v);
}

bool element::can_be_primitive_underlier() const {
    return can_be_primitive_underlier_;
}

void element::can_be_primitive_underlier(const bool v) {
    can_be_primitive_underlier_ = v;
}

bool element::in_global_module() const {
    return in_global_module_;
}

void element::in_global_module(const bool v) {
    in_global_module_ = v;
}

bool element::can_be_enumeration_underlier() const {
    return can_be_enumeration_underlier_;
}

void element::can_be_enumeration_underlier(const bool v) {
    can_be_enumeration_underlier_ = v;
}

bool element::is_default_enumeration_type() const {
    return is_default_enumeration_type_;
}

void element::is_default_enumeration_type(const bool v) {
    is_default_enumeration_type_ = v;
}

bool element::is_associative_container() const {
    return is_associative_container_;
}

void element::is_associative_container(const bool v) {
    is_associative_container_ = v;
}

bool element::is_floating_point() const {
    return is_floating_point_;
}

void element::is_floating_point(const bool v) {
    is_floating_point_ = v;
}

const dogen::identification::entities::codec_id& element::containing_element_id() const {
    return containing_element_id_;
}

dogen::identification::entities::codec_id& element::containing_element_id() {
    return containing_element_id_;
}

void element::containing_element_id(const dogen::identification::entities::codec_id& v) {
    containing_element_id_ = v;
}

void element::containing_element_id(const dogen::identification::entities::codec_id&& v) {
    containing_element_id_ = std::move(v);
}

const std::list<std::string>& element::plantuml() const {
    return plantuml_;
}

std::list<std::string>& element::plantuml() {
    return plantuml_;
}

void element::plantuml(const std::list<std::string>& v) {
    plantuml_ = v;
}

void element::plantuml(const std::list<std::string>&& v) {
    plantuml_ = std::move(v);
}

}
