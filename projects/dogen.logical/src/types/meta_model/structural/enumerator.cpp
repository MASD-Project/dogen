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
#include "dogen.logical/types/meta_model/structural/enumerator.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::configuration>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::meta_model::structural {

enumerator::enumerator(
    const std::string& documentation,
    const dogen::logical::meta_model::name& name,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const std::list<dogen::logical::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const std::string& value)
    : documentation_(documentation),
      name_(name),
      configuration_(configuration),
      static_stereotypes_(static_stereotypes),
      dynamic_stereotypes_(dynamic_stereotypes),
      value_(value) { }

void enumerator::swap(enumerator& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(name_, other.name_);
    swap(configuration_, other.configuration_);
    swap(static_stereotypes_, other.static_stereotypes_);
    swap(dynamic_stereotypes_, other.dynamic_stereotypes_);
    swap(value_, other.value_);
}

bool enumerator::operator==(const enumerator& rhs) const {
    return documentation_ == rhs.documentation_ &&
        name_ == rhs.name_ &&
        configuration_ == rhs.configuration_ &&
        static_stereotypes_ == rhs.static_stereotypes_ &&
        dynamic_stereotypes_ == rhs.dynamic_stereotypes_ &&
        value_ == rhs.value_;
}

enumerator& enumerator::operator=(enumerator other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& enumerator::documentation() const {
    return documentation_;
}

std::string& enumerator::documentation() {
    return documentation_;
}

void enumerator::documentation(const std::string& v) {
    documentation_ = v;
}

void enumerator::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const dogen::logical::meta_model::name& enumerator::name() const {
    return name_;
}

dogen::logical::meta_model::name& enumerator::name() {
    return name_;
}

void enumerator::name(const dogen::logical::meta_model::name& v) {
    name_ = v;
}

void enumerator::name(const dogen::logical::meta_model::name&& v) {
    name_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::configuration>& enumerator::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::meta_model::configuration>& enumerator::configuration() {
    return configuration_;
}

void enumerator::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void enumerator::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const std::list<dogen::logical::meta_model::static_stereotypes>& enumerator::static_stereotypes() const {
    return static_stereotypes_;
}

std::list<dogen::logical::meta_model::static_stereotypes>& enumerator::static_stereotypes() {
    return static_stereotypes_;
}

void enumerator::static_stereotypes(const std::list<dogen::logical::meta_model::static_stereotypes>& v) {
    static_stereotypes_ = v;
}

void enumerator::static_stereotypes(const std::list<dogen::logical::meta_model::static_stereotypes>&& v) {
    static_stereotypes_ = std::move(v);
}

const std::list<std::string>& enumerator::dynamic_stereotypes() const {
    return dynamic_stereotypes_;
}

std::list<std::string>& enumerator::dynamic_stereotypes() {
    return dynamic_stereotypes_;
}

void enumerator::dynamic_stereotypes(const std::list<std::string>& v) {
    dynamic_stereotypes_ = v;
}

void enumerator::dynamic_stereotypes(const std::list<std::string>&& v) {
    dynamic_stereotypes_ = std::move(v);
}

const std::string& enumerator::value() const {
    return value_;
}

std::string& enumerator::value() {
    return value_;
}

void enumerator::value(const std::string& v) {
    value_ = v;
}

void enumerator::value(const std::string&& v) {
    value_ = std::move(v);
}

}
