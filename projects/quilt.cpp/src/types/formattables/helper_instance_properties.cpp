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
#include "dogen/quilt.cpp/types/formattables/helper_instance_properties.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

helper_instance_properties::helper_instance_properties(
    const std::string& identifiable_name,
    const std::string& complete_name,
    const std::string& complete_name_identifiable_name)
    : identifiable_name_(identifiable_name),
      complete_name_(complete_name),
      complete_name_identifiable_name_(complete_name_identifiable_name) { }

void helper_instance_properties::swap(helper_instance_properties& other) noexcept {
    using std::swap;
    swap(identifiable_name_, other.identifiable_name_);
    swap(complete_name_, other.complete_name_);
    swap(complete_name_identifiable_name_, other.complete_name_identifiable_name_);
}

bool helper_instance_properties::operator==(const helper_instance_properties& rhs) const {
    return identifiable_name_ == rhs.identifiable_name_ &&
        complete_name_ == rhs.complete_name_ &&
        complete_name_identifiable_name_ == rhs.complete_name_identifiable_name_;
}

helper_instance_properties& helper_instance_properties::operator=(helper_instance_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& helper_instance_properties::identifiable_name() const {
    return identifiable_name_;
}

std::string& helper_instance_properties::identifiable_name() {
    return identifiable_name_;
}

void helper_instance_properties::identifiable_name(const std::string& v) {
    identifiable_name_ = v;
}

void helper_instance_properties::identifiable_name(const std::string&& v) {
    identifiable_name_ = std::move(v);
}

const std::string& helper_instance_properties::complete_name() const {
    return complete_name_;
}

std::string& helper_instance_properties::complete_name() {
    return complete_name_;
}

void helper_instance_properties::complete_name(const std::string& v) {
    complete_name_ = v;
}

void helper_instance_properties::complete_name(const std::string&& v) {
    complete_name_ = std::move(v);
}

const std::string& helper_instance_properties::complete_name_identifiable_name() const {
    return complete_name_identifiable_name_;
}

std::string& helper_instance_properties::complete_name_identifiable_name() {
    return complete_name_identifiable_name_;
}

void helper_instance_properties::complete_name_identifiable_name(const std::string& v) {
    complete_name_identifiable_name_ = v;
}

void helper_instance_properties::complete_name_identifiable_name(const std::string&& v) {
    complete_name_identifiable_name_ = std::move(v);
}

} } } }
