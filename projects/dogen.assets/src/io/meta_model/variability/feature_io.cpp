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
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/io/meta_model/name_tree_io.hpp"
#include "dogen.variability/io/meta_model/value_type_io.hpp"
#include "dogen.variability/io/meta_model/binding_point_io.hpp"
#include "dogen.variability/io/meta_model/configuration_io.hpp"
#include "dogen.assets/io/meta_model/variability/feature_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::variability::meta_model::configuration>& v) {
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

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::variability::meta_model::binding_point>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::assets::meta_model::variability {

std::ostream& operator<<(std::ostream& s, const feature& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::variability::feature\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(v.documentation()) << "\"" << ", "
      << "\"configuration\": " << v.configuration() << ", "
      << "\"name\": " << v.name() << ", "
      << "\"key\": " << "\"" << tidy_up_string(v.key()) << "\"" << ", "
      << "\"identifiable_key\": " << "\"" << tidy_up_string(v.identifiable_key()) << "\"" << ", "
      << "\"unparsed_type\": " << "\"" << tidy_up_string(v.unparsed_type()) << "\"" << ", "
      << "\"mapped_type\": " << "\"" << tidy_up_string(v.mapped_type()) << "\"" << ", "
      << "\"parsed_type\": " << v.parsed_type() << ", "
      << "\"value\": " << "\"" << tidy_up_string(v.value()) << "\"" << ", "
      << "\"value_type\": " << v.value_type() << ", "
      << "\"binding_point\": " << v.binding_point() << ", "
      << "\"is_optional\": " << v.is_optional() << ", "
      << "\"requires_optionality\": " << v.requires_optionality()
      << " }";
    return(s);
}

}
