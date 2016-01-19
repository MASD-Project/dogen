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
#include "dogen/quilt.cpp/types/formatters/io/pair_helper_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

void pair_helper_stitch(
    nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) {

    {
        auto snf(a.make_scoped_namespace_formatter(t.namespaces()));
        const auto first(t.children().front());
        const auto second(t.children().back());
a.stream() << std::endl;
a.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << t.complete_name() << "& v) {" << std::endl;
a.stream() << "    s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << t.name() << "\\\"\" << \", \";" << std::endl;
a.stream() << std::endl;
a.stream() << "    s << \"\\\"first\\\": \" << " << a.streaming_for_type(first, "v.first") << " << \", \";" << std::endl;
a.stream() << "    s << \"\\\"second\\\": \" << " << a.streaming_for_type(second, "v.second") << ";" << std::endl;
a.stream() << "    s << \" }\";" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    }
a.stream() << std::endl;
}
} } } } }
