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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen.archetypes/io/location_io.hpp"
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.variability/io/meta_model/configuration_io.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.assets/types/meta_model/variability/abstract_profile_entry.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::configuration>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::assets::meta_model::variability {

abstract_profile_entry::abstract_profile_entry(
    const std::string& documentation,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const dogen::assets::meta_model::name& name,
    const std::string& key,
    const std::string& value,
    const dogen::archetypes::location& location)
    : documentation_(documentation),
      configuration_(configuration),
      name_(name),
      key_(key),
      value_(value),
      location_(location) { }

void abstract_profile_entry::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::abstract_profile_entry\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(documentation_) << "\"" << ", "
      << "\"configuration\": " << configuration_ << ", "
      << "\"name\": " << name_ << ", "
      << "\"key\": " << "\"" << tidy_up_string(key_) << "\"" << ", "
      << "\"value\": " << "\"" << tidy_up_string(value_) << "\"" << ", "
      << "\"location\": " << location_
      << " }";
}

void abstract_profile_entry::swap(abstract_profile_entry& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(configuration_, other.configuration_);
    swap(name_, other.name_);
    swap(key_, other.key_);
    swap(value_, other.value_);
    swap(location_, other.location_);
}

bool abstract_profile_entry::compare(const abstract_profile_entry& rhs) const {
    return documentation_ == rhs.documentation_ &&
        configuration_ == rhs.configuration_ &&
        name_ == rhs.name_ &&
        key_ == rhs.key_ &&
        value_ == rhs.value_ &&
        location_ == rhs.location_;
}

const std::string& abstract_profile_entry::documentation() const {
    return documentation_;
}

std::string& abstract_profile_entry::documentation() {
    return documentation_;
}

void abstract_profile_entry::documentation(const std::string& v) {
    documentation_ = v;
}

void abstract_profile_entry::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::configuration>& abstract_profile_entry::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::meta_model::configuration>& abstract_profile_entry::configuration() {
    return configuration_;
}

void abstract_profile_entry::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
    configuration_ = v;
}

void abstract_profile_entry::configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::assets::meta_model::name& abstract_profile_entry::name() const {
    return name_;
}

dogen::assets::meta_model::name& abstract_profile_entry::name() {
    return name_;
}

void abstract_profile_entry::name(const dogen::assets::meta_model::name& v) {
    name_ = v;
}

void abstract_profile_entry::name(const dogen::assets::meta_model::name&& v) {
    name_ = std::move(v);
}

const std::string& abstract_profile_entry::key() const {
    return key_;
}

std::string& abstract_profile_entry::key() {
    return key_;
}

void abstract_profile_entry::key(const std::string& v) {
    key_ = v;
}

void abstract_profile_entry::key(const std::string&& v) {
    key_ = std::move(v);
}

const std::string& abstract_profile_entry::value() const {
    return value_;
}

std::string& abstract_profile_entry::value() {
    return value_;
}

void abstract_profile_entry::value(const std::string& v) {
    value_ = v;
}

void abstract_profile_entry::value(const std::string&& v) {
    value_ = std::move(v);
}

const dogen::archetypes::location& abstract_profile_entry::location() const {
    return location_;
}

dogen::archetypes::location& abstract_profile_entry::location() {
    return location_;
}

void abstract_profile_entry::location(const dogen::archetypes::location& v) {
    location_ = v;
}

void abstract_profile_entry::location(const dogen::archetypes::location&& v) {
    location_ = std::move(v);
}

}
