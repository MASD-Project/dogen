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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_STEREOTYPES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_STEREOTYPES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/hash/entities/location_hash.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/context.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Locates objects with stereotypes and performs the required
 * expansion.
 */
class stereotypes_transform final {
private:
    /**
     * @brief Strips the internal modules of the supplied location.
     */
    static entities::location
    strip_internal_modules(const entities::location& l);

    /**
     * @brief Returns true if the well-known stereotype denotes a
     * logical element type, false otherwise.
     */
    static bool is_element_type(const entities::static_stereotypes ss);

    /**
     * @brief Transforms the static stereotypes of the object, if any
     * exist.
     */
    static void transform_static_stereotypes(entities::structural::object& o,
        entities::model& m);

    /**
     * @brief Transforms the dynamic stereotypes of the object, if any
     * exist.
     */
    static void transform_dynamic_stereotypes(entities::structural::object& o,
        const entities::model& m);

private:
    struct visitor_details {
        visitor_details(const entities::name& b) : base(b) { }
        visitor_details(const entities::name& b, const entities::name& d) :
            base(b), derived(d) { }

        entities::name base;
        boost::optional<entities::name> derived;
    };

    static std::unordered_map<entities::location, std::list<entities::name>>
    bucket_leaves_by_location(const std::list<entities::name>& leaves);

    static void add_visitor_to_model(
        const boost::shared_ptr<entities::structural::visitor> v,
        entities::model& m);

    /**
     * @brief Create a visitor for the object o.
     *
     * @param o visitable object
     * @param leaves cached leaves to avoid look-up.
     *
     * @pre leaves must not be empty.
     */
    static boost::shared_ptr<entities::structural::visitor>
    create_visitor(const entities::structural::object& o,
        const entities::location& l, const entities::origin_types ot,
        const std::list<entities::name>& leaves);

    /**
     * @brief Injects an accept operation for the given visitor, to
     * the supplied object and all its leaves.
     */
    static void update_visited_leaves(const std::list<entities::name>& leaves,
        const visitor_details& vd, entities::model& m);

    /**
     * @brief Performs the expansion of the visitable stereotype.
     */
    static void expand_visitable(entities::structural::object& o,
        entities::model& m);

    /**
     * @brief Try to expand the stereotype as an object
     * template. Returns true on success, false otherwise.
     */
    static bool try_as_object_template(const std::string& s,
        entities::structural::object& o, const entities::model& m);

    /**
     * @brief Transforms all stereotypes for the object.
     */
    static void apply(entities::structural::object& o, entities::model& m);

    /**
     * @brief Transforms all stereotypes for the primitive.
     */
    static void apply(entities::structural::primitive& p);

public:
    /**
     * @brief Expands all stereotypes used in model.
     */
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
