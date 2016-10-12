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
#include "dogen/annotations/types/value_template.hpp"

namespace dogen {
namespace annotations {

value_template::value_template()
    : kind_(static_cast<dogen::annotations::template_kinds>(0)) { }

value_template::value_template(
    const dogen::annotations::name& name,
    const dogen::annotations::ownership_hierarchy& ownership_hierarchy,
    const std::list<std::string>& untyped_value,
    const dogen::annotations::template_kinds kind)
    : name_(name),
      ownership_hierarchy_(ownership_hierarchy),
      untyped_value_(untyped_value),
      kind_(kind) { }

void value_template::swap(value_template& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(ownership_hierarchy_, other.ownership_hierarchy_);
    swap(untyped_value_, other.untyped_value_);
    swap(kind_, other.kind_);
}

bool value_template::operator==(const value_template& rhs) const {
    return name_ == rhs.name_ &&
        ownership_hierarchy_ == rhs.ownership_hierarchy_ &&
        untyped_value_ == rhs.untyped_value_ &&
        kind_ == rhs.kind_;
}

value_template& value_template::operator=(value_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::annotations::name& value_template::name() const {
    return name_;
}

dogen::annotations::name& value_template::name() {
    return name_;
}

void value_template::name(const dogen::annotations::name& v) {
    name_ = v;
}

void value_template::name(const dogen::annotations::name&& v) {
    name_ = std::move(v);
}

const dogen::annotations::ownership_hierarchy& value_template::ownership_hierarchy() const {
    return ownership_hierarchy_;
}

dogen::annotations::ownership_hierarchy& value_template::ownership_hierarchy() {
    return ownership_hierarchy_;
}

void value_template::ownership_hierarchy(const dogen::annotations::ownership_hierarchy& v) {
    ownership_hierarchy_ = v;
}

void value_template::ownership_hierarchy(const dogen::annotations::ownership_hierarchy&& v) {
    ownership_hierarchy_ = std::move(v);
}

const std::list<std::string>& value_template::untyped_value() const {
    return untyped_value_;
}

std::list<std::string>& value_template::untyped_value() {
    return untyped_value_;
}

void value_template::untyped_value(const std::list<std::string>& v) {
    untyped_value_ = v;
}

void value_template::untyped_value(const std::list<std::string>&& v) {
    untyped_value_ = std::move(v);
}

dogen::annotations::template_kinds value_template::kind() const {
    return kind_;
}

void value_template::kind(const dogen::annotations::template_kinds v) {
    kind_ = v;
}

} }
