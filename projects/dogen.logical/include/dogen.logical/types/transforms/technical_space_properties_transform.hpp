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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_TECHNICAL_SPACE_PROPERTIES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_TECHNICAL_SPACE_PROPERTIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/optional/optional.hpp>
#include "dogen.identification/types/entities/logical_name_tree.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.logical/types/features/technical_space_properties.hpp"
#include "dogen.logical/types/entities/structural/technical_space_properties.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Reads technical space specific properties.
 */
class technical_space_properties_transform final {
private:
    static boost::optional<entities::structural::technical_space_properties>
    obtain_properties(
        const features::technical_space_properties::feature_group& fg,
        entities::element& e);

    static std::unordered_map<identification::entities::logical_id,
                              entities::structural::technical_space_properties>
    obtain_properties(const variability::entities::feature_model& fm,
        entities::model& m);

private:
    static void
    walk_name_tree(const bool is_cpp_standard_98,
        const identification::entities::logical_name_tree& nt,
        const bool top_level, const std::unordered_map<
        identification::entities::logical_id,
        entities::structural::technical_space_properties>& src_tsps,
        entities::structural::technical_space_properties& dest_tsp);

    static entities::structural::technical_space_properties
    compute_properties(const bool is_cpp_standard_98,
        const std::unordered_map<identification::entities::logical_id,
        entities::structural::technical_space_properties>& src_tsps,
        const std::list<logical::entities::attribute>& attrs);

    static void populate_properties(
        const std::unordered_map<identification::entities::logical_id,
        entities::structural::technical_space_properties>& src_tsps,
        entities::model& m);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
