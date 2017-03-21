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
#ifndef DOGEN_YARN_TYPES_STEREOTYPES_EXPANDER_FWD_HPP
#define DOGEN_YARN_TYPES_STEREOTYPES_EXPANDER_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/hash/location_hash.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Locates objects with stereotypes and performs the required
 * expansion.
 */
class stereotypes_expander {
private:
    /**
     * @brief If true, this stereotype is part of the list of
     * stereotypes that are valid but require no action from this
     * expander; it is someone else's problem.
     */
    bool is_stereotype_handled_externally(const std::string& s) const;

private:
    struct visitor_details {
        visitor_details(const name& b) : base(b) { }
        visitor_details(const name& b, const name& d) : base(b), derived(d) { }

        name base;
        boost::optional<name> derived;
    };

    std::unordered_map<location, std::list<name> >
    bucket_leaves_by_location(const std::list<name>& leaves) const;

    void add_visitor_to_model(const visitor& v, intermediate_model& im) const;

    /**
     * @brief Create a visitor for the object o.
     *
     * @param o visitable object
     * @param leaves cached leaves to avoid look-up.
     *
     * @pre leaves must not be empty.
     */
    visitor create_visitor(const object& o, const location& l,
        const origin_types ot, const std::list<name>& leaves) const;

    /**
     * @brief Injects an accept operation for the given visitor, to
     * the supplied object and all its leaves.
     */
    void update_visited_leaves(const std::list<name>& leaves,
        const visitor_details& vd, intermediate_model& im) const;

    /**
     * @brief Performs the expansion of the visitable stereotype.
     */
    void expand_visitable(object& o, intermediate_model& im) const;

    /**
     * @brief Try to expand the stereotype as a concept. Returns true
     * on success, false otherwise.
     */
    bool try_expand_concept(
        const std::string& s, object& o, const intermediate_model& im) const;

    /**
     * @brief Expands all stereotypes for the object.
     */
    void expand(object& o, intermediate_model& im) const;

    /**
     * @brief Expands all stereotypes for the primitive.
     */
    void expand(primitive& p) const;

public:
    /**
     * @brief Expands all stereotypes used in model.
     */
    void expand(intermediate_model& im);
};

} }

#endif
