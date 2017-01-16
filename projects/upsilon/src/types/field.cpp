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
#include "dogen/upsilon/types/field.hpp"

namespace dogen {
namespace upsilon {

field::field(
    const std::string& name,
    const dogen::upsilon::name& type_name,
    const std::string& comment)
    : name_(name),
      type_name_(type_name),
      comment_(comment) { }

void field::swap(field& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(type_name_, other.type_name_);
    swap(comment_, other.comment_);
}

bool field::operator==(const field& rhs) const {
    return name_ == rhs.name_ &&
        type_name_ == rhs.type_name_ &&
        comment_ == rhs.comment_;
}

field& field::operator=(field other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& field::name() const {
    return name_;
}

std::string& field::name() {
    return name_;
}

void field::name(const std::string& v) {
    name_ = v;
}

void field::name(const std::string&& v) {
    name_ = std::move(v);
}

const dogen::upsilon::name& field::type_name() const {
    return type_name_;
}

dogen::upsilon::name& field::type_name() {
    return type_name_;
}

void field::type_name(const dogen::upsilon::name& v) {
    type_name_ = v;
}

void field::type_name(const dogen::upsilon::name&& v) {
    type_name_ = std::move(v);
}

const std::string& field::comment() const {
    return comment_;
}

std::string& field::comment() {
    return comment_;
}

void field::comment(const std::string& v) {
    comment_ = v;
}

void field::comment(const std::string&& v) {
    comment_ = std::move(v);
}

} }
