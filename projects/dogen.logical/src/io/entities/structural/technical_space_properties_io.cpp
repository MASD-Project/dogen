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
#include "dogen.logical/io/entities/structural/technical_space_properties_io.hpp"

namespace dogen::logical::entities::structural {

std::ostream& operator<<(std::ostream& s, const technical_space_properties& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::structural::technical_space_properties\"" << ", "
      << "\"requires_manual_default_constructor\": " << v.requires_manual_default_constructor() << ", "
      << "\"requires_manual_move_constructor\": " << v.requires_manual_move_constructor() << ", "
      << "\"requires_stream_manipulators\": " << v.requires_stream_manipulators() << ", "
      << "\"is_floating_point\": " << v.is_floating_point() << ", "
      << "\"requires_static_reference_equals\": " << v.requires_static_reference_equals()
      << " }";
    return(s);
}

}
