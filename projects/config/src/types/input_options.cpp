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
#include "dogen/config/types/input_options.hpp"

namespace dogen {
namespace config {

input_options::input_options(
    const dogen::config::input& target,
    const std::list<dogen::config::input>& references)
    : target_(target),
      references_(references) { }

void input_options::swap(input_options& other) noexcept {
    using std::swap;
    swap(target_, other.target_);
    swap(references_, other.references_);
}

bool input_options::operator==(const input_options& rhs) const {
    return target_ == rhs.target_ &&
        references_ == rhs.references_;
}

input_options& input_options::operator=(input_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::config::input& input_options::target() const {
    return target_;
}

dogen::config::input& input_options::target() {
    return target_;
}

void input_options::target(const dogen::config::input& v) {
    target_ = v;
}

void input_options::target(const dogen::config::input&& v) {
    target_ = std::move(v);
}

const std::list<dogen::config::input>& input_options::references() const {
    return references_;
}

std::list<dogen::config::input>& input_options::references() {
    return references_;
}

void input_options::references(const std::list<dogen::config::input>& v) {
    references_ = v;
}

void input_options::references(const std::list<dogen::config::input>&& v) {
    references_ = std::move(v);
}

} }
