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
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_properties_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::unordered_map<std::string, formatter_configuration>
formatter_properties_factory::make(
    const std::unordered_map<std::string, path_derivatives>&
    path_derivatives,
    const std::unordered_map<std::string, std::list<std::string> >&
    inclusion_dependencies,
    const std::unordered_map<std::string, bool>& enablement,
    std::unordered_set<std::string> enabled_formatters,
    std::unordered_map<std::string, std::string>
    facet_directory_for_facet) const {

    std::unordered_map<std::string, formatter_configuration> r;
    for (const auto& pair : path_derivatives) {
        auto& entry(r[pair.first]);
        entry.file_path(pair.second.file_path());
        entry.header_guard(pair.second.header_guard());
    }

    for (const auto& pair : inclusion_dependencies)
        r[pair.first].inclusion_dependencies(pair.second);

    for (const auto& pair : enablement)
        r[pair.first].enabled(pair.second);

    for (auto& pair : r) {
        pair.second.enabled_formatters(enabled_formatters);
        pair.second.facet_directory_for_facet(facet_directory_for_facet);
    }

    return r;
}

} } } }
