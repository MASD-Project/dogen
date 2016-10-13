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
#ifndef DOGEN_ANNOTATIONS_TYPES_PROFILER_HPP
#define DOGEN_ANNOTATIONS_TYPES_PROFILER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/profile.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/ownership_hierarchy_repository.hpp"

namespace dogen {
namespace annotations {

class profiler {
private:
    struct prof_ann {
        profile prof;
        annotation ann;
        bool merged;
    };

private:
    std::vector<boost::filesystem::path> to_profile_directories(
        const std::vector<boost::filesystem::path>& data_dirs) const;

    std::list<profile> hydrate_profiles(
        const std::vector<boost::filesystem::path>& profile_dirs) const;

    std::unordered_map<std::string, prof_ann>
    create_prof_ann_map(const std::list<profile>& profiles) const;

    void validate_profiles(const ownership_hierarchy_repository& ohrp,
        const std::unordered_map<std::string, prof_ann>& pa) const;

    void instantiate_value_templates(
        std::unordered_map<std::string, prof_ann>& pa) const;

    void walk_up_parent_tree_and_merge(
        const std::string& current,
        std::unordered_map<std::string, prof_ann>& pa) const;

    void merge(std::unordered_map<std::string, prof_ann>& pa) const;

    std::unordered_map<std::string, prof_ann>
    create_annotation_map(
        const std::unordered_map<std::string, prof_ann>& pa) const;

public:
    std::unordered_map<std::string, annotation>
    generate(const std::vector<boost::filesystem::path>& data_dirs,
        const ownership_hierarchy_repository& ohrp) const;
};

} }

#endif
