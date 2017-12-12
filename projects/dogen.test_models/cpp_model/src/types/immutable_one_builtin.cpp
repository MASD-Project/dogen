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
#include "dogen/test_models/cpp_model/types/immutable_one_builtin.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

immutable_one_builtin::immutable_one_builtin()
    : prop_0_(static_cast<bool>(0)) { }

immutable_one_builtin::immutable_one_builtin(const bool prop_0)
    : prop_0_(prop_0) { }

bool immutable_one_builtin::operator==(const immutable_one_builtin& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

bool immutable_one_builtin::prop_0() const {
    return prop_0_;
}

} } }
