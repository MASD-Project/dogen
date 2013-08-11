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
#include "dogen/cpp/io/decl_specifier_io.hpp"
#include "dogen/cpp/io/function_specifier_types_io.hpp"
#include "dogen/cpp/io/storage_class_types_io.hpp"
#include "dogen/cpp/io/type_specifier_io.hpp"

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const decl_specifier& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::decl_specifier\"" << ", "
      << "\"storage_class_type\": " << v.storage_class_type() << ", "
      << "\"type_specifier\": " << v.type_specifier() << ", "
      << "\"function_specifier\": " << v.function_specifier() << ", "
      << "\"is_friend\": " << v.is_friend() << ", "
      << "\"is_typedef\": " << v.is_typedef()
      << " }";
    return(s);
}

} }