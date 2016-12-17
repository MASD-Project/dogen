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
#include "dogen/quilt.csharp/types/formattables/assistant_properties.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

assistant_properties::assistant_properties()
    : requires_assistance_(static_cast<bool>(0)) { }

assistant_properties::assistant_properties(
    const bool requires_assistance,
    const std::string& assistant_method_postfix)
    : requires_assistance_(requires_assistance),
      assistant_method_postfix_(assistant_method_postfix) { }

void assistant_properties::swap(assistant_properties& other) noexcept {
    using std::swap;
    swap(requires_assistance_, other.requires_assistance_);
    swap(assistant_method_postfix_, other.assistant_method_postfix_);
}

bool assistant_properties::operator==(const assistant_properties& rhs) const {
    return requires_assistance_ == rhs.requires_assistance_ &&
        assistant_method_postfix_ == rhs.assistant_method_postfix_;
}

assistant_properties& assistant_properties::operator=(assistant_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool assistant_properties::requires_assistance() const {
    return requires_assistance_;
}

void assistant_properties::requires_assistance(const bool v) {
    requires_assistance_ = v;
}

const std::string& assistant_properties::assistant_method_postfix() const {
    return assistant_method_postfix_;
}

std::string& assistant_properties::assistant_method_postfix() {
    return assistant_method_postfix_;
}

void assistant_properties::assistant_method_postfix(const std::string& v) {
    assistant_method_postfix_ = v;
}

void assistant_properties::assistant_method_postfix(const std::string&& v) {
    assistant_method_postfix_ = std::move(v);
}

} } } }
