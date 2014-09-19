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
#include "dogen/cpp/types/state.hpp"

namespace dogen {
namespace cpp {

state::state()
    : has_primitive_properties_(static_cast<bool>(0)) { }

state::state(
    const std::list<dogen::cpp::property_info>& personal_properties,
    const std::list<dogen::cpp::property_info>& all_properties,
    const bool has_primitive_properties)
    : personal_properties_(personal_properties),
      all_properties_(all_properties),
      has_primitive_properties_(has_primitive_properties) { }

void state::swap(state& other) noexcept {
    using std::swap;
    swap(personal_properties_, other.personal_properties_);
    swap(all_properties_, other.all_properties_);
    swap(has_primitive_properties_, other.has_primitive_properties_);
}

bool state::operator==(const state& rhs) const {
    return personal_properties_ == rhs.personal_properties_ &&
        all_properties_ == rhs.all_properties_ &&
        has_primitive_properties_ == rhs.has_primitive_properties_;
}

state& state::operator=(state other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::cpp::property_info>& state::personal_properties() const {
    return personal_properties_;
}

std::list<dogen::cpp::property_info>& state::personal_properties() {
    return personal_properties_;
}

void state::personal_properties(const std::list<dogen::cpp::property_info>& v) {
    personal_properties_ = v;
}

void state::personal_properties(const std::list<dogen::cpp::property_info>&& v) {
    personal_properties_ = std::move(v);
}

const std::list<dogen::cpp::property_info>& state::all_properties() const {
    return all_properties_;
}

std::list<dogen::cpp::property_info>& state::all_properties() {
    return all_properties_;
}

void state::all_properties(const std::list<dogen::cpp::property_info>& v) {
    all_properties_ = v;
}

void state::all_properties(const std::list<dogen::cpp::property_info>&& v) {
    all_properties_ = std::move(v);
}

bool state::has_primitive_properties() const {
    return has_primitive_properties_;
}

void state::has_primitive_properties(const bool v) {
    has_primitive_properties_ = v;
}

} }