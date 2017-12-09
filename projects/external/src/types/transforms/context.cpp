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
#include "dogen/external/types/transforms/context.hpp"

namespace dogen {
namespace external {
namespace transforms {

context::context(const dogen::probing::prober& prober)
    : prober_(prober) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(prober_, other.prober_);
}

bool context::operator==(const context& rhs) const {
    return prober_ == rhs.prober_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::probing::prober& context::prober() const {
    return prober_;
}

dogen::probing::prober& context::prober() {
    return prober_;
}

void context::prober(const dogen::probing::prober& v) {
    prober_ = v;
}

void context::prober(const dogen::probing::prober&& v) {
    prober_ = std::move(v);
}

} } }
