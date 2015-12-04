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
#ifndef DOGEN_YARN_TYPES_ASSEMBLER_HPP
#define DOGEN_YARN_TYPES_ASSEMBLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/element.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Responsible for performing the assembly of an intermediate
 * yarn model.
 *
 * @section yarn_assembler_0 Requirements
 *
 * The intermediate models supplied as input are expected to have
 * already been through the expansion workflow. This is done to avoid
 * having to copy and modify these models.
 *
 * @section yarn_assembler_1 Workflow description
 *
 * Assembly is defined as a workflow that starts with a set of
 * intermediate models produced by the frontends, merges them into the
 * @merged intermediate model and then applies a series of operations
 * to the merged intermediate model to produce the final result. The
 * sequence in which the operations are done is important and is
 * dependent on the requirements of the classes responsible for those
 * operations.
 *
 */
class assembler {
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
     * @brief Create the merged intermediate model.
     */
    intermediate_model create_merged_model_activity(
        const std::list<intermediate_model>& models) const;

    /**
     * @brief Inject system-generated elements.
     */
    void inject_system_elements_activity(
        intermediate_model& merged_model) const;

    /**
     * @brief Ensures all references to elements point to elements in
     * the merged model.
     */
    void resolve_element_references_activity(
        intermediate_model& merged_model) const;

    /**
     * @brief Index all generalization relationships.
     */
    void index_generalizations_activity(intermediate_model& merged_model) const;

    /**
     * @brief Index all concepts.
     */
    void index_concepts_activity(intermediate_model& merged_model) const;

    /**
     * @brief Index all properties.
     */
    void index_properties_activity(intermediate_model& merged_model) const;

    /**
     * @brief Index all associations.
     */
    void index_associations_activity(intermediate_model& merged_model) const;

    /**
     * @brief Determines if the type has generatable types or not and
     * updates the flag accordingly.
     */
    void update_model_generability_activity(
        intermediate_model& merged_model) const;

public:
    /**
     * @brief Executes the assembly workflow.
     */
    intermediate_model assemble(const std::list<intermediate_model>& m) const;
};

} }

#endif
