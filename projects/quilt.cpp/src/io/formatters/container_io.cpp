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
        s <<  "\"" << (*i)->id() << "\"";
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
                s <<  "\"" << (*k)->id() << "\"";
            }
            s << "] }";
        }
        s << "] }";

    }
    s << " ]";
    return s;
}


std::ostream& operator<<(std::ostream& s, const container& c) {
    s << "{ " << "\"__type__\": "
      << "\"dogen::quilt::cpp::formatters::container\", ";
    to_stream(s, "enum_formatters", c.enum_formatters());
    to_stream(s, "exception_formatters", c.exception_formatters());
    to_stream(s, "namespace_formatters", c.namespace_formatters());
    to_stream(s, "visitor_formatters", c.visitor_formatters());
    to_stream(s, "forward_declarations_formatters",
        c.forward_declarations_formatters());
    to_stream(s, "odb_options_formatters", c.odb_options_formatters());
    to_stream(s, "cmakelists_formatters", c.cmakelists_formatters());
    to_stream(s, "registrar_formatters", c.registrar_formatters());
    to_stream(s, "includers_formatters", c.includers_formatters());
    to_stream(s, "all_file_formatters", c.all_file_formatters());
    to_stream(s, "all_internal_file_formatters",
        c.all_internal_file_formatters());
    to_stream(s, "all_external_file_formatters",
        c.all_external_file_formatters());

    to_stream(s, c.helper_formatters());
    s << " }";
    return s;
}

} } } }
