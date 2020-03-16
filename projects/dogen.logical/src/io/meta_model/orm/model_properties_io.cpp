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
#include "dogen.logical/io/meta_model/orm/letter_case_io.hpp"
#include "dogen.logical/io/meta_model/orm/database_system_io.hpp"
#include "dogen.logical/io/meta_model/orm/model_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::logical::meta_model::orm::letter_case>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<dogen::logical::meta_model::orm::database_system>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::meta_model::orm {

std::ostream& operator<<(std::ostream& s, const model_properties& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::meta_model::orm::model_properties\"" << ", "
      << "\"schema_name\": " << "\"" << tidy_up_string(v.schema_name()) << "\"" << ", "
      << "\"capitalised_schema_name\": " << "\"" << tidy_up_string(v.capitalised_schema_name()) << "\"" << ", "
      << "\"letter_case\": " << v.letter_case() << ", "
      << "\"database_systems\": " << v.database_systems()
      << " }";
    return(s);
}

}
