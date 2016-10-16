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
#ifndef DOGEN_ANNOTATIONS_TYPES_PROFILE_HYDRATOR_HPP
#define DOGEN_ANNOTATIONS_TYPES_PROFILE_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include "dogen/annotations/types/name.hpp"
#include "dogen/annotations/types/template_kinds.hpp"
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/annotations/types/entry_template.hpp"
#include "dogen/annotations/types/profile.hpp"

namespace dogen {
namespace annotations {

class profile_hydrator {
private:
    template_kinds to_template_kind(const std::string& s) const;

    name read_name(const boost::property_tree::ptree& pt) const;

    archetype_location
    read_ownership_hierarchy(const boost::property_tree::ptree& pt) const;

    std::list<entry_template>
    read_templates(const boost::property_tree::ptree& pt) const;

    profile read_stream(std::istream& s) const;

public:
    profile hydrate(std::istream& s) const;
    profile hydrate(const boost::filesystem::path& p) const;

};

} }

#endif
