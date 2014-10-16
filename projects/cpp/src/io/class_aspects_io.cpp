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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/cpp/io/class_aspects_io.hpp"

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const class_aspects& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::class_aspects\"" << ", "
      << "\"enable_complete_constructor\": " << v.enable_complete_constructor() << ", "
      << "\"generate_defaulted_functions\": " << v.generate_defaulted_functions() << ", "
      << "\"generate_explicit_default_constructor\": " << v.generate_explicit_default_constructor() << ", "
      << "\"generate_explicit_move_constructor\": " << v.generate_explicit_move_constructor() << ", "
      << "\"generate_explicit_destructor\": " << v.generate_explicit_destructor() << ", "
      << "\"destructor_is_pure_virtual\": " << v.destructor_is_pure_virtual() << ", "
      << "\"generate_explicit_assignment_operator\": " << v.generate_explicit_assignment_operator() << ", "
      << "\"generate_complete_constructor\": " << v.generate_complete_constructor() << ", "
      << "\"generate_equality\": " << v.generate_equality()
      << " }";
    return(s);
}

} }