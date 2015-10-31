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
#ifndef DOGEN_YARN_TYPES_GENERALIZATION_INDEXER_HPP
#define DOGEN_YARN_TYPES_GENERALIZATION_INDEXER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/relationship_types.hpp"

namespace dogen {
namespace yarn {

class generalization_indexer {
public:
    generalization_indexer() = default;
    generalization_indexer(const generalization_indexer&) = default;
    generalization_indexer(generalization_indexer&&) = default;
    generalization_indexer& operator=(const generalization_indexer&) = default;
    ~generalization_indexer() noexcept = default;

private:
    /**
     * @brief Details of generalization relationships we're interested
     * in.
     */
    struct generalization_details {
        std::unordered_map<name, std::list<name> > leaves;
        std::unordered_map<name, std::list<name> > original_parents;
    };

private:
    /**
     * @brief Returns true if type is a leaf type in an inheritance
     * tree.
     */
    bool is_leaf(const yarn::object& o) const;

private:
    /**
     * @brief Populates the leaves container recursively.
     *
     * @return original parents of the tree we are recursing into.
     */
    std::list<name> recurse_generalization(const intermediate_model& m,
        const yarn::name& leaf, const yarn::object& o,
        generalization_details& d) const;

    /**
     * @brief Obtains all of the details of the generalization
     * relationships.
     */
    generalization_details obtain_details(const intermediate_model& m) const;

    /**
     * @brief Populates properties related to generalization.
     */
    void populate(const generalization_details& d, intermediate_model& m) const;

public:
    /**
     * @brief Indexes the generalisation relationships for this model.
     */
    void index(intermediate_model& m) const;
};

} }

#endif
