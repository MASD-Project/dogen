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
#include "dogen/cpp/types/formatters/types/visitor_header_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/formatting_assistant.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

dogen::formatters::file visitor_header_formatter_stitch(
    formatters::formatting_assistant& fa,
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
            for (const auto& t : v.types()) {
fa.stream() << "                virtual void visit(const " << t << "&) const { }" << std::endl;
fa.stream() << "                virtual void visit(const " << t << "&) { }" << std::endl;
fa.stream() << "                virtual void visit(" << t << "&) const { }" << std::endl;
fa.stream() << "                virtual void visit(" << t << "&) { }" << std::endl;
            }
fa.stream() << "};" << std::endl;
fa.stream() << std::endl;
        } // snf
fa.stream() << std::endl;
    } // sbf
    return fa.make_file();
}

} } } }
