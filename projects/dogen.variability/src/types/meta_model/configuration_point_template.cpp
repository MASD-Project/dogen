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
#include "dogen.variability/io/meta_model/element_io.hpp"
#include "dogen.variability/io/meta_model/template_kind_io.hpp"
#include "dogen.variability/types/meta_model/configuration_point_template.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen::variability::meta_model {

configuration_point_template::configuration_point_template()
    : kind_(static_cast<dogen::variability::meta_model::template_kind>(0)) { }

configuration_point_template::configuration_point_template(
    const dogen::variability::meta_model::name& name,
    const std::string& description,
    const dogen::archetypes::location& location,
    const dogen::variability::meta_model::template_kind kind,
    const std::string& instantiation_domain_name,
    const std::list<std::string>& untyped_value)
    : dogen::variability::meta_model::element(
      name,
      description),
      location_(location),
      kind_(kind),
      instantiation_domain_name_(instantiation_domain_name),
      untyped_value_(untyped_value) { }

void configuration_point_template::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::variability::meta_model::configuration_point_template\"" << ", "
      << "\"__parent_0__\": ";
    dogen::variability::meta_model::element::to_stream(s);
    s << ", "
      << "\"location\": " << location_ << ", "
      << "\"kind\": " << kind_ << ", "
      << "\"instantiation_domain_name\": " << "\"" << tidy_up_string(instantiation_domain_name_) << "\"" << ", "
      << "\"untyped_value\": " << untyped_value_
      << " }";
}

void configuration_point_template::swap(configuration_point_template& other) noexcept {
    dogen::variability::meta_model::element::swap(other);

    using std::swap;
    swap(location_, other.location_);
    swap(kind_, other.kind_);
    swap(instantiation_domain_name_, other.instantiation_domain_name_);
    swap(untyped_value_, other.untyped_value_);
}

bool configuration_point_template::equals(const dogen::variability::meta_model::element& other) const {
    const configuration_point_template* const p(dynamic_cast<const configuration_point_template* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool configuration_point_template::operator==(const configuration_point_template& rhs) const {
    return dogen::variability::meta_model::element::compare(rhs) &&
        location_ == rhs.location_ &&
        kind_ == rhs.kind_ &&
        instantiation_domain_name_ == rhs.instantiation_domain_name_ &&
        untyped_value_ == rhs.untyped_value_;
}

configuration_point_template& configuration_point_template::operator=(configuration_point_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::archetypes::location& configuration_point_template::location() const {
    return location_;
}

dogen::archetypes::location& configuration_point_template::location() {
    return location_;
}

void configuration_point_template::location(const dogen::archetypes::location& v) {
    location_ = v;
}

void configuration_point_template::location(const dogen::archetypes::location&& v) {
    location_ = std::move(v);
}

dogen::variability::meta_model::template_kind configuration_point_template::kind() const {
    return kind_;
}

void configuration_point_template::kind(const dogen::variability::meta_model::template_kind v) {
    kind_ = v;
}

const std::string& configuration_point_template::instantiation_domain_name() const {
    return instantiation_domain_name_;
}

std::string& configuration_point_template::instantiation_domain_name() {
    return instantiation_domain_name_;
}

void configuration_point_template::instantiation_domain_name(const std::string& v) {
    instantiation_domain_name_ = v;
}

void configuration_point_template::instantiation_domain_name(const std::string&& v) {
    instantiation_domain_name_ = std::move(v);
}

const std::list<std::string>& configuration_point_template::untyped_value() const {
    return untyped_value_;
}

std::list<std::string>& configuration_point_template::untyped_value() {
    return untyped_value_;
}

void configuration_point_template::untyped_value(const std::list<std::string>& v) {
    untyped_value_ = v;
}

void configuration_point_template::untyped_value(const std::list<std::string>&& v) {
    untyped_value_ = std::move(v);
}

}
