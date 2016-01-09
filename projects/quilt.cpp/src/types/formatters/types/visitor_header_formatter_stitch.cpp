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
    formatters::entity_formatting_assistant& fa,
    const formattables::visitor_info& v) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        {
            auto snf(fa.make_scoped_namespace_formatter());
fa.stream() << std::endl;
            fa.comment(v.documentation());
fa.stream() << "class " << v.name() << " {" << std::endl;
fa.stream() << "public:" << std::endl;
fa.stream() << "    virtual ~" << v.name() << "() noexcept = 0;" << std::endl;
fa.stream() << std::endl;
fa.stream() << "public:" << std::endl;
            bool is_first(true);
            for (const auto& t : v.types()) {
                if (!is_first)
fa.stream() << std::endl;
                fa.comment_start_method_group(t.documentation());
fa.stream() << "    virtual void visit(const " << t.qualified_name() << "&) const { }" << std::endl;
fa.stream() << "    virtual void visit(const " << t.qualified_name() << "&) { }" << std::endl;
fa.stream() << "    virtual void visit(" << t.qualified_name() << "&) const { }" << std::endl;
fa.stream() << "    virtual void visit(" << t.qualified_name() << "&) { }" << std::endl;
                fa.comment_end_method_group(t.documentation());
                is_first = false;
            }
fa.stream() << "};" << std::endl;
fa.stream() << std::endl;
fa.stream() << "inline " << v.name() << "::~" << v.name() << "() noexcept { }" << std::endl;
fa.stream() << std::endl;
        } // snf
fa.stream() << std::endl;
    } // sbf
    return fa.make_file();
}

} } } } }
