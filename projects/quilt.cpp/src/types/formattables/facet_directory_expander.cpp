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
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/facet_directory_expander.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void facet_directory_expander::expand(
    const std::unordered_map<std::string, annotations::path_annotations>& pa,
    const formatters::container& fc, model& fm) const {

    for (const auto& f : fc.file_formatters()) {
        const auto i(pa.find(f->ownership_hierarchy().formatter_name()));
        if (i == pa.end())
            continue;

        const auto fctn(f->ownership_hierarchy().facet_name());
        fm.facet_configurations()[fctn].directory(i->second.facet_directory());
    }
}

} } } }
