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
#include "masd.dogen.archetypes/io/location_io.hpp"
#include "masd.dogen.variability/io/meta_model/value_io.hpp"
#include "masd.dogen.variability/types/meta_model/value.hpp"
#include "masd.dogen.variability/io/meta_model/element_io.hpp"
#include "masd.dogen.variability/io/meta_model/value_type_io.hpp"
#include "masd.dogen.variability/io/meta_model/binding_type_io.hpp"
#include "masd.dogen.variability/io/meta_model/template_kind_io.hpp"
#include "masd.dogen.variability/types/meta_model/feature_template.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::variability::meta_model::value>& lhs,
const boost::shared_ptr<masd::dogen::variability::meta_model::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<masd::dogen::variability::meta_model::value>& v) {
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

namespace masd::dogen::variability::meta_model {

feature_template::feature_template()
    : value_type_(static_cast<masd::dogen::variability::meta_model::value_type>(0)),
      binding_type_(static_cast<masd::dogen::variability::meta_model::binding_type>(0)),
      kind_(static_cast<masd::dogen::variability::meta_model::template_kind>(0)) { }

feature_template::feature_template(
    const masd::dogen::variability::meta_model::name& name,
    const std::string& description,
    const masd::dogen::archetypes::location& location,
    const boost::shared_ptr<masd::dogen::variability::meta_model::value>& default_value,
    const masd::dogen::variability::meta_model::value_type value_type,
    const masd::dogen::variability::meta_model::binding_type binding_type,
    const masd::dogen::variability::meta_model::template_kind kind)
    : masd::dogen::variability::meta_model::element(
      name,
      description),
      location_(location),
      default_value_(default_value),
      value_type_(value_type),
      binding_type_(binding_type),
      kind_(kind) { }

void feature_template::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::variability::meta_model::feature_template\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::variability::meta_model::element::to_stream(s);
    s << ", "
      << "\"location\": " << location_ << ", "
      << "\"default_value\": " << default_value_ << ", "
      << "\"value_type\": " << value_type_ << ", "
      << "\"binding_type\": " << binding_type_ << ", "
      << "\"kind\": " << kind_
      << " }";
}

void feature_template::swap(feature_template& other) noexcept {
    masd::dogen::variability::meta_model::element::swap(other);

    using std::swap;
    swap(location_, other.location_);
    swap(default_value_, other.default_value_);
    swap(value_type_, other.value_type_);
    swap(binding_type_, other.binding_type_);
    swap(kind_, other.kind_);
}

bool feature_template::equals(const masd::dogen::variability::meta_model::element& other) const {
    const feature_template* const p(dynamic_cast<const feature_template* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool feature_template::operator==(const feature_template& rhs) const {
    return masd::dogen::variability::meta_model::element::compare(rhs) &&
        location_ == rhs.location_ &&
        default_value_ == rhs.default_value_ &&
        value_type_ == rhs.value_type_ &&
        binding_type_ == rhs.binding_type_ &&
        kind_ == rhs.kind_;
}

feature_template& feature_template::operator=(feature_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::archetypes::location& feature_template::location() const {
    return location_;
}

masd::dogen::archetypes::location& feature_template::location() {
    return location_;
}

void feature_template::location(const masd::dogen::archetypes::location& v) {
    location_ = v;
}

void feature_template::location(const masd::dogen::archetypes::location&& v) {
    location_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::variability::meta_model::value>& feature_template::default_value() const {
    return default_value_;
}

boost::shared_ptr<masd::dogen::variability::meta_model::value>& feature_template::default_value() {
    return default_value_;
}

void feature_template::default_value(const boost::shared_ptr<masd::dogen::variability::meta_model::value>& v) {
    default_value_ = v;
}

void feature_template::default_value(const boost::shared_ptr<masd::dogen::variability::meta_model::value>&& v) {
    default_value_ = std::move(v);
}

masd::dogen::variability::meta_model::value_type feature_template::value_type() const {
    return value_type_;
}

void feature_template::value_type(const masd::dogen::variability::meta_model::value_type v) {
    value_type_ = v;
}

masd::dogen::variability::meta_model::binding_type feature_template::binding_type() const {
    return binding_type_;
}

void feature_template::binding_type(const masd::dogen::variability::meta_model::binding_type v) {
    binding_type_ = v;
}

masd::dogen::variability::meta_model::template_kind feature_template::kind() const {
    return kind_;
}

void feature_template::kind(const masd::dogen::variability::meta_model::template_kind v) {
    kind_ = v;
}

}
