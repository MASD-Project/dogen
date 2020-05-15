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
#include "dogen.variability/io/entities/element_io.hpp"
#include "dogen.variability/io/entities/binding_point_io.hpp"
#include "dogen.variability/types/entities/profile_template.hpp"
#include "dogen.variability/io/entities/configuration_point_template_io.hpp"

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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::variability::entities::configuration_point_template>& v) {
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

profile_template::profile_template()
    : binding_point_(static_cast<dogen::variability::entities::binding_point>(0)) { }

profile_template::profile_template(
    const dogen::variability::entities::name& name,
    const std::string& description,
    const dogen::variability::entities::binding_point binding_point,
    const std::list<std::string>& parents,
    const std::string& stereotype,
    const std::list<dogen::variability::entities::configuration_point_template>& templates)
    : dogen::variability::entities::element(
      name,
      description),
      binding_point_(binding_point),
      parents_(parents),
      stereotype_(stereotype),
      templates_(templates) { }

void profile_template::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::variability::entities::profile_template\"" << ", "
      << "\"__parent_0__\": ";
    dogen::variability::entities::element::to_stream(s);
    s << ", "
      << "\"binding_point\": " << binding_point_ << ", "
      << "\"parents\": " << parents_ << ", "
      << "\"stereotype\": " << "\"" << tidy_up_string(stereotype_) << "\"" << ", "
      << "\"templates\": " << templates_
      << " }";
}

void profile_template::swap(profile_template& other) noexcept {
    dogen::variability::entities::element::swap(other);

    using std::swap;
    swap(binding_point_, other.binding_point_);
    swap(parents_, other.parents_);
    swap(stereotype_, other.stereotype_);
    swap(templates_, other.templates_);
}

bool profile_template::equals(const dogen::variability::entities::element& other) const {
    const profile_template* const p(dynamic_cast<const profile_template* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool profile_template::operator==(const profile_template& rhs) const {
    return dogen::variability::entities::element::compare(rhs) &&
        binding_point_ == rhs.binding_point_ &&
        parents_ == rhs.parents_ &&
        stereotype_ == rhs.stereotype_ &&
        templates_ == rhs.templates_;
}

profile_template& profile_template::operator=(profile_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::variability::entities::binding_point profile_template::binding_point() const {
    return binding_point_;
}

void profile_template::binding_point(const dogen::variability::entities::binding_point v) {
    binding_point_ = v;
}

const std::list<std::string>& profile_template::parents() const {
    return parents_;
}

std::list<std::string>& profile_template::parents() {
    return parents_;
}

void profile_template::parents(const std::list<std::string>& v) {
    parents_ = v;
}

void profile_template::parents(const std::list<std::string>&& v) {
    parents_ = std::move(v);
}

const std::string& profile_template::stereotype() const {
    return stereotype_;
}

std::string& profile_template::stereotype() {
    return stereotype_;
}

void profile_template::stereotype(const std::string& v) {
    stereotype_ = v;
}

void profile_template::stereotype(const std::string&& v) {
    stereotype_ = std::move(v);
}

const std::list<dogen::variability::entities::configuration_point_template>& profile_template::templates() const {
    return templates_;
}

std::list<dogen::variability::entities::configuration_point_template>& profile_template::templates() {
    return templates_;
}

void profile_template::templates(const std::list<dogen::variability::entities::configuration_point_template>& v) {
    templates_ = v;
}

void profile_template::templates(const std::list<dogen::variability::entities::configuration_point_template>&& v) {
    templates_ = std::move(v);
}

}
