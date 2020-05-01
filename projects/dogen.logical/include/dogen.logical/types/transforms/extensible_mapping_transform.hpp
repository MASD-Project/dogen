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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_EXTENSIBLE_MAPPING_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_EXTENSIBLE_MAPPING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/helpers/mapping.hpp"
#include "dogen.logical/types/helpers/mapping_set.hpp"
#include "dogen.logical/types/helpers/mapping_value.hpp"
#include "dogen.logical/types/helpers/mapping_set_repository.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/input_model_set.hpp"
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

class extensible_mapping_transform final {
private:
    /**
     * @brief Retrieve all extensible mappables in the model set.
     */
    static std::unordered_map<std::string,
                       boost::shared_ptr<
                           entities::mapping::extensible_mappable>
                       >
    obtain_mappables(const logical::entities::input_model_set& ms);

    /**
     * @brief Creates all of the element id mappings from the
     * mappables.
     */
    static std::unordered_map<std::string, std::list<helpers::mapping>>
    create_mappings(const std::unordered_map<std::string,
        boost::shared_ptr<entities::mapping::extensible_mappable>>&
        mappables);

    /**
     * @brief Ensures the mappings are valid.
     */
    static void validate_mappings(const std::unordered_map<std::string,
        std::list<helpers::mapping>>& mappings);

private:
    static void insert(const std::string& lam_id, const entities::name& n,
        const entities::technical_space ts,
        std::unordered_map<entities::technical_space,
        std::unordered_map<std::string, entities::name>>& map);

    static void populate_mapping_set(
        const std::list<helpers::mapping>& mappings,
        helpers::mapping_set& ms);

    static helpers::mapping_set_repository create_repository(
        const std::unordered_map<std::string,
        std::list<helpers::mapping>>& mappings_by_set_name);

private:
    static entities::model map(const helpers::mapping_set_repository& msrp,
        const entities::model& src, const entities::technical_space to);

public:
    static logical::entities::input_model_set apply(const context& ctx,
        const logical::entities::input_model_set& src,
        const entities::technical_space to);
};

}

#endif
