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
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/io/meta_model/origin_types_io.hpp"
#include "dogen.assets/io/meta_model/technical_space_io.hpp"
#include "dogen.assets/io/meta_model/structural/module_io.hpp"
#include "dogen.assets/io/meta_model/orm/model_properties_io.hpp"
#include "dogen.assets/io/meta_model/extraction_properties_io.hpp"
#include "dogen.assets/io/meta_model/mapping/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/decoration/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/structural/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/templating/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/variability/element_repository_io.hpp"
#include "dogen.assets/io/meta_model/serialization/element_repository_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::assets::meta_model::name, dogen::assets::meta_model::origin_types>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_set<dogen::assets::meta_model::name>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::assets::meta_model::structural::module>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::assets::meta_model::technical_space>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::assets::meta_model::orm::model_properties>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::assets::meta_model {

std::ostream& operator<<(std::ostream& s, const model& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::model\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"meta_name\": " << v.meta_name() << ", "
      << "\"origin_type\": " << v.origin_type() << ", "
      << "\"origin_sha1_hash\": " << "\"" << tidy_up_string(v.origin_sha1_hash()) << "\"" << ", "
      << "\"origin_element_id\": " << "\"" << tidy_up_string(v.origin_element_id()) << "\"" << ", "
      << "\"references\": " << v.references() << ", "
      << "\"leaves\": " << v.leaves() << ", "
      << "\"root_module\": " << v.root_module() << ", "
      << "\"input_technical_space\": " << v.input_technical_space() << ", "
      << "\"output_technical_spaces\": " << v.output_technical_spaces() << ", "
      << "\"orm_properties\": " << v.orm_properties() << ", "
      << "\"extraction_properties\": " << v.extraction_properties() << ", "
      << "\"structural_elements\": " << v.structural_elements() << ", "
      << "\"decoration_elements\": " << v.decoration_elements() << ", "
      << "\"variability_elements\": " << v.variability_elements() << ", "
      << "\"mapping_elements\": " << v.mapping_elements() << ", "
      << "\"templating_elements\": " << v.templating_elements() << ", "
      << "\"serialization_elements\": " << v.serialization_elements()
      << " }";
    return(s);
}

}
