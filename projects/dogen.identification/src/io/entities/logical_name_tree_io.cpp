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
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.identification/io/entities/logical_name_tree_io.hpp"
#include "dogen.identification/io/entities/qualified_representations_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::logical_name_tree>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::identification::entities {

std::ostream& operator<<(std::ostream& s, const logical_name_tree& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::identification::entities::logical_name_tree\"" << ", "
      << "\"qualified\": " << v.qualified() << ", "
      << "\"current\": " << v.current() << ", "
      << "\"children\": " << v.children() << ", "
      << "\"are_children_opaque\": " << v.are_children_opaque() << ", "
      << "\"is_circular_dependency\": " << v.is_circular_dependency() << ", "
      << "\"is_current_simple_type\": " << v.is_current_simple_type() << ", "
      << "\"is_floating_point\": " << v.is_floating_point()
      << " }";
    return(s);
}

}
