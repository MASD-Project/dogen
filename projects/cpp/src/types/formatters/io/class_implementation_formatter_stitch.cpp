/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright(C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/formatters/io/inserter_implementation_helper_stitch.hpp"
#include "dogen/cpp/types/formatters/io/inserter_implementation_helper_stitch.hpp"
#include "dogen/cpp/types/formatters/io/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace io {

dogen::formatters::file class_implementation_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::class_info& c) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        fa.add_helper_methods();

        {
            auto snf(fa.make_scoped_namespace_formatter());
            const bool no_arg(!c.is_parent() && c.parents().empty() &&
                c.properties().empty());
fa.stream() << std::endl;
fa.stream() << "std::ostream& operator<<(std::ostream& s, const " << c.name() << "&" << (no_arg ? "" : " v") << ") {" << std::endl;
            if (c.is_parent() || !c.parents().empty()) {
fa.stream() << "    v.to_stream(s);" << std::endl;
fa.stream() << "    return(s);" << std::endl;
            } else
                io::inserter_implementation_helper_stitch(fa, c, false/*inside_class*/);
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
        } // snf
    } // sbf
    return fa.make_file();
}
} } } }
