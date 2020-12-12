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
#include "dogen.dia/types/entities/attribute.hpp"
#include "dogen.dia/types/entities/composite.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::dia::entities::attribute>& lhs,
const boost::shared_ptr<dogen::dia::entities::attribute>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::dia::entities::composite>& lhs,
const boost::shared_ptr<dogen::dia::entities::composite>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::dia::entities {

composite::composite(
    const std::string& type,
    const std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >& value,
    const boost::shared_ptr<dogen::dia::entities::composite>& inner_composite)
    : type_(type),
      value_(value),
      inner_composite_(inner_composite) { }

void composite::swap(composite& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(value_, other.value_);
    swap(inner_composite_, other.inner_composite_);
}

bool composite::operator==(const composite& rhs) const {
    return type_ == rhs.type_ &&
        value_ == rhs.value_ &&
        inner_composite_ == rhs.inner_composite_;
}

composite& composite::operator=(composite other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& composite::type() const {
    return type_;
}

std::string& composite::type() {
    return type_;
}

void composite::type(const std::string& v) {
    type_ = v;
}

void composite::type(const std::string&& v) {
    type_ = std::move(v);
}

const std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >& composite::value() const {
    return value_;
}

std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >& composite::value() {
    return value_;
}

void composite::value(const std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >& v) {
    value_ = v;
}

void composite::value(const std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >&& v) {
    value_ = std::move(v);
}

const boost::shared_ptr<dogen::dia::entities::composite>& composite::inner_composite() const {
    return inner_composite_;
}

boost::shared_ptr<dogen::dia::entities::composite>& composite::inner_composite() {
    return inner_composite_;
}

void composite::inner_composite(const boost::shared_ptr<dogen::dia::entities::composite>& v) {
    inner_composite_ = v;
}

void composite::inner_composite(const boost::shared_ptr<dogen::dia::entities::composite>&& v) {
    inner_composite_ = std::move(v);
}

}
