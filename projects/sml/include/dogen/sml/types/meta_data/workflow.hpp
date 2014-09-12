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
#ifndef DOGEN_SML_TYPES_META_DATA_WORKFLOW_HPP
#define DOGEN_SML_TYPES_META_DATA_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif


#include <memory>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/meta_data/grapher.hpp"
#include "dogen/sml/types/meta_data/registrar.hpp"
#include "dogen/sml/types/module_containment_graph.hpp"

namespace dogen {
namespace sml {
namespace meta_data {

class workflow {
public:
    workflow() = default;
    workflow(const workflow&) = default;
    ~workflow() = default;
    workflow(workflow&&) = default;
    workflow& operator=(const workflow&) = default;

private:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static registrar& get_registrar();

private:
    /**
     * @brief Setup the DAG of enrichers.
     */
    graph_type build_graph_activity();

public:
    /**
     * @brief Add the root enricher to the workflow.
     *
     * @pre the root enricher must not yet be registered.
     */
    static void register_root_enricher(std::shared_ptr<enricher_interface> e);

    /**
     * @brief Add an ordinary (non-root) enricher to the workflow.
     */
    static void register_ordinary_enricher(
        std::shared_ptr<enricher_interface> e);

public:
    /**
     * @brief Execute the meta-data workflow on the supplied model.
     *
     * @pre the root enricher must be registered.
     */
    void execute(const module_containment_graph& graph, model& m) const;

private:
    static std::unique_ptr<registrar> registrar_;
};

} } }

#endif
