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
#include "dogen.assets/types/meta_model/variability/entry.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::configuration>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::assets::meta_model::variability {

entry::entry(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const dogen::assets::meta_model::name& name,
    const std::string& key,
    const std::string& value)
    : documentation_(documentation),
      configuration_(configuration),
      name_(name),
      key_(key),
      value_(value) { }

void entry::swap(entry& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(configuration_, other.configuration_);
    swap(name_, other.name_);
    swap(key_, other.key_);
    swap(value_, other.value_);
}

bool entry::operator==(const entry& rhs) const {
    return documentation_ == rhs.documentation_ &&
        configuration_ == rhs.configuration_ &&
        name_ == rhs.name_ &&
        key_ == rhs.key_ &&
        value_ == rhs.value_;
}

entry& entry::operator=(entry other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& entry::documentation() const {
    return documentation_;
}

std::string& entry::documentation() {
    return documentation_;
}

void entry::documentation(const std::string& v) {
    documentation_ = v;
}

void entry::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::configuration>& entry::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::meta_model::configuration>& entry::configuration() {
    return configuration_;
}

void entry::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void entry::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::assets::meta_model::name& entry::name() const {
    return name_;
}

dogen::assets::meta_model::name& entry::name() {
    return name_;
}

void entry::name(const dogen::assets::meta_model::name& v) {
    name_ = v;
}

void entry::name(const dogen::assets::meta_model::name&& v) {
    name_ = std::move(v);
}

const std::string& entry::key() const {
    return key_;
}

std::string& entry::key() {
    return key_;
}

void entry::key(const std::string& v) {
    key_ = v;
}

void entry::key(const std::string&& v) {
    key_ = std::move(v);
}

const std::string& entry::value() const {
    return value_;
}

std::string& entry::value() {
    return value_;
}

void entry::value(const std::string& v) {
    value_ = v;
}

void entry::value(const std::string&& v) {
    value_ = std::move(v);
}

}
