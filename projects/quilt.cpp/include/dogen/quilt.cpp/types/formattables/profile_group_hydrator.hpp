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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PROFILE_GROUP_HYDRATOR_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PROFILE_GROUP_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <utility>
#include <istream>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/quilt.cpp/types/formattables/profile_types.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class profile_group_hydrator {
private:
    std::forward_list<boost::filesystem::path>
    create_directory_list(const std::forward_list<boost::filesystem::path>&
        data_directories) const;

    profile_types to_profile_type(const std::string v) const;

    decoration_profile
    read_decoration_profile(const boost::property_tree::ptree& pt) const;

    std::pair<std::string, facet_profile>
    read_facet_profile(const boost::property_tree::ptree& pt) const;

    std::pair<std::string, formatter_profile>
    read_formatter_profile(const boost::property_tree::ptree& pt) const;

    std::unordered_map<std::string, facet_profile>
    read_facet_profiles(const boost::property_tree::ptree& pt) const;

    std::unordered_map<std::string, formatter_profile>
    read_formatter_profiles(const boost::property_tree::ptree& pt) const;

    profile_group read_stream(std::istream& s) const;

public:
    profile_group hydrate(std::istream& s) const;

    profile_group hydrate(const boost::filesystem::path& p) const;

    std::unordered_map<std::string, profile_group>
    hydrate(const std::forward_list<boost::filesystem::path>&
        data_directories) const;
};

} } } }

#endif
