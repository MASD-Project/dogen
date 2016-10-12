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
#include "dogen/annotations/types/value.hpp"
#include "dogen/annotations/types/value_template.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::annotations::value>& lhs,
const boost::shared_ptr<dogen::annotations::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace annotations {

value_template::value_template()
    : kind_(static_cast<dogen::annotations::template_kinds>(0)) { }

value_template::value_template(
    const std::string& name,
    const dogen::annotations::ownership_hierarchy& ownership_hierarchy,
    const boost::shared_ptr<dogen::annotations::value>& value,
    const dogen::annotations::template_kinds kind)
    : name_(name),
      ownership_hierarchy_(ownership_hierarchy),
      value_(value),
      kind_(kind) { }

void value_template::swap(value_template& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(ownership_hierarchy_, other.ownership_hierarchy_);
    swap(value_, other.value_);
    swap(kind_, other.kind_);
}

bool value_template::operator==(const value_template& rhs) const {
    return name_ == rhs.name_ &&
        ownership_hierarchy_ == rhs.ownership_hierarchy_ &&
        value_ == rhs.value_ &&
        kind_ == rhs.kind_;
}

value_template& value_template::operator=(value_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& value_template::name() const {
    return name_;
}

std::string& value_template::name() {
    return name_;
}

void value_template::name(const std::string& v) {
    name_ = v;
}

void value_template::name(const std::string&& v) {
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

const boost::shared_ptr<dogen::annotations::value>& value_template::value() const {
    return value_;
}

boost::shared_ptr<dogen::annotations::value>& value_template::value() {
    return value_;
}

void value_template::value(const boost::shared_ptr<dogen::annotations::value>& v) {
    value_ = v;
}

void value_template::value(const boost::shared_ptr<dogen::annotations::value>&& v) {
    value_ = std::move(v);
}

dogen::annotations::template_kinds value_template::kind() const {
    return kind_;
}

void value_template::kind(const dogen::annotations::template_kinds v) {
    kind_ = v;
}

} }
