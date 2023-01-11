/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.cli/io/generation_configuration_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<boost::filesystem::path>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << (*i).generic_string() << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen::cli {

std::ostream& operator<<(std::ostream& s, const generation_configuration& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cli::generation_configuration\"" << ", "
      << "\"reference_model_directories\": " << v.reference_model_directories() << ", "
      << "\"target\": " << "\"" << v.target().generic_string() << "\"" << ", "
      << "\"output_directory\": " << "\"" << v.output_directory().generic_string() << "\""
      << " }";
    return(s);
}

}
