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
#ifndef DOGEN_YARN_TYPES_ASSOCIATION_INDEXER_HPP
#define DOGEN_YARN_TYPES_ASSOCIATION_INDEXER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_set>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/relationship_types.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Information indexer that specialises in indexing
 * associations for objects.
 *
 * @section yarn_association_indexer_0 Requirements
 *
 * The indexing of properties is expected to have taken place.
 *
 * @section yarn_property_indexer_1 Indexing Process
 *
 * The indexer goes through all properties in objects and, for every
 * nested qualified name, unpacks all the associations implied by
 * their presence.
 *
 * Associations are of two types: @e regular or @e pointer. This
 * distinction is required due to the usage of the association at code
 * generation time.
 *
 * A @e regular association means a full type definition is required
 * to be available due to the association. A @e pointer definition
 * means that the type is used via pointer and as such a forward
 * declaration may suffice.
 */
class association_indexer {
public:
    association_indexer() = default;
    association_indexer(const association_indexer&) = default;
    association_indexer(association_indexer&&) = default;
    association_indexer& operator=(const association_indexer&) = default;
    ~association_indexer() noexcept = default;

private:
    /**
     * @brief Removes duplicate names, preserving the original order
     * of elements in the list.
     *
     * @param names list of names to process
     * @param processed list of names that have already been processed
     * somewhere else, if any.
     */
    void remove_duplicates(std::list<name>& names,
        std::unordered_set<name> processed =
        std::unordered_set<name>()) const;

    /**
     * @brief Iterates through the nested name recursively, picking
     * up associations as it goes along.
     */
    void recurse_nested_names(const intermediate_model& m, object& o,
        const nested_name& nn, bool& is_pointer) const;

private:
    /**
     * @brief Indexes a specific object.
     */
    void index_object(const intermediate_model& m, object& o) const;

public:
    /**
     * @brief Indexes all association relationships.
     */
    void index(intermediate_model& m) const;
};

} }

#endif
