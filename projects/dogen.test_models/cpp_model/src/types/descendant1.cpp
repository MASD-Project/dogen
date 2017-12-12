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
#include "dogen/test_models/cpp_model/io/base_io.hpp"
#include "dogen/test_models/cpp_model/types/descendant1.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

void descendant1::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::descendant1\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::cpp_model::base::to_stream(s);
    s << " }";
}

void descendant1::swap(descendant1& other) noexcept {
    dogen::test_models::cpp_model::base::swap(other);

}

bool descendant1::compare(const descendant1& /*rhs*/) const {
    return true;
}

} } }
