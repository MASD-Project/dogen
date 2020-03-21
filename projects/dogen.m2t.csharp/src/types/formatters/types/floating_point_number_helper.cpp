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
#include "dogen.m2t.csharp/types/formatters/assistant.hpp"
#include "dogen.m2t.csharp/types/formatters/types/traits.hpp"
#include "dogen.m2t.csharp/types/formattables/helper_properties.hpp"
#include "dogen.m2t.csharp/types/formatters/types/floating_point_number_helper.hpp"

namespace dogen::m2t::csharp::formatters::types {

std::string floating_point_number_helper::id() const {
    static auto r(std::string("<") + traits::facet() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string floating_point_number_helper::family() const {
    static std::string r("FloatingPointNumber");
    return r;
}

std::list<std::string>
floating_point_number_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_archetype(),
        traits::primitive_archetype()
    });
    return r;
}

std::list<std::string>
floating_point_number_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        traits::facet()
    });
    return r;
}

std::string floating_point_number_helper::helper_name() const {
    static std::string r("floating_point_number_helper");
    return r;
}

void floating_point_number_helper::
format(assistant& a, const formattables::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
a.stream() << "        /// <summary>" << std::endl;
a.stream() << "        /// Compare floating point numbers, taking precision into account (" << qn << " version)." << std::endl;
a.stream() << "        /// </summary>" << std::endl;
a.stream() << "        static private bool NearlyEqual(" << qn << " lhs, " << qn << " rhs)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            " << qn << " epsilon = Math.Max(Math.Abs(lhs), Math.Abs(rhs)) * " << qn << ".Epsilon;" << std::endl;
a.stream() << "            return Math.Abs(lhs - rhs) <= epsilon;" << std::endl;
a.stream() << "        }" << std::endl;
}
}
