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
#include "dogen/om/types/preamble_scheme.hpp"

namespace dogen {
namespace om {

preamble_scheme::preamble_scheme(const std::unordered_map<std::string, dogen::om::preamble>& preambles)
    : preambles_(preambles) { }

void preamble_scheme::swap(preamble_scheme& other) noexcept {
    using std::swap;
    swap(preambles_, other.preambles_);
}

bool preamble_scheme::operator==(const preamble_scheme& rhs) const {
    return preambles_ == rhs.preambles_;
}

preamble_scheme& preamble_scheme::operator=(preamble_scheme other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::om::preamble>& preamble_scheme::preambles() const {
    return preambles_;
}

std::unordered_map<std::string, dogen::om::preamble>& preamble_scheme::preambles() {
    return preambles_;
}

void preamble_scheme::preambles(const std::unordered_map<std::string, dogen::om::preamble>& v) {
    preambles_ = v;
}

void preamble_scheme::preambles(const std::unordered_map<std::string, dogen::om::preamble>&& v) {
    preambles_ = std::move(v);
}

} }