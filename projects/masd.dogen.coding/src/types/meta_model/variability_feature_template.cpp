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
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.coding/types/meta_model/variability_feature_template.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& lhs,
const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace masd::dogen::coding::meta_model {

variability_feature_template::variability_feature_template()
    : template_kind_(static_cast<masd::dogen::variability::meta_model::template_kind>(0)),
      binding_point_(static_cast<masd::dogen::variability::meta_model::binding_point>(0)) { }

variability_feature_template::variability_feature_template(
    const std::string& documentation,
    const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration,
    const masd::dogen::coding::meta_model::name& name,
    const std::string& type,
    const masd::dogen::archetypes::location& location,
    const masd::dogen::variability::meta_model::template_kind template_kind,
    const masd::dogen::variability::meta_model::binding_point binding_point)
    : documentation_(documentation),
      configuration_(configuration),
      name_(name),
      type_(type),
      location_(location),
      template_kind_(template_kind),
      binding_point_(binding_point) { }

void variability_feature_template::swap(variability_feature_template& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(configuration_, other.configuration_);
    swap(name_, other.name_);
    swap(type_, other.type_);
    swap(location_, other.location_);
    swap(template_kind_, other.template_kind_);
    swap(binding_point_, other.binding_point_);
}

bool variability_feature_template::operator==(const variability_feature_template& rhs) const {
    return documentation_ == rhs.documentation_ &&
        configuration_ == rhs.configuration_ &&
        name_ == rhs.name_ &&
        type_ == rhs.type_ &&
        location_ == rhs.location_ &&
        template_kind_ == rhs.template_kind_ &&
        binding_point_ == rhs.binding_point_;
}

variability_feature_template& variability_feature_template::operator=(variability_feature_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& variability_feature_template::documentation() const {
    return documentation_;
}

std::string& variability_feature_template::documentation() {
    return documentation_;
}

void variability_feature_template::documentation(const std::string& v) {
    documentation_ = v;
}

void variability_feature_template::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& variability_feature_template::configuration() const {
    return configuration_;
}

boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& variability_feature_template::configuration() {
    return configuration_;
}

void variability_feature_template::configuration(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void variability_feature_template::configuration(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const masd::dogen::coding::meta_model::name& variability_feature_template::name() const {
    return name_;
}

masd::dogen::coding::meta_model::name& variability_feature_template::name() {
    return name_;
}

void variability_feature_template::name(const masd::dogen::coding::meta_model::name& v) {
    name_ = v;
}

void variability_feature_template::name(const masd::dogen::coding::meta_model::name&& v) {
    name_ = std::move(v);
}

const std::string& variability_feature_template::type() const {
    return type_;
}

std::string& variability_feature_template::type() {
    return type_;
}

void variability_feature_template::type(const std::string& v) {
    type_ = v;
}

void variability_feature_template::type(const std::string&& v) {
    type_ = std::move(v);
}

const masd::dogen::archetypes::location& variability_feature_template::location() const {
    return location_;
}

masd::dogen::archetypes::location& variability_feature_template::location() {
    return location_;
}

void variability_feature_template::location(const masd::dogen::archetypes::location& v) {
    location_ = v;
}

void variability_feature_template::location(const masd::dogen::archetypes::location&& v) {
    location_ = std::move(v);
}

masd::dogen::variability::meta_model::template_kind variability_feature_template::template_kind() const {
    return template_kind_;
}

void variability_feature_template::template_kind(const masd::dogen::variability::meta_model::template_kind v) {
    template_kind_ = v;
}

masd::dogen::variability::meta_model::binding_point variability_feature_template::binding_point() const {
    return binding_point_;
}

void variability_feature_template::binding_point(const masd::dogen::variability::meta_model::binding_point v) {
    binding_point_ = v;
}

}
