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
#ifndef DOGEN_SML_TYPES_INDEXER_HPP
#define DOGEN_SML_TYPES_INDEXER_HPP

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
 * @brief Populates all of the indexing data structures across the
 * model.
 *
 * The indexer expects to receive a partial model such as ones coming
 * straight out of Dia to SML transformation.
 *
 * The indexer as the following responsibilities:
 *
 * @li populate the original parents of all children involved in
 * inheritance relationships;
 *
 * @li populate the leaves of all parents in inheritance
 * relationships;
 *
 * @li expand the modeled concepts in all types which model concepts,
 * taking into account refinements.
 *
 * @li populate the inherited properties and all properties containers
 * of all types.
 */
class indexer {
public:
    indexer() = default;
    indexer(const indexer&) = default;
    indexer(indexer&&) = default;
    indexer& operator=(const indexer&) = default;

public:
    virtual ~indexer() noexcept { }

private:
    /**
     * @brief Find the object with the given qname, or throws.
     */
    abstract_object& find_object(const qname& qn, model& m);

    /**
     * @brief Finds the relationship container, or throws.
     */
    std::list<qname>& find_relationships(const relationship_types rt,
        abstract_object& o);

private:
    /**
     * @brief Given a concept, adds all the properties associated with
     * that concept.
     */
    void properties_for_concept(const sml::qname& qn,
        std::list<sml::property>& properties,
        std::unordered_set<sml::qname>& processed_qnames, const model& m) const;

    /**
     * @brief Given an initial qname and a list of concepts, it
     * expands it to take into account all the refinement
     * relationships these may be part of.
     */
    void expand_concept_hierarchy(const model& m, const qname& qn,
        std::list<qname>& concepts) const;

    /**
     * @brief Populates the all properties container.
     */
    void populate_all_properties(abstract_object& o, const model& m);

private:
    /**
     * @brief Populates the modeled concepts relationship of every
     * type involved in modeling concepts.
     */
    void index_modeled_concepts(model& m);

    /**
     * @brief Indexes inheritance information for the leaf and all of
     * its parents.
     */
    void index_inheritance(abstract_object& parent, abstract_object& leaf,
        model& m);

    /**
     * @brief Indexes information related to inheritance relationships
     * across all objects in the model.
     */
    void index_inheritance(model& m);

    /**
     * @brief Indexes information related to refinement relationships
     * for a given concept.
     */
    void index_refinements(concept& c, model& m,
        std::unordered_set<sml::qname>& processed_qnames);

    /**
     * @brief Indexes information related to refinement relationships
     * across all concepts the model.
     */
    void index_refinements(model& m);

private:
    void index(abstract_object& o);

public:
    /**
     * @brief Indexes the supplied model.
     */
    void index(model& m);
};

} }

#endif
