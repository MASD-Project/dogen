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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_ASSOCIATIONS_TRANSFORM_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_ASSOCIATIONS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_set>
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/hash/meta_model/name_hash.hpp"
#include "masd.dogen.coding/types/meta_model/endomodel.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"

namespace masd::dogen::coding::transforms {

/**
 * @brief Transform that specialises in indexing associations for
 * objects.
 *
 * @section coding_association_expander_0 Requirements
 *
 * The expansion of local attributes is expected to have taken place.
 *
 * @section coding_attribute_indexer_1 Indexing Process
 *
 * The expander goes through all attributes in objects and, for every
 * name tree, unpacks all the associations implied by their presence.
 *
 * Associations are of two types: @e regular or @e weak. This
 * distinction is required due to the usage of the association at code
 * generation time.
 *
 * A @e regular association means a full type definition is required
 * to be available due to the association. A @e weak association means
 * that the type is used via pointer and as such a forward declaration
 * may suffice.
 */
class associations_transform final {
private:
    /**
     * @brief Removes duplicate names, preserving the original order
     * of elements in the list.
     *
     * @param names list of names to process
     * @param processed list of names that have already been processed
     * somewhere else, if any.
     */
    static void remove_duplicates(std::list<meta_model::name>& names,
        std::unordered_set<meta_model::name> processed =
        std::unordered_set<meta_model::name>());

    /**
     * @brief Walks through the name tree, picking up associations as
     * it goes along.
     */
    static void walk_name_tree(const meta_model::endomodel& em,
        meta_model::object& o, const meta_model::name_tree& nt,
        const bool inherit_opaqueness_from_parent);

private:
    /**
     * @brief Expands a specific object.
     */
    static void expand_object(const meta_model::endomodel& em,
        meta_model::object& o);

public:
    /**
     * @brief Expands all association relationships.
     */
    static void transform(const context& ctx, meta_model::endomodel& em);
};

}

#endif
