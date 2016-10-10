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
#ifndef DOGEN_YARN_TYPES_POST_MERGE_WORKFLOW_HPP
#define DOGEN_YARN_TYPES_POST_MERGE_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/injector_registrar.hpp"
#include "dogen/yarn/types/element.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Responsible for performing all the tasks after the merging
 * of the models has taken place.
 */
class post_merge_workflow {
private:
    /**
     * @brief Returns true if the element is generatable, false
     * otherwise.
     */
    bool is_generatable(const element& e) const;

    /**
     * @brief Returns true if there are any types that require code
     * generation, false otherwise.
     */
    bool has_generatable_types(const intermediate_model& m) const;

private:
    /**
     * @brief Create indices.
     */
    void create_indices(intermediate_model& im) const;

    /**
     * @brief Expand all stereotypes used in model.
     */
    void expand_stereotypes(intermediate_model& im) const;

    /**
     * @brief Expand element containment.
     */
    void expand_containment(intermediate_model& im) const;

    /**
     * @brief Ensures all references point to elements in the model.
     */
    void resolve_element_references(intermediate_model& im) const;

    /**
     * @brief Expand all generalization relationships.
     */
    void expand_generalizations(const dynamic::repository& drp,
        intermediate_model& im) const;

    /**
     * @brief Expand all concepts.
     */
    void expand_concepts(intermediate_model& im) const;

    /**
     * @brief Expand all attributes.
     */
    void expand_attributes(intermediate_model& im) const;

    /**
     * @brief Expand all associations.
     */
    void expand_associations(intermediate_model& im) const;

    /**
     * @brief Determines if the type has generatable types or not and
     * updates the flag accordingly.
     */
    void update_model_generability(intermediate_model& im) const;

    /**
     * @brief Injects any external types into the model.
     */
    void inject_model(const injector_registrar& rg,
        intermediate_model& im) const;

public:
    /**
     * @brief Executes the post-merge workflow.
     */
    void execute(const dynamic::repository& drp, const injector_registrar& rg,
        intermediate_model& im) const;
};

} }

#endif
