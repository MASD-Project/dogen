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
#include "dogen/dynamic/types/ownership_hierarchy.hpp"

namespace dogen {
namespace dynamic {

ownership_hierarchy::ownership_hierarchy(
    const std::string& model,
    const std::string& facet,
    const std::string& formatter)
    : model_(model),
      facet_(facet),
      formatter_(formatter) { }

void ownership_hierarchy::swap(ownership_hierarchy& other) noexcept {
    using std::swap;
    swap(model_, other.model_);
    swap(facet_, other.facet_);
    swap(formatter_, other.formatter_);
}

bool ownership_hierarchy::operator==(const ownership_hierarchy& rhs) const {
    return model_ == rhs.model_ &&
        facet_ == rhs.facet_ &&
        formatter_ == rhs.formatter_;
}

ownership_hierarchy& ownership_hierarchy::operator=(ownership_hierarchy other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& ownership_hierarchy::model() const {
    return model_;
}

std::string& ownership_hierarchy::model() {
    return model_;
}

void ownership_hierarchy::model(const std::string& v) {
    model_ = v;
}

void ownership_hierarchy::model(const std::string&& v) {
    model_ = std::move(v);
}

const std::string& ownership_hierarchy::facet() const {
    return facet_;
}

std::string& ownership_hierarchy::facet() {
    return facet_;
}

void ownership_hierarchy::facet(const std::string& v) {
    facet_ = v;
}

void ownership_hierarchy::facet(const std::string&& v) {
    facet_ = std::move(v);
}

const std::string& ownership_hierarchy::formatter() const {
    return formatter_;
}

std::string& ownership_hierarchy::formatter() {
    return formatter_;
}

void ownership_hierarchy::formatter(const std::string& v) {
    formatter_ = v;
}

void ownership_hierarchy::formatter(const std::string&& v) {
    formatter_ = std::move(v);
}

} }