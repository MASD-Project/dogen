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
#include "dogen/test_models/stereotypes/types/versioned.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {

versioned::versioned()
    : version_(static_cast<unsigned int>(0)) { }

versioned::versioned(const unsigned int version)
    : version_(version) { }

void versioned::swap(versioned& other) noexcept {
    using std::swap;
    swap(version_, other.version_);
}

bool versioned::operator==(const versioned& rhs) const {
    return version_ == rhs.version_;
}

versioned& versioned::operator=(versioned other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

unsigned int versioned::version() const {
    return version_;
}

void versioned::version(const unsigned int v) {
    version_ = v;
}

} } }
