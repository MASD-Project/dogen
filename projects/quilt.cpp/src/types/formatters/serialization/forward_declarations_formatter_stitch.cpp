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
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/forward_declarations_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

dogen::formatters::file forward_declarations_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::forward_declarations_info& fd) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
fa.stream() << std::endl;
fa.stream() << "namespace boost {" << std::endl;
fa.stream() << "namespace serialization {" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template<class Archive>" << std::endl;
fa.stream() << "void save(Archive& ar, const " << fd.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template<class Archive>" << std::endl;
fa.stream() << "void load(Archive& ar, " << fd.qualified_name() << "& v, unsigned int version);" << std::endl;
fa.stream() << std::endl;
fa.stream() << "} }" << std::endl;
fa.stream() << std::endl;
    } // sbf
    return fa.make_file();
}

} } } } }
