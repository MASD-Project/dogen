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
#include <boost/io/ios_state.hpp>
#include "dogen/test_models/cpp_model/io/builtins_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

std::ostream& operator<<(std::ostream& s, const builtins& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::builtins\"" << ", "
      << "\"bool_property\": " << v.bool_property() << ", "
      << "\"char_property\": " << "\"" << v.char_property() << "\"" << ", "
      << "\"uchar_property\": " << "\"" << v.uchar_property() << "\"" << ", "
      << "\"int_property\": " << v.int_property() << ", "
      << "\"uint_property\": " << v.uint_property() << ", "
      << "\"long_property\": " << v.long_property() << ", "
      << "\"ulong_property\": " << v.ulong_property() << ", "
      << "\"long_long_property\": " << v.long_long_property() << ", "
      << "\"ulong_long_property\": " << v.ulong_long_property() << ", "
      << "\"short_property\": " << v.short_property() << ", "
      << "\"ushort_property\": " << v.ushort_property() << ", "
      << "\"double_property\": " << v.double_property() << ", "
      << "\"float_property\": " << v.float_property()
      << " }";
    return(s);
}

} } }
