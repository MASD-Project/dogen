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
#include "dogen.org/types/entities/block.hpp"

namespace dogen::org::entities {

block::block()
    : type_(static_cast<dogen::org::entities::block_type>(0)) { }

block::block(
    const std::string& name,
    const std::list<dogen::org::entities::parameter>& parameters,
    const std::string& contents,
    const dogen::org::entities::block_type type)
    : name_(name),
      parameters_(parameters),
      contents_(contents),
      type_(type) { }

void block::swap(block& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(parameters_, other.parameters_);
    swap(contents_, other.contents_);
    swap(type_, other.type_);
}

bool block::operator==(const block& rhs) const {
    return name_ == rhs.name_ &&
        parameters_ == rhs.parameters_ &&
        contents_ == rhs.contents_ &&
        type_ == rhs.type_;
}

block& block::operator=(block other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& block::name() const {
    return name_;
}

std::string& block::name() {
    return name_;
}

void block::name(const std::string& v) {
    name_ = v;
}

void block::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<dogen::org::entities::parameter>& block::parameters() const {
    return parameters_;
}

std::list<dogen::org::entities::parameter>& block::parameters() {
    return parameters_;
}

void block::parameters(const std::list<dogen::org::entities::parameter>& v) {
    parameters_ = v;
}

void block::parameters(const std::list<dogen::org::entities::parameter>&& v) {
    parameters_ = std::move(v);
}

const std::string& block::contents() const {
    return contents_;
}

std::string& block::contents() {
    return contents_;
}

void block::contents(const std::string& v) {
    contents_ = v;
}

void block::contents(const std::string&& v) {
    contents_ = std::move(v);
}

dogen::org::entities::block_type block::type() const {
    return type_;
}

void block::type(const dogen::org::entities::block_type v) {
    type_ = v;
}

}
