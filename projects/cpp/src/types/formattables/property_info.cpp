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
#include "dogen/cpp/types/formattables/property_info.hpp"
#include "dogen/cpp/types/settings/opaque_settings.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& lhs,
const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace cpp {
namespace formattables {

property_info::property_info()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)) { }

property_info::property_info(
    const std::string& name,
    const std::string& documentation,
    const dogen::cpp::formattables::nested_type_info& type,
    const std::list<std::pair<std::string, std::string> >& opaque_parameters,
    const bool is_immutable,
    const bool is_fluent,
    const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& opaque_settings)
    : name_(name),
      documentation_(documentation),
      type_(type),
      opaque_parameters_(opaque_parameters),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      opaque_settings_(opaque_settings) { }

void property_info::swap(property_info& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(documentation_, other.documentation_);
    swap(type_, other.type_);
    swap(opaque_parameters_, other.opaque_parameters_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(opaque_settings_, other.opaque_settings_);
}

bool property_info::operator==(const property_info& rhs) const {
    return name_ == rhs.name_ &&
        documentation_ == rhs.documentation_ &&
        type_ == rhs.type_ &&
        opaque_parameters_ == rhs.opaque_parameters_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        opaque_settings_ == rhs.opaque_settings_;
}

property_info& property_info::operator=(property_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& property_info::name() const {
    return name_;
}

std::string& property_info::name() {
    return name_;
}

void property_info::name(const std::string& v) {
    name_ = v;
}

void property_info::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& property_info::documentation() const {
    return documentation_;
}

std::string& property_info::documentation() {
    return documentation_;
}

void property_info::documentation(const std::string& v) {
    documentation_ = v;
}

void property_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const dogen::cpp::formattables::nested_type_info& property_info::type() const {
    return type_;
}

dogen::cpp::formattables::nested_type_info& property_info::type() {
    return type_;
}

void property_info::type(const dogen::cpp::formattables::nested_type_info& v) {
    type_ = v;
}

void property_info::type(const dogen::cpp::formattables::nested_type_info&& v) {
    type_ = std::move(v);
}

const std::list<std::pair<std::string, std::string> >& property_info::opaque_parameters() const {
    return opaque_parameters_;
}

std::list<std::pair<std::string, std::string> >& property_info::opaque_parameters() {
    return opaque_parameters_;
}

void property_info::opaque_parameters(const std::list<std::pair<std::string, std::string> >& v) {
    opaque_parameters_ = v;
}

void property_info::opaque_parameters(const std::list<std::pair<std::string, std::string> >&& v) {
    opaque_parameters_ = std::move(v);
}

bool property_info::is_immutable() const {
    return is_immutable_;
}

void property_info::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool property_info::is_fluent() const {
    return is_fluent_;
}

void property_info::is_fluent(const bool v) {
    is_fluent_ = v;
}

const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& property_info::opaque_settings() const {
    return opaque_settings_;
}

boost::shared_ptr<dogen::cpp::settings::opaque_settings>& property_info::opaque_settings() {
    return opaque_settings_;
}

void property_info::opaque_settings(const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& v) {
    opaque_settings_ = v;
}

void property_info::opaque_settings(const boost::shared_ptr<dogen::cpp::settings::opaque_settings>&& v) {
    opaque_settings_ = std::move(v);
}

} } }