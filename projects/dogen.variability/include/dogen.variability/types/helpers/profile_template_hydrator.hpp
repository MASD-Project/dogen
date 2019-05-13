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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_PROFILE_TEMPLATE_HYDRATOR_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_PROFILE_TEMPLATE_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen.archetypes/types/location.hpp"
#include "dogen.variability/types/meta_model/name.hpp"
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.variability/types/meta_model/profile_template.hpp"
#include "dogen.variability/types/meta_model/configuration_point_template.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"

namespace dogen::variability::helpers {

/**
 * @brief Reads an unbound configuration from JSON.
 */
class profile_template_hydrator final {
private:
    meta_model::template_kind to_template_kind(const std::string& s) const;

    meta_model::name read_name(const boost::property_tree::ptree& pt) const;

    archetypes::location
    read_archetype_location(const boost::property_tree::ptree& pt) const;

    std::list<meta_model::configuration_point_template>
    read_templates(const boost::property_tree::ptree& pt) const;

    meta_model::profile_template read_stream(std::istream& s) const;

public:
    meta_model::profile_template hydrate(std::istream& s) const;
    meta_model::profile_template hydrate(const boost::filesystem::path& p) const;
};

}

#endif
