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
#include "dogen/quilt.cpp/types/formattables/profile_group_hydrator.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group_expander.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

profile_group_expander::profile_group_types
profile_group_expander::
hydrate(const std::forward_list<boost::filesystem::path>&
    data_directories) const {
    profile_group_hydrator h;
    return h.hydrate(data_directories);
}

void profile_group_expander::check_profile_groups(
    const formatters::container& /*fc*/, const profile_group_types& /*pgs*/) const {

}

profile_group_expander::profile_group_types
profile_group_expander::merge(const profile_group_types& /*pgs*/) const {
    profile_group_expander::profile_group_types r;
    return r;
}

void profile_group_expander::
populate_model(const profile_group_types& /*pgs*/, model& /*fm*/) const {

}

void profile_group_expander::expand(
    const std::forward_list<boost::filesystem::path>& data_directories,
    const formatters::container& fc, model& fm) const {

    const auto original(hydrate(data_directories));
    check_profile_groups(fc, original);
    const auto merged(merge(original));
    populate_model(merged, fm);
}

} } } }
