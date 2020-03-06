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
#ifndef DOGEN_ASSETS_TYPES_HELPERS_RESOLVER_HPP
#define DOGEN_ASSETS_TYPES_HELPERS_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/optional.hpp>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/structural/object_template.hpp"
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/types/helpers/indices.hpp"

namespace dogen::assets::helpers {

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
    static bool is_floating_point(const meta_model::model& m,
        const meta_model::name& n);
    static bool is_builtin(const meta_model::model& m,
        const meta_model::name& n);
    static bool is_primitive(const meta_model::model& m,
        const meta_model::name& n);
    static bool is_object(const meta_model::model& m,
        const meta_model::name& n);
    static bool is_enumeration(const meta_model::model& m,
        const meta_model::name& n);
    static bool is_object_template(const meta_model::model& m,
        const meta_model::name& n);

private:
    /**
     * @brief Returns true if the name is in the model and can be
     * referred to from an attribute, false otherwise.
     */
    static bool is_name_referable(const indices& idx,
        const meta_model::name& n);

    /**
     * @brief Resolves a name that has internal modules set.
     */
    static meta_model::name resolve_name_with_internal_modules(
        const meta_model::model& m, const indices& idx,
        const meta_model::name& ctx, const meta_model::name& n);

    /**
     * @brief Resolves a name where the ctx has internal modules.
     */
    static boost::optional<meta_model::name>
    try_resolve_name_with_context_internal_modules(
        const indices& idx, meta_model::name ctx, const meta_model::name& n);

    /**
     * @brief Resolves a name where the ctx has model modules.
     */
    static boost::optional<meta_model::name>
    try_resolve_name_with_context_model_modules(
        const indices& idx, meta_model::name ctx, const meta_model::name& n);

    /**
     * @brief Resolves a partially formed name into a full name.
     */
    static meta_model::name resolve_name(
        const meta_model::model& m, const indices& idx,
        const meta_model::name& ctx, const meta_model::name& n);

    /**
     * @brief Resolves all references contained in a name tree.
     */
    static void resolve_name_tree(const meta_model::model& m,
        const indices& idx, const meta_model::name& owner,
        meta_model::name_tree& nt);

    /**
     * @brief Resolves all references to types in the supplied attribute.
     */
    static void resolve_attribute(const meta_model::model& m,
        const indices& idx, const meta_model::name& owner,
        meta_model::attribute& attr);

    /**
     * @brief Resolves all references to types in the supplied attributes.
     */
    static void resolve_attributes(const meta_model::model& m,
        const indices& idx, const meta_model::name& owner,
        std::list<meta_model::attribute>& attributes);

    /**
     * @brief Validates the inheritance graph for the object.
     *
     * @note should really be moved to validator.
     */
    static void validate_inheritance_graph(
        const meta_model::model& m,
        const meta_model::structural::object& o);

    /**
     * @brief Ensures that all object templates that are parents of
     * the current object template are defined in the model.
     *
     * @note should really be moved to validator.
     */
    static void validate_object_template_inheritance(
        const meta_model::model& m,
        const meta_model::structural::object_template& ot);

    /**
     * @brief Resolve all object templates.
     */
    static void resolve_object_templates(const indices& idx,
        meta_model::model& m);

    /**
     * @brief Resolve all objects.
     */
    static void resolve_objects(const indices& idx,
        meta_model::model& m);

    /**
     * @brief Resolve all enumerations.
     */
    static void resolve_enumerations(const indices& idx,
        meta_model::model& m);

    /**
     * @brief Resolve all primitives.
     */
    static void resolve_primitives(const indices& idx,
        meta_model::model& m);

    /**
     * @brief Resolve all feature bundles.
     */
    static void resolve_feature_template_bundles(const indices& idx,
        meta_model::model& m);

public:
    /**
     * @brief Resolves the name against the supplied model.
     */
    static meta_model::name resolve(const meta_model::model& m,
        const indices& idx, const meta_model::name& ctx,
        const meta_model::name& n);

    /**
     * @brief Resolves the name as an object template name.
     */
    /**@{*/
    static boost::optional<meta_model::name>
    try_resolve_object_template_name(meta_model::name ctx,
        const std::string& s, const meta_model::model& m);
    static boost::optional<meta_model::name>
    try_resolve_object_template_name(const meta_model::name& ctx,
        const meta_model::name& n, const meta_model::model& m);
    /**@}*/

public:
    /**
     * @brief Resolve all references to types within model.
     */
    static void resolve(const indices& idx, meta_model::model& m);
};

}

#endif
