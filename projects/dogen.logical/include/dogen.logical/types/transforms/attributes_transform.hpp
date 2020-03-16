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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_ATTRIBUTES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_ATTRIBUTES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/context.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Transformation that specialises in expanding attributes
 * across the model.
 *
 * @section assets_attributes_transform_0 Model requirements
 *
 * The basic expansion of local attributes and of object templates is
 * expected to have taken place.
 *
 * @section assets_attributes_transform_1 Types of attributes
 *
 * There are three sets of attributes the expander is interested in:
 *
 * @li local attributes;
 * @li inherited attributes;
 * @li all attributes.
 *
 * Lets cover each of these in more details.
 *
 * @subsection assets_attributes_transform_11 Local attributes
 *
 * On a natural, pre-expanded state, local attributes encompass only
 * the attributes defined on the class directly. The transform behaves
 * differently depending on whether it is processing an object or an
 * object template.
 *
 * For objects, the job of the expander is to expand the local
 * attributes to include all attributes obtained by instantiating
 * object templates. This is because we treat them no differently from
 * attributes defined in the class for purposes of code generation. As
 * we rely on the object template transform, all we need is the set of
 * all attributes of all object templates we instantiate. Local
 * attributes are useful to define all member variables owned by a
 * class.
 *
 * For object templates, local attributes are untouched. This is for
 * two reasons. First, because we rely on the local attributes of
 * object templates to process the local attributes of objects, as
 * explained above, via object template expansion; thus local
 * attributes provide a quick way to access all the attributes of all
 * object templates one models. The second reason is due to the
 * representation of object templates in source code: there is no
 * requirement for a "meta-object template" - something from which
 * object templates get attributes from. There is nothing above object
 * templates that replicate the relationship we have between object
 * templates and objects. When object templates get expressed in
 * source code - say as C++ concepts - all we require is the set of
 * all attributes for that object template (see below).
 *
 * @subsection assets_attributes_transform_12 Inherited attributes
 *
 * These provide an easy way to look-up which attributes one has
 * inherited and from whom. For objects, the inherited attributes are
 * the "all attribute" set of each parent (see below). They are useful
 * to call parent constructors and the like.
 *
 * For object templates, inherited attributes are not particularly
 * useful. We still index them by, arbitrarily, adding all the local
 * attributes of the parent. However, we haven't yet found a good use
 * case for them.
 *
 * @subsection assets_attributes_transform_13 All attributes
 *
 * The "all attribute" set contains every single attribute. It is the
 * sum all the local attributes with all of the inherited
 * attributes. For objects it is useful for full constructors. For
 * object templates it is effectively the full interface of the object
 * template.
 *
 */
class attributes_transform final {
private:
    /**
     * @brief Returns the object with the given name, or throws.
     */
    static entities::structural::object&
    find_object(const entities::name& n, entities::model& m);

    /**
     * @brief Returns the object template with the given name, or
     * throws.
     */
    static entities::structural::object_template&
    find_object_template(const entities::name& n, entities::model& m);

private:
    /**
     * @brief Expands a specific object.
     */
    static void expand_object(entities::structural::object& o,
        entities::model& m, std::unordered_set<std::string>& processed_ids);

    /**
     * @brief Expands all objects in the model.
     */
    static void expand_objects(entities::model& m);

    /**
     * @brief Expands a specific object template
     */
    static void expand_object_template(
        entities::structural::object_template& ot, entities::model& m,
        std::unordered_set<std::string>& processed_ids);

    /**
     * @brief Expands all object templates in the model.
     */
    static void expand_object_templates(entities::model& m);

public:
    /**
     * @brief Indexes the supplied model.
     */
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
