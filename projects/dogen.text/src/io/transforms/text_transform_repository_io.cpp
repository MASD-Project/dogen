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
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.text/io/transforms/model_to_text_transform_io.hpp"
#include "dogen.text/io/transforms/text_transform_repository_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::shared_ptr<dogen::text::transforms::model_to_text_transform>& v) {
    s << "{ " << "\"__type__\": " << "\"std::shared_ptr\"" << ", "
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

inline std::ostream& operator<<(std::ostream& s, const std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> >& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::identification::entities::logical_meta_id, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >& v) {
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

namespace dogen::text::transforms {

std::ostream& operator<<(std::ostream& s, const text_transform_repository& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::text::transforms::text_transform_repository\"" << ", "
      << "\"model_to_text_transforms_by_meta_name\": " << v.model_to_text_transforms_by_meta_name()
      << " }";
    return(s);
}

}
