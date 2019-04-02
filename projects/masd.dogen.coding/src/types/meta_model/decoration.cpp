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
#include "masd.dogen.coding/types/meta_model/decoration.hpp"

namespace masd::dogen::coding::meta_model {

decoration::decoration(
    const std::string& preamble,
    const std::string& postamble)
    : preamble_(preamble),
      postamble_(postamble) { }

void decoration::swap(decoration& other) noexcept {
    using std::swap;
    swap(preamble_, other.preamble_);
    swap(postamble_, other.postamble_);
}

bool decoration::operator==(const decoration& rhs) const {
    return preamble_ == rhs.preamble_ &&
        postamble_ == rhs.postamble_;
}

decoration& decoration::operator=(decoration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& decoration::preamble() const {
    return preamble_;
}

std::string& decoration::preamble() {
    return preamble_;
}

void decoration::preamble(const std::string& v) {
    preamble_ = v;
}

void decoration::preamble(const std::string&& v) {
    preamble_ = std::move(v);
}

const std::string& decoration::postamble() const {
    return postamble_;
}

std::string& decoration::postamble() {
    return postamble_;
}

void decoration::postamble(const std::string& v) {
    postamble_ = v;
}

void decoration::postamble(const std::string&& v) {
    postamble_ = std::move(v);
}

}
