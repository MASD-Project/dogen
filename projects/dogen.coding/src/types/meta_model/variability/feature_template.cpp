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
#include "dogen.coding/types/meta_model/variability/feature_template.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::configuration>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::coding::meta_model::variability {

feature_template::feature_template()
    : value_type_(static_cast<dogen::variability::meta_model::value_type>(0)),
      binding_point_(static_cast<dogen::variability::meta_model::binding_point>(0)),
      template_kind_(static_cast<dogen::variability::meta_model::template_kind>(0)) { }

feature_template::feature_template(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const dogen::coding::meta_model::name& name,
    const std::string& key,
    const std::string& identifiable_key,
    const std::string& value,
    const dogen::archetypes::location& location,
    const dogen::variability::meta_model::value_type value_type,
    const dogen::variability::meta_model::binding_point binding_point,
    const dogen::variability::meta_model::template_kind template_kind)
    : documentation_(documentation),
      configuration_(configuration),
      name_(name),
      key_(key),
      identifiable_key_(identifiable_key),
      value_(value),
      location_(location),
      value_type_(value_type),
      binding_point_(binding_point),
      template_kind_(template_kind) { }

void feature_template::swap(feature_template& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(configuration_, other.configuration_);
    swap(name_, other.name_);
    swap(key_, other.key_);
    swap(identifiable_key_, other.identifiable_key_);
    swap(value_, other.value_);
    swap(location_, other.location_);
    swap(value_type_, other.value_type_);
    swap(binding_point_, other.binding_point_);
    swap(template_kind_, other.template_kind_);
}

bool feature_template::operator==(const feature_template& rhs) const {
    return documentation_ == rhs.documentation_ &&
        configuration_ == rhs.configuration_ &&
        name_ == rhs.name_ &&
        key_ == rhs.key_ &&
        identifiable_key_ == rhs.identifiable_key_ &&
        value_ == rhs.value_ &&
        location_ == rhs.location_ &&
        value_type_ == rhs.value_type_ &&
        binding_point_ == rhs.binding_point_ &&
        template_kind_ == rhs.template_kind_;
}

feature_template& feature_template::operator=(feature_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& feature_template::documentation() const {
    return documentation_;
}

std::string& feature_template::documentation() {
    return documentation_;
}

void feature_template::documentation(const std::string& v) {
    documentation_ = v;
}

void feature_template::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::configuration>& feature_template::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::meta_model::configuration>& feature_template::configuration() {
    return configuration_;
}

void feature_template::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void feature_template::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::coding::meta_model::name& feature_template::name() const {
    return name_;
}

dogen::coding::meta_model::name& feature_template::name() {
    return name_;
}

void feature_template::name(const dogen::coding::meta_model::name& v) {
    name_ = v;
}

void feature_template::name(const dogen::coding::meta_model::name&& v) {
    name_ = std::move(v);
}

const std::string& feature_template::key() const {
    return key_;
}

std::string& feature_template::key() {
    return key_;
}

void feature_template::key(const std::string& v) {
    key_ = v;
}

void feature_template::key(const std::string&& v) {
    key_ = std::move(v);
}

const std::string& feature_template::identifiable_key() const {
    return identifiable_key_;
}

std::string& feature_template::identifiable_key() {
    return identifiable_key_;
}

void feature_template::identifiable_key(const std::string& v) {
    identifiable_key_ = v;
}

void feature_template::identifiable_key(const std::string&& v) {
    identifiable_key_ = std::move(v);
}

const std::string& feature_template::value() const {
    return value_;
}

std::string& feature_template::value() {
    return value_;
}

void feature_template::value(const std::string& v) {
    value_ = v;
}

void feature_template::value(const std::string&& v) {
    value_ = std::move(v);
}

const dogen::archetypes::location& feature_template::location() const {
    return location_;
}

dogen::archetypes::location& feature_template::location() {
    return location_;
}

void feature_template::location(const dogen::archetypes::location& v) {
    location_ = v;
}

void feature_template::location(const dogen::archetypes::location&& v) {
    location_ = std::move(v);
}

dogen::variability::meta_model::value_type feature_template::value_type() const {
    return value_type_;
}

void feature_template::value_type(const dogen::variability::meta_model::value_type v) {
    value_type_ = v;
}

dogen::variability::meta_model::binding_point feature_template::binding_point() const {
    return binding_point_;
}

void feature_template::binding_point(const dogen::variability::meta_model::binding_point v) {
    binding_point_ = v;
}

dogen::variability::meta_model::template_kind feature_template::template_kind() const {
    return template_kind_;
}

void feature_template::template_kind(const dogen::variability::meta_model::template_kind v) {
    template_kind_ = v;
}

}
