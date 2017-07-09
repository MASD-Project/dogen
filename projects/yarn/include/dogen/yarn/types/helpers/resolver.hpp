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
#ifndef DOGEN_YARN_TYPES_HELPERS_RESOLVER_HPP
#define DOGEN_YARN_TYPES_HELPERS_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/optional.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/helpers/indices.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

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
    static bool is_floating_point(const intermediate_model& im, const name& n);
    static bool is_builtin(const intermediate_model& im, const name& n);
    static bool is_primitive(const intermediate_model& im, const name& n);
    static bool is_object(const intermediate_model& im, const name& n);
    static bool is_enumeration(const intermediate_model& im, const name& n);
    static bool is_concept(const intermediate_model& im, const name& n);

private:
    /**
     * @brief Returns true if the name is in the model and can be
     * referred to from an attribute, false otherwise.
     */
    static bool is_name_referable(const indices& idx, const name& n);

    /**
     * @brief Resolves a name that has internal modules set.
     */
    static name resolve_name_with_internal_modules(const intermediate_model& im,
        const indices& idx, const name& ctx, const name& n);

    /**
     * @brief Resolves a name where the ctx has internal modules.
     */
    static boost::optional<name> try_resolve_name_with_context_internal_modules(
        const indices& idx, name ctx, const name& n);

    /**
     * @brief Resolves a partially formed name into a full name.
     */
    static name resolve_name(const intermediate_model& im,
        const indices& idx, const name& ctx, const name& n);

    /**
     * @brief Resolves all references contained in a name tree.
     */
    static void resolve_name_tree(const intermediate_model& im,
        const indices& idx, const name& owner, name_tree& nt);

    /**
     * @brief Resolves all references to types in the supplied attribute.
     */
    static void resolve_attribute(const intermediate_model& im,
        const indices& idx, const name& owner, attribute& attr);

    /**
     * @brief Resolves all references to types in the supplied attributes.
     */
    static void resolve_attributes(const intermediate_model& im,
        const indices& idx, const name& owner,
        std::list<attribute>& attributes);

    /**
     * @brief Validates the inheritance graph for the object.
     *
     * @note should really be moved to validator.
     */
    static void validate_inheritance_graph(const intermediate_model& im,
        const object& o);

    /**
     * @brief Ensures that all concepts refined by the current concept
     * are defined in the model.
     *
     * @note should really be moved to validator.
     */
    static void validate_refinements(const intermediate_model& im,
        const concept& c);

    /**
     * @brief Resolve all concepts.
     */
    static void resolve_concepts(const indices& idx,
        intermediate_model& im);

    /**
     * @brief Resolve all objects.
     */
    static void resolve_objects(const indices& idx, intermediate_model& im);

    /**
     * @brief Resolve all enumerations.
     */
    static void resolve_enumerations(intermediate_model& im);

    /**
     * @brief Resolve all primitives.
     */
    static void resolve_primitives(const indices& idx, intermediate_model& im);

public:
    /**
     * @brief Resolves the name against the supplied model.
     */
    static name resolve(const intermediate_model& im, const indices& idx,
        const name& ctx, const name& n);

    /**
     * @brief Resolves the name as a concept name.
     */
    static boost::optional<name> try_resolve_concept_name(name ctx,
        const std::string& s, const intermediate_model& im);

public:
    /**
     * @brief Resolve all references to types within model.
     */
    static void resolve(const indices& idx, intermediate_model& im);
};

} } }

#endif
