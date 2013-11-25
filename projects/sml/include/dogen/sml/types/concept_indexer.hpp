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
#ifndef DOGEN_SML_TYPES_CONCEPT_INDEXER_HPP
#define DOGEN_SML_TYPES_CONCEPT_INDEXER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_set>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/relationship_types.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Information indexer that specialises in expanding
 * concept-related relationships across the model.
 *
 * The concept_indexer expects to receive a partial model such as ones
 * coming straight out of Dia to SML transformation. Its job is to
 * take the existing data and to expand it, duplicating information
 * across the model to make it easier to access without requiring any
 * additional look-ups.
 *
 * The concept indexer is responsible for the following concrete
 * tasks:
 *
 * @li expand the refined concepts in all concepts which refine other
 * concepts.
 *
 * @li expand the modeled concepts in all types which model concepts,
 * taking into account refinements.
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
     * @brief Returns the object with the given qname, or throws.
     */
    abstract_object& find_object(const qname& qn, model& m);

    /**
     * @brief Finds the relationship container, or throws.
     */
    std::list<qname>& find_relationships(const relationship_types rt,
        abstract_object& o);

    /**
     * @brief Returns the concept with the given qname, or throws.
     */
    concept& find_concept(const qname& qn, model& m);

    /**
     * @brief Removes duplicate qnames, preserving the original order
     * of elements in the list.
     */
    void remove_duplicates(std::list<qname>& names) const;

private:
    /**
     * @brief Indexes a specific object.
     */
    void index_object(abstract_object& parent, abstract_object& leaf,
        model& m);

    /**
     * @brief Indexes all objects in the model.
     */
    void index_objects(model& m);

    /**
     * @brief Populates index information in a concept.
     */
    void index_concept(concept& c, model& m,
        std::unordered_set<sml::qname>& processed_qnames);

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
