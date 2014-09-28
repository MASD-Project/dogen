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
#ifndef DOGEN_SML_TYPES_WORKFLOW_HPP
#define DOGEN_SML_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include "dogen/config/types/knitting_settings.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Responsible for executing a complete SML workflow.
 */
class workflow {
public:
    workflow() = delete;
    workflow(const workflow&) = default;
    ~workflow() = default;
    workflow(workflow&&) = default;
    workflow& operator=(const workflow&) = default;

public:
    explicit workflow(const config::knitting_settings& s);

private:
    /**
     * @brief Returns true if the type is generatable, false
     * otherwise.
     */
    bool is_generatable(const type& t) const;

private:
    /**
     * @brief Injects system types into model.
     */
    void inject_system_types_activity(std::list<model>& models) const;

    /**
     * @brief Create the merged model.
     */
    model create_merged_model_activity(const std::list<model>& models) const;

    /**
     * @brief Resolve all types.
     */
    void resolve_types_activity(model& merged_model) const;

    /**
     * @brief Add meta-data to merged model.
     */
    void process_meta_data_activity(model& merged_model) const;

    /**
     * @brief Index all concepts in model.
     */
    void index_concepts_activity(model& merged_model) const;

    /**
     * @brief Index all properties in model.
     */
    void index_properties_activity(model& merged_model) const;

    /**
     * @brief Index all associations of all objects in model.
     */
    void index_associations_activity(model& merged_model) const;

private:
    /**
     * @brief Returns true if there are any types that require code
     * generation, false otherwise.
     */
    bool has_generatable_types(const sml::model& model) const;

public:
    /**
     * @brief Executes the workflow.
     *
     * @note parameter copied by design.
     */
    std::pair<bool, model> execute(std::list<model> models) const;

private:
    const config::knitting_settings settings_;
};

} }

#endif
