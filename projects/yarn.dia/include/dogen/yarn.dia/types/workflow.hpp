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
#ifndef DOGEN_YARN_DIA_TYPES_WORKFLOW_HPP
#define DOGEN_YARN_DIA_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include "dogen/dia/types/diagram_fwd.hpp"
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/types/builder.hpp"
#include "dogen/yarn.dia/types/validator.hpp"
#include "dogen/yarn.dia/types/grapher.hpp"

namespace dogen {
namespace yarn {
namespace dia {

class workflow {
public:
    workflow() = default;
    workflow(const workflow&) = delete;
    workflow(workflow&&) = default;
    ~workflow() = default;

private:
    std::list<processed_object>
    create_processed_objects(const dogen::dia::diagram& d) const;

    void validate_processed_objects(
        const std::list<processed_object>& pos) const;

    std::string obtain_external_modules(
        const std::list<processed_object>& pos) const;

private:
    /**
     * @brief Setup the DAG of processed objects.
     */
    std::pair<graph_type,
              const std::unordered_map<std::string, std::list<std::string>>
              >
    generate_graph(const std::list<processed_object>& pos);

    builder create_builder(const std::string& model_name,
        const std::string& external_modules,
        const std::unordered_map<std::string, std::list<std::string>>&
        child_id_to_parent_ids) const;

    /**
     * @brief Transforms the entire graph of processed objects into a
     * Yarn model.
     */
    meta_model::intermediate_model
    generate_model(builder& b, const graph_type& g);

public:
    meta_model::intermediate_model execute(const dogen::dia::diagram& diagram,
        const std::string& model_name);
};

} } }

#endif
