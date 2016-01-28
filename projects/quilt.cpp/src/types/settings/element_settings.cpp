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
    const std::string& helper_family)
    : disable_complete_constructor_(disable_complete_constructor),
      disable_xml_serialization_(disable_xml_serialization),
      helper_family_(helper_family) { }

void element_settings::swap(element_settings& other) noexcept {
    using std::swap;
    swap(disable_complete_constructor_, other.disable_complete_constructor_);
    swap(disable_xml_serialization_, other.disable_xml_serialization_);
    swap(helper_family_, other.helper_family_);
}

bool element_settings::operator==(const element_settings& rhs) const {
    return disable_complete_constructor_ == rhs.disable_complete_constructor_ &&
        disable_xml_serialization_ == rhs.disable_xml_serialization_ &&
        helper_family_ == rhs.helper_family_;
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

const std::string& element_settings::helper_family() const {
    return helper_family_;
}

std::string& element_settings::helper_family() {
    return helper_family_;
}

void element_settings::helper_family(const std::string& v) {
    helper_family_ = v;
}

void element_settings::helper_family(const std::string&& v) {
    helper_family_ = std::move(v);
}

} } } }
