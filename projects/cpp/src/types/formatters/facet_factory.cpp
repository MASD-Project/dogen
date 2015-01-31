/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/formatters/facet_factory.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

std::forward_list<facet> facet_factory::build(
    const std::unordered_map<std::string, container>& formatters_by_facet,
    const std::unordered_map<std::string, settings::global_settings>&
        global_settings_for_facet) const {

    std::unordered_map<std::string, facet> facet_by_id;
    for (const auto pair : formatters_by_facet)
        facet_by_id[pair.first].container(pair.second);

    for (auto pair : global_settings_for_facet)
        facet_by_id[pair.first].global_settings(pair.second);

    std::forward_list<facet> r;
    for (const auto& pair : facet_by_id) {
        auto f(pair.second);
        f.id(pair.first);
        r.push_front(f);
    }

    return r;
}

} } }
