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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_OBJECT_TEMPLATES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_OBJECT_TEMPLATES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_set>
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/meta_model/model.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Transform that specialises in indexing
 * object-template-related relationships across the model.
 *
 * @section assets_object_templates_transform_0 Model requirements
 *
 * The object templates transform expects to receive a merged
 * endmodel, but in practice it makes no requirements in terms of any
 * dependent transforms.
 *
 * @section assets_object_templates_transform_1 Transformation
 *
 * The object templates expander only touches two types of model
 * elements: object templates and objects. This is because these are
 * the only two elements involved in relationships that deal with
 * object templates. Each of these are processed differently.
 *
 * @subsection assets_object_templates_transform_11 First stage: expanding object templates
  *
 * The object templates transform starts by processing all object
 * templates. Each object template goes through two steps: @e
 * expansion and @e reduction. Expansion is defined as adding to each
 * inherited object template the set of all object templates implied
 * by the inheritance graph of that object template: that is, the
 * object template itself, the object templates that the object
 * template inherits from (lets call it @e parents), the object
 * templates that the parents inherits from and so on.
 *
 * Once the expansion is complete, reduction takes place: that is, all
 * duplicate object templates are removed. The final result is known
 * as the _reduced object templates set_.
 *
 * Note that we use the word @e set here in the mathematical sense, as
 * implementation-wise we use lists manage these relationships. This
 * is because we aim to preserve order where possible; this is to
 * avoid having the code generation move (potentially dramatically)
 * every time any alteration is done to the object templates
 * hierarchy.
 *
 * @subsection assets_object_templates_transform_12 Second stage: expand objects
 *
 * The object templates expander is also responsible for updating the
 * instantiated object templates in an object - if any. Thus, only
 * objects that are part of such relationships are affected. For
 * example a child which does not instantiate any object templates is
 * not affected, even if its parent does instantiate object templates.
 *
 * Note that object expansion must be done after the object templates
 * expansion described above, as it depends on it.
 *
 * For objects which do not have parents, the operation is simple: for
 * a given object @e o, we just need to compute the reduced object
 * template set, as implied by the object templates it instantiates.
 *
 * For objects with parents things are slightly more complicated. We
 * must first compute the reduced object template set implied by all
 * its parents; this includes @e all instantiated object templates
 * found in the entirety of the inheritance graph of a given
 * object. Lets call that set @e P. We then take the set of all object
 * templates instantiated by the object directly (say @e R). The final
 * set of instantiated object templates for the object is given by the
 * set difference between @e R and @e S; that is, we remove all object
 * templates in @e R which are part of @e S - leaving those that only
 * exist in @e R but not in @e S.
 *
 */
class object_templates_transform final {
private:
    /**
     * @brief Returns the object with the given name, or throws.
     */
    static  meta_model::structural::object&
    find_object(const meta_model::name& n, meta_model::model& m);

    /**
     * @brief Returns the object template with the given name, or
     * throws.
     */
    static meta_model::structural::object_template& resolve_object_template(
        const meta_model::name& owner,
        const meta_model::name& object_template_name,
        meta_model::model& m);

    /**
     * @brief Removes duplicate names, preserving the original order
     * of elements in the list.
     */
    static void remove_duplicates(std::list<meta_model::name>& names);

private:
    /**
     * @brief Expands a specific object.
     */
    static void expand_object(meta_model::structural::object& o,
        meta_model::model& m,
        std::unordered_set<meta_model::name>& processed_names);

    /**
     * @brief Expands all objects in the model.
     */
    static void expand_objects(meta_model::model& m);

    /**
     * @brief Expands an object template.
     */
    static void
    expand_object_template(meta_model::structural::object_template& otp,
        meta_model::model& m,
        std::unordered_set<meta_model::name>& processed_names);

    /**
     * @brief Expands all object templates in the model.
     */
    static void expand_object_templates(meta_model::model& m);

public:
    /**
     * @brief Transforms the object templates the supplied model.
     */
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
