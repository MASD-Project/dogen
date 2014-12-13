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
#include "dogen/dynamic/types/name.hpp"

namespace dogen {
namespace dynamic {

name::name(
    const std::string& simple_name,
    const std::string& owner,
    const std::string& complete_name)
    : simple_name_(simple_name),
      owner_(owner),
      complete_name_(complete_name) { }

void name::swap(name& other) noexcept {
    using std::swap;
    swap(simple_name_, other.simple_name_);
    swap(owner_, other.owner_);
    swap(complete_name_, other.complete_name_);
}

bool name::operator==(const name& rhs) const {
    return simple_name_ == rhs.simple_name_ &&
        owner_ == rhs.owner_ &&
        complete_name_ == rhs.complete_name_;
}

name& name::operator=(name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& name::simple_name() const {
    return simple_name_;
}

std::string& name::simple_name() {
    return simple_name_;
}

void name::simple_name(const std::string& v) {
    simple_name_ = v;
}

void name::simple_name(const std::string&& v) {
    simple_name_ = std::move(v);
}

const std::string& name::owner() const {
    return owner_;
}

std::string& name::owner() {
    return owner_;
}

void name::owner(const std::string& v) {
    owner_ = v;
}

void name::owner(const std::string&& v) {
    owner_ = std::move(v);
}

const std::string& name::complete_name() const {
    return complete_name_;
}

std::string& name::complete_name() {
    return complete_name_;
}

void name::complete_name(const std::string& v) {
    complete_name_ = v;
}

void name::complete_name(const std::string&& v) {
    complete_name_ = std::move(v);
}

} }