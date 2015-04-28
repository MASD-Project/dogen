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
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

void class_header_formatter_stitch(std::ostream& s,
    const boost::optional<dogen::formatters::general_settings>& gs,
    const settings::formatter_settings& fs,
    const formattables::class_info& c) {

    dogen::formatters::cpp::scoped_boilerplate_formatter
       sbf(s, gs, fs.inclusion_dependencies(), *fs.header_guard());

    {
        dogen::formatters::cpp::scoped_namespace_formatter snf(
           s, c.namespaces(), false/*create_anonymous_namespace*/,
           true/*add_new_line*/);

        std::string final_status;
        if (!c.is_parent())
            final_status = "final ";

s << std::endl;
s << "class " << c.name() << " " << final_status << "{" << std::endl;
s << "public:" << std::endl;
        if (!c.requires_manual_default_constructor())
s << "    " << c.name() << "() = default;" << std::endl;
s << "    " << c.name() << "(const " << c.name() << "&) = default;" << std::endl;
        if (!c.requires_manual_move_constructor())
s << "    " << c.name() << "(" << c.name() << "&&) = default;" << std::endl;
        if (!c.is_parent() && c.parents().empty())
s << "    ~" << c.name() << "() = default;" << std::endl;
        if (c.is_immutable())
s << "    " << c.name() << "& operator=(const " << c.name() << "&) = delete;" << std::endl;
        if (c.all_properties().empty())
s << "    " << c.name() << "& operator=(const " << c.name() << "&) = default;" << std::endl;
s << std::endl;
        if (c.requires_manual_default_constructor()) {
s << "public:" << std::endl;
s << "    " << c.name() << "();" << std::endl;
s << std::endl;
        }
        if (c.class_type() != cpp::formattables::class_types::unversioned_key &&
            c.class_type() != cpp::formattables::class_types::versioned_key &&
            c.requires_manual_move_constructor() &&
            !c.all_properties().empty()) {
s << "public:" << std::endl;
s << "    " << c.name() << "(" << c.name() << "&& rhs);" << std::endl;
s << std::endl;
        }
s << std::endl;
s << "};" << std::endl;
s << std::endl;
    }
s << std::endl;
}

} } } }
