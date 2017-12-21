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
#ifndef DOGEN_MODELING_TYPES_TRANSFORMS_STEREOTYPES_TRANSFORM_HPP
#define DOGEN_MODELING_TYPES_TRANSFORMS_STEREOTYPES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/meta_model/visitor.hpp"
#include "dogen.modeling/types/meta_model/primitive.hpp"
#include "dogen.modeling/hash/meta_model/location_hash.hpp"
#include "dogen.modeling/types/meta_model/endomodel.hpp"
#include "dogen.modeling/types/transforms/context.hpp"

namespace dogen {
namespace modeling {
namespace transforms {

/**
 * @brief Locates objects with stereotypes and performs the required
 * expansion.
 */
class stereotypes_transform final {
private:
    /**
     * @brief If true, this stereotype is part of the list of
     * stereotypes that are valid but require no action from this
     * expander; it is someone else's problem.
     */
    static bool is_stereotype_handled_externally(const std::string& s);

    /**
     * @brief Transforms the static stereotypes of the object, if any
     * exist.
     */
    static void transform_static_stereotypes(meta_model::object& o,
        meta_model::endomodel& em);

    /**
     * @brief Transforms the dynamic stereotypes of the object, if any
     * exist.
     */
    static void transform_dynamic_stereotypes(meta_model::object& o,
        meta_model::endomodel& em);

private:
    struct visitor_details {
        visitor_details(const meta_model::name& b) : base(b) { }
        visitor_details(const meta_model::name& b, const meta_model::name& d) :
            base(b), derived(d) { }

        meta_model::name base;
        boost::optional<meta_model::name> derived;
    };

    static std::unordered_map<meta_model::location, std::list<meta_model::name>>
    bucket_leaves_by_location(const std::list<meta_model::name>& leaves);

    static void add_visitor_to_model(
        const boost::shared_ptr<meta_model::visitor> v,
        meta_model::endomodel& em);

    /**
     * @brief Create a visitor for the object o.
     *
     * @param o visitable object
     * @param leaves cached leaves to avoid look-up.
     *
     * @pre leaves must not be empty.
     */
    static boost::shared_ptr<meta_model::visitor>
    create_visitor(const meta_model::object& o,
        const meta_model::location& l, const meta_model::origin_types ot,
        const std::list<meta_model::name>& leaves);

    /**
     * @brief Injects an accept operation for the given visitor, to
     * the supplied object and all its leaves.
     */
    static void update_visited_leaves(const std::list<meta_model::name>& leaves,
        const visitor_details& vd, meta_model::endomodel& em);

    /**
     * @brief Performs the expansion of the visitable stereotype.
     */
    static void expand_visitable(meta_model::object& o,
        meta_model::endomodel& em);

    /**
     * @brief Try to expand the stereotype as an object
     * template. Returns true on success, false otherwise.
     */
    static bool try_as_object_template(const std::string& s,
        meta_model::object& o, const meta_model::endomodel& em);

    /**
     * @brief Transforms all stereotypes for the object.
     */
    static void transform(meta_model::object& o,
        meta_model::endomodel& em);

    /**
     * @brief Transforms all stereotypes for the primitive.
     */
    static void transform(meta_model::primitive& p);

public:
    /**
     * @brief Expands all stereotypes used in model.
     */
    static void transform(const context& ctx, meta_model::endomodel& em);
};

} } }

#endif
