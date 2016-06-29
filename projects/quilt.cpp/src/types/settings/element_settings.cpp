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
#include "dogen/quilt.cpp/types/settings/element_settings.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

element_settings::element_settings()
    : disable_complete_constructor_(static_cast<bool>(0)),
      disable_xml_serialization_(static_cast<bool>(0)) { }

element_settings::element_settings(
    const bool disable_complete_constructor,
    const bool disable_xml_serialization,
    const std::string& string_conversion_method)
    : disable_complete_constructor_(disable_complete_constructor),
      disable_xml_serialization_(disable_xml_serialization),
      string_conversion_method_(string_conversion_method) { }

void element_settings::swap(element_settings& other) noexcept {
    using std::swap;
    swap(disable_complete_constructor_, other.disable_complete_constructor_);
    swap(disable_xml_serialization_, other.disable_xml_serialization_);
    swap(string_conversion_method_, other.string_conversion_method_);
}

bool element_settings::operator==(const element_settings& rhs) const {
    return disable_complete_constructor_ == rhs.disable_complete_constructor_ &&
        disable_xml_serialization_ == rhs.disable_xml_serialization_ &&
        string_conversion_method_ == rhs.string_conversion_method_;
}

element_settings& element_settings::operator=(element_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool element_settings::disable_complete_constructor() const {
    return disable_complete_constructor_;
}

void element_settings::disable_complete_constructor(const bool v) {
    disable_complete_constructor_ = v;
}

bool element_settings::disable_xml_serialization() const {
    return disable_xml_serialization_;
}

void element_settings::disable_xml_serialization(const bool v) {
    disable_xml_serialization_ = v;
}

const std::string& element_settings::string_conversion_method() const {
    return string_conversion_method_;
}

std::string& element_settings::string_conversion_method() {
    return string_conversion_method_;
}

void element_settings::string_conversion_method(const std::string& v) {
    string_conversion_method_ = v;
}

void element_settings::string_conversion_method(const std::string&& v) {
    string_conversion_method_ = std::move(v);
}

} } } }
