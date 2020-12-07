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
#include "dogen.text.cpp/types/transforms/io/inserter_implementation_helper.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"

namespace dogen::text::cpp::transforms::io {

void inserter_implementation_helper(
    text::formatters::assistant& ast,
    const logical::entities::structural::object& o,
    const bool inside_class) {
    const auto qn(ast.get_qualified_name(o.name()));

    if (ast.requires_stream_manipulators()) {
        ast.stream() << "    boost::io::ios_flags_saver ifs(s);" << std::endl;
        ast.stream() << "    s.setf(std::ios_base::boolalpha);" << std::endl;
        ast.stream() << "    s.setf(std::ios::fixed, std::ios::floatfield);"
                     << std::endl;
        ast.stream() << "    s.precision(6);" << std::endl;
        ast.stream() << "    s.setf(std::ios::showpoint);" << std::endl;
        ast.stream() << std::endl;
    }

    const bool no_parent_and_no_attributes(
        o.parents().empty() &&
        o.all_attributes().empty());

    ast.stream() << "    s << \" { \"" << std::endl;
    ast.stream() << "      << \"\\\"__type__\\\": \" << \"\\\"" << qn
                 << "\\\"\"" <<
        (no_parent_and_no_attributes ? " << \" }\";" : " << \", \"")
                 << std::endl;

    utility::formatters::sequence_formatter sf(o.parents().size());
    sf.prefix_configuration().first("  << ").not_first("s << ");
    sf.element_separator("");
    if (!o.parents().empty()) {
        const auto& pn(o.parents().front());
        const auto pqn(ast.get_qualified_name(pn));
        ast.stream() << "    " << sf.prefix() << "\"\\\"__parent_"
                     << sf.current_position() << "__\\\": \""
                     << sf.postfix() << ";" << std::endl;
        ast.stream() << "    " << pqn << "::to_stream(s);" << std::endl;
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

    for (const auto& attr : o.local_attributes()) {
        std::string variable_name;
        if (inside_class)
            variable_name = attr.member_variable_name();
        else
            variable_name = "v." + attr.getter_setter_name() + "()";

        ast.stream() << "    " << sf.prefix() << "<< \"\\\""
                     << attr.name().simple() << "\\\": \" << "
                     << ast.streaming_for_type(attr.parsed_type().current(),
                         variable_name) << sf.postfix() << std::endl;
        sf.next();
    }

    if (!no_parent_and_no_attributes) {
        if (!o.local_attributes().empty())
            ast.stream() << "      << \" }\";" << std::endl;
        else
            ast.stream() << "    s << \" }\";" << std::endl;
    }

    if (!inside_class)
        ast.stream() << "    return(s);" << std::endl;
}

}
