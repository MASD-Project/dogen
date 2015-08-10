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
#ifndef DOGEN_TACK_TYPES_CONCEPT_INDEXER_HPP
#define DOGEN_TACK_TYPES_CONCEPT_INDEXER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_set>
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/types/relationship_types.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Information indexer that specialises in indexing
 * concept-related relationships across the model.
 *
 * @section tack_concept_indexer_0 Model requirements
 *
 * The concept indexer expects to receive a partial model such as ones
 * coming straight out of Dia to TACK transformation.
 *
 * @section tack_concept_indexer_1 First stage: indexing concepts
 *
 * The concept indexer only touches two types of model elements:
 * concepts and abstract objects. This is because these are the only
 * two elements involved in relationships that involve concepts.
 *
 * The concept indexer starts by processing all concepts. Each concept
 * goes through two steps: @e expansion and @e reduction. Expansion is
 * defined as adding to each refined concept the set of all concepts
 * implied by the refinement graph of that concept: that is, the
 * concept itself, the concepts that the concept refines (lets call it
 * @e parents), the concepts that the parents refine and so on.
 *
 * Once the expansion is complete, reduction takes place: that is, all
 * duplicate concepts are removed. The final result is known as the @e
 * reduced @e concept @e set.
 *
 * Note that we use the word @e set here in the mathematical sense, as
 * implementation-wise we use lists manage these relationships. This
 * is because we aim to preserve order where possible; this is to
 * avoid having the code generation move (potentially dramatically)
 * every time any alteration is done to the concept hierarchy.
 *
 * @section tack_concept_indexer_2 Second stage: indexing objects
 *
 * The concept indexer is also responsible for updating the modeled
 * concepts in abstract objects. Thus only objects that are part of
 * such relationships are affected. For example a child which does not
 * model any concepts is not affected, even if its parent does model
 * concepts.
 *
 * Note that object indexing must be done after the concept indexing
 * described above as it depends on it.
 *
 * For objects which do not have parents, the operation is simple: for
 * a given object o, we just need to compute its reduced concept set
 * implied by its modeled concepts.
 *
 * For objects with parents things are slightly more complicated. We
 * must first compute the reduced concept set implied by all its
 * parents; this includes @e all modeled concepts found in the
 * entirety of the inheritance graph of a given object. Lets call that
 * set P. We then take the set of all concepts modeled by the object
 * directly (say R). The final set of modeled concepts for the object
 * is given by the set difference between R and S; that is, we remove
 * all concepts in R which are part of S - leaving those that only
 * exist in R but not in S.
 *
 */
class concept_indexer {
public:
    concept_indexer() = default;
    concept_indexer(const concept_indexer&) = default;
    concept_indexer(concept_indexer&&) = default;
    concept_indexer& operator=(const concept_indexer&) = default;

public:
    virtual ~concept_indexer() noexcept { }

private:
    /**
     * @brief Returns the object with the given name, or throws.
     */
    object& find_object(const name& n, model& m);

    /**
     * @brief Finds the relationship container, or throws.
     */
    std::list<name>&
    find_relationships(const relationship_types rt, object& o);

    /**
     * @brief Returns the concept with the given name, or throws.
     */
    concept& find_concept(const name& n, model& m);

    /**
     * @brief Removes duplicate names, preserving the original order
     * of elements in the list.
     */
    void remove_duplicates(std::list<name>& names) const;

private:
    /**
     * @brief Indexes a specific object.
     */
    void index_object(object& o, model& m,
        std::unordered_set<tack::name>& processed_names);

    /**
     * @brief Indexes all objects in the model.
     */
    void index_objects(model& m);

    /**
     * @brief Populates index information in a concept.
     */
    void index_concept(concept& c, model& m,
        std::unordered_set<name>& processed_names);

    /**
     * @brief Indexes all concepts in the model.
     */
    void index_concepts(model& m);

public:
    /**
     * @brief Indexes the supplied model.
     */
    void index(model& m);
};

} }

#endif
