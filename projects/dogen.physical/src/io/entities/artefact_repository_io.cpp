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
#include "dogen.physical/io/entities/artefact_set_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.physical/io/entities/artefact_repository_io.hpp"
#include "dogen.physical/io/entities/extraction_properties_io.hpp"
#include "dogen.physical/io/entities/meta_model_properties_io.hpp"
#include "dogen.identification/io/entities/logical_provenance_io.hpp"
#include "dogen.identification/io/entities/logical_meta_physical_id_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::identification::entities::logical_id, dogen::physical::entities::artefact_set>& v) {
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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_set<dogen::identification::entities::logical_meta_physical_id>& v) {
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

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const artefact_repository& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::physical::entities::artefact_repository\"" << ", "
      << "\"provenance\": " << v.provenance() << ", "
      << "\"artefact_sets_by_logical_id\": " << v.artefact_sets_by_logical_id() << ", "
      << "\"extraction_properties\": " << v.extraction_properties() << ", "
      << "\"enabled_archetype_for_element\": " << v.enabled_archetype_for_element() << ", "
      << "\"managed_directories\": " << v.managed_directories() << ", "
      << "\"has_generatable_artefacts\": " << v.has_generatable_artefacts() << ", "
      << "\"meta_model_properties\": " << v.meta_model_properties()
      << " }";
    return(s);
}

}
