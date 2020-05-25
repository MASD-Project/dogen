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
#include <boost/algorithm/string.hpp>
#include "dogen/io/tracing_level_io.hpp"
#include "dogen/io/tracing_format_io.hpp"
#include "dogen/io/tracing_backend_io.hpp"
#include "dogen/io/tracing_configuration_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {

std::ostream& operator<<(std::ostream& s, const tracing_configuration& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::tracing_configuration\"" << ", "
      << "\"level\": " << v.level() << ", "
      << "\"format\": " << v.format() << ", "
      << "\"guids_enabled\": " << v.guids_enabled() << ", "
      << "\"logging_impact\": " << "\"" << tidy_up_string(v.logging_impact()) << "\"" << ", "
      << "\"use_short_names\": " << v.use_short_names() << ", "
      << "\"output_directory\": " << "\"" << v.output_directory().generic_string() << "\"" << ", "
      << "\"backend\": " << v.backend() << ", "
      << "\"run_id\": " << "\"" << tidy_up_string(v.run_id()) << "\"" << ", "
      << "\"filter_regexes\": " << v.filter_regexes()
      << " }";
    return(s);
}

}
