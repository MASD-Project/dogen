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
#include "masd.dogen.generation.cpp/types/formattables/odb_properties.hpp"

namespace masd::dogen::generation::cpp::formattables {

odb_properties::odb_properties()
    : is_value_(static_cast<bool>(0)) { }

odb_properties::odb_properties(
    const bool is_value,
    const std::list<std::string>& top_level_odb_pragmas,
    const std::unordered_map<std::string, std::list<std::string> >& attribute_level_odb_pragmas)
    : is_value_(is_value),
      top_level_odb_pragmas_(top_level_odb_pragmas),
      attribute_level_odb_pragmas_(attribute_level_odb_pragmas) { }

void odb_properties::swap(odb_properties& other) noexcept {
    using std::swap;
    swap(is_value_, other.is_value_);
    swap(top_level_odb_pragmas_, other.top_level_odb_pragmas_);
    swap(attribute_level_odb_pragmas_, other.attribute_level_odb_pragmas_);
}

bool odb_properties::operator==(const odb_properties& rhs) const {
    return is_value_ == rhs.is_value_ &&
        top_level_odb_pragmas_ == rhs.top_level_odb_pragmas_ &&
        attribute_level_odb_pragmas_ == rhs.attribute_level_odb_pragmas_;
}

odb_properties& odb_properties::operator=(odb_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool odb_properties::is_value() const {
    return is_value_;
}

void odb_properties::is_value(const bool v) {
    is_value_ = v;
}

const std::list<std::string>& odb_properties::top_level_odb_pragmas() const {
    return top_level_odb_pragmas_;
}

std::list<std::string>& odb_properties::top_level_odb_pragmas() {
    return top_level_odb_pragmas_;
}

void odb_properties::top_level_odb_pragmas(const std::list<std::string>& v) {
    top_level_odb_pragmas_ = v;
}

void odb_properties::top_level_odb_pragmas(const std::list<std::string>&& v) {
    top_level_odb_pragmas_ = std::move(v);
}

const std::unordered_map<std::string, std::list<std::string> >& odb_properties::attribute_level_odb_pragmas() const {
    return attribute_level_odb_pragmas_;
}

std::unordered_map<std::string, std::list<std::string> >& odb_properties::attribute_level_odb_pragmas() {
    return attribute_level_odb_pragmas_;
}

void odb_properties::attribute_level_odb_pragmas(const std::unordered_map<std::string, std::list<std::string> >& v) {
    attribute_level_odb_pragmas_ = v;
}

void odb_properties::attribute_level_odb_pragmas(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    attribute_level_odb_pragmas_ = std::move(v);
}

}
