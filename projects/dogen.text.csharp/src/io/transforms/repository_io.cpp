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
#include <string>
#include <ostream>
#include <forward_list>
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"
#include "dogen.text.csharp/types/transforms/model_to_text_transform.hpp"
#include "dogen.text/types/transforms/helper_transform.hpp"
#include "dogen.text.csharp/io/transforms/repository_io.hpp"

namespace dogen::text::csharp::transforms {

template<typename Id, typename Containee>
inline std::ostream& to_stream(std::ostream& s, const Id& key,
    const std::forward_list<Containee>& value) {
    s << "\"" << key << "\": " << "[ ";

    for(auto i(value.begin()); i != value.end(); ++i) {
        if (i != value.begin()) s << ", ";
        s <<  "\"" << (*i)->archetype().meta_name().id().value() << "\"";
    }
    s << " ], ";
    return s;
}

inline std::ostream& to_stream(std::ostream& s,
    const std::unordered_map<identification::entities::logical_meta_id,
    std::forward_list<std::shared_ptr<model_to_text_transform>>>& safmt) {
    s << "\"stock_artefact_formatters_by_meta_name\": " << "[ ";

    for(auto i(safmt.begin()); i != safmt.end(); ++i) {
        if (i != safmt.begin()) s << ", ";
        s <<  "{ \"" << i->first << "\":" << "[ ";
        for(auto j(i->second.begin()); j != i->second.end(); ++j) {
            if (j != i->second.begin()) s << ", ";
            s << (*j)->archetype().meta_name().id().value();
        }
            s << "] }";
    }
    s << "], ";
    return s;
}


std::ostream& operator<<(std::ostream& s, const repository& rp) {
    s << "{ " << "\"__type__\": "
      << "\"dogen::text::cpp::formatters::container\", ";
    to_stream(s, rp.stock_artefact_formatters_by_meta_name());
    to_stream(s, "stock_artefact_formatters", rp.stock_artefact_formatters());
    s << " }";
    return s;
}

}
