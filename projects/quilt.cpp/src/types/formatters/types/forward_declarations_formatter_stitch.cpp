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
#include "dogen/quilt.cpp/types/formatters/types/forward_declarations_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {
dogen::formatters::artefact forward_declarations_formatter_stitch(
    assistant& a, const fabric::forward_declarations& fd) {

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            const auto ns(a.make_namespaces(fd.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));

            if (fd.is_enum()) {
a.stream() << std::endl;
a.stream() << "enum class " << fd.name().simple() << " : " << fd.underlying_type().simple() << ";" << std::endl;
a.stream() << std::endl;
            } else {
a.stream() << std::endl;
a.stream() << "class " << fd.name().simple() << ";" << std::endl;
a.stream() << std::endl;
            }
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

} } } } }
