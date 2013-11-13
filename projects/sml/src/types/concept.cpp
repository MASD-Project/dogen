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
#include "dogen/sml/types/concept.hpp"

namespace dogen {
namespace sml {

concept::concept()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)),
      origin_type_(static_cast<dogen::sml::origin_types>(0)) { }

concept::concept(concept&& rhs)
    : all_properties_(std::move(rhs.all_properties_)),
      local_properties_(std::move(rhs.local_properties_)),
      inherited_properties_(std::move(rhs.inherited_properties_)),
      documentation_(std::move(rhs.documentation_)),
      meta_data_(std::move(rhs.meta_data_)),
      name_(std::move(rhs.name_)),
      generation_type_(std::move(rhs.generation_type_)),
      origin_type_(std::move(rhs.origin_type_)),
      operations_(std::move(rhs.operations_)),
      refines_(std::move(rhs.refines_)) { }

concept::concept(
    const std::list<dogen::sml::property>& all_properties,
    const std::list<dogen::sml::property>& local_properties,
    const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& inherited_properties,
    const std::string& documentation,
    const boost::property_tree::ptree& meta_data,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const dogen::sml::origin_types& origin_type,
    const std::list<dogen::sml::operation>& operations,
    const std::list<dogen::sml::qname>& refines)
    : all_properties_(all_properties),
      local_properties_(local_properties),
      inherited_properties_(inherited_properties),
      documentation_(documentation),
      meta_data_(meta_data),
      name_(name),
      generation_type_(generation_type),
      origin_type_(origin_type),
      operations_(operations),
      refines_(refines) { }

void concept::swap(concept& other) noexcept {
    using std::swap;
    swap(all_properties_, other.all_properties_);
    swap(local_properties_, other.local_properties_);
    swap(inherited_properties_, other.inherited_properties_);
    swap(documentation_, other.documentation_);
    swap(meta_data_, other.meta_data_);
    swap(name_, other.name_);
    swap(generation_type_, other.generation_type_);
    swap(origin_type_, other.origin_type_);
    swap(operations_, other.operations_);
    swap(refines_, other.refines_);
}

bool concept::operator==(const concept& rhs) const {
    return all_properties_ == rhs.all_properties_ &&
        local_properties_ == rhs.local_properties_ &&
        inherited_properties_ == rhs.inherited_properties_ &&
        documentation_ == rhs.documentation_ &&
        meta_data_ == rhs.meta_data_ &&
        name_ == rhs.name_ &&
        generation_type_ == rhs.generation_type_ &&
        origin_type_ == rhs.origin_type_ &&
        operations_ == rhs.operations_ &&
        refines_ == rhs.refines_;
}

concept& concept::operator=(concept other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::sml::property>& concept::all_properties() const {
    return all_properties_;
}

std::list<dogen::sml::property>& concept::all_properties() {
    return all_properties_;
}

void concept::all_properties(const std::list<dogen::sml::property>& v) {
    all_properties_ = v;
}

void concept::all_properties(const std::list<dogen::sml::property>&& v) {
    all_properties_ = std::move(v);
}

const std::list<dogen::sml::property>& concept::local_properties() const {
    return local_properties_;
}

std::list<dogen::sml::property>& concept::local_properties() {
    return local_properties_;
}

void concept::local_properties(const std::list<dogen::sml::property>& v) {
    local_properties_ = v;
}

void concept::local_properties(const std::list<dogen::sml::property>&& v) {
    local_properties_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& concept::inherited_properties() const {
    return inherited_properties_;
}

std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& concept::inherited_properties() {
    return inherited_properties_;
}

void concept::inherited_properties(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& v) {
    inherited_properties_ = v;
}

void concept::inherited_properties(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >&& v) {
    inherited_properties_ = std::move(v);
}

const std::string& concept::documentation() const {
    return documentation_;
}

std::string& concept::documentation() {
    return documentation_;
}

void concept::documentation(const std::string& v) {
    documentation_ = v;
}

void concept::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const boost::property_tree::ptree& concept::meta_data() const {
    return meta_data_;
}

boost::property_tree::ptree& concept::meta_data() {
    return meta_data_;
}

void concept::meta_data(const boost::property_tree::ptree& v) {
    meta_data_ = v;
}

void concept::meta_data(const boost::property_tree::ptree&& v) {
    meta_data_ = std::move(v);
}

const dogen::sml::qname& concept::name() const {
    return name_;
}

dogen::sml::qname& concept::name() {
    return name_;
}

void concept::name(const dogen::sml::qname& v) {
    name_ = v;
}

void concept::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

dogen::sml::generation_types concept::generation_type() const {
    return generation_type_;
}

void concept::generation_type(const dogen::sml::generation_types& v) {
    generation_type_ = v;
}

dogen::sml::origin_types concept::origin_type() const {
    return origin_type_;
}

void concept::origin_type(const dogen::sml::origin_types& v) {
    origin_type_ = v;
}

const std::list<dogen::sml::operation>& concept::operations() const {
    return operations_;
}

std::list<dogen::sml::operation>& concept::operations() {
    return operations_;
}

void concept::operations(const std::list<dogen::sml::operation>& v) {
    operations_ = v;
}

void concept::operations(const std::list<dogen::sml::operation>&& v) {
    operations_ = std::move(v);
}

const std::list<dogen::sml::qname>& concept::refines() const {
    return refines_;
}

std::list<dogen::sml::qname>& concept::refines() {
    return refines_;
}

void concept::refines(const std::list<dogen::sml::qname>& v) {
    refines_ = v;
}

void concept::refines(const std::list<dogen::sml::qname>&& v) {
    refines_ = std::move(v);
}

} }