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
#ifndef DOGEN_TACK_TYPES_GENERALIZATION_INDEXER_HPP
#define DOGEN_TACK_TYPES_GENERALIZATION_INDEXER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/types/qname.hpp"
#include "dogen/tack/hash/qname_hash.hpp"
#include "dogen/tack/types/relationship_types.hpp"

namespace dogen {
namespace tack {

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
        std::unordered_map<qname, std::list<qname> > leaves;
        std::unordered_map<qname, std::list<qname> > original_parents;
    };

private:
    /**
     * @brief Returns true if type is a leaf type in an inheritance
     * tree.
     */
    bool is_leaf(const tack::object& o) const;

private:
    /**
     * @brief Populates the leaves container recursively.
     *
     * @return original parents of the tree we are recursing into.
     */
    std::list<qname> recurse_generalization(
        const model& m, const tack::qname& leaf, const tack::object& o,
        generalization_details& d) const;

    /**
     * @brief Obtains all of the details of the generalization
     * relationships.
     */
    generalization_details obtain_details(const model& m) const;

    /**
     * @brief Populates properties related to generalization.
     */
    void populate(const generalization_details& d, model& m) const;

public:
    /**
     * @brief Indexes the generalisation relationships for this model.
     */
    void index(model& m) const;
};

} }

#endif
