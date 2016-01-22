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
#ifndef DOGEN_YARN_TYPES_RESOLVER_HPP
#define DOGEN_YARN_TYPES_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/concept.hpp"

namespace dogen {
namespace yarn {

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
class resolver {
private:
    /**
     * @brief Returns true if the name is in the model, false
     * otherwise.
     */
    bool is_name_in_model(const intermediate_model& m, const name& n) const;

    /**
     * @brief Resolves a partially formed name into a full name.
     */
    name resolve_partial_type(const intermediate_model& m, const name& n) const;

    /**
     * @brief Resolves all references contained in a nested name.
     */
    void resolve_partial_type(const intermediate_model& m,
        nested_name& nn) const;

    /**
     * @brief Resolves all references to types in the supplied properties.
     */
    void resolve_properties(const intermediate_model& m,
        const name& owner, std::list<property>& p) const;

    /**
     * @brief Validates the inheritance graph for the object.
     *
     * @note should really be moved to validator.
     */
    void validate_inheritance_graph(const intermediate_model& m,
        const object& o) const;

    /**
     * @brief Ensures that all concepts refined by the current concept
     * are defined in the model.
     *
     * @note should really be moved to validator.
     */
    void validate_refinements(const intermediate_model& m,
        const concept& c) const;

    /**
     * @brief Resolve all concepts.
     */
    void resolve_concepts(intermediate_model& m) const;

    /**
     * @brief Resolve all objects.
     */
    void resolve_objects(intermediate_model& m) const;

public:
    /**
     * @brief Resolve all references to types within model.
     *
     * @pre Resolution has not been performed yet.
     */
    void resolve(intermediate_model& m) const;
};

} }

#endif
