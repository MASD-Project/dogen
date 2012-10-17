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
#include "dogen/all_primitives/io/a_class_io.hpp"
#include "dogen/all_primitives/io/versioned_key_io.hpp"

namespace dogen {
namespace all_primitives {

std::ostream& operator<<(std::ostream& stream, a_class value) {
    boost::io::ios_flags_saver ifs(stream);
    stream << std::boolalpha;

    stream << " { "
           << "\"__type__\": " << "\"a_class\"" << ", "
           << "\"bool_property\": " << value.bool_property() << ", "
           << "\"char_property\": " << "\"" << value.char_property() << "\"" << ", "
           << "\"uchar_property\": " << "\"" << value.uchar_property() << "\"" << ", "
           << "\"int_property\": " << value.int_property() << ", "
           << "\"uint_property\": " << value.uint_property() << ", "
           << "\"long_property\": " << value.long_property() << ", "
           << "\"ulong_property\": " << value.ulong_property() << ", "
           << "\"long_long_property\": " << value.long_long_property() << ", "
           << "\"ulong_long_property\": " << value.ulong_long_property() << ", "
           << "\"short_property\": " << value.short_property() << ", "
           << "\"ushort_property\": " << value.ushort_property() << ", "
           << "\"versioned_key\": " << value.versioned_key()
           << " }";
    return(stream);
}

} }