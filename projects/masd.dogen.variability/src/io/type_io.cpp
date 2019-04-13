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
#include "masd.dogen.variability/io/name_io.hpp"
#include "masd.dogen.variability/io/type_io.hpp"
#include "masd.dogen.variability/io/value_io.hpp"
#include "masd.dogen.variability/io/scope_types_io.hpp"
#include "masd.dogen.variability/io/value_types_io.hpp"
#include "masd.dogen.archetypes/io/archetype_location_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<masd::dogen::variability::value>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace masd::dogen::variability {

std::ostream& operator<<(std::ostream& s, const type& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"masd::dogen::variability::type\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"value_type\": " << v.value_type() << ", "
      << "\"scope\": " << v.scope() << ", "
      << "\"archetype_location\": " << v.archetype_location() << ", "
      << "\"default_value\": " << v.default_value() << ", "
      << "\"is_partially_matchable\": " << v.is_partially_matchable()
      << " }";
    return(s);
}

}
