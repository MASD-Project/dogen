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
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/value.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::variability::value>& lhs,
const boost::shared_ptr<masd::dogen::variability::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace masd::dogen::variability {

type::type()
    : value_type_(static_cast<masd::dogen::variability::value_types>(0)),
      scope_(static_cast<masd::dogen::variability::scope_types>(0)),
      is_partially_matchable_(static_cast<bool>(0)) { }

type::type(
    const masd::dogen::variability::name& name,
    const masd::dogen::variability::value_types value_type,
    const masd::dogen::variability::scope_types scope,
    const masd::dogen::variability::archetype_location& archetype_location,
    const boost::shared_ptr<masd::dogen::variability::value>& default_value,
    const bool is_partially_matchable)
    : name_(name),
      value_type_(value_type),
      scope_(scope),
      archetype_location_(archetype_location),
      default_value_(default_value),
      is_partially_matchable_(is_partially_matchable) { }

void type::swap(type& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(value_type_, other.value_type_);
    swap(scope_, other.scope_);
    swap(archetype_location_, other.archetype_location_);
    swap(default_value_, other.default_value_);
    swap(is_partially_matchable_, other.is_partially_matchable_);
}

bool type::operator==(const type& rhs) const {
    return name_ == rhs.name_ &&
        value_type_ == rhs.value_type_ &&
        scope_ == rhs.scope_ &&
        archetype_location_ == rhs.archetype_location_ &&
        default_value_ == rhs.default_value_ &&
        is_partially_matchable_ == rhs.is_partially_matchable_;
}

type& type::operator=(type other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::variability::name& type::name() const {
    return name_;
}

masd::dogen::variability::name& type::name() {
    return name_;
}

void type::name(const masd::dogen::variability::name& v) {
    name_ = v;
}

void type::name(const masd::dogen::variability::name&& v) {
    name_ = std::move(v);
}

masd::dogen::variability::value_types type::value_type() const {
    return value_type_;
}

void type::value_type(const masd::dogen::variability::value_types v) {
    value_type_ = v;
}

masd::dogen::variability::scope_types type::scope() const {
    return scope_;
}

void type::scope(const masd::dogen::variability::scope_types v) {
    scope_ = v;
}

const masd::dogen::variability::archetype_location& type::archetype_location() const {
    return archetype_location_;
}

masd::dogen::variability::archetype_location& type::archetype_location() {
    return archetype_location_;
}

void type::archetype_location(const masd::dogen::variability::archetype_location& v) {
    archetype_location_ = v;
}

void type::archetype_location(const masd::dogen::variability::archetype_location&& v) {
    archetype_location_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::variability::value>& type::default_value() const {
    return default_value_;
}

boost::shared_ptr<masd::dogen::variability::value>& type::default_value() {
    return default_value_;
}

void type::default_value(const boost::shared_ptr<masd::dogen::variability::value>& v) {
    default_value_ = v;
}

void type::default_value(const boost::shared_ptr<masd::dogen::variability::value>&& v) {
    default_value_ = std::move(v);
}

bool type::is_partially_matchable() const {
    return is_partially_matchable_;
}

void type::is_partially_matchable(const bool v) {
    is_partially_matchable_ = v;
}

}
