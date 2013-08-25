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
#include <ostream>
#include "dogen/om/io/cmake_feature_io.hpp"
#include "dogen/om/types/cmake_add_library.hpp"

namespace dogen {
namespace om {

void cmake_add_library::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::cmake_add_library\"" << ", "
      << "\"__parent_0__\": ";
    cmake_feature::to_stream(s);
    s << " }";
}

bool cmake_add_library::equals(const dogen::om::cmake_feature& other) const {
    const cmake_add_library* const p(dynamic_cast<const cmake_add_library* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cmake_add_library::operator==(const cmake_add_library& /*rhs*/) const {
    return true;
}

} }