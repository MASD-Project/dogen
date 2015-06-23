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
#include "dogen/cpp/types/formatters/odb/class_header_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace odb {

dogen::formatters::file class_header_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::class_info& c) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        const auto& os(c.settings().opaque_settings());
        const auto odbs(fa.get_odb_settings(os));
        if (!odbs || odbs->pragmas().empty()) {
fa.stream() << "// class has no ODB pragmas defined." << std::endl;
fa.stream() << std::endl;
        } else {
            {
                auto snf(fa.make_scoped_namespace_formatter());

fa.stream() << std::endl;
fa.stream() << "#ifdef ODB_COMPILER" << std::endl;
fa.stream() << std::endl;
                const std::string odb_key("odb_pragma");
                for (const auto& pg : odbs->pragmas())
fa.stream() << "#pragma db object(" << c.name() << ") " << pg << std::endl;

                bool is_first(true);
                for (const auto p : c.properties()) {
                    const auto& pos(p.opaque_settings());
                    const auto podbs(fa.get_odb_settings(pos));
                    if (podbs) {
                        for (const auto pg : podbs->pragmas()) {
                            if (is_first)
fa.stream() << std::endl;
                            is_first = false;
fa.stream() << "#pragma db member(" << c.name() << "::" << fa.make_member_variable_name(p) << ") " << pg << std::endl;
                        }
                    }
                }
fa.stream() << std::endl;
fa.stream() << "#endif" << std::endl;
fa.stream() << std::endl;
            }
fa.stream() << std::endl;
        }
    } // sbf
    return fa.make_file();
}
} } } }
