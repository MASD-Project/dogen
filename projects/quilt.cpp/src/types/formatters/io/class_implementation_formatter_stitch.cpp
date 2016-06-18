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
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/io/inserter_implementation_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/inserter_implementation_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

dogen::formatters::file class_implementation_formatter_stitch(
    assistant& a, const properties::class_info& c) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        a.add_helper_methods(c);

        {
            auto snf(a.make_scoped_namespace_formatter(c.namespaces()));
            const bool no_arg(!c.is_parent() && c.parents().empty() &&
                c.properties().empty());
a.stream() << std::endl;
a.stream() << "std::ostream& operator<<(std::ostream& s, const " << c.name() << "&" << (no_arg ? "" : " v") << ") {" << std::endl;
            if (c.is_parent() || !c.parents().empty()) {
a.stream() << "    v.to_stream(s);" << std::endl;
a.stream() << "    return(s);" << std::endl;
            } else
                io::inserter_implementation_helper_stitch(a, c, false/*inside_class*/);
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_file();
}
} } } } }
