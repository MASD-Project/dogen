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
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/helper_formatter_interface.hpp"
#include "dogen/quilt.cpp/io/formatters/container_io.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
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
    const std::unordered_map<std::string, std::unordered_map<std::string,
    std::list<std::shared_ptr<helper_formatter_interface>>>>& helpers) {
    s << "\"helper_formatters\": " << "[ ";

    for(auto i(helpers.begin()); i != helpers.end(); ++i) {
        if (i != helpers.begin()) s << ", ";
        s <<  "{ \"" << i->first << "\":" << "[ ";
        for(auto j(i->second.begin()); j != i->second.end(); ++j) {
            if (j != i->second.begin()) s << ", ";
            s <<  "{ \"" << j->first << "\":" << "[ ";
            for(auto k(j->second.begin()); k != j->second.end(); ++k) {
                if (k != j->second.begin()) s << ", ";
                s <<  "\"" << (*k)->formatter_name() << "\"";
            }
            s << "] }";
        }
        s << "] }";

    }
    s << " ]";
    return s;
}

inline std::ostream& to_stream(std::ostream& s,
    const std::unordered_map<std::type_index,
    std::forward_list<std::shared_ptr<file_formatter_interface>>>& ffti) {
    s << "\"file_formatters_by_type_index\": " << "[ ";

    for(auto i(ffti.begin()); i != ffti.end(); ++i) {
        if (i != ffti.begin()) s << ", ";
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
    to_stream(s, rp.file_formatters_by_type_index());
    to_stream(s, "all_file_formatters", rp.file_formatters());
    to_stream(s, rp.helper_formatters());
    s << " }";
    return s;
}

} } } }
