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
#include "dogen/quilt.cpp/types/formatters/types/visitor_header_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {

dogen::formatters::file visitor_header_formatter_stitch(
    assistant& a, const formattables::visitor_info& v) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            auto snf(a.make_scoped_namespace_formatter(v.namespaces()));
a.stream() << std::endl;
            a.comment(v.documentation());
a.stream() << "class " << v.name() << " {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    virtual ~" << v.name() << "() noexcept = 0;" << std::endl;
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
            bool is_first(true);
            for (const auto& t : v.types()) {
                if (!is_first)
a.stream() << std::endl;
                a.comment_start_method_group(t.documentation());
a.stream() << "    virtual void visit(const " << t.qualified_name() << "&) const { }" << std::endl;
a.stream() << "    virtual void visit(const " << t.qualified_name() << "&) { }" << std::endl;
a.stream() << "    virtual void visit(" << t.qualified_name() << "&) const { }" << std::endl;
a.stream() << "    virtual void visit(" << t.qualified_name() << "&) { }" << std::endl;
                a.comment_end_method_group(t.documentation());
                is_first = false;
            }
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "inline " << v.name() << "::~" << v.name() << "() noexcept { }" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_file();
}

} } } } }
