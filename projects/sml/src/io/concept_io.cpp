/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <ostream>
#include <sstream>
#include "dogen/sml/io/concept_io.hpp"
#include "dogen/sml/io/generation_types_io.hpp"
#include "dogen/sml/io/operation_io.hpp"
#include "dogen/sml/io/origin_types_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/qname_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::property>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace boost {
namespace property_tree {

inline std::ostream& operator<<(std::ostream& s, const boost::property_tree::ptree& v) {
    std::ostringstream ss;
    boost::property_tree::write_json(ss, v);

    std::string content(ss.str());
    boost::replace_all(content, "\r\n", "");
    boost::replace_all(content, "\n", "");

    s << content;
    return s;
}

} }

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::operation>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::qname>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace sml {

std::ostream& operator<<(std::ostream& s, const concept& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::concept\"" << ", "
      << "\"all_properties\": " << v.all_properties() << ", "
      << "\"local_properties\": " << v.local_properties() << ", "
      << "\"inherited_properties\": " << v.inherited_properties() << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(v.documentation()) << "\"" << ", "
      << "\"meta_data\": " << v.meta_data() << ", "
      << "\"name\": " << v.name() << ", "
      << "\"generation_type\": " << v.generation_type() << ", "
      << "\"origin_type\": " << v.origin_type() << ", "
      << "\"operations\": " << v.operations() << ", "
      << "\"refines\": " << v.refines()
      << " }";
    return(s);
}

} }