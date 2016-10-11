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
#include "dogen/annotations/types/ownership_hierarchy.hpp"

namespace dogen {
namespace annotations {

ownership_hierarchy::ownership_hierarchy(
    const std::string& model_name,
    const std::string& facet_name,
    const std::string& formatter_name)
    : model_name_(model_name),
      facet_name_(facet_name),
      formatter_name_(formatter_name) { }

void ownership_hierarchy::swap(ownership_hierarchy& other) noexcept {
    using std::swap;
    swap(model_name_, other.model_name_);
    swap(facet_name_, other.facet_name_);
    swap(formatter_name_, other.formatter_name_);
}

bool ownership_hierarchy::operator==(const ownership_hierarchy& rhs) const {
    return model_name_ == rhs.model_name_ &&
        facet_name_ == rhs.facet_name_ &&
        formatter_name_ == rhs.formatter_name_;
}

ownership_hierarchy& ownership_hierarchy::operator=(ownership_hierarchy other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& ownership_hierarchy::model_name() const {
    return model_name_;
}

std::string& ownership_hierarchy::model_name() {
    return model_name_;
}

void ownership_hierarchy::model_name(const std::string& v) {
    model_name_ = v;
}

void ownership_hierarchy::model_name(const std::string&& v) {
    model_name_ = std::move(v);
}

const std::string& ownership_hierarchy::facet_name() const {
    return facet_name_;
}

std::string& ownership_hierarchy::facet_name() {
    return facet_name_;
}

void ownership_hierarchy::facet_name(const std::string& v) {
    facet_name_ = v;
}

void ownership_hierarchy::facet_name(const std::string&& v) {
    facet_name_ = std::move(v);
}

const std::string& ownership_hierarchy::formatter_name() const {
    return formatter_name_;
}

std::string& ownership_hierarchy::formatter_name() {
    return formatter_name_;
}

void ownership_hierarchy::formatter_name(const std::string& v) {
    formatter_name_ = v;
}

void ownership_hierarchy::formatter_name(const std::string&& v) {
    formatter_name_ = std::move(v);
}

} }
