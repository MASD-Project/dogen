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
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/io/entities/region_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.variability/io/entities/configuration_io.hpp"
#include "dogen.identification/io/entities/physical_name_io.hpp"
#include "dogen.physical/io/entities/meta_model_properties_io.hpp"
#include "dogen.physical/io/entities/outputting_properties_io.hpp"
#include "dogen.identification/io/entities/logical_provenance_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"
#include "dogen.identification/io/entities/logical_meta_physical_id_io.hpp"

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

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::physical::entities::artefact>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::shared_ptr<dogen::physical::entities::artefact> >& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::region>& v) {
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

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const model& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::physical::entities::model\"" << ", "
      << "\"meta_name\": " << v.meta_name() << ", "
      << "\"configuration\": " << v.configuration() << ", "
      << "\"provenance\": " << v.provenance() << ", "
      << "\"name\": " << v.name() << ", "
      << "\"id\": " << v.id() << ", "
      << "\"technical_space\": " << "\"" << tidy_up_string(v.technical_space()) << "\"" << ", "
      << "\"managed_directories\": " << v.managed_directories() << ", "
      << "\"outputting_properties\": " << v.outputting_properties() << ", "
      << "\"orphan_artefacts\": " << v.orphan_artefacts() << ", "
      << "\"meta_model_properties\": " << v.meta_model_properties() << ", "
      << "\"has_generatable_artefacts\": " << v.has_generatable_artefacts() << ", "
      << "\"regions_by_logical_id\": " << v.regions_by_logical_id()
      << " }";
    return(s);
}

}
