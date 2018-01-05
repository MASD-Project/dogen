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
#include <ostream>
#include "dogen.modeling/io/meta_model/opaque_properties_io.hpp"
#include "dogen.modeling/types/meta_model/fake_opaque_properties.hpp"

namespace dogen {
namespace modeling {
namespace meta_model {

void fake_opaque_properties::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::modeling::meta_model::fake_opaque_properties\"" << ", "
      << "\"__parent_0__\": ";
    dogen::modeling::meta_model::opaque_properties::to_stream(s);
    s << " }";
}

bool fake_opaque_properties::equals(const dogen::modeling::meta_model::opaque_properties& other) const {
    const fake_opaque_properties* const p(dynamic_cast<const fake_opaque_properties* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool fake_opaque_properties::operator==(const fake_opaque_properties& /*rhs*/) const {
    return true;
}

} } }
