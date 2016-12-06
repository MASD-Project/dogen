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
#include "dogen/quilt.csharp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen/quilt.csharp/io/formatters/repository_io.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

template<typename Containee>
inline std::ostream& to_stream(std::ostream& s, const std::string& key,
    const std::forward_list<Containee>& value) {
    s << "\"" << key << "\": " << "[ ";

    for(auto i(value.begin()); i != value.end(); ++i) {
        if (i != value.begin()) s << ", ";
        s <<  "\"" << (*i)->formatter_name() << "\"";
    }
    s << " ], ";
    return s;
}
inline std::ostream& to_stream(std::ostream& s,
    const std::unordered_map<std::type_index,
    std::forward_list<std::shared_ptr<artefact_formatter_interface>>>& safti) {
    s << "\"stock_artefact_formatters_by_type_index\": " << "[ ";

    for(auto i(safti.begin()); i != safti.end(); ++i) {
        if (i != safti.begin()) s << ", ";
        s <<  "{ \"" << i->first.name() << "\":" << "[ ";
        for(auto j(i->second.begin()); j != i->second.end(); ++j) {
            if (j != i->second.begin()) s << ", ";
                s <<  "\"" << (*j)->formatter_name() << "\"";
        }
            s << "] }";
    }
    s << "], ";
    return s;
}


std::ostream& operator<<(std::ostream& s, const repository& rp) {
    s << "{ " << "\"__type__\": "
      << "\"dogen::quilt::cpp::formatters::container\", ";
    to_stream(s, rp.stock_artefact_formatters_by_type_index());
    to_stream(s, "stock_artefact_formatters", rp.stock_artefact_formatters());
    s << " }";
    return s;
}

} } } }
