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
#include "dogen/quilt.cpp/types/formatters/serialization/enum_header_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

dogen::formatters::artefact enum_header_formatter_stitch(
    assistant& a, const yarn::enumeration& e) {
    {
        auto sbf(a.make_scoped_boilerplate_formatter());
a.stream() << std::endl;
a.stream() << "template<class Archive>" << std::endl;
a.stream() << "void serialize(Archive& ar, " << a.get_qualified_name(e.name()) << "& v, unsigned int /*version*/){" << std::endl;
a.stream() << "    using boost::serialization::make_nvp;" << std::endl;
a.stream() << "    ar & make_nvp(\"" << e.name().simple() << "\", v);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
} } } } }
