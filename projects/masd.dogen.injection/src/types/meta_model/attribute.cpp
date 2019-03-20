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
#include "masd.dogen.injection/types/meta_model/attribute.hpp"

namespace masd::dogen::injection::meta_model {

attribute::attribute(
    const std::list<std::pair<std::string, std::string> >& tagged_values,
    const std::list<std::string>& stereotypes,
    const std::string& documentation,
    const std::string& name,
    const masd::dogen::annotations::annotation& annotation,
    const std::string& type,
    const std::string& value)
    : tagged_values_(tagged_values),
      stereotypes_(stereotypes),
      documentation_(documentation),
      name_(name),
      annotation_(annotation),
      type_(type),
      value_(value) { }

void attribute::swap(attribute& other) noexcept {
    using std::swap;
    swap(tagged_values_, other.tagged_values_);
    swap(stereotypes_, other.stereotypes_);
    swap(documentation_, other.documentation_);
    swap(name_, other.name_);
    swap(annotation_, other.annotation_);
    swap(type_, other.type_);
    swap(value_, other.value_);
}

bool attribute::operator==(const attribute& rhs) const {
    return tagged_values_ == rhs.tagged_values_ &&
        stereotypes_ == rhs.stereotypes_ &&
        documentation_ == rhs.documentation_ &&
        name_ == rhs.name_ &&
        annotation_ == rhs.annotation_ &&
        type_ == rhs.type_ &&
        value_ == rhs.value_;
}

attribute& attribute::operator=(attribute other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::pair<std::string, std::string> >& attribute::tagged_values() const {
    return tagged_values_;
}

std::list<std::pair<std::string, std::string> >& attribute::tagged_values() {
    return tagged_values_;
}

void attribute::tagged_values(const std::list<std::pair<std::string, std::string> >& v) {
    tagged_values_ = v;
}

void attribute::tagged_values(const std::list<std::pair<std::string, std::string> >&& v) {
    tagged_values_ = std::move(v);
}

const std::list<std::string>& attribute::stereotypes() const {
    return stereotypes_;
}

std::list<std::string>& attribute::stereotypes() {
    return stereotypes_;
}

void attribute::stereotypes(const std::list<std::string>& v) {
    stereotypes_ = v;
}

void attribute::stereotypes(const std::list<std::string>&& v) {
    stereotypes_ = std::move(v);
}

const std::string& attribute::documentation() const {
    return documentation_;
}

std::string& attribute::documentation() {
    return documentation_;
}

void attribute::documentation(const std::string& v) {
    documentation_ = v;
}

void attribute::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::string& attribute::name() const {
    return name_;
}

std::string& attribute::name() {
    return name_;
}

void attribute::name(const std::string& v) {
    name_ = v;
}

void attribute::name(const std::string&& v) {
    name_ = std::move(v);
}

const masd::dogen::annotations::annotation& attribute::annotation() const {
    return annotation_;
}

masd::dogen::annotations::annotation& attribute::annotation() {
    return annotation_;
}

void attribute::annotation(const masd::dogen::annotations::annotation& v) {
    annotation_ = v;
}

void attribute::annotation(const masd::dogen::annotations::annotation&& v) {
    annotation_ = std::move(v);
}

const std::string& attribute::type() const {
    return type_;
}

std::string& attribute::type() {
    return type_;
}

void attribute::type(const std::string& v) {
    type_ = v;
}

void attribute::type(const std::string&& v) {
    type_ = std::move(v);
}

const std::string& attribute::value() const {
    return value_;
}

std::string& attribute::value() {
    return value_;
}

void attribute::value(const std::string& v) {
    value_ = v;
}

void attribute::value(const std::string&& v) {
    value_ = std::move(v);
}

}
