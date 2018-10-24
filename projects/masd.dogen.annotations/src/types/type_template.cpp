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
#include "masd.dogen.annotations/types/value.hpp"
#include "masd.dogen.annotations/types/type_template.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::annotations::value>& lhs,
const boost::shared_ptr<masd::dogen::annotations::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace masd::dogen::annotations {

type_template::type_template()
    : value_type_(static_cast<masd::dogen::annotations::value_types>(0)),
      scope_(static_cast<masd::dogen::annotations::scope_types>(0)),
      kind_(static_cast<masd::dogen::annotations::template_kinds>(0)) { }

type_template::type_template(
    const masd::dogen::annotations::name& name,
    const masd::dogen::annotations::value_types value_type,
    const masd::dogen::annotations::scope_types scope,
    const masd::dogen::annotations::archetype_location& archetype_location,
    const boost::shared_ptr<masd::dogen::annotations::value>& default_value,
    const masd::dogen::annotations::template_kinds kind)
    : name_(name),
      value_type_(value_type),
      scope_(scope),
      archetype_location_(archetype_location),
      default_value_(default_value),
      kind_(kind) { }

void type_template::swap(type_template& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(value_type_, other.value_type_);
    swap(scope_, other.scope_);
    swap(archetype_location_, other.archetype_location_);
    swap(default_value_, other.default_value_);
    swap(kind_, other.kind_);
}

bool type_template::operator==(const type_template& rhs) const {
    return name_ == rhs.name_ &&
        value_type_ == rhs.value_type_ &&
        scope_ == rhs.scope_ &&
        archetype_location_ == rhs.archetype_location_ &&
        default_value_ == rhs.default_value_ &&
        kind_ == rhs.kind_;
}

type_template& type_template::operator=(type_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::annotations::name& type_template::name() const {
    return name_;
}

masd::dogen::annotations::name& type_template::name() {
    return name_;
}

void type_template::name(const masd::dogen::annotations::name& v) {
    name_ = v;
}

void type_template::name(const masd::dogen::annotations::name&& v) {
    name_ = std::move(v);
}

masd::dogen::annotations::value_types type_template::value_type() const {
    return value_type_;
}

void type_template::value_type(const masd::dogen::annotations::value_types v) {
    value_type_ = v;
}

masd::dogen::annotations::scope_types type_template::scope() const {
    return scope_;
}

void type_template::scope(const masd::dogen::annotations::scope_types v) {
    scope_ = v;
}

const masd::dogen::annotations::archetype_location& type_template::archetype_location() const {
    return archetype_location_;
}

masd::dogen::annotations::archetype_location& type_template::archetype_location() {
    return archetype_location_;
}

void type_template::archetype_location(const masd::dogen::annotations::archetype_location& v) {
    archetype_location_ = v;
}

void type_template::archetype_location(const masd::dogen::annotations::archetype_location&& v) {
    archetype_location_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::annotations::value>& type_template::default_value() const {
    return default_value_;
}

boost::shared_ptr<masd::dogen::annotations::value>& type_template::default_value() {
    return default_value_;
}

void type_template::default_value(const boost::shared_ptr<masd::dogen::annotations::value>& v) {
    default_value_ = v;
}

void type_template::default_value(const boost::shared_ptr<masd::dogen::annotations::value>&& v) {
    default_value_ = std::move(v);
}

masd::dogen::annotations::template_kinds type_template::kind() const {
    return kind_;
}

void type_template::kind(const masd::dogen::annotations::template_kinds v) {
    kind_ = v;
}

}
