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
#include "masd.dogen/io/tracing_configuration_io.hpp"
#include "masd.dogen.coding/io/transforms/options_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<masd::dogen::tracing_configuration>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace masd::dogen::coding::transforms {

std::ostream& operator<<(std::ostream& s, const options& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"masd::dogen::coding::transforms::options\"" << ", "
      << "\"target\": " << "\"" << v.target().generic_string() << "\"" << ", "
      << "\"output_directory_path\": " << "\"" << v.output_directory_path().generic_string() << "\"" << ", "
      << "\"compatibility_mode\": " << v.compatibility_mode() << ", "
      << "\"probe_directory\": " << "\"" << v.probe_directory().generic_string() << "\"" << ", "
      << "\"tracing\": " << v.tracing()
      << " }";
    return(s);
}

}
