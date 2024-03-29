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
#include "dogen.codec/io/entities/comment_io.hpp"
#include "dogen.codec/io/entities/attribute_io.hpp"
#include "dogen.identification/io/entities/name_io.hpp"
#include "dogen.identification/io/entities/stereotype_io.hpp"
#include "dogen.variability/io/entities/configuration_io.hpp"
#include "dogen.identification/io/entities/tagged_value_io.hpp"
#include "dogen.identification/io/entities/codec_provenance_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::tagged_value>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::stereotype>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
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

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::codec::entities {

std::ostream& operator<<(std::ostream& s, const attribute& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::codec::entities::attribute\"" << ", "
      << "\"tagged_values\": " << v.tagged_values() << ", "
      << "\"stereotypes\": " << v.stereotypes() << ", "
      << "\"templates\": " << v.templates() << ", "
      << "\"configurations\": " << v.configurations() << ", "
      << "\"name\": " << v.name() << ", "
      << "\"configuration\": " << v.configuration() << ", "
      << "\"provenance\": " << v.provenance() << ", "
      << "\"tagged_values_overrides\": " << v.tagged_values_overrides() << ", "
      << "\"comment\": " << v.comment() << ", "
      << "\"type\": " << "\"" << tidy_up_string(v.type()) << "\"" << ", "
      << "\"value\": " << "\"" << tidy_up_string(v.value()) << "\""
      << " }";
    return(s);
}

}
