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
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.identification/io/entities/model_type_io.hpp"
#include "dogen.logical/io/entities/structural/module_io.hpp"
#include "dogen.logical/io/entities/orm/model_properties_io.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.logical/io/entities/orm/element_repository_io.hpp"
#include "dogen.logical/io/entities/build/element_repository_io.hpp"
#include "dogen.logical/io/entities/mapping/element_repository_io.hpp"
#include "dogen.identification/io/entities/injection_provenance_io.hpp"
#include "dogen.logical/io/entities/physical/element_repository_io.hpp"
#include "dogen.logical/io/entities/decoration/element_repository_io.hpp"
#include "dogen.logical/io/entities/structural/element_repository_io.hpp"
#include "dogen.logical/io/entities/templating/element_repository_io.hpp"
#include "dogen.logical/io/entities/variability/element_repository_io.hpp"
#include "dogen.logical/io/entities/serialization/element_repository_io.hpp"
#include "dogen.logical/io/entities/visual_studio/element_repository_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::logical::entities::name, dogen::identification::entities::model_type>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_set<dogen::logical::entities::name>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::logical::entities::structural::module>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::technical_space>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_set<dogen::identification::entities::technical_space>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::logical::entities::orm::model_properties>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::logical::entities::name>& v) {
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

namespace dogen::logical::entities {

std::ostream& operator<<(std::ostream& s, const model& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::model\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"meta_name\": " << v.meta_name() << ", "
      << "\"provenance\": " << v.provenance() << ", "
      << "\"references\": " << v.references() << ", "
      << "\"leaves\": " << v.leaves() << ", "
      << "\"root_module\": " << v.root_module() << ", "
      << "\"input_technical_space\": " << v.input_technical_space() << ", "
      << "\"output_technical_spaces\": " << v.output_technical_spaces() << ", "
      << "\"all_technical_spaces\": " << v.all_technical_spaces() << ", "
      << "\"orm_properties\": " << v.orm_properties() << ", "
      << "\"structural_elements\": " << v.structural_elements() << ", "
      << "\"decoration_elements\": " << v.decoration_elements() << ", "
      << "\"variability_elements\": " << v.variability_elements() << ", "
      << "\"mapping_elements\": " << v.mapping_elements() << ", "
      << "\"templating_elements\": " << v.templating_elements() << ", "
      << "\"serialization_elements\": " << v.serialization_elements() << ", "
      << "\"visual_studio_elements\": " << v.visual_studio_elements() << ", "
      << "\"orm_elements\": " << v.orm_elements() << ", "
      << "\"build_elements\": " << v.build_elements() << ", "
      << "\"physical_elements\": " << v.physical_elements() << ", "
      << "\"meta_names\": " << v.meta_names()
      << " }";
    return(s);
}

}
