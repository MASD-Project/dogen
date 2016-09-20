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
#include "dogen/formatters/types/file_properties.hpp"

namespace dogen {
namespace formatters {

file_properties::file_properties()
    : generate_preamble_(static_cast<bool>(0)) { }

file_properties::file_properties(
    const bool generate_preamble,
    const dogen::formatters::decoration& decoration)
    : generate_preamble_(generate_preamble),
      decoration_(decoration) { }

void file_properties::swap(file_properties& other) noexcept {
    using std::swap;
    swap(generate_preamble_, other.generate_preamble_);
    swap(decoration_, other.decoration_);
}

bool file_properties::operator==(const file_properties& rhs) const {
    return generate_preamble_ == rhs.generate_preamble_ &&
        decoration_ == rhs.decoration_;
}

file_properties& file_properties::operator=(file_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool file_properties::generate_preamble() const {
    return generate_preamble_;
}

void file_properties::generate_preamble(const bool v) {
    generate_preamble_ = v;
}

const dogen::formatters::decoration& file_properties::decoration() const {
    return decoration_;
}

dogen::formatters::decoration& file_properties::decoration() {
    return decoration_;
}

void file_properties::decoration(const dogen::formatters::decoration& v) {
    decoration_ = v;
}

void file_properties::decoration(const dogen::formatters::decoration&& v) {
    decoration_ = std::move(v);
}

} }
