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
#include "dogen/test_models/primitive/io/consumer_io.hpp"
#include "dogen/test_models/primitive/io/int_primitive_io.hpp"
#include "dogen/test_models/primitive/io/bool_primitive_io.hpp"
#include "dogen/test_models/primitive/io/char_primitive_io.hpp"
#include "dogen/test_models/primitive/io/long_primitive_io.hpp"
#include "dogen/test_models/primitive/io/uint_primitive_io.hpp"
#include "dogen/test_models/primitive/io/float_primitive_io.hpp"
#include "dogen/test_models/primitive/io/short_primitive_io.hpp"
#include "dogen/test_models/primitive/io/uchar_primitive_io.hpp"
#include "dogen/test_models/primitive/io/ulong_primitive_io.hpp"
#include "dogen/test_models/primitive/io/double_primitive_io.hpp"
#include "dogen/test_models/primitive/io/ushort_primitive_io.hpp"

namespace dogen {
namespace test_models {
namespace primitive {

std::ostream& operator<<(std::ostream& s, const consumer& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::primitive::consumer\"" << ", "
      << "\"prop0\": " << v.prop0() << ", "
      << "\"prop1\": " << v.prop1() << ", "
      << "\"prop2\": " << v.prop2() << ", "
      << "\"prop3\": " << v.prop3() << ", "
      << "\"prop4\": " << v.prop4() << ", "
      << "\"prop5\": " << v.prop5() << ", "
      << "\"prop6\": " << v.prop6() << ", "
      << "\"prop7\": " << v.prop7() << ", "
      << "\"prop8\": " << v.prop8() << ", "
      << "\"prop9\": " << v.prop9() << ", "
      << "\"prop10\": " << v.prop10()
      << " }";
    return(s);
}

} } }
