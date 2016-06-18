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
#include "dogen/quilt.cpp/types/formatters/serialization/class_header_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

dogen::formatters::file class_header_formatter_stitch(
    assistant& a, const properties::class_info& c) {
    {
        auto sbf(a.make_scoped_boilerplate_formatter());

        if (!c.is_parent() && !c.parents().empty()) {
            for (const auto p : c.parents()) {
a.stream() << "namespace boost {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>struct" << std::endl;
a.stream() << "is_virtual_base_of<" << std::endl;
a.stream() << "    " << p.qualified_name() << "," << std::endl;
a.stream() << "    " << c.qualified_name() << std::endl;
a.stream() << "> : public mpl::true_ {};" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
            }
        }
a.stream() << std::endl;
a.stream() << "BOOST_SERIALIZATION_SPLIT_FREE(" << c.qualified_name() << ")" << std::endl;
        if (c.is_parent()) {
a.stream() << "BOOST_SERIALIZATION_ASSUME_ABSTRACT(" << c.qualified_name() << ")" << std::endl;
a.stream() << std::endl;
        }
a.stream() << "namespace boost {" << std::endl;
a.stream() << "namespace serialization {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void save(Archive& ar, const " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void load(Archive& ar, " << c.qualified_name() << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "} }" << std::endl;
a.stream() << std::endl;
    } // sbf
    return a.make_file();
}
} } } } }
