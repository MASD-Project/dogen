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
#ifndef DOGEN_YARN_TYPES_PROPERTY_INDEXER_HPP
#define DOGEN_YARN_TYPES_PROPERTY_INDEXER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_set>
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Information indexer that specialises in indexing
 * properties across the model.
 *
 * @section yarn_property_indexer_0 Model requirements
 *
 * The concept indexer expects to receive a partial model such as ones
 * coming straight out of Dia to Yarn transformation. The indexing of
 * concepts is expected to have taken place.
 *
 * @section yarn_property_indexer_1 Types of properties
 *
 * There are three sets of properties the indexer is interested in:
 *
 * @li local properties;
 * @li inherited properties;
 * @li all properties.
 *
 * Lets cover each of these in more details.
 *
 * @subsection yarn_property_indexer_11 Local properties
 *
 * On a natural, pre-indexed state, local properties encompass only
 * the properties defined on the class directly. The indexer behaves
 * differently depending on whether it is indexing an object or a
 * concept.
 *
 * For objects, the job of the indexer is to expand the local
 * properties to include all properties obtained by modeling
 * concepts. This is because we treat them no differently from
 * properties defined in the class for purposes of code generation. As
 * we rely on concept expansion, all we need is the set of all
 * properties of all concepts we model. Local properties are useful to
 * define all member variables owned by a class.
 *
 * For concepts, local properties are untouched. This is for two
 * reasons. First, because we rely on the local properties of concepts
 * to process the local properties of objects, as explained above, via
 * concept expansion; thus local properties provide a quick way to
 * access all the properties of all concepts one models. The second
 * reason is due to the representation of concepts in source code:
 * there is no requirement for a "meta-concept" - something from which
 * concepts get properties from. There is nothing above concepts that
 * replicate the relationship we have between concepts and
 * objects. When concepts get expressed in source code, all we require
 * is the set of all properties for that concept (see below).
 *
 * @subsection yarn_property_indexer_12 Inherited properties
 *
 * These provide an easy way to look-up which properties one has
 * inherited and from whom. For objects, the inherited properties are
 * the "all property" set of each parent (see below). They are useful
 * to call parent constructors and the like.
 *
 * For concepts, inherited properties are not particularly useful. We
 * still index them by, arbitrarily, adding all the local properties
 * of the parent. However, we still haven't found a good use for them.
 *
 * @subsection yarn_property_indexer_13 All properties
 *
 * The "all property" set contains every single property. It is the
 * sum all the local properties with all of the inherited
 * properties. For objects it is useful for full constructors. For
 * concepts it is effectively the full interface of the concept.
 *
 */
class property_indexer {
public:
    property_indexer() = default;
    property_indexer(const property_indexer&) = default;
    property_indexer(property_indexer&&) = default;
    property_indexer& operator=(const property_indexer&) = default;

public:
    virtual ~property_indexer() noexcept { }

private:
    /**
     * @brief Returns the object with the given name, or throws.
     */
    object& find_object(const name& n, intermediate_model& m);

    /**
     * @brief Returns the concept with the given name, or throws.
     */
    concept& find_concept(const name& n, intermediate_model& m);

private:
    /**
     * @brief Indexes a specific object.
     */
    void index_object(object& o, intermediate_model& m,
        std::unordered_set<name>& processed_names);

    /**
     * @brief Indexes all objects in the model.
     */
    void index_objects(intermediate_model& m);

    /**
     * @brief Populates index information in a concept.
     */
    void index_concept(concept& c, intermediate_model& m,
        std::unordered_set<name>& processed_names);

    /**
     * @brief Indexes all concepts in the model.
     */
    void index_concepts(intermediate_model& m);

public:
    /**
     * @brief Indexes the supplied model.
     */
    void index(intermediate_model& m);
};

} }

#endif
