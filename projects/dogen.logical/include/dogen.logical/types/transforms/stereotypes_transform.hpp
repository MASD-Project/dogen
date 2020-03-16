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
#include "dogen.logical/types/meta_model/structural/object.hpp"
#include "dogen.logical/types/meta_model/structural/visitor.hpp"
#include "dogen.logical/types/meta_model/structural/primitive.hpp"
#include "dogen.logical/hash/meta_model/location_hash.hpp"
#include "dogen.logical/types/meta_model/model.hpp"
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
    static meta_model::location
    strip_internal_modules(const meta_model::location& l);

    /**
     * @brief Returns true if the well-known stereotype denotes a assets
     * element type, false otherwise.
     */
    static bool is_element_type(const meta_model::static_stereotypes ss);

    /**
     * @brief Transforms the static stereotypes of the object, if any
     * exist.
     */
    static void transform_static_stereotypes(meta_model::structural::object& o,
        meta_model::model& m);

    /**
     * @brief Transforms the dynamic stereotypes of the object, if any
     * exist.
     */
    static void transform_dynamic_stereotypes(meta_model::structural::object& o,
        const meta_model::model& m);

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
        const boost::shared_ptr<meta_model::structural::visitor> v,
        meta_model::model& m);

    /**
     * @brief Create a visitor for the object o.
     *
     * @param o visitable object
     * @param leaves cached leaves to avoid look-up.
     *
     * @pre leaves must not be empty.
     */
    static boost::shared_ptr<meta_model::structural::visitor>
    create_visitor(const meta_model::structural::object& o,
        const meta_model::location& l, const meta_model::origin_types ot,
        const std::list<meta_model::name>& leaves);

    /**
     * @brief Injects an accept operation for the given visitor, to
     * the supplied object and all its leaves.
     */
    static void update_visited_leaves(const std::list<meta_model::name>& leaves,
        const visitor_details& vd, meta_model::model& m);

    /**
     * @brief Performs the expansion of the visitable stereotype.
     */
    static void expand_visitable(meta_model::structural::object& o,
        meta_model::model& m);

    /**
     * @brief Try to expand the stereotype as an object
     * template. Returns true on success, false otherwise.
     */
    static bool try_as_object_template(const std::string& s,
        meta_model::structural::object& o, const meta_model::model& m);

    /**
     * @brief Transforms all stereotypes for the object.
     */
    static void apply(meta_model::structural::object& o, meta_model::model& m);

    /**
     * @brief Transforms all stereotypes for the primitive.
     */
    static void apply(meta_model::structural::primitive& p);

public:
    /**
     * @brief Expands all stereotypes used in model.
     */
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
