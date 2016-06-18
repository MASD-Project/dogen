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
#include "dogen/quilt.cpp/types/formatters/odb/class_header_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace odb {

dogen::formatters::file class_header_formatter_stitch(
    assistant& a, const properties::class_info& c) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        const auto odbs(a.get_odb_settings());
        if (!odbs || odbs->pragmas().empty()) {
a.stream() << "// class has no ODB pragmas defined." << std::endl;
a.stream() << std::endl;
        } else {
            {
                auto snf(a.make_scoped_namespace_formatter(c.namespaces()));

a.stream() << std::endl;
a.stream() << "#ifdef ODB_COMPILER" << std::endl;
a.stream() << std::endl;
                const std::string odb_key("odb_pragma");
                for (const auto& pg : odbs->pragmas())
a.stream() << "#pragma db object(" << c.name() << ") " << pg << std::endl;

                bool is_first(true);
                for (const auto p : c.properties()) {
                    const auto podbs(a.get_odb_settings(p.id()));
                    if (podbs) {
                        for (const auto pg : podbs->pragmas()) {
                            if (is_first)
a.stream() << std::endl;
                            is_first = false;
a.stream() << "#pragma db member(" << c.name() << "::" << a.make_member_variable_name(p) << ") " << pg << std::endl;
                        }
                    }
                }
a.stream() << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << std::endl;
            }
a.stream() << std::endl;
        }
    } // sbf
    return a.make_file();
}
} } } } }
