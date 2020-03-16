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
#include "dogen.tracing/io/tracer_io.hpp"
#include "dogen.generation/io/transforms/context_io.hpp"
#include "dogen.variability/io/entities/feature_model_io.hpp"
#include "dogen.physical/io/entities/location_repository_io.hpp"
#include "dogen.generation/io/entities/intra_backend_segment_properties_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::physical::entities::location_repository>& v) {
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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::variability::entities::feature_model>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::tracing::tracer>& v) {
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

namespace dogen::generation::transforms {

std::ostream& operator<<(std::ostream& s, const context& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::generation::transforms::context\"" << ", "
      << "\"archetype_location_repository\": " << v.archetype_location_repository() << ", "
      << "\"intra_backend_segment_properties\": " << v.intra_backend_segment_properties() << ", "
      << "\"output_directory_path\": " << "\"" << v.output_directory_path().generic_string() << "\"" << ", "
      << "\"feature_model\": " << v.feature_model() << ", "
      << "\"tracer\": " << v.tracer() << ", "
      << "\"generation_timestamp\": " << "\"" << tidy_up_string(v.generation_timestamp()) << "\""
      << " }";
    return(s);
}

}
