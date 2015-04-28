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
#include "dogen/cpp/types/settings/type_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

type_settings::type_settings()
    : disable_complete_constructor_(static_cast<bool>(0)) { }

type_settings::type_settings(const bool disable_complete_constructor)
    : disable_complete_constructor_(disable_complete_constructor) { }

void type_settings::swap(type_settings& other) noexcept {
    using std::swap;
    swap(disable_complete_constructor_, other.disable_complete_constructor_);
}

bool type_settings::operator==(const type_settings& rhs) const {
    return disable_complete_constructor_ == rhs.disable_complete_constructor_;
}

type_settings& type_settings::operator=(type_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool type_settings::disable_complete_constructor() const {
    return disable_complete_constructor_;
}

void type_settings::disable_complete_constructor(const bool v) {
    disable_complete_constructor_ = v;
}

} } }