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
#include "dogen/yarn/types/meta_model/enumerator.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

enumerator::enumerator(
    const std::string& documentation,
    const dogen::yarn::meta_model::name& name,
    const dogen::annotations::annotation& annotation,
    const std::string& value)
    : documentation_(documentation),
      name_(name),
      annotation_(annotation),
      value_(value) { }

void enumerator::swap(enumerator& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(name_, other.name_);
    swap(annotation_, other.annotation_);
    swap(value_, other.value_);
}

bool enumerator::operator==(const enumerator& rhs) const {
    return documentation_ == rhs.documentation_ &&
        name_ == rhs.name_ &&
        annotation_ == rhs.annotation_ &&
        value_ == rhs.value_;
}

enumerator& enumerator::operator=(enumerator other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& enumerator::documentation() const {
    return documentation_;
}

std::string& enumerator::documentation() {
    return documentation_;
}

void enumerator::documentation(const std::string& v) {
    documentation_ = v;
}

void enumerator::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const dogen::yarn::meta_model::name& enumerator::name() const {
    return name_;
}

dogen::yarn::meta_model::name& enumerator::name() {
    return name_;
}

void enumerator::name(const dogen::yarn::meta_model::name& v) {
    name_ = v;
}

void enumerator::name(const dogen::yarn::meta_model::name&& v) {
    name_ = std::move(v);
}

const dogen::annotations::annotation& enumerator::annotation() const {
    return annotation_;
}

dogen::annotations::annotation& enumerator::annotation() {
    return annotation_;
}

void enumerator::annotation(const dogen::annotations::annotation& v) {
    annotation_ = v;
}

void enumerator::annotation(const dogen::annotations::annotation&& v) {
    annotation_ = std::move(v);
}

const std::string& enumerator::value() const {
    return value_;
}

std::string& enumerator::value() {
    return value_;
}

void enumerator::value(const std::string& v) {
    value_ = v;
}

void enumerator::value(const std::string&& v) {
    value_ = std::move(v);
}

} } }
