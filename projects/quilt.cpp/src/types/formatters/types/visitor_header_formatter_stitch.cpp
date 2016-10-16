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

dogen::formatters::artefact visitor_header_formatter_stitch(
    assistant& a, const yarn::visitor& v) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            const auto ns(a.make_namespaces(v.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
            a.comment(v.documentation());
            if (!v.parent())
a.stream() << "class " << v.name().simple() << " {" << std::endl;
            else {
                const auto& pn(*v.parent());
                const auto pqn(a.get_qualified_name(pn));
a.stream() << "class " << v.name().simple() << " : public " << pqn << " {" << std::endl;
            }
a.stream() << "public:" << std::endl;
a.stream() << "    virtual ~" << v.name().simple() << "() noexcept = 0;" << std::endl;
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
            if (v.parent()) {
                const auto& pn(*v.parent());
                const auto pqn(a.get_qualified_name(pn));
a.stream() << "    using " << pqn << "::visit;" << std::endl;
a.stream() << std::endl;
            }

            bool is_first(true);
            for (const auto& t : v.visits()) {
                if (!is_first)
a.stream() << std::endl;
                const auto qn(a.get_qualified_name(t));
                const auto doc("Accept visits for type " + qn);
                a.comment_start_method_group(doc);
a.stream() << "    virtual void visit(const " << qn << "&) const { }" << std::endl;
a.stream() << "    virtual void visit(const " << qn << "&) { }" << std::endl;
a.stream() << "    virtual void visit(" << qn << "&) const { }" << std::endl;
a.stream() << "    virtual void visit(" << qn << "&) { }" << std::endl;
                a.comment_end_method_group(doc);
                is_first = false;
            }
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "inline " << v.name().simple() << "::~" << v.name().simple() << "() noexcept { }" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

} } } } }
