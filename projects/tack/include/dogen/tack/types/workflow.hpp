/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_TACK_TYPES_WORKFLOW_HPP
#define DOGEN_TACK_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include "dogen/tack/types/model.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Responsible for executing a complete Tack workflow.
 */
class workflow {
public:
    workflow() = default;
    workflow(const workflow&) = default;
    ~workflow() = default;
    workflow(workflow&&) = default;
    workflow& operator=(const workflow&) = default;

private:
    /**
     * @brief Returns true if the type is generatable, false
     * otherwise.
     */
    bool is_generatable(const type& t) const;

private:
    /**
     * @brief Create the merged model.
     */
    model create_merged_model_activity(const std::list<model>& models) const;

    /**
     * @brief Index all generalizations.
     */
    void index_generalizations_activity(model& merged_model) const;

    /**
     * @brief Injects system types into the model.
     */
    void inject_system_types_activity(model& m) const;

    /**
     * @brief Resolve all types.
     */
    void resolve_types_activity(model& merged_model) const;

    /**
     * @brief Index all concepts in model.
     */
    void index_concepts_activity(model& merged_model) const;

    /**
     * @brief Index all properties in model.
     */
    void index_properties_activity(model& merged_model) const;

    /**
     * @brief Index all associations.
     */
    void index_associations_activity(model& merged_model) const;

    /**
     * @brief Determines if the type has generatable types or not and
     * updates the flag accordingly.
     */
    void update_model_generability_activity(model& merged_model) const;

private:
    /**
     * @brief Returns true if there are any types that require code
     * generation, false otherwise.
     */
    bool has_generatable_types(const model& model) const;

public:
    /**
     * @brief Executes the workflow.
     *
     * @note parameter copied by design.
     */
    model execute(std::list<model> models) const;
};

} }

#endif
