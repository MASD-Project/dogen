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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_PHYSICAL_TO_LOGICAL_POPULATION_TRANSFORM_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_PHYSICAL_TO_LOGICAL_POPULATION_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.text/types/entities/model.hpp"
#include "dogen.text/types/transforms/context_fwd.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"


namespace dogen::orchestration::transforms {

/**
 * @brief Populate logical elements that require information from the
 * physical dimension.
 */
class physical_to_logical_population_transform final {
private:
    static identification::entities::technical_space
    get_technical_space(const logical::entities::model& m);

    static std::list<std::string>
    make_odb_databases(const text::entities::model& m);

    static std::unordered_set<identification::entities::logical_meta_id>
    meta_names_for_project_items();
    static bool is_project_item(
        const identification::entities::logical_meta_id& mn);

private:
    static void transform_build_files(text::entities::model& m);
    static void transform_project_items(text::entities::model& m);

public:
    static void apply(const text::transforms::context& ctx,
        text::entities::model& m);
};

}

#endif
