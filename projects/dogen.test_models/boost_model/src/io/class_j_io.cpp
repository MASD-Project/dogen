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
#include "dogen/test_models/boost_model/io/class_j_io.hpp"
#include "dogen/test_models/boost_model/io/date_primitive_io.hpp"
#include "dogen/test_models/boost_model/io/ptime_primitive_io.hpp"
#include "dogen/test_models/boost_model/io/time_duration_primitive_io.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

std::ostream& operator<<(std::ostream& s, const class_j& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::boost_model::class_j\"" << ", "
      << "\"prop_0\": " << v.prop_0() << ", "
      << "\"prop_1\": " << v.prop_1() << ", "
      << "\"prop_2\": " << v.prop_2()
      << " }";
    return(s);
}

} } }
