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
#include "dogen.codec.dia/types/processed_attribute.hpp"

namespace dogen::codec::dia {

processed_attribute::processed_attribute(
    const std::string& name,
    const std::string& type,
    const dogen::codec::dia::processed_comment& comment,
    const std::string& value)
    : name_(name),
      type_(type),
      comment_(comment),
      value_(value) { }

void processed_attribute::swap(processed_attribute& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(type_, other.type_);
    swap(comment_, other.comment_);
    swap(value_, other.value_);
}

bool processed_attribute::operator==(const processed_attribute& rhs) const {
    return name_ == rhs.name_ &&
        type_ == rhs.type_ &&
        comment_ == rhs.comment_ &&
        value_ == rhs.value_;
}

processed_attribute& processed_attribute::operator=(processed_attribute other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& processed_attribute::name() const {
    return name_;
}

std::string& processed_attribute::name() {
    return name_;
}

void processed_attribute::name(const std::string& v) {
    name_ = v;
}

void processed_attribute::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& processed_attribute::type() const {
    return type_;
}

std::string& processed_attribute::type() {
    return type_;
}

void processed_attribute::type(const std::string& v) {
    type_ = v;
}

void processed_attribute::type(const std::string&& v) {
    type_ = std::move(v);
}

const dogen::codec::dia::processed_comment& processed_attribute::comment() const {
    return comment_;
}

dogen::codec::dia::processed_comment& processed_attribute::comment() {
    return comment_;
}

void processed_attribute::comment(const dogen::codec::dia::processed_comment& v) {
    comment_ = v;
}

void processed_attribute::comment(const dogen::codec::dia::processed_comment&& v) {
    comment_ = std::move(v);
}

const std::string& processed_attribute::value() const {
    return value_;
}

std::string& processed_attribute::value() {
    return value_;
}

void processed_attribute::value(const std::string& v) {
    value_ = v;
}

void processed_attribute::value(const std::string&& v) {
    value_ = std::move(v);
}

}
