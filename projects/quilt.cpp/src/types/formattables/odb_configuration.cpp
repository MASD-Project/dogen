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
#include "dogen/quilt.cpp/types/formattables/odb_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

odb_configuration::odb_configuration(
    const std::list<std::string>& top_level_odb_pragmas,
    const std::unordered_map<std::string, std::list<std::string> >& attribute_level_odb_pragmas)
    : top_level_odb_pragmas_(top_level_odb_pragmas),
      attribute_level_odb_pragmas_(attribute_level_odb_pragmas) { }

void odb_configuration::swap(odb_configuration& other) noexcept {
    using std::swap;
    swap(top_level_odb_pragmas_, other.top_level_odb_pragmas_);
    swap(attribute_level_odb_pragmas_, other.attribute_level_odb_pragmas_);
}

bool odb_configuration::operator==(const odb_configuration& rhs) const {
    return top_level_odb_pragmas_ == rhs.top_level_odb_pragmas_ &&
        attribute_level_odb_pragmas_ == rhs.attribute_level_odb_pragmas_;
}

odb_configuration& odb_configuration::operator=(odb_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& odb_configuration::top_level_odb_pragmas() const {
    return top_level_odb_pragmas_;
}

std::list<std::string>& odb_configuration::top_level_odb_pragmas() {
    return top_level_odb_pragmas_;
}

void odb_configuration::top_level_odb_pragmas(const std::list<std::string>& v) {
    top_level_odb_pragmas_ = v;
}

void odb_configuration::top_level_odb_pragmas(const std::list<std::string>&& v) {
    top_level_odb_pragmas_ = std::move(v);
}

const std::unordered_map<std::string, std::list<std::string> >& odb_configuration::attribute_level_odb_pragmas() const {
    return attribute_level_odb_pragmas_;
}

std::unordered_map<std::string, std::list<std::string> >& odb_configuration::attribute_level_odb_pragmas() {
    return attribute_level_odb_pragmas_;
}

void odb_configuration::attribute_level_odb_pragmas(const std::unordered_map<std::string, std::list<std::string> >& v) {
    attribute_level_odb_pragmas_ = v;
}

void odb_configuration::attribute_level_odb_pragmas(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    attribute_level_odb_pragmas_ = std::move(v);
}

} } } }
