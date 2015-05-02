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
#ifndef DOGEN_DYNAMIC_EXPANSION_TYPES_WORKFLOW_HPP
#define DOGEN_DYNAMIC_EXPANSION_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/dynamic/expansion/types/grapher.hpp"
#include "dogen/dynamic/expansion/types/registrar.hpp"
#include "dogen/dynamic/expansion/types/expansion_context.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

/**
 * @brief Orchestrator for the expansion workflow.
 */
class workflow {
public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static expansion::registrar& registrar();

private:
    /**
     * @brief Ensures the workflow is in a valid state.
     */
    void validate() const;

private:
    /**
     * @brief Creates a graph of expanders.
     */
    graph_type build_expander_graph_activity() const;

    /**
     * @brief Creates the expansion context.
     */
    expansion_context create_expansion_context_activity(
        const config::cpp_options& options,
        const schema::repository& rp,
        const sml::model& m) const;

    /**
     * @brief Performs the expansion.
     */
    void perform_expansion_activity(const graph_type& g,
        expansion_context& ec) const;

public:
    /**
     * @brief Expands the dynamic fields in the object.
     */
    sml::model execute(
        const config::cpp_options& options,
        const schema::repository& rp,
        const sml::model& m) const;

private:
    static std::shared_ptr<expansion::registrar> registrar_;
};

} } }

#endif
