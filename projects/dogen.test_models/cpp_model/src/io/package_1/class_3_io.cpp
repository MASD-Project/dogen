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
#include "dogen/test_models/cpp_model/io/package_1/class_3_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {
namespace package_1 {

std::ostream& operator<<(std::ostream& s, const class_3& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::package_1::class_3\"" << ", "
      << "\"prop_0\": " << v.prop_0()
      << " }";
    return(s);
}

} } } }
