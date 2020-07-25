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
#include "dogen.physical/types/entities/archetype.hpp"

namespace dogen::physical::entities {

archetype::archetype(
    const std::string& description,
    const dogen::physical::entities::meta_name& meta_name,
    const std::list<dogen::identification::entities::label>& labels,
    const std::string& default_postfix,
    const std::string& override_postfix,
    const std::list<std::string>& depends,
    const std::list<std::string>& generates,
    const std::string& generated_by,
    const std::string& archetype_kind_id,
    const std::string& logical_meta_element_id,
    const std::string& part,
    const dogen::physical::entities::relations& relations)
    : description_(description),
      meta_name_(meta_name),
      labels_(labels),
      default_postfix_(default_postfix),
      override_postfix_(override_postfix),
      depends_(depends),
      generates_(generates),
      generated_by_(generated_by),
      archetype_kind_id_(archetype_kind_id),
      logical_meta_element_id_(logical_meta_element_id),
      part_(part),
      relations_(relations) { }

void archetype::swap(archetype& other) noexcept {
    using std::swap;
    swap(description_, other.description_);
    swap(meta_name_, other.meta_name_);
    swap(labels_, other.labels_);
    swap(default_postfix_, other.default_postfix_);
    swap(override_postfix_, other.override_postfix_);
    swap(depends_, other.depends_);
    swap(generates_, other.generates_);
    swap(generated_by_, other.generated_by_);
    swap(archetype_kind_id_, other.archetype_kind_id_);
    swap(logical_meta_element_id_, other.logical_meta_element_id_);
    swap(part_, other.part_);
    swap(relations_, other.relations_);
}

bool archetype::operator==(const archetype& rhs) const {
    return description_ == rhs.description_ &&
        meta_name_ == rhs.meta_name_ &&
        labels_ == rhs.labels_ &&
        default_postfix_ == rhs.default_postfix_ &&
        override_postfix_ == rhs.override_postfix_ &&
        depends_ == rhs.depends_ &&
        generates_ == rhs.generates_ &&
        generated_by_ == rhs.generated_by_ &&
        archetype_kind_id_ == rhs.archetype_kind_id_ &&
        logical_meta_element_id_ == rhs.logical_meta_element_id_ &&
        part_ == rhs.part_ &&
        relations_ == rhs.relations_;
}

archetype& archetype::operator=(archetype other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& archetype::description() const {
    return description_;
}

std::string& archetype::description() {
    return description_;
}

void archetype::description(const std::string& v) {
    description_ = v;
}

void archetype::description(const std::string&& v) {
    description_ = std::move(v);
}

const dogen::physical::entities::meta_name& archetype::meta_name() const {
    return meta_name_;
}

dogen::physical::entities::meta_name& archetype::meta_name() {
    return meta_name_;
}

void archetype::meta_name(const dogen::physical::entities::meta_name& v) {
    meta_name_ = v;
}

void archetype::meta_name(const dogen::physical::entities::meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::list<dogen::identification::entities::label>& archetype::labels() const {
    return labels_;
}

std::list<dogen::identification::entities::label>& archetype::labels() {
    return labels_;
}

void archetype::labels(const std::list<dogen::identification::entities::label>& v) {
    labels_ = v;
}

void archetype::labels(const std::list<dogen::identification::entities::label>&& v) {
    labels_ = std::move(v);
}

const std::string& archetype::default_postfix() const {
    return default_postfix_;
}

std::string& archetype::default_postfix() {
    return default_postfix_;
}

void archetype::default_postfix(const std::string& v) {
    default_postfix_ = v;
}

void archetype::default_postfix(const std::string&& v) {
    default_postfix_ = std::move(v);
}

const std::string& archetype::override_postfix() const {
    return override_postfix_;
}

std::string& archetype::override_postfix() {
    return override_postfix_;
}

void archetype::override_postfix(const std::string& v) {
    override_postfix_ = v;
}

void archetype::override_postfix(const std::string&& v) {
    override_postfix_ = std::move(v);
}

const std::list<std::string>& archetype::depends() const {
    return depends_;
}

std::list<std::string>& archetype::depends() {
    return depends_;
}

void archetype::depends(const std::list<std::string>& v) {
    depends_ = v;
}

void archetype::depends(const std::list<std::string>&& v) {
    depends_ = std::move(v);
}

const std::list<std::string>& archetype::generates() const {
    return generates_;
}

std::list<std::string>& archetype::generates() {
    return generates_;
}

void archetype::generates(const std::list<std::string>& v) {
    generates_ = v;
}

void archetype::generates(const std::list<std::string>&& v) {
    generates_ = std::move(v);
}

const std::string& archetype::generated_by() const {
    return generated_by_;
}

std::string& archetype::generated_by() {
    return generated_by_;
}

void archetype::generated_by(const std::string& v) {
    generated_by_ = v;
}

void archetype::generated_by(const std::string&& v) {
    generated_by_ = std::move(v);
}

const std::string& archetype::archetype_kind_id() const {
    return archetype_kind_id_;
}

std::string& archetype::archetype_kind_id() {
    return archetype_kind_id_;
}

void archetype::archetype_kind_id(const std::string& v) {
    archetype_kind_id_ = v;
}

void archetype::archetype_kind_id(const std::string&& v) {
    archetype_kind_id_ = std::move(v);
}

const std::string& archetype::logical_meta_element_id() const {
    return logical_meta_element_id_;
}

std::string& archetype::logical_meta_element_id() {
    return logical_meta_element_id_;
}

void archetype::logical_meta_element_id(const std::string& v) {
    logical_meta_element_id_ = v;
}

void archetype::logical_meta_element_id(const std::string&& v) {
    logical_meta_element_id_ = std::move(v);
}

const std::string& archetype::part() const {
    return part_;
}

std::string& archetype::part() {
    return part_;
}

void archetype::part(const std::string& v) {
    part_ = v;
}

void archetype::part(const std::string&& v) {
    part_ = std::move(v);
}

const dogen::physical::entities::relations& archetype::relations() const {
    return relations_;
}

dogen::physical::entities::relations& archetype::relations() {
    return relations_;
}

void archetype::relations(const dogen::physical::entities::relations& v) {
    relations_ = v;
}

void archetype::relations(const dogen::physical::entities::relations&& v) {
    relations_ = std::move(v);
}

}
