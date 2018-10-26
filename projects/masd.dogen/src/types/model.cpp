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
#include "masd.dogen/types/model.hpp"

namespace masd::dogen {

model::model(
    const std::string& name,
    const std::string& type,
    const std::string& content)
    : name_(name),
      type_(type),
      content_(content) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(type_, other.type_);
    swap(content_, other.content_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        type_ == rhs.type_ &&
        content_ == rhs.content_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& model::name() const {
    return name_;
}

std::string& model::name() {
    return name_;
}

void model::name(const std::string& v) {
    name_ = v;
}

void model::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& model::type() const {
    return type_;
}

std::string& model::type() {
    return type_;
}

void model::type(const std::string& v) {
    type_ = v;
}

void model::type(const std::string&& v) {
    type_ = std::move(v);
}

const std::string& model::content() const {
    return content_;
}

std::string& model::content() {
    return content_;
}

void model::content(const std::string& v) {
    content_ = v;
}

void model::content(const std::string&& v) {
    content_ = std::move(v);
}

}
