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
#include "dogen/quilt.csharp/types/formatters/types/number_helper.hpp"
#include "dogen/quilt.csharp/types/formattables/helper_properties.hpp"
#include "dogen/quilt.csharp/types/formatters/types/traits.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/formatters/types/csharp/scoped_namespace_formatter.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace types {

std::string number_helper::formatter_name() const {
    static auto r(std::string("<") + traits::facet() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string number_helper::family() const {
    static std::string r("Number");
    return r;
}

std::list<std::string>
number_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        types::traits::class_archetype()
    });
    return r;
}

std::list<std::string>
number_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        traits::facet()
    });
    return r;
}

std::string number_helper::helper_name() const {
    static std::string r("number_helper");
    return r;
}

void number_helper::
format(assistant& a, const formattables::helper_properties& /*hp*/) const {
a.stream() << std::endl;
a.stream() << "bool create_number(const unsigned int position) {" << std::endl;
a.stream() << "    return (position % 2) == 0;" << std::endl;
a.stream() << "}" << std::endl;
}
} } } } }
