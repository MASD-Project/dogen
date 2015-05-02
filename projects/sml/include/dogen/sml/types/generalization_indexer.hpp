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
#ifndef DOGEN_SML_TYPES_GENERALIZATION_INDEXER_HPP
#define DOGEN_SML_TYPES_GENERALIZATION_INDEXER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/relationship_types.hpp"

namespace dogen {
namespace sml {

class generalization_indexer {
public:
    generalization_indexer() = default;
    generalization_indexer(const generalization_indexer&) = default;
    generalization_indexer(generalization_indexer&&) = default;
    generalization_indexer& operator=(const generalization_indexer&) = default;
    ~generalization_indexer() noexcept = default;

private:
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

public:
    /**
     * @brief Indexes the generalisation relationships for this model.
     */
    void index(model& m) const;
};

} }

#endif
