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
#include "dogen/quilt.cpp/types/settings/helper_settings.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

helper_settings::helper_settings(const std::string& family)
    : family_(family) { }

void helper_settings::swap(helper_settings& other) noexcept {
    using std::swap;
    swap(family_, other.family_);
}

bool helper_settings::operator==(const helper_settings& rhs) const {
    return family_ == rhs.family_;
}

helper_settings& helper_settings::operator=(helper_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& helper_settings::family() const {
    return family_;
}

std::string& helper_settings::family() {
    return family_;
}

void helper_settings::family(const std::string& v) {
    family_ = v;
}

void helper_settings::family(const std::string&& v) {
    family_ = std::move(v);
}

} } } }
