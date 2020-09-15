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
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.physical/io/entities/operation_io.hpp"
#include "dogen.variability/io/entities/configuration_io.hpp"
#include "dogen.physical/io/entities/formatting_styles_io.hpp"
#include "dogen.identification/io/entities/physical_name_io.hpp"
#include "dogen.physical/io/entities/enablement_properties_io.hpp"
#include "dogen.identification/io/entities/logical_provenance_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"

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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, boost::filesystem::path>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << "\"" << i->second.generic_string() << "\"";
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

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

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const artefact& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::physical::entities::artefact\"" << ", "
      << "\"meta_name\": " << v.meta_name() << ", "
      << "\"configuration\": " << v.configuration() << ", "
      << "\"provenance\": " << v.provenance() << ", "
      << "\"name\": " << v.name() << ", "
      << "\"enabled\": " << v.enabled() << ", "
      << "\"overwrite\": " << v.overwrite() << ", "
      << "\"file_path\": " << "\"" << v.file_path().generic_string() << "\"" << ", "
      << "\"file_path_new\": " << "\"" << v.file_path_new().generic_string() << "\"" << ", "
      << "\"content\": " << "\"" << tidy_up_string(v.content()) << "\"" << ", "
      << "\"relative_paths\": " << v.relative_paths() << ", "
      << "\"dependencies\": " << v.dependencies() << ", "
      << "\"relations\": " << v.relations() << ", "
      << "\"unified_diff\": " << "\"" << tidy_up_string(v.unified_diff()) << "\"" << ", "
      << "\"operation\": " << v.operation() << ", "
      << "\"enablement_properties\": " << v.enablement_properties() << ", "
      << "\"formatting_style\": " << v.formatting_style() << ", "
      << "\"formatting_input\": " << "\"" << tidy_up_string(v.formatting_input()) << "\""
      << " }";
    return(s);
}

}
