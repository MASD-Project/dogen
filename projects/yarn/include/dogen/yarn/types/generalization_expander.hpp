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
#ifndef DOGEN_YARN_TYPES_GENERALIZATION_EXPANDER_HPP
#define DOGEN_YARN_TYPES_GENERALIZATION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/name.hpp"

namespace dogen {
namespace yarn {

class generalization_expander {
private:
    std::unordered_set<std::string>
    obtain_parent_ids(const intermediate_model& im) const;

    void populate_properties_up_the_generalization_tree(
        const yarn::name& leaf, intermediate_model& im,
        yarn::object& o) const;

    void populate_generalizable_properties(
        const std::unordered_set<std::string>& parent_ids,
        intermediate_model& im) const;

    void sort_leaves(intermediate_model& im) const;

public:
    void expand_new(intermediate_model& im) const;

private:
    /**
     * @brief Details of generalization relationships we're interested
     * in.
     */
    struct generalization_details {
        std::unordered_map<std::string, std::list<name> > leaves;
        std::unordered_map<std::string, boost::optional<name> > root_parents;
        std::unordered_set<std::string> parents;
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
     * @return Root parents of the tree we are recursing into.
     */
    boost::optional<name> recurse_generalization(const intermediate_model& im,
        const yarn::name& leaf, const yarn::object& o,
        generalization_details& d) const;

    /**
     * @brief Obtains all of the details of the generalization
     * relationships.
     */
    generalization_details obtain_details(const intermediate_model& im) const;

    /**
     * @brief Populates properties related to generalization.
     */
    void populate(const generalization_details& d,
        intermediate_model& im) const;

public:
    /**
     * @brief Expands the generalization relationships for this model.
     */
    void expand(intermediate_model& im) const;
};

} }

#endif
