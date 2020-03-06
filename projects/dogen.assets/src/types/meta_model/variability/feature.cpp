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
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.assets/types/meta_model/variability/feature.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::configuration>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::assets::meta_model::variability {

feature::feature()
    : value_type_(static_cast<dogen::variability::meta_model::value_type>(0)),
      is_optional_(static_cast<bool>(0)),
      requires_optionality_(static_cast<bool>(0)) { }

feature::feature(feature&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      configuration_(std::move(rhs.configuration_)),
      name_(std::move(rhs.name_)),
      key_(std::move(rhs.key_)),
      identifiable_key_(std::move(rhs.identifiable_key_)),
      unparsed_type_(std::move(rhs.unparsed_type_)),
      mapped_type_(std::move(rhs.mapped_type_)),
      parsed_type_(std::move(rhs.parsed_type_)),
      value_(std::move(rhs.value_)),
      value_type_(std::move(rhs.value_type_)),
      binding_point_(std::move(rhs.binding_point_)),
      is_optional_(std::move(rhs.is_optional_)),
      requires_optionality_(std::move(rhs.requires_optionality_)) { }

feature::feature(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const dogen::assets::meta_model::name& name,
    const std::string& key,
    const std::string& identifiable_key,
    const std::string& unparsed_type,
    const std::string& mapped_type,
    const std::string& parsed_type,
    const std::string& value,
    const dogen::variability::meta_model::value_type value_type,
    const boost::optional<dogen::variability::meta_model::binding_point>& binding_point,
    const bool is_optional,
    const bool requires_optionality)
    : documentation_(documentation),
      configuration_(configuration),
      name_(name),
      key_(key),
      identifiable_key_(identifiable_key),
      unparsed_type_(unparsed_type),
      mapped_type_(mapped_type),
      parsed_type_(parsed_type),
      value_(value),
      value_type_(value_type),
      binding_point_(binding_point),
      is_optional_(is_optional),
      requires_optionality_(requires_optionality) { }

void feature::swap(feature& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(configuration_, other.configuration_);
    swap(name_, other.name_);
    swap(key_, other.key_);
    swap(identifiable_key_, other.identifiable_key_);
    swap(unparsed_type_, other.unparsed_type_);
    swap(mapped_type_, other.mapped_type_);
    swap(parsed_type_, other.parsed_type_);
    swap(value_, other.value_);
    swap(value_type_, other.value_type_);
    swap(binding_point_, other.binding_point_);
    swap(is_optional_, other.is_optional_);
    swap(requires_optionality_, other.requires_optionality_);
}

bool feature::operator==(const feature& rhs) const {
    return documentation_ == rhs.documentation_ &&
        configuration_ == rhs.configuration_ &&
        name_ == rhs.name_ &&
        key_ == rhs.key_ &&
        identifiable_key_ == rhs.identifiable_key_ &&
        unparsed_type_ == rhs.unparsed_type_ &&
        mapped_type_ == rhs.mapped_type_ &&
        parsed_type_ == rhs.parsed_type_ &&
        value_ == rhs.value_ &&
        value_type_ == rhs.value_type_ &&
        binding_point_ == rhs.binding_point_ &&
        is_optional_ == rhs.is_optional_ &&
        requires_optionality_ == rhs.requires_optionality_;
}

feature& feature::operator=(feature other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& feature::documentation() const {
    return documentation_;
}

std::string& feature::documentation() {
    return documentation_;
}

void feature::documentation(const std::string& v) {
    documentation_ = v;
}

void feature::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::configuration>& feature::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::meta_model::configuration>& feature::configuration() {
    return configuration_;
}

void feature::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void feature::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::assets::meta_model::name& feature::name() const {
    return name_;
}

dogen::assets::meta_model::name& feature::name() {
    return name_;
}

void feature::name(const dogen::assets::meta_model::name& v) {
    name_ = v;
}

void feature::name(const dogen::assets::meta_model::name&& v) {
    name_ = std::move(v);
}

const std::string& feature::key() const {
    return key_;
}

std::string& feature::key() {
    return key_;
}

void feature::key(const std::string& v) {
    key_ = v;
}

void feature::key(const std::string&& v) {
    key_ = std::move(v);
}

const std::string& feature::identifiable_key() const {
    return identifiable_key_;
}

std::string& feature::identifiable_key() {
    return identifiable_key_;
}

void feature::identifiable_key(const std::string& v) {
    identifiable_key_ = v;
}

void feature::identifiable_key(const std::string&& v) {
    identifiable_key_ = std::move(v);
}

const std::string& feature::unparsed_type() const {
    return unparsed_type_;
}

std::string& feature::unparsed_type() {
    return unparsed_type_;
}

void feature::unparsed_type(const std::string& v) {
    unparsed_type_ = v;
}

void feature::unparsed_type(const std::string&& v) {
    unparsed_type_ = std::move(v);
}

const std::string& feature::mapped_type() const {
    return mapped_type_;
}

std::string& feature::mapped_type() {
    return mapped_type_;
}

void feature::mapped_type(const std::string& v) {
    mapped_type_ = v;
}

void feature::mapped_type(const std::string&& v) {
    mapped_type_ = std::move(v);
}

const std::string& feature::parsed_type() const {
    return parsed_type_;
}

std::string& feature::parsed_type() {
    return parsed_type_;
}

void feature::parsed_type(const std::string& v) {
    parsed_type_ = v;
}

void feature::parsed_type(const std::string&& v) {
    parsed_type_ = std::move(v);
}

const std::string& feature::value() const {
    return value_;
}

std::string& feature::value() {
    return value_;
}

void feature::value(const std::string& v) {
    value_ = v;
}

void feature::value(const std::string&& v) {
    value_ = std::move(v);
}

dogen::variability::meta_model::value_type feature::value_type() const {
    return value_type_;
}

void feature::value_type(const dogen::variability::meta_model::value_type v) {
    value_type_ = v;
}

const boost::optional<dogen::variability::meta_model::binding_point>& feature::binding_point() const {
    return binding_point_;
}

boost::optional<dogen::variability::meta_model::binding_point>& feature::binding_point() {
    return binding_point_;
}

void feature::binding_point(const boost::optional<dogen::variability::meta_model::binding_point>& v) {
    binding_point_ = v;
}

void feature::binding_point(const boost::optional<dogen::variability::meta_model::binding_point>&& v) {
    binding_point_ = std::move(v);
}

bool feature::is_optional() const {
    return is_optional_;
}

void feature::is_optional(const bool v) {
    is_optional_ = v;
}

bool feature::requires_optionality() const {
    return requires_optionality_;
}

void feature::requires_optionality(const bool v) {
    requires_optionality_ = v;
}

}
