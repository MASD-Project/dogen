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
#include "dogen/quilt.cpp/types/properties/aspect_properties_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

aspect_properties_factory::aspect_properties_factory(
    const annotations::aspect_annotations_repository& asrp)
    : repository_(asrp) { }

void aspect_properties_factory::compute_properties(const yarn::name_tree& nt,
    const bool is_top_level, aspect_properties& ap) const {

    for (const auto& c : nt.children())
        compute_properties(c, false/*is_top_level*/, ap);

    if (is_top_level && nt.is_current_simple_type())
        ap.requires_manual_default_constructor(true);

    const auto i(repository_.by_id().find(nt.current().id()));
    if (i == repository_.by_id().end())
        return;

    const auto as(i->second);
    if (as.requires_stream_manipulators())
        ap.requires_stream_manipulators(true);

    if (!is_top_level)
        return;

    if (as.requires_manual_default_constructor())
        ap.requires_manual_default_constructor(true);

    if (as.requires_manual_move_constructor())
        ap.requires_manual_move_constructor(true);
}

aspect_properties aspect_properties_factory::
make(const std::list<yarn::attribute>& attributes) const {
    aspect_properties r;
    for (const auto a : attributes) {
        const auto& nt(a.parsed_type());
        compute_properties(nt, true/*is_top_level*/, r);
    }
    return r;
}

} } } }
