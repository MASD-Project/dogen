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
#include "dogen/trivial_inheritance/io/base_io.hpp"
#include "dogen/trivial_inheritance/types/descendant1.hpp"

namespace dogen {
namespace trivial_inheritance {

void descendant1::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::trivial_inheritance::descendant1\"" << ", "
      << "\"__parent_0__\": ";
    base::to_stream(s);
    s << " }";
}

bool descendant1::equals(const dogen::trivial_inheritance::base& other) const {
    const descendant1* const p(dynamic_cast<const descendant1* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool descendant1::operator==(const descendant1& /*rhs*/) const {
    return true;
}

} }