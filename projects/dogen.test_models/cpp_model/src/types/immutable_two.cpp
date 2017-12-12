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
#include "dogen/test_models/cpp_model/types/immutable_two.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

immutable_two::immutable_two()
    : prop_0_(static_cast<bool>(0)) { }

immutable_two::immutable_two(
    const bool prop_0,
    const std::string& prop_1)
    : prop_0_(prop_0),
      prop_1_(prop_1) { }

bool immutable_two::operator==(const immutable_two& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_;
}

bool immutable_two::prop_0() const {
    return prop_0_;
}

const std::string& immutable_two::prop_1() const {
    return prop_1_;
}

} } }
