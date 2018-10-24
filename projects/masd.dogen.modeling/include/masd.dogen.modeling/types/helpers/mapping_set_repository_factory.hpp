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
#ifndef DOGEN_MODELING_TYPES_HELPERS_MAPPING_SET_REPOSITORY_FACTORY_HPP
#define DOGEN_MODELING_TYPES_HELPERS_MAPPING_SET_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.modeling/types/meta_model/name.hpp"
#include "masd.dogen.modeling/types/helpers/mapping.hpp"
#include "masd.dogen.modeling/types/helpers/mapping_set.hpp"
#include "masd.dogen.modeling/types/helpers/mapping_value.hpp"
#include "masd.dogen.modeling/types/helpers/mapping_set_repository.hpp"

namespace masd::dogen::modeling::helpers {

class mapping_set_repository_factory final {
private:
    /**
     * @brief Obtains all the element id mappings.
     */
    std::unordered_map<std::string, std::list<mapping>> obtain_mappings(
        const std::vector<boost::filesystem::path>& dirs) const;

    /**
     * @brief Ensures the mappings are valid.
     */
    void validate_mappings(const std::unordered_map<std::string,
        std::list<mapping>>& mappings) const;

private:
    void insert(const std::string& lam_id, const meta_model::name& n,
        const meta_model::languages l, std::unordered_map<meta_model::languages,
        std::unordered_map<std::string, meta_model::name>>& map) const;

    void populate_mapping_set(const std::list<mapping>& mappings,
        mapping_set& ms) const;

    mapping_set_repository create_repository(
        const std::unordered_map<std::string,
        std::list<mapping>>& mappings_by_set_name) const;

public:
    mapping_set_repository make(
        const std::vector<boost::filesystem::path>& dirs) const;
};

}

#endif
