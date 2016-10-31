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
#include "dogen/quilt.cpp/types/formatters/hash/enum_header_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace hash {

dogen::formatters::artefact enum_header_formatter_stitch(
    assistant& a, const yarn::enumeration& e) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
a.stream() << std::endl;
a.stream() << "namespace std {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>" << std::endl;
a.stream() << "struct hash<" << a.get_qualified_name(e.name()) << "> {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    size_t operator()(const " << a.get_qualified_name(e.name()) << "& v) const {" << std::endl;
a.stream() << "        return std::hash<unsigned int>()(static_cast<unsigned int>(v));" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

} } } } }
