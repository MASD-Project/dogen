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
#include "dogen/test_models/primitive/types/consumer.hpp"

namespace dogen {
namespace test_models {
namespace primitive {

consumer::consumer(const dogen::test_models::primitive::product_id& prop0)
    : prop0_(prop0) { }

void consumer::swap(consumer& other) noexcept {
    using std::swap;
    swap(prop0_, other.prop0_);
}

bool consumer::operator==(const consumer& rhs) const {
    return prop0_ == rhs.prop0_;
}

consumer& consumer::operator=(consumer other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::primitive::product_id& consumer::prop0() const {
    return prop0_;
}

dogen::test_models::primitive::product_id& consumer::prop0() {
    return prop0_;
}

void consumer::prop0(const dogen::test_models::primitive::product_id& v) {
    prop0_ = v;
}

void consumer::prop0(const dogen::test_models::primitive::product_id&& v) {
    prop0_ = std::move(v);
}

} } }
