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
#include <boost/algorithm/string.hpp>
#include "masd.dogen.generation.csharp/io/fabric/visual_studio_configuration_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace masd::dogen::generation::csharp::fabric {

std::ostream& operator<<(std::ostream& s, const visual_studio_configuration& v) {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::generation::csharp::fabric::visual_studio_configuration\"" << ", "
      << "\"project_solution_guid\": " << "\"" << tidy_up_string(v.project_solution_guid()) << "\"" << ", "
      << "\"project_guid\": " << "\"" << tidy_up_string(v.project_guid()) << "\""
      << " }";
    return(s);
}

}
