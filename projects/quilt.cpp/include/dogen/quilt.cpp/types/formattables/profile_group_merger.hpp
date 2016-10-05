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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PROFILE_GROUP_MERGER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PROFILE_GROUP_MERGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include "dogen/quilt.cpp/types/formattables/profile_group.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class profile_group_merger {
private:
    decoration_profile merge(const decoration_profile& parent,
        const decoration_profile& child) const;

    profile_group
    merge(const profile_group& parent, const profile_group& child) const;

    profile_group walk_up_parent_tree_and_process(const std::string& current,
        const std::unordered_map<std::string, profile_group>& original,
        std::unordered_map<std::string, profile_group>& done) const;

public:
    std::unordered_map<std::string, profile_group>
    merge(const std::unordered_map<std::string, profile_group>& original) const;
};

} } } }

#endif
