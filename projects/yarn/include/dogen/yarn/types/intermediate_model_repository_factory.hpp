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
#ifndef DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_REPOSITORY_FACTORY_HPP
#define DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/yarn/types/descriptor.hpp"
#include "dogen/yarn/types/mapping.hpp"
#include "dogen/yarn/types/frontend_registrar.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/mapping_set_repository.hpp"
#include "dogen/yarn/types/intermediate_model_repository.hpp"

namespace dogen {
namespace yarn {

/**
 *  @brief Creates an intermdiate model repository,
 */
class intermediate_model_repository_factory final {
private:
    /**
     * @brief Obtains all the element id mappings.
     */
    std::unordered_map<std::string, std::list<mapping>> obtain_mappings(
        const std::vector<boost::filesystem::path>& dirs) const;

    /**
     * @brief Obtain the mapping repository.
     */
    mapping_set_repository obtain_mapping_set_repository(
        const std::unordered_map<std::string, std::list<mapping>>&
        mappings) const;

    /**
     * @brief Obtains an intermediate model.
     */
    intermediate_model intermediate_model_for_descriptor(frontend_registrar& rg,
        const descriptor& d) const;

    /**
     * @brief Populats the repository with the target model.
     */
    void populate_target_model(
        const annotations::annotation_groups_factory& agf,
        const annotations::type_repository& atrp,
        const options::knitting_options& ko, frontend_registrar& rg,
        const mapping_set_repository& msrp,
        intermediate_model_repository& imrp) const;

public:
    /**
     * @brief Create the repository.
     */
    intermediate_model_repository
    make(const std::vector<boost::filesystem::path>& dirs,
        const annotations::annotation_groups_factory& agf,
        const annotations::type_repository& atrp,
        const options::knitting_options& ko,
        frontend_registrar& rg) const;

};

} }

#endif
