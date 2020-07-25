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
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.variability/io/entities/element_io.hpp"
#include "dogen.variability/io/entities/binding_point_io.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/io/entities/potential_binding_io.hpp"
#include "dogen.variability/io/entities/configuration_point_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::variability::entities::configuration_point>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::variability::entities::potential_binding>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::variability::entities {

configuration::configuration()
    : source_binding_point_(static_cast<dogen::variability::entities::binding_point>(0)),
      from_target_(static_cast<bool>(0)) { }

configuration::configuration(
    const dogen::identification::entities::name& name,
    const std::string& description,
    const std::unordered_map<std::string, dogen::variability::entities::configuration_point>& configuration_points,
    const std::list<dogen::variability::entities::potential_binding>& profile_bindings,
    const std::list<dogen::variability::entities::potential_binding>& configuration_bindings,
    const dogen::variability::entities::binding_point source_binding_point,
    const bool from_target)
    : dogen::variability::entities::element(
      name,
      description),
      configuration_points_(configuration_points),
      profile_bindings_(profile_bindings),
      configuration_bindings_(configuration_bindings),
      source_binding_point_(source_binding_point),
      from_target_(from_target) { }

void configuration::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::variability::entities::configuration\"" << ", "
      << "\"__parent_0__\": ";
    dogen::variability::entities::element::to_stream(s);
    s << ", "
      << "\"configuration_points\": " << configuration_points_ << ", "
      << "\"profile_bindings\": " << profile_bindings_ << ", "
      << "\"configuration_bindings\": " << configuration_bindings_ << ", "
      << "\"source_binding_point\": " << source_binding_point_ << ", "
      << "\"from_target\": " << from_target_
      << " }";
}

void configuration::swap(configuration& other) noexcept {
    dogen::variability::entities::element::swap(other);

    using std::swap;
    swap(configuration_points_, other.configuration_points_);
    swap(profile_bindings_, other.profile_bindings_);
    swap(configuration_bindings_, other.configuration_bindings_);
    swap(source_binding_point_, other.source_binding_point_);
    swap(from_target_, other.from_target_);
}

bool configuration::equals(const dogen::variability::entities::element& other) const {
    const configuration* const p(dynamic_cast<const configuration* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool configuration::operator==(const configuration& rhs) const {
    return dogen::variability::entities::element::compare(rhs) &&
        configuration_points_ == rhs.configuration_points_ &&
        profile_bindings_ == rhs.profile_bindings_ &&
        configuration_bindings_ == rhs.configuration_bindings_ &&
        source_binding_point_ == rhs.source_binding_point_ &&
        from_target_ == rhs.from_target_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::variability::entities::configuration_point>& configuration::configuration_points() const {
    return configuration_points_;
}

std::unordered_map<std::string, dogen::variability::entities::configuration_point>& configuration::configuration_points() {
    return configuration_points_;
}

void configuration::configuration_points(const std::unordered_map<std::string, dogen::variability::entities::configuration_point>& v) {
    configuration_points_ = v;
}

void configuration::configuration_points(const std::unordered_map<std::string, dogen::variability::entities::configuration_point>&& v) {
    configuration_points_ = std::move(v);
}

const std::list<dogen::variability::entities::potential_binding>& configuration::profile_bindings() const {
    return profile_bindings_;
}

std::list<dogen::variability::entities::potential_binding>& configuration::profile_bindings() {
    return profile_bindings_;
}

void configuration::profile_bindings(const std::list<dogen::variability::entities::potential_binding>& v) {
    profile_bindings_ = v;
}

void configuration::profile_bindings(const std::list<dogen::variability::entities::potential_binding>&& v) {
    profile_bindings_ = std::move(v);
}

const std::list<dogen::variability::entities::potential_binding>& configuration::configuration_bindings() const {
    return configuration_bindings_;
}

std::list<dogen::variability::entities::potential_binding>& configuration::configuration_bindings() {
    return configuration_bindings_;
}

void configuration::configuration_bindings(const std::list<dogen::variability::entities::potential_binding>& v) {
    configuration_bindings_ = v;
}

void configuration::configuration_bindings(const std::list<dogen::variability::entities::potential_binding>&& v) {
    configuration_bindings_ = std::move(v);
}

dogen::variability::entities::binding_point configuration::source_binding_point() const {
    return source_binding_point_;
}

void configuration::source_binding_point(const dogen::variability::entities::binding_point v) {
    source_binding_point_ = v;
}

bool configuration::from_target() const {
    return from_target_;
}

void configuration::from_target(const bool v) {
    from_target_ = v;
}

}
