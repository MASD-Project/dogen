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
#include "dogen.assets/types/meta_model/attribute.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::configuration>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::assets::meta_model {

attribute::attribute()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)) { }

attribute::attribute(attribute&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      configuration_(std::move(rhs.configuration_)),
      name_(std::move(rhs.name_)),
      static_stereotypes_(std::move(rhs.static_stereotypes_)),
      dynamic_stereotypes_(std::move(rhs.dynamic_stereotypes_)),
      unparsed_type_(std::move(rhs.unparsed_type_)),
      parsed_type_(std::move(rhs.parsed_type_)),
      is_immutable_(std::move(rhs.is_immutable_)),
      is_fluent_(std::move(rhs.is_fluent_)),
      orm_properties_(std::move(rhs.orm_properties_)),
      member_variable_name_(std::move(rhs.member_variable_name_)) { }

attribute::attribute(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const dogen::assets::meta_model::name& name,
    const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const std::string& unparsed_type,
    const dogen::assets::meta_model::name_tree& parsed_type,
    const bool is_immutable,
    const bool is_fluent,
    const boost::optional<dogen::assets::meta_model::orm::attribute_properties>& orm_properties,
    const std::string& member_variable_name)
    : documentation_(documentation),
      configuration_(configuration),
      name_(name),
      static_stereotypes_(static_stereotypes),
      dynamic_stereotypes_(dynamic_stereotypes),
      unparsed_type_(unparsed_type),
      parsed_type_(parsed_type),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      orm_properties_(orm_properties),
      member_variable_name_(member_variable_name) { }

void attribute::swap(attribute& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(configuration_, other.configuration_);
    swap(name_, other.name_);
    swap(static_stereotypes_, other.static_stereotypes_);
    swap(dynamic_stereotypes_, other.dynamic_stereotypes_);
    swap(unparsed_type_, other.unparsed_type_);
    swap(parsed_type_, other.parsed_type_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(orm_properties_, other.orm_properties_);
    swap(member_variable_name_, other.member_variable_name_);
}

bool attribute::operator==(const attribute& rhs) const {
    return documentation_ == rhs.documentation_ &&
        configuration_ == rhs.configuration_ &&
        name_ == rhs.name_ &&
        static_stereotypes_ == rhs.static_stereotypes_ &&
        dynamic_stereotypes_ == rhs.dynamic_stereotypes_ &&
        unparsed_type_ == rhs.unparsed_type_ &&
        parsed_type_ == rhs.parsed_type_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        orm_properties_ == rhs.orm_properties_ &&
        member_variable_name_ == rhs.member_variable_name_;
}

attribute& attribute::operator=(attribute other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& attribute::documentation() const {
    return documentation_;
}

std::string& attribute::documentation() {
    return documentation_;
}

void attribute::documentation(const std::string& v) {
    documentation_ = v;
}

void attribute::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::configuration>& attribute::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::meta_model::configuration>& attribute::configuration() {
    return configuration_;
}

void attribute::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void attribute::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::assets::meta_model::name& attribute::name() const {
    return name_;
}

dogen::assets::meta_model::name& attribute::name() {
    return name_;
}

void attribute::name(const dogen::assets::meta_model::name& v) {
    name_ = v;
}

void attribute::name(const dogen::assets::meta_model::name&& v) {
    name_ = std::move(v);
}

const std::list<dogen::assets::meta_model::static_stereotypes>& attribute::static_stereotypes() const {
    return static_stereotypes_;
}

std::list<dogen::assets::meta_model::static_stereotypes>& attribute::static_stereotypes() {
    return static_stereotypes_;
}

void attribute::static_stereotypes(const std::list<dogen::assets::meta_model::static_stereotypes>& v) {
    static_stereotypes_ = v;
}

void attribute::static_stereotypes(const std::list<dogen::assets::meta_model::static_stereotypes>&& v) {
    static_stereotypes_ = std::move(v);
}

const std::list<std::string>& attribute::dynamic_stereotypes() const {
    return dynamic_stereotypes_;
}

std::list<std::string>& attribute::dynamic_stereotypes() {
    return dynamic_stereotypes_;
}

void attribute::dynamic_stereotypes(const std::list<std::string>& v) {
    dynamic_stereotypes_ = v;
}

void attribute::dynamic_stereotypes(const std::list<std::string>&& v) {
    dynamic_stereotypes_ = std::move(v);
}

const std::string& attribute::unparsed_type() const {
    return unparsed_type_;
}

std::string& attribute::unparsed_type() {
    return unparsed_type_;
}

void attribute::unparsed_type(const std::string& v) {
    unparsed_type_ = v;
}

void attribute::unparsed_type(const std::string&& v) {
    unparsed_type_ = std::move(v);
}

const dogen::assets::meta_model::name_tree& attribute::parsed_type() const {
    return parsed_type_;
}

dogen::assets::meta_model::name_tree& attribute::parsed_type() {
    return parsed_type_;
}

void attribute::parsed_type(const dogen::assets::meta_model::name_tree& v) {
    parsed_type_ = v;
}

void attribute::parsed_type(const dogen::assets::meta_model::name_tree&& v) {
    parsed_type_ = std::move(v);
}

bool attribute::is_immutable() const {
    return is_immutable_;
}

void attribute::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool attribute::is_fluent() const {
    return is_fluent_;
}

void attribute::is_fluent(const bool v) {
    is_fluent_ = v;
}

const boost::optional<dogen::assets::meta_model::orm::attribute_properties>& attribute::orm_properties() const {
    return orm_properties_;
}

boost::optional<dogen::assets::meta_model::orm::attribute_properties>& attribute::orm_properties() {
    return orm_properties_;
}

void attribute::orm_properties(const boost::optional<dogen::assets::meta_model::orm::attribute_properties>& v) {
    orm_properties_ = v;
}

void attribute::orm_properties(const boost::optional<dogen::assets::meta_model::orm::attribute_properties>&& v) {
    orm_properties_ = std::move(v);
}

const std::string& attribute::member_variable_name() const {
    return member_variable_name_;
}

std::string& attribute::member_variable_name() {
    return member_variable_name_;
}

void attribute::member_variable_name(const std::string& v) {
    member_variable_name_ = v;
}

void attribute::member_variable_name(const std::string&& v) {
    member_variable_name_ = std::move(v);
}

}
