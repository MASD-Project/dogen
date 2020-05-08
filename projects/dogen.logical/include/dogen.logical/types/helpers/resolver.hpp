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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_RESOLVER_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/helpers/indices.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Resolves type references within a model.
 *
 * Properties may come in from transformation missing information in
 * their names - such as the model name, etc. The resolver fills in
 * the missing gaps.
 *
 * The resolver is also responsible for making sure that all
 * references to types (e.g. names) can be resolved to a type in the
 * model.
 */
class resolver final {
private:
    static bool is_floating_point(const entities::model& m,
        const entities::name& n);
    static bool is_builtin(const entities::model& m,
        const entities::name& n);
    static bool is_primitive(const entities::model& m,
        const entities::name& n);
    static bool is_object(const entities::model& m,
        const entities::name& n);
    static bool is_enumeration(const entities::model& m,
        const entities::name& n);
    static bool is_object_template(const entities::model& m,
        const entities::name& n);

private:
    /**
     * @brief Returns true if the name is in the model and can be
     * referred to from an attribute, false otherwise.
     */
    static bool is_name_referable(const indices& idx,
        const entities::name& n);

    /**
     * @brief Resolves a name that has internal modules set.
     */
    static entities::name resolve_name_with_internal_modules(
        const entities::model& m, const indices& idx,
        const entities::name& ctx, const entities::name& n);

    /**
     * @brief Resolves a name where the ctx has internal modules.
     */
    static boost::optional<entities::name>
    try_resolve_name_with_context_internal_modules(
        const indices& idx, entities::name ctx, const entities::name& n);

    /**
     * @brief Resolves a name where the ctx has model modules.
     */
    static boost::optional<entities::name>
    try_resolve_name_with_context_model_modules(
        const indices& idx, entities::name ctx, const entities::name& n);

    /**
     * @brief Resolves a partially formed name into a full name.
     */
    static entities::name resolve_name(
        const entities::model& m, const indices& idx,
        const entities::name& ctx, const entities::name& n);

    /**
     * @brief Resolves all references contained in a name tree.
     */
    static void resolve_name_tree(const entities::model& m,
        const indices& idx, const entities::name& owner,
        entities::name_tree& nt);

    /**
     * @brief Resolves all references to types in the supplied attribute.
     */
    static void resolve_attribute(const entities::model& m,
        const indices& idx, const entities::name& owner,
        entities::attribute& attr);

    /**
     * @brief Resolves all references to types in the supplied attributes.
     */
    static void resolve_attributes(const entities::model& m,
        const indices& idx, const entities::name& owner,
        std::list<entities::attribute>& attributes);

    /**
     * @brief Validates the inheritance graph for the object.
     *
     * @note should really be moved to validator.
     */
    static void validate_inheritance_graph(
        const entities::model& m,
        const entities::structural::object& o);

    /**
     * @brief Ensures that all object templates that are parents of
     * the current object template are defined in the model.
     *
     * @note should really be moved to validator.
     */
    static void validate_object_template_inheritance(
        const entities::model& m,
        const entities::structural::object_template& ot);

    /**
     * @brief Resolve all object templates.
     */
    static void resolve_object_templates(const indices& idx,
        entities::model& m);

    /**
     * @brief Resolve all objects.
     */
    static void resolve_objects(const indices& idx,
        entities::model& m);

    /**
     * @brief Resolve all enumerations.
     */
    static void resolve_enumerations(const indices& idx,
        entities::model& m);

    /**
     * @brief Resolve all primitives.
     */
    static void resolve_primitives(const indices& idx,
        entities::model& m);

    /**
     * @brief Resolve all feature template bundles.
     */
    static void resolve_feature_template_bundles(const indices& idx,
        entities::model& m);

    /**
     * @brief Resolve all feature bundles.
     */
    static void resolve_feature_bundles(const indices& idx,
        entities::model& m);

    /**
     * @brief Resolve all archetypes.
     */
    static void resolve_archetypes(const indices& idx, entities::model& m);

public:
    /**
     * @brief Resolves the name against the supplied model.
     */
    static entities::name resolve(const entities::model& m,
        const indices& idx, const entities::name& ctx,
        const entities::name& n);

    /**
     * @brief Resolves the name as an object template name.
     */
    /**@{*/
    static boost::optional<entities::name>
    try_resolve_object_template_name(entities::name ctx,
        const std::string& s, const entities::model& m);
    static boost::optional<entities::name>
    try_resolve_object_template_name(const entities::name& ctx,
        const entities::name& n, const entities::model& m);
    /**@}*/

public:
    /**
     * @brief Resolve all references to types within model.
     */
    static void resolve(const indices& idx, entities::model& m);
};

}

#endif
