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
#include "dogen.injection/io/entities/element_io.hpp"
#include "dogen.identification/io/entities/name_io.hpp"
#include "dogen.injection/io/entities/attribute_io.hpp"
#include "dogen.variability/io/entities/configuration_io.hpp"
#include "dogen.identification/io/entities/injection_id_io.hpp"
#include "dogen.identification/io/entities/tagged_value_io.hpp"
#include "dogen.identification/io/entities/injection_provenance_io.hpp"

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

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::injection::entities::attribute>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::injection::entities {

std::ostream& operator<<(std::ostream& s, const element& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::injection::entities::element\"" << ", "
      << "\"tagged_values\": " << v.tagged_values() << ", "
      << "\"tagged_values_overrides\": " << v.tagged_values_overrides() << ", "
      << "\"stereotypes\": " << v.stereotypes() << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(v.documentation()) << "\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"configuration\": " << v.configuration() << ", "
      << "\"provenance\": " << v.provenance() << ", "
      << "\"parents\": " << v.parents() << ", "
      << "\"attributes\": " << v.attributes() << ", "
      << "\"fallback_element_type\": " << "\"" << tidy_up_string(v.fallback_element_type()) << "\"" << ", "
      << "\"can_be_primitive_underlier\": " << v.can_be_primitive_underlier() << ", "
      << "\"in_global_module\": " << v.in_global_module() << ", "
      << "\"can_be_enumeration_underlier\": " << v.can_be_enumeration_underlier() << ", "
      << "\"is_default_enumeration_type\": " << v.is_default_enumeration_type() << ", "
      << "\"is_associative_container\": " << v.is_associative_container() << ", "
      << "\"is_floating_point\": " << v.is_floating_point() << ", "
      << "\"containing_element_id\": " << v.containing_element_id()
      << " }";
    return(s);
}

}
