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
#include "dogen/upsilon/types/representation.hpp"

namespace dogen {
namespace upsilon {

representation::representation()
    : target_(static_cast<dogen::upsilon::target_types>(0)),
      pof_(static_cast<bool>(0)) { }

representation::representation(
    const dogen::upsilon::target_types target,
    const bool pof)
    : target_(target),
      pof_(pof) { }

void representation::swap(representation& other) noexcept {
    using std::swap;
    swap(target_, other.target_);
    swap(pof_, other.pof_);
}

bool representation::operator==(const representation& rhs) const {
    return target_ == rhs.target_ &&
        pof_ == rhs.pof_;
}

representation& representation::operator=(representation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::upsilon::target_types representation::target() const {
    return target_;
}

void representation::target(const dogen::upsilon::target_types v) {
    target_ = v;
}

bool representation::pof() const {
    return pof_;
}

void representation::pof(const bool v) {
    pof_ = v;
}

} }
