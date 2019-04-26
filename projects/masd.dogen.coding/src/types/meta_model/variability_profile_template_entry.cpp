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
#include "masd.dogen.coding/types/meta_model/variability_profile_template_entry.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& lhs,
const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace masd::dogen::coding::meta_model {

variability_profile_template_entry::variability_profile_template_entry(
    const std::string& documentation,
    const masd::dogen::variability::annotation& annotation,
    const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration,
    const masd::dogen::coding::meta_model::name& name,
    const std::string& key,
    const std::list<std::string>& value)
    : documentation_(documentation),
      annotation_(annotation),
      configuration_(configuration),
      name_(name),
      key_(key),
      value_(value) { }

void variability_profile_template_entry::swap(variability_profile_template_entry& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(annotation_, other.annotation_);
    swap(configuration_, other.configuration_);
    swap(name_, other.name_);
    swap(key_, other.key_);
    swap(value_, other.value_);
}

bool variability_profile_template_entry::operator==(const variability_profile_template_entry& rhs) const {
    return documentation_ == rhs.documentation_ &&
        annotation_ == rhs.annotation_ &&
        configuration_ == rhs.configuration_ &&
        name_ == rhs.name_ &&
        key_ == rhs.key_ &&
        value_ == rhs.value_;
}

variability_profile_template_entry& variability_profile_template_entry::operator=(variability_profile_template_entry other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& variability_profile_template_entry::documentation() const {
    return documentation_;
}

std::string& variability_profile_template_entry::documentation() {
    return documentation_;
}

void variability_profile_template_entry::documentation(const std::string& v) {
    documentation_ = v;
}

void variability_profile_template_entry::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const masd::dogen::variability::annotation& variability_profile_template_entry::annotation() const {
    return annotation_;
}

masd::dogen::variability::annotation& variability_profile_template_entry::annotation() {
    return annotation_;
}

void variability_profile_template_entry::annotation(const masd::dogen::variability::annotation& v) {
    annotation_ = v;
}

void variability_profile_template_entry::annotation(const masd::dogen::variability::annotation&& v) {
    annotation_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& variability_profile_template_entry::configuration() const {
    return configuration_;
}

boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& variability_profile_template_entry::configuration() {
    return configuration_;
}

void variability_profile_template_entry::configuration(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void variability_profile_template_entry::configuration(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const masd::dogen::coding::meta_model::name& variability_profile_template_entry::name() const {
    return name_;
}

masd::dogen::coding::meta_model::name& variability_profile_template_entry::name() {
    return name_;
}

void variability_profile_template_entry::name(const masd::dogen::coding::meta_model::name& v) {
    name_ = v;
}

void variability_profile_template_entry::name(const masd::dogen::coding::meta_model::name&& v) {
    name_ = std::move(v);
}

const std::string& variability_profile_template_entry::key() const {
    return key_;
}

std::string& variability_profile_template_entry::key() {
    return key_;
}

void variability_profile_template_entry::key(const std::string& v) {
    key_ = v;
}

void variability_profile_template_entry::key(const std::string&& v) {
    key_ = std::move(v);
}

const std::list<std::string>& variability_profile_template_entry::value() const {
    return value_;
}

std::list<std::string>& variability_profile_template_entry::value() {
    return value_;
}

void variability_profile_template_entry::value(const std::list<std::string>& v) {
    value_ = v;
}

void variability_profile_template_entry::value(const std::list<std::string>&& v) {
    value_ = std::move(v);
}

}
