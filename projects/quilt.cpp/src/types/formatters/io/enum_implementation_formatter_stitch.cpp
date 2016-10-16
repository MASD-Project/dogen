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
#include "dogen/quilt.cpp/types/formatters/io/enum_header_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

dogen::formatters::artefact enum_implementation_formatter_stitch(
    assistant& a, const yarn::enumeration& e) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "std::ostream& operator<<(std::ostream& s, const " << e.name().simple() << "& v) {" << std::endl;
a.stream() << "    s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << e.name().simple() << "\\\", \" << \"\\\"value\\\": \";" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::string attr;" << std::endl;
a.stream() << "    switch (v) {" << std::endl;
            for (const auto& en : e.enumerators()) {
a.stream() << "    case " << e.name().simple() << "::" << en.name() << ":" << std::endl;
a.stream() << "        attr = \"\\\"" << en.name() << "\\\"\";" << std::endl;
a.stream() << "        break;" << std::endl;
            }
a.stream() << "    default:" << std::endl;
a.stream() << "        throw std::invalid_argument(\"Invalid value for " << e.name().simple() << "\");" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    s << attr << \" }\";" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
         } // snf
    } // sbf
    return a.make_artefact();
}

} } } } }
