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
#include "dogen/quilt.cpp/types/formatters/hash/class_header_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace hash {

dogen::formatters::file class_header_formatter_stitch(
    assistant& a, const formattables::class_info& c) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            auto snf(a.make_scoped_namespace_formatter(c.namespaces()));
a.stream() << std::endl;
a.stream() << "struct " << c.name() << "_hasher {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    static std::size_t hash(const " << c.name() << "& v);" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
a.stream() << "namespace std {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>" << std::endl;
a.stream() << "struct hash<" << c.qualified_name() << "> {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    size_t operator()(const " << c.qualified_name() << "& v) const {" << std::endl;
a.stream() << "        return " << c.qualified_name() << "_hasher::hash(v);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
    } // sbf
    return a.make_file();
}
} } } } }
