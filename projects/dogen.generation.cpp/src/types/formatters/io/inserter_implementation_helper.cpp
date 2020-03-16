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
#include "dogen.generation.cpp/types/formatters/io/inserter_implementation_helper.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"

namespace dogen::generation::cpp::formatters::io {

void inserter_implementation_helper(
    assistant& a, const logical::meta_model::structural::object& o, const bool inside_class) {

    const auto qn(a.get_qualified_name(o.name()));

    if (a.requires_stream_manipulators()) {
a.stream() << "    boost::io::ios_flags_saver ifs(s);" << std::endl;
a.stream() << "    s.setf(std::ios_base::boolalpha);" << std::endl;
a.stream() << "    s.setf(std::ios::fixed, std::ios::floatfield);" << std::endl;
a.stream() << "    s.precision(6);" << std::endl;
a.stream() << "    s.setf(std::ios::showpoint);" << std::endl;
a.stream() << std::endl;
    }

    const bool no_parent_and_no_attributes(o.parents().empty() &&
        o.all_attributes().empty());
a.stream() << "    s << \" { \"" << std::endl;
a.stream() << "      << \"\\\"__type__\\\": \" << \"\\\"" << qn << "\\\"\"" << (no_parent_and_no_attributes ? " << \" }\";" : " << \", \"") << std::endl;

    generation::formatters::sequence_formatter sf(o.parents().size());
    sf.prefix_configuration().first("  << ").not_first("s << ");
    sf.element_separator("");
    if (!o.parents().empty()) {
        const auto& pn(o.parents().front());
        const auto pqn(a.get_qualified_name(pn));
a.stream() << "    " << sf.prefix() << "\"\\\"__parent_" << sf.current_position() << "__\\\": \"" << sf.postfix() << ";" << std::endl;
a.stream() << "    " << pqn << "::to_stream(s);" << std::endl;
        sf.next();
    }

    sf.reset(o.local_attributes().size());

    if (!o.parents().empty())
        sf.prefix_configuration().first("s << \", \"\n      ");
    else
        sf.prefix_configuration().first("  ");
    sf.prefix_configuration().not_first("  ");
    sf.postfix_configuration().not_last(" << \", \"");
    sf.element_separator("");

    for (const auto attr : o.local_attributes()) {
        std::string variable_name;
        if (inside_class)
            variable_name = attr.member_variable_name();
        else
            variable_name = "v." + attr.getter_setter_name() + "()";

a.stream() << "    " << sf.prefix() << "<< \"\\\"" << attr.name().simple() << "\\\": \" << " << a.streaming_for_type(attr.parsed_type().current(), variable_name) << sf.postfix() << std::endl;
        sf.next();
    }

    if (!no_parent_and_no_attributes) {
        if (!o.local_attributes().empty())
a.stream() << "      << \" }\";" << std::endl;
        else
a.stream() << "    s << \" }\";" << std::endl;
    }

    if (!inside_class)
a.stream() << "    return(s);" << std::endl;
}
}
