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
#include "masd.dogen.modeling/types/meta_model/attribute.hpp"

namespace masd::dogen::modeling::meta_model {

attribute::attribute()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)) { }

attribute::attribute(attribute&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      annotation_(std::move(rhs.annotation_)),
      name_(std::move(rhs.name_)),
      unparsed_type_(std::move(rhs.unparsed_type_)),
      parsed_type_(std::move(rhs.parsed_type_)),
      is_immutable_(std::move(rhs.is_immutable_)),
      is_fluent_(std::move(rhs.is_fluent_)),
      orm_properties_(std::move(rhs.orm_properties_)) { }

attribute::attribute(
    const std::string& documentation,
    const masd::dogen::annotations::annotation& annotation,
    const masd::dogen::modeling::meta_model::name& name,
    const std::string& unparsed_type,
    const masd::dogen::modeling::meta_model::name_tree& parsed_type,
    const bool is_immutable,
    const bool is_fluent,
    const boost::optional<masd::dogen::modeling::meta_model::orm_attribute_properties>& orm_properties)
    : documentation_(documentation),
      annotation_(annotation),
      name_(name),
      unparsed_type_(unparsed_type),
      parsed_type_(parsed_type),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      orm_properties_(orm_properties) { }

void attribute::swap(attribute& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(annotation_, other.annotation_);
    swap(name_, other.name_);
    swap(unparsed_type_, other.unparsed_type_);
    swap(parsed_type_, other.parsed_type_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(orm_properties_, other.orm_properties_);
}

bool attribute::operator==(const attribute& rhs) const {
    return documentation_ == rhs.documentation_ &&
        annotation_ == rhs.annotation_ &&
        name_ == rhs.name_ &&
        unparsed_type_ == rhs.unparsed_type_ &&
        parsed_type_ == rhs.parsed_type_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        orm_properties_ == rhs.orm_properties_;
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

const masd::dogen::annotations::annotation& attribute::annotation() const {
    return annotation_;
}

masd::dogen::annotations::annotation& attribute::annotation() {
    return annotation_;
}

void attribute::annotation(const masd::dogen::annotations::annotation& v) {
    annotation_ = v;
}

void attribute::annotation(const masd::dogen::annotations::annotation&& v) {
    annotation_ = std::move(v);
}

const masd::dogen::modeling::meta_model::name& attribute::name() const {
    return name_;
}

masd::dogen::modeling::meta_model::name& attribute::name() {
    return name_;
}

void attribute::name(const masd::dogen::modeling::meta_model::name& v) {
    name_ = v;
}

void attribute::name(const masd::dogen::modeling::meta_model::name&& v) {
    name_ = std::move(v);
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

const masd::dogen::modeling::meta_model::name_tree& attribute::parsed_type() const {
    return parsed_type_;
}

masd::dogen::modeling::meta_model::name_tree& attribute::parsed_type() {
    return parsed_type_;
}

void attribute::parsed_type(const masd::dogen::modeling::meta_model::name_tree& v) {
    parsed_type_ = v;
}

void attribute::parsed_type(const masd::dogen::modeling::meta_model::name_tree&& v) {
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

const boost::optional<masd::dogen::modeling::meta_model::orm_attribute_properties>& attribute::orm_properties() const {
    return orm_properties_;
}

boost::optional<masd::dogen::modeling::meta_model::orm_attribute_properties>& attribute::orm_properties() {
    return orm_properties_;
}

void attribute::orm_properties(const boost::optional<masd::dogen::modeling::meta_model::orm_attribute_properties>& v) {
    orm_properties_ = v;
}

void attribute::orm_properties(const boost::optional<masd::dogen::modeling::meta_model::orm_attribute_properties>&& v) {
    orm_properties_ = std::move(v);
}

}
