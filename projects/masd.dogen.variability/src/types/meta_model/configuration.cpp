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
#include "masd.dogen.variability/io/meta_model/element_io.hpp"
#include "masd.dogen.variability/io/meta_model/binding_type_io.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/io/meta_model/configuration_point_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>& v) {
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

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<masd::dogen::variability::meta_model::binding_type>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace masd::dogen::variability::meta_model {

configuration::configuration(configuration&& rhs)
    : masd::dogen::variability::meta_model::element(
        std::forward<masd::dogen::variability::meta_model::element>(rhs)),
      configuration_points_(std::move(rhs.configuration_points_)),
      binding_type_(std::move(rhs.binding_type_)) { }

configuration::configuration(
    const masd::dogen::variability::meta_model::name& name,
    const std::string& description,
    const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>& configuration_points,
    const boost::optional<masd::dogen::variability::meta_model::binding_type>& binding_type)
    : masd::dogen::variability::meta_model::element(
      name,
      description),
      configuration_points_(configuration_points),
      binding_type_(binding_type) { }

void configuration::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::variability::meta_model::configuration\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::variability::meta_model::element::to_stream(s);
    s << ", "
      << "\"configuration_points\": " << configuration_points_ << ", "
      << "\"binding_type\": " << binding_type_
      << " }";
}

void configuration::swap(configuration& other) noexcept {
    masd::dogen::variability::meta_model::element::swap(other);

    using std::swap;
    swap(configuration_points_, other.configuration_points_);
    swap(binding_type_, other.binding_type_);
}

bool configuration::equals(const masd::dogen::variability::meta_model::element& other) const {
    const configuration* const p(dynamic_cast<const configuration* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool configuration::operator==(const configuration& rhs) const {
    return masd::dogen::variability::meta_model::element::compare(rhs) &&
        configuration_points_ == rhs.configuration_points_ &&
        binding_type_ == rhs.binding_type_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>& configuration::configuration_points() const {
    return configuration_points_;
}

std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>& configuration::configuration_points() {
    return configuration_points_;
}

void configuration::configuration_points(const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>& v) {
    configuration_points_ = v;
}

void configuration::configuration_points(const std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point>&& v) {
    configuration_points_ = std::move(v);
}

const boost::optional<masd::dogen::variability::meta_model::binding_type>& configuration::binding_type() const {
    return binding_type_;
}

boost::optional<masd::dogen::variability::meta_model::binding_type>& configuration::binding_type() {
    return binding_type_;
}

void configuration::binding_type(const boost::optional<masd::dogen::variability::meta_model::binding_type>& v) {
    binding_type_ = v;
}

void configuration::binding_type(const boost::optional<masd::dogen::variability::meta_model::binding_type>&& v) {
    binding_type_ = std::move(v);
}

}
