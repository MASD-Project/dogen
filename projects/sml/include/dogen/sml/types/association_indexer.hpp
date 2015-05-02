/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_SML_TYPES_ASSOCIATION_INDEXER_HPP
#define DOGEN_SML_TYPES_ASSOCIATION_INDEXER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_set>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/relationship_types.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Information indexer that specialises in indexing
 * associations for objects.
 *
 * @section sml_association_indexer_0 Model requirements
 *
 * The association indexer expects to receive a partial model such as
 * ones coming straight out of Dia to SML transformation. The indexing
 * of properties is expected to have taken place.
 *
 * @section sml_property_indexer_1 Indexing Process
 *
 * The indexer goes through all properties in objects and, for every
 * nested qualified name, unpacks all the associations implied by
 * their presence.
 *
 * Associations are of two types: @e regular or @e pointer. This
 distinction is required due to the usage of the association at code
 generation time.
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
     * @brief Removes duplicate qnames, preserving the original order
     * of elements in the list.
     *
     * @param names list of names to process
     * @param processed list of names that have already been processed
     * somewhere else, if any.
     */
    void remove_duplicates(std::list<qname>& names,
        std::unordered_set<qname> processed =
        std::unordered_set<qname>()) const;

    /**
     * @brief Iterates through the nested qname recursively, picking
     * up associations as it goes along.
     */
    void recurse_nested_qnames(const model& m, object& o,
        const nested_qname& nqn, bool& is_pointer) const;

    /**
     * @brief Populates the leaves container recursively.
     */
    void add_leaf(const model& m, const sml::qname& leaf, const sml::object& o,
        std::unordered_map<qname, std::list<qname> >& leaves) const;

    /**
     * @brief Computes all the leaves for all parents.
     */
    std::unordered_map<qname, std::list<qname> >
    obtain_leaves(const model& m) const;

    /**
     * @brief Populates the leaves replationships.
     */
    void populate_leaves(const std::unordered_map<qname, std::list<qname> >&
        leaves, model& m) const;

private:
    /**
     * @brief Indexes a specific object.
     */
    void index_object(const model& m, object& o) const;

public:
    /**
     * @brief Indexes the leaves for this model.
     */
    void index_leaves(model& m) const;

    /**
     * @brief Handles all relationships other than leaves.
     */
    void index_non_leaves_relationships(model& m) const;
};

} }

#endif
