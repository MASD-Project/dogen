/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/dynamic/types/field.hpp"
#include "dogen/dynamic/types/value.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::dynamic::value>& lhs,
const boost::shared_ptr<dogen::dynamic::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace dynamic {

field::field(
    const boost::shared_ptr<dogen::dynamic::value>& value,
    const dogen::dynamic::name& name)
    : value_(value),
      name_(name) { }

void field::swap(field& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
    swap(name_, other.name_);
}

bool field::operator==(const field& rhs) const {
    return value_ == rhs.value_ &&
        name_ == rhs.name_;
}

field& field::operator=(field other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::dynamic::value>& field::value() const {
    return value_;
}

boost::shared_ptr<dogen::dynamic::value>& field::value() {
    return value_;
}

void field::value(const boost::shared_ptr<dogen::dynamic::value>& v) {
    value_ = v;
}

void field::value(const boost::shared_ptr<dogen::dynamic::value>&& v) {
    value_ = std::move(v);
}

const dogen::dynamic::name& field::name() const {
    return name_;
}

dogen::dynamic::name& field::name() {
    return name_;
}

void field::name(const dogen::dynamic::name& v) {
    name_ = v;
}

void field::name(const dogen::dynamic::name&& v) {
    name_ = std::move(v);
}

} }