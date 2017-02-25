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
#ifndef DOGEN_YARN_TYPES_SECOND_STAGE_EXPANDER_HPP
#define DOGEN_YARN_TYPES_SECOND_STAGE_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/injector_registrar.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/indices.hpp"

namespace dogen {
namespace yarn {

class second_stage_expander {
private:
    /**
     * @brief Returns true if the element belongs to the target model,
     * false otherwise.
     */
    bool is_generatable(const element& e) const;

    /**
     * @brief Returns true if there are any types that require code
     * generation, false otherwise.
     */
    bool has_generatable_types(const intermediate_model& m) const;

private:
    /**
     * @brief Creates the merged intermediate model.
     */
    intermediate_model
    merge_intermediate_models(const std::list<intermediate_model>& ims) const;

    /**
     * @brief Expands all enumerations.
     */
    void expand_enumerations(const annotations::type_repository& atrp,
        intermediate_model& im) const;

    /**
     * @brief Create indices.
     */
    indices create_indices(intermediate_model& im) const;

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
    void resolve_element_references(const indices& idx,
        intermediate_model& im) const;

    /**
     * @brief Expand all generalization relationships.
     */
    void expand_generalizations(const annotations::type_repository& atrp,
        const indices& idx, intermediate_model& im) const;

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
    void inject_model(const annotations::type_repository& atrp,
        const annotations::annotation& ra, const injector_registrar& rg,
        intermediate_model& im) const;

    /**
     * @brief Ensures the model passes all validation rules.
     */
    void validate(const indices& idx, const intermediate_model& im) const;

public:
    /**
     * @brief Make the final model.
     */
    intermediate_model
    make(const annotations::type_repository& atrp, const injector_registrar& rg,
        const std::list<intermediate_model>& ims) const;
};

} }

#endif
