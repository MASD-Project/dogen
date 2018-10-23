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
#ifndef DOGEN_ANNOTATIONS_TYPES_TYPE_REPOSITORY_FACTORY_HPP
#define DOGEN_ANNOTATIONS_TYPES_TYPE_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen.annotations/types/type_repository.hpp"
#include "dogen.annotations/types/archetype_location_repository.hpp"
#include "dogen.annotations/types/type_template.hpp"
#include "dogen.annotations/types/type.hpp"

namespace dogen::annotations {

/**
 * @brief Produces a repository.
 */
class type_repository_factory {
private:
    /**
     * @brief Hydrates all the type templates.
     */
    std::list<type_template> hydrate_templates(
        const std::vector<boost::filesystem::path>& data_dirs) const;

    /**
     * @brief Instantiates all templates into field definition
     * instances.
     */
    std::list<type> instantiate_templates(
        const archetype_location_repository& alrp,
        const std::list<type_template>& tts) const;

    /**
     * @brief Index fields into the repository.
     */
    type_repository create_repository(
        const std::list<type>& ts) const;

public:
    /**
     * @brief Generate the repository with the data available in the
     * supplied directories.
     */
    type_repository make(
        const archetype_location_repository& alrp,
        const std::vector<boost::filesystem::path>& data_dirs) const;
};

}

#endif
