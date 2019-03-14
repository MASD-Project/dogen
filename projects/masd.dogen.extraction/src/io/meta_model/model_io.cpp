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
#include "masd.dogen.annotations/io/annotation_io.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/io/meta_model/artefact_io.hpp"
#include "masd.dogen.extraction/io/meta_model/outputting_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<masd::dogen::extraction::meta_model::artefact>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::filesystem::path>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << (*i).generic_string() << "\"";
    }
    s << "] ";
    return s;
}

}

namespace masd::dogen::extraction::meta_model {

std::ostream& operator<<(std::ostream& s, const model& v) {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::extraction::meta_model::model\"" << ", "
      << "\"annotation\": " << v.annotation() << ", "
      << "\"name\": " << "\"" << tidy_up_string(v.name()) << "\"" << ", "
      << "\"language\": " << "\"" << tidy_up_string(v.language()) << "\"" << ", "
      << "\"artefacts\": " << v.artefacts() << ", "
      << "\"managed_directories\": " << v.managed_directories() << ", "
      << "\"outputting_properties\": " << v.outputting_properties()
      << " }";
    return(s);
}

}
